Universal Driver  
Botrobi  
========  

* 2 output ports (W1, W2)  
Output ports can be set to 2 states: 0 - off, 1 - on. Each port can be set independently.   

* 2 input ports (P1, P2)  
Input ports can be connected to 1 or 2 sensors each. Sensors can haveopen state - 0, close state - 100 or 200.  
Possible input ports combinations:  
Possible configurations-------------------------|-----Possible output values  
P1 <-------> C1(100).				| 0, 100	  
P1 <-------> C2(200).				| 0, 200  
P1 <-------> C1(100) <-------> C2(200).		| 0, 100, 200, 300  
P2 <-------> C1(100).                           | 0, 100  
P2 <-------> C2(200).                           | 0, 200  
P2 <-------> C1(100) <-------> C2(200).         | 0, 100, 200, 300  
  
Electronic Circuit  
------------  
TBD  
