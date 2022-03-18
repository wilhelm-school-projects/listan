#ifndef LIST_H
#define LIST_H

#include <initializer_list>
#include <memory>

template<typename T>
class List
{
public:
    List();
    List(List const &);
    List(List &&) noexcept;
    List(std::initializer_list<T>);

    List & operator=(List const &)&;        // Borde jag inte behöva skriva List<T> som returtyp 
    List & operator=(List &&)& noexcept;    // som jag är tvungen att göra i .tcc filen?  

    void push_front(T);
    void push_back(T);

    T back() const noexcept;
    T & back() noexcept;

    T front() const noexcept;
    T & front() noexcept;

    T & at(int idx);
    T const & at(int idx) const;

    int size() const noexcept;
    bool empty() const noexcept;

    void swap(List & other) noexcept;
private:
    struct Node                             // Jag behövde slänga in denna här för att lyckas göra head till en
    {                                       // unique_ptr av Node, hur kommer sig det?
        Node() = default;
        Node(Node* p, Node* n)            // Överflödig?
            : value{}, prev{p}, next{} 
        {
        }
        Node(T v, Node* p, Node* n)
            : value{v}, prev{p}, next{n} 
        {
        }
        T value;
        Node * prev;
        std::unique_ptr<Node> next;
    };
    std::unique_ptr<Node> head;
    Node* tail;
    int sz;
};

#include "List.tcc"

#endif //LIST_H
