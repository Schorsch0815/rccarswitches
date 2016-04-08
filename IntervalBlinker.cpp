/*
 * BlinkerRelay.cpp
 *
 *  Created on: Sep 18, 2015
 *      Author: ejocsch
 */

#include "IntervalBlinker.h"

#include <limits.h>
#include <iostream>

#include "Arduino.h"

using namespace std;

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

        cout << "millis() = " << lMillis << endl;
        cout << "mLastBlinkTimestamp = " << mLastBlinkTimestamp << endl;
        cout << "mIntervalDuration = " << mIntervalDuration << endl;

        // in case we start from scratch (millis() returns 0 or we have an oberflow of millis (after 49,71 days uptime
        // or the last change of blinker is older than interval duration we will switch the blinker
        if ( ( lMillis < mLastBlinkTimestamp ) || ( mIntervalDuration <= millis() - mLastBlinkTimestamp ) )
        {
            setState( getInvertedState() );
            cout << "let's change blinker state. it's " << getState() << " now!" << endl;
            mLastBlinkTimestamp = lMillis;
        }
    }
    else
    {
        setState( OFF );
    }
}
