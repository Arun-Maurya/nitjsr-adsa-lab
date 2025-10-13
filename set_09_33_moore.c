#include <stdio.h>
#include <string.h>
#define NO_OF_CHARS 256

void badCharHeuristic(char *str, int size, int badchar[NO_OF_CHARS]) {
    int i;
    for (i = 0; i < NO_OF_CHARS; i++)
        badchar[i] = -1;
    for (i = 0; i < size; i++)
        badchar[(int)str[i]] = i;
}

void boyerMoore(char *txt, char *pat) {
    int m = strlen(pat);
    int n = strlen(txt);
    int badchar[NO_OF_CHARS];

    badCharHeuristic(pat, m, badchar);

    int s = 0; // shift
    while (s <= (n - m)) {
        int j = m - 1;

        while (j >= 0 && pat[j] == txt[s + j])
            j--;

        if (j < 0) {
            printf("Pattern found at index %d\n", s);
            s += (s + m < n) ? m - badchar[txt[s + m]] : 1;
        } else {
            s += (j - badchar[txt[s + j]] > 1) ? j - badchar[txt[s + j]] : 1;
        }
    }
}

int main() {
    char txt[100], pat[50];
    printf("Enter text: ");
    gets(txt);
    printf("Enter pattern: ");
    gets(pat);
    boyerMoore(txt, pat);
    return 0;
}
