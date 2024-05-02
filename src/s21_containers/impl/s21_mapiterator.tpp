#ifndef S21_MAPITERATOR_TPP
#define S21_MAPITERATOR_TPP
#include "../iterators/s21_mapiterator.h"

template <typename K, typename T>
s21::map<K, T>::iterator::iterator() : container(nullptr), node(nullptr) {}

template <typename K, typename T>
s21::map<K, T>::iterator::iterator(const iterator& other) {
  this->container = other.container;
  this->node = other.node;
}

template <typename K, typename T>
s21::map<K, T>::iterator::iterator(const map<K, T>* container,
                                   map<K, T>::Node* node) {
  this->container = container;
  this->node = node;
}

template <typename K, typename T>
s21::map<K, T>::iterator::~iterator() {
  this->container = nullptr;
  this->node = nullptr;
}

template <typename K, typename T>
typename s21::map<K, T>::iterator& s21::map<K, T>::iterator::operator=(
    const iterator& other) {
  this->container = other.container;
  this->node = other.node;

  return *this;
}

template <typename K, typename T>
typename s21::map<K, T>::iterator::value_type
s21::map<K, T>::iterator::operator*() {
  std::pair<const key_type, mapped_type> pr =
      std::make_pair(this->node->key, this->node->value);
  return pr;
}

template <typename K, typename T>
typename s21::map<K, T>::iterator& s21::map<K, T>::iterator::operator++() {
  if (!this->node) return *this;

  if (this->node->right) {
    this->node = this->node->right;
    while (this->node->left) this->node = this->node->left;
  } else if (this->node->parent) {
    Node* parent = this->node->parent;
    while (parent && this->node == parent->right) {
      this->node = parent;
      parent = parent->parent;
    }
    this->node = parent;
  }

  return *this;
}

template <typename K, typename T>
typename s21::map<K, T>::iterator s21::map<K, T>::iterator::operator++(int) {
  iterator iter = *this;

  if (!this->node) return *this;

  if (this->node->right) {
    this->node = this->node->right;
    while (this->node->left) this->node = this->node->left;
  } else {
    Node* parent = this->node->parent;
    while (parent && this->node == parent->right) {
      this->node = parent;
      parent = parent->parent;
    }
    this->node = parent;
  }

  return iter;
}

template <typename K, typename T>
typename s21::map<K, T>::iterator& s21::map<K, T>::iterator::operator--() {
  if (!this->node) {
    this->node = this->container->root_node;
    while (this->node && this->node->right) this->node = this->node->right;
    if (!this->node) return *this;
    return *this;
  }

  if (this->node->left) {
    this->node = this->node->left;
    while (this->node->right) this->node = this->node->right;
  } else {
    Node* parent = this->node->parent;
    while (parent && this->node == parent->left) {
      this->node = parent;
      parent = parent->parent;
    }
    this->node = parent;
  }

  return *this;
}

template <typename K, typename T>
typename s21::map<K, T>::iterator s21::map<K, T>::iterator::operator--(int) {
  iterator iter = *this;
  if (!this->node) {
    this->node = this->container->root_node;
    while (this->node && this->node->right) this->node = this->node->right;
    if (!this->node) return *this;
    return iter;
  }

  if (this->node->left) {
    this->node = this->node->left;
    while (this->node->right) this->node = this->node->right;
  } else {
    Node* parent = this->node->parent;
    while (parent && this->node == parent->left) {
      this->node = parent;
      parent = parent->parent;
    }
    this->node = parent;
  }

  return iter;
}

template <typename K, typename T>
bool s21::map<K, T>::iterator::operator==(const iterator& other) const {
  return (this->container == other.container) && (this->node == other.node);
}

template <typename K, typename T>
bool s21::map<K, T>::iterator::operator!=(const iterator& other) const {
  return (this->container != other.container) || (this->node != other.node);
}

#endif