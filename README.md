Universal Driver
Botrobi
========

* 2 output ports (W1, W2)  
Output ports can be set to 2 states: 0 - off, 1 - on. Each port can be set independently.

* 2 input ports (P1, P2)  
Input ports can be connected to 1 or 2 sensors each. Sensors can have open state or close state each.  
Possible input ports combinations are:  
 '-'  - do not read sensor on particular port - do not care
 '0'  - read sensor on port, ON when single or both sensros are open,
 'A'  - read sensor on port, ON when sensor A is closed
 'B'  - read sensor on port, ON when sensor B is closed
 'AB' - read sensor on port, ON when sensor A and B are closed

* timer  
Allow to control output ports using timers. Resolution 1s, min 1s max 600s. When set to 0 couters are disabled.  

* 4 programs  
Each program can have 4 independednt conditions.  


* There are 3 modes available:  
- use sensors state to control the output
- use sensors state to control the output with safety timers
- use timers to control the output

Electronic Circuit
------------
TBD  

