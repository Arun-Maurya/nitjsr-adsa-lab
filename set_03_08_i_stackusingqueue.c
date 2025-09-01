#include <stdio.h>
#include <stdlib.h>

#define SIZE 100

// Queue structure
struct Queue {
    int arr[SIZE];
    int front, rear;
};

// Initialize queue
void init(struct Queue *q) {
    q->front = -1;
    q->rear = -1;
}

// Check if queue is empty
int isEmpty(struct Queue *q) {
    return (q->front == -1);
}

// Check if queue is full
int isFull(struct Queue *q) {
    return ((q->rear + 1) % SIZE == q->front);
}

// Enqueue operation
void enqueue(struct Queue *q, int x) {
    if (isFull(q)) {
        printf("Queue Overflow!\n");
        return;
    }
    if (isEmpty(q)) {
        q->front = q->rear = 0;
    } else {
        q->rear = (q->rear + 1) % SIZE;
    }
    q->arr[q->rear] = x;
}

// Dequeue operation
int dequeue(struct Queue *q) {
    if (isEmpty(q)) {
        return -1; // underflow
    }
    int val = q->arr[q->front];
    if (q->front == q->rear) {
        q->front = q->rear = -1;
    } else {
        q->front = (q->front + 1) % SIZE;
    }
    return val;
}

// Peek front element
int peek(struct Queue *q) {
    if (isEmpty(q)) return -1;
    return q->arr[q->front];
}

// Global queues
struct Queue q1, q2;

// Push operation (costly)
void push(int x) {
    // Step 1: enqueue into q2
    enqueue(&q2, x);

    // Step 2: move all elements from q1 to q2
    while (!isEmpty(&q1)) {
        enqueue(&q2, dequeue(&q1));
    }

    // Step 3: swap q1 and q2
    struct Queue temp = q1;
    q1 = q2;
    q2 = temp;

    printf("%d pushed\n", x);
}

// Pop operation (O(1))
int pop() {
    if (isEmpty(&q1)) {
        printf("Stack is EMPTY!\n");
        return -1;
    }
    int val = dequeue(&q1);
    printf("%d popped\n", val);
    return val;
}

// Display stack elements
void display() {
    if (isEmpty(&q1)) {
        printf("Stack is EMPTY!\n");
        return;
    }
    printf("Stack elements (top to bottom): ");
    int i = q1.front;
    while (1) {
        printf("%d ", q1.arr[i]);
        if (i == q1.rear) break;
        i = (i + 1) % SIZE;
    }
    printf("\n");
}

// Main function
int main() {
    init(&q1);
    init(&q2);

    push(10);
    push(20);
    push(30);
    push(40);

    display();

    pop();
    pop();

    display();

    push(50);
    push(60);

    display();

    return 0;
}
