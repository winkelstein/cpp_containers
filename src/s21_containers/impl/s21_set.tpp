#ifndef S21_SET_TPP
#define S21_SET_TPP
#include "../include/s21_set.h"

template <typename T>
s21::set<T>::set() {
  this->s_size = 0;
  this->set_elements = nullptr;
}

template <typename T>
s21::set<T>::set(std::initializer_list<value_type> const& items) : s_size(0) {
  this->set_elements = new T[items.size()];
  for (const value_type* iter = items.begin(); iter != items.end(); ++iter) {
    this->insert(*iter);
  }
  this->sort();
}

template <typename T>
s21::set<T>::set(const set& s) : s_size(s.s_size) {
  this->set_elements = new T[s.s_size];
  for (size_t i = 0; i < s.s_size; ++i) {
    this->set_elements[i] = s.set_elements[i];
  }
}
template <typename T>
s21::set<T>::set(set&& s) : s_size(s.s_size) {
  this->set_elements = s.set_elements;
  s.s_size = 0;
  s.set_elements = nullptr;
}

template <typename T>
s21::set<T>::~set() {
  this->clear();
}
template <typename T>
s21::set<T> s21::set<T>::operator=(set&& s) {
  this->clear();
  this->s_size = s.s_size;
  this->set_elements = s.set_elements;
  s.s_size = 0;
  s.set_elements = nullptr;
  return *this;
}

template <typename T>
typename s21::set<T>::iterator s21::set<T>::begin() {
  if (s_size == 0) {
    return iterator();
  }

  return iterator(this, 0);
}

template <typename T>
typename s21::set<T>::iterator s21::set<T>::end() {
  if (s_size == 0) {
    return iterator();
  }

  return iterator(this, this->s_size);
}

template <typename T>
bool s21::set<T>::empty() {
  return this->s_size == 0 ? true : false;
}
template <typename T>
typename s21::set<T>::size_type s21::set<T>::size() {
  return this->s_size;
}

template <typename T>
typename s21::set<T>::size_type s21::set<T>::max_size() {
  return std::numeric_limits<size_type>::max() / sizeof(T);
}

template <typename T>
void s21::set<T>::clear() {
  delete[] this->set_elements;
  this->set_elements = nullptr;
  this->s_size = 0;
}

template <typename T>
void s21::set<T>::erase(iterator pos) {
  if (pos.pos < this->begin().pos || pos.pos >= this->end().pos) {
    throw std::out_of_range("iterator is out of bounds");
  }
  size_t index = pos.pos;
  for (size_t i = index; i < s_size - 1; ++i) {
    set_elements[i] = set_elements[i + 1];
  }
  --this->s_size;
}

template <typename T>
typename s21::set<T>::iterator s21::set<T>::find(const key_type& key) {
  for (size_t i = 0; i < s_size; ++i) {
    if (set_elements[i] == key) {
      return iterator(this, i);
    }
  }
  return end();
}

template <typename T>
void s21::set<T>::swap(set& other) {
  std::swap(this->s_size, other.s_size);
  std::swap(this->set_elements, other.set_elements);
}

template <typename T>
bool s21::set<T>::contains(const key_type& key) {
  return this->find(key) != this->end() ? true : false;
}

template <typename T>
std::pair<typename s21::set<T>::iterator, bool> s21::set<T>::insert(
    const value_type& value) {
  iterator it = this->find(value);
  if (it != this->end()) {
    return std::make_pair(this->find(value), false);
  }
  T* new_set_elements = new T[s_size + 1];
  size_t i = 0;
  for (; i < s_size; ++i) {
    new_set_elements[i] = set_elements[i];
  }
  new_set_elements[i] = value;
  delete[] set_elements;
  set_elements = new_set_elements;
  ++this->s_size;
  return std::make_pair(iterator(this, i), true);
}

template <typename T>
void s21::set<T>::merge(set& other) {
  if (this == &other) {
    return;
  }
  for (size_t i = 0; i < other.s_size; ++i) {
    if (this->find(other.set_elements[i]) == this->end()) {
      this->insert(other.set_elements[i]);
    }
  }
  this->sort();
  other.clear();
}

template <typename T>
void s21::set<T>::sort() {
  bool swapped = false;

  for (size_type i = 0; i < this->s_size - 1; i++) {
    swapped = false;
    for (size_type j = 0; j < this->s_size - i - 1; j++) {
      if (this->set_elements[j] > this->set_elements[j + 1]) {
        value_type temp = this->set_elements[j];
        this->set_elements[j] = this->set_elements[j + 1];
        this->set_elements[j + 1] = temp;

        swapped = true;
      }
    }

    if (swapped == false) break;
  }
}

#endif
