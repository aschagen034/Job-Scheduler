#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "job.h"

//////////////////////////
// function definitions //
//////////////////////////

void help() {
	printf("List of operation codes:\n");
	printf("\t'h' for help;\n");
	printf("\t'a' for adding a job to the scheduler;\n");
	printf("\t'p' for removing a job from the scheduler;\n");
	printf("\t'u' for searching jobs per user;\n");
	printf("\t'j' for searching jobs per capacity;\n");
	printf("\t'l' for listing all jobs;\n");
	printf("\t'q' for quit.\n");
}

void read(char *job_name, char *user_name, int *num_cpus, int *num_gpus, int *memory, double *time, int *priority) {
	if(job_name != NULL) {
		printf("Enter the name of the job: ");
		scanf("%s", job_name);
	}
	if(user_name != NULL) {
		printf("Enter the name of the user: ");
		scanf("%s", user_name);
	}
	if(num_cpus != NULL) {
		printf("Enter the number of CPUs: ");
		scanf("%d", num_cpus);
	}
	if(num_gpus != NULL) {
		printf("Enter the number of GPUs: ");
		scanf("%d", num_gpus);
	}
	if(memory != NULL) {
		printf("Enter the amount of memory: ");
		scanf("%d", memory);
	}
	if(time != NULL) {
		printf("Enter the amount of time: ");
		scanf("%lf", time);
	}
	if(priority != NULL) {
		printf("Enter the priority: ");
		scanf("%d", priority);
	}
}


//Recieves information and adds new job to the scheduler linked list.
struct job * add_job(struct job *scheduler, char *job_name, char *user_name, int num_cpus, int num_gpus, int memory, double time, int priority) {

	struct job *cur, *prev, *new_job;
	

	//allocate memory for new_job node
	new_job = malloc(sizeof(struct job));
	new_job->next = NULL;
    // check if allocation was successful
    if (new_job == NULL) {
        printf("Memory allocation failed.\n");
        return scheduler;
    }

	strcpy(new_job->job_name, job_name);
	strcpy(new_job->user_name, user_name);
	new_job->num_cpus = num_cpus;
	new_job->num_gpus = num_gpus;
	new_job->memory = memory;
    new_job->time = time;
    new_job->priority = priority;


	for(cur = scheduler, prev = NULL; cur != NULL && new_job->priority <= cur->priority; prev = cur, cur = cur->next);
	/*Loop iterates through scheduler list. When the new priority is the largest it will add node to beginning of list.
	since prev will be NULL. Then, if priority is the smallest cur will iterate until it is NULL and add to end of list.*/

	if(prev == NULL){
		//When prev is NULL then new job is added to beginning of the list
		//Make the new node's next point to the first node
		new_job->next = cur;
		return new_job;
	}
	else if(cur == NULL){
		//When cur is NULL then new job is added to end of the list
		//Make last node point to new last node
		prev->next = new_job;
		return scheduler;
	}
	else if(cur->priority < new_job->priority){
		//This case new job is added between two nodes, with its previous being of the same priority
		//Cur will point one past the last node of the same priority, which we can then use prev to point to the new job
		new_job->next = cur;
		prev->next = new_job;
		return scheduler;
	}
   
	
	return scheduler;
}

//Prints the information of the job to removed and then removes it by using the free function. Removes the first function in scheduler list.
struct job *pop_job(struct job *scheduler) {

    if (scheduler == NULL) {
        return scheduler;
    }
	//p points to first node, move scheduler to next node
    struct job* p = scheduler;
    scheduler = scheduler->next;
    printf("|----------------------|----------------------|------|------|------|--------|----------|\n");
    printf("| Job name             | User name            | CPUs | GPUs | Mem. | Time   | Priority |\n");
    printf("|----------------------|----------------------|------|------|------|--------|----------|\n");
    printf("| %-20s | %-20s | %4d | %4d | %4d | %6.2f | %8d |\n", p->job_name, p->user_name, p->num_cpus, p->num_gpus, p->memory, p->time, p->priority);
    printf("|----------------------|----------------------|------|------|------|--------|----------|\n");
    free(p);
    return scheduler;
}

//Recieves list and user name, prints out all jobs from specified user, if no user found function does nothing
void list_user(struct job *scheduler, char *user_name) {
    struct job *p = scheduler;
	int found = 0;
    
    // Print header only if the user is found
    while (p != NULL) {
        if (strcmp(p->user_name, user_name) == 0) {
			if(found == 0){
            printf("|----------------------|----------------------|------|------|------|--------|----------|\n");
            printf("| Job name             | User name            | CPUs | GPUs | Mem. | Time   | Priority |\n");
            printf("|----------------------|----------------------|------|------|------|--------|----------|\n");
            found = 1;
        }
		printf("| %-20s | %-20s | %4d | %4d | %4d | %6.2f | %8d |\n", p->job_name, p->user_name, p->num_cpus, p->num_gpus, p->memory, p->time, p->priority);
        printf("|----------------------|----------------------|------|------|------|--------|----------|\n");
        
    }
	//p points to next node
	p = p->next;
	}

}

//Receives list and specified criteria for jobs. If jobs are found that match the criteria it lists them out, otherwise nothing is printed
void list_jobs(struct job *scheduler, int num_cpus, int num_gpus, int memory, double time) {
    struct job *p = scheduler;
    int found = 0;

    while (p != NULL) {
        if (p->num_cpus == num_cpus && p->num_gpus == num_gpus && p->memory == memory && p->time == time) {
            if (found == 0) {
                printf("|----------------------|----------------------|------|------|------|--------|----------|\n");
                printf("| Job name             | User name            | CPUs | GPUs | Mem. | Time   | Priority |\n");
                printf("|----------------------|----------------------|------|------|------|--------|----------|\n");
                found = 1;
            }
            printf("| %-20s | %-20s | %4d | %4d | %4d | %6.2f | %8d |\n", p->job_name, p->user_name, p->num_cpus, p->num_gpus, p->memory, p->time, p->priority);
            printf("|----------------------|----------------------|------|------|------|--------|----------|\n");
        }
		//Moves p to next node
        p = p->next;
    }

}

//Recieves scheduler list and prints out all jobs. If empty, nothing is printed
void list_all_jobs(struct job *scheduler) {
	struct job *p = scheduler;
	int found = 0;
	
	//If p is NULL, then the program does not do anything
	while(p != NULL)
	{

	if(found == 0){
		
	printf("|----------------------|----------------------|------|------|------|--------|----------|\n");
	printf("| Job name             | User name            | CPUs | GPUs | Mem. | Time   | Priority |\n");
	printf("|----------------------|----------------------|------|------|------|--------|----------|\n");
	found = 1;
	}
	printf("| %-20s | %-20s | %4d | %4d | %4d | %6.2f | %8d |\n", p->job_name, p->user_name, p->num_cpus, p->num_gpus, p->memory, p->time, p->priority);
	printf("|----------------------|----------------------|------|------|------|--------|----------|\n");
	//Moves to next node
	p = p->next;
	
	}
}

//Clears all jobs in the scheduler linked list
struct job * clear_jobs(struct job *scheduler) 
{

	struct job *p;

	while(scheduler != NULL)
	{
		p = scheduler;
		scheduler = scheduler->next;
		if(p!= NULL)
			free(p);
	}
	return NULL;

}