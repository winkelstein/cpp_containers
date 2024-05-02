#ifndef S21_MULTImultiset_TPP
#define S21_MULTImultiset_TPP
#include "../include/s21_multiset.h"

template <typename T>
s21::multiset<T>::multiset() {
  this->s_size = 0;
  this->multiset_elements = nullptr;
}

template <typename T>
s21::multiset<T>::multiset(std::initializer_list<value_type> const& items)
    : s_size(0) {
  this->multiset_elements = new T[items.size()];
  for (const value_type* iter = items.begin(); iter != items.end(); ++iter) {
    this->insert(*iter);
  }
  this->sort();
}

template <typename T>
s21::multiset<T>::multiset(const multiset& s) {
  this->s_size = s.s_size;
  this->multiset_elements = new T[s.s_size];
  for (size_t i = 0; i < s.s_size; ++i) {
    this->multiset_elements[i] = s.multiset_elements[i];
  }
}
template <typename T>
s21::multiset<T>::multiset(multiset&& s) {
  this->s_size = s.s_size;
  this->multiset_elements = s.multiset_elements;
  s.s_size = 0;
  s.multiset_elements = nullptr;
}

template <typename T>
s21::multiset<T>::~multiset() {
  this->clear();
}
template <typename T>
s21::multiset<T> s21::multiset<T>::operator=(multiset&& s) {
  this->clear();
  this->s_size = s.s_size;
  this->multiset_elements = s.multiset_elements;
  s.s_size = 0;
  s.multiset_elements = nullptr;
  return *this;
}

template <typename T>
typename s21::multiset<T>::iterator s21::multiset<T>::begin() {
  if (s_size == 0) {
    return iterator();
  }

  return iterator(this, 0);
}

template <typename T>
typename s21::multiset<T>::iterator s21::multiset<T>::end() {
  if (s_size == 0) {
    return iterator();
  }

  return iterator(this, this->s_size);
}

template <typename T>
bool s21::multiset<T>::empty() {
  return this->size() == 0 ? true : false;
}
template <typename T>
typename s21::multiset<T>::size_type s21::multiset<T>::size() {
  return this->s_size;
}

template <typename T>
typename s21::multiset<T>::size_type s21::multiset<T>::max_size() {
  return std::numeric_limits<size_type>::max() / sizeof(T);
}

template <typename T>
void s21::multiset<T>::clear() {
  delete[] this->multiset_elements;
  this->multiset_elements = nullptr;
  this->s_size = 0;
}

template <typename T>
void s21::multiset<T>::erase(iterator pos) {
  if (!this->empty() &&
      (pos.pos >= this->begin().pos && pos.pos < this->end().pos)) {
    size_t index = pos.pos;
    for (size_t i = index; i < s_size - 1; ++i) {
      multiset_elements[i] = multiset_elements[i + 1];
    }
    --this->s_size;
  }
}

template <typename T>
typename s21::multiset<T>::iterator s21::multiset<T>::find(
    const key_type& key) {
  for (size_t i = 0; i < s_size; ++i) {
    if (multiset_elements[i] == key) {
      return iterator(this, i);
    }
  }
  return end();
}

template <typename T>
void s21::multiset<T>::swap(multiset& other) {
  std::swap(this->s_size, other.s_size);
  std::swap(this->multiset_elements, other.multiset_elements);
}

template <typename T>
bool s21::multiset<T>::contains(const key_type& key) {
  return this->find(key) != this->end() ? true : false;
}

template <typename T>
typename s21::multiset<T>::iterator s21::multiset<T>::insert(
    const value_type& value) {
  T* new_multiset_elements = new T[s_size + 1];
  size_t i = 0;
  for (; i < s_size; ++i) {
    new_multiset_elements[i] = multiset_elements[i];
  }
  new_multiset_elements[i] = value;
  delete[] multiset_elements;
  multiset_elements = new_multiset_elements;
  ++this->s_size;
  return iterator(this, i);
}

template <typename T>
void s21::multiset<T>::merge(multiset& other) {
  if (this == &other) {
    return;
  }
  for (size_t i = 0; i < other.s_size; ++i) {
    this->insert(other.multiset_elements[i]);
  }
  this->sort();
  other.clear();
}

template <typename T>
typename s21::multiset<T>::size_type s21::multiset<T>::count(
    const key_type& key) {
  if (!this->contains(key)) {
    return 0;
  }
  size_type ans = 0;
  for (size_t i = 0; i < this->s_size; ++i) {
    if (this->multiset_elements[i] == key) {
      ans++;
    }
    if (ans > 0 && this->multiset_elements[i] != key) {
      break;
    }
  }
  return ans;
}
template <typename T>
std::pair<typename s21::multiset<T>::iterator,
          typename s21::multiset<T>::iterator>
s21::multiset<T>::equal_range(const key_type& key) {
  iterator first = lower_bound(key);
  iterator last = upper_bound(key);
  return std::make_pair(first, last);
}

template <typename T>
typename s21::multiset<T>::iterator s21::multiset<T>::lower_bound(
    const key_type& key) {
  iterator it = begin();
  while (it != end() && key > *it) {
    ++it;
  }
  return it;
}

template <typename T>
typename s21::multiset<T>::iterator s21::multiset<T>::upper_bound(
    const key_type& key) {
  iterator it = begin();
  while (it != end() && key >= *it) {
    ++it;
  }
  return it;
}

template <typename T>
void s21::multiset<T>::sort() {
  bool swapped = false;

  for (size_type i = 0; i < this->s_size - 1; i++) {
    swapped = false;
    for (size_type j = 0; j < this->s_size - i - 1; j++) {
      if (this->multiset_elements[j] >= this->multiset_elements[j + 1]) {
        value_type temp = this->multiset_elements[j];
        this->multiset_elements[j] = this->multiset_elements[j + 1];
        this->multiset_elements[j + 1] = temp;

        swapped = true;
      }
    }

    if (swapped == false) break;
  }
}

#endif
