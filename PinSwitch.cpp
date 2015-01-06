/*
 * PinSwitch.cpp
 *
 *  Created on: 19.12.2014
 *      Author: Jochen
 */
#include "Arduino.h"

#include "PinSwitch.h"

PinSwitch::PinSwitch(unsigned int pPin) : Switch(), minputPin(pPin)
{
}

PinSwitch::~PinSwitch()
{
}

void PinSwitch::setup(void)
{
    pinMode(minputPin,INPUT);
}


void PinSwitch::refresh(void)
{
    setState(digitalRead(getInputPin()) ? ON : OFF);
}

