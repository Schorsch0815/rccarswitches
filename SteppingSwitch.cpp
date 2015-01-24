/*
 * SteppingSwitch.cpp
 *
 *  Created on: 30.12.2014
 *      Author: Jochen
 */

#include "SteppingSwitch.h"

SteppingSwitch::SteppingSwitch(const Condition & pSwitchCondition,unsigned int pNumberOfSteps, unsigned long pImpulseDuration,
                               unsigned long pImpluseCooldown) :
        ImpulseSwitch(pSwitchCondition, pImpulseDuration, pImpluseCooldown), mNumberOfSteps(pNumberOfSteps), mCurrentStep(0)
{
}

SteppingSwitch::~SteppingSwitch()
{
}

void SteppingSwitch::setup()
{
    ImpulseSwitch::setup();
}

void SteppingSwitch::setState( SwitchState_t pState )
{
    if (OFF == pState)
    {
        ImpulseSwitch::setState(pState);
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
                ImpulseSwitch::setState(OFF);
                mCurrentStep = 0;
            }
            else
            {
                ImpulseSwitch::setState(ON);
            }
        }
    }
    else
    {
        mWasSwitched = false;
    }
}

