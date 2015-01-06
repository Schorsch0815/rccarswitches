/*
 * ImpulsPinSwitch.h
 *
 *  Created on: 19.12.2014
 *      Author: Jochen
 */

#ifndef IMPULSPINSWITCH_H_
#define IMPULSPINSWITCH_H_

#include "PinSwitch.h"

class ImpulsPinSwitch : public PinSwitch
{
public:
    ImpulsPinSwitch(unsigned int pPin, unsigned long pImpulseDuration, unsigned long pImpluseCooldown);
    virtual ~ImpulsPinSwitch();

    virtual void refresh(void);

protected:

    unsigned long getImpulseActiveDuration();

    inline unsigned long getMinImpulseDuration()
    {
        return mminImpulseDuration;
    }

protected:
    bool mwasSwitched;

private:
    unsigned long mimpulseChangeTimestamp;
    unsigned long mminImpulseDuration;
    unsigned long mimpulseCooldown;
    bool mimpulseActive;
};

#endif /* IMPULSPINSWITCH_H_ */
