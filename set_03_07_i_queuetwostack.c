#include <stdio.h>
#include <stdlib.h>

#define SIZE 100

// Stack structure
struct Stack {
    int arr[SIZE];
    int top;
};

// Initialize stack
void init(struct Stack *s) {
    s->top = -1;
}

// Check if stack is empty
int isEmpty(struct Stack *s) {
    return (s->top == -1);
}

// Check if stack is full
int isFull(struct Stack *s) {
    return (s->top == SIZE - 1);
}

// Push element into stack
void push(struct Stack *s, int x) {
    if (isFull(s)) {
        printf("Stack Overflow!\n");
        return;
    }
    s->arr[++s->top] = x;
}

// Pop element from stack
int pop(struct Stack *s) {
    if (isEmpty(s)) {
        printf("Stack Underflow!\n");
        return -1;
    }
    return s->arr[s->top--];
}

// Peek top element
int peek(struct Stack *s) {
    if (isEmpty(s)) {
        return -1;
    }
    return s->arr[s->top];
}

// Global stacks
struct Stack s1, s2;

// Enqueue operation (costly)
void enqueue(int x) {
    // Step 1: move all elements from s1 to s2
    while (!isEmpty(&s1)) {
        push(&s2, pop(&s1));
    }

    // Step 2: push x into s1
    push(&s1, x);

    // Step 3: move everything back from s2 to s1
    while (!isEmpty(&s2)) {
        push(&s1, pop(&s2));
    }

    printf("%d enqueued\n", x);
}

// Dequeue operation (O(1))
int dequeue() {
    if (isEmpty(&s1)) {
        printf("Queue is EMPTY!\n");
        return -1;
    }
    int val = pop(&s1);
    printf("%d dequeued\n", val);
    return val;
}

// Display queue elements
void display() {
    if (isEmpty(&s1)) {
        printf("Queue is EMPTY!\n");
        return;
    }
    printf("Queue elements: ");
    for (int i = 0; i <= s1.top; i++) {
        printf("%d ", s1.arr[i]);
    }
    printf("\n");
}

int main() {
    init(&s1);
    init(&s2);

    enqueue(10);
    enqueue(20);
    enqueue(30);
    enqueue(40);

    display();

    dequeue();
    dequeue();

    display();

    enqueue(50);
    enqueue(60);

    display();

    return 0;
}
