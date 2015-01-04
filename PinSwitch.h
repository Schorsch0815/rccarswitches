/*
 * PinSwitch.h
 *
 *  Created on: 19.12.2014
 *      Author: Jochen
 */

#ifndef PINSWITCH_H_
#define PINSWITCH_H_

#include "Switch.h"

class PinSwitch : public Switch
{
public:
    PinSwitch(unsigned int pPin);
    virtual ~PinSwitch();

    virtual void setup(void);

    virtual void refresh(void);

protected:
    inline unsigned int getInputPin()
    {
        return m_inputPin;
    }

private:
    unsigned int m_inputPin;
};

#endif /* PINSWITCH_H_ */
