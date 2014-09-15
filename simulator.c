#include "header/headers.h"

int main(){
	char a;
	int i;
	printf("\n");
	printf("\t\tTHE PROJECT HAS BEEN CREATED UNDER THE GUIDANCE OF\n\t\t\t   Prof. P SATEESH KUMAR\n\n\n");
	printf("Enter the Arrival times and burst times of processes in the process.txt");
	scanf("%c", &a);
	get_detail_from_file();
	StableSort();
	
	while(1){
		printf("MENU\n1 FOR FCFS\n2 FOR SJF\n3 FOR PRIOROTY\n4 FOR ROUND ROBIN\n5 FOR SRTF\n6 EXIT\n\n");
		scanf("%d", &i);
		re_initialize();
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
			printf("Enter Quantum Value :");
			scanf("%d", &quantum);
			rr();
			break;
		case 5:
			srtf();
			break;
		case 6:
			printf("\n****Thank You !!***\n\n");
			return 0;
		default:
			printf("Invalid choice\nChoose a valid one ");
	}
}
	return 0;
}