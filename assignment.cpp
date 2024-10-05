#include <iostream>
using namespace std;

struct Process {
    int processId;
    int executionTime;
    int remainingTime;
    Process* next;
};

class CircularLinkedList {
public:
    Process* head;

    CircularLinkedList() {
        head = nullptr;
    }

    void insertProcess(Process* newProcess) {
        if (head == nullptr) {
            head = newProcess;
            newProcess->next = newProcess;
        } else {
            Process* temp = head;
            while (temp->next != head) {
                temp = temp->next;
            }
            temp->next = newProcess;
            newProcess->next = head;
        }
    }

    void displayProcesses() {
        if (head == nullptr) {
            cout << "No processes remaining." << endl;
            return;
        }
        Process* temp = head;
        while (true) {
            cout << "Process " << temp->processId << " has remaining time: " << temp->remainingTime << endl;
            temp = temp->next;
            if (temp == head) {
                break;
            }
        }
        cout << endl;
    }

    void scheduleProcesses(int timeQuantum) {
        if (head == nullptr) return;

        while (true) {
            Process* currentProcess = head;
            bool completed_a_cycle = false;
            int processesFinishedThisCycle = 0;

            while (true) {
                if (currentProcess->remainingTime > 0) {
                    cout << "Running Process " << currentProcess->processId << " with remaining time: " << currentProcess->remainingTime << endl;
                    int timeToRun = min(currentProcess->remainingTime, timeQuantum);
                    currentProcess->remainingTime -= timeToRun;

                    if (currentProcess->remainingTime <= 0) {
                        cout << "Process " << currentProcess->processId << " has finished." << endl;
                        processesFinishedThisCycle++;
                    }
                }
                currentProcess = currentProcess->next;
                if (currentProcess == head) {
                    completed_a_cycle = true;
                    break;
                }
            }

            Process* temp = head;
            Process* prev = nullptr;

            while (true) {
                if (temp->remainingTime <= 0) {
                    if (prev) {
                        prev->next = temp->next;
                    } else {
                        if (temp->next == head) {
                            head = nullptr;
                        } else {
                            head = temp->next;
                            Process* last = head;
                            while (last->next != temp) {
                                last = last->next;
                            }
                            last->next = head;
                        }
                    }
                    delete temp;
                    temp = (prev) ? prev->next : head;
                    continue;
                }
                prev = temp;
                temp = temp->next;
                if (temp == head) break;
            }

            if (head != nullptr) {
                displayProcesses();
            }

            if (head == nullptr) {
                break;
            }
        }
    }
};

int main() {
    CircularLinkedList processList;
    int numberOfProcesses;
    cout << "Enter the number of processes: ";
    cin >> numberOfProcesses;
    for (int i = 0; i < numberOfProcesses; i++) {
        int executionTime;
        cout << "Enter execution time for Process " << (i + 1) << ": ";
        cin >> executionTime;
        processList.insertProcess(new Process{i + 1, executionTime, executionTime, nullptr});
    }
    int timeQuantum;
    cout << "Enter time quantum: ";
    cin >> timeQuantum;
    processList.scheduleProcesses(timeQuantum);
    return 0;
}
