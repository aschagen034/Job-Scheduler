/*
    Student Name: Andrew Schagen 
    U ID: U22296650
    c99 compiling used
    
    In this program, the code implements a FIFO(first in, first out) scheduler using dynamically allocated linked lists.
	Each job will be of the type struct job and include the job name, user name, number of CPU's, number of GPU's, memory, 
	time, and priority. The user is asked to enter an operation code where the code then implements a switch statement to 
	call specific functions with each code. A read function is used to take in the job information from the user. The program 
	can add jobs to the scheduler list as well as remove jobs by utilizing the FIFO method. It can list all jobs in the list
	and search jobs by certain criteria as well. Finally, we can call the clear function to clear all jobs from the list and terminate
	the program. In this code, another aspect was added to the add_job function in that it sorts the jobs in order by priority
	from highest to lowest. Essentially, it creates an ordered linked list, and if a new job has the same priority as other jobs,
	the new job will be added as the last one of the same priority.
    
*/
#include <stdio.h>
#include <stdlib.h>
#include "job.h"



#define NAME_LEN 20
#define SIZE_LEN 3


///////////////////
// main function //
///////////////////

int main() {
	char code;
	char job_name[NAME_LEN+1], user_name[NAME_LEN+1];
	int num_cpus, num_gpus, memory, priority;
	double time;

	struct job *scheduler = NULL;

	help();
	printf("\n");

	for (;;) {
		// read operation code
		printf("Enter operation code: ");
		scanf(" %c", &code);
		while(getchar() != '\n') /* skips to end of line */
			;

		// run operation
		switch (code) {
			case 'h':
				help();
				break;
			case 'a':
				read(job_name, user_name, &num_cpus, &num_gpus, &memory, &time, &priority);
				scheduler = add_job(scheduler, job_name, user_name, num_cpus, num_gpus, memory, time, priority);
				break;
			case 'p':
				scheduler = pop_job(scheduler);
				break;
			case 'u':
				read(NULL, user_name, NULL, NULL, NULL, NULL, NULL);
				list_user(scheduler, user_name);
				break;
			case 'j':
				read(NULL, NULL, &num_cpus, &num_gpus, &memory, &time, NULL);
				list_jobs(scheduler, num_cpus, num_gpus, memory, time);
				break;
			case 'l':
				list_all_jobs(scheduler);
				break;
			case 'q':
				scheduler = clear_jobs(scheduler);
				return 0;
			default:
				printf("Illegal operation code!\n");
		}
		printf("\n");
	}
}



