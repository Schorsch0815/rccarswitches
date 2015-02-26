rccarswitches
=============

Helper library with classes implementing switches (used by [rccarpolicelightbar](https://github.com/Schorsch0815/rccarpolicelightbar) and [rccarligths](https://github.com/Schorsch0815/rccarlights))

Ate the moment the following types of switches are available:

1. Switch - Simple switch, where the state can be changed via method setState.
2. ConditionSwitch - A switch, which allows to specify a condition (a function object). In case the condition returns true, the switch will has the status ON, otherwise OFF.
3. ImpulseSwitch - A ConditionSwitch, which is enhanced by an impulse behavior. The state of the switch changes when the condition is true for a configurable time.
4. SteppingSwitch - It's an ImpulseSwitch with more than 2 states. The different states of the switch will be handled as steps and will be switched in a circular way. For a stepping switch with 4 steps the order of steps will be 0,1,2,3,0,1,... Each impulse will switch to the next step.

Known issues
------------

At the moment neither Makefiles nor Eclipse project files are part of the project.


