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
    q->front = q->rear = -1;
}

// Check if queue is empty
int isEmpty(struct Queue *q) {
    return (q->front == -1);
}

// Check if queue is full
int isFull(struct Queue *q) {
    return (q->rear == SIZE - 1);
}

// Enqueue operation
void enqueue(struct Queue *q, int x) {
    if (isFull(q)) {
        printf("Queue Overflow!\n");
        return;
    }
    if (q->front == -1) q->front = 0;
    q->arr[++q->rear] = x;
}

// Dequeue operation
int dequeue(struct Queue *q) {
    if (isEmpty(q)) {
        return -1;
    }
    int val = q->arr[q->front];
    if (q->front == q->rear) {
        q->front = q->rear = -1;
    } else {
        q->front++;
    }
    return val;
}

// Global queues
struct Queue q1, q2;

// Push operation (O(1))
void push(int x) {
    enqueue(&q1, x);
    printf("%d pushed into stack\n", x);
}

// Pop operation (O(n))
int pop() {
    if (isEmpty(&q1)) {
        printf("Stack Underflow!\n");
        return -1;
    }

    // Move elements except last one
    while (q1.front != q1.rear) {
        enqueue(&q2, dequeue(&q1));
    }

    // Last element (stack top)
    int val = dequeue(&q1);

    // Swap q1 and q2
    struct Queue temp = q1;
    q1 = q2;
    q2 = temp;

    printf("%d popped from stack\n", val);
    return val;
}

// Display stack elements
void display() {
    if (isEmpty(&q1)) {
        printf("Stack is EMPTY!\n");
        return;
    }

    printf("Stack elements (top to bottom): ");
    for (int i = q1.rear; i >= q1.front; i--) {
        printf("%d ", q1.arr[i]);
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
