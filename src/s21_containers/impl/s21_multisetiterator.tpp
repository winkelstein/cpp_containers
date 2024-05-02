#ifndef S21_MULTISETITERATOR_TPP
#define S21_MULTISETITERATOR_TPP
#include "../iterators/s21_multisetiterator.h"

template <typename T>
s21::multiset<T>::iterator::iterator() : container(nullptr), pos(-1) {}

template <typename T>
s21::multiset<T>::iterator::iterator(const iterator& other) {
  this->container = other.container;
  this->pos = other.pos;
}

template <typename T>
s21::multiset<T>::iterator::iterator(const multiset<value_type>* container,
                                     size_type pos) {
  this->container = container;
  this->pos = pos;
}

template <typename T>
s21::multiset<T>::iterator::~iterator() {
  this->container = nullptr;
  this->pos = 0;
}

template <typename T>
typename s21::multiset<T>::iterator& s21::multiset<T>::iterator::operator=(
    const iterator& other) {
  this->container = other.container;
  this->pos = other.pos;

  return *this;
}

template <typename T>
typename s21::multiset<T>::iterator::reference
s21::multiset<T>::iterator::operator*() {
  return this->container->multiset_elements[this->pos];
}

template <typename T>
typename s21::multiset<T>::iterator::pointer
s21::multiset<T>::iterator::operator->() {
  return &this->container->multiset_elements[this->pos];
}

template <typename T>
typename s21::multiset<T>::iterator& s21::multiset<T>::iterator::operator++() {
  this->pos++;
  return *this;
}

template <typename T>
typename s21::multiset<T>::iterator s21::multiset<T>::iterator::operator++(
    int) {
  iterator iter = *this;
  this->pos++;
  return iter;
}

template <typename T>
typename s21::multiset<T>::iterator& s21::multiset<T>::iterator::operator--() {
  this->pos--;
  return *this;
}

template <typename T>
typename s21::multiset<T>::iterator s21::multiset<T>::iterator::operator--(
    int) {
  iterator iter = *this;
  this->pos--;
  return iter;
}

template <typename T>
bool s21::multiset<T>::iterator::operator==(const iterator& other) const {
  return (this->container == other.container) && (this->pos == other.pos);
}

template <typename T>
bool s21::multiset<T>::iterator::operator!=(const iterator& other) const {
  return (this->container != other.container) || (this->pos != other.pos);
}

#endif