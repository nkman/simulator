#ifndef _HEADER_FUNCTION_H
#define _HEADER_FUNCTION_H

/*
* Defined functions.
*/
void get_detail_from_file(void);
void split(char *, char);
static void print_process(void);
void FCFS(void);
void SJF(void);
int shortest_process(float);

/*
* Read from file.
*/
void get_detail_from_file(){
	FILE *process_file;
	char line[129];
	process_file = fopen(file, "r");
	if(process_file == NULL){
		printf("Error opening file.\n");
		return;
	}

	while(fgets(line, sizeof line, process_file) != NULL){
		if(line[0] != '#'){
			split(line, '\t');
		}
	}
}

/*
* split and save in process.
*/
void split(char *line, char tab){
	char delim[2];
	delim[0] = tab;
	delim[1] = '\n';
	line = strtok(line, delim);
	strcpy(process[total_process].name, line);
	line = strtok(NULL, delim);
	process[total_process].arrival_time = atof(line);
	line = strtok(NULL, delim);
	process[total_process].burst_time = atof(line);
	memset(process[total_process].is_completed, 2, 0);
	total_process++;
	return;
}

static void print_process(){
	int i;
	for(i=0;i<total_process;i++){
		printf("%f\t%f\n", process[i].arrival_time, process[i].burst_time);
	}
}

/*
* First Come First Serve Algo.
*/
void FCFS(){
	printf("First Come First Serve scheduling started...\n");
	int i=0;
	float elapsed_time = 0.0, waiting_time = 0.0, turnaround_time = 0.0;
	while(i<total_process){
		elapsed_time += process[i].burst_time;
		process[i].termination_time[0] = elapsed_time;
		process[i].is_completed[0] = 1;
		process[i].turnaround_time[0] = process[i].termination_time[0] - process[i].arrival_time;
		if(elapsed_time - process[i].arrival_time > 0)
			process[i].waiting_time[0] = elapsed_time - process[i].arrival_time;
		else
			process[i].waiting_time[0] = 0;

		waiting_time += process[i].waiting_time[0] - process[i].burst_time;
		// waiting_time -= process[i].burst_time;

		turnaround_time += process[i].turnaround_time[0] - process[i].burst_time;
		// turnaround_time -= process[i].burst_time;
		printf("Process %s completed in %f and ended at %f.\n", process[i].name, process[i].burst_time, elapsed_time);
		i++;
	}
	waiting_time /= total_process;
	turnaround_time /= total_process;
	printf("Avg turnaround_time is %f and avg waiting_time is %f\n\n\n", turnaround_time, waiting_time);
}

/*
* Sortest Job First
*/
void SJF(){
	printf("Non-Preemptive SJF...\n");
	float curr_time, total_burst_time=0;
	float elapsed_time = 0.0, waiting_time = 0.0, turnaround_time = 0.0;
	int i, smallest;
	for(i=0; i<total_process; i++)
		total_burst_time += process[i].burst_time;

	

	for(curr_time=0; curr_time<total_burst_time;){
		smallest = shortest_process(curr_time);

		if(curr_time - process[smallest].arrival_time > 0){
			process[smallest].waiting_time[1] = curr_time - process[smallest].arrival_time;
			waiting_time += process[smallest].waiting_time[1];
		}
		curr_time += process[smallest].burst_time;
		turnaround_time += curr_time - process[smallest].arrival_time;
		process[smallest].termination_time[1] = curr_time;
		process[smallest].is_completed[1] = 1;
		printf("Process %s completed in %f and ended at %f, waited for %f.\n", process[smallest].name, process[smallest].burst_time, process[smallest].termination_time[1], process[smallest].waiting_time[1]);

	}

	waiting_time /= total_process;
	turnaround_time /= total_process;
	printf("Avg turnaround_time is %f and avg waiting_time is %f\n\n\n", turnaround_time, waiting_time);

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

#endif /* _HEADER_FUNCTION_H */