#include <stdio.h>
#include <stdlib.h>

#define TABLE_SIZE 1000
typedef struct Node {
    int key;
    struct Node* next;
} Node;

Node* hashTable[TABLE_SIZE];

int hash(int key) {
    return abs(key) % TABLE_SIZE;
}
void insert(int key) {
    int index = hash(key);
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->key = key;
    newNode->next = hashTable[index];
    hashTable[index] = newNode;
}
int search(int key) {
    int index = hash(key);
    Node* temp = hashTable[index];

    while (temp) {
        if (temp->key == key)
            return 1;
        temp = temp->next;
    }
    return 0;
}
void intersection(int output[], int array1[], int lenArr1, int array2[], int lenArr2) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        hashTable[i] = NULL;
    }
    for (int i = 0; i < lenArr1; i++) {
        insert(array1[i]);
    }

    int k = 0;
    for (int i = 0; i < lenArr2; i++) {
        if (search(array2[i])) {
            output[k++] = array2[i];
        }
    }
    output[k] = -1;
}
int main() {
    int n1, n2;
    scanf("%d", &n1);
    int array1[n1];
    for (int i = 0; i < n1; i++) {
        scanf("%d", &array1[i]);
    }
    scanf("%d", &n2);
    int array2[n2];
    for (int i = 0; i < n2; i++) {
        scanf("%d", &array2[i]);
    }

    int output[n2];
    intersection(output, array1, n1, array2, n2);
    for (int i = 0; output[i] != -1; i++) {
        printf("%d ", output[i]);
    }
    return 0;
}
