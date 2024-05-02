#ifndef S21_LIST_H
#define S21_LIST_H
#include <exception>
#include <initializer_list>
#include <limits>

namespace s21 {
template <class T>
class list {
 public:
  class iterator;

 private:
  /* List Member type */

  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using const_iterator = const iterator;
  using size_type = size_t;

  struct Node {
    T data;
    Node *next;
  };

 private:
  Node *first_node;
  Node *last_node;
  size_type m_size;

 public:
  /* List Functions */

  // default constructor, creates empty list 
  list();
  // parameterized constructor, creates the list of size n
  explicit list(size_type n);
  // initializer list constructor, creates list initizialized
  // using std::initializer_list
  list(std::initializer_list<value_type> const &items);
  // copy constructor
  list(const list &l);
  // move constructor
  list(list &&l);
  // destructor
  ~list();
  // assignment operator overload for moving object
  list operator=(list &&l);

  /* List Element access */

  // access the first element
  const_reference front() const;
  // access the last element
  const_reference back() const;

  /* List Iterators */

  // returns an iterator to the beginning
  iterator begin();
  // returns an iterator to the end
  iterator end();

  /* List Capacity */

  // checks whether the container is empty
  inline bool empty() const { return !this->m_size; }
  // returns the number of elements
  inline size_type size() const { return this->m_size; }
  // returns the maximum possible number of elements
  inline size_type max_size() const {
    return std::numeric_limits<size_type>::max() / sizeof(Node);
  }

  /* List Modifiers */

  // clears the contents
  void clear();
  // inserts element into concrete pos and returns the iterator that points to
  // the new element
  iterator insert(iterator pos, const_reference value);
  // erases element at pos
  void erase(iterator pos);
  // adds an element to the end
  void push_back(const_reference value);
  // removes the last element
  void pop_back();
  // adds an element to the head
  void push_front(const_reference value);
  // removes the first element
  void pop_front();
  // swaps the contents
  void swap(list &other);
  // merges two sorted lists
  void merge(list &other);
  // transfers elements from list other starting from pos
  void splice(const_iterator pos, list &other);
  // reverses the order of the elements
  void reverse();
  // removes consecutive duplicate elements
  void unique();
  // sorts the elements
  void sort();

 public:
  value_type *to_array();
  void sort_array(value_type *arr);
  void array_to_list(value_type *arr, size_type len);
  void reverse_array(value_type *arr);
  void unique_array(value_type *arr, size_type *len);
};
}  // namespace s21

#include "../impl/s21_list.tpp"
#include "../iterators/s21_listiterator.h"
#endif