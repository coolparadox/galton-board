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

#include "BoardDrawingArea.h"

const unsigned int BOARD_MARGIN = 10;

BoardDrawingArea::BoardDrawingArea(unsigned int n_levels, std::vector<Ball> grid)
    : BoardDrawingArea(n_levels, grid, 60, 5)
{
}

BoardDrawingArea::BoardDrawingArea(unsigned int n_levels, std::vector<Ball> grid, unsigned int ball_size, unsigned int peg_size)
    : _n_levels(n_levels),
      _grid(grid),
      _ball_size(ball_size),
      _peg_size(peg_size)
{
    assert(_n_levels >= 2);
    assert(_peg_size > 0);
    assert(_ball_size > _peg_size);
    _board_size = _n_levels * (_ball_size + _peg_size) + _peg_size;
    set_size_request(_board_size + 2 * BOARD_MARGIN, _board_size + 2 * BOARD_MARGIN);
}

BoardDrawingArea::~BoardDrawingArea()
{
}

bool BoardDrawingArea::on_draw(const Cairo::RefPtr<Cairo::Context>& cr)
{
    const int x_offset = (get_allocated_width() - _board_size) / 2;
    const int y_offset = (get_allocated_height() - _board_size) / 2;

    // coordinates for the center of the board
    int xc, yc;
    xc = _board_size / 2;
    yc = _board_size / 2;

    cr->set_line_width(10.0);

    // draw red lines out from the center of the window
    cr->set_source_rgb(0.8, 0.0, 0.0);
    cr->move_to(0 + x_offset, 0 + y_offset);
    cr->line_to(_board_size + x_offset, _board_size + y_offset);
    cr->stroke();

    return true;
}
