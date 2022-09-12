SMART DISPATCHER

Implementation of the consumer consumer producer, using RAII design pattern.
Simulating reporters reporting to a single news feed all their reports.
The reports are sorted by types (sports, weather or news), and then printed on the screen.
All these jobs are done simultaneously.

Developed in C++, POSIX libraries.

To run the program, please provide as a parameter a path to a configuration file, containing blocks of 3 unsigned ints, and one last block of 1 unsigned int.

Data represented by a single 3 lined block:
- Producer ID
- Number of products
- Capacity of each of their individual bounded queue.

The last number in the file represents the buffer of the screen's bounded queue.

Example for a configuration file:

1  
4  
3  

2  
3  
6  

3  
10  
4  

4  
4  
2  

5
