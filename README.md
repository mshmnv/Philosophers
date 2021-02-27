# Dining Philosophers

* A number of philosophers are sitting at a round table doing one of three things: eating, thinking or sleeping.
* While eating, they are not thinking or sleeping, while sleeping, they are not eating or thinking and of course, while thinking, they are not eating or sleeping.
* The philosophers sit at a circular table with a large bowl of spaghetti in the center.
* There are some forks on the table.
* As spaghetti is difficult to serve and eat with a single fork, it is assumed that a philosopher must eat with two forks, one for each hand.
* The philosophers must never be starving.
* Every philosopher needs to eat.
* The simulation stops when a philosopher dies.

## philo_one
* *philosopher = thread*
* *forks = mutexes*
* *one fork between each philosopher*

## philo_two
* *philosopher = thread*
* *forks = semaphore*
* *forks are in the middle of the table*

## philo_three
* *philosopher = process*
* *forks = semaphore*
* *forks are in the middle of the table*

### Usage
Arguments: *number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]*

```
make
./philo_one 5 410 200 200
```

### TESTS
```
# Someone dies
./philo_one 5 410 200 200
./philo_one 4 310 200 100

# Nobody dies
./philo_one 6 410 200 200
./philo_one 5 800 200 200
./philo_one 4 410 200 200

# With the number of times to eat
./philo_one 5 800 200 200 7
./philo_one 3 310 200 100 2
./philo_one 4 410 200 200 10
```
