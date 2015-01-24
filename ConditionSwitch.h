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

typedef bool Condition(void);

class ConditionSwitch : public Switch
{

public:
    ConditionSwitch(Condition * pSwitchCondition);

    virtual void refresh(void);

protected:

    inline bool evaluateCondition(void)
    {
        return mSwitchCondition();
    }

private:
    ConditionSwitch() : mSwitchCondition(NULL)
    {
        // no default constructor for switch with Predicate
    }

private:
    Condition * mSwitchCondition;
};

#endif /* SWITCH_H_ */
