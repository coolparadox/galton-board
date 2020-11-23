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

BoardDrawingArea::BoardDrawingArea(unsigned int n_levels, std::vector<Ball>& grid,
        unsigned int ball_size, unsigned int peg_size, unsigned int n_colors)
    : _n_levels(n_levels),
      _grid(grid),
      _ball_size(ball_size),
      _peg_size(peg_size),
      _n_colors(n_colors)
{
    assert(_n_levels >= 2);
    assert(_n_colors > 0);
    assert(_n_colors <= 6);
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
    draw_background(cr);
    cr->translate((get_allocated_width() - _board_size) / 2, (get_allocated_height() - _board_size) / 2);
    draw_contour(cr);
    draw_pegs(cr);
    draw_balls(cr);
    return true;
}

void BoardDrawingArea::draw_background(const Cairo::RefPtr<Cairo::Context>& cr)
{
    cr->save();
    cr->set_source_rgb(0.5, 0.5, 0.5);
    cr->set_line_width(1);
    cr->move_to(0,0);
    cr->line_to(get_allocated_width(), 0);
    cr->line_to(get_allocated_width(), get_allocated_height());
    cr->line_to(0, get_allocated_height());
    cr->close_path();
    cr->fill_preserve();
    cr->stroke();
    cr->restore();
}

void BoardDrawingArea::draw_contour(const Cairo::RefPtr<Cairo::Context>& cr)
{
    cr->save();
    cr->set_line_width(1);
    cr->set_source_rgb(1, 1, 1);
    cr->move_to(_board_size / 2, -_ball_size - _ball_size / 2);
    cr->line_to(_board_size + _ball_size, _board_size);
    cr->line_to(-_ball_size, _board_size);
    cr->close_path();
    cr->fill_preserve();
    cr->stroke();
    cr->restore();
}

void BoardDrawingArea::draw_pegs(const Cairo::RefPtr<Cairo::Context>& cr)
{
    cr->save();
    cr->set_line_width(1);
    cr->set_source_rgb(0.5, 0.5, 0.5);
    for (int level = 0; level < _n_levels; ++level)
    {
        for (int displacement = -level; displacement <= level; displacement += 2)
        {
            cr->arc(displacement * (_ball_size + _peg_size) / 2 + _board_size / 2,
                    level * (_ball_size + _peg_size) + _ball_size,
                    _peg_size / 2, 0.0, 2.0 * M_PI);
            cr->fill_preserve();
            cr->stroke();
        }
    }
    cr->restore();
}

void set_color_from_ball(const Cairo::RefPtr<Cairo::Context>& cr, const Ball& ball);

void BoardDrawingArea::draw_balls(const Cairo::RefPtr<Cairo::Context>& cr)
{
    for (auto ball = _grid.cbegin(); ball != _grid.cend(); ++ball)
    {
        cr->save();
        cr->set_line_width(1.0);
        set_color_from_ball(cr, *ball);
        cr->arc(ball->get_displacement() * (_ball_size + _peg_size) / 2 + _board_size / 2,
                ball->get_level() * (_ball_size + _peg_size) + _ball_size / 2 - _peg_size / 2,
                _ball_size / 2 + _peg_size / 4, 0.0, 2.0 * M_PI);
        cr->fill_preserve();
        cr->restore();
        cr->stroke();
    }
}

void BoardDrawingArea::set_color_from_ball(const Cairo::RefPtr<Cairo::Context>& cr, const Ball& ball)
{
    switch (ball.get_id() % _n_colors)
    {
        case 0:
            cr->set_source_rgb(1, 0, 0);
            break;
        case 1:
            cr->set_source_rgb(0, 1, 0);
            break;
        case 2:
            cr->set_source_rgb(0, 0, 1);
            break;
        case 3:
            cr->set_source_rgb(1, 1, 0);
            break;
        case 4:
            cr->set_source_rgb(1, 0, 1);
            break;
        case 5:
            cr->set_source_rgb(0.5, 0.5, 0.5);
            break;
        default:
            cr->set_source_rgb(0, 0, 0);
    }
}
