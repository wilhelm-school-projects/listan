#ifndef LIST_H
#define LIST_H

#include <initializer_list>
#include <memory>

namespace List_NS
{
    template<typename T>
    class List
    {
    private:
        struct Node                             // Jag behövde slänga in denna här för att lyckas göra head till en
        {                                       // unique_ptr av Node, hur kommer sig det?
            Node() = default;
            Node(Node* p, Node* n)            
                : value{}, prev{p}, next{n} 
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

        class List_Iterator         // Jag kunde inte "fördeklarera" (class List_Iterator;) i
        {                           // Den publika delen och sedan lägga denna i private delen
        public:                     // när den private delen låg under den publika, varför?
            List_Iterator(Node* const& node_ptr);
            typedef std::bidirectional_iterator_tag iterator_category;
            typedef T                               value_type;
            typedef value_type                      difference_type;
            typedef value_type*                     pointer;
            typedef value_type&                     reference;

            List_Iterator& operator++();     //pre
            List_Iterator operator++(int);   //post
            List_Iterator& operator--();
            List_Iterator operator--(int);
            
            reference operator*();
            pointer operator->();
            
            bool operator==(List_Iterator const& rhs);
            bool operator!=(List_Iterator const& rhs);

        private:
            Node* curr_ptr;
        };

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

        List_Iterator begin();  //returna List_Iterator& ?
        List_Iterator end();

    private:
        std::unique_ptr<Node> head;
        Node* tail;
        int sz;
    };
}

#include "List.tcc"

#endif //LIST_H
