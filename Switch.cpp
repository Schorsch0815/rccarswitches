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

#include "Switch.h"

Switch::Switch()
    : mState( OFF )
{
}

Switch::~Switch()
{
}

/**
 * This implementation do nothing for the base class, because no special initialization is needed.
 */
void Switch::setup()
{
}

/**
 * This implementation do nothing for the base class, because no special handling is needed to update the switch state.
 * The only way to change the state of the switch is to call #setState.
 */
void Switch::refresh()
{
}

void Switch::setState( SwitchState_t pState )
{
    mState = pState;
}
