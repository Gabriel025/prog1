#ifndef BINTREE_D_H
#define BINTREE_D_H

#include<iostream>
#include<algorithm>

template <class T>
class bin_tree
{
public:
    class node
    {
        friend class bin_tree;

    private:
        node *m_left, *m_right;
        T m_data;

    public:
        node();// = default;
        node(const T& d);
        node(T&& d);
        ~node();

        node(const node& other);
        node(node&& other);

        node& operator=(node other);

        static void swap(node& a, node& b);

        bool operator==(const node& other) const;
        bool operator!=(const node& other) const;

        const T& value() const;
        void set_value(const T& val);
        void set_value(T&& val);

        node *left();
        const node *left() const;
        node *right();
        const node *right() const;

        node *insert_left(const T& data, bool overwrite = false);
        node *insert_left(T&& data, bool overwrite = false);
        node *insert_right(const T& data, bool overwrite = false);
        node *insert_right(T&& data, bool overwrite = false);

    private:
        static void _print(const node *n, bool print_nulls, int max_width,
            std::wstring pre = L"", int type = -1);
    };

    bin_tree();
    bin_tree(const T& r);
    bin_tree(T&& r);
    ~bin_tree();

    bin_tree(const bin_tree<T>& other);
    bin_tree(bin_tree<T>&& other);

    bin_tree<T>& operator=(bin_tree<T> other);

    void print(bool print_nulls = false, int max_width = 64) const;

protected:
    node m_root;
};

//node constructors and destructos
template<class T>
bin_tree<T>::node::node() : m_data(), m_left(nullptr), m_right(nullptr) { std::wcout<<__FILE__<<":"<<__LINE__<<": bin_tree<T>::node::node()\n"; }

template<class T>
bin_tree<T>::node::node(const T& d) : m_data((std::wcout<<__FILE__<<":"<<__LINE__<<": bin_tree<T>::node::node(const T& d = "<<d<<")\n", d)), m_left(nullptr), m_right(nullptr) {}

template<class T>
bin_tree<T>::node::node(T&& d) : m_data((std::wcout<<__FILE__<<":"<<__LINE__<<": bin_tree<T>::node::node(T&& d = "<<d<<")\n", std::forward<T>(d))), m_left(nullptr), m_right(nullptr) {}

template<class T>
bin_tree<T>::node::~node()
{std::wcout<<__FILE__<<":"<<__LINE__<<": bin_tree<T>::node::~node()\n";
    delete m_left;
    delete m_right;
}



//copy/move constructor, copy assignment (copy-and-swap style, thus includes move semantics)
template<class T>
bin_tree<T>::node::node(const node& other)
{std::wcout<<__FILE__<<":"<<__LINE__<<": bin_tree<T>::node::node(const node& other)\n";
    if(*this == other) return; //prevent self-assignment
    if(other.m_left != nullptr)
        m_left = new node(*other.m_left);
    else m_left = nullptr;

    if(other.m_right != nullptr)
        m_right = new node(*other.m_right);
    else m_right = nullptr;

    m_data = other.m_data;
}

template<class T>
bin_tree<T>::node::node(node&& other) : node((std::wcout<<__FILE__<<":"<<__LINE__<<": bin_tree<T>::node::node(node&& other)\n", 0)) //construct self as an empty instance and swap it out
{
    swap(*this, other);
}

template<class T>
typename bin_tree<T>::node& bin_tree<T>::node::operator=(node other)
{std::wcout<<__FILE__<<":"<<__LINE__<<": bin_tree<T>::node::operator=(node other)\n";
    swap(*this, other);

    return *this;
}

template<class T>
void bin_tree<T>::node::swap(node& a, node& b)
{std::wcout<<__FILE__<<":"<<__LINE__<<": bin_tree<T>::node::swap(node& a, node& b)\n";
    //std::swap tries to use move semantics if applicable (if "data" has move semantics)
    std::swap(a.m_data, b.m_data);
    std::swap(a.m_left, b.m_left);
    std::swap(a.m_right, b.m_right);
}



//node equality operators
template<class T>
bool bin_tree<T>::node::operator==(const node& other) const
{ std::wcout<<__FILE__<<":"<<__LINE__<<": bin_tree<T>::node::operator==(const node& other)\n"; 
    return m_data == other.m_data && m_left == other.m_left && m_right == other.m_right;
}

template<class T>
bool bin_tree<T>::node::operator!=(const node& other) const
{
    return !(*this == other);
}



//node value accessors and mutators
template<class T>
const T& bin_tree<T>::node::value() const { return m_data; }

template<class T>
void bin_tree<T>::node::set_value(const T& val) { m_data = val; }

template<class T>
void bin_tree<T>::node::set_value(T&& val) { m_data = std::forward<T>(val); }



//node child accessors and mutators
template<class T>
const typename bin_tree<T>::node *bin_tree<T>::node::left() const { return m_left; }

template<class T>
typename bin_tree<T>::node *bin_tree<T>::node::left() { return m_left; }

template<class T>
const typename bin_tree<T>::node *bin_tree<T>::node::right() const { return m_right; }

template<class T>
typename bin_tree<T>::node *bin_tree<T>::node::right() { return m_right; }

template<class T>
typename bin_tree<T>::node *bin_tree<T>::node::insert_left(const T& data, bool overwrite)
{std::wcout<<__FILE__<<":"<<__LINE__<<": bin_tree<T>::node::insert_left(const T& data = "<<data<<", bool overwrite = "<<overwrite<<")";
    if(!overwrite && m_left != nullptr){ std::wcout<<" --failed, would need overwrite\n"; return nullptr; }std::wcout<<"\n";
    if(m_left != nullptr) delete m_left;

    return m_left = new node(data);
}

template<class T>
typename bin_tree<T>::node *bin_tree<T>::node::insert_left(T&& data, bool overwrite)
{std::wcout<<__FILE__<<":"<<__LINE__<<": bin_tree<T>::node::insert_left(T&& data = "<<data<<", bool overwrite = "<<overwrite<<")";
    if(!overwrite && m_left != nullptr){ std::wcout<<" --failed, would need overwrite\n"; return nullptr; }std::wcout<<"\n";
    if(m_left != nullptr) delete m_left;

    return m_left = new node(std::forward<T>(data));
}

template<class T>
typename bin_tree<T>::node *bin_tree<T>::node::insert_right(const T& data, bool overwrite)
{std::wcout<<__FILE__<<":"<<__LINE__<<": bin_tree<T>::node::insert_right(const T& data = "<<data<<", bool overwrite = "<<overwrite<<")";
    if(!overwrite && m_right != nullptr){ std::wcout<<" --failed, would need overwrite\n"; return nullptr; }std::wcout<<"\n";
    if(m_right != nullptr) delete m_right;

    return m_right = new node(data);
}

template<class T>
typename bin_tree<T>::node *bin_tree<T>::node::insert_right(T&& data, bool overwrite)
{std::wcout<<__FILE__<<":"<<__LINE__<<": bin_tree<T>::node::insert_right(T&& data = "<<data<<", bool overwrite = "<<overwrite<<")";
    if(!overwrite && m_right != nullptr){ std::wcout<<" --failed, would need overwrite\n"; return nullptr; }std::wcout<<"\n";
    if(m_right != nullptr) delete m_right;

    return m_right = new node(std::forward<T>(data));
}



template<class T>
void bin_tree<T>::node::_print(const node *n, bool print_nulls, int max_width,
    std::wstring pre, int type)
{
    if(type != -1) //if we're not at the root node
    {
        std::wcout<<pre;
        if(type == 0) std::wcout<<L"├─";
        else std::wcout<<L"└─";
    }

    if(n == nullptr) //note: this can only happens if print_nulls is true or tree is empty (if stored as pointer)
    {
        std::wcout<<L"NULL\n";
        return;
    }

    std::wcout<<n->m_data<<L"\n";

    int pre_len = pre.length();
    if(pre_len + 2 > max_width)
    {
        std::wcout<<pre;
        if(type == 0) std::wcout<<L"│ └─...\n";
        else if(type == 1) std::wcout<<L"  └─...\n";

        return;
    }

    if(type == 0) pre += L"│ ";
    else if(type == 1) pre += L"  ";

    if(print_nulls || n->m_left != nullptr && n->m_right != nullptr)
    {
        _print(n->m_left, print_nulls, max_width, pre, 0);
        _print(n->m_right, print_nulls, max_width, pre, 1);
    }
    else
    {
        if(n->m_left != nullptr) _print(n->m_left, print_nulls, max_width, pre, 1);
        if(n->m_right != nullptr) _print(n->m_right, print_nulls, max_width, pre, 1);
    }
}



//constructors, destructor
template<class T>
bin_tree<T>::bin_tree() { std::wcout<<__FILE__<<":"<<__LINE__<<": bin_tree<T>::bin_tree()\n"; }

template<class T>
bin_tree<T>::bin_tree(const T& r) : m_root((std::wcout<<__FILE__<<":"<<__LINE__<<": bin_tree<T>::bin_tree(const T& r = "<<r<<")\n", r)) {}

template<class T>
bin_tree<T>::bin_tree(T&& r) : m_root((std::wcout<<__FILE__<<":"<<__LINE__<<": bin_tree<T>::bin_tree(T&& r = "<<r<<")\n", std::forward<T>(r))) {}

template<class T>
bin_tree<T>::~bin_tree() {std::wcout<<__FILE__<<":"<<__LINE__<<": bin_tree<T>::~bin_tree()\n";}



//copy/move constructor, copy assignment (copy-and-swap style, thus includes move semantics)
template<class T>
bin_tree<T>::bin_tree(const bin_tree<T>& other) : m_root((std::wcout<<__FILE__<<":"<<__LINE__<<": bin_tree<T>::bin_tree(const bin_tree<T>& other)\n", other.m_root)) {}

template<class T>
bin_tree<T>::bin_tree(bin_tree<T>&& other) : m_root((std::wcout<<__FILE__<<":"<<__LINE__<<": bin_tree<T>::bin_tree(bin_tree<T>&& other)\n", std::move(other.m_root))) {}

template<class T>
bin_tree<T>& bin_tree<T>::operator=(bin_tree<T> other)
{std::wcout<<__FILE__<<":"<<__LINE__<<": bin_tree<T>::operator=(bin_tree<T> other)\n";
    std::swap(m_root, other.m_root);

    return *this;
}



template<class T>
void bin_tree<T>::print(bool print_nulls, int max_width) const
{
    node::_print(&m_root, print_nulls, max_width);
}

#endif //BINTREE_D_H