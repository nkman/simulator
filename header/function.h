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

/*
void split(char *line, char tab){
	char temp[43];
	// memset(temp, 43, 0);
	int i, j=0, k=0;
	for(i=0;i<strlen(line);i++){
		if(temp[k] == tab || temp[k] == '\n'){
			switch(j){
				case 1:
							strcpy(process[total_process].name, temp);
							break;
				case 2:
							process[total_process].arrival_time = atof(temp);
							break;
				case 3:
							process[total_process].burst_time = atof(temp);
							break;
				default:
							break;
			}
			memset(temp, 43, 0);
			total_process++;
			j++;
			k=0;
		}
		printf("%s length %lu\n", temp, strlen(temp));
		temp[strlen(temp)] = line[k];
		k++;
	}
}
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
	total_process++;
	return;
}

static void print_process(){
	int i;
	for(i=0;i<total_process;i++){
		printf("%f\t%f\n", process[i].arrival_time, process[i].burst_time);
	}
}

#endif /* _HEADER_FUNCTION_H */