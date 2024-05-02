#ifndef S21_VECTOR_TPP
#define S21_VECTOR_TPP
#include "../include/s21_vector.h"

template <typename T>
s21::vector<T>::vector() : m_size(0), m_capacity(1), m_arr(nullptr) {
  this->m_arr = new value_type[this->m_capacity];
}

template <typename T>
s21::vector<T>::vector(size_type n) : m_size(n), m_capacity(n), m_arr(nullptr) {
  if (n != 0) {
    this->m_arr = new value_type[this->m_capacity];
  }
}

template <typename T>
s21::vector<T>::vector(std::initializer_list<value_type> const &items)
    : m_size(items.size()), m_capacity(items.size()), m_arr(nullptr) {
  this->m_arr = new value_type[this->m_capacity];

  size_type i = 0;
  for (const value_type *iter = items.begin(); iter != items.end();
       ++iter, i++) {
    this->m_arr[i] = *iter;
  }
}

template <typename T>
s21::vector<T>::vector(const vector &v)
    : m_capacity(v.m_capacity), m_size(v.m_size) {
  this->m_arr = new value_type[this->m_capacity];

  for (size_type i = 0; i < this->m_size; i++) {
    this->m_arr[i] = v.m_arr[i];
  }
}

template <typename T>
s21::vector<T>::vector(vector &&v) {
  this->m_arr = v.m_arr;
  this->m_capacity = v.m_capacity;
  this->m_size = v.m_size;

  v.m_arr = nullptr;
  v.m_capacity = 0;
  v.m_size = 0;
}

template <typename T>
s21::vector<T>::~vector() {
  if (this->m_arr) {
    delete[] this->m_arr;
    this->m_size = 0;
    this->m_capacity = 0;
    this->m_arr = nullptr;
  }
}

template <typename T>
s21::vector<T> s21::vector<T>::operator=(vector &&v) {
  if (this->m_arr) delete[] this->m_arr;
  this->m_arr = v.m_arr;
  this->m_capacity = v.m_capacity;
  this->m_size = v.m_size;

  v.m_arr = nullptr;
  v.m_capacity = 0;
  v.m_size = 0;

  return *this;
}

template <typename T>
typename s21::vector<T>::reference s21::vector<T>::at(size_type pos) {
  if (this->m_size <= pos) {
    throw std::out_of_range("vector: out of range");
  }

  return this->m_arr[pos];
}

template <typename T>
typename s21::vector<T>::reference s21::vector<T>::operator[](size_type pos) {
  return this->m_arr[pos];
}

template <typename T>
typename s21::vector<T>::const_reference s21::vector<T>::front() {
  return this->m_arr[0];
}

template <typename T>
typename s21::vector<T>::const_reference s21::vector<T>::back() {
  return this->m_arr[this->m_size - 1];
}

template <typename T>
T *s21::vector<T>::data() {
  return this->m_arr;
}

template <typename T>
typename s21::vector<T>::iterator s21::vector<T>::begin() {
  if (this->m_size == 0) {
    return iterator(this, -1);
  }

  return iterator(this, 0);
}

template <typename T>
typename s21::vector<T>::iterator s21::vector<T>::end() {
  if (this->m_size == 0) {
    return iterator(this, -1);
  }

  return iterator(this, this->m_size);
}

template <typename T>
bool s21::vector<T>::empty() {
  return !this->m_size;
}

template <typename T>
typename s21::vector<T>::size_type s21::vector<T>::size() {
  return this->m_size;
}

template <typename T>
typename s21::vector<T>::size_type s21::vector<T>::max_size() {
  return std::numeric_limits<size_type>::max() / sizeof(value_type);
}

template <typename T>
void s21::vector<T>::reserve(size_type size) {
  this->realloc(size);
}

template <typename T>
typename s21::vector<T>::size_type s21::vector<T>::capacity() {
  return this->m_capacity;
}

template <typename T>
void s21::vector<T>::shrink_to_fit() {
  if (this->m_size != this->m_capacity) {
    this->realloc(this->m_size);
  }
}

template <typename T>
void s21::vector<T>::clear() {
  this->m_size = 0;
}

template <typename T>
typename s21::vector<T>::iterator s21::vector<T>::insert(
    iterator pos, const_reference value) {
  size_type index = pos.m_index;

  if (index > this->m_size || index < 0) {
    throw std::out_of_range("attention - vector::insert");
  }

  this->m_size++;
  if (this->m_size > this->m_capacity) {
    size_type new_capacity =
        this->m_capacity * 2;  // Удвоение capacity если не зватает места
    this->realloc(new_capacity);
  }
  // Сдвигаем элементы после позиции вставки на одну позицию вправо
  for (size_type i = this->m_size - 1; i > index; --i) {
    this->m_arr[i] = this->m_arr[i - 1];
  }
  // Вставляем новое значение в позицию и возвращаем вставляемый элемент
  this->m_arr[index] = value;
  return iterator(this, index);
}

template <typename T>
void s21::vector<T>::erase(iterator pos) {
  size_type index = pos.index();
  // добавление исключения
  if (index >= this->m_size || index < 0) {
    throw std::out_of_range("attention - vector::erase");
  }
  // сдвиг масива
  for (size_type i = index; i < this->m_size - 1; i++) {
    this->m_arr[i] = this->m_arr[i - 1];
  }
  // вектор --
  this->m_size--;
}

template <typename T>
void s21::vector<T>::push_back(const_reference value) {
  this->m_size++;

  if (this->m_size <= this->m_capacity) {
    this->m_arr[this->m_size - 1] = value;
  } else {
    this->realloc(this->m_size);
    this->m_arr[this->m_size - 1] = value;
  }
}

template <typename T>
void s21::vector<T>::pop_back() {
  this->m_size--;
}

template <typename T>
void s21::vector<T>::swap(vector &other) {
  std::swap(this->m_arr, other.m_arr);
  std::swap(this->m_capacity, other.m_capacity);
  std::swap(this->m_size, other.m_size);
}

template <typename T>
void s21::vector<T>::realloc(size_type new_capacity) {
  if (new_capacity > this->m_capacity) {
    value_type *temp = new value_type[new_capacity];
    for (size_type i = 0; i < this->m_capacity; i++) {
      temp[i] = this->m_arr[i];
    }
    delete[] this->m_arr;
    this->m_arr = temp;
    this->m_capacity = new_capacity;
  } else if (new_capacity < this->m_capacity) {
    value_type *temp = new value_type[new_capacity];

    for (size_type i = 0; i < new_capacity; i++) {
      temp[i] = this->m_arr[i];
    }

    delete[] this->m_arr;
    this->m_arr = temp;
    this->m_capacity = new_capacity;
  }
}

#endif