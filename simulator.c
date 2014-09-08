#include "header/headers.h"

int main(){
	char a;
	int i;
	printf("Enter the Arrival times and burst times of processes in the process.txt\n");
	scanf("%c", &a);
	get_detail_from_file();
	StableSort();
	
	while(1){
		printf("MENU\n1 FOR FCFS\n2 FOR SJF\n3 FOR PRIOROTY\n4 FOR ROUND ROBIN\n5 FOR SRTF\n6 EXIT\n\n");
		scanf("%d", &i);
	switch(i){
		case 1:
			FCFS();
			break;
		case 2:
			SJF();
			break;
		case 3:
			priority_scheduling();
			break;
		case 4:
			rr();
			break;
		case 5:
			srtf();
			break;
		case 6:
			return 0;
		default:
			printf("Invalid choice\nChoose a valid one ");
	}
}
	return 0;
}