#include <stdio.h>
#include <string.h>

// Function to compute LPS (Longest Prefix Suffix) array
void computeLPS(char *pat, int m, int *lps) {
    int len = 0; // length of the previous longest prefix suffix
    lps[0] = 0;  // LPS[0] is always 0
    int i = 1;

    while (i < m) {
        if (pat[i] == pat[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if (len != 0) {
                len = lps[len - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
}

// KMP Search function
void KMPsearch(char *pat, char *txt) {
    int m = strlen(pat);
    int n = strlen(txt);

    int lps[m];
    computeLPS(pat, m, lps);

    int i = 0; // index for text
    int j = 0; // index for pattern

    while (i < n) {
        if (pat[j] == txt[i]) {
            i++;
            j++;
        }

        if (j == m) {
            printf("Pattern found at index %d\n", i - j);
            j = lps[j - 1];
        } else if (i < n && pat[j] != txt[i]) {
            if (j != 0)
                j = lps[j - 1];
            else
                i++;
        }
    }
}

int main() {
    char text[100], pattern[50];

    printf("Enter the text: ");
    gets(text);
    printf("Enter the pattern: ");
    gets(pattern);

    KMPsearch(pattern, text);
    return 0;
}
