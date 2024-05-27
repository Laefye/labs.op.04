#include "list.h"

struct List listInit(size_t size) {
    return {
        .first = 0,
        .last = 0,
        .size = size,
        .count = 0,
    };
}

void listPush(struct List* list, void* element) {
    if (!list->first) {
        list->first = (Node*) malloc(sizeof(struct Node));
        list->first->next = 0;
        list->first->prev = 0;
        list->first->ptr = malloc(list->size);
        memcpy(list->first->ptr, element, list->size);

        list->last = list->first;
    } else {
        list->last->next = (Node*) malloc(sizeof(struct Node));
        list->last->next->next = 0;
        list->last->next->prev = list->last;
        list->last->next->ptr = malloc(list->size);
        memcpy(list->last->next->ptr, element, list->size);

        list->last = list->last->next;
    }
    list->count++;
}

void listFree(struct List* list) {
    struct Node* node = list->last;
    while (node) {
        struct Node* prev = node->prev;
        free(node->ptr);
        free(node);
        node = prev;
    }
}

struct Node* listIndex(struct List* list, size_t index) {
    size_t i = 0;
    for (struct Node* node = list->first; node; node = node->next) {
        if (i == index) {
            return node;
        }
        i++;
    }
    return 0;
}
