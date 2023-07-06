#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "DLB.h"

static char SENTINEL = '^';

DLBTrie *DLB_new()
{
    DLBTrie *trie = malloc(sizeof(DLBTrie));
    trie->root = NULL; // DLB is initially empty
    trie->n = 0;
    return trie;
}

DLBNode *DLB_new_node()
{
    DLBNode *node = (DLBNode *)calloc(1, sizeof(DLBNode));
    return node;
}
void DLB_remove_node(DLBNode *node)
{
    free(node);
}

DLBNode *DLB_put_node(DLBTrie *trie, DLBNode *x, char *key, int val, int pos)
{
    DLBNode *result = x;
    if (!x)
    {
        result = DLB_new_node(); // if a node doesn't exist, create new node
        result->letter = key[pos];
        result->level = pos;
        if (pos < (strlen(key) - 1))                                  // check if more letters to process
            result->child = DLB_put_node(trie, x, key, val, pos + 1); // recursively call DLB_put_node()
        else
            result->val = val;
    }
    else if (x->letter == key[pos]) // if a node already exists
    {
        if (pos < (strlen(key) - 1))
            result->child = DLB_put_node(trie, x, key, val, pos + 1);
        else
            result->val = val;
    }
    else
        result->sibling = DLB_put_node(trie, x->child, key, val, pos);
    return result;
}

// API

void DLB_put(DLBTrie *trie, char *key, int val)
{
    if (!key) // check for NULL key
        fprintf(stderr, "Call to put() with a NULL key");
    char *new_key = calloc(strlen(key) + 2, sizeof(char)); // additional space for SENTINEL
    strcat(new_key, key);
    strcat(new_key, &SENTINEL); // add SENTINEL to key
    trie->root = DLB_put_node(trie, trie->root, new_key, val, 0);
    free(new_key);
}

DLBNode *DLB_get_node(DLBTrie *trie, DLBNode *x, char *key, int pos)
{
    DLBNode *result = NULL;
    if (x)
    {
        if (x->letter == key[pos])
        {
            if (pos == (strlen(key) - 1))
                result = x;
            else
                result = DLB_get_node(trie, x->child, key, pos + 1);
        }
        else
            result = DLB_get_node(trie, x->sibling, key, pos);
    }
    return result;
}

int DLB_get(DLBTrie *trie, char *key)
{
    if (!key)
        fprintf(stderr, "Call to get() with a NULL key");
    char *new_key = calloc(strlen(key) + 2, sizeof(char)); // additional space for SENTINEL
    strcat(new_key, key);
    strcat(new_key, &SENTINEL); // add SENTINEL to key
    DLBNode *result = DLB_get_node(trie, trie->root, new_key, 0);
    free(new_key);
    if (result)
        return result->val;
    else
        return -1; // -1 indicates does not exist
}

bool DLB_contains(DLBTrie *trie, char *key)
{
    return (DLB_get(trie, key) != -1);
}