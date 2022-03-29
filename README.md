# Philosophers
A 42Paris project about multithreading

# Use
```
./philo [Number of philosophers <1-200>] [time_to_die] [time_to_eat] [time_to_sleep]
```
# test
|Test|Passing|Comment|
|:--|---|--:|
|./philo 1 200 200 200|~|Takes two forks but still die|
|./philo 2 800 200 200|√|Working as intended|
|./philo 5 800 200 200|√|Working as intended|
|./philo 5 800 200 200 7|√|Working as intended|
|./philo 4 410 200 200|√|Working as intended|
|./philo 4 310 200 200|×|No one is dying|
|./philo 4 500 200 1.2|√|Working as intended|
|./philo 4 0 200 200|√|Working as intended|
|./philo 4 -500 200 200|√|Working as intended|
|./philo 4 500 200 2147483647|~|philo dying but a bit late (should be 500 ms)|
|./philo 4 2147483647 200 200|√|Working as intended|
|./philo 4 214748364732 200 200|√|Working as intended|
|./philo 4 200 210 200|~|Dying but too late|
