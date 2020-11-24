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

/*
 * PlayTracker triggers the steps of a simulation where balls fall in a Galton board.
 */
class PlayTracker
{

 public:
    PlayTracker(unsigned int n_levels, std::vector<Ball>& balls);
    virtual ~PlayTracker();

    // Remove all balls from the board, and add the first ball to the top position.
    void reset();
    // Tell all balls to fall one level, and if there is room add another ball to the top position.
    // Answer true if the board is not yet full.
    bool step();

 protected:

    // Answer true or false with equal probability.
    bool get_random_toss();

    // Number of levels of the board.
    unsigned int _n_levels;
    // Id of the next ball that will be placed at the top of the board on the next simulation step.
    unsigned int _next_ball_id;
    // All balls currently in the board.
    std::vector<Ball>& _balls;

    /*
     * Generation of pseudorandom numbers; used by get_random_toss().
     */
    std::default_random_engine _gen;
    std::uniform_int_distribution<int> _dist;

};

#endif // SRC_MODEL_PLAYTRACKER_H
