// assignment2.cpp : Defines the entry point for the console application.
/* 
	command to run:
	./routing -N switchportcount -B buffersize -p packetgenprob -queue INQ|KOUQ|iSLIP -K knockout -out outputfile -T maxtimeslot
	Ex: ./routing -N 8 -B 4 -p 0.5 -queue INQ -K 4.8 -out outputfile.txt -T 5

*/

#include "stdafx.h"
#include <iostream>
#include <stdlib.h>						// for strtod(), strtoll()
#include <vector>
#include <string.h>						// for strcat() and strcpy()
#include <limits.h>						// for INT_MAX
#include <algorithm>					// for min()
#include <stdio.h>
#include <ctime>
#include <conio.h>
#include <math.h>

using namespace std;

#define default_ports 8
#define max_ports 40
#define default_buffers_per_port 4
#define default_packetgenprob 0.5
#define default_maxtimeslots 10000
#define default_knockout 4.8
#define packet_params 5			
// < packet_id, arrival_time, transmission_completion_time, input_port, output_port >


double total_packet_delay = 0;
double total_packets_transmitted = 0;
double total_packets_generated = 0;
double KOUQ_drop_prob_per_slot = 0;
long long last_pktID = 1;

struct packet
{
	long long packet_id;
	double arrival_time, transmission_completion_time;
	int input_port, output_port;
};


// Function that returns random numbers from 0 to N-1 with equal probability
int destination(int N)
{
	return (rand() % N);	// returns a random in/out port number with equal probability
}

double arrival_offset(double low, double high)
{
	double offset = low + (double) rand()/((double)(RAND_MAX/(high - low)));
	return offset;
}

bool generate_with_probability(double p)
{
	bool generate_or_not = (rand() % 100) < (p*100);
	return generate_or_not;
}

void initialization(bool packetgen[])
{
	for(int i = 0; i < max_ports; i++)
	{
		packetgen[i] = false;
		/*
		in_buffer[i].reserve(B+1);
		out_buffer[i].reserve(B+1);

		packet new_packet;
		new_packet.packet_id = 0;
		new_packet.arrival_time = -1.0;
		new_packet.transmission_completion_time = -2.0;
		new_packet.input_port = -1;
		new_packet.output_port = -2;
		in_buffer[i].push_back(new_packet);
		out_buffer[i].push_back(new_packet);
		// initialized all the ports with a dummy header packet
		*/
	}
}

void traffic_generation(int N, int B, bool packetgen[], vector < vector<packet> > &in_buffer, double p, double t)
{
	int in_port, dest_port;

	for(in_port = 0; in_port < N; in_port++)
	{
		if(generate_with_probability(p) && (in_buffer[in_port].size() < B))
		{
			// if packet is generated and input buffer has still space left
			packetgen[in_port] = true;		// packet generated from this port
			dest_port = destination(N);		// destination randomly selected

			packet new_packet;
			new_packet.arrival_time = t + arrival_offset(0.001, 0.01);	//change it
			new_packet.packet_id = last_pktID++;
			new_packet.input_port = in_port;
			new_packet.output_port = dest_port;
			in_buffer[in_port].push_back(new_packet);	// added a new packet to the input queue
			total_packets_generated++;
		}
	}
}


void schedule_INQ(int N, int B, vector < vector<packet> > &in_buffer, vector < vector<packet> > &out_buffer, double t)
{
	int in_port, out_port, accepted_port, accepted_port_index;
	// an array of vectors, to tell that for each out_port, what are the in_ports contending
	vector < vector<int> > contention_list(max_ports);

	// find out if there are any cases of contention for the generated and/or head packets
	// from each port
	for (in_port = 0; in_port < N; in_port++)
	{
		if(in_buffer[in_port].size() >= 1)
		{
			/*
				if a packet is there at the head of in_port
				can't use packetDest[] to check because it updates after each run of 
				traffic_gen(), but there might be an already waiting packet in some input 
				queue, whose dest. may not be the same as the present value in packetDest[]
			*/ 

			contention_list[in_buffer[in_port][0].output_port].push_back(in_port);
		}	
	}

	for(out_port = 0; out_port < N; out_port++)
	{
		if(contention_list[out_port].size() == 1)
		{
			accepted_port = contention_list[out_port][0];
			// no output port contention - place head packet in output port buffer
			out_buffer[out_port].push_back(in_buffer[accepted_port][0]);
			
			// erase the head packet from input buffer
			in_buffer[accepted_port].erase(in_buffer[accepted_port].begin());
		}

		else if(contention_list[out_port].size() > 1)
		{
			// contention for the output port occurs; select a random in_port for acceptance
			accepted_port_index = destination(contention_list[out_port].size());
			accepted_port = contention_list[out_port][accepted_port_index];
			
			// place head packet from selected in_port in output port buffer
			out_buffer[out_port].push_back(in_buffer[accepted_port][0]);
			
			// erase the head packet from input buffer
			in_buffer[accepted_port].erase(in_buffer[accepted_port].begin());
		}
	}
}

void schedule_KOUQ(int N, int B, vector < vector<packet> > &in_buffer, vector < vector<packet> > &out_buffer, double K, double t)
{
	int in_port, out_port, min_index, contention_port, contending_in_port;
	// an array of vectors, to tell that for each out_port, what are the in_ports contending
	vector < vector<int> > contention_list(max_ports);

	// find out if there are any cases of contention for the generated and/or head packets
	// from each port
	for (in_port = 0; in_port < N; in_port++)
	{
		if(in_buffer[in_port].size() == 1)
		{
			/*
				if a packet is there at the head of in_port
				can't use packetDest[] to check because it updates after each run of 
				traffic_gen(), but there might be an already waiting packet in some input 
				queue, whose dest. may not be the same as the present value in packetDest[]
			*/ 

			// while inserting a contending port, insert in accrodance with the arrival times, so that the contention list contents always
			// remain sorted w.r.t. arrival times
			if(contention_list[in_buffer[in_port][0].output_port].size() == 0)
			{
				// no contending input port yet inserted for this output port 
				contention_list[in_buffer[in_port][0].output_port].push_back(in_port);
			}

			else
			{
				// some contending input port already inserted for this output port; hence have to insert in a position as per
				// increasing arrival times
				min_index = 0;
				contention_port = in_buffer[in_port][0].output_port;

				while(min_index < contention_list[contention_port].size())
				{
					// search for the proper position to insert this new in_port
					// if two or more packets from in_ports have same arrival times, the one which comes first from an input port with 
					// that arrival time will be scheduled first

					contending_in_port = contention_list[contention_port][min_index];
					if(in_buffer[in_port][0].arrival_time < in_buffer[contending_in_port][0].arrival_time)
						break;
					else
						min_index++;
				}

				// place the current in_port at its proper position
				contention_list[contention_port].insert(contention_list[contention_port].begin() + min_index, in_port);	

			}
			
		}	
	}

	// scheduling part
	for (out_port = 0; out_port < N; out_port++)
	{
		if(contention_list[out_port].size() <= K)
		{
			// no dropping required

			while(contention_list[out_port].size() > 0)
			{
				// until all the (<=K) packet requests are scheduled
				// in_ports sorted already accroding to their packet's arrival times - just schedule them in that order
				contending_in_port = contention_list[out_port][0];

				if(out_buffer[out_port].size() < B)		// if buffer of current out_port isn't already full
					out_buffer[out_port].push_back(in_buffer[contending_in_port][0]);
			
				// erase the in_port at the head of the contention_list for current out_port
				contention_list[out_port].erase(contention_list[out_port].begin());

				// erase the head packet from input buffer
				in_buffer[contending_in_port].erase(in_buffer[contending_in_port].begin());
			}
		}

		else
		{
			// more than K packets contending - should keep only K randomly selected packets and put them into output buffer 
			// (according to arrival times) - for the rest of the packets, dropping occurs
			KOUQ_drop_prob_per_slot++;		// packet drop occurs for this port, in this slot

			int max_pkts = (int)(floor(K));
			int selected_in_port, selected_in_port_index;
			int pkt = 0;
			int current_timeslot_initial_index;
			/*
				when the first time in current time slot a packet arrives, this variable serves as a marker to start checking for correct positions to
				insert a new packet into out_buffer, otherwise it's difficult to understand whether for the current packet we need to compare arrival
				times with out_buffer packets or in_buffer packets. If we always start checking from this marker then we can always compare with the
				in_buffer packets only
			*/

			while((pkt < max_pkts) && (out_buffer[out_port].size() < B))
			{
				// till K packets and if buffer is not yet full, select a random contending in_port
				selected_in_port_index = destination(contention_list[out_port].size());  // hence necessary to delete from contention_list everytime
				selected_in_port = contention_list[out_port][selected_in_port_index];

				if (pkt == 0)
				{
					// first packet, so just keep it in the corresponding buffer of out_port 
					out_buffer[out_port].push_back(in_buffer[selected_in_port][0]);
					current_timeslot_initial_index = out_buffer[out_port].size() - 1;
				}

				else
				{
					// buffer of current out_port might already have some queued packets - have to insert a new incoming packet at its proper
					// position as per the arrival time
					min_index =  current_timeslot_initial_index;
					/*
						start checking the position to insert from element at current_timeslot_initial_index;since if there were any other packets 
						already in that port buffer, they are already sorted as per their arrival times, and these new packets are arriving at a 
						later timeslot, so all of them would be having arrival times greater than those already present from the previous timeslots; 
						hence for these new packets in the current timeslot, no need to check their position wrt the packets from previous timeslot(s) already present
					*/
				
					while(min_index < out_buffer[out_port].size())
					{
						// search for the proper position to insert this new in_port
						// if two or more packets from in_ports have same arrival times, the one which comes first from an input port with 
						// that arrival time will be scheduled first

						if(in_buffer[selected_in_port][0].arrival_time < out_buffer[out_port][min_index].arrival_time)
							break;
						else
							min_index++;
					}

					// place the current packet at its proper position in out_buffer
					out_buffer[out_port].insert(out_buffer[out_port].begin() + min_index, in_buffer[selected_in_port][0]);

				}

				// erase the selected_in_port from the contention_list for current out_port
				contention_list[out_port].erase(contention_list[out_port].begin() + selected_in_port_index);

				// erase the head packet from input buffer
				in_buffer[selected_in_port].erase(in_buffer[selected_in_port].begin());
				
				pkt++;
				
			}

			// for the rest of the packets (> K) - should be definitely cleared out of the in_buffer ports. contention_list[out_port] is also
			// being cleared for safety (although doesn't matter)
			for(int i = 0; i < N; i++)
			{
				if ((in_buffer[i].size() > 0) && (in_buffer[i][0].output_port == out_port))
				{
					// if any more input port has a packet destined for current out_port, it should be rejected since max. limit (K) is reached
					in_buffer[i].erase(in_buffer[i].begin());
				}

			}
				
			contention_list[out_port].clear();
		}
	}
}

void schedule_iSLIP(int N, int B, vector < vector<packet> > &in_buffer, vector < vector<packet> > &out_buffer, double t)
{

}


void transmission(int N, int B, vector < vector<packet> > &out_buffer, double t)
{
	int out_port;
	FILE *writer;

	writer = fopen("packet_history.txt", "a");

	for(out_port = 0; out_port < N; out_port++)
	{
		if(out_buffer[out_port].size() >= 1)	// if this out_port has buffered any packet
		{
			// transmission complete time is till the beginning of the next timeslot
			out_buffer[out_port][0].transmission_completion_time = t+1;

			total_packet_delay += (t+1) - floor(out_buffer[out_port][0].arrival_time);
			total_packets_transmitted++;

			// write this packet's history in file
			fprintf(writer, "%lld \t %Lf\t\t %Lf\t\t %d\t %d\n", out_buffer[out_port][0].packet_id, out_buffer[out_port][0].arrival_time, out_buffer[out_port][0].transmission_completion_time, out_buffer[out_port][0].input_port, out_buffer[out_port][0].output_port);
		
			// erase packet from output buffer
			out_buffer[out_port].erase(out_buffer[out_port].begin());

		}
	}	

	fclose(writer);
}


void scheduling(int N, int B, char queueType[], vector < vector<packet> > &in_buffer, vector < vector<packet> > &out_buffer, double K, double t)
{
	if (strcmp(queueType, "INQ") == 0)
		schedule_INQ(N, B, in_buffer, out_buffer, t);
	else if (strcmp(queueType, "KOUQ") == 0)
		schedule_KOUQ(N, B, in_buffer, out_buffer, K, t);
	else if (strcmp(queueType, "iSLIP") == 0)
		schedule_iSLIP(N, B, in_buffer, out_buffer, t);
	else
		cout<<"Error! No such scheduling algorithm.....";

}

int main(int argc, char* argv[])
{
	int status = remove("packet_history.txt");
	int N, B;			// switch-port count, buffer size
	double p, K;	// packet generation probability and knockout
	char queueType[10];	// queue type
	char out[256];		// output filename
	double T;		// max. timeslots
	char *pEnd;			// for strtoll() and strtod()

	bool packetgen[max_ports];		// only kept for checking purpose
	vector < vector<packet> > in_buffer(max_ports);
	vector < vector<packet> > out_buffer(max_ports);

	if (argc == 1)	
	{
		// no arguments passed - i.e. default case
		N = default_ports;
		B = default_buffers_per_port;
		p = default_packetgenprob;
		K = default_knockout;
		strcpy(queueType, "INQ");
		strcpy(out, "outfile.txt");
		T = default_maxtimeslots;
	} 

	else
	{
		N = atoi(argv[1]);
		B = atoi(argv[2]);
		p = strtod(argv[3], &pEnd);
		strcpy(queueType, argv[4]);
		K = strtod(argv[5], &pEnd);
		strcpy(out, argv[6]);
		T = strtod(argv[7], &pEnd);		
	}



	// read values printed
	 cout<<N<<" "<<B<<" "<<p<<" "<<queueType<<" "<<K<<" "<<out<<" "<<T;

	// initialize srand with distinctive value
	srand(time(NULL));

	double t = 0; 

	while(t < T)
	{
		initialization(packetgen);
		traffic_generation(N, B, packetgen, in_buffer, p, t);
		scheduling(N, B, queueType, in_buffer, out_buffer, K, t);
		transmission(N, B, out_buffer, t);
		t++;
		cout<<t<<endl;
	}

	cout<<"\nAvg. packet delay = "<<total_packet_delay / total_packets_transmitted;
	cout<<"\n Total generated = "<<total_packets_generated;
	cout<<"\n Average KOUQ drop probability = "<<KOUQ_drop_prob_per_slot / (N * T);
	getch();
	return 0;
}