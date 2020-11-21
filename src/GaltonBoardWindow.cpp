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

#include "GaltonBoardWindow.h"

GaltonBoardWindow::GaltonBoardWindow()
    : _addCreditButton("Add Credit"),
      _withdrawCreditsButton("Withdraw Credits"),
      _playButton("Play")
{
    /*
     * Compose the UI:
     * - drawing area
     * - button row
     */
    set_border_width(5);
    Gtk::Box* topBox { Gtk::make_managed<Gtk::Box>(Gtk::ORIENTATION_VERTICAL, 5) };
    add(*topBox);
    topBox->set_border_width(5);
    topBox->set_homogeneous(false);
    topBox->pack_start(_boardDrawingArea);
    Gtk::ButtonBox* buttons { Gtk::make_managed<Gtk::ButtonBox>(Gtk::ORIENTATION_HORIZONTAL) };
    topBox->pack_start(*buttons);
    buttons->add(_addCreditButton);
    buttons->add(_withdrawCreditsButton);
    buttons->add(_playButton);
    show_all_children();

    // m_button.signal_clicked().connect(sigc::mem_fun(*this, &GaltonBoardWindow::on_button_clicked));
}

GaltonBoardWindow::~GaltonBoardWindow()
{
}

//void GaltonBoardWindow::on_button_clicked()
//{
//    std::cout << "Hello World" << std::endl;
//}
