/*
 * BlinkerRelay.cpp
 *
 *  Created on: Sep 18, 2015
 *      Author: ejocsch
 */

#include "IntervalBlinker.h"

#include "Arduino.h"

IntervalBlinker::IntervalBlinker( Switch &pSwitch, unsigned long pIntervalDuration ) :
        mSwitch( pSwitch ), mIntervalDuration( pIntervalDuration ), mLastBlinkTimestamp(0L)
{
}

IntervalBlinker::~IntervalBlinker()
{
}

void IntervalBlinker::refresh()
{
    if (mSwitch.getState())
    {
        if ((mIntervalDuration < millis() - mLastBlinkTimestamp))
        {
            setState( getInvertedState() );
            mLastBlinkTimestamp = millis();
        }
    }
    else
    {
        setState( OFF );
    }
}
