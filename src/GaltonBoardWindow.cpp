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

#include <gtkmm/box.h>
#include <gtkmm/buttonbox.h>
#include <gtkmm/frame.h>

#include "GaltonBoardWindow.h"

GaltonBoardWindow::GaltonBoardWindow(CreditManager creditManager)
    : _creditManager(creditManager),
      _addCreditButton("CREDIT IN"),
      _withdrawCreditsButton("CREDITS OUT"),
      _playButton("START"),
      _creditsInLabel("0"),
      _creditsOutLabel("0"),
      _nRoundsLabel("0")
{
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
    _withdrawCreditsButton.set_sensitive(_creditManager.can_withdraw());
    _playButton.set_sensitive(_creditManager.can_play());
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
    _creditManager.register_play();
    refresh_controls();
}
