
# Philosophers

A multithreaded simulation of the **Dining Philosophers Problem**,The project explores thread management, mutexes, synchronization, and the challenges of sharing resources safely between concurrent tasks.

## Overview

Several philosophers sit around a circular table. Each philosopher alternates between **thinking**, **eating**, and **sleeping**.

- There is one fork between each pair of neighboring philosophers.
- A philosopher needs **two forks** to eat.
- After eating, a philosopher sleeps and then starts thinking again.
- The simulation ends when a philosopher dies or, if a meal limit is provided, when all philosophers have eaten the required number of times.

The challenge is to coordinate access to the forks while avoiding data races and deadlocks.

## Getting Started

### Requirements

- A C compiler (`cc`, `gcc`, or `clang`)
- `make`
- A Unix-like system with POSIX threads

### Build

```bash
make
```

This generates the `philo` executable.

### Run

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

All time values are in **milliseconds (ms)**.

| Argument | Description |
| --- | --- |
| `number_of_philosophers` | Number of philosophers (and forks) at the table. |
| `time_to_die` | Maximum time a philosopher can go without starting another meal. |
| `time_to_eat` | Time spent eating. |
| `time_to_sleep` | Time spent sleeping. |
| `number_of_times_each_philosopher_must_eat` | Optional minimum meal count for every philosopher before the simulation stops. |

**Examples**

```bash
./philo 5 800 200 200
./philo 5 800 200 200 7
./philo 1 800 200 200
```

## Example Output

```text
0 1 is thinking
1 1 has taken a fork
1 1 has taken a fork
1 1 is eating
201 1 is sleeping
201 2 has taken a fork
201 2 has taken a fork
201 2 is eating
```

Each log line follows this format:

```text
<timestamp_in_ms> <philosopher_id> <action>
```

Possible actions include `has taken a fork`, `is eating`, `is sleeping`, `is thinking`, and `died`. The exact order of messages varies because threads run concurrently.

## How It Works

1. **Threads:** Each philosopher runs independently in a thread and repeats the think/eat/sleep cycle.
2. **Fork mutexes:** Each fork is protected by a mutex, so only one philosopher can hold it at a time.
3. **Deadlock prevention:** Philosophers use a coordinated fork-acquisition strategy instead of all locking forks in the same order.
4. **Monitoring:** A monitoring routine checks when each philosopher last ate and detects starvation.
5. **Synchronized output:** Shared state and log messages are protected to prevent data races and interleaved output.

### Special Case: One Philosopher

With only one philosopher, there is only one fork. The philosopher cannot obtain two forks, so they cannot eat and will eventually die when `time_to_die` is reached.

## Makefile Commands

| Command | Description |
| --- | --- |
| `make` | Build the executable. |
| `make clean` | Remove object files. |
| `make fclean` | Remove object files and the executable. |
| `make re` | Rebuild the project from scratch. |

## What I Learned

- Creating and joining POSIX threads with `pthread_create` and `pthread_join`
- Protecting shared resources with `pthread_mutex_lock` and `pthread_mutex_unlock`
- Understanding race conditions, deadlocks, and starvation
- Coordinating worker threads with a monitoring routine
- Handling timing and cleanup in concurrent C programs

## Notes

Thread scheduling depends on the operating system. Small differences in timestamps and message order are normal, especially under heavy system load.

---
