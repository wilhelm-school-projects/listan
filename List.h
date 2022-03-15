#ifndef LIST_H
#define LIST_H

#include <initializer_list>
#include <memory>

class List
{
public:
    List();
    List(List const &);
    List(List &&) noexcept;
    List(std::initializer_list<int>);

    List & operator=(List const &)&;
    List & operator=(List &&)& noexcept;

    void push_front(int);
    void push_back(int);

    int back() const noexcept;
    int & back() noexcept;

    int front() const noexcept;
    int & front() noexcept;

    int & at(int idx);
    int const & at(int idx) const;

    int size() const noexcept;
    bool empty() const noexcept;

    void swap(List & other) noexcept;
private:
    struct Node                             // Jag behövde slänga in denna här för att lyckas göra head till en
    {                                       // unique_ptr av Node, hur kommer sig det?
        Node() = default;
        Node(int v, Node* p)            // Överflödig?
            : value{v}, prev{p}, next{} 
        {
        }
        Node(int v, Node* p, Node* n)
            : value{v}, prev{p}, next{n} 
        {
        }
        int value;
        Node * prev;
        std::unique_ptr<Node> next;
    };
    std::unique_ptr<Node> head;
    Node* tail;
    int sz;
};

#endif //LIST_H
