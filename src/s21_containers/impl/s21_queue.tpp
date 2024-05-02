#ifndef S21_QUEUE_TPP
#define S21_QUEUE_TPP
#include "../include/s21_queue.h"

template <typename T>
s21::queue<T>::queue() : node_back(nullptr), node_front(nullptr), m_size(0) {}

template <typename T>
s21::queue<T>::queue(std::initializer_list<value_type> const &items) : queue() {
  for (const value_type *iter = items.begin(); iter != items.end(); ++iter) {
    this->push(*iter);
  }
}

template <typename T>
s21::queue<T>::queue(const queue &q) : queue() {
  if (!q.node_front) {
    return;
  }

  Node *curr = q.node_front;
  do {
    this->push(curr->data);
    curr = curr->next;
  } while (curr);
}

template <typename T>
s21::queue<T>::queue(queue &&q) {
  this->node_back = q.node_back;
  this->node_front = q.node_front;
  this->m_size = q.m_size;

  q.node_back = nullptr;
  q.node_front = nullptr;
  q.m_size = 0;
}

template <typename T>
s21::queue<T>::~queue() {
  while (!this->empty()) {
    this->pop();
  }
}

template <typename T>
s21::queue<T> s21::queue<T>::operator=(queue &&q) {
  this->node_back = q.node_back;
  this->node_front = q.node_front;
  this->m_size = q.m_size;

  q.node_back = nullptr;
  q.node_front = nullptr;
  q.m_size = 0;

  return *this;
}

template <typename T>
typename s21::queue<T>::const_reference s21::queue<T>::front() {
  if (this->m_size == 0) {
    throw std::runtime_error("Queue has no elements");
  }

  return this->node_front->data;
}

template <typename T>
typename s21::queue<T>::const_reference s21::queue<T>::back() {
  if (this->m_size == 0) {
    throw std::runtime_error("Queue has no elements");
  }
  return this->node_back->data;
}

template <typename T>
bool s21::queue<T>::empty() {
  return !this->m_size;
}

template <typename T>
typename s21::queue<T>::size_type s21::queue<T>::size() {
  return this->m_size;
}

template <typename T>
void s21::queue<T>::push(const_reference value) {
  if (this->m_size == 0) {
    this->node_front = new Node;
    this->node_front->data = value;

    this->node_back = this->node_front;
  } else {
    Node *new_node = new Node;
    this->node_back->next = new_node;
    new_node->data = value;

    this->node_back = new_node;
  }
  this->m_size++;
}

template <typename T>
void s21::queue<T>::pop() {
  if (this->m_size == 0) {
    throw std::runtime_error("Queue has no elements");
  }

  Node *temp = this->node_front;
  this->node_front = this->node_front->next;
  delete temp;
  this->m_size--;
}

template <typename T>
void s21::queue<T>::swap(queue &other) {
  std::swap(this->m_size, other.m_size);
  std::swap(this->node_back, other.node_back);
  std::swap(this->node_front, other.node_front);
}

#endif