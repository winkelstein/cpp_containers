#ifndef S21_VECTORITERATOR_TPP
#define S21_VECTORITERATOR_TPP
#include "../iterators/s21_vectoriterator.h"

template <typename T>
s21::vector<T>::iterator::iterator() : container(nullptr), pos(-1) {}

template <typename T>
s21::vector<T>::iterator::iterator(const iterator& other) {
  this->container = other.container;
  this->pos = other.pos;
}

template <typename T>
s21::vector<T>::iterator::iterator(const vector<value_type>* container,
                                   size_type pos) {
  this->container = container;
  this->pos = pos;
}

template <typename T>
s21::vector<T>::iterator::~iterator() {
  this->container = nullptr;
  this->pos = 0;
}

template <typename T>
typename s21::vector<T>::iterator& s21::vector<T>::iterator::operator=(
    const iterator& other) {
  this->container = other.container;
  this->pos = pos;

  return *this;
}

template <typename T>
typename s21::vector<T>::iterator::reference
s21::vector<T>::iterator::operator*() {
  return this->container->m_arr[this->pos];
}

template <typename T>
typename s21::vector<T>::iterator::pointer
s21::vector<T>::iterator::operator->() {
  return &this->container->m_arr[this->pos];
}

template <typename T>
typename s21::vector<T>::iterator& s21::vector<T>::iterator::operator++() {
  this->pos++;
  return *this;
}

template <typename T>
typename s21::vector<T>::iterator s21::vector<T>::iterator::operator++(int) {
  iterator iter = *this;
  this->pos++;
  return iter;
}

template <typename T>
typename s21::vector<T>::iterator& s21::vector<T>::iterator::operator--() {
  this->pos--;
  return *this;
}

template <typename T>
typename s21::vector<T>::iterator s21::vector<T>::iterator::operator--(int) {
  iterator iter = *this;
  this->pos--;
  return iter;
}

template <typename T>
bool s21::vector<T>::iterator::operator==(const iterator& other) const {
  return (this->container == other.container) && (this->pos == other.pos);
}

template <typename T>
bool s21::vector<T>::iterator::operator!=(const iterator& other) const {
  return (this->container != other.container) || (this->pos != other.pos);
}

#endif