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

#include "SteppingSwitch.h"

SteppingSwitch::SteppingSwitch( Condition & pSwitchCondition,
                                unsigned int pNumberOfSteps,
                                unsigned long pImpulseDuration,
                                unsigned long pImpluseCooldown ) :
        ImpulseSwitch( pSwitchCondition, pImpulseDuration, pImpluseCooldown ),
        mNumberOfSteps( pNumberOfSteps ),
        mCurrentStep( 0 )
{
}

SteppingSwitch::~SteppingSwitch()
{
}

/**
 * Calls the setup method of the parent class
 */
void SteppingSwitch::setup()
{
    ImpulseSwitch::setup();
}

/**
 * Passing the state ON will not influence the step position of the switch.
 */
void SteppingSwitch::setState( SwitchState_t pState )
{
    if (OFF == pState)
    {
        ImpulseSwitch::setState( pState );
        mCurrentStep = 0;
    }
}

/**
 * The refresh methods checks whether the current impulse is longer or equal active as the minimum impulse duration. If
 * yes the current step was increased and if the maximum number of steps was reached the next step will be
 * the first one again. Every impulse will increase the step by one.
 */
void SteppingSwitch::refresh( void )
{
    if (getMinImpulseDuration() <= getImpulseActiveDuration())
    {
        // to prevent toggling when impulse is still "active" but switch was changed during this impulse
        if (!mWasSwitched)
        {
            // toggle switch state
            ++mCurrentStep;
            mWasSwitched = true;

            if (mCurrentStep >= mNumberOfSteps)
            {
                ImpulseSwitch::setState( OFF );
                mCurrentStep = 0;
            }
            else
            {
                ImpulseSwitch::setState( ON );
            }
        }
    }
    else
    {
        mWasSwitched = false;
    }
}

