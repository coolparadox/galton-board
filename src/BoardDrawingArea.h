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

#ifndef SRC_BOARDDRAWINGAREA_H
#define SRC_BOARDDRAWINGAREA_H

#include <gtkmm/drawingarea.h>

#include "model/Ball.h"

/*
 * BoardDrawingArea is a graphical 2D representation of a Galton board
 * with positions eventually filled with balls.
 */
class BoardDrawingArea : public Gtk::DrawingArea
{

 public:

    BoardDrawingArea(unsigned int n_levels, std::vector<Ball>& balls, unsigned int ball_size,
            unsigned int peg_size, unsigned int n_colors);
    virtual ~BoardDrawingArea();

 protected:

    // Number of levels of the board.
    unsigned int _n_levels;
    // Balls that are currently in the board.
    std::vector<Ball>& _balls;
    // Diameter of each ball [pixels].
    unsigned int _ball_size;
    // Diameter of each board peg [pixels].
    unsigned int _peg_size;
    // Number of distinct colors of the balls.
    unsigned int _n_colors;
    // Size of the board [pixels].
    unsigned int _board_size;

    // Draw the background of the widget.
    void draw_background(const Cairo::RefPtr<Cairo::Context>& cr);
    // Draw the board contour.
    void draw_contour(const Cairo::RefPtr<Cairo::Context>& cr);
    // Draw the board pegs.
    void draw_pegs(const Cairo::RefPtr<Cairo::Context>& cr);
    // Draw the balls currently in the board.
    void draw_balls(const Cairo::RefPtr<Cairo::Context>& cr);
    // Set the pen color for drawing a given ball.
    void set_color_from_ball(const Cairo::RefPtr<Cairo::Context>& cr, const Ball& ball);

    // Drawing event handler.
    bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;

};

#endif // SRC_BOARDDRAWINGAREA_H
