#ifndef _HEADER_VARIABLE_H
#define _HEADER_VARIABLE_H

struct Process{
	int arrival_time;
	int burst_time;
	int termination_time;
};

typedef struct Process process;
static int is_preemptive = 0;

#endif /* _HEADER_VARIABLE_H */