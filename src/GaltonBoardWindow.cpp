/*
* Copyright 2020 Rafael Lorandi <coolparadox@gmail.com>
*
* This file is part of galton-board, a naive game-like simulation of
* a Galton board.
* 
* galton-board is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
* 
* galton-board is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
* 
* You should have received a copy of the GNU General Public License
* along with galton-board  If not, see <http://www.gnu.org/licenses/>
*/

#include <cassert>

#include <glibmm/main.h>
#include <gtkmm/box.h>
#include <gtkmm/buttonbox.h>
#include <gtkmm/frame.h>

#include "GaltonBoardWindow.h"

GaltonBoardWindow::GaltonBoardWindow(BoardDrawingArea& boardDrawingArea, CreditManager creditManager,
        PlayTracker playTracker, unsigned int step_duration_ms)
    : _creditManager(creditManager),
      _playTracker(playTracker),
      _boardDrawingArea(boardDrawingArea),
      _addCreditButton("CREDIT IN"),
      _withdrawCreditsButton("CREDITS OUT"),
      _playButton("RESUME"),
      _creditsInLabel("0"),
      _creditsOutLabel("0"),
      _nRoundsLabel("0"),
      _play_timer_id(0),
      _is_playing(false),
      _is_paused(false),
      _step_duration_ms(step_duration_ms)
{
    assert(_step_duration_ms > 0);

    /*
     * Compose the UI
     */

    set_border_width(5);
    Gtk::Box* topBox { Gtk::make_managed<Gtk::Box>(Gtk::ORIENTATION_VERTICAL, 10) };
    add(*topBox);
    topBox->set_border_width(5);
    topBox->set_homogeneous(false);

    // UI: Board drawing area
    topBox->pack_start(_boardDrawingArea);

    // UI: User controls
    Gtk::Box* controlsBox { Gtk::make_managed<Gtk::Box>(Gtk::ORIENTATION_HORIZONTAL, 10) };
    topBox->pack_start(*controlsBox);

    // UI: Credits in
    Gtk::Frame* frame_in { Gtk::make_managed<Gtk::Frame>("Credits In") };
    controlsBox->pack_start(*frame_in);
    Gtk::Box* box_in { Gtk::make_managed<Gtk::Box>(Gtk::ORIENTATION_VERTICAL, 5) };
    frame_in->add(*box_in);
    box_in->pack_start(_creditsInLabel);
    box_in->pack_start(_addCreditButton);

    // UI: Credits out
    Gtk::Frame* frame_out { Gtk::make_managed<Gtk::Frame>("Credits Out") };
    controlsBox->pack_start(*frame_out);
    Gtk::Box* box_out { Gtk::make_managed<Gtk::Box>(Gtk::ORIENTATION_VERTICAL, 5) };
    frame_out->add(*box_out);
    box_out->pack_start(_creditsOutLabel);
    box_out->pack_start(_withdrawCreditsButton);

    // UI: Play count
    Gtk::Frame* frame_play { Gtk::make_managed<Gtk::Frame>("Play Count") };
    controlsBox->pack_start(*frame_play);
    Gtk::Box* box_play { Gtk::make_managed<Gtk::Box>(Gtk::ORIENTATION_VERTICAL, 5) };
    frame_play->add(*box_play);
    box_play->pack_start(_nRoundsLabel);
    box_play->pack_start(_playButton);
    _playButton.set_size_request(100, -1);  // Accomodate label changes

    // UI: refresh state
    refresh_controls();
    show_all_children();

    /*
     * Hook user events
     */

    _addCreditButton.signal_clicked().connect(sigc::mem_fun(*this, &GaltonBoardWindow::on_add_credit_clicked));
    _withdrawCreditsButton.signal_clicked().connect(sigc::mem_fun(*this, &GaltonBoardWindow::on_withdraw_credits_clicked));
    _playButton.signal_clicked().connect(sigc::mem_fun(*this, &GaltonBoardWindow::on_play_clicked));

}

GaltonBoardWindow::~GaltonBoardWindow()
{
}

void GaltonBoardWindow::refresh_controls()
{
    // Update the enablement of buttons
    _addCreditButton.set_sensitive(!_is_playing && _creditManager.can_deposit());
    _withdrawCreditsButton.set_sensitive(!_is_playing && _creditManager.can_withdraw());
    _playButton.set_sensitive(_creditManager.can_play());

    // Update the semantic of the PLAY button
    if (_is_playing)
    {
        if (_is_paused)
        {
            // Simulation is paused; reuse the PLAY button for resuming it.
            _playButton.set_label("RESUME");
        }
        else
        {
            // Simulation is ongoing; reuse the PLAY button for pausing it.
            _playButton.set_label("PAUSE");
        }
    }
    else
    {
        // Simulation is not happening; reuse the PLAY button for starting it.
        _playButton.set_label("START");
    }

    // Update exteriorization of the account balance
    _creditsInLabel.set_text(std::to_string(_creditManager.get_remaining_credits()));
    _creditsOutLabel.set_text(std::to_string(_creditManager.get_withdrawed_credits()));
    _nRoundsLabel.set_text(std::to_string(_creditManager.get_play_count()));
}

void GaltonBoardWindow::on_add_credit_clicked()
{
    _creditManager.add_credit();
    refresh_controls();
}

void GaltonBoardWindow::on_withdraw_credits_clicked()
{
    _creditManager.withdraw_credits();
    refresh_controls();
}

void GaltonBoardWindow::on_play_clicked()
{
    if (_is_playing && _is_paused)
    {
        // Simulation is paused; resume it.
        _is_paused = false;
        return;
    }

    if (_is_playing)
    {
        // Simulation is ongoing; pause it.
        _is_paused = true;
        refresh_controls();
        return;
    }

    // Simulation is not happening; start it.
    _is_playing = true;
    _is_paused = false;
    _playTracker.reset();

    // Start a periodic timer to sync the steps of the simulation.
    sigc::slot<bool> play_timer_slot = sigc::bind(sigc::mem_fun(*this, &GaltonBoardWindow::on_play_timer), _play_timer_id);
    _play_timer = Glib::signal_timeout().connect(play_timer_slot, _step_duration_ms);

    refresh_controls();
}

bool GaltonBoardWindow::on_play_timer(int timer_id)
{
    if (!_is_playing || _is_paused)
    {
        // Simulation is not happening or is paused; ignore the simulation timer.
        return true;
    }
    if (!_playTracker.step())
    {
        // The simulation came to an end; stop the simulation timer in order to stop generating events.
        _play_timer.disconnect();
        _play_timer_id = 0;
        _is_playing = false;
        _is_paused = false;
        _creditManager.register_play();
    }
    // Draw the new state of the simulation.
    _boardDrawingArea.queue_draw();
    // Refresh other widgets.
    refresh_controls();
    return true;

}
