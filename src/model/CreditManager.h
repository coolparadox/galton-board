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

#ifndef SRC_MODEL_GAMEMANAGER_H
#define SRC_MODEL_GAMEMANAGER_H

class CreditManager
{

 public:
    CreditManager();
    virtual ~CreditManager();

    bool can_deposit() const;
    bool can_withdraw() const;
    bool can_play() const;

    unsigned int get_remaining_credits() const;
    unsigned int get_withdrawed_credits() const;
    unsigned int get_play_count() const;

    void add_credit();
    void withdraw_credits();
    void register_play();

 protected:
    unsigned int _remaining_credits;
    unsigned int _withdrawed_credits;
    unsigned int _play_counter;

};

#endif // SRC_MODEL_GAMEMANAGER_H
