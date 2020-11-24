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

#ifndef SRC_GALTONBOARDWINDOW_H
#define SRC_GALTONBOARDWINDOW_H

#include <gtkmm/button.h>
#include <gtkmm/label.h>
#include <gtkmm/window.h>

#include "BoardDrawingArea.h"
#include "model/CreditManager.h"
#include "model/PlayTracker.h"

/*
 * GaltonBoardWindow is the main window of this application, comprising:
 * - a Galton board representation
 * - counters (credits, rounds)
 * - control buttons
 */
class GaltonBoardWindow : public Gtk::Window
{

 public:

    GaltonBoardWindow(BoardDrawingArea& boardDrawingArea, CreditManager creditManager,
            PlayTracker playTracker, unsigned int step_duration_ms);
    virtual ~GaltonBoardWindow();

 protected:

    BoardDrawingArea& _boardDrawingArea;
    CreditManager _creditManager;
    PlayTracker _playTracker;
    unsigned int _step_duration_ms;

    // Refresh the state of counter labels and control buttons
    void refresh_controls();
    // Handler of the CREDIT IN button click event
    void on_add_credit_clicked();
    // Handler of the CREDITS OUT button click event
    void on_withdraw_credits_clicked();
    // Handler of the PLAY button click event
    void on_play_clicked();
    // Handler of simulation step timer
    bool on_play_timer(int timer_id);

    // Id of the simulation step timer
    int _play_timer_id;
    // Generator of periodic timer events
    sigc::connection _play_timer;

    // Is the simulation playing?
    bool _is_playing;
    // Is the simulation paused?
    bool _is_paused;

    /*
     * Widgets that change or react to the application state
     */
    Gtk::Label _creditsInLabel;
    Gtk::Label _creditsOutLabel;
    Gtk::Label _nRoundsLabel;
    Gtk::Button _addCreditButton;
    Gtk::Button _withdrawCreditsButton;
    Gtk::Button _playButton;

};

#endif // SRC_GALTONBOARDWINDOW_H
