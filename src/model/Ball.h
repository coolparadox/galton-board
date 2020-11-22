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

#ifndef SRC_MODEL_BALL_H
#define SRC_MODEL_BALL_H

#include <random>

class Ball
{

 public:
    Ball(unsigned int id);
    virtual ~Ball();

    unsigned int get_id() const;
    int get_displacement() const;
    int get_level() const;
    bool is_stuck() const;
    bool fall(std::vector<Ball>& grid, unsigned int n_levels, bool toss);

 protected:

    unsigned int _id;
    int _displacement;
    int _level;
    bool _stuck;

};

#endif // SRC_MODEL_BALL_H
