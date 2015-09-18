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

#ifndef CONDITION_H_
#define CONDITION_H_

/**
 * Base class for conditions and has to be subclassed for concrete implementations. A condition is needed when
 * using a ConditionSwitch, ImpulseSwitch or SteppingSwitch. The switch will use the Condition::operator() to
 * "evaluate" the condition. That means the condition will influence the behavior of the Switch. (See
 * ConditionSwitch for more information).
 *
 * The condition allows to specify a delay, which defines the delay after the condition propagates the
 * internal detected change to the outside.
 *
 * When writing an own condition, at least the virtual method evaluate() has to be overloaded. It should return reflect the
 * value of the condition and can be implemented as required.
 */
class Condition
{
public:
    /**
     * Constructor
     *
     * The optional parameter fDelay allows to specify an arbitrary value for a
     * delay.
     *
     * @param fOnDelay defines a delay after the condition raises a change from false to true in milliseconds
     * @param fOffDelay defines a delay after the condition raises a change from ttrue to false in milliseconds
     */
    Condition( unsigned long fOnDelay = 0, unsigned long fOffDelay = 0 );

    /**
     * Destructor
     */
    virtual ~Condition();

    /**
     * Evaluates the value of the condition and regards an existing delay.
     *
     * @return the value of the condition, can be either true or false.
     */
    bool operator()();

private:
    /**
     * Evaluates the condition and has to be overloaded by a subclass.
     * @return the value of the condition, can be either true or false
     */
    virtual bool evaluate() = 0;

    unsigned long mOnDelay;           ///< delay in milliseconds
    unsigned long mOffDelay;           ///< delay in milliseconds
    unsigned long mChangeDetected; ///< holds the time stamp the condition change was detected
    bool mCurrentState;    ///< current propagate value of the switch
    bool mUpcommingState;  ///< upcoming state of the last call to evaluate
};

#endif /* CONDITION_H_ */
