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
 * "evaluate" the condition. That means the condition will influence the behaviour of the Switch. (See
 * ConditionSwitch for more information).
 *
 * When writing an own condition, at least the virtual operator() has to be overloaded. It should return reflect the
 * value of the condition and can be implemented as required.
 */
class Condition
{
public:
    /**
     * Construtor
     */
    Condition();

    /**
     * Destructor
     */
    virtual ~Condition();

    /**
     * This operator is used to evaluate the value of the condition.
     * @return the value of the condition, can be either true or false.
     */
    virtual bool operator()() = 0;
};

#endif /* CONDITION_H_ */
