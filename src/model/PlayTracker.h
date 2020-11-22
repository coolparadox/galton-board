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

#ifndef SRC_MODEL_PLAYTRACKER_H
#define SRC_MODEL_PLAYTRACKER_H

#include <vector>

#include "Ball.h"

class PlayTracker
{

 public:
    PlayTracker(unsigned int n_levels, std::vector<Ball>& grid);
    virtual ~PlayTracker();

    void reset();
    bool step();

 protected:

    bool get_random_toss();

    unsigned int _n_levels;
    unsigned int _next_ball_id;
    std::vector<Ball>& _grid;

    std::default_random_engine _gen;
    std::uniform_int_distribution<int> _dist;

};

#endif // SRC_MODEL_PLAYTRACKER_H
