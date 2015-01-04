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
        PinSwitch(pPin), m_wasSwitched(false), m_impulseChangeTimestamp(pMinImpulsDuration), m_minImpulseDuration(ULONG_MAX), m_impulseCooldown(
                pImpluseCooldown), m_impulseActive(false)
{
}

ImpulsPinSwitch::~ImpulsPinSwitch()
{
}

void ImpulsPinSwitch::refresh(void)
{
    if (m_minImpulseDuration < getImpulseActiveDuration())
    {
        // to prevent toggling when impulse is still "active" but switch was changed during this impulse
        if (!m_wasSwitched)
        {
            // toggle switch state
            setState(getInvertedState());
            m_wasSwitched = true;
        }
    }
    else
    {
        m_wasSwitched = false;
    }
}

unsigned long ImpulsPinSwitch::getImpulseActiveDuration()
{
    if (digitalRead(getInputPin()))
    {
        if (!m_impulseActive)
        {
            // switch cannot be retriggered before defiended cool down. m_impulseChangeTimestamp has value of last release action
            if (m_impulseChangeTimestamp < m_impulseCooldown)
            {
                return 0;
            }

            m_impulseActive = true;
            m_impulseChangeTimestamp = millis();
        }

        // in case impulse is active we return at least 1 milliseconds for duration
        return max(1, millis() - m_impulseChangeTimestamp);
    }
    else
    {
        if (m_impulseActive)
        {
            m_impulseActive = false;
            m_impulseChangeTimestamp = millis();
        }
    }
    return 0;
}
