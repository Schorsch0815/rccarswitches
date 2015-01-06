/*
 * PinSwitch.cpp
 *
 *  Created on: 19.12.2014
 *      Author: Jochen
 */
#include "Arduino.h"

#include "PinSwitch.h"

PinSwitch::PinSwitch(unsigned int pPin) : Switch(), mInputPin(pPin)
{
}

PinSwitch::~PinSwitch()
{
}

void PinSwitch::setup(void)
{
    pinMode(mInputPin,INPUT);
}


void PinSwitch::refresh(void)
{
    setState(digitalRead(getInputPin()) ? ON : OFF);
}

