#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    int process_id;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int waiting_time;
    int turnaround_time;
    int is_completed;
} Process;

int n; // Number of processes

// Function to find the index of the process with the shortest remaining time
int findNextProcess(Process proc[], int current_time) {
    int min_time = INT_MAX;
    int index = -1;
    for (int i = 0; i < n; i++) {
        if (proc[i].arrival_time <= current_time && !proc[i].is_completed) {
            if (proc[i].remaining_time < min_time) {
                min_time = proc[i].remaining_time;
                index = i;
            } else if (proc[i].remaining_time == min_time) {
                if (proc[i].arrival_time < proc[index].arrival_time) {
                    index = i;
                }
            }
        }
    }
    return index;
}

// Function to perform the SRTF scheduling
void srtf(Process proc[]) {
    int current_time = 0;
    int completed = 0;
    int prev = -1;
    int first_execution[100] = {0}; // It helsp to track if the process has started for the first time 

    // Use for loop to initialize remaining times and completion status
    for (int i = 0; i < n; i++) {
        proc[i].remaining_time = proc[i].burst_time;
        proc[i].is_completed = 0;
    }

    // Process execution loop
    while (completed != n) {
        int index = findNextProcess(proc, current_time);

        if (index != -1) {
            // Print only when a process starts for first time and it has the form of current_time, time and process and starts
            if (first_execution[proc[index].process_id] == 0) {
                printf("current_time %d Time %d: Process %d starts\n", current_time, current_time, proc[index].process_id);
                first_execution[proc[index].process_id] = 1;  // From beginning
            }

            proc[index].remaining_time--;

            if (proc[index].remaining_time == 0) {
                proc[index].is_completed = 1;
                completed++;
                proc[index].turnaround_time = current_time + 1 - proc[index].arrival_time;
                proc[index].waiting_time = proc[index].turnaround_time - proc[index].burst_time;

                // the statement will print when the process completes execution
                printf("current_time %d Time %d: Process %d completes\n", current_time + 1, current_time + 1, proc[index].process_id);
            }
            current_time++;
        } else {
            int next_one = INT_MAX;
            //otherwise you another for loop to check the arrival_time and current_time
            for (int i = 0; i < n; i++) {
                if (!proc[i].is_completed && proc[i].arrival_time > current_time) {
                    if (proc[i].arrival_time < next_one) {
                        next_one = proc[i].arrival_time;
                    }
                }
            }
            printf("current_time %d: CPU is idle\n", current_time);
            current_time = next_one;
        }
    }
}

// Function to print the processes and their details
void printProcesses(Process proc[]) {
    printf("\nProcess ID\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n",
               proc[i].process_id, proc[i].arrival_time, proc[i].burst_time,
               proc[i].waiting_time, proc[i].turnaround_time);
    }
}

int main() {
    // Initialize processes with their IDs, arrival times, and burst times
    Process proc[] = {{1, 0, 8}, {2, 1, 4}, {3, 2, 9}, {4, 3, 5}};
    n = sizeof(proc) / sizeof(proc[0]);

    srtf(proc);
    printProcesses(proc);

    return 0;
}
