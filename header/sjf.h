#ifndef _HEADER_SJF_H
#define _HEADER_SJF_H

/*SJF*/
void SJF(void);
int shortest_process(float);
void *sjf_non_parts(void *);

/*
* Sortest Job First
*/
void SJF(){
	printf("Non-Preemptive SJF Scheduling started...\n");
	float curr_time, total_burst_time=0;
	float elapsed_time = 0.0, waiting_time = 0.0, turnaround_time = 0.0;
	int i, smallest, j;
	for(i=0; i<total_process; i++)
		total_burst_time += process[i].burst_time;

	int *thread_con = malloc(sizeof(int)*total_process);
	memset(thread_con, sizeof(thread_con), 0);

	pthread_t *thread = malloc(sizeof(pthread_t)*total_process);
	memset(thread, sizeof(thread), 0);

	data_sjf_non_preemptive *data = malloc(sizeof(data_sjf_non_preemptive)*total_process);
	memset(data, sizeof(data), 0);

	i = 0;
	int join;
	for(curr_time=0; curr_time<total_burst_time;){
		smallest = shortest_process(curr_time);
		process[smallest].is_completed[1] = 1;

		process[smallest].state[1] = 1;
		data[i].smallest = smallest;
		data[i].curr_time = curr_time;

		/*
		* Defining pthreads.
		*/
		thread_con[i] = pthread_create(&thread[i], NULL, &(sjf_non_parts), &data[i]);
		if(thread_con[i]){
			fprintf(stderr, "Error - pthread_create() return code: %d\n", thread_con[i]);
			exit(EXIT_FAILURE);
		}
		curr_time += process[smallest].burst_time;
		/*
		* wait till the completion.
		*/
		pthread_join(thread[i], NULL);
		i++;
	}

	// for(j=0;j<i;j++){
	// 	pthread_join(thread[j], (void **) &join);
	// }

	for(j=0;j<total_process;j++){
		waiting_time += process[j].waiting_time[1];
		turnaround_time += process[j].termination_time[1] - process[j].arrival_time;
	}

	waiting_time /= total_process;
	turnaround_time /= total_process;
	printf("\nAvg turnaround_time is %f and avg waiting_time is %f\n\n", turnaround_time, waiting_time);
}

void *sjf_non_parts(void *data){
	data_sjf_non_preemptive *_data = (struct _data_ *)data;
	int smallest;
	float curr_time, elapsed_time = 0.0, waiting_time = 0.0, turnaround_time = 0.0;

	
	smallest = (*_data).smallest;
	curr_time = (*_data).curr_time;

	process[smallest].state[1] = 2;
	if(curr_time - process[smallest].arrival_time > 0){
		process[smallest].waiting_time[1] = curr_time - process[smallest].arrival_time;
		waiting_time += process[smallest].waiting_time[1];
	}
	curr_time += process[smallest].burst_time;
	turnaround_time += curr_time - process[smallest].arrival_time;
	process[smallest].termination_time[1] = curr_time;
	process[smallest].is_completed[1] = 1;
	// printf("Process %s completed in %f and ended at %f, waited for %f.\n", process[smallest].name, process[smallest].burst_time, process[smallest].termination_time[1], process[smallest].waiting_time[1]);
	printf("Process %s Turnaround time is %f, Waiting time is %f \nTerminated at %f\n",  process[smallest].name, process[smallest].turnaround_time[1], process[smallest].waiting_time[1], process[smallest].termination_time[1]);
	process[smallest].state[1] = 4;
}

int shortest_process(float curr_time){
	int i, *smallest = malloc(total_process*sizeof(int)), smallest_size=0;
	int to_return;
	for(i=0;i<total_process;i++){
		/*
		* Find shortest burst_time in 0 <= arrival_time <= curr_time && is_completed == 0
		*/

		if(process[i].is_completed[1] != 1)
			if(process[i].arrival_time <= curr_time){
				smallest[smallest_size] = i;
				smallest_size++;
			}
	}

	if(smallest_size == 1)
		return smallest[0];

	to_return = smallest[0];
	for(i=0;i<smallest_size;i++){
		if(process[smallest[i]].burst_time < process[to_return].burst_time)
			to_return = smallest[i];
	}

	return to_return;
}

#endif /* _HEADER_SJF_H */