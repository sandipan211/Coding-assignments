#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <cctype>			// for tolower()

#define TOTAL_SIMULATION_TIME   1.0e4    // Simulation time
#define num_servers 3
#define chair_buffers 10
#define dropping_probability 0.01

using namespace std;

// Function for generating exponential variates based on inverse transform sampling
long double generate_exp_rv(long double mean)		// mean = 1/ effective_lambda
{
	long double x;                     //  to get: a uniform random number from 0 to 1

	do
	{
		x = ((long double) rand() / RAND_MAX);
	} while ((x == 0) || (x == 1));

  
  return(-log(x) * mean);
}


int factorial(int n) 
{ 
    if (n == 0) 
        return 1; 
    return n * factorial(n - 1); 
}

int upcoming_dep_time_index(long double departure_timestamp[])
{
	int min_index = 0;
	for(int i = 1; i < num_servers; i++)
		if (departure_timestamp[i] < departure_timestamp[min_index])
			min_index = i;

	return min_index; 
}

int find_first_free_officer(int free_officer[])
{
	for(int i = 0; i < num_servers; i++)
		if(free_officer[i] == 1)
			return i;
}


// Function that returns random numbers from 0 to num_servers-1 with equal probability
int queue_number()
{
	return (rand() % num_servers);			// returns a random queue number with equal probability (from queues 0, 1, and 2)
}

// Generate random numbers between 1 to 12 with equal probability using a
// function that generates random numbers from 1 to 6 with equal probability

/* 
	simulation for each of the m queues:
	The following is the simulation of m M/M/1 queues effectively:-
*/
void simulate(long double lambda, long double mu, int mmi)
{
	long double interarrival_time = 1.0/lambda;   // Mean time between arrivals
	// equiprobable queuing arrivals; so equivalent arrival rate is reduced by num_servers

	long double service_time = 1.0/mu;      // Mean service time

	long double present_time = 0;	// the master clock that keeps ticking - simulation time
	long double arrival_timestamp[num_servers];	// instant of current arrival for each queue
	long double departure_timestamp[num_servers];	// instant of a departure for each queue
	long double prev_arr_or_dep_timestamp[num_servers];	// instant of the last event

	long double time_sum_current_system_passengers[num_servers];
	long double time_sum_current_waiting_passengers[num_servers];
	long double time_sum_current_service[num_servers];

	long double passengers_serviced[num_servers];
	long double passengers_arrived[num_servers];
	long double passengers_waited[num_servers];
	long double current_system_passengers[num_servers];
	long double current_waiting_passengers[num_servers];

	int more_arrivals_on_mindep_queue[num_servers];
	int queue_index, last_queue_index, min_index, last_min_index;
	int first_iter = 1;
	long double min_dep_time;

	long double output_et = 0, output_en = 0;
	long double output_eq[num_servers];
	long double output_nq[num_servers];
	// instants of arrival and departure will keep updating as per exponential distribution,
	// while the master clock keeps ticking

	// initializing the arrays
	for(int i  = 0; i < num_servers; i++)
	{
		arrival_timestamp[i] = 0;
		departure_timestamp[i] = TOTAL_SIMULATION_TIME;
		prev_arr_or_dep_timestamp[i] = 0;
		passengers_arrived[i] = 0;
		passengers_waited[i] = 0;
		passengers_serviced[i] = 0;
		time_sum_current_system_passengers[i] = 0;
		time_sum_current_waiting_passengers[i] = 0;
		current_system_passengers[i] = 0;
		current_waiting_passengers[i] = 0;
		more_arrivals_on_mindep_queue[i] = 1;
		output_eq[i] = 0;
		output_nq[i] = 0;
		time_sum_current_service[i] = 0;
	}


	// cout<<"\n========================================================================================================================";
	// cout<<"\n                                                Queue simulation : parameters";
	// cout<<"\n========================================================================================================================";
	// cout<<"\nCLOCK || In Airport Security System ||  Waiting in Queue || Passengers Arrived || Passengers Serviced || Passengers waited";
	// cout<<"\n========================================================================================================================";

	// assumed that first arrival occurs at time t = 0
	
	while(present_time < TOTAL_SIMULATION_TIME)
	{

		//cout<<"\n"<< present_time<<"||"<<current_system_passengers <<"\t\t\t  ||"<< current_waiting_passengers <<"\t\t      ||"<< passengers_arrived<< "\t\t           ||" << passengers_serviced<< "\t\t\t\t||"<<passengers_waited;

		// selecting a queue for an arrival to go to
		if(first_iter)
		{
			queue_index = queue_number(); 
			// since first arrival is at t = 0, do this only the first time; from the next time
			// onwards, queue to go will be calculated inside the if{} below 
			first_iter = 0;
		}

		min_index = upcoming_dep_time_index(departure_timestamp);
		min_dep_time = departure_timestamp[min_index];
		// handling an arrival: an arrival to queue i has to keep track of only the FCFS departure of queue i; whereas in M/M/3
		// queue, an arrival had to keep track of FCFS departure of all three servers
		if(arrival_timestamp[queue_index] < min_dep_time)			 
		{
			passengers_arrived[queue_index]++;
			present_time = arrival_timestamp[queue_index];
			/* 
				To find average number of passengers in the checking system, we want to have:
					avg = total time spent by all passengers in system / (total runtime)

				current_system_passengers will always keep increasing, but current_waiting_passengers
				may decrease/increase and eventually it will become zero
			*/
			// following line calculates the systm time spent till just before new arrival 
			time_sum_current_system_passengers[queue_index] += current_system_passengers[queue_index] * (arrival_timestamp[queue_index] - prev_arr_or_dep_timestamp[queue_index]);
			current_system_passengers[queue_index]++;
			prev_arr_or_dep_timestamp[queue_index] = present_time;
			last_queue_index = queue_index;

			if(current_system_passengers[queue_index] == 1)
			// If there is only 1 passenger in the current queue, timestamp to finish the service is computed;
			// if it is before the next arrival to this queue, no passenger has to wait; else, has to.	
			{
				departure_timestamp[queue_index] = present_time + generate_exp_rv(service_time);
				time_sum_current_service[queue_index] += departure_timestamp[queue_index] - present_time;
			}
			
			if(current_system_passengers[queue_index] > 1)
			{
				current_waiting_passengers[queue_index]++;
				passengers_waited[queue_index]++;
			}


			

			// the next arrival could be to the same queue or to a different queue
			queue_index = queue_number();			// passenger selecting a queue
			arrival_timestamp[queue_index] = present_time + generate_exp_rv(interarrival_time);


					
			// an officer (server) can check one passenger with a service rate mu at a time. If
			// more passengers arrive on that queue before current passenger is checked, more jobs
			// wait in the queue and waiting time sums up. Hence, at any time, if currently there 
			// are more than 1 passengers in the queue, from the next job onwards waiting will start.
			



			if(min_index == queue_index)
				more_arrivals_on_mindep_queue[min_index] = 1;

			else    // the queue having incoming departure doesn't have the next arrival in it
				more_arrivals_on_mindep_queue[min_index] = 0;
				

			if(arrival_timestamp[queue_index] < min_dep_time)
					time_sum_current_waiting_passengers[queue_index] += current_waiting_passengers[queue_index] * (arrival_timestamp[queue_index] - prev_arr_or_dep_timestamp[queue_index]);
				else
					time_sum_current_waiting_passengers[queue_index] += current_waiting_passengers[queue_index] * (min_dep_time - prev_arr_or_dep_timestamp[queue_index]);
	
		}


		else
		{
			// queue with index min_index is being served
			present_time = departure_timestamp[min_index];
			time_sum_current_system_passengers[min_index] += current_system_passengers[min_index] * (departure_timestamp[min_index] - prev_arr_or_dep_timestamp[min_index]);
			
			current_system_passengers[min_index]--;
			passengers_serviced[min_index]++;
			

			// accounting for any leftover waiting time for the queue just serviced; condition
			// may have arisen from problems discussed in arrivals section
			if(more_arrivals_on_mindep_queue[min_index] == 0) 
			{
				// if arrival didn't happen on the queue having departure, meaning it's last
				// waiting time from prev_arr_or_dep_timestamp to departure_timestamp hasn't
				// been summed up, then add it
				time_sum_current_waiting_passengers[min_index] += current_waiting_passengers[min_index] * (departure_timestamp[min_index] - prev_arr_or_dep_timestamp[min_index]);
			}

			// making the serviced one have the MAX time now, so that while finding out the 
			// next departure time using min of those present in departure_timestamp[], it 
			// is not taken into account 
			departure_timestamp[min_index] = TOTAL_SIMULATION_TIME;

			prev_arr_or_dep_timestamp[min_index] = present_time;

			last_min_index = min_index;
			// checking NEXT if there could be any other departure from this queue before the next arrival (computed earlier)
			if(current_system_passengers[min_index] > 0)
			{
				departure_timestamp[min_index] = present_time + generate_exp_rv(service_time); // for next departure time
				time_sum_current_service[min_index] = departure_timestamp[min_index] - present_time;
				current_waiting_passengers[min_index]--; // after one departure is done, waiting queue descreases by 1
								
			}

			
			min_index = upcoming_dep_time_index(departure_timestamp);
			min_dep_time = departure_timestamp[min_index];

			// This new min. departure could be from the last dep. queue (last_min_index) or some
			// other queue (min_index != last_min_index)
			if((more_arrivals_on_mindep_queue[last_min_index] == 1) && (last_min_index == min_index))
			// if next arrival was indeed on mindep_queue
			{
				if(min_dep_time < arrival_timestamp[last_min_index])
				{ 
					// prev and current deps. on same queue, and current dep. before arrival on this queue
					time_sum_current_waiting_passengers[last_min_index] += current_waiting_passengers[last_min_index] * (min_dep_time - prev_arr_or_dep_timestamp[last_min_index]);
					more_arrivals_on_mindep_queue[last_min_index] = 1;	//redundant line
				}
				else			
				{
					// add the queuing time upto next arrival
					time_sum_current_waiting_passengers[last_min_index] += current_waiting_passengers[last_min_index] * (arrival_timestamp[last_min_index] - prev_arr_or_dep_timestamp[last_min_index]);

				}
			}

			if((more_arrivals_on_mindep_queue[last_min_index] != 1) && (last_min_index == min_index))
			{
				if(min_dep_time < arrival_timestamp[queue_index])	// next arrival on some other queue
				{
					// job of line below is done in next iteration as more_arrivals_on_mindep_queue = 0
					// time_sum_current_waiting_passengers[last_min_index] += current_waiting_passengers[last_min_index] * (min_dep_time - prev_arr_or_dep_timestamp[last_min_index]);
					more_arrivals_on_mindep_queue[last_min_index] = 0;
				}
			}

			if ((more_arrivals_on_mindep_queue[last_min_index] == 1) && (last_min_index != min_index))
			{
				if(min_dep_time < arrival_timestamp[last_min_index])	// next arrival on same queue but departure on different queue
					time_sum_current_waiting_passengers[min_index] += current_waiting_passengers[min_index] * (min_dep_time - prev_arr_or_dep_timestamp[min_index]);
				
			}

			if ((more_arrivals_on_mindep_queue[last_min_index] != 1) && (last_min_index != min_index))
			{
				if(min_dep_time < arrival_timestamp[queue_index])	// next arrival on different queue and departure on  different queue
				{
					more_arrivals_on_mindep_queue[last_min_index] = 0;
				}
			}

			if((current_system_passengers[0] = 0) && (current_system_passengers[1] ==0) && (current_system_passengers[2] ==0))
			{
				// if no passenger in the system, start the departure time afresh
				for(int i = 0; i < num_servers; i++)
					departure_timestamp[i] = TOTAL_SIMULATION_TIME;
			}
		}
	}



	
	// Compute outputs

	long double eq =0, nq = 0, total_passengers_arrived = 0, total_passengers_waited = 0, total_service_time = 0;
	for(int i = 0; i < num_servers; i++)
	{
		output_et += time_sum_current_system_passengers[i];
		output_en += time_sum_current_system_passengers[i];
		total_passengers_arrived += passengers_arrived[i]; 
		total_passengers_waited += passengers_waited[i];
		eq += time_sum_current_waiting_passengers[i];
		nq += time_sum_current_waiting_passengers[i];
		total_service_time += time_sum_current_service[i];
	}


	cout<<"\n\n====================================================";
	cout<<"\n                      Reports";
	cout<<"\n====================================================";

	cout<<"\nAverage number of passengers getting inspected = "<< output_et/present_time;
	cout<<"\nAverage response time for passengers in getting inspected = "<< output_et/total_passengers_arrived;
	cout<<"\nAverage time for which a passenger has to wait until getting inspected = "<<(output_et - total_service_time)/total_passengers_arrived;
	// for(int i =  0; i < num_servers; i++)
	// {
	// 	cout<<time_sum_current_waiting_passengers[i] / passengers_waited[i] <<"\t";
	// }
	cout<<"\nAverage number of passengers waiting in queue before each officer = "<< total_passengers_waited/total_passengers_arrived;
	// cout<<"\ntotal queue time"<< time_sum_current_waiting_passengers<<" "<<time_sum_current_system_passengers;
}




/* 
	simulation for 1 queue with m (=3) servers:
	The following is the simulation of an M/M/3 queue effectively:-
*/

void simulate(long double lambda, long double mu, char mmi)
{
	long double interarrival_time = 1.0/lambda;   // Mean time between arrivals
	long double service_time = 1.0/mu;      // Mean service time

	long double present_time = 0;	// the master clock that keeps ticking - simulation time
	long double arrival_timestamp = 0;	// instant of current arrival
	long double departure_timestamp[num_servers];	// instant of a departure
	long double prev_arr_or_dep_timestamp = 0;	// instant of the last event
	
	long double current_system_passengers = 0;
	long double time_sum_current_system_passengers = 0;
	long double current_waiting_passengers = 0;
	long double time_sum_current_waiting_passengers = 0;

	long double passengers_serviced = 0;
	long double passengers_arrived = 0;
	long double passengers_waited = 0;

	long double servers_engaged = 0;
	int free_officer[num_servers];		// initially all servers are free
	int free_officer_index;

	int min_index;
	long double min_dep_time;
	int all_servers_engaged = 0;				// initially false
	// instants of arrival and departure will keep updating as per exponential distribution,
	// while the master clock keeps ticking

	// Array initializations
	for(int i = 0; i < num_servers; i++)
	{
		free_officer[i] = 1;
		departure_timestamp[i] = TOTAL_SIMULATION_TIME;
	}	

	cout<<"\n========================================================================================================================================";
	cout<<"\n                                                Queue simulation : parameters";
	cout<<"\n========================================================================================================================================";
	cout<<"\nCLOCK || In Airport Security System ||  Waiting in Queue || Passengers Arrived || Passengers Serviced || Passengers waited || Servers engaged";
	cout<<"\n========================================================================================================================================";

	while(present_time < TOTAL_SIMULATION_TIME)
	{

		cout<<"\n"<< present_time<<"||"<<current_system_passengers <<"\t\t\t  ||"<< current_waiting_passengers <<"\t\t      ||"<< passengers_arrived<< "\t\t           ||" << passengers_serviced<< "\t\t\t\t||"<<passengers_waited<<"\t\t\t||"<<servers_engaged;
		
		min_index = upcoming_dep_time_index(departure_timestamp);
		min_dep_time = departure_timestamp[min_index];
		if(arrival_timestamp < min_dep_time)			// handling an arrival 
		{
			passengers_arrived++;
			present_time = arrival_timestamp;

			// when m (=3) servers are already allocated, from the next arrival onwards, we 
			// should know that more servers cannot be engaged. Hence we first check if number
			// engaged servers is already m or not
			if(servers_engaged == num_servers)
				all_servers_engaged = 1;
			else
			{
				all_servers_engaged = 0;		// to be safe as of now - avoid potential error
				servers_engaged++;				// allocating an officer if free
			}
			/* 
				To find average number of passengers in the checking system, we want to have:
					avg = total time spent by all passengers in system / (total runtime)

				current_system_passengers will always keep increasing, but current_waiting_passengers
				may decrease/increase and eventually it will become zero
		
			*/

			// In the following snippet, we are calculating the amount of time being spent by 
			// each passenger in the system
			time_sum_current_system_passengers += current_system_passengers * (arrival_timestamp - prev_arr_or_dep_timestamp);
			current_system_passengers++;

			arrival_timestamp = present_time + generate_exp_rv(interarrival_time);
			prev_arr_or_dep_timestamp = present_time;

			// end of snippet


			// an officer (server) can check one passenger with a service rate mu at a time. There 
			// are m servers in the system. If more passengers arrive on that queue before current 
			// passengers are checked in the engaged servers, more jobs wait in the queue and 
			// waiting time sums up. 
			if(all_servers_engaged)
			{
				current_waiting_passengers++;
				passengers_waited++;

				if(arrival_timestamp < departure_timestamp[min_index])
					time_sum_current_waiting_passengers += current_waiting_passengers * (arrival_timestamp - prev_arr_or_dep_timestamp);
				else
					time_sum_current_waiting_passengers += current_waiting_passengers * (departure_timestamp[min_index] - prev_arr_or_dep_timestamp);

			}

			else
			// Also if there is only 1 passenger before each server in the queue, timestamp to 
			// finish the service is computed; if it is before the next arrival, no passenger 
			// has to wait; else, has to.	
			{
				// find the first free officer to allocate the passenger to
				free_officer_index = find_first_free_officer(free_officer);
				departure_timestamp[free_officer_index] = present_time + generate_exp_rv(service_time);
				free_officer[free_officer_index] = 0;	// officer occupied
			}
		}


		else
		{
			present_time = departure_timestamp[min_index];
			time_sum_current_system_passengers += current_system_passengers * (departure_timestamp[min_index] - prev_arr_or_dep_timestamp);
			
			current_system_passengers--;
			passengers_serviced++;
			servers_engaged--;				// officer serviced one and became free now
			departure_timestamp[min_index] = TOTAL_SIMULATION_TIME; 
			// making the serviced one have the MAX time now, so that while finding out the 
			// next departure time using min of those present in departure_timestamp[], it 
			// is not taken into account 
			free_officer[min_index] = 1;	// officer made free now

			prev_arr_or_dep_timestamp = present_time;

			// the moment an officer is free, if there are any waiting passenger(s), allocate
			// them the server
			if(current_waiting_passengers > 0)
			{
				// find the first free officer to allocate the passenger to
				free_officer_index = find_first_free_officer(free_officer);
				departure_timestamp[free_officer_index] = present_time + generate_exp_rv(service_time);
				free_officer[free_officer_index] = 0;	// officer occupied
				current_waiting_passengers--;
				servers_engaged++;
			}
			// checking NEXT if there could be any other departure before the next arrival (computed earlier)

			min_index = upcoming_dep_time_index(departure_timestamp);
			min_dep_time = departure_timestamp[min_index]; // since one who came first is served first
			
			if(min_dep_time < arrival_timestamp)
			{
				time_sum_current_waiting_passengers += current_waiting_passengers * (min_dep_time - prev_arr_or_dep_timestamp);
			}

			else			
			{
				// add the queuing time upto next arrival
				time_sum_current_waiting_passengers += current_waiting_passengers * (arrival_timestamp - prev_arr_or_dep_timestamp);

			}
			

			if(current_system_passengers == 0)
			{
				// if no passenger in the system, start the departure time afresh
				for(int i = 0; i < num_servers; i++)
					departure_timestamp[i] = TOTAL_SIMULATION_TIME;
			}
		}
	}



	
	// Compute outputs
	cout<<"\n\n====================================================";
	cout<<"\n                      Reports";
	cout<<"\n====================================================";

	cout<<"\nAverage number of passengers getting inspected = "<< time_sum_current_system_passengers/present_time;
	cout<<"\nAverage response time for passengers in getting inspected = "<< time_sum_current_system_passengers/passengers_arrived;
	cout<<"\nAverage time for which a passenger has to wait until getting inspected = "<< time_sum_current_waiting_passengers/passengers_waited;
	cout<<"\nAverage number of passengers waiting in queue before each officer = "<< passengers_waited/passengers_arrived;
	//cout<<"\ntotal queue time"<< time_sum_current_waiting_passengers<<" "<<time_sum_current_system_passengers;
}


/* 
	Simulation for each of the m queue with m (=3) servers. This case is only for the elderly
	passengers, not the regular ones. For each officer there will be a queue of 10 chairs, that's it. 
	All passengers are considered elderly here. An elderly passenger P joins any queue of chairs 
	with an equal probability. If the queue in which he/she goes is full, P is dropped from the system, with a probability
	0.01. 
	The following is the simulation of an M/M/1/B (B=10) queue effectively:-
*/
void simulate(long double lambda, long double mu)
{
	long double effective_lambda = lambda * (1.0 - dropping_probability);
	long double interarrival_time = 1.0/effective_lambda;   // Mean time between arrivals
	// equiprobable queuing arrivals; so equivalent arrival rate is reduced by num_servers

	long double service_time = 1.0/mu;      // Mean service time

	long double present_time = 0;	// the master clock that keeps ticking - simulation time
	long double arrival_timestamp[num_servers];	// instant of current arrival for each queue
	long double departure_timestamp[num_servers];	// instant of a departure for each queue
	long double prev_arr_or_dep_timestamp[num_servers];	// instant of the last event
	int free_chairs_per_queue[num_servers];

	long double time_sum_current_system_passengers[num_servers];
	long double time_sum_current_waiting_passengers[num_servers];
	long double time_sum_current_service[num_servers];

	long double passengers_serviced[num_servers];
	long double passengers_arrived[num_servers];
	long double passengers_waited[num_servers];
	long double passengers_dropped[num_servers];
	long double current_system_passengers[num_servers];
	long double current_waiting_passengers[num_servers];

	int more_arrivals_on_mindep_queue[num_servers];
	int queue_index, last_queue_index, min_index, last_min_index;
	int first_iter = 1;
	int attempt_number;
	long double min_dep_time;

	long double output_et = 0, output_en = 0;
	long double output_eq[num_servers];
	long double output_nq[num_servers];
	// instants of arrival and departure will keep updating as per exponential distribution,
	// while the master clock keeps ticking

	// initializing the arrays
	for(int i  = 0; i < num_servers; i++)
	{
		arrival_timestamp[i] = 0;
		departure_timestamp[i] = TOTAL_SIMULATION_TIME;
		prev_arr_or_dep_timestamp[i] = 0;
		passengers_arrived[i] = 0;
		passengers_waited[i] = 0;
		passengers_serviced[i] = 0;
		passengers_dropped[i] = 0;
		free_chairs_per_queue[i] = chair_buffers;
		time_sum_current_system_passengers[i] = 0;
		time_sum_current_waiting_passengers[i] = 0;
		current_system_passengers[i] = 0;
		current_waiting_passengers[i] = 0;
		more_arrivals_on_mindep_queue[i] = 1;
		output_eq[i] = 0;
		output_nq[i] = 0;
		time_sum_current_service[i] = 0;
	}


	// cout<<"\n========================================================================================================================";
	// cout<<"\n                                                Queue simulation : parameters";
	// cout<<"\n========================================================================================================================";
	// cout<<"\nCLOCK || In Airport Security System ||  Waiting in Queue || Passengers Arrived || Passengers Serviced || Passengers waited";
	// cout<<"\n========================================================================================================================";

	// assumed that first arrival occurs at time t = 0
	
	while(present_time < TOTAL_SIMULATION_TIME)
	{

		//cout<<"\n"<< present_time<<"||"<<current_system_passengers <<"\t\t\t  ||"<< current_waiting_passengers <<"\t\t      ||"<< passengers_arrived<< "\t\t           ||" << passengers_serviced<< "\t\t\t\t||"<<passengers_waited;

		// selecting a queue for an arrival to go to
		if(first_iter)
		{
			queue_index = queue_number(); 
			// since first arrival is at t = 0, do this only the first time; from the next time
			// onwards, queue to go will be calculated inside the if{} below 
			first_iter = 0;
		}

		min_index = upcoming_dep_time_index(departure_timestamp);
		min_dep_time = departure_timestamp[min_index];
		// handling an arrival: an arrival to queue i has to keep track of only the FCFS departure of queue i; whereas in M/M/3
		// queue, an arrival had to keep track of FCFS departure of all three servers
		if(arrival_timestamp[queue_index] < min_dep_time)			 
		{
			passengers_arrived[queue_index]++;
			present_time = arrival_timestamp[queue_index];
			free_chairs_per_queue[queue_index]--;			// occupied one chair in selected queue 
			/* 
				To find average number of passengers in the checking system, we want to have:
					avg = total time spent by all passengers in system / (total runtime)

				current_system_passengers will always keep increasing, but current_waiting_passengers
				may decrease/increase and eventually it will become zero
			*/
			// following line calculates the systm time spent till just before new arrival 
			time_sum_current_system_passengers[queue_index] += current_system_passengers[queue_index] * (arrival_timestamp[queue_index] - prev_arr_or_dep_timestamp[queue_index]);
			current_system_passengers[queue_index]++;
			prev_arr_or_dep_timestamp[queue_index] = present_time;
			last_queue_index = queue_index;

			if(current_system_passengers[queue_index] == 1)
			// If there is only 1 passenger in the current queue, timestamp to finish the service is computed;
			// if it is before the next arrival to this queue, no passenger has to wait; else, has to.	
			{
				departure_timestamp[queue_index] = present_time + generate_exp_rv(service_time);
				time_sum_current_service[queue_index] += departure_timestamp[queue_index] - present_time;
			}
			
			if(current_system_passengers[queue_index] > 1)
			{
				current_waiting_passengers[queue_index]++;
				passengers_waited[queue_index]++;
			}

			/*
				The following loop is needed for the following reason:
				Initially attempt_number = 1
				If the next arrival is scheduled to happen to such a queue which is already full,
				that passenger needs to be dropped, and the next arrival timestamp should be 
				calculated as present time + (attempt_number)*(interarrival time), since then the next
				arrival time will keep delaying by (interarrival_time) period, while master clock(present_time)
				keeps ticking
			*/
			

			attempt_number = 1;
			while(1)
			{
				// the next arrival could be to the same queue or to a different queue
				queue_index = queue_number();			// passenger selecting a queue
				if(free_chairs_per_queue[queue_index] > 0)	// if a chair is free in that queue
				{
					arrival_timestamp[queue_index] = present_time + (attempt_number) * generate_exp_rv(interarrival_time);
					break;	// arrival is possible, no drop
				}

				else	
				{
					// if chosen queue is full, drop the passenger from the system
					passengers_dropped[queue_index]++;
					attempt_number++;
				}	
			}
			
			// an officer (server) can check one passenger with a service rate mu at a time. If
			// more passengers arrive on that queue before current passenger is checked, more jobs
			// wait in the queue and waiting time sums up. Hence, at any time, if currently there 
			// are more than 1 passengers in the queue, from the next job onwards waiting will start.
			

			// in the above loop, if previous chosen queue was x, but now y has been chosen (x!=y)
			// then for the queue x, from the current value of prev_arr_or_dep_timestamp, any
			// queuing time is not being accounted for in the statements below, because if() depends
			// on queue_index, and queue_index has been changed from queue_index of x to queue_index
			// of y now. To account for that delay, implementation has been done in the departures portion
			
			// if(last_queue_index == queue_index)	// if arrival is again to same queue
			// {

			// 	if(arrival_timestamp[queue_index] < min_dep_time)
			// 		time_sum_current_waiting_passengers[queue_index] += current_waiting_passengers[queue_index] * (arrival_timestamp[queue_index] - prev_arr_or_dep_timestamp[queue_index]);
			// 	else
			// 		time_sum_current_waiting_passengers[queue_index] += current_waiting_passengers[queue_index] * (min_dep_time - prev_arr_or_dep_timestamp[queue_index]);

			// }

			// else
			// {
			// 	if(arrival_timestamp[queue_index] <min_dep_time)
			// 	{
			// 		time_sum_current_waiting_passengers[]
			// 	}
			// }

			if(min_index == queue_index)
				more_arrivals_on_mindep_queue[min_index] = 1;

			else    // the queue having incoming departure doesn't have the next arrival in it
				more_arrivals_on_mindep_queue[min_index] = 0;
				

			if(arrival_timestamp[queue_index] < min_dep_time)
					time_sum_current_waiting_passengers[queue_index] += current_waiting_passengers[queue_index] * (arrival_timestamp[queue_index] - prev_arr_or_dep_timestamp[queue_index]);
				else
					time_sum_current_waiting_passengers[queue_index] += current_waiting_passengers[queue_index] * (min_dep_time - prev_arr_or_dep_timestamp[queue_index]);
	
		}


		else
		{
			// queue with index min_index is being served
			present_time = departure_timestamp[min_index];
			time_sum_current_system_passengers[min_index] += current_system_passengers[min_index] * (departure_timestamp[min_index] - prev_arr_or_dep_timestamp[min_index]);
			
			current_system_passengers[min_index]--;
			passengers_serviced[min_index]++;
			free_chairs_per_queue[min_index]++;	// chair released after service
			

			// accounting for any leftover waiting time for the queue just serviced; condition
			// may have arisen from problems discussed in arrivals section
			if(more_arrivals_on_mindep_queue[min_index] == 0) 
			{
				// if arrival didn't happen on the queue having departure, meaning it's last
				// waiting time from prev_arr_or_dep_timestamp to departure_timestamp hasn't
				// been summed up, then add it
				time_sum_current_waiting_passengers[min_index] += current_waiting_passengers[min_index] * (departure_timestamp[min_index] - prev_arr_or_dep_timestamp[min_index]);
			}

			// making the serviced one have the MAX time now, so that while finding out the 
			// next departure time using min of those present in departure_timestamp[], it 
			// is not taken into account 
			departure_timestamp[min_index] = TOTAL_SIMULATION_TIME;

			prev_arr_or_dep_timestamp[min_index] = present_time;

			last_min_index = min_index;
			// checking NEXT if there could be any other departure from this queue before the next arrival (computed earlier)
			if(current_system_passengers[min_index] > 0)
			{
				departure_timestamp[min_index] = present_time + generate_exp_rv(service_time); // for next departure time
				time_sum_current_service[min_index] = departure_timestamp[min_index] - present_time;
				current_waiting_passengers[min_index]--; // after one departure is done, waiting queue descreases by 1
								
			}

			
			min_index = upcoming_dep_time_index(departure_timestamp);
			min_dep_time = departure_timestamp[min_index];

			// This new min. departure could be from the last dep. queue (last_min_index) or some
			// other queue (min_index != last_min_index)
			if((more_arrivals_on_mindep_queue[last_min_index] == 1) && (last_min_index == min_index))
			// if next arrival was indeed on mindep_queue
			{
				if(min_dep_time < arrival_timestamp[last_min_index])
				{ 
					// prev and current deps. on same queue, and current dep. before arrival on this queue
					time_sum_current_waiting_passengers[last_min_index] += current_waiting_passengers[last_min_index] * (min_dep_time - prev_arr_or_dep_timestamp[last_min_index]);
					more_arrivals_on_mindep_queue[last_min_index] = 1;	//redundant line
				}
				else			
				{
					// add the queuing time upto next arrival
					time_sum_current_waiting_passengers[last_min_index] += current_waiting_passengers[last_min_index] * (arrival_timestamp[last_min_index] - prev_arr_or_dep_timestamp[last_min_index]);

				}
			}

			if((more_arrivals_on_mindep_queue[last_min_index] != 1) && (last_min_index == min_index))
			{
				if(min_dep_time < arrival_timestamp[queue_index])	// next arrival on some other queue
				{
					// job of line below is done in next iteration as more_arrivals_on_mindep_queue = 0
					// time_sum_current_waiting_passengers[last_min_index] += current_waiting_passengers[last_min_index] * (min_dep_time - prev_arr_or_dep_timestamp[last_min_index]);
					more_arrivals_on_mindep_queue[last_min_index] = 0;
				}
			}

			if ((more_arrivals_on_mindep_queue[last_min_index] == 1) && (last_min_index != min_index))
			{
				if(min_dep_time < arrival_timestamp[last_min_index])	// next arrival on same queue but departure on different queue
					time_sum_current_waiting_passengers[min_index] += current_waiting_passengers[min_index] * (min_dep_time - prev_arr_or_dep_timestamp[min_index]);
				
			}

			if ((more_arrivals_on_mindep_queue[last_min_index] != 1) && (last_min_index != min_index))
			{
				if(min_dep_time < arrival_timestamp[queue_index])	// next arrival on different queue and departure on  different queue
				{
					more_arrivals_on_mindep_queue[last_min_index] = 0;
				}
			}

			if((current_system_passengers[0] = 0) && (current_system_passengers[1] ==0) && (current_system_passengers[2] ==0))
			{
				// if no passenger in the system, start the departure time afresh
				for(int i = 0; i < num_servers; i++)
					departure_timestamp[i] = TOTAL_SIMULATION_TIME;
			}
		}
	}



	
	// Compute outputs

	long double eq =0, nq = 0, total_passengers_arrived = 0, total_passengers_waited = 0, total_service_time = 0;
	for(int i = 0; i < num_servers; i++)
	{
		output_et += time_sum_current_system_passengers[i];
		output_en += time_sum_current_system_passengers[i];
		total_passengers_arrived += passengers_arrived[i]; 
		total_passengers_waited += passengers_waited[i];
		eq += time_sum_current_waiting_passengers[i];
		nq += time_sum_current_waiting_passengers[i];
		total_service_time += time_sum_current_service[i];
	}


	cout<<"\n\n====================================================";
	cout<<"\n                      Reports";
	cout<<"\n====================================================";

	cout<<"\nAverage number of passengers getting inspected = "<< output_et/present_time;
	cout<<"\nAverage response time for passengers in getting inspected = "<< output_et/total_passengers_arrived;
	cout<<"\nAverage time for which a passenger has to wait until getting inspected = "<<(output_et - total_service_time)/total_passengers_arrived;
	// for(int i =  0; i < num_servers; i++)
	// {
	// 	cout<<time_sum_current_waiting_passengers[i] / passengers_waited[i] <<"\t";
	// }
	cout<<"\nAverage number of passengers waiting in queue before each officer = "<< total_passengers_waited/total_passengers_arrived;
	// cout<<"\ntotal queue time"<< time_sum_current_waiting_passengers<<" "<<time_sum_current_system_passengers;
}


void formula_results(long double lambda, long double mu, char choice)
{
	long double ew, enq, et, en, traffic_intensity, p_zero, sum_term, zeta_factor1, queuing_prob;
	int i;
	if(choice == 'a')
	{
		// using formulae for M/M/1 queue
		et = 1.0 / (mu - lambda);
		en = lambda * et;
		ew = et - (1.0 / mu);
		enq = lambda * ew;
	}

	else if(choice == 'b')
	{
		sum_term = 0;
		traffic_intensity = lambda / (num_servers * mu);
		
		for(i = 0; i < num_servers-1; i++)
			sum_term += (pow((num_servers * traffic_intensity), i))	/ factorial(i);

		zeta_factor1 = (pow((num_servers * traffic_intensity), num_servers)) / (factorial(i) * (1 - traffic_intensity));

		p_zero = 1.0 / (sum_term + zeta_factor1);
		queuing_prob = zeta_factor1 * p_zero;

		enq = (traffic_intensity * queuing_prob) / (1 - traffic_intensity);
		ew = enq / lambda;
		et = ew + 1.0/mu;
		en = lambda * et;
	}

	else if(choice == 'c')
	{
		traffic_intensity = lambda/mu;
		p_zero = (1 - traffic_intensity) / (1 - pow(traffic_intensity, (chair_buffers+1)));

		en = (traffic_intensity / (1 - traffic_intensity)) - ((chair_buffers+1) * pow(traffic_intensity, (chair_buffers+1))) / (1 - pow(traffic_intensity, (chair_buffers+1)));
		et = en / (lambda * (1 - dropping_probability));
		ew = et - 1.0/mu;
		enq = lambda * (1 - dropping_probability) * ew;
	}

	cout<<"\n\n====================================================";
	cout<<"\nResults using formulae:\n";
	cout<<"\nAverage number of passengers getting inspected = "<< en;
	cout<<"\nAverage response time for passengers in getting inspected = "<< et;
	cout<<"\nAverage time for which a passenger has to wait until getting inspected = "<< ew;
	cout<<"\nAverage number of passengers waiting in queue before each officer = "<< enq;
}


int main()
{
	char choice;
	long double lambda, mu;

	// initialize srand with distinctive value
	srand(time(NULL));
	
	do
	{
		cout<<"Queue Simulations at Delhi Airport"<<endl<<"-----------------------"<<endl<<endl;
		cout<<"Case A: 3 serving officers - 3 queues - A regular day"<<endl;
		cout<<"Case B: 3 serving officers - 1 queue - A less busy day"<<endl;
		cout<<"Case C: 3 serving officers - 3 queues - 10 chairs per officer for the elderly"<<endl<<endl;
		cout<<"Press 'e' for exit"<<endl<<endl;
		cout<<"Choose a case: ";
		cin>>choice;

		tolower(choice);					// converting received character to lowercase

		switch(choice)
		{
			case 'a':	cout<<"\nEnter the mean arrival rate (passengers per hour): ";
						cin>>lambda;
						cout<<"\nEnter the mean service rate (passengers per hour): ";
						cin>>mu;

						if(lambda > mu)
						{
							cout<<"\nNot a stable system....arrival rate should be lesser than service rate! Enter again...";
							break;
						}	

						simulate(lambda, mu, 1);	//last arg only for function overloading
						// formula_results(lambda, mu, choice);
						break;

			case 'b':	cout<<"\nEnter the mean arrival rate (passengers per hour): ";
						cin>>lambda;
						cout<<"\nEnter the mean service rate (passengers per hour): ";
						cin>>mu;

						if(lambda > mu)
						{
							cout<<"\nNot a stable system....arrival rate should be lesser than service rate! Enter again...";
							break;
						}	
						simulate(lambda, mu, 'm');
						// formula_results(lambda, mu, choice);
						break;

			case 'c':	cout<<"\nEnter the mean arrival rate (passengers per hour): ";
						cin>>lambda;
						cout<<"\nEnter the mean service rate (passengers per hour): ";
						cin>>mu;
						
						if(lambda > mu)
						{
							cout<<"\nNot a stable system....arrival rate should be lesser than service rate! Enter again...";
							break;
						}	
						simulate(lambda, mu);
						// formula_results(lambda, mu, choice);
						break;

			case 'e':	cout<< "Quitting simulation...\n\n";
						exit(0);

			default:    cout<<"\nInvalid choice! Try again.........";
						break;

		}

		cout<<"\nWant to do another simulation? (press y to continue or e to exit)\t\t";
		cin>>choice;

	}while((choice != 'e') && (choice != 'E'));



	return 0;
}