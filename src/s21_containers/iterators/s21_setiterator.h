#ifndef S21_SETITERATOR_H
#define S21_SETITERATOR_H
#include "../include/s21_set.h"

namespace s21 {
template <class T>
class set<T>::iterator {
 private:
  using value_type = T;
  using reference = value_type&;
  using pointer = value_type*;
  using size_type = size_t;

 private:
  const set<value_type>* container;  // Pointer to the list container

 public:
  size_type pos;
  iterator();
  iterator(const iterator& other);
  iterator(const set<value_type>* container, size_type pos);

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

#include "../impl/s21_setiterator.tpp"
// #include "../impl/s21_set.tpp"
#endif