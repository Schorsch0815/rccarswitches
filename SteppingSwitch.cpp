/*
 * SteppingSwitch.cpp
 *
 *  Created on: 30.12.2014
 *      Author: Jochen
 */

#include "SteppingSwitch.h"

SteppingSwitch::SteppingSwitch(unsigned int pNumberOfSteps, unsigned int pPin, unsigned long pImpulseDuration,
                               unsigned long pImpluseCooldown) :
        ImpulsePinSwitch(pPin, pImpulseDuration, pImpluseCooldown), mNumberOfSteps(pNumberOfSteps), mCurrentStep(0)
{
}

SteppingSwitch::~SteppingSwitch()
{
}

void SteppingSwitch::setup()
{
    ImpulsePinSwitch::setup();
}

void SteppingSwitch::setState( SwitchState_t pState )
{
    if (OFF == pState)
    {
        ImpulsePinSwitch::setState(pState);
        mCurrentStep = 0;
    }
}

void SteppingSwitch::refresh(void)
{
    if (getMinImpulseDuration() < getImpulseActiveDuration())
    {
        // to prevent toggling when impulse is still "active" but switch was changed during this impulse
        if (!mWasSwitched)
        {
            // toggle switch state
            ++mCurrentStep;
            mWasSwitched = true;

            if (mCurrentStep > mNumberOfSteps)
            {
                ImpulsePinSwitch::setState(OFF);
                mCurrentStep = 0;
            }
            else
            {
                ImpulsePinSwitch::setState(ON);
            }
        }
    }
    else
    {
        mWasSwitched = false;
    }
}

