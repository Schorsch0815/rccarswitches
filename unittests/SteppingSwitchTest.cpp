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

#include "../SteppingSwitch.h"
#include "Arduino.h"
#include <cstdio>

class SimpleSteppingSwitchCondition : public Condition
{
public:
    SimpleSteppingSwitchCondition() : Condition(),mValue(false)
    {
    }

    virtual bool operator()();

    bool mValue;
};

bool SimpleSteppingSwitchCondition::operator()()
{
    return mValue;
}

// Tests stepping switch but with too short impulse
TEST(SteppingSwitchTest, ImpulseToShort)
{
    SimpleSteppingSwitchCondition lCondition;

    SteppingSwitch s1(lCondition,4,1000,0);

    EXPECT_EQ(Switch::OFF,s1.getState());
    EXPECT_EQ(0U,s1.getCurrentStep());

    s1.setup();
    s1.refresh();
    EXPECT_EQ(Switch::OFF,s1.getState());
    EXPECT_EQ(0U,s1.getCurrentStep());

    lCondition.mValue = true;
    s1.refresh();
    EXPECT_EQ(Switch::OFF,s1.getState());
    EXPECT_EQ(0U,s1.getCurrentStep());
    delay(900);
    s1.refresh();

    EXPECT_EQ(Switch::OFF,s1.getState());
    EXPECT_EQ(0U,s1.getCurrentStep());
}


// Tests stepping switch long impulse
TEST(SteppingSwitchTest, ImpulseLongEnough)
{
    SimpleSteppingSwitchCondition lCondition;

    SteppingSwitch s1(lCondition,4,1001,0);

    EXPECT_EQ(Switch::OFF,s1.getState());
    EXPECT_EQ(0U,s1.getCurrentStep());

    s1.setup();
    s1.refresh();
    EXPECT_EQ(Switch::OFF,s1.getState());
    EXPECT_EQ(0U,s1.getCurrentStep());
    lCondition.mValue = true;
    s1.refresh();
    delay(1001);
    s1.refresh();
    EXPECT_EQ(Switch::ON,s1.getState());
    EXPECT_EQ(1U,s1.getCurrentStep());

    lCondition.mValue = false;
    s1.refresh();

    EXPECT_EQ(Switch::ON,s1.getState());
    EXPECT_EQ(1U,s1.getCurrentStep());
}

// Tests stepping switch that after #ofMaxSteps impulses the step is identical with the first step
TEST(SteppingSwitchTest, SteppingPassOverTest)
{
    SimpleSteppingSwitchCondition lCondition;

    SteppingSwitch s1(lCondition,4,1000,0);

    EXPECT_EQ(Switch::OFF,s1.getState());
    EXPECT_EQ(0U,s1.getCurrentStep());

    s1.setup();

    for (unsigned int i = 0; i < 4; ++i)
    {
        lCondition.mValue = true;
        s1.refresh();
        delay(1001);
        s1.refresh();
        if (3 > i)
        {
            EXPECT_EQ(Switch::ON,s1.getState());
            EXPECT_EQ(i + 1,s1.getCurrentStep());
        }
        else
        {
            EXPECT_EQ(Switch::OFF,s1.getState());
            EXPECT_EQ(0U,s1.getCurrentStep());
        }
        lCondition.mValue = false;

        s1.refresh();

        if (3 > i)
        {
            EXPECT_EQ(Switch::ON,s1.getState());
            EXPECT_EQ(i + 1,s1.getCurrentStep());
        }
        else
        {
            EXPECT_EQ(Switch::OFF,s1.getState());
            EXPECT_EQ(0U,s1.getCurrentStep());
        }
        delay(50);
    }
}

