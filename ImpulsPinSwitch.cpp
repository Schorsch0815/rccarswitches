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
        PinSwitch(pPin), mwasSwitched(false), mimpulseChangeTimestamp(pMinImpulsDuration), mminImpulseDuration(ULONG_MAX), mimpulseCooldown(
                pImpluseCooldown), mimpulseActive(false)
{
}

ImpulsPinSwitch::~ImpulsPinSwitch()
{
}

void ImpulsPinSwitch::refresh(void)
{
    if (mminImpulseDuration < getImpulseActiveDuration())
    {
        // to prevent toggling when impulse is still "active" but switch was changed during this impulse
        if (!mwasSwitched)
        {
            // toggle switch state
            setState(getInvertedState());
            mwasSwitched = true;
        }
    }
    else
    {
        mwasSwitched = false;
    }
}

unsigned long ImpulsPinSwitch::getImpulseActiveDuration()
{
    if (digitalRead(getInputPin()))
    {
        if (!mimpulseActive)
        {
            // switch cannot be retriggered before defiended cool down. mimpulseChangeTimestamp has value of last release action
            if (mimpulseChangeTimestamp < mimpulseCooldown)
            {
                return 0;
            }

            mimpulseActive = true;
            mimpulseChangeTimestamp = millis();
        }

        // in case impulse is active we return at least 1 milliseconds for duration
        return max(1, millis() - mimpulseChangeTimestamp);
    }
    else
    {
        if (mimpulseActive)
        {
            mimpulseActive = false;
            mimpulseChangeTimestamp = millis();
        }
    }
    return 0;
}
