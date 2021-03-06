#include <iterator>
#include <utility>
#include <stdexcept>
#include <memory>
namespace List_NS
{
    template<typename T>
    List<T>::List()
        : head{ std::make_unique<Node>() }, tail{}, sz{}
    {
        head->next = std::make_unique<Node>(head.get(), nullptr);   
        tail = head->next.get();                                    
    }                                                              

    template<typename T>
    List<T>::List(List const & other)  
        : List{}
    {
        for (Node * tmp {other.head->next.get()}; tmp != other.tail ; )
        {
            push_back(tmp->value);
            tmp = tmp->next.get();
        }
    }
    template<typename T>
    List<T>::List(List && tmp) noexcept
        :List{}
    {
        swap(tmp);
    }
    template<typename T>
    List<T>::List(std::initializer_list<T> lst)
        : List{}
    {
        for ( auto const& val : lst )       
        {
            push_back(val);
        }
    }

    template<typename T>
    void List<T>::push_front(T const& value) 
    {
        Node * old_first { head->next.get() };
        head->next = std::make_unique<Node>(value, head.get(), head->next.release());   
        old_first->prev = head->next.get();
        ++sz;
    }

    template<typename T>
    void List<T>::push_back(T const& value)
    {
        Node * old_last { tail->prev };    
        old_last->next.release();    
        old_last->next = std::make_unique<Node>(value, old_last, tail);
        tail->prev = old_last->next.get();
        ++sz;
    }

    template<typename T>
    bool List<T>::empty() const noexcept
    {
        return head->next.get() == tail;
    }

    template<typename T>
    T List<T>::back() const noexcept
    {
        return tail->prev->value;
    }
    template<typename T>
    T & List<T>::back() noexcept
    {
        return tail->prev->value;
    }

    template<typename T>
    T List<T>::front() const noexcept
    {
        return head->next->value;
    }
    template<typename T>
    T & List<T>::front() noexcept
    {
        return head->next->value;
    }

    template<typename T>
    T & List<T>::at(int idx)
    {
        return const_cast<T &>(static_cast<List const *>(this)->at(idx));
    }
    template<typename T>
    T const & List<T>::at(int idx) const
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

    template<typename T>
    int List<T>::size() const noexcept
    {
        return sz;
    }

    template<typename T>
    void List<T>::swap(List & other) noexcept
    {
        using std::swap;
        swap(head, other.head);
        swap(tail, other.tail);
        swap(sz, other.sz);
    }

    template<typename T>
    List<T> & List<T>::operator=(List const & rhs) & 
    {
        List{rhs}.swap(*this);      
        return *this;              
    }                               

    template<typename T>
    List<T> & List<T>::operator=(List && rhs)& noexcept
    {
        swap(rhs);
        return *this;
    }

    template<typename T>
    // I c++20 kr??vs inte typename f??re returtyp
    typename List<T>::List_Iterator List<T>::begin()
    {
        return List<T>::List_Iterator{head->next.get()};
    }

    template<typename T>
    typename List<T>::List_Iterator List<T>::end()
    {
        return List<T>::List_Iterator{tail};
    }

    /* List_Iterator */

    template<typename T>
    List<T>::List_Iterator::List_Iterator(Node* const& node_ptr)
        : curr_ptr{node_ptr}
    {
    }


    template<typename T>
    bool List<T>::List_Iterator::operator==(List<T>::List_Iterator const& rhs) const
    {
        return curr_ptr == rhs.curr_ptr;
    }
    template<typename T>
    bool List<T>::List_Iterator::operator!=(List<T>::List_Iterator const& rhs) const
    {
        return !(*this == rhs);
    }

    template<typename T>
    typename List<T>::List_Iterator& List<T>::List_Iterator::operator++()      // pre
    {
        this->curr_ptr = this->curr_ptr->next.get();
        return *this;                                           
    }     
    template<typename T>
    typename List<T>::List_Iterator List<T>::List_Iterator::operator++(int)    // post
    {
        List<T>::List_Iterator old{*this};
        operator++();
        return old;
    }

    template<typename T>
    typename List<T>::List_Iterator& List<T>::List_Iterator::operator--()
    {
        this->curr_ptr = this->curr_ptr->prev;
        return *this;      
    }
    template<typename T>
    typename List<T>::List_Iterator List<T>::List_Iterator::operator--(int)
    {
        List<T>::List_Iterator old{*this};
        operator--();
        return old;
    }

    template<typename T>
    typename List<T>::List_Iterator::value_type& List<T>::List_Iterator::operator*()    
    {                                                                                   
        return curr_ptr->value;
    }

    template<typename T>
    typename List<T>::List_Iterator::pointer List<T>::List_Iterator::operator->()
    {
        return &(operator*());
    }
}