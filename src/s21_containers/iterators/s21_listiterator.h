#ifndef S21_LISTITERATOR_H
#define S21_LISTITERATOR_H
#include "../include/s21_list.h"

namespace s21 {
template <class T>
class list<T>::iterator {
 private:
  using value_type = T;
  using reference = value_type&;
  using pointer = value_type*;
  using size_type = size_t;

 private:
  const list<value_type>* container;  // Pointer to the list container
  s21::list<T>::Node* node;

 public:
  iterator();
  iterator(const iterator& other);
  iterator(const list<value_type>* container, s21::list<T>::Node* node);

  ~iterator();

  iterator& operator=(const iterator& other);

  reference operator*();
  pointer operator->();

  iterator& operator++();    // Prefix increment
  iterator operator++(int);  // Postfix increment
  iterator& operator--();    // Prefix decrement
  iterator operator--(int);  // Postfix decrement

  bool operator==(const iterator& other) const;
  bool operator!=(const iterator& other) const;
};
}  // namespace s21

#include "../impl/s21_listiterator.tpp"
#endif