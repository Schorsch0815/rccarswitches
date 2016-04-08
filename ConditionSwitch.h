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

#ifndef CONDITIONSWITCH_H_
#define CONDITIONSWITCH_H_

#include <stdio.h>

#include "Switch.h"
#include "Condition.h"

/**
 * This class provides a switch where the status change can be influenced by evaluating
 * a condition. When creating a switch a Condition object can be passed, which will be
 * evaluated for each refresh. When evaluated condition returns true the state of the
 * switch changes to ON and OFF otherwise.
 *
 */
class ConditionSwitch : public Switch
{

  public:
    /**
     * Constructor. It requires a condition object, which will be evaluated to determine
     * the state of the switch.
     *
     * @param pSwitchCondition condition object
     */
    ConditionSwitch( Condition &pSwitchCondition );

    ~ConditionSwitch();

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
     * Evaluates the conditions passed during construction.
     * @return true if the condition was evaluated to true otherwise false
     */
    inline bool evaluateCondition( void ) { return ( mSwitchCondition )(); }

  private:
    Condition &mSwitchCondition; ///< reference to the condition object
};

#endif /* SWITCH_H_ */
