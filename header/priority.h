#ifndef _HEADER_PRIORITY_H
#define _HEADER_PRIORITY_H

/*Priority*/
void priority_scheduling(void);
int priority_order(float);
void *priority_scheduling_func(void *);

/*
* priority.
*/
void priority_scheduling(){
	printf("Priority Scheduling started...\n");
	int i,j, next;
	float curr_time, total_burst_time=0;
	float elapsed_time = 0.0, waiting_time = 0.0, turnaround_time = 0.0;

	for(i=0; i<total_process; i++)
		total_burst_time += process[i].burst_time;

	int *thread_con = malloc(sizeof(int)*total_process);
	memset(thread_con, sizeof(thread_con), 0);

	pthread_t *thread = malloc(sizeof(pthread_t)*total_process);
	memset(thread, sizeof(thread), 0);

	data_priority_non_preemptive *data = malloc(sizeof(data_priority_non_preemptive)*total_process);
	memset(data, sizeof(data), 0);

	for(curr_time=0; curr_time<total_burst_time;){
		//TODO: define this function.
		next = priority_order(curr_time);
		process[next].is_completed[3] = 1;

		/*ready*/
		process[i].state[3] = 1;
		data[i].smallest = next;
		data[i].curr_time = curr_time;

		//TODO: define this function => priority_scheduling_func.
		thread_con[i] = pthread_create(&thread[i], NULL, &(priority_scheduling_func), &data[i]);
		if(thread_con[i]){
			fprintf(stderr, "Error - pthread_create() return code: %d\n", thread_con[i]);
			exit(EXIT_FAILURE);
		}

		pthread_join(thread[i], NULL);
		curr_time += process[next].burst_time;
		i++;
	}

	/*
	* wait till the completion.
	*/
	// for(j=0;j<i;j++){
	// 	pthread_join(thread[j], NULL);
	// }

	for(j=0;j<total_process;j++){
		waiting_time += process[j].waiting_time[3];
		turnaround_time += process[j].termination_time[3] - process[j].arrival_time;
	}

	waiting_time /= total_process;
	turnaround_time /= total_process;
	printf("Avg turnaround_time is %f and avg waiting_time is %f\n\n\n", turnaround_time, waiting_time);
}

int priority_order(float curr_time){
	int i, *next = malloc(total_process*sizeof(int)), next_size=0;
	int to_return;
	for(i=0;i<total_process;i++){
		if(process[i].is_completed[3] != 1)
			if(process[i].arrival_time <= curr_time){
				next[next_size] = i;
				next_size++;
			}
	}

	if(next_size == 1)
		return next[0];

	to_return = next[0];
	for(i=0;i<next_size;i++){
		if(process[next[i]].priority < process[to_return].priority)
			to_return = next[i];
	}

	return to_return;
}


void *priority_scheduling_func(void *data){
	data_priority_non_preemptive *_data = (struct _data_ *)data;
	int smallest;
	float curr_time, elapsed_time = 0.0, waiting_time = 0.0, turnaround_time = 0.0;

	process[smallest].state[3] = 2;
	smallest = (*_data).smallest;
	curr_time = (*_data).curr_time;

	if(curr_time - process[smallest].arrival_time > 0){
		process[smallest].waiting_time[3] = curr_time - process[smallest].arrival_time;
		waiting_time += process[smallest].waiting_time[3];
	}
	curr_time += process[smallest].burst_time;
	turnaround_time += curr_time - process[smallest].arrival_time;
	process[smallest].termination_time[3] = curr_time;
	process[smallest].is_completed[3] = 1;
	printf("Process %s completed in %f and ended at %f, waited for %f.\n", process[smallest].name, process[smallest].burst_time, process[smallest].termination_time[3], process[smallest].waiting_time[3]);
	process[smallest].state[3] = 4;
}

#endif /* _HEADER_PRIORITY_H */