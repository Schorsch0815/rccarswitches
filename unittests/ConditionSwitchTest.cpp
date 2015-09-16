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

#include "gtest/gtest.h"

#include "../ConditionSwitch.h"

#include "Arduino.h"

class SimpleCondition : public Condition
{
public:
    SimpleCondition() :
            Condition(), mValue( false )
    {
    }

    virtual bool evaluate();

    bool mValue;
};

bool SimpleCondition::evaluate()
{
    return mValue;
}

class SimpleDelayedCondition : public Condition
{
public:
    SimpleDelayedCondition( unsigned long fDelay ) :
            Condition( fDelay ), mValue( false )
    {
    }

    virtual bool evaluate();

    bool mValue;
};

bool SimpleDelayedCondition::evaluate()
{
    return mValue;
}

// Test simple Condition switch
TEST(ConditionSwitchTest, SetGet)
{
    SimpleCondition lCondition;

    ConditionSwitch s1(lCondition);

    s1.refresh();
    EXPECT_EQ(Switch::OFF,s1.getState());

    lCondition.mValue = true;
    s1.refresh();

    EXPECT_EQ(Switch::ON,s1.getState());
}

// Tests condition switch with delay
TEST(ConditionSwitchTest, SetGetWithDelayedCondition)
{
    SimpleDelayedCondition lCondition(500);

    ConditionSwitch s1(lCondition);

    s1.refresh();
    EXPECT_EQ(Switch::OFF,s1.getState());

    lCondition.mValue = true;

    s1.refresh();
    EXPECT_EQ(Switch::OFF,s1.getState());

    delay(460);

    s1.refresh();
    EXPECT_EQ(Switch::OFF,s1.getState());

    delay(40);

    s1.refresh();
    EXPECT_EQ(Switch::ON,s1.getState());
}

// Tests condition switch with too short delay
TEST(ConditionSwitchTest, SetGetWithDelayedConditionTooShortDelay)
{
    SimpleDelayedCondition lCondition(500);

    ConditionSwitch s1(lCondition);

    s1.refresh();
    EXPECT_EQ(Switch::OFF,s1.getState());

    lCondition.mValue = true;

    s1.refresh();
    EXPECT_EQ(Switch::OFF,s1.getState());

    delay(480);

    s1.refresh();
    EXPECT_EQ(Switch::OFF,s1.getState());

    delay(5);

    lCondition.mValue = false;
    s1.refresh();
    EXPECT_EQ(Switch::OFF,s1.getState());

    lCondition.mValue = true;
    s1.refresh();

    delay(40);
    s1.refresh();
    EXPECT_EQ(Switch::OFF,s1.getState());
}
