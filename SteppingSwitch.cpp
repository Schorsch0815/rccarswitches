/*
 * SteppingSwitch.cpp
 *
 *  Created on: 30.12.2014
 *      Author: Jochen
 */

#include "SteppingSwitch.h"

SteppingSwitch::SteppingSwitch(unsigned int pNumberOfSteps, unsigned int pPin, unsigned long pImpulseDuration,
                               unsigned long pImpluseCooldown) :
        ImpulsPinSwitch(pPin, pImpulseDuration, pImpluseCooldown), mnumberOfSteps(pNumberOfSteps), mcurrentStep(0)
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
        mcurrentStep = 0;
    }
}

void SteppingSwitch::refresh(void)
{
    if (getMinImpulseDuration() < getImpulseActiveDuration())
    {
        // to prevent toggling when impulse is still "active" but switch was changed during this impulse
        if (!mwasSwitched)
        {
            // toggle switch state
            ++mcurrentStep;
            mwasSwitched = true;

            if (mcurrentStep > mnumberOfSteps)
            {
                ImpulsPinSwitch::setState(OFF);
                mcurrentStep = 0;
            }
            else
            {
                ImpulsPinSwitch::setState(ON);
            }
        }
    }
    else
    {
        mwasSwitched = false;
    }
}

