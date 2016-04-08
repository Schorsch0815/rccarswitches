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

#include "../IntervalBlinker.h"

#include <iostream>

#include "Arduino.h"

using namespace std;

class IntervalBlinkerTest : public ::testing::Test
{
  protected:
    virtual void SetUp() { ArduinoMockController::getInstance().reset(); }

    virtual void TearDown() {}
};

// Test normal blinker
TEST_F( IntervalBlinkerTest, TestBlinkInterval600 )
{
    ArduinoMockController::getInstance().setTimerMode( ArduinoMockController::MANUAL_TIMER_MODE );
    Switch s1;

    IntervalBlinker lBlinker( s1, 600 );

    ArduinoMockController::getInstance().setMilliSeconds( 1000 );
    lBlinker.refresh();
    EXPECT_EQ( Switch::OFF, lBlinker.getState() );

    s1.setState( Switch::ON );
    lBlinker.refresh();
    EXPECT_EQ( Switch::ON, lBlinker.getState() );

    ArduinoMockController::getInstance().setMilliSeconds( 1599 );
    lBlinker.refresh();
    EXPECT_EQ( Switch::ON, lBlinker.getState() );

    ArduinoMockController::getInstance().setMilliSeconds( 1600 );
    lBlinker.refresh();
    EXPECT_EQ( Switch::OFF, lBlinker.getState() );

    ArduinoMockController::getInstance().setMilliSeconds( 2199 );
    lBlinker.refresh();
    EXPECT_EQ( Switch::OFF, lBlinker.getState() );

    ArduinoMockController::getInstance().setMilliSeconds( 2200 );
    lBlinker.refresh();
    EXPECT_EQ( Switch::ON, lBlinker.getState() );

    ArduinoMockController::getInstance().setMilliSeconds( 2799 );
    lBlinker.refresh();
    EXPECT_EQ( Switch::ON, lBlinker.getState() );

    s1.setState( Switch::OFF );
    lBlinker.refresh();
    EXPECT_EQ( Switch::OFF, lBlinker.getState() );

    ArduinoMockController::getInstance().setMilliSeconds( 3399 );
    lBlinker.refresh();
    EXPECT_EQ( Switch::OFF, lBlinker.getState() );
}

// Test normal blinker
TEST_F( IntervalBlinkerTest, TestBlinkInterval100 )
{
    ArduinoMockController::getInstance().setTimerMode( ArduinoMockController::MANUAL_TIMER_MODE );
    Switch s1;

    IntervalBlinker lBlinker( s1, 100 );

    lBlinker.refresh();
    EXPECT_EQ( Switch::OFF, lBlinker.getState() );

    s1.setState( Switch::ON );
    lBlinker.refresh();
    EXPECT_EQ( Switch::ON, lBlinker.getState() );

    delay( 95 );
    lBlinker.refresh();
    EXPECT_EQ( Switch::ON, lBlinker.getState() );

    delay( 7 );
    lBlinker.refresh();
    EXPECT_EQ( Switch::OFF, lBlinker.getState() );

    delay( 95 );
    lBlinker.refresh();
    EXPECT_EQ( Switch::OFF, lBlinker.getState() );

    delay( 5 );
    lBlinker.refresh();
    EXPECT_EQ( Switch::ON, lBlinker.getState() );

    delay( 95 );
    lBlinker.refresh();
    EXPECT_EQ( Switch::ON, lBlinker.getState() );

    s1.setState( Switch::OFF );
    lBlinker.refresh();
    EXPECT_EQ( Switch::OFF, lBlinker.getState() );

    delay( 5 );
    lBlinker.refresh();
    EXPECT_EQ( Switch::OFF, lBlinker.getState() );
}
