# Philosophers

*This project has been created as part of the 42 curriculum by bchagas-*

## Description

The **Philosophers** project introduces the fundamental concepts of concurrent programming using threads. This project explores how to create and manage threads, utilize mutexes for synchronization, understand critical concepts like data races and deadlocks, and most importantly, learn how to avoid these common pitfalls in multi-threaded applications.

### Project Goals

- Understand the basics of threading and concurrent programming
- Learn how to create and manage multiple threads simultaneously
- Master mutex usage for protecting shared resources
- Identify and prevent data races and deadlock situations

### The Dining Philosophers Problem

This project implements a simulation of the classic **Dining Philosophers Problem**, a fundamental synchronization problem in computer science. In this scenario, a number of philosophers sit at a round table with a bowl of spaghetti in the center. Between each pair of philosophers is a single fork. Each philosopher alternates between eating, sleeping and thinking:

- **Eating**: The philosopher needs two forks (one on their left and one on their right) to eat
- **Sleeping**: After eating, the philosopher rests
- **Thinking**: The philosopher contemplates life

The challenge is to design a solution where philosophers can eat without encountering deadlock (where all philosophers are waiting for a fork) or starvation (where a philosopher never gets to eat).

## Instructions

### Compilation

The project must be compiled using `cc` with the following flags:
```bash
-Wall -Wextra -Werror -pthread
```

The included `Makefile` already compiles the program correctly. Simply run:
```bash
make
```

### Execution

After compilation, run the program with the following arguments:
```bash
./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]
```

#### Arguments Explanation

1. **number_of_philosophers**: The number of philosophers (and forks) at the table
2. **time_to_die**: Time in milliseconds - if a philosopher doesn't start eating within this time after their last meal, they die
3. **time_to_eat**: Time in milliseconds - how long it takes for a philosopher to eat
4. **time_to_sleep**: Time in milliseconds - how long a philosopher sleeps after eating
5. **[number_of_times_each_philosopher_must_eat]** (optional): If specified, the simulation stops when all philosophers have eaten at least this many times. If not specified, the simulation runs until a philosopher dies

### Program Output

The program logs each philosopher's actions with timestamps:
```
[timestamp_in_ms] [philosopher_id] has taken a fork
[timestamp_in_ms] [philosopher_id] is eating
[timestamp_in_ms] [philosopher_id] is sleeping
[timestamp_in_ms] [philosopher_id] is thinking
[timestamp_in_ms] [philosopher_id] died
```

The simulation will result in one of three outcomes:

1. **A philosopher dies**: If the timing parameters make it impossible to keep all philosophers alive
2. **Simulation completes successfully**: If the optional `number_of_times_each_philosopher_must_eat` argument is provided and all philosophers eat the required number of times
3. **Infinite simulation**: If the parameters allow all philosophers to eat indefinitely without dying

## Resources

### Official Documentation

The primary resources for this project were:

- **pthread manual pages**: 
  - `man pthread_create` - Creating threads
  - `man pthread_join` - Waiting for thread termination
  
- **mutex manual pages**:
  - `man pthread_mutex_init` - Initializing mutexes
  - `man pthread_mutex_lock` - Locking mutexes
  - `man pthread_mutex_unlock` - Unlocking mutexes
  - `man pthread_mutex_destroy` - Destroying mutexes

### Additional Learning

- **AI Tools**: Used for clarifying complex threading concepts and synchronization patterns that were not immediately clear from manual pages alone