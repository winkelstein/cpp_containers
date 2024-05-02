#ifndef S21_ARRAY_TPP
#define S21_ARRAY_TPP
#include "../include/s21_array.h"

template <typename T, size_t N>
s21::array<T, N>::array() : m_arr(new value_type[N]) {}

template <typename T, size_t N>
s21::array<T, N>::array(std::initializer_list<value_type> const& items)
    : array() {
  size_t i = 0;
  for (auto iter = items.begin(); iter != items.end(); ++iter, i++) {
    this->m_arr[i] = *iter;
  }
}

template <typename T, size_t N>
s21::array<T, N>::array(const array& a) : array() {
  for (size_t i = 0; i < this->m_size; i++) {
    this->m_arr[i] = a.m_arr[i];
  }
}

template <typename T, size_t N>
s21::array<T, N>::array(array&& a) {
  this->m_arr = a.m_arr;

  a.m_arr = 0;
  a.m_size = 0;
}

template <typename T, size_t N>
s21::array<T, N>::~array() {
  delete[] this->m_arr;
  this->m_size = 0;
}

template <typename T, size_t N>
s21::array<T, N> s21::array<T, N>::operator=(array&& a) {
  this->m_arr = a.m_arr;

  a.m_arr = 0;

  return *this;
}

template <typename T, size_t N>
typename s21::array<T, N>::reference s21::array<T, N>::at(size_type pos) {
  if (pos >= this->m_size) {
    throw std::out_of_range("Argument pos must be less than size");
  }

  return this->m_arr[pos];
}

template <typename T, size_t N>
typename s21::array<T, N>::reference s21::array<T, N>::operator[](
    size_type pos) {
  return this->m_arr[pos];
}

template <typename T, size_t N>
typename s21::array<T, N>::iterator s21::array<T, N>::begin() {
  if (this->m_size == 0) {
    throw std::runtime_error("Array has no elements");
  }

  return &this->m_arr[0];
}

template <typename T, size_t N>
typename s21::array<T, N>::iterator s21::array<T, N>::end() {
  if (this->m_size == 0) {
    throw std::runtime_error("Array has no elements");
  }

  return &this->m_arr[this->m_size];
}

template <typename T, size_t N>
void s21::array<T, N>::swap(array& other) {
  std::swap(this->m_arr, other.m_arr);
}

template <typename T, size_t N>
void s21::array<T, N>::fill(const_reference value) {
  for (size_t i = 0; i < this->m_size; i++) {
    this->m_arr[i] = value;
  }
}

#endif