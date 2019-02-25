Universal Driver
Botrobi
========

* 2 output ports (W1, W2)  
Output ports can be set to 2 states: 0 - off, 1 - on. Each port can be set independently.

* 2 input ports (P1, P2)  
Input ports can be connected to 1 or 2 sensors each. Sensors can haveopen state - 0, close state - 100 or 200.  
Possible input ports combinations:  

 | Possible configurations P1 or/and P2 | Possible output values |
 | -------------- | ----------- |
 | P <-------> C1(100) | 0, 100 |
 | P <-------> C2(200) | 0, 200 |
 | P <-------> C1(100) <-------> C2(200) | 0, 100, 200, 300 |
 
* timer  
Allow to control output ports using timers. Resolution 1s, min 1s max 600s. When set to 0 couters are disabled.  

* 4 programs  
Each program can have 4 independednt conditions.  

Electronic Circuit
------------
TBD  

