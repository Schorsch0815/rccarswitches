/*
 * SteppingSwitch.cpp
 *
 *  Created on: 30.12.2014
 *      Author: Jochen
 */

#include "SteppingSwitch.h"

SteppingSwitch::SteppingSwitch(unsigned int pNumberOfSteps, unsigned int pPin, unsigned long pImpulseDuration,
                               unsigned long pImpluseCooldown) :
        ImpulsPinSwitch(pPin, pImpulseDuration, pImpluseCooldown), mNumberOfSteps(pNumberOfSteps), mCurrentStep(0)
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
                ImpulsPinSwitch::setState(OFF);
                mCurrentStep = 0;
            }
            else
            {
                ImpulsPinSwitch::setState(ON);
            }
        }
    }
    else
    {
        mWasSwitched = false;
    }
}

