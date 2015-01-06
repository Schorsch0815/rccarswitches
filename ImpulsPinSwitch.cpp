/*
 * ImpulsPinSwitch.cpp
 *
 *  Created on: 19.12.2014
 *      Author: Jochen
 */

#include "ImpulsPinSwitch.h"

#include <limits.h>
#include <Arduino.h>

ImpulsPinSwitch::ImpulsPinSwitch(unsigned int pPin, unsigned long pMinImpulsDuration, unsigned long pImpluseCooldown) :
        PinSwitch(pPin), mWasSwitched(false), mImpulseChangeTimestamp(pMinImpulsDuration), mMinImpulseDuration(ULONG_MAX), mImpulseCooldown(
                pImpluseCooldown), mImpulseActive(false)
{
}

ImpulsPinSwitch::~ImpulsPinSwitch()
{
}

void ImpulsPinSwitch::refresh(void)
{
    if (mMinImpulseDuration < getImpulseActiveDuration())
    {
        // to prevent toggling when impulse is still "active" but switch was changed during this impulse
        if (!mWasSwitched)
        {
            // toggle switch state
            setState(getInvertedState());
            mWasSwitched = true;
        }
    }
    else
    {
        mWasSwitched = false;
    }
}

unsigned long ImpulsPinSwitch::getImpulseActiveDuration()
{
    if (digitalRead(getInputPin()))
    {
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

        // in case impulse is active we return at least 1 milliseconds for duration
        return max(1, mIllis() - mImpulseChangeTimestamp);
    }
    else
    {
        if (mImpulseActive)
        {
            mImpulseActive = false;
            mImpulseChangeTimestamp = millis();
        }
    }
    return 0;
}
