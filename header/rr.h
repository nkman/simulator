#ifndef _HEADER_RR_H
#define _HEADER_RR_H
void rr(void);

void rr(){
	printf("RR started...\n");
	float total_burst_time, curr_time = 0.0, waiting_time = 0.0, turnaround_time = 0.0;
	int i, curr_index;

	for(i=0; i<total_process; i++){
		total_burst_time += process[i].burst_time;
		process[i].remaining_time = process[i].burst_time;
	}

	curr_index = 0;

	for(curr_time=0; curr_time<total_burst_time;curr_time+=quantum){
		if(process[curr_index].remaining_time <= quantum){
			curr_time -= quantum;
			curr_time += process[curr_index].remaining_time;
			process[curr_index].remaining_time = 0;
			process[curr_index].state[4] = 4;
			process[curr_index].is_completed[4] = 1;
			process[curr_index].turnaround_time[4] = curr_time - process[curr_index].arrival_time + quantum;
			process[curr_index].waiting_time[4] = process[curr_index].turnaround_time[4] - process[curr_index].burst_time;
			process[curr_index].termination_time[4] = curr_time + quantum;

			printf("Process %s completed in %f and ended at %f, waited for %f.\n", process[curr_index].name, process[curr_index].burst_time, process[curr_index].termination_time[4], process[curr_index].waiting_time[4]);
		}
		else
			process[curr_index].remaining_time -= quantum;

		i = 0;
		while(i<total_process){
			curr_index += 1;
			curr_index %= total_process;
			if(process[curr_index].is_completed[4] == 0)
				break;
			i++;
		}
	}

	int j;
	for(j=0;j<total_process;j++){
		waiting_time += process[j].waiting_time[4];
		turnaround_time += process[j].termination_time[4] - process[j].arrival_time;
	}

	waiting_time /= total_process;
	turnaround_time /= total_process;
	printf("Avg turnaround_time is %f and avg waiting_time is %f\n\n\n", turnaround_time, waiting_time);
}
#endif /* _HEADER_RR_H */