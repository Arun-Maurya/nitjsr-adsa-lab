#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct Point {
    int x, y;
} Point;

Point p0;

// Function to swap two points
void swap(Point *p1, Point *p2) {
    Point temp = *p1;
    *p1 = *p2;
    *p2 = temp;
}

// Returns square of distance between p1 and p2
int distSq(Point p1, Point p2) {
    return (p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y);
}

// To find orientation of ordered triplet (p, q, r)
// 0 --> collinear, 1 --> clockwise, 2 --> counterclockwise
int orientation(Point p, Point q, Point r) {
    int val = (q.y - p.y)*(r.x - q.x) - (q.x - p.x)*(r.y - q.y);
    if (val == 0) return 0;
    return (val > 0) ? 1 : 2;
}

// Comparison function for qsort
int compare(const void *vp1, const void *vp2) {
    Point *p1 = (Point *)vp1;
    Point *p2 = (Point *)vp2;

    int o = orientation(p0, *p1, *p2);
    if (o == 0)
        return (distSq(p0, *p2) >= distSq(p0, *p1)) ? -1 : 1;
    return (o == 2) ? -1 : 1;
}

// Print stack contents as hull
void printHull(Point points[], int n) {
    // Find the bottom-most point
    int ymin = points[0].y, min = 0;
    for (int i = 1; i < n; i++) {
        int y = points[i].y;
        if ((y < ymin) || (ymin == y && points[i].x < points[min].x)) {
            ymin = points[i].y;
            min = i;
        }
    }

    // Place the bottom-most point at first position
    swap(&points[0], &points[min]);
    p0 = points[0];

    // Sort remaining points based on polar angle with p0
    qsort(&points[1], n - 1, sizeof(Point), compare);

    // Remove points with same angle, keep farthest
    int m = 1;
    for (int i = 1; i < n; i++) {
        while (i < n - 1 && orientation(p0, points[i], points[i + 1]) == 0)
            i++;
        points[m] = points[i];
        m++;
    }

    if (m < 3) {
        printf("Convex hull not possible\n");
        return;
    }

    Point stack[m];
    int top = 2;
    stack[0] = points[0];
    stack[1] = points[1];
    stack[2] = points[2];

    for (int i = 3; i < m; i++) {
        while (orientation(stack[top - 1], stack[top], points[i]) != 2)
            top--;
        stack[++top] = points[i];
    }

    printf("\nPoints in Convex Hull (in counterclockwise order):\n");
    for (int i = 0; i <= top; i++)
        printf("(%d, %d)\n", stack[i].x, stack[i].y);
}

int main() {
    int n;
    printf("Enter number of points: ");
    scanf("%d", &n);

    Point points[n];
    printf("Enter points (x y):\n");
    for (int i = 0; i < n; i++)
        scanf("%d %d", &points[i].x, &points[i].y);

    printHull(points, n);
    return 0;
}
