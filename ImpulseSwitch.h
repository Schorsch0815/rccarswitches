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

#ifndef IMPULSPINSWITCH_H_
#define IMPULSPINSWITCH_H_

#include "ConditionSwitch.h"

/**
 * The impulse switch enhances the ConditionSwitch with a functionality similar as an impulse or latching
 * relay. The condition will be evaluated and if the result of condition is true for a configurable time
 * the switch will change it's state. This minimum impulse duration can be specified in milliseconds.
 * To understand the exact behavior, it's important to know that the state of condition will be determined
 * whenever the method refresh was called. Therefore it must be clear, that in case the condition toggles
 * all the time but it returns always true, when it's evaluated by the refresh method the impulse switch
 * will change the state after the minimum impulse duration is passed. Therefore the application has to
 * ensure to call the refresh method often enough to provide a reliable result.
 * In addition to that a cool down delay can be specified. This delay specifies the time after a state
 * switch, when switch ignores a new incoming impulse.
 */
class ImpulseSwitch : public ConditionSwitch
{
public:
    /**
     * Constructor. Creates an impulse switch and allows to specify a condition, a minimum impulse duration
     * and the cool down delay.
     * @param pSwitchCondition condition object.
     * @param pMinImpulsDuration minimum impulse duration in milliseconds.
     * @param pCoolDownDelay the impulse cool down delay in milliseconds, the default value is 0.
     */
    ImpulseSwitch( Condition & pSwitchCondition,
                   unsigned long pMinImpulseDuration,
                   unsigned long pCoolDownDelay = 0L );

    /**
     *  Sets up the switch. Has to be called before the switch can be used.
     */
    virtual void setup( void );

    /**
     * Refreshes the switch state. Has to be called within the loop of an application.
     */
    virtual void refresh( void );

protected:

    /**
     * Determines the duration since when the condition returns true.
     * @return the duration since the impulse is active in milliseconds
     */
    unsigned long getImpulseActiveDuration();

    /**
     * @return the minimum impulse duration in milliseconds
     */
    inline unsigned long getMinImpulseDuration()
    {
        return mMinImpulseDuration;
    }

protected:
    bool mWasSwitched; ///< Helper flag to prevent toggling of the switch after the first switch.

private:
    unsigned long mImpulseChangeTimestamp; ///< timestamp when a change of conditions state was detected.
    unsigned long mMinImpulseDuration; ///< minimum duration [milliseconds] of in impulse to change the switch state.
    unsigned long mCoolDownDelay; ///< Switch did detect an new impulse for cool down delay [milliseconds] after a state switch.
    bool mImpulseActive; ///< Flag indicating whether an impulse is active or not
};

#endif /* IMPULSPINSWITCH_H_ */
