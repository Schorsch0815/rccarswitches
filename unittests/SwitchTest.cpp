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

#include "../Switch.h"

// Tests Switch setState and getState.
TEST(SwitchTest, SetGet)
{

    Switch s1;

    EXPECT_EQ(Switch::OFF,s1.getState());

    s1.setState(Switch::ON);
    EXPECT_EQ(Switch::ON,s1.getState());

    s1.setState(Switch::OFF);
    EXPECT_EQ(Switch::OFF,s1.getState());
}

// Tests Switch setup do nothing.
TEST(SwitchTest, Setup)
{

    Switch s1;

    EXPECT_EQ(Switch::OFF,s1.getState());

    s1.setup();
    EXPECT_EQ(Switch::OFF,s1.getState());
}

// Tests Switch setup do nothing.
TEST(SwitchTest, Refresh)
{

    Switch s1;

    EXPECT_EQ(Switch::OFF,s1.getState());

    s1.refresh();
    EXPECT_EQ(Switch::OFF,s1.getState());
}

