/*
 * SteppingSwitch.cpp
 *
 *  Created on: 30.12.2014
 *      Author: Jochen
 */

#include "SteppingSwitch.h"

SteppingSwitch::SteppingSwitch(unsigned int pNumberOfSteps, unsigned int pPin, unsigned long pImpulseDuration,
                               unsigned long pImpluseCooldown) :
        ImpulsPinSwitch(pPin, pImpulseDuration, pImpluseCooldown), m_numberOfSteps(pNumberOfSteps), m_currentStep(0)
{
}

SteppingSwitch::~SteppingSwitch()
{
}

void SteppingSwitch::setup()
{
    ImpulsPinSwitch::setup();
}

void SteppingSwitch::setState( SwitchState_t pState )
{
    if (OFF == pState)
    {
        ImpulsPinSwitch::setState(pState);
        m_currentStep = 0;
    }
}

void SteppingSwitch::refresh(void)
{
    if (getMinImpulseDuration() < getImpulseActiveDuration())
    {
        // to prevent toggling when impulse is still "active" but switch was changed during this impulse
        if (!m_wasSwitched)
        {
            // toggle switch state
            ++m_currentStep;
            m_wasSwitched = true;

            if (m_currentStep > m_numberOfSteps)
            {
                ImpulsPinSwitch::setState(OFF);
                m_currentStep = 0;
            }
            else
            {
                ImpulsPinSwitch::setState(ON);
            }
        }
    }
    else
    {
        m_wasSwitched = false;
    }
}

