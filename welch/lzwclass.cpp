#include <iostream>
#include <algorithm>
#include <locale>


template <class T>
class bin_tree
{
public:
    class node
    {
    private:
        node *left, *right;
        T data;

        node() = default;
        node(const T& d) : data(d), left(nullptr), right(nullptr) {}
        node(T&& d) : data(d), left(nullptr), right(nullptr) {}

        node(const node& other)
        {
            if(other.left != nullptr)
                left = new node(*other.left);
            else left = nullptr;

            if(other.right != nullptr)
                right = new node(*other.right)
            else right = nullptr;

            data = other.data;
        }
        node(node&& other) : node()
        {
            swap(*this, other);
        }

        ~node()
        {
            delete left;
            delete right;
        }

        node& operator=(node other) //copy-and-swap idiom!
        {
            swap(*this, other);
        }

        static void swap(node& a, node& b)
        {
            std::swap(a.left, b.left);
            std::swap(a.right, b.right);
            std::swap(a.data, b.data);
        }

        static void _print(node *n, const std::ostream& ostr, int max_width,
            std::wstring pre = "", int type = -1)
        {
            if(type != -1)
            {
                ostr<<pre;
                if(type == 0) ostr<<L"├─";
                else ostr<<L"└─";
            }
            if(n == nullptr) ostr<<L"NULL\n";
            else
            {
                ostr<<L""<<n->data<<"\n";

                int pre_len = pre.length();
                if(pre_len + 2 > max_width)
                {
                    ostr<<pre;
                    if(type == 0) ostr<<L"│ └─...\n";
                    else if(type == 1) ostr<<L"  └─...\n";
                }
                else
                {
                    if(type == 0) pre += L"│ ";
                    else if(type == 1) pre += L"  ";

                    _print(n->left, ostr, max_width, pre, 0);
                    _print(n->right, ostr, max_width, pre, 1);

                    pre = pre.substr(0, pre_len);
                }
            }
        }

    public:

        bool operator==(const node& other)
        {
            return data == other.data && left == other.left && right == other.right;
        }
        bool operator!=(const node& other)
        {
            return !(*this == other);
        }

        T& value() { return data; }
        const T& value() const { return data; }
        void value(const T& val) { data = val; }
        void value(T&& val) { data = val; }

    };

    bin_tree() : root(), n_nodes(0) {}
    bin_tree(const T& r) : root(r), n_nodes(1) {}

    bin_tree(const bin_tree<T>& other) : root(other.root), n_nodes(other.n_nodes) {}
    bin_tree(bin_tree<T>&& other) : root(std::move(other.root)), n_nodes(other.n_nodes) {}

    ~bin_tree() = default;

    bin_tree<T>& operator=(const bin_tree<T> other)
    {
        node::swap(root, other.root);
    }

    void print(const std::ostream& ostr = std::wcout, int max_width = 64) const
    {
        node::_print(&root, ostr, max_width);
    }

protected:
    node root;
    int n_nodes;
};

class lzw_tree : public bin_tree<int>
{
public:
    //!constructors and stuff
    void insert(int bit)//!
    {

    }

private:
    node *current;
};

int main(int argc, char **argv)
{
    //lzw_tree tree;



    return 0;
}
