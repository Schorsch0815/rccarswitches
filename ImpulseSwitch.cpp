/*
 * ImpulsPinSwitch.cpp
 *
 *  Created on: 19.12.2014
 *      Author: Jochen
 */

#include <limits.h>
#include <Arduino.h>

#include "ImpulseSwitch.h"

ImpulseSwitch::ImpulseSwitch(Condition * pSwitchCondition, void *pParam, unsigned long pMinImpulsDuration, unsigned long pImpluseCooldown) :
ConditionSwitch(pSwitchCondition,pParam), mWasSwitched(false), mImpulseChangeTimestamp(ULONG_MAX), mMinImpulseDuration(pMinImpulsDuration), mImpulseCooldown(
                pImpluseCooldown), mImpulseActive(false)
{
}

void ImpulseSwitch::refresh(void)
{
//    Serial.print("\nmMinImpulseDuration:   ");
//    Serial.print(mMinImpulseDuration);
    if (mMinImpulseDuration < getImpulseActiveDuration())
    {
//        Serial.print("  Should I switch");
        // to prevent toggling when impulse is still "active" but switch was changed during this impulse
        if (!mWasSwitched)
        {
            // toggle switch state
            setState(getInvertedState());
//            Serial.print("  Switch on");
            mWasSwitched = true;
        }
    }
    else
    {
//        Serial.print("  Switch off");
        mWasSwitched = false;
    }
}

unsigned long ImpulseSwitch::getImpulseActiveDuration()
{
    if (evaluateCondition())
    {
//        Serial.print("  Evaluation is true   ");

        if (!mImpulseActive)
        {
            // switch cannot be retriggered before defiended cool down. mImpulseChangeTimestamp has value of last release action
            if (mImpulseChangeTimestamp < mImpulseCooldown)
            {
                return 0;
            }

            mImpulseActive = true;
            mImpulseChangeTimestamp = millis();
        }

//        Serial.print("  return ");
//        Serial.println(max(1, millis() - mImpulseChangeTimestamp));
        // in case impulse is active we return at least 1 milliseconds for duration
        return max(1, millis() - mImpulseChangeTimestamp);
    }
    else
    {
//        Serial.print("  Evaluation is false");
        if (mImpulseActive)
        {
            mImpulseActive = false;
            mImpulseChangeTimestamp = millis();
        }
    }
    return 0;
}
