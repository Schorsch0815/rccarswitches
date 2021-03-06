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

#include "ConditionSwitch.h"

ConditionSwitch::ConditionSwitch( Condition &pSwitchCondition )
    : Switch()
    , mSwitchCondition( pSwitchCondition )
{
}

ConditionSwitch::~ConditionSwitch()
{
}

/**
 * Calls the setup method of the parent class
 */
void ConditionSwitch::setup()
{
    Switch::setup();
}

/**
 * Changes the state of the switch by evaluating the condition object.
 */
void ConditionSwitch::refresh( void )
{
    setState( evaluateCondition() ? ON : OFF );
}
