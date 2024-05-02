#ifndef S21_QUEUE_H
#define S21_QUEUE_H

#include <initializer_list>
#include <utility>

namespace s21 {
template <class T>
class queue {
 private:
  /* Queue Member type */
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
  Node *node_back;
  Node *node_front;
  size_type m_size;

 public:
  /* Queue Member functions */

  // default constructor, creates empty queue
  queue();

  // initializer list constructor, creates queue initizialized using
  // std::initializer_list
  queue(std::initializer_list<value_type> const &items);
  // copy constructor
  queue(const queue &q);
  // move constructor
  queue(queue &&q);
  // destructor
  ~queue();
  // assignment operator overload for moving object
  queue operator=(queue &&q);

  /* Queue Element access */

  // access the first element
  const_reference front();
  // access the last element
  const_reference back();

  /* Queue Capacity */

  // checks whether the container is empty
  bool empty();
  // returns the number of elements
  size_type size();

  /* Queue Modifiers */

  // inserts element at the end
  void push(const_reference value);
  // removes the first element
  void pop();
  // swaps the contents
  void swap(queue &other);
};
}  // namespace s21

#include "../impl/s21_queue.tpp"
#endif