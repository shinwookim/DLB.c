typedef struct
{
    char key;
    DLBNode *sibling;
    DLBNode *child;
    int level;
} DLBNode;

typedef struct
{
    DLBNode *root; // root of trie
    int n;         // number of keys in trie
} DLBTrie;