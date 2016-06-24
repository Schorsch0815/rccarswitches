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

#ifndef STEPPINGSWITCH_H_
#define STEPPINGSWITCH_H_

#include "ImpulseSwitch.h"

/**
 * This class provides a so called stepping switch. In difference to a usual switch a
 * stepping switch has more than two switch positions, the number has to be specified during
 * creation of a switch and cannot be changed afterwards.
 * Every impulse, that's detected by the refresh methods will change the switch position to
 * the next step. in case the maximum step is reached the next step is the first one. This
 * first position is equal to the OFF state of the switch. Therefore in case the setState method
 * was called with state OFF the stepping switch will be set to the first position! The number
 * of steps includes the OFF state as one step.
 * The conditional and impulse behavior is similar as described for the ImpulseSwitch.
 */
class SteppingSwitch : public ImpulseSwitch
{
public:
    /**
     * Constructor.  Creates a stepping switch and allows to specify a condition, the number of steps,
     * a minimum impulse duration and the cool down delay.
     * @param pSwitchCondition condition object.
     * @param pNumberOfSteps number of maximum steps (state OFF counts as one step)
     * @param pMinImpulseDuration minimum impulse duration in milliseconds.
     * @param pCoolDownDelay the impulse cool down delay in milliseconds, the default value is 0.
     */
    SteppingSwitch( Condition &pSwitchCondition,
                    unsigned int pNumberOfSteps,
                    unsigned long pMinImpulseDuration,
                    unsigned long pCoolDownDelay = 0L );

    /**
     * Destrcutor
     */
    virtual ~SteppingSwitch();

    /**
     *  Sets up the switch. Has to be called before the switch can be used.
     */
    virtual void setup( void );

    /**
     * Refreshes the current position of the switch. Has to be called within the loop of an application.
     */
    virtual void refresh( void );

    /**
     * Returns the current step of the switch.
     * @return current step number [0 &lt;= current step number &lt; max steps]
     */
    inline unsigned int getCurrentStep()
    {
        return mCurrentStep;
    }

    /**
     * Allows to reset the stepping switch to position 0 and setting state to OFF.
     * @param pState
     */
    virtual void setState( SwitchState_t pState );

private:
    unsigned int mNumberOfSteps; ///< Maximum number of steps
    unsigned int mCurrentStep;   ///< Current step number [0 &lt;= current step number &lt; max steps]
};

#endif /* STEPPINGSWITCH_H_ */
