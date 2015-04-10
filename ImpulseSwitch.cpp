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

#include <limits.h>

#include "Arduino.h"

#include "ImpulseSwitch.h"

using namespace std;

ImpulseSwitch::ImpulseSwitch(Condition & pSwitchCondition, unsigned long pMinImpulsDuration,
                             unsigned long pCoolDownDelay) :
        ConditionSwitch(pSwitchCondition), mWasSwitched(false), mImpulseChangeTimestamp(ULONG_MAX), mMinImpulseDuration(
                pMinImpulsDuration), mCoolDownDelay(pCoolDownDelay), mImpulseActive(false)
{
}


/**
 * Calls the setup method of the parent class
 */
void ImpulseSwitch::setup()
{
    ConditionSwitch::setup();
}


/**
 * The refresh methods checks whether the current impulse is longer or equal active as the minimum impulse duration. If
 * yes the state of switch was changed and the change flag was set to prevent toggling of the switch state.
 */
void ImpulseSwitch::refresh(void)
{
    if (mMinImpulseDuration <= getImpulseActiveDuration())
    {
        // to prevent toggling when impulse is still "active" but switch was changed during this impulse
        if (!mWasSwitched)
        {
            // toggle switch state
            setState(getInvertedState());
            mWasSwitched = true;
        }
    }
    else
    {
        mWasSwitched = false;
    }
}

/**
 * Have in mind that this method is called by refresh, therefore the method cannot detects break in
 * the current impulse if these brakes occur between two method invocations.
 */
unsigned long ImpulseSwitch::getImpulseActiveDuration()
{
    if (evaluateCondition())
    {

        if (!mImpulseActive)
        {
            // switch cannot be retriggered before defiended cool down. mImpulseChangeTimestamp has value of last release action
            if (mImpulseChangeTimestamp < mCoolDownDelay)
            {
                return 0;
            }

            mImpulseActive = true;
            mImpulseChangeTimestamp = millis();
        }

        // in case impulse is active we return at least 1 milliseconds for duration
        long lMillis = millis();
        long lDiff = lMillis - mImpulseChangeTimestamp;
        return max(1L, lDiff);
    }
    else
    {
        if (mImpulseActive)
        {
            mImpulseActive = false;
            mImpulseChangeTimestamp = millis();
        }
    }
    return 0;
}
