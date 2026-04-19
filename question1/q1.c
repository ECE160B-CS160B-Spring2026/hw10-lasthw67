#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXWORD 100
const char *keywords[] = {
    "auto", "break", "case", "char", "const", "continue", "default",
    "do", "double", "else", "enum", "extern", "float", "for",
    "goto", "if", "inline", "int", "long", "register", "restrict",
    "return", "short", "signed", "sizeof", "static", "struct",
    "switch", "typedef", "union", "unsigned", "void", "volatile", "while"
};

#define NKEYS (sizeof(keywords) / sizeof(keywords[0]))

int counts[NKEYS] = {0};
int getword(char *word, int lim) {
    int c;
    char *w = word;
    while (isspace(c = getchar()))
        ;

    if (c != EOF)
        *w++ = c;

    if (!isalpha(c)) {
        *w = '\0';
        return c;
    }

    for (; --lim > 0; w++) {
        c = getchar();
        if (!isalnum(c)) {
            ungetc(c, stdin);
            break;
        }
        *w = c;
    }
    *w = '\0';
    return word[0];
}
int binsearch(char *word, const char *keywords[], int n) {
    int low = 0, high = n - 1, mid, cond;

    while (low <= high) {
        mid = (low + high) / 2;
        cond = strcmp(word, keywords[mid]);

        if (cond < 0)
            high = mid - 1;
        else if (cond > 0)
            low = mid + 1;
        else
            return mid;
    }
    return -1;
}

int main() {
    char word[MAXWORD];
    int index;

    while (getword(word, MAXWORD) != EOF) {
        if (isalpha(word[0])) {
            index = binsearch(word, keywords, NKEYS);
            if (index >= 0)
                counts[index]++;
        }
    }
    for (int i = 0; i < NKEYS; i++) {
        if (counts[i] > 0)
            printf("%s: %d\n", keywords[i], counts[i]);
    }

    return 0;
}
