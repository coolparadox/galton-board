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

/*
 * A Ball is an entity that mimics falling in a Galton board,
 * ie, when falling it randomly chooses a unit horizontal displacement
 * as if its fall was being interrupted by a peg.
 */
class Ball
{

 public:
    // When constructing, a Ball remembers its ID and has zero displacement and level values
    // (ie, it's at the top of the board).
    Ball(unsigned int id);
    virtual ~Ball();

    // Query the Ball's ID.
    unsigned int get_id() const;
    // Query the Ball's horizontal displacement.
    int get_displacement() const;
    // Query the Ball's vertical displacement.
    int get_level() const;
    // Is the Ball blocked from falling to a lower level?
    bool is_stuck() const;
    // Tell the Ball to fall to the next lower level.
    // Parameters:
    // - balls: all balls currently in the board
    // - n_levels: number of levels of the board
    // - toss: true or false, uniformly distributed
    // Returns true if the Ball succeeded in falling one level.
    bool fall(std::vector<Ball>& balls, unsigned int n_levels, bool toss);

 protected:

    unsigned int _id;
    int _displacement;
    int _level;
    bool _stuck;

};

#endif // SRC_MODEL_BALL_H
