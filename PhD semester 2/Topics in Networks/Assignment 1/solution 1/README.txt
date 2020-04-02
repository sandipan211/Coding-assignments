How to run
-----------------
$g++ assignment1_1.cpp -o routing
$./routing −top topology_file −conn connections_file −rt routing_table_file −
ft forwarding_tablefile − path paths_file − flag hop_or_dist − p 0|1

							OR

$make all - compiles the code

Then the four csaes for each network:

$./routing -top top14.doc -conn NSFNET_100.doc -rt routingfile.txt -ft forwarding.txt -path pathfile.txt -flag dist -p 0

$./routing -top top14.doc -conn NSFNET_100.doc -rt routingfile.txt -ft forwarding.txt -path pathfile.txt -flag dist -p 1

$./routing -top top14.doc -conn NSFNET_100.doc -rt routingfile.txt -ft forwarding.txt -path pathfile.txt -flag hop -p 0

$./routing -top top14.doc -conn NSFNET_100.doc -rt routingfile.txt -ft forwarding.txt -path pathfile.txt -flag hop -p 1


$./routing -top top24.doc -conn ARPANET_100.doc -rt routingfile.txt -ft forwarding.txt -path pathfile.txt -flag dist -p 0

$./routing -top top24.doc -conn ARPANET_100.doc -rt routingfile.txt -ft forwarding.txt -path pathfile.txt -flag dist -p 1

$./routing -top top24.doc -conn ARPANET_100.doc -rt routingfile.txt -ft forwarding.txt -path pathfile.txt -flag hop -p 0

$./routing -top top24.doc -conn ARPANET_100.doc -rt routingfile.txt -ft forwarding.txt -path pathfile.txt -flag hop -p 1

File Formats:
-----------------

1. Routing Table: 
	- [ Source_node || Destination_node || Path || Path Delay || Path Cost ]
	- Path is stored as : [1-2-3-4-5-6]
	- For each node, two consecutive lines represent the shortest and second-shortest paths respectively for the current source-destination pair.

2. Forwarding table ( for each admitted connection):
	- [ Router’s ID || ID(Incoming Port) || VCID || ID(Outgoing Port) || VCID ] 

3. Output file (for each admitted connection):
	- [Connection ID || Source || Destination|| Path || {VCID List}|| Path Cost]

4. Pathfile:
	- [Total_connections  Admitted Connections]



Explanations:
-----------------

There are two parts in the question : Routing setup and Connection establishment.

================================================================================
									Routing Setup
================================================================================

 - The topology is read into a matrix.

 - Distance metric here (other than hop) is used as 10 * propagation delay
 - To find the two shortest paths from each node to evey other node, Floyd-Warshall algorithm has been used.

 - Then, the routing table is stored in a file.

 - Functions used:

 	- read_topology()
 	- original_topology()
 	- all_pairs_shortest_paths()
 	- store_shortest_paths()
 	- remove_shortest_path()
 	- store_second_best_path()
 	- print_shortest_paths()
 	- print_cost_and_parent()
 	- store_routing_table()

================================================================================
 							   Connection Establishment
================================================================================
 - The connections are read into a matrix first.

 - For optimistic approach and pessimistic approach, just the calculation using the given formula is different - the rest of the procedure is the same.

 - While calculating using the given formula, since we have to check for each link in the shortest path (best or second-best), we check the given condition for each link  - if each link passes the condition, then only we move forward by subtracting the calculated quantity (B) from the capacity of each link in the path (essentially meaning that a bandwidth of B has been alloted to this path).
 
 - VCIDs are alloted starting from 0.

 - Functions used:

 	- read_connections()
 	- connection_establishment()
 	- my_min()
 	- check_shortest_path()


