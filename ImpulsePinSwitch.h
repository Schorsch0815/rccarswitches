/*
 * ImpulsPinSwitch.h
 *
 *  Created on: 19.12.2014
 *      Author: Jochen
 */

#ifndef IMPULSPINSWITCH_H_
#define IMPULSPINSWITCH_H_

#include "PinSwitch.h"

class ImpulsePinSwitch : public PinSwitch
{
public:
    ImpulsePinSwitch(unsigned int pPin, unsigned long pImpulseDuration, unsigned long pImpluseCooldown);
    virtual ~ImpulsePinSwitch();

    virtual void refresh(void);

protected:

    unsigned long getImpulseActiveDuration();

    inline unsigned long getMinImpulseDuration()
    {
        return mMinImpulseDuration;
    }

protected:
    bool mWasSwitched;

private:
    unsigned long mImpulseChangeTimestamp;
    unsigned long mMinImpulseDuration;
    unsigned long mImpulseCooldown;
    bool mImpulseActive;
};

#endif /* IMPULSPINSWITCH_H_ */
