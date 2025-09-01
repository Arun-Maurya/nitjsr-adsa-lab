#include <stdio.h>
#include <stdlib.h>

// Node structure
struct Node {
    int data;
    struct Node *next;
};

struct Node *front = NULL, *rear = NULL;

// Function to check if queue is empty
int isEmpty() {
    return (front == NULL);
}

// Function to insert element in circular queue
void enqueue(int value) {
    struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));
    if (!newNode) {
        printf("Memory allocation failed!\n");
        return;
    }
    newNode->data = value;
    newNode->next = NULL;

    if (front == NULL) {
        // first node
        front = rear = newNode;
        rear->next = front;  // circular link
    } else {
        rear->next = newNode;
        rear = newNode;
        rear->next = front;  // maintain circular link
    }
    printf("%d inserted into queue\n", value);
}

// Function to delete element from circular queue
int dequeue() {
    if (isEmpty()) {
        printf("Queue is EMPTY!\n");
        return -1;
    }

    int value;
    if (front == rear) {
        // only one node
        value = front->data;
        free(front);
        front = rear = NULL;
    } else {
        struct Node *temp = front;
        value = temp->data;
        front = front->next;
        rear->next = front;  // maintain circular link
        free(temp);
    }
    printf("%d removed from queue\n", value);
    return value;
}

// Function to display elements of circular queue
void display() {
    if (isEmpty()) {
        printf("Queue is EMPTY!\n");
        return;
    }

    struct Node *temp = front;
    printf("Queue elements: ");
    do {
        printf("%d ", temp->data);
        temp = temp->next;
    } while (temp != front);
    printf("\n");
}

// Main function
int main() {
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
