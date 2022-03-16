#ifndef LIST_IT_H
#define LIST_IT_H

#include <initializer_list>
#include <memory>
#include <iterator>

class List
{
private:
    struct Node                             // Jag behövde slänga in denna här för att lyckas göra head till en
    {                                       // unique_ptr av Node, hur kommer sig det?
        Node() = default;
        Node(int v, Node* p, Node* n)
            : value{v}, prev{p}, next{n} 
        {
        }
        int value;
        Node * prev;
        std::unique_ptr<Node> next;
    };

    class List_Iterator         // Jag kunde inte "fördeklarera" (class List_Iterator;) i
    {                           // Den publika delen och sedan lägga denna i private delen
    public:                     // när den private delen låg under den publika, varför?
        List_Iterator(Node* const& node_ptr);
        typedef std::bidirectional_iterator_tag iterator_category;
        typedef int                             value_type;
        typedef value_type                      difference_type;
        typedef value_type*                     pointer;
        typedef value_type&                     reference;

        List_Iterator& operator++();     //pre
        List_Iterator operator++(int);   //post
        List_Iterator& operator--();
        List_Iterator operator--(int);
        
        value_type& operator*();
        
        bool operator==(List_Iterator const& rhs);
        bool operator!=(List_Iterator const& rhs);

    private:
        Node* curr_ptr;
    };

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

    List_Iterator begin();  //returna List_Iterator& ?
    List_Iterator end();

private:
    std::unique_ptr<Node> head;
    Node* tail;
    int sz;
};

#endif //LIST_H
