#ifndef S21_LISTITERATOR_TPP
#define S21_LISTITERATOR_TPP
#include "../iterators/s21_listiterator.h"

template <typename T>
s21::list<T>::iterator::iterator() : container(nullptr), node(nullptr) {}

template <typename T>
s21::list<T>::iterator::iterator(const iterator& other) {
  this->container = other.container;
  this->node = other.node;
}

template <typename T>
s21::list<T>::iterator::iterator(const list<T>* container,
                                 s21::list<T>::Node* node) {
  this->container = container;
  this->node = node;
}

template <typename T>
s21::list<T>::iterator::~iterator() {
  this->container = nullptr;
  this->node = nullptr;
}

template <typename T>
typename s21::list<T>::iterator& s21::list<T>::iterator::operator=(
    const iterator& other) {
  this->container = other.container;
  this->node = other.node;
  return *this;
}

template <typename T>
typename s21::list<T>::iterator::reference s21::list<T>::iterator::operator*() {
  return this->node->data;
}

template <typename T>
typename s21::list<T>::iterator::pointer s21::list<T>::iterator::operator->() {
  return &this->node->data;
}

template <typename T>
typename s21::list<T>::iterator& s21::list<T>::iterator::operator++() {
  this->node = this->node->next;
  return *this;
}

template <typename T>
typename s21::list<T>::iterator s21::list<T>::iterator::operator++(int) {
  iterator iter = *this;
  this->node = this->node->next;
  return iter;
}

template <typename T>
typename s21::list<T>::iterator& s21::list<T>::iterator::operator--() {
  Node* temp = this->container->first_node;

  while (temp->next != this->node) {
    temp = temp->next;
  }

  this->node = temp;
  return *this;
}

template <typename T>
typename s21::list<T>::iterator s21::list<T>::iterator::operator--(int) {
  iterator iter = *this;
  Node* temp = this->container->first_node;

  while (temp->next != this->node) {
    temp = temp->next;
  }

  this->node = temp;
  return iter;
}

template <typename T>
bool s21::list<T>::iterator::operator==(const iterator& other) const {
  return (this->node == other.node);
}

template <typename T>
bool s21::list<T>::iterator::operator!=(const iterator& other) const {
  return (this->node != other.node);
}

#endif