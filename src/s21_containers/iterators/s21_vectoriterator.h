#ifndef S21_VECTORITERATOR_H
#define S21_VECTORITERATOR_H
#include "../include/s21_vector.h"

namespace s21 {
template <class T>
class vector<T>::iterator {
 private:
  using value_type = T;
  using reference = value_type&;
  using pointer = value_type*;
  using size_type = size_t;

 private:
  const vector<value_type>* container;  // Pointer to the list container
  size_type pos;

 public:
  iterator();
  iterator(const iterator& other);
  iterator(const vector<value_type>* container, size_type pos);

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

 public:
  inline size_t index() const { return this->pos; }
};
}  // namespace s21

#include "../impl/s21_vectoriterator.tpp"
#endif