#ifndef LIST_H
#define LIST_H
#include <stdlib.h>
#include <string.h>

struct Node {
    void* ptr;
    struct Node* next;
    struct Node* prev;
};

struct List {
    Node* first;
    Node* last;
    size_t size;
    size_t count;
};

struct List listInit(size_t size);

void listPush(struct List* list, void* element);

void listFree(struct List* list);

struct Node* listIndex(struct List* list, size_t index);

#endif // LIST_H
