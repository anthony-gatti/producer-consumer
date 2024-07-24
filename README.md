# Producer-Consumer Problem with Pthreads

This repository contains a C implementation of the Producer-Consumer problem using pthreads. The problem demonstrates the usage of condition variables and mutexes to handle synchronization between threads.

## Overview

The Producer-Consumer problem is a classic example of a multi-process synchronization problem. Here, we have a fixed-size buffer shared between producer threads and consumer threads. The producer threads generate data and place it into the buffer, while consumer threads take data from the buffer and process it. The synchronization is necessary to prevent the producer from adding data to a full buffer and the consumer from removing data from an empty buffer.

### Key Concepts:

- **Buffer**: A fixed-size array used to hold data temporarily.
- **Producers**: Threads that generate and add data to the buffer.
- **Consumers**: Threads that remove and process data from the buffer.
- **Mutex**: A mutual exclusion lock to ensure that only one thread can access the buffer at a time.
- **Condition Variables**: Used to signal threads when the buffer is not full or not empty.

## Files

- `producer_consumer.c`: Contains the implementation of the producer and consumer functions, as well as the main function to run the threads.

## Building the Project

To build the project, you need to have `gcc` and the `pthread` library installed. You can build the project using the following command:

```sh
gcc -o producer_consumer producer_consumer.c -lpthread
```
## Running the Program

After building the project, you can run the program using the following command:
```sh
./producer_consumer
```
The output will show the interactions between the producer and consumer threads, indicating when data is produced and consumed.

## Customizing

- **Number of Producers and Consumers**: The number of producer and consumer threads can be adjusted by changing the num_producers and num_consumers variables in the main function.