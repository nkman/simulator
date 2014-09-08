#ifndef _HEADER_SORT_H
#define _HEADER_SORT_H

void StableSort(){ 
	int i, j;
	for(i=1;i<total_process;i++){
		for(j=1;j<total_process-i+1;j++){
			if(process[j-1].arrival_time>process[j].arrival_time){
			Process temp = process[j];
			process[j]=process[j-1];
			process[j-1]=temp;  
			}
		}
	}
}

#endif /* _HEADER_SORT_H */