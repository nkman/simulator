#ifndef _HEADER_FUNCTION_H
#define _HEADER_FUNCTION_H

/*
* Defined functions.
*/
void get_detail_from_file(void);
void split(char *, char);
static void print_process(void);
void FCFS(void);

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

		waiting_time += process[i].waiting_time[0];
		waiting_time -= process[i].burst_time;

		turnaround_time += process[i].turnaround_time[0];
		turnaround_time -= process[i].burst_time;
		printf("Process %s completed in %f and ended at %f.\n", process[i].name, process[i].burst_time, elapsed_time);
		i++;
	}
	waiting_time /= total_process;
	turnaround_time /= total_process;
	printf("Avg turnaround_time is %f and avg waiting_time is %f\n", turnaround_time, waiting_time);
}

#endif /* _HEADER_FUNCTION_H */