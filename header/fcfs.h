#ifndef _HEADER_FCFS_H
#define _HEADER_FCFS_H

void FCFS(void);
void *fcfs_thread(void *);

void FCFS(){
	printf("First Come First Serve Scheduling started...\n");
	int i=0, j;
	float curr_time = 0.0, total_burst_time, waiting_time = 0.0, turnaround_time = 0.0;

	int *thread_con = malloc(sizeof(int)*total_process);
	memset(thread_con, sizeof(thread_con), 0);

	pthread_t *thread = malloc(sizeof(pthread_t)*total_process);
	memset(thread, sizeof(thread), 0);


	data_fcfs *data = malloc(sizeof(data_fcfs)*total_process);
	memset(data, sizeof(data), 0);

	for(i=0; i<total_process; i++)
		total_burst_time += process[i].burst_time;

	i=0;
	for(curr_time=0;curr_time<total_burst_time;){

		data[i].smallest = i;
		data[i].curr_time = curr_time;

		thread_con[i] = pthread_create(&thread[i], NULL, &(fcfs_thread), &data[i]);
		if(thread_con[i]){
			fprintf(stderr, "Error - pthread_create() return code: %d\n", thread_con[i]);
			exit(EXIT_FAILURE);
		}

		pthread_join(thread[i], NULL);
		curr_time += process[i].burst_time;
		i++;
	}

	for(j=0;j<total_process;j++){
		waiting_time += process[j].waiting_time[0];
		turnaround_time += process[j].termination_time[0] - process[j].arrival_time;
	}

	waiting_time /= total_process;
	turnaround_time /= total_process;
	printf("Avg turnaround_time is %f and avg waiting_time is %f\n\n\n", turnaround_time, waiting_time);
}

void *fcfs_thread(void *data){
	data_priority_non_preemptive *_data = (struct _data_ *)data;
	int i;
	float curr_time;

	i = (*_data).smallest;
	curr_time = (*_data).curr_time;

	if(curr_time - process[i].arrival_time > 0){
		process[i].waiting_time[0] = curr_time - process[i].arrival_time;
	}
	curr_time += process[i].burst_time;
	process[i].is_completed[0] = 1;
	
	process[i].termination_time[0] = curr_time;
	printf("Process %s completed in %f and ended at %f, waited for %f.\n", process[i].name, process[i].burst_time, process[i].termination_time[0], process[i].waiting_time[0]);
}

#endif /* _HEADER_FCFS_H */