#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXWORD 1000
#define MAXNODES 10000

struct tnode {
    char *word;
    int count;
    struct tnode *left;
    struct tnode *right;
};

struct tnode *addtree(struct tnode *, char *);
void tree_to_array(struct tnode *, struct tnode **, int *);
int getword(char *, int);
int compare(const void *, const void *);

struct tnode *node_list[MAXNODES];
int node_count = 0;

struct tnode *addtree(struct tnode *p, char *w) {
    int cond;

    if (p == NULL) {
        p = (struct tnode *) malloc(sizeof(struct tnode));
        p->word = strdup(w);
        p->count = 1;
        p->left = p->right = NULL;
    } else if ((cond = strcmp(w, p->word)) == 0) {
        p->count++;
    } else if (cond < 0) {
        p->left = addtree(p->left, w);
    } else {
        p->right = addtree(p->right, w);
    }
    return p;
}

void tree_to_array(struct tnode *p, struct tnode **arr, int *i) {
    if (p != NULL) {
        tree_to_array(p->left, arr, i);
        arr[(*i)++] = p;
        tree_to_array(p->right, arr, i);
    }
}

int compare(const void *a, const void *b) {
    struct tnode *t1 = *(struct tnode **)a;
    struct tnode *t2 = *(struct tnode **)b;

    if (t2->count != t1->count)
        return t2->count - t1->count;
    return strcmp(t1->word, t2->word);
}

int getword(char *word, int lim) {
    int c;
    char *w = word;

    while (isspace(c = getchar()))
        ;

    if (c == EOF)
        return EOF;

    *w++ = c;

    if (!isalpha(c)) {
        *w = '\0';
        return c;
    }

    for (; --lim > 0; w++) {
        if (!isalnum(*w = getchar())) {
            ungetc(*w, stdin);
            break;
        }
    }

    *w = '\0';
    return word[0];
}

int main(void) {
    struct tnode *root = NULL;
    char word[MAXWORD];
    int i = 0;

    while (getword(word, MAXWORD) != EOF) {
        if (isalpha(word[0])) {
            root = addtree(root, word);
        }
    }

    tree_to_array(root, node_list, &node_count);

    qsort(node_list, node_count, sizeof(struct tnode *), compare);

    for (i = 0; i < node_count; i++) {
        printf("%d %s\n", node_list[i]->count, node_list[i]->word);
    }

    return 0;
}
