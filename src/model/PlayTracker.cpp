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
#include "PlayTracker.h"

PlayTracker::PlayTracker(unsigned int n_levels, std::vector<Ball>& balls)
    : _n_levels(n_levels),
      _balls(balls),
      _next_ball_id(0),
      _dist(0,1)
{
    assert(n_levels > 0);
}

PlayTracker::~PlayTracker()
{
}

void PlayTracker::reset()
{
    _balls.clear();
    _next_ball_id = 0;
    _balls.emplace_back(_next_ball_id++);
}

bool PlayTracker::step()
{
    bool has_room = true;
    // Loop over all balls starting by older ones (ie, more close to the bottom of the board)
    for (auto ball = _balls.begin(); ball != _balls.end(); ++ball)
    {
        // Take note if this is the top ball.
        bool is_top_ball = ball->get_level() == 0;
        // Ask the ball to fall one level.
        bool has_falled = ball->fall(_balls, _n_levels, get_random_toss());
        if (is_top_ball && !has_falled)
        {
            // The top ball did not fall; assume the board is full.
            has_room = false;
        }
    }
    if (has_room)
    {
        // The board is not yet full; add another ball at the top.
        _balls.emplace_back(_next_ball_id++);
    }
    return has_room;
}

bool PlayTracker::get_random_toss()
{
    return _dist(_gen);
}
