#include <stdio.h>
#include <stdlib.h>

#define SIZE 5  // maximum size of the queue

int queue[SIZE];
int front = -1, rear = -1;

// Function to check if the queue is full
int isFull() {
    return ((front == 0 && rear == SIZE - 1) || (rear + 1 == front));
}

// Function to check if the queue is empty
int isEmpty() {
    return (front == -1);
}

// Function to insert an element in the queue
void enqueue(int value) {
    if (isFull()) {
        printf("Queue is FULL! Cannot insert %d\n", value);
        return;
    }
    if (front == -1) // first insertion
        front = 0;
    rear = (rear + 1) % SIZE;
    queue[rear] = value;
    printf("%d inserted into queue\n", value);
}

// Function to delete an element from the queue
int dequeue() {
    if (isEmpty()) {
        printf("Queue is EMPTY!\n");
        return -1;
    }
    int data = queue[front];
    if (front == rear) {
        // Only one element left
        front = rear = -1;
    } else {
        front = (front + 1) % SIZE;
    }
    printf("%d removed from queue\n", data);
    return data;
}

// Function to display the queue
void display() {
    if (isEmpty()) {
        printf("Queue is EMPTY!\n");
        return;
    }
    printf("Queue elements: ");
    int i = front;
    while (1) {
        printf("%d ", queue[i]);
        if (i == rear)
            break;
        i = (i + 1) % SIZE;
    }
    printf("\n");
}

int main() {
    enqueue(10);
    enqueue(20);
    enqueue(30);
    enqueue(40);
    enqueue(50);

    display();

    dequeue();
    dequeue();

    display();

    enqueue(60);
    enqueue(70);

    display();

    return 0;
}
