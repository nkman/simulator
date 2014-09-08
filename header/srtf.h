#ifndef _HEADER_SRTF_H
#define _HEADER_SRTF_H
void srtf(void);
int srtf_shortest(float);
void *srtf_thread(void *);

void srtf(){
	printf("SRTF started...\n");
	float total_burst_time, curr_time = 0.0, waiting_time = 0.0, turnaround_time = 0.0;
	int i, curr_index,j=0;

	for(i=0; i<total_process; i++){
		total_burst_time += process[i].burst_time;
		process[i].remaining_time = process[i].burst_time;
	}

	curr_index = 0;

	int *thread_con = malloc(sizeof(int)*total_process);
	memset(thread_con, sizeof(thread_con), 0);

	pthread_t *thread = malloc(sizeof(pthread_t)*total_process);
	memset(thread, sizeof(thread), 0);

	data_sjf_non_preemptive *data = malloc(sizeof(data_sjf_non_preemptive)*total_process);
	memset(data, sizeof(data), 0);

	for(curr_time=0;curr_time<total_burst_time;curr_time++){
		curr_index = srtf_shortest(curr_time);
		
		data[curr_index].smallest = curr_index;
		data[curr_index].curr_time = curr_time;

		thread_con[curr_index] = pthread_create(&thread[curr_index], NULL, &(srtf_thread), &data[curr_index]);
		if(thread_con[curr_index]){
			fprintf(stderr, "Error - pthread_create() return code: %d\n", thread_con[curr_index]);
			exit(EXIT_FAILURE);
		}
		pthread_join(thread[curr_index], NULL);
		// j++;
	}

	for(j=0;j<total_process;j++){
		waiting_time += process[j].waiting_time[2];
		turnaround_time += process[j].termination_time[2] - process[j].arrival_time;
	}

	waiting_time /= total_process;
	turnaround_time /= total_process;
	printf("Avg turnaround_time is %f and avg waiting_time is %f\n\n\n", turnaround_time, waiting_time);
}

int srtf_shortest(float curr_time){
	int i, min=0,max=0;
	for( i=1;i<total_process;i++){
		if(process[i].remaining_time > process[max].remaining_time)
			max = i;
	}
    min=max;
    // printf("Max :%d\n", max);
	for(i=0;i<total_process;i++){
		if((process[i].remaining_time < process[min].remaining_time) && (process[i].is_completed[2] == 0) && (curr_time >= process[i].arrival_time)){
			min = i;
		}
	}
	// printf("Min :%d\n", min);
	return min;
}

void *srtf_thread(void *data){
	int curr_index;
	float curr_time;
	data_sjf_non_preemptive *_data = (struct _data_ *)data;

	curr_index = (*_data).smallest;
	curr_time = (*_data).curr_time;

	process[curr_index].remaining_time -= 1;
	// printf("index:%d\n", curr_index);

	if(process[curr_index].remaining_time == 0){

		process[curr_index].is_completed[2] = 1;
		process[curr_index].turnaround_time[2] = curr_time + 1 - process[curr_index].arrival_time;
		process[curr_index].waiting_time[2] = process[curr_index].turnaround_time[2] - process[curr_index].burst_time;
		process[curr_index].termination_time[2] = curr_time + 1;

		printf("Process %s completed in %f and ended at %f, waited for %f.\n", process[curr_index].name, process[curr_index].burst_time, process[curr_index].termination_time[2], process[curr_index].waiting_time[2]);
	}
}
#endif /* _HEADER_SRTF_H */