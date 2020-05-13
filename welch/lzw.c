#include <stdio.h>
#include <stdlib.h>

#include <locale.h>
#include <wchar.h>

#include <malloc.h>
#include <memory.h>


typedef struct tag_bintree_node
{
    int data;
    struct tag_bintree_node* left;
    struct tag_bintree_node* right;
} bintree_node;

typedef struct
{
    bintree_node *root;
    int n_nodes;
    bintree_node *ins;
} lzw_hdr;


lzw_hdr lzw_create(void);
void lzw_insert(lzw_hdr *tree, char ch);
void lzw_free(lzw_hdr *tree);
void bintree_free(bintree_node *root);

void bintree_preorder_print(bintree_node *root);
void bintree_postorder_print(bintree_node *root);

#define BINTREE_PRINT_MAX_WIDTH 50
void bintree_print(bintree_node *node);
void _bintree_print_sub(bintree_node *node, wchar_t *pre, int last);


int main()
{
    srand(1);
    setlocale(LC_ALL, "");

    lzw_hdr tree = lzw_create();

    char input;
    while(!feof(stdin))
    {
        input = (char)getchar();
        if(input == 'r')
        {
            for(int i = 0; i < 100; i++)
                lzw_insert(&tree, rand() % 2 ? '0' : '1');
        }

        lzw_insert(&tree, input);
    }

    bintree_print(tree.root);

    lzw_free(&tree);

    return 0;
}


lzw_hdr lzw_create(void)
{
    lzw_hdr tree;
    tree.root = calloc(1, sizeof(bintree_node));
    tree.n_nodes = 1;
    tree.ins = tree.root;
    return tree;
}

void lzw_insert(lzw_hdr *tree, char ch)
{
    if(tree->root == NULL || tree->ins == NULL) return;

    bintree_node **child = NULL;

    if(ch == '0') child = &tree->ins->left;
    else if(ch =='1') child = &tree->ins->right;
    else return;
    
    if(*child == NULL)
    {
        *child = calloc(1, sizeof(bintree_node));
        (*child)->data = tree->n_nodes++;
        tree->ins = tree->root;
    }
    else tree->ins = *child;
}

void lzw_free(lzw_hdr *tree)
{
    bintree_free(tree->root);
    tree->root = tree->ins = NULL;
    tree->n_nodes = 0;
}

void bintree_free(bintree_node *root)
{
    if(root->left != NULL)
        bintree_free(root->left);
    if(root->right != NULL)
        bintree_free(root->right);
    free(root);
}


void bintree_preorder_print(bintree_node *root)
{
    if(root == NULL) return;
    printf("%d", root->data);
    bintree_preorder_print(root->left);
    bintree_preorder_print(root->right);
}

void bintree_postorder_print(bintree_node *root)
{
    if(root == NULL) return;
    bintree_postorder_print(root->left);
    bintree_postorder_print(root->right);
    printf("%d", root->data);
}

void bintree_print(bintree_node *root)
{
    static wchar_t indent[BINTREE_PRINT_MAX_WIDTH];
    memset(indent, 0, sizeof(wchar_t) * BINTREE_PRINT_MAX_WIDTH);

    _bintree_print_sub(root, indent, -1);
}

void _bintree_print_sub(bintree_node *node, wchar_t *pre, int type)
{
    if(type != -1)
    {
        wprintf(pre);
        if(type == 0) wprintf(L"├─");
        else wprintf(L"└─");
    }
    if(node == NULL) wprintf(L"NULL\n");
    else
    {

        wprintf(L"%d\n", node->data);

        int pre_len = wcslen(pre);
        if(pre_len + 2 > BINTREE_PRINT_MAX_WIDTH)
        {
            wprintf(pre);
            if(type == 0) wprintf(L"│ └─...\n");
            else if(type == 1) wprintf(L"  └─...\n");
        }
        else
        {
            if(type == 0) swprintf(pre + pre_len, 3, L"│ ");
            else if(type == 1) swprintf(pre + pre_len, 3, L"  ");

            _bintree_print_sub(node->left, pre, 0);
            _bintree_print_sub(node->right, pre, 1);

            pre[pre_len] = L'\0';
        }
    }
}


/*
001000010011011101010000110010110110000111011001111001000110110100000010111
110101010010111101110000011110010111001011111011000010011110111001001111101
*/
