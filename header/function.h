#ifndef _HEADER_FUNCTION_H
#define _HEADER_FUNCTION_H

/*
* Defined functions.
*/
void get_detail_from_file(void);
void split(char *, char);
static void print_process(void);

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
	/* line = name. */
	strcpy(process[total_process].name, line);

	line = strtok(NULL, delim);
	/* line = arrival_time. */
	process[total_process].arrival_time = atof(line);

	line = strtok(NULL, delim);
	/* line = burst_time. */
	process[total_process].burst_time = atof(line);

	line = strtok(NULL, delim);
	/* line = priority. */
	process[total_process].priority = atoi(line);

	memset(process[total_process].is_completed, 2, 0);
	total_process++;
	return;
}

static void print_process(){
	int i;
	for(i=0;i<total_process;i++){
		printf("%f\t%f\t%d\n", process[i].arrival_time, process[i].burst_time, process[i].priority);
	}
}

#endif /* _HEADER_FUNCTION_H */