#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int process_id;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int waiting_time;
    int turnaround_time;
} Process;

// Function to calculate waiting times and execution order for all processes
void calculateWaitingTimeAndExecutionOrder(Process proc[], int n, int quantum) {
    int remaining_time[n];  // Array to track remaining of the burst time
    //Use for loop to see the remaining of the burst time
    for (int i = 0; i < n; i++) {
        remaining_time[i] = proc[i].burst_time;
    }

    int current_time = 0;  // Keeps track of the current execution time
    int completed = 0;  // Number of completed processes
    int execution_order[1000];  // Store the execution of the sequence
    int exe_index = 0;  // Index for execution sequence storage

   
    //Use the while to keep the traversing untill all processes are completed
    while (completed < n) {
        int done = 1;  // Check if all the processes are done
    //use the for loop to check the process
        for (int i = 0; i < n; i++) {
            if (remaining_time[i] > 0) {
                done = 0;  // At least one process is still remaining
                
                // Store the execution order
                execution_order[exe_index++] = proc[i].process_id;
                
                if (remaining_time[i] > quantum) {
                    current_time += quantum;
                    remaining_time[i] -= quantum;
                } else {
                    current_time += remaining_time[i];
                    proc[i].waiting_time = current_time - proc[i].arrival_time - proc[i].burst_time;
                    remaining_time[i] = 0;
                    completed++;
                }
            }
        }
        //if finised finished the loop
        if (done == 1) break;

    }
        

    // Print the execution order
    printf("Execution Order: ");
    //use for loop to print the execution order
    for (int i = 0; i < exe_index; i++) {
        printf("P%d ", execution_order[i]);
    }
    printf("\n");
}

// Function to calculate turnaround times for all processes
void calculateTurnaroundTime(Process proc[], int n) {
    for (int i = 0; i < n; i++) {
        proc[i].turnaround_time = proc[i].waiting_time + proc[i].burst_time;
    }
}

void roundRobin(Process proc[], int n, int quantum) {
    calculateWaitingTimeAndExecutionOrder(proc, n, quantum);
    calculateTurnaroundTime(proc, n);
}
//Help us to print the processes
void printProcesses(Process proc[], int n) {
    printf("Process ID\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n",
               proc[i].process_id, proc[i].arrival_time, proc[i].burst_time,
               proc[i].waiting_time, proc[i].turnaround_time);
    }
}

int main() {
    Process proc[] = {{1, 0, 24}, {2, 0, 3}, {3, 0, 3}};
    int n = sizeof(proc) / sizeof(proc[0]); 
    int quantum = 4; 

    roundRobin(proc, n, quantum);
    printProcesses(proc, n);

    return 0;
}

