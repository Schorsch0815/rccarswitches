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

#ifndef SWITCH_H_
#define SWITCH_H_

/**
 * The base class for a plain simple switch. Simple switches maintains a \ref SwitchState_t,
 * which can hold different values.
 *
 */
class Switch
{
public:
    /**
     * Enum, which represents state of the switch
     */
    typedef enum
    {
        OFF, ON
    } SwitchState_t;

    /**
     * Constructor
     */
    Switch();

    /**
     * Destructor
     */
    virtual ~Switch();

    /**
     * Sets up the switch. Has to be called before the switch can be used.
     */
    virtual void setup();

    /**
     * Refreshes the switch state. Has to be called within the loop of an application.
     */
    virtual void refresh();

    /**
     * sets the state of the switch to the passed pState
     *
     * @param pState new state of the switch
     */
    virtual void setState( SwitchState_t pState );

    /**
     *
     * @return the current state of the switch
     */
    inline SwitchState_t getState( void )
    {
        return mState;
    }

    /**
     *
     * @return the inverted state of the switch
     */
    inline SwitchState_t getInvertedState( void )
    {
        return (ON == mState) ? OFF : ON;;
    }

private:
    SwitchState_t mState; /**< state of the switch */
};

#endif /* SWITCH_H_ */
