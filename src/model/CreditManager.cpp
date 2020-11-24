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

#include <gtkmm/box.h>
#include <gtkmm/buttonbox.h>
#include <gtkmm/frame.h>

#include "CreditManager.h"

CreditManager::CreditManager()
    : _remaining_credits(0),
      _withdrawed_credits(0),
      _play_counter(0),
      _is_playing(false)
{
}

CreditManager::~CreditManager()
{
}

bool CreditManager::can_deposit() const
{
    return true;
}

bool CreditManager::can_withdraw() const
{
    return _remaining_credits > 0;
}

bool CreditManager::can_play() const
{
    return _is_playing || _remaining_credits > 0;
}

unsigned int CreditManager::get_remaining_credits() const
{
    return _remaining_credits;
}

unsigned int CreditManager::get_withdrawed_credits() const
{
    return _withdrawed_credits;
}

unsigned int CreditManager::get_play_count() const
{
    return _play_counter;
}

void CreditManager::add_credit()
{
    _remaining_credits += 1;
}

void CreditManager::withdraw_credits()
{
    if (can_withdraw())
    {
        _withdrawed_credits += _remaining_credits;
        _remaining_credits = 0;
    }
}

void CreditManager::acknowledge_play_start()
{
    assert(can_play());
    assert(!_is_playing);
    _is_playing = true;
    _remaining_credits -= 1;
}

void CreditManager::acknowledge_play_end()
{
    assert(_is_playing);
    _play_counter += 1;
    _is_playing = false;
}

bool CreditManager::is_playing() const
{
    return _is_playing;
}
