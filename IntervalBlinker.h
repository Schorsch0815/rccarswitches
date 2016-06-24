/*
 * BlinkerRelay.h
 *
 *  Created on: Sep 18, 2015
 *      Author: ejocsch
 */

#ifndef INTERVALBLINKER_H_
#define INTERVALBLINKER_H_

#include "Switch.h"

/**
 * Nearly every 49,7 days the blinker has a problem because of the overrun of the milli seconds counter in arduino,
 * which is based on an unsigend long which is 2^32. Therefore the problem occurs ever 2^32 / 1000 /60 / 60 / 24 days =
 * 49,71027 days
 */
class IntervalBlinker : public Switch
{
public:
    IntervalBlinker( Switch &pSwitch, unsigned long pIntervalDuration );
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
