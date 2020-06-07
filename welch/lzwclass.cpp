#include <iostream>
#include <algorithm>
#include <locale>

#include "bintree.d.h"

class lzw_tree : public bin_tree<int>
{
    friend class node;
public:
    lzw_tree() : bin_tree(-1), current(&m_root) {}

    bool insert(int bit)
    {
        if(bit == 0)
            if(current->insert_left(0) == nullptr)
                current = current->left();
            else current = &m_root;
        if(bit == 1)
            if(current->insert_right(1) == nullptr)
                current = current->right();
            else current = &m_root;

        return false;
    }

private:
    node *current;
};

int main(int argc, char **argv)
{
    std::setlocale(LC_ALL, "");

    lzw_tree t;

    t.insert(0);
    t.insert(0);
    t.insert(0);
    t.insert(1);
    std::wcout<<"***";
    lzw_tree t2;
    t2 = std::move(t);

    return 0;

    lzw_tree tree;
    char in;
    while(!std::cin.eof())
    {
        while(true)
        {
            std::cin.read(&in, 1);
            if(in == '\n') break;

            tree.insert(in == '1' ? 1 : 0);
        }

        tree.print();
    }

    return 0;
}
