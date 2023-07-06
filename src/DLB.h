typedef struct DLBNode
{
    int val; // DLB holds integer values
    char letter;
    struct DLBNode *sibling;
    struct DLBNode *child;
    int level; // for level-order traversal
} DLBNode;

typedef struct DLBTrie
{
    struct DLBNode *root; // root of trie
    int n;                // number of keys in trie
} DLBTrie;