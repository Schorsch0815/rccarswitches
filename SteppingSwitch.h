/*
 * SteppingSwitch.h
 *
 *  Created on: 30.12.2014
 *      Author: Jochen
 */

#ifndef STEPPINGSWITCH_H_
#define STEPPINGSWITCH_H_

#include "ImpulseSwitch.h"

class SteppingSwitch : public ImpulseSwitch
{
public:
    SteppingSwitch(Condition * pSwitchCondition, void *pParam, unsigned int pNumberOfSteps, unsigned long pImpulseDuration,
                   unsigned long pImpluseCooldown);
    virtual ~SteppingSwitch();

    virtual void setup(void);
    virtual void refresh(void);

    inline unsigned int getCurrentStep()
    {
        return mCurrentStep;
    }

    void setState(SwitchState_t pState);

private:
    unsigned int mNumberOfSteps;
    unsigned int mCurrentStep;
};

#endif /* STEPPINGSWITCH_H_ */
