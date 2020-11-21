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

    // Board drawing area
    topBox->pack_start(_boardDrawingArea);

    // User controls
    Gtk::Box* controlsBox { Gtk::make_managed<Gtk::Box>(Gtk::ORIENTATION_HORIZONTAL, 10) };
    topBox->pack_start(*controlsBox);

    // Credits in
    Gtk::Frame* frame_in { Gtk::make_managed<Gtk::Frame>("Credits In") };
    controlsBox->pack_start(*frame_in);
    Gtk::Box* box_in { Gtk::make_managed<Gtk::Box>(Gtk::ORIENTATION_VERTICAL, 5) };
    frame_in->add(*box_in);
    box_in->pack_start(_creditsInLabel);
    box_in->pack_start(_addCreditButton);

    // Credits out
    Gtk::Frame* frame_out { Gtk::make_managed<Gtk::Frame>("Credits Out") };
    controlsBox->pack_start(*frame_out);
    Gtk::Box* box_out { Gtk::make_managed<Gtk::Box>(Gtk::ORIENTATION_VERTICAL, 5) };
    frame_out->add(*box_out);
    box_out->pack_start(_creditsOutLabel);
    box_out->pack_start(_withdrawCreditsButton);

    // Play count
    Gtk::Frame* frame_play { Gtk::make_managed<Gtk::Frame>("Play Count") };
    controlsBox->pack_start(*frame_play);
    Gtk::Box* box_play { Gtk::make_managed<Gtk::Box>(Gtk::ORIENTATION_VERTICAL, 5) };
    frame_play->add(*box_play);
    box_play->pack_start(_nRoundsLabel);
    box_play->pack_start(_playButton);

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
