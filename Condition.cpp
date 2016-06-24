/*--------------------------------------------------------------------
 * This file is part of the RcCarSwitches arduino library.
 *
 * RcCarSwitches is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * RcCarSwitches is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with RcCarSwitches.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Copyright: Jochen Schales 2015
 *
 * --------------------------------------------------------------------*/

#include "Condition.h"

#include <stdio.h>
#include "Arduino.h"

Condition::Condition( unsigned long fOnDelay, unsigned long fOffDelay )
    : mOnDelay( fOnDelay )
    , mOffDelay( fOffDelay )
    , mChangeDetected( millis() )
    , mCurrentState( false )
    , mUpcommingState( false )
{
}

Condition::~Condition()
{
}

bool Condition::operator()()
{
    bool lState = evaluate();
    unsigned long lCurrentMillis = millis();
    unsigned long lDelay = ( mCurrentState ? mOffDelay : mOnDelay );

    if ( 0 < lDelay )
    {
        if ( mCurrentState != mUpcommingState )
        {
            // last time we detect a change of condition
            if ( lState == mCurrentState )
            {
                // condition falls back to current state before delay was passed
                mUpcommingState = lState;
                mChangeDetected = lCurrentMillis;
            }
            else
            {
                // change will be detected if last change least longer than configured delay
                if ( mChangeDetected + lDelay <= lCurrentMillis )
                {
                    mCurrentState = lState;
                    mChangeDetected = lCurrentMillis;
                }
            }
        }
        else
        {
            if ( lState != mCurrentState )
            {
                // a state change was recognized and we have to remember the new upcoming state
                mUpcommingState = lState;
                mChangeDetected = lCurrentMillis;
            }
        }
    }
    else
    {
        mUpcommingState = lState;
        mCurrentState = lState;
        mChangeDetected = lCurrentMillis;
    }
    return mCurrentState;
}
