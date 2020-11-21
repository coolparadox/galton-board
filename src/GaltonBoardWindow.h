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

class GaltonBoardWindow : public Gtk::Window
{

 public:

    GaltonBoardWindow(CreditManager creditManager);
    virtual ~GaltonBoardWindow();

 protected:

    CreditManager _creditManager;

    BoardDrawingArea _boardDrawingArea;
    Gtk::Label _creditsInLabel;
    Gtk::Label _creditsOutLabel;
    Gtk::Label _nRoundsLabel;
    Gtk::Button _addCreditButton;
    Gtk::Button _withdrawCreditsButton;
    Gtk::Button _playButton;

};

#endif // SRC_GALTONBOARDWINDOW_H