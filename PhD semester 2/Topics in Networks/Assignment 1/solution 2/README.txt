How to run:
---------------
$g++ assignment1_2.cpp -o queue
$./queue

					OR

$make all - compiles the code
$./queue

Inputs - mean arrival rate (lambda) and mean service rate (mu)
 
Output formats:
---------------
There are two sets of reports presented: the first set represents the reports actually found out using queue simulations; and the second set represents the reports for the same system found out using queuing theory formulae (just for quick verification). The second set can be printed, for each case of switch(),  by uncommenting the line :
			
			formula_results(lambda, mu, choice);

The results are almost as close as possible. Also, since case B is a single queue system, the queue simulations have been also printed for instances of time. Simulation time is a parameter has been defined as a constant in the program. It may be changed as per requirement.


Enough comments have been written in the code for proper explanation.

