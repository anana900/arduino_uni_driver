Farm Universal Driver
========

* 2 output ports (W1, W2)  
 Output ports can be set to 3 states: 'off', 'on', '-' (neutral).
 Each port can be set independently.

* 2 input ports (P1, P2)  
 Input ports can be connected to 2 sensors each. Sensors can have open state or close state each.
 
* Possible input ports combinations are:  
 '-'  - do not read sensor on particular port - do not care  
 '0'  - read sensor on port, ON when single or both sensros are open  
 'B'  - read sensor on port, ON when sensor B is closed  
 'C'  - read sensor on port, ON when sensor C is closed  
 'BC' - read sensor on port, ON when sensor B and C are closed

* Timer  
 Allow to control output ports using timers. Resolution 1s, min 1s max 600s. When set to 0 couters are disabled.  

* 4 programs  
 Each program can have 4 independednt conditions.  

* There are 3 modes available:  
 use sensors state to control the output
 use sensors state to control the output with safety timers
 use timers to control the output

  

