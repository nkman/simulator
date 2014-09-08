#ifndef _HEADER_VARIABLE_H
#define _HEADER_VARIABLE_H

#define PREEMPTIVE 1
#define NO_PREEMPTIVE 0

/*
* Process Decriptor.
* name - process name [i.e. P1] max 50 characters.
* 0 - FCFS, 1 - SJF_NON_PREEMPTIVE, 2 - SJF_PREEMPTIVE, 3 - PRIORITY, 4 - RR.
* New, Ready, Running, Waiting, Terminated.
*/
struct incoming_process{
	char name[50];
	float arrival_time;
	float burst_time;
	int priority;
	int is_completed[5];
	float termination_time[5];
	float waiting_time[5];
	float turnaround_time[5];
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
* 1 if priority
*/
static unsigned int is_priority = 0;
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

/*Same for priority datas*/
typedef data_sjf_non_preemptive data_priority_non_preemptive;
/* Fcfs */
typedef data_sjf_non_preemptive data_fcfs;
#endif /* _HEADER_VARIABLE_H */