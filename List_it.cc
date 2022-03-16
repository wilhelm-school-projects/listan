#include "List_it.h"
#include <iterator>
#include <utility>
#include <stdexcept>
#include <memory>

List::List()
    : head{ std::make_unique<Node>() }, tail{}, sz{}
{
    head->next = std::make_unique<Node>(0, head.get(), nullptr); 
    tail = head->next.get();
}

List::List(List const & other)
    : List{}
{
    for (Node * tmp {other.head->next.get()}; tmp != other.tail ; )
    {
        push_back(tmp->value);
        tmp = tmp->next.get();
    }
}
List::List(List && tmp) noexcept
    :List{}
{
    swap(tmp);
}
List::List(std::initializer_list<int> lst)
    : List{}
{
    for ( auto val : lst )
    {
        push_back(val);
    }
}

void List::push_front(int value)
{
    Node * old_first { head->next.get() };
    head->next = std::make_unique<Node>(value, head.get(), head->next.release());
    old_first->prev = head->next.get();
    ++sz;
}

void List::push_back(int value)
{
    Node * old_last { tail->prev };    
    old_last->next.release();    
    old_last->next = std::make_unique<Node>(value, old_last, tail);
    tail->prev = old_last->next.get();
    ++sz;
}

bool List::empty() const noexcept
{
    return head->next.get() == tail;
}

int List::back() const noexcept
{
    return tail->prev->value;
}
int & List::back() noexcept
{
    return tail->prev->value;
}

int List::front() const noexcept
{
    return head->next->value;
}
int & List::front() noexcept
{
    return head->next->value;
}

int & List::at(int idx)
{
    return const_cast<int &>(static_cast<List const *>(this)->at(idx));
}
int const & List::at(int idx) const
{
    if (idx >= sz)
        throw std::out_of_range{"Index not found"};
    Node * tmp {head->next.get()};
    while ( idx > 0 )
    {
        tmp = tmp->next.get();
        --idx;
    }
    return tmp->value;
}

int List::size() const noexcept
{
    return sz;
}

void List::swap(List & other) noexcept
{
    using std::swap;
    swap(head, other.head);
    swap(tail, other.tail);
    swap(sz, other.sz);
}

List & List::operator=(List const & rhs) & // Vad betyder denna &?
{
    List{rhs}.swap(*this);      // Skapar en temporär List med samma innehåll som rhs.
    return *this;               // Anropar swap och skickar med *this för att ge denna vad 
}                               // den temporära listan innehåller.

List & List::operator=(List && rhs)& noexcept
{
    swap(rhs);
    return *this;
}
    
List::List_Iterator List::begin()
{
    return List::List_Iterator{head->next.get()};
}

List::List_Iterator List::end()
{
    return List::List_Iterator{tail};
}

/* List_Iterator */

List::List_Iterator::List_Iterator(Node* const& node_ptr)
    : curr_ptr{node_ptr}
{
}

List::List_Iterator::value_type& List::List_Iterator::operator*()
{
    return curr_ptr->value;
}

bool List::List_Iterator::operator==(List::List_Iterator const& rhs)
{
    return curr_ptr == rhs.curr_ptr;
}
bool List::List_Iterator::operator!=(List::List_Iterator const& rhs)
{
    return !(*this == rhs);
}

List::List_Iterator& List::List_Iterator::operator++()      // pre
{
    this->curr_ptr = this->curr_ptr->next.get();
    return *this;                                           
}     
List::List_Iterator List::List_Iterator::operator++(int)    // post
{
    List::List_Iterator old{*this};
    operator++();
    return old;
}

List::List_Iterator& List::List_Iterator::operator--()
{
    this->curr_ptr = this->curr_ptr->prev;
    return *this;      
}
List::List_Iterator List::List_Iterator::operator--(int)
{
    List::List_Iterator old{*this};
    operator--();
    return old;
}





























