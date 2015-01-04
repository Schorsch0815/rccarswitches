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
        return m_minImpulseDuration;
    }

protected:
    bool m_wasSwitched;

private:
    unsigned long m_impulseChangeTimestamp;
    unsigned long m_minImpulseDuration;
    unsigned long m_impulseCooldown;
    bool m_impulseActive;
};

#endif /* IMPULSPINSWITCH_H_ */
