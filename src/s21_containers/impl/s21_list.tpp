#ifndef S21_VECTOR_TPP
#define S21_VECTOR_TPP
#include "../include/s21_list.h"

template <typename T>
s21::list<T>::list() : first_node(nullptr), last_node(nullptr), m_size(0) {}

template <typename T>
s21::list<T>::list(size_type n) : m_size(0) {
  if (n < 1) {
    throw std::invalid_argument("List size must be greater than zero");
  }

  for (size_type i = 0; i < n; i++) {
    this->push_back(value_type());
  }
}

template <typename T>
s21::list<T>::list(std::initializer_list<value_type> const& items) : list() {
  for (const value_type* iter = items.begin(); iter != items.end(); ++iter) {
    this->push_back(*iter);
  }
}

template <typename T>
s21::list<T>::list(const list& l) : list() {
  this->clear();
  Node* node = l.first_node;
  while (node) {
    this->push_back(node->data);
    node = node->next;
  }
}

template <typename T>
s21::list<T>::list(list&& l) {
  this->m_size = l.m_size;
  this->first_node = l.first_node;
  this->last_node = l.last_node;

  l.m_size = 0;
  l.first_node = 0;
  l.last_node = 0;
}

template <typename T>
s21::list<T>::~list() {
  this->clear();
}

template <typename T>
s21::list<T> s21::list<T>::operator=(list&& l) {
  this->clear();

  this->m_size = l.m_size;
  this->first_node = l.first_node;
  this->last_node = l.last_node;

  l.m_size = 0;
  l.first_node = nullptr;
  l.last_node = nullptr;

  return *this;
}

template <typename T>
typename s21::list<T>::iterator s21::list<T>::begin() {
  if (this->m_size == 0) {
    return iterator(this, nullptr);
  }
  return iterator(this, this->first_node);
}

template <typename T>
typename s21::list<T>::iterator s21::list<T>::end() {
  if (m_size == 0) {
    return iterator(this, nullptr);
  }

  return iterator(this, this->last_node->next);
}

template <typename T>
typename s21::list<T>::const_reference s21::list<T>::front() const {
  return this->first_node->data;
}

template <typename T>
typename s21::list<T>::const_reference s21::list<T>::back() const {
  return this->last_node->data;
}

template <typename T>
void s21::list<T>::clear() {
  while (!this->empty()) {
    this->pop_front();
  }
}

template <typename T>
typename s21::list<T>::iterator s21::list<T>::insert(iterator pos,
                                                     const_reference value) {
  iterator new_iter;
  if (pos == this->begin()) {
    this->push_front(value);
    new_iter = iterator(this, this->first_node);
  } else if (pos == this->end()) {
    this->push_back(value);
    new_iter = iterator(this, this->last_node);
  } else {
    Node* temp = this->first_node;
    --pos;

    for (iterator iter = this->begin(); iter != pos; ++iter) {
      temp = temp->next;
    }

    Node* new_node = new Node;
    new_node->data = value;
    new_node->next = temp->next;

    temp->next = new_node;
    new_iter = iterator(this, new_node);
    this->m_size++;
  }
  return new_iter;
}

template <typename T>
void s21::list<T>::erase(iterator pos) {
  if (this->m_size == 0) {
    return;
  }

  if (pos == this->begin()) {
    this->pop_front();
  } else if (pos == this->end()) {
    this->pop_back();
  } else {
    Node* temp = this->first_node;
    --pos;

    for (iterator iter = this->begin(); iter != pos; ++iter) {
      temp = temp->next;
    }

    Node* new_next = temp->next->next;
    delete temp->next;
    temp->next = new_next;
    this->m_size--;
  }
}

template <typename T>
void s21::list<T>::push_back(const_reference value) {
  Node* elem = new Node;
  elem->data = value;
  elem->next = nullptr;

  if (this->m_size == 0) {
    this->first_node = elem;
  } else {
    this->last_node->next = elem;
  }

  this->last_node = elem;
  this->m_size++;
}

template <typename T>
void s21::list<T>::pop_back() {
  if (this->m_size == 1) {
    delete this->last_node;
    this->first_node = nullptr;
    this->last_node = nullptr;
    this->m_size = 0;
  } else {
    Node* ptr = this->first_node;

    while (ptr->next != this->last_node) {
      ptr = ptr->next;
    }

    delete this->last_node;
    this->last_node = ptr;
    this->m_size--;
  }
}

template <typename T>
void s21::list<T>::push_front(const_reference value) {
  Node* elem = new Node;
  elem->data = value;
  elem->next = this->first_node;

  this->first_node = elem;
  this->m_size++;
}

template <typename T>
void s21::list<T>::pop_front() {
  if (m_size > 1) {
    Node* ptr = this->first_node->next;
    delete this->first_node;
    this->first_node = ptr;
  } else {
    delete this->first_node;
    this->first_node = nullptr;
  }
  m_size--;
}

template <typename T>
void s21::list<T>::swap(list& other) {
  std::swap(this->m_size, other.m_size);
  std::swap(this->first_node, other.first_node);
  std::swap(this->last_node, other.last_node);
}

template <typename T>
void s21::list<T>::merge(list& other) {
  for (iterator iter = other.begin(); iter != other.end(); ++iter) {
    this->push_front(*iter);
  }

  this->sort();

  other.clear();
}

template <typename T>
void s21::list<T>::splice(const_iterator pos, list& other) {
  if (other.empty())  // If the other list is empty, nothing to do
    return;

  for (const_reference value : other) {
    insert(pos, value);
  }

  // Clear the other list after splicing its elements
  other.clear();
}

template <typename T>
void s21::list<T>::reverse() {
  if (this->m_size == 0) {
    throw std::runtime_error("List has no elements");
  }

  value_type* temp_arr = this->to_array();
  this->reverse_array(temp_arr);
  size_type _size = this->m_size;
  this->array_to_list(temp_arr, _size);

  delete[] temp_arr;
}

template <typename T>
void s21::list<T>::unique() {
  if (this->m_size == 0) {
    throw std::runtime_error("List has no elements");
  }

  value_type* temp_arr = this->to_array();
  size_type new_len = this->m_size;
  this->unique_array(temp_arr, &new_len);
  this->array_to_list(temp_arr, new_len);

  delete[] temp_arr;
}

template <typename T>
void s21::list<T>::sort() {
  if (this->m_size == 0) {
    throw std::runtime_error("List has no elements");
  }

  value_type* temp_arr = this->to_array();
  this->sort_array(temp_arr);
  size_type _size = this->m_size;
  this->array_to_list(temp_arr, _size);

  delete[] temp_arr;
}

template <typename T>
typename s21::list<T>::value_type* s21::list<T>::to_array() {
  value_type* arr = new value_type[this->m_size];

  size_type i = 0;
  for (iterator iter = this->begin(); iter != this->end(); ++iter, i++) {
    arr[i] = *iter;
  }

  return arr;
}

template <typename T>
void s21::list<T>::sort_array(value_type* arr) {
  bool swapped = false;

  for (size_type i = 0; i < this->m_size - 1; i++) {
    swapped = false;
    for (size_type j = 0; j < this->m_size - i - 1; j++) {
      if (arr[j] > arr[j + 1]) {
        value_type temp = arr[j];
        arr[j] = arr[j + 1];
        arr[j + 1] = temp;

        swapped = true;
      }
    }

    if (swapped == false) break;
  }
}

template <typename T>
void s21::list<T>::array_to_list(value_type* arr, size_type len) {
  this->clear();

  for (size_type i = 0; i < len; i++) {
    this->push_back(arr[i]);
  }
}

template <typename T>
void s21::list<T>::reverse_array(value_type* arr) {
  value_type* temp_arr = new value_type[this->m_size];

  for (size_type i = 0; i < this->m_size; i++) {
    temp_arr[i] = arr[this->m_size - i - 1];
  }

  for (size_type i = 0; i < this->m_size; i++) {
    arr[i] = temp_arr[i];
  }

  delete[] temp_arr;
}

template <typename T>
void s21::list<T>::unique_array(value_type* arr, size_type* len) {
  value_type* temp_arr = new value_type[*len];
  size_type new_len = 0;

  for (size_type i = 0; i < *len; ++i) {
    bool is_unique = true;
    for (size_type j = 0; j < new_len; ++j) {
      if (temp_arr[j] == arr[i]) {
        is_unique = false;
        break;
      }
    }
    if (is_unique) {
      temp_arr[new_len++] = arr[i];
    }
  }

  for (size_type i = 0; i < new_len; ++i) {
    arr[i] = temp_arr[i];
  }
  *len = new_len;

  delete[] temp_arr;
}

#endif