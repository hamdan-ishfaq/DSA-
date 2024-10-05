# DSA-
Task 1: Process Scheduler

### Approach:
A circular linked list is used to manage processes. Each process runs for a set time (time quantum) before switching to the next.

### Assumptions:
User inputs valid process execution times and time quantum.

### Challenges Faced:
Managing memory in the linked list and removing completed processes without disrupting the cycle.


Task 2: Task Scheduler

### Approach:
Similar to Task 1 but for tasks. New tasks can be added while others are running, managed with a circular linked list.

### Assumptions:
User provides valid task durations and time quantum.

### Challenges Faced:
Dynamically adding tasks and keeping the list organized without breaking the task flow.


Task 3: Large Number Primality Test

### Approach:
A large number is stored as segments in a linked list. The number’s primality is checked using prime numbers up to its square root.

### Assumptions:
The number is divided into segments and stored correctly in the list.

### Challenges Faced:
Main issue was storing the sqrt of the original number in order to generate prime numbers up to that for checking the divisibility.
