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
        mstate = pState;
    }

    inline SwitchState_t getState( void )
    {
        return mstate;
    }

    inline SwitchState_t getInvertedState( void )
    {
        return (ON == mstate) ? OFF : ON;;
    }

protected:

private:

    SwitchState_t mstate;
};

#endif /* SWITCH_H_ */
