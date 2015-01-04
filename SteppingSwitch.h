/*
 * SteppingSwitch.h
 *
 *  Created on: 30.12.2014
 *      Author: Jochen
 */

#ifndef STEPPINGSWITCH_H_
#define STEPPINGSWITCH_H_

#include "ImpulsPinSwitch.h"

class SteppingSwitch : public ImpulsPinSwitch
{
public:
    SteppingSwitch(unsigned int pNumberOfSteps, unsigned int pPin, unsigned long pImpulseDuration,
                   unsigned long pImpluseCooldown);
    virtual ~SteppingSwitch();

    virtual void setup(void);
    virtual void refresh(void);

    inline unsigned int getCurrentStep()
    {
        return m_currentStep;
    }

    void setState(SwitchState_t pState);

private:
    unsigned int m_numberOfSteps;
    unsigned int m_currentStep;
};

#endif /* STEPPINGSWITCH_H_ */
