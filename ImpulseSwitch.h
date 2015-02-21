/*
 * ImpulsPinSwitch.h
 *
 *  Created on: 19.12.2014
 *      Author: Jochen
 */

#ifndef IMPULSPINSWITCH_H_
#define IMPULSPINSWITCH_H_

#include "ConditionSwitch.h"

class ImpulseSwitch : public ConditionSwitch
{
public:
    ImpulseSwitch(Condition * pSwitchCondition, void *pParam, unsigned long pMinImpulsDuration, unsigned long pImpluseCooldown);

    virtual void refresh(void);

protected:

    unsigned long getImpulseActiveDuration();

    inline unsigned long getMinImpulseDuration()
    {
        return mMinImpulseDuration;
    }

private:
    ImpulseSwitch() : ConditionSwitch(NULL, NULL),
            mWasSwitched(false), mImpulseChangeTimestamp(0), mMinImpulseDuration(0), mImpulseCooldown(0), mImpulseActive(
                    false)
    {
        // no default constructor for switch with Predicate
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
