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
        return -1; // underflow
    }
    return s->arr[s->top--];
}

// Peek element
int peek(struct Stack *s) {
    if (isEmpty(s)) return -1;
    return s->arr[s->top];
}

// Global stacks
struct Stack s1, s2;

// Enqueue operation (O(1))
void enqueue(int x) {
    push(&s1, x);
    printf("%d enqueued\n", x);
}

// Dequeue operation (O(n) in worst case)
int dequeue() {
    if (isEmpty(&s1) && isEmpty(&s2)) {
        printf("Queue is EMPTY!\n");
        return -1;
    }

    // If s2 is empty, move elements from s1
    if (isEmpty(&s2)) {
        while (!isEmpty(&s1)) {
            push(&s2, pop(&s1));
        }
    }

    int val = pop(&s2);
    printf("%d dequeued\n", val);
    return val;
}

// Display queue elements
void display() {
    if (isEmpty(&s1) && isEmpty(&s2)) {
        printf("Queue is EMPTY!\n");
        return;
    }

    printf("Queue elements: ");

    // Print elements in s2 (in reverse order)
    for (int i = s2.top; i >= 0; i--) {
        printf("%d ", s2.arr[i]);
    }

    // Print elements in s1 (in normal order)
    for (int i = 0; i <= s1.top; i++) {
        printf("%d ", s1.arr[i]);
    }

    printf("\n");
}

// Main function
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
