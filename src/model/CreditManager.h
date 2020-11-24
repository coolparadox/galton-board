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

/*
 * CreditManager manages the credit balance.
 */
class CreditManager
{

 public:
    CreditManager();
    virtual ~CreditManager();

    // Can credits be deposited?
    bool can_deposit() const;
    // Are there credits to withdraw?
    bool can_withdraw() const;
    // Are these enough credits to play the simulation?
    bool can_play() const;
    // Is the simulation playing?
    bool is_playing() const;

    // Query the current credit balance.
    unsigned int get_remaining_credits() const;
    // Query the total number of withdrawed credits since the start of the application,
    unsigned int get_withdrawed_credits() const;
    // Query the total number of times the simulation was played since the start of the application.
    unsigned int get_play_count() const;

    // Add one credit to the balance.
    void add_credit();
    // Withdraw all credits from the balance.
    void withdraw_credits();
    // Acknowledge that one simulation was started.
    void acknowledge_play_start();
    // Acknowledge that one simulation was ended.
    void acknowledge_play_end();

 protected:
    unsigned int _remaining_credits;
    unsigned int _withdrawed_credits;
    unsigned int _play_counter;
    bool _is_playing;

};

#endif // SRC_MODEL_GAMEMANAGER_H
