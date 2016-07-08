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

#include <cstdio>
#include <iostream>

#include "../ImpulseSwitch.h"
#include "Arduino.h"

using namespace std;

class SimpleImpulseSwitchCondition : public Condition
{
public:
    SimpleImpulseSwitchCondition()
        : Condition()
        , mValue( false )
    {
    }

    virtual bool evaluate();

    bool mValue;
};

bool SimpleImpulseSwitchCondition::evaluate()
{
    return mValue;
}

class ImpulseSwitchTest : public ::testing::Test
{
protected:
    virtual void SetUp()
    {
        ArduinoMockController::getInstance().reset();
    }

    virtual void TearDown()
    {
    }
};

// Tests impulse switch but with too short impulse
TEST_F( ImpulseSwitchTest, ImpulseToShort )
{
    ArduinoMockController::getInstance().setTimerMode( ArduinoMockController::MANUAL_TIMER_MODE );
    SimpleImpulseSwitchCondition lCondition;

    ImpulseSwitch s1( lCondition, 1000, 0 );

    EXPECT_EQ( Switch::OFF, s1.getState() );

    s1.setup();
    s1.refresh();
    EXPECT_EQ( Switch::OFF, s1.getState() );

    lCondition.mValue = true;
    s1.refresh();
    EXPECT_EQ( Switch::OFF, s1.getState() );

    delay( 999 );

    s1.refresh();
    EXPECT_EQ( Switch::OFF, s1.getState() );
}

// Tests impulse switch long impulse
TEST_F( ImpulseSwitchTest, ImpulseLongEnough )
{
    ArduinoMockController::getInstance().setTimerMode( ArduinoMockController::MANUAL_TIMER_MODE );
    SimpleImpulseSwitchCondition lCondition;

    ImpulseSwitch s1( lCondition, 1000, 0 );

    EXPECT_EQ( Switch::OFF, s1.getState() );

    ArduinoMockController::getInstance().setMilliSeconds( 0 );
    s1.setup();
    s1.refresh();
    EXPECT_EQ( Switch::OFF, s1.getState() );

    lCondition.mValue = true;
    s1.refresh();

    ArduinoMockController::getInstance().setMilliSeconds( 1000 );

    s1.refresh();
    EXPECT_EQ( Switch::ON, s1.getState() );

    lCondition.mValue = false;
    s1.refresh();

    EXPECT_EQ( Switch::ON, s1.getState() );
}
