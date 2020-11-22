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
#include <iostream>
#include "Ball.h"

Ball::Ball(unsigned int id)
    : _id(id),
      _x(0),
      _y(0),
      _stuck(false)
{
    std::cerr << "Ball " << _id << ": " << _y << " " << _x << std::endl << std::endl;
}

Ball::~Ball()
{
}

unsigned int Ball::get_id() const
{
    return _id;
}

int Ball::get_x() const
{
    return _x;
}

int Ball::get_y() const
{
    return _y;
}

bool Ball::is_stuck() const
{
    return _stuck;
}

bool Ball::fall(std::vector<Ball>& grid, unsigned int n_levels, bool toss)
{
    if (_stuck)
    {
        // The ball is already stuck after a previous fall attempt.
        return false;
    }
    assert(n_levels > 0);
    const int max_y = n_levels - 1;
    if (_y >= max_y)
    {
        // The ball is already at the bottom of the board.
        _stuck = true;
        return false;
    }
    // Is there room to fall one more level?
    bool can_fall_left = true;
    bool can_fall_right = true;
    for (auto ball = grid.cbegin(); ball != grid.cend(); ++ball)
    {
        if (ball->get_y() == _y + 1)
        {
            if (ball->get_x() == _x - 1) {
                can_fall_left = false;
            }
            if (ball->get_x() == _x + 1) {
                can_fall_right = false;
            }
        }
    }
    if (!can_fall_left && !can_fall_right)
    {
        // There is nowhere to fall further.
        _stuck = true;
        return false;
    }
    if (can_fall_left && can_fall_right)
    {
        // There are two possible empty positions below.
        // Assume the toss is random and use it to choose a side.
        if (toss)
        {
            can_fall_left = false;
        }
        else
        {
            can_fall_right = false;
        }
    }
    // Fall one level.
    _y += 1;
    if (_y >= max_y)
    {
        // This is the last level
        _stuck = true;
    }
    if (can_fall_left)
    {
        _x -= 1;
    }
    else
    {
        _x += 1;
    }
    std::cerr << "Fall " << _id << ": " << _y << " " << _x << std::endl;
    return true;
}