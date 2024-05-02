#ifndef S21_STACK_H
#define S21_STACK_H

#include <initializer_list>
#include <utility>

namespace s21 {
template <class T>
class stack {
 private:
  /* Stack Member type */
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

  struct Node {
    value_type data;
    Node *next;

    Node() : data(), next(nullptr) {}
  };

 private:
  Node *m_top;
  size_type m_size;

 public:
  /* Stack Member functions */

  // default constructor, creates empty stack
  stack();
  // initializer list constructor, creates stack initizialized using
  // std::initializer_list
  stack(std::initializer_list<value_type> const &items);
  // copy constructor
  stack(const stack &s);
  // move constructor
  stack(stack &&s);
  // destructor
  ~stack();
  // assignment operator overload for moving object
  stack operator=(stack &&s);

  /* Stack Element access */

  // accesses the top element
  const_reference top();

  /* Stack Capacity */

  // checks whether the container is empty
  bool empty();
  // returns the number of elements
  size_type size();

  /* Stack Modifiers */

  // inserts element at the top
  void push(const_reference value);
  // removes the top element
  void pop();
  // swaps the contents
  void swap(stack &other);
};
}  // namespace s21

#include "../impl/s21_stack.tpp"
#endif