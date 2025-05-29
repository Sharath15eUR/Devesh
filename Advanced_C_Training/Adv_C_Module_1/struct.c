#include<stdio.h>
#include<string.h>

#define MAX_TASKS 3
#define MAX_TASK_LEN 100
#define DAYS 7

typedef struct
{
    /* data */
    char dayName[10];
    char tasks[MAX_TASKS][MAX_TASK_LEN];
    int taskCount;
} calendar;


int main(){
    calendar week[DAYS] = {{"Monday"}, {"Tuesday"}, {"Wednesday"}, {"Thursday"},
        {"Friday"}, {"Saturday"}, {"Sunday"}};

    char day[10], task[MAX_TASK_LEN];
    while (1) {
        printf("Enter day dayName (or 'exit'): ");
        scanf("%s", day);
        if (!strcasecmp(day, "exit")) break;

        int i, found = 0;
        for (i = 0; i < DAYS; i++) {
            if (!strcasecmp(day, week[i].dayName)) { found = 1; break; }
        }
        if (!found) { printf("Invalid day.\n"); continue; }

        if (week[i].taskCount >= MAX_TASKS) {
            printf("Task limit reached.\n"); continue;
        }

        getchar(); // clear newline
        printf("Enter task: ");
        fgets(task, MAX_TASK_LEN, stdin);
        task[strcspn(task, "\n")] = 0;
        strcpy(week[i].tasks[week[i].taskCount++], task);
    }

    printf("\n--- Weekly Tasks ---\n");
    for (int i = 0; i < DAYS; i++) {
        printf("%s:\n", week[i].dayName);
        for (int j = 0; j < week[i].taskCount; j++)
            printf("  %d. %s\n", j + 1, week[i].tasks[j]);
        if (week[i].taskCount == 0) printf("  No tasks\n");
    }
    
}
