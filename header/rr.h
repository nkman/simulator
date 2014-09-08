#ifndef _HEADER_RR_H
#define _HEADER_RR_H
void rr(void);
void *rr_thread(void *);

static float current_time_rr=0.0;
void rr(){
	printf("RR started...\n");
	float total_burst_time, waiting_time = 0.0, turnaround_time = 0.0;
	int i, curr_index, j=0;

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


	for(current_time_rr=0; current_time_rr < total_burst_time;){
		
		data[curr_index].smallest = curr_index;
		data[curr_index].curr_time = current_time_rr;

		thread_con[curr_index] = pthread_create(&thread[curr_index], NULL, &(rr_thread), &data[curr_index]);
		if(thread_con[curr_index]){
			fprintf(stderr, "Error - pthread_create() return code: %d\n", thread_con[curr_index]);
			exit(EXIT_FAILURE);
		}
		pthread_join(thread[curr_index], NULL);

		i = 0;
		while(i<total_process){
			curr_index += 1;
			curr_index %= total_process;
			if(process[curr_index].is_completed[4] == 0)
				break;
			i++;
		}
		// printf("current_time_rr :%f\n", current_time_rr);
		current_time_rr += quantum;
		// j++;
	}

	
	for(j=0;j<total_process;j++){
		waiting_time += process[j].waiting_time[4];
		turnaround_time += process[j].termination_time[4] - process[j].arrival_time;
	}

	waiting_time /= total_process;
	turnaround_time /= total_process;
	printf("Avg turnaround_time is %f and avg waiting_time is %f\n\n\n", turnaround_time, waiting_time);
}

static int k = 0;
void *rr_thread(void *data){
	// printf("k: %d\n", k++);
	int i, curr_index;
	// float current_time_rr;
	data_sjf_non_preemptive *_data = (struct _data_ *)data;

	curr_index = (*_data).smallest;
	// current_time_rr = (*_data).current_time_rr;

	if(process[curr_index].remaining_time <= quantum){
		if(process[curr_index].remaining_time ==0)return ;
		current_time_rr -= quantum;
		current_time_rr += process[curr_index].remaining_time;
		process[curr_index].remaining_time = 0;
		process[curr_index].state[4] = 4;
		process[curr_index].is_completed[4] = 1;
		process[curr_index].turnaround_time[4] = current_time_rr - process[curr_index].arrival_time + quantum;
		process[curr_index].waiting_time[4] = process[curr_index].turnaround_time[4] - process[curr_index].burst_time;
		process[curr_index].termination_time[4] = current_time_rr + quantum;

		printf("Process %s completed in %f and ended at %f, waited for %f.\n", process[curr_index].name, process[curr_index].burst_time, process[curr_index].termination_time[4], process[curr_index].waiting_time[4]);
	}
	else
		process[curr_index].remaining_time -= quantum;
}
#endif /* _HEADER_RR_H */