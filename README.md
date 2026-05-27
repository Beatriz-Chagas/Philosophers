# Philosophers
# *This project has been created as part of the 42 curriculum by <login>.*

# Philosophers

## Description

`Philosophers` is a concurrency and synchronization project from the 42 curriculum based on the classical Dining Philosophers Problem.

The objective of the project is to simulate multiple philosophers sitting around a table while sharing limited resources (forks). Each philosopher alternates between eating, sleeping, and thinking.

To eat, a philosopher must hold two forks simultaneously. Since forks are shared between neighboring philosophers, the project focuses on thread synchronization, mutex handling, deadlock prevention, race condition avoidance, and precise time management.

The project is implemented in C using POSIX threads (`pthread`) and mutexes.

---

## Project Flow

1. `main()` calls `parse_args()` to validate and read the parameters.
2. `main()` calls `init_rules()` to configure mutexes, simulation start time, and forks.
3. `main()` calls `init_philos()` to allocate and initialize each philosopher.
4. `main()` creates:
   - one `philo_routine` thread per philosopher
   - one `monitor_routine` thread
5. Each `philo_routine` follows this cycle:
   - attempts `take_forks()` using ordered mutex locking
   - executes `eat_sleep()` after acquiring both forks
   - releases forks with `put_forks()`
   - prints `is thinking`
6. `monitor_routine` continuously checks:
   - whether a philosopher exceeded `time_die`
   - whether all philosophers reached `must_eat` (when defined)
7. When `dead` is set:
   - philosopher routines stop during the next `simulation_finished()` check
8. `main()` joins all threads and performs `cleanup()`.

---

## Features

- POSIX thread-based simulation
- Mutex-protected shared resources
- Deadlock prevention strategy
- Centralized monitoring thread
- Precise timestamped logging
- Optional meal limit (`must_eat`)
- Proper cleanup of memory and mutexes

---

## Program Arguments

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]