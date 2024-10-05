#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

struct Task {
    string taskId;
    int totalTime;
    int timeLeft;
    Task* nextTask;
};

class TaskScheduler {
public:
    Task* currentTask;

    TaskScheduler() {
        currentTask = nullptr;
    }

    void addTask(Task* newTask) {
        if (currentTask == nullptr) {
            currentTask = newTask;
            newTask->nextTask = newTask;
        } else {
            Task* temp = currentTask;
            while (temp->nextTask != currentTask) {
                temp = temp->nextTask;
            }
            temp->nextTask = newTask;
            newTask->nextTask = currentTask;
        }
    }

    void showTasks() {
        if (currentTask == nullptr) {
            cout << "No tasks in the queue." << endl;
            return;
        }
        Task* temp = currentTask;
        while (true) {
            cout << "Task " << temp->taskId << " has " << temp->timeLeft << " units of time remaining." << endl;
            temp = temp->nextTask;
            if (temp == currentTask) {
                break;
            }
        }
        cout << endl;
    }

    void runTasks(int timeSlice) {
        if (currentTask == nullptr) return;

        while (true) {
            Task* taskInProgress = currentTask;
            bool cycleComplete = false;

            while (true) {
                if (taskInProgress->timeLeft > 0) {
                    cout << "Executing Task " << taskInProgress->taskId << " with " << taskInProgress->timeLeft << " units of time left." << endl;
                    int timeUsed = min(taskInProgress->timeLeft, timeSlice);
                    taskInProgress->timeLeft -= timeUsed;
                }

                taskInProgress = taskInProgress->nextTask;

                if (taskInProgress == currentTask) {
                    cycleComplete = true;
                    break;
                }
            }

            Task* temp = currentTask;
            Task* prevTask = nullptr;

            while (true) {
                if (temp->timeLeft <= 0) {
                    if (prevTask) {
                        prevTask->nextTask = temp->nextTask;
                    } else {
                        if (temp->nextTask == currentTask) {
                            currentTask = nullptr;
                        } else {
                            currentTask = temp->nextTask;
                            Task* lastTask = currentTask;
                            while (lastTask->nextTask != temp) {
                                lastTask = lastTask->nextTask;
                            }
                            lastTask->nextTask = currentTask;
                        }
                    }
                    delete temp;
                    temp = (prevTask) ? prevTask->nextTask : currentTask;
                    continue;
                }
                prevTask = temp;
                temp = temp->nextTask;
                if (temp == currentTask) break;
            }

            if (currentTask != nullptr) {
                showTasks();
            }

            if (currentTask == nullptr) {
                break;
            }

            char addNewTask;
            cout << "Would you like to add a new task? (y/n): ";
            cin >> addNewTask;

            if (addNewTask == 'y' || addNewTask == 'Y') {
                int taskDuration;
                cout << "Enter duration for the new Task: ";
                cin >> taskDuration;
                addTask(new Task{"T" + to_string(rand() % 100 + 1), taskDuration, taskDuration, nullptr});
            }
        }
    }
};

int main() {
    TaskScheduler taskQueue;
    int taskCount;
    cout << "Enter the number of initial tasks: ";
    cin >> taskCount;
    for (int i = 0; i < taskCount; i++) {
        int taskDuration;
        cout << "Enter duration for Task T" << (i + 1) << ": ";
        cin >> taskDuration;
        taskQueue.addTask(new Task{"T" + to_string(i + 1), taskDuration, taskDuration, nullptr});
    }

    int timeSlice;
    cout << "Enter time slice (time quantum): ";
    cin >> timeSlice;

    taskQueue.runTasks(timeSlice);

    cout << "All tasks have been completed." << endl;
    return 0;
}
