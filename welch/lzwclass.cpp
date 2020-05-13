#include <iostream>
#include <locale>

#include <vector>
#include <stack>
#include <queue>

#include <memory>

template <typename T>
class bin_tree
{
private:
    node root;
    int n_nodes;

public:
    class node
    {
    private:
        node *left, *right;
        T data;

        node();
        node(T d) : data(d);
        node(node& other);
        node(node&& other);
        ~node();

    public:
        node& operator=(node& other);
        node& operator=(node&& other);
    };

    bin_tree() : root(nullptr), n_nodes(0);
    bin_tree(T r) : root(r);
    bin_tree(bin_tree<T>& other);
    bin_tree(bin_tree<T>&& other);
    ~bin_tree();
    bin_tree<T>& operator=(bin_tree<T>& other);
    bin_tree<T>& operator=(bin_tree<T>&& other);


};