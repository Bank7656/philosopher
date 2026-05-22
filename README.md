*This project has been created as part of the 42 curriculum by thacharo*

# Philosophers

## Description
The "Philosophers" project is a classic computer science exercise designed to teach the fundamentals of threading a process. It provides hands-on experience with thread synchronization, mutex logic, and monitoring loops.

The project is divided into two distinct architectures:

* **Mandatory program** (`philo`): Focuses heavily on memory sharing and preventing data races.

* **Bonus program** (`philo_bonus`): Shifts the architecture from threads to processes and changes how the shared resources are managed.

### Mutex vs. Semaphore Implementation

| Action / Concept | Mutex (Mandatory) | Semaphore (Bonus) | Description |
| :--- | :--- | :--- | :--- |
| **Initialization** | `pthread_mutex_init()` | `sem_open()` | Creates or initializes the lock. `sem_open` can take an initial value (e.g., the total number of forks), whereas a mutex is strictly binary (locked/unlocked). |
| **Acquire / Lock** | `pthread_mutex_lock()` | `sem_wait()` | Attempts to take the lock. If the mutex is already locked, or if the semaphore value is 0, the thread/process blocks until it becomes available. |
| **Release / Unlock** | `pthread_mutex_unlock()`| `sem_post()` | Releases the lock. For mutexes, it unlocks it. For semaphores, it increments the value, signaling that a resource (fork) is available. |
| **Destruction** | `pthread_mutex_destroy()`| `sem_close()` | Cleans up the resource. `pthread_mutex_destroy` destroys the mutex object. `sem_close` closes the named semaphore for the calling process. |
| **System Cleanup** | *N/A (Handled by destroy)*| `sem_unlink()` | Removes the named semaphore from the system. Required for semaphores to ensure they don't persist in the OS after the program exits. |


## **Instructions**

### Compilation

**Mandatory Part (Threads & Mutexes):** Navigate to the mandatory directory and run make:

``` Bash
cd philo
make
```

**Bonus Part (Processes & Semaphores):** Navigate to the bonus directory and run make:

``` Bash
cd philo_bonus
make
```

### Usage:
Run the executable followed by the required parameters. The syntax is identical for both the mandatory and bonus programs:

``` bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

``` bash
./philo_bonus number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

### Argument Breakdown

* **number_of_philosophers:** The total number of philosophers sitting at the table, which also equals the total number of forks available.
* **time_to_die:** Measured in milliseconds. If a philosopher does not start eating within this amount of time since their last meal (or since the simulation started), they will die.  
* **time_to_eat:** Measured in milliseconds. This is the exact duration it takes for a philosopher to eat their spaghetti. They must hold two forks during this entire time.  
* **time_to_sleep:** Measured in milliseconds. The duration a philosopher spends sleeping after they finish their meal.  
* **[number_of_times_each_philosopher_must_eat] (Optional):** If you provide this argument, the simulation will automatically stop once every single philosopher has eaten this specific number of times. If you do not provide this argument, the simulation will just keep running until a philosopher dies.

### Example Usage:

Run a simulation with 5 philosophers, an 800ms time to die, 200ms to eat, and 200ms to sleep. The simulation runs until someone starves:

``` bash
./philo 5 800 200 200
```



Run a simulation with 4 philosophers, where the simulation stops after everyone has eaten at least 7 times:

``` bash
./philo 4 410 200 200 7
```

---
## **Resources**

* **POSIX Threads (pthreads) Documentation:** The official Linux manual pages for understanding pthread_create, pthread_join, and the lifecycle of threads.

* **Advanced Linux Programming (Chapter 4: Threads):** A comprehensive guide detailing thread synchronization, the dangers of data races, and the implementation of mutexes in C.

* **A Classic Problem - Dining Philosophers:** [Toronto Metropolitan University Lecture](https://www.ee.torontomu.ca/~courses/coe518/Labs/lab4/lisi.edu-dining-Philosopherecture8.pdf)

* **Dining Philosopher Solution using Semaphores:** [GeeksforGeeks Guide](https://www.geeksforgeeks.org/operating-systems/dining-philosopher-problem-using-semaphores/)


## AI Usage Declaration

During the development of this project, Artificial Intelligence tools were utilized to enhance productivity and deepen understanding, strictly adhering to the project's academic guidelines. AI was used for the following specific tasks:

* **Conceptual Brainstorming:** AI was used to explore different structural approaches to the monitoring loop and to clarify the abstract mechanics of data races. The generated ideas were subsequently tested and refined through peer review.

* **Debugging & Logic Review:** When encountering complex synchronization issues, AI assisted in identifying potential flaws in the mutex locking order. The logic was then manually walked through, verified, and rewritten to ensure complete comprehension.

* **Reducing Tedium:** AI tools were leveraged to assist with repetitive tasks and general-purpose prompting, allowing for more focused effort on the core computational thinking and problem-solving required to prevent philosopher starvation.
