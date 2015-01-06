/*
 * Switch.h
 *
 *  Created on: 19.12.2014
 *      Author: Jochen
 */

#ifndef SWITCH_H_
#define SWITCH_H_

class Switch
{
public:
    typedef enum
    {
        OFF, ON
    } SwitchState_t;

    Switch();
    virtual ~Switch();

    virtual void setup(void)
    {
    }

    virtual void refresh(void)
    {
    }

    inline void setState( SwitchState_t pState )
    {
        mState = pState;
    }

    inline SwitchState_t getState( void )
    {
        return mState;
    }

    inline SwitchState_t getInvertedState( void )
    {
        return (ON == mState) ? OFF : ON;;
    }

protected:

private:

    SwitchState_t mState;
};

#endif /* SWITCH_H_ */
