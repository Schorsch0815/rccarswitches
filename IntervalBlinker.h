/*
 * BlinkerRelay.h
 *
 *  Created on: Sep 18, 2015
 *      Author: ejocsch
 */

#ifndef INTERVALBLINKER_H_
#define INTERVALBLINKER_H_

#include "Switch.h"

class IntervalBlinker : public Switch
{
public:
    IntervalBlinker( Switch & pSwitch, unsigned long pIntervalDuration );
    virtual ~IntervalBlinker();

    /**
     * Refreshes the switch state. Has to be called within the loop of an application.
     */
    virtual void refresh();
private:

    Switch &mSwitch;
    unsigned long mLastBlinkTimestamp;
    unsigned long mIntervalDuration;

};

#endif /* INTERVALBLINKER_H_ */
