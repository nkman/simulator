#ifndef _HEADER_VARIABLE_H
#define _HEADER_VARIABLE_H

#define PREEMPTIVE 1
#define NO_PREEMPTIVE 0

/*
* Process Decriptor.
* name - process name [i.e. P1] max 50 characters.
* 0 - FCFS, 1 - SJF, 2 - RR.
*/
struct incoming_process{
	char name[50];
	float arrival_time;
	float burst_time;
	int is_completed[3];
	float termination_time[3];
	float waiting_time[3];
	float turnaround_time[3];
};
typedef struct incoming_process Process;

/*
* Process description.
* max number of process can be 500.
*/
static Process process[500];

/*
* 1 if using PREEMPTIVE.
* 0 otherwise.
*/
static unsigned int is_preemptive = NO_PREEMPTIVE;

/*
* total number of process to consider.
* Zero initially.
*/
static unsigned int total_process = 0;

/*
* Process file, tab separated entries.
* will not consider the lines which starts with "#"
*/
#define file "process.txt"

/*
* structure used in sjf non-preemptive
* to send multiple arguments.
*/
struct _data_{
	int smallest;
	float curr_time;
};
typedef struct _data_ data_sjf_non_preemptive;
#endif /* _HEADER_VARIABLE_H */