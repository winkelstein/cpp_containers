#ifndef S21_STACK_TPP
#define S21_STACK_TPP
#include "../include/s21_stack.h"

template <typename T>
s21::stack<T>::stack() : m_top(nullptr), m_size(0) {}

template <typename T>
s21::stack<T>::stack(std::initializer_list<value_type> const &items) : stack() {
  for (const value_type *iter = items.begin(); iter != items.end(); ++iter) {
    this->push(*iter);
  }
}

template <typename T>
s21::stack<T>::stack(const stack &s) : stack() {
  if (s.m_top) {
    Node *current = s.m_top;
    Node *prev = nullptr;
    Node *newNode;

    while (current) {
      newNode = new Node;
      newNode->data = current->data;

      if (!m_top) {
        m_top = newNode;
      } else {
        prev->next = newNode;
      }

      prev = newNode;
      current = current->next;
    }
  }

  this->m_size = s.m_size;
}

template <typename T>
s21::stack<T>::stack(stack &&s) {
  this->m_top = s.m_top;
  this->m_size = s.m_size;

  s.m_top = nullptr;
  s.m_size = 0;
}

template <typename T>
s21::stack<T>::~stack() {
  while (!this->empty()) {
    this->pop();
  }
}

template <typename T>
s21::stack<T> s21::stack<T>::operator=(stack &&s) {
  while (!this->empty()) {
    this->pop();
  }

  this->m_top = s.m_top;
  this->m_size = s.m_size;

  s.m_top = nullptr;
  s.m_size = 0;

  return *this;
}

template <typename T>
typename s21::stack<T>::const_reference s21::stack<T>::top() {
  if (this->m_size == 0) {
    throw std::runtime_error("Stack has no elements");
  }

  return this->m_top->data;
}

template <typename T>
bool s21::stack<T>::empty() {
  return !this->m_size;
}

template <typename T>
typename s21::stack<T>::size_type s21::stack<T>::size() {
  return this->m_size;
}

template <typename T>
void s21::stack<T>::push(const_reference value) {
  if (this->m_size == 0) {
    this->m_top = new Node;
    this->m_top->data = value;

  } else {
    Node *new_node = new Node;
    new_node->data = value;
    new_node->next = this->m_top;

    this->m_top = new_node;
  }
  this->m_size++;
}

template <typename T>
void s21::stack<T>::pop() {
  if (this->m_size == 0) {
    throw std::runtime_error("Stack has no elements");
  }

  if (this->m_size > 1) {
    Node *temp = this->m_top;
    this->m_top = this->m_top->next;
    delete temp;
  } else {
    delete this->m_top;
  }
  this->m_size--;
}

template <typename T>
void s21::stack<T>::swap(stack &other) {
  std::swap(this->m_top, other.m_top);
  std::swap(this->m_size, other.m_size);
}
#endif