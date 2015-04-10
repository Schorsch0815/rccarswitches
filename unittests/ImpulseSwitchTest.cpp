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

#include "../ImpulseSwitch.h"
#include "Arduino.h"
#include <cstdio>

class SimpleImpulseSwitchCondition : public Condition
{
public:
    SimpleImpulseSwitchCondition() : Condition(), mValue(false)
    {
    }

    virtual bool operator()();

    bool mValue;
};

bool SimpleImpulseSwitchCondition::operator()()
{
    return mValue;
}

// Tests impulse switch but with too short impulse
TEST(ImpulseSwitchTest, ImpulseToShort)
{
    SimpleImpulseSwitchCondition lCondition;

    ImpulseSwitch s1(lCondition,1000,0);

    EXPECT_EQ(Switch::OFF,s1.getState());

    s1.setup();
    s1.refresh();
    EXPECT_EQ(Switch::OFF,s1.getState());
    lCondition.mValue = true;
    s1.refresh();
    EXPECT_EQ(Switch::OFF,s1.getState());
    delay(900);
    s1.refresh();

    EXPECT_EQ(Switch::OFF,s1.getState());
}


// Tests impulse switch long impulse
TEST(ImpulseSwitchTest, ImpulseLongEnough)
{
    SimpleImpulseSwitchCondition lCondition;

    ImpulseSwitch s1(lCondition,1000,0);

    EXPECT_EQ(Switch::OFF,s1.getState());

    s1.setup();
    s1.refresh();
    EXPECT_EQ(Switch::OFF,s1.getState());
    lCondition.mValue = true;
    s1.refresh();
    delay(1001);
    s1.refresh();
    EXPECT_EQ(Switch::ON,s1.getState());

    lCondition.mValue = false;
    s1.refresh();

    EXPECT_EQ(Switch::ON,s1.getState());
}

