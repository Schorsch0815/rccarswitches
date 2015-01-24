/*
 * ConditionSwitch.cpp
 *
 *  Created on: 22.01.2015
 *      Author: Jochen
 */
#include "Arduino.h"

#include "ConditionSwitch.h"

ConditionSwitch::ConditionSwitch( Condition * pSwitchCondition) : Switch(), mSwitchCondition(pSwitchCondition)
{
}

void ConditionSwitch::refresh(void)
{
    setState(evaluateCondition() ? ON : OFF);
}

