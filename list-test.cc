
#include "List.h"

#include "catch.hpp"
#include <iterator>
#include <iostream>
#include <string>

using namespace std;
using namespace List_NS;

TEST_CASE( "Not integer type" )
{
    List_NS::List<string> lst{"cpp", "är", "kul"};
    CHECK(lst.at(2) == "kul");
    CHECK(lst.size() == 3);
    List_NS::List<string> l2;
    l2 = lst;
    CHECK(l2.size() == lst.size());
    CHECK(l2.front() == lst.front());
    CHECK(l2.back() == lst.back());
} 

TEST_CASE( "Create list" )
{
    List<int> lst{1,4,2,6,8,9};
    CHECK(lst.at(2) == 2);
    CHECK(lst.size() == 6);
    List<int> l2;
    l2 = lst;
    CHECK(l2.size() == lst.size());
    CHECK(l2.front() == lst.front());
    CHECK(l2.back() == lst.back());
} 

TEST_CASE( "Copy constructor" )
{
    List<int> lst1{1,4,2};
    List<int> lst2{lst1};
    
    CHECK(lst2.at(0) == lst1.at(0));
    CHECK(lst2.at(1) == lst1.at(1));
    CHECK(lst2.at(2) == lst1.at(2));
}

TEST_CASE( "Default constructor" )
{
    List<int> empty_list{}, nonempty_list{1};
    CHECK(empty_list.empty() == true);
    CHECK(nonempty_list.empty() == false);
}

TEST_CASE( "Move constructor" )
{
    List<int> list{std::move(List<int>{2,3,4})};
    CHECK(list.at(0) == 2);
    CHECK(list.at(1) == 3);
    CHECK(list.at(2) == 4);
}

TEST_CASE( "push_front/back" )
{
    List<int> list{2,3,4};
    list.push_front(1);
    list.push_back(5);
    CHECK(list.at(0) == 1);
    CHECK(list.at(4) == 5);
}

TEST_CASE( "const back/front" )
{
    const List<int> list{1,2,3,4,5};
    CHECK(list.back() == 5);
    CHECK(list.front() == 1);
}

TEST_CASE( "non-const back/front" )
{
    List<int> list{1,2};
    list.back() = 4;
    list.front() = 3;
    CHECK(list.front() == 3);
    CHECK(list.back() == 4);
}

TEST_CASE( "const at" )
{
    const List<int> list{1};
    CHECK(list.at(0) == 1);
}

TEST_CASE( "non-const at" )
{
    List<int> list{1};
    list.at(0) = 2;
    CHECK(list.front() == 2);
}

TEST_CASE( "size" )
{
    List<int> list{1,2,3,4,5,6};
    CHECK(list.size() == 6);
}

TEST_CASE( "swap" )
{
    List<int> list1{1,2}, list2{3,4};
    list1.swap(list2);
    CHECK(list1.at(0) == 3);
    CHECK(list1.at(1) == 4);
    CHECK(list2.at(0) == 1);
    CHECK(list2.at(1) == 2);
}

TEST_CASE( "Copy assignment" )
{
    List<int> list1{1,2}, list2{};
    list2 = list1;
    CHECK(list1.at(0) == 1);
    CHECK(list1.at(1) == 2);
    CHECK(list2.at(0) == 1);
    CHECK(list2.at(1) == 2);
}

TEST_CASE( "Move assignment " )
{
    List<int> list2{};
    list2 = std::move(List<int>{1,2});
    CHECK(list2.at(0) == 1);
    CHECK(list2.at(1) == 2);
}

/* Iterator tests */

TEST_CASE( "begin/end" )
{
    List<int> lst{1,4,2,6,8,9};
    auto it {lst.begin()};
    *it = 3; 
    CHECK(*lst.begin() == 3);
    CHECK(*lst.end() == 0); 
}

TEST_CASE( "Equal/not equal" )
{
    List<int> lst {1,4,2,6,8,9};
    auto it1 {lst.begin()};
    auto it2 {lst.begin()};
    auto it3 {lst.end()};

    CHECK(it1 == it2);
    CHECK(it1 != it3);
}

TEST_CASE( "pre/post increment" )
{
    List<int> lst {1,4,2,6,8,9};
    auto it{lst.begin()};

    CHECK(*(it++) == 1);    
    CHECK(*it == 4);
    CHECK(*(++it) == 2);    
}

TEST_CASE( "pre/post decrement" )
{
    List<int> lst {1,4,2,6,8,9};
    auto it{lst.end()};

    CHECK(*(it--) == 0);    
    CHECK(*it == 9);
    CHECK(*(--it) == 8);    
}

TEST_CASE( "operator->" )
{
    List<std::string> lst {"ord", "består", "av", "bokstäver"};
    auto it{lst.begin()};
    CHECK(it->size() == 3);
}

TEST_CASE( "reversed iterations" )                  
{
    List<int> lst{2,3,1,5};
    auto rb { make_reverse_iterator(lst.end()) };       
    auto re { make_reverse_iterator(lst.begin()) };
    for ( auto it = rb; it != re; ++it )
    {
        cout << *it << ' ';
    }

}













































