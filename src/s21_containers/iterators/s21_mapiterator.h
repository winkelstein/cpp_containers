#ifndef S21_MAPITERATOR_H
#define S21_MAPITERATOR_H
#include "../include/s21_map.h"

namespace s21 {
template <class K, class T>
class map<K, T>::iterator {
 private:
  using key_type = K;
  using mapped_type = T;
  using value_type = std::pair<const key_type, mapped_type>;
  using reference = value_type&;
  using pointer = value_type*;
  using size_type = size_t;

 private:
  const map<K, T>* container;
  map<K, T>::Node* node;

 public:
  iterator();
  iterator(const iterator& other);
  iterator(const map<K, T>* container, map<K, T>::Node* node);

  ~iterator();

  iterator& operator=(const iterator& other);

  value_type operator*();

  iterator& operator++();    // Prefix increment
  iterator operator++(int);  // Postfix increment
  iterator& operator--();    // Prefix decrement
  iterator operator--(int);  // Postfix decrement

  bool operator==(const iterator& other) const;
  bool operator!=(const iterator& other) const;

 public:
  inline Node* get_node() const { return this->node; }
};
}  // namespace s21

#include "../impl/s21_mapiterator.tpp"
#endif