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

#include <gtkmm/application.h>
#include "src/GaltonBoardWindow.h"

/*
 * Application settings
 */

// Number of levels a ball must fall to get to the bottom
const unsigned int n_levels = 10;

// Time between each step of the simulation [ms]
const unsigned int step_duration_ms = 100;

// Diameter of the balls [pixels]
const unsigned int ball_size = 25;

// Diameter of the pegs [pixels]
const unsigned int peg_size = 4;

// Length of ball color cycling (maximum 6)
const unsigned int n_colors = 6;

/*
 * Some parameters that are defined by the above settings:
 *
 * - Total amount of balls entering the simulation: n_balls = n_levels * (n_levels + 1) / 2
 * - Total simulation time [ms]: sim_time = n_balls * step_duration_ms
 * - Board size [pixels]: board_size = n_levels * (ball_size + peg_size) + peg_size
 * - Drawing widget size [pixels]: drawing_size = board_size + 20
 *
 * KNOWN ISSUES
 * The rendering of the drawing widget is based on full redrawing --
 * it does not scale well with the increase of the number of objects in the scene.
 */

int main(int argc, char *argv[])
{
    Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(argc, argv, "coolparadox.com.games.galton-board");
    std::vector<Ball> grid;
    BoardDrawingArea boardDrawingArea(n_levels, grid, ball_size, peg_size, n_colors);
    GaltonBoardWindow window(boardDrawingArea, CreditManager(), PlayTracker(n_levels, grid), step_duration_ms);
    return app->run(window);
}
