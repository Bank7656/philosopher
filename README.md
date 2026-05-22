*This project has been created as part of the 42 curriculum by thacharo*

**Description**
* The "Philosophers" project is a classic computer science exercise designed to teach the fundamentals of threading a process.
* This project is an excellent way to get hands-on experience with thread synchronization, mutex logic, and monitoring loops.

The mandatory program `philo` focuses heavily on **memory sharing and preventing data races**.

The bonus program `philo_bonus` shifts the architecture **from threads to processes and changes how the shared resources are managed**.

**Comparing the specific mutex and semaphore commands**

| Action / Concept | Mutex (Mandatory) | Semaphore (Bonus) | Description |
| :--- | :--- | :--- | :--- |
| **Initialization** | `pthread_mutex_init()` | `sem_open()` | Creates or initializes the lock. `sem_open` can take an initial value (e.g., the total number of forks), whereas a mutex is strictly binary (locked/unlocked). |
| **Acquire / Lock** | `pthread_mutex_lock()` | `sem_wait()` | Attempts to take the lock. If the mutex is already locked, or if the semaphore value is 0, the thread/process blocks until it becomes available. |
| **Release / Unlock** | `pthread_mutex_unlock()`| `sem_post()` | Releases the lock. For mutexes, it unlocks it. For semaphores, it increments the value, signaling that a resource (fork) is available. |
| **Destruction** | `pthread_mutex_destroy()`| `sem_close()` | Cleans up the resource. `pthread_mutex_destroy` destroys the mutex object. `sem_close` closes the named semaphore for the calling process. |
| **System Cleanup** | *N/A (Handled by destroy)*| `sem_unlink()` | Removes the named semaphore from the system. Required for semaphores to ensure they don't persist in the OS after the program exits. |

---

**Instructions**

Compile the Mandatory Part (Threads & Mutexes):
Navigate to the mandatory directory and run make:

``` Bash
cd philo
make
```

Compile the Bonus Part (Processes & Semaphores):
Navigate to the bonus directory and run make:

``` Bash
cd philo_bonus
make
```

Usage:

``` bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

``` bash
./philo_bonus number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

* **number_of_philosophers:** The total number of philosophers sitting at the table, which also equals the total number of forks available.
* **time_to_die:** Measured in milliseconds. If a philosopher does not start eating within this amount of time since their last meal (or since the simulation started), they will die.  
* **time_to_eat:** Measured in milliseconds. This is the exact duration it takes for a philosopher to eat their spaghetti. They must hold two forks during this entire time.  
* **time_to_sleep:** Measured in milliseconds. The duration a philosopher spends sleeping after they finish their meal.  
* **[number_of_times_each_philosopher_must_eat] (Optional):** If you provide this argument, the simulation will automatically stop once every single philosopher has eaten this specific number of times. If you do not provide this argument, the simulation will just keep running until a philosopher dies.

Example Usage:

Run a simulation with 5 philosophers, an 800ms time to die, 200ms to eat, and 200ms to sleep. The simulation runs until someone starves:

``` bash
./philo 5 800 200 200
```



Run a simulation with 4 philosophers, where the simulation stops after everyone has eaten at least 7 times:

``` bash
./philo 4 410 200 200 7
```

---
**Resources**

* POSIX Threads (pthreads) Documentation: The official Linux manual pages for understanding pthread_create, pthread_join, and the lifecycle of threads.

* Advanced Linux Programming (Chapter 4: Threads): A comprehensive guide detailing thread synchronization, the dangers of data races, and the implementation of mutexes in C.

* A Classic Problem - Dining Philosophers (Toronto Metropolitan University): https://www.ee.torontomu.ca/~courses/coe518/Labs/lab4/lisi.edu-dining-Philosopherecture8.pdf

* Dining Philosopher Solution using Semaphores: https://www.geeksforgeeks.org/operating-systems/dining-philosopher-problem-using-semaphores/

