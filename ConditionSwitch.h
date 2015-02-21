/*
 * Switch.h
 *
 *  Created on: 19.12.2014
 *      Author: Jochen
 */

#ifndef CONDITIONSWITCH_H_
#define CONDITIONSWITCH_H_

#include <stdio.h>

#include "Switch.h"

typedef bool Condition(void * pThis);

class ConditionSwitch : public Switch
{

public:
    ConditionSwitch(Condition * pSwitchCondition, void *pParam);

    virtual void refresh(void);

protected:

    inline bool evaluateCondition(void)
    {
        return mSwitchCondition(mParam);
    }

private:
    ConditionSwitch() : mSwitchCondition(NULL), mParam(NULL)
    {
        // no default constructor for switch with Predicate
    }

private:
    Condition * mSwitchCondition;
    void *mParam;
};

#endif /* SWITCH_H_ */
