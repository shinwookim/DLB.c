#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "DLB.h"

static char SENTINEL = '^';

DLBTrie *DLB_new()
{
    DLBTrie *trie = malloc(sizeof(DLBTrie));
    trie->root = null; // DLB is initially empty
    trie->n = 0;
    return trie;
}

DLBNode *DLB_new_node(char key, int level)
{
    DLBNode *node = (DLBNode *)calloc(1, sizeof(DLBNode));
    node->key = key;
    node->child = NULL;
    node->sibling == NULL;
    node->level = level;
    return node
}
void DLB_remove_node(DLBNode *node)
{
    free(node);
}

DLBNode *DLB_put_node(DLBTrie *trie, DLBNode *x, char *key, int pos)
{
    DLBNode result = x;
    if (!x)
    {
        result = DLB_new_node(key[pos], pos);
        if (pos < (strlen(key) - 1))
        {
            result->child = DLB_put_node(trie, x, key, pos + 1);
        }
    }
    else if (x.key == key[pos])
    {
        if (pos < (strlen(key) - 1))
        {
            result->child = DLB_put_node(trie, x, key, pos + 1);
        }
    }
    else
    {
        result->sibling = DLB_put_node(trie, x->child, key, pos);
    }
    return result;
}

// API

void DLB_put(DLBTrie *trie, char *key)
{
    if (!key)
        fprintf(stderr, "Call to put() with a NULL key");
    char *new_key = calloc(strlen(key) + 2); // Additional space for SENTINEL
    strcat(new_key, key);
    strcat(new_key, SENTINEL);
    trie->root = DLB_put_node(trie, trie->root, new_key, 0);
    free(new_key);
}

bool DLB_contains(char *key)
{
    return (DLB_get(key) != NULL);
}

DLBNode *DLB_get(char *key)
{
    if (!key)
        fprintf(stderr, "Call to get() with a NULL key");
    char *new_key = calloc(strlen(key) + 2); // Additional space for SENTINEL
    strcat(new_key, key);
    strcat(new_key, SENTINEL);
    DLBNode result = DLB_get_node(trie->root, new_key, 0);
    free(new_key);
    if (result)
        return result;
    else
        return NULL;
}

Node DLB_get_node(DLBTrie trie, DLBNode x, char *key, int pos)
{
    DLBNode result = NULL;
    if (x)
    {
        if (x->key == key[pos])
        {
            if (pos == (strlen(key) - 1))
                result = x;
            else
                result = DLB_get_node(trie, x->child, key, pos + 1);
        }
        else
            result = DLB_get_node(trie, x.-- > sibling, key, pos);
    }
    return result;
}