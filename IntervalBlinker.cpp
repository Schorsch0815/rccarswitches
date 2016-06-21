/*
 * BlinkerRelay.cpp
 *
 *  Created on: Sep 18, 2015
 *      Author: ejocsch
 */

#include "IntervalBlinker.h"

#include <limits.h>

#include "Arduino.h"

IntervalBlinker::IntervalBlinker( Switch &pSwitch, unsigned long pIntervalDuration )
    : mSwitch( pSwitch )
    , mLastBlinkTimestamp( ULONG_MAX )
    , mIntervalDuration( pIntervalDuration )
{
}

IntervalBlinker::~IntervalBlinker() {}

void IntervalBlinker::refresh()
{
    if ( mSwitch.getState() )
    {
        unsigned long lMillis = millis();

        // in case we start from scratch (millis() returns 0 or we have an overflow of millis (after 49,71 days uptime
        // or the last change of blinker is older than interval duration we will switch the blinker
        if ( ( lMillis < mLastBlinkTimestamp ) || ( mIntervalDuration <= lMillis - mLastBlinkTimestamp ) )
        {
            setState( getInvertedState() );
            mLastBlinkTimestamp = lMillis;
        }
    }
    else
    {
        setState( OFF );
    }
}
