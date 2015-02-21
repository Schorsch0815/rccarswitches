/*
 * ConditionSwitch.cpp
 *
 *  Created on: 22.01.2015
 *      Author: Jochen
 */
#include "Arduino.h"

#include "ConditionSwitch.h"

ConditionSwitch::ConditionSwitch(Condition * pSwitchCondition, void *pParam) :
        Switch(), mSwitchCondition(pSwitchCondition), mParam(pParam)
{
}

void ConditionSwitch::refresh(void)
{
    setState(evaluateCondition() ? ON : OFF);
}

