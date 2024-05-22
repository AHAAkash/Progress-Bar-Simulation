#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <stdbool.h>

const int BAR_LENGTH = 50;
const int MAX_TASKS = 5;

typedef struct {
    int id;
    int progress;
    int step;
} Task;

void print_bar(Task task);
void clear_screen();

int main() {
    Task tasks[MAX_TASKS];
    srand(time(NULL));

    for (int i = 0; i < MAX_TASKS; i++) {
        tasks[i].id = i + 1;
        tasks[i].progress = 0;
        tasks[i].step = rand() % 5 + 1; // Random step value between 1 and 5
    }

    bool task_incomplete = true;
    while (task_incomplete) {
        task_incomplete = false;
        clear_screen();

        for (int i = 0; i < MAX_TASKS; i++) {
            tasks[i].progress += tasks[i].step;
            if (tasks[i].progress > 100) {
                tasks[i].progress = 100;
            } else if (tasks[i].progress < 100) {
                task_incomplete = true;
            }
            print_bar(tasks[i]);
        }
        sleep(1);
    }

    printf("All tasks completed!\n");
    return 0;
}

// Clear screen
void clear_screen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void print_bar(Task task) {
    int bars_to_show = (task.progress * BAR_LENGTH) / 100;
    printf("\nTask %d: [", task.id);
    for (int i = 0; i < BAR_LENGTH; i++) {
        if (i < bars_to_show) {
            printf("=");
        } else {
            printf(" ");
        }
    }
    printf("] %d%%\n", task.progress);
}
