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
        m_state = pState;
    }

    inline SwitchState_t getState( void )
    {
        return m_state;
    }

    inline SwitchState_t getInvertedState( void )
    {
        return (ON == m_state) ? OFF : ON;;
    }

protected:

private:

    SwitchState_t m_state;
};

#endif /* SWITCH_H_ */
