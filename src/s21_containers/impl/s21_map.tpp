#ifndef S21_MAP_TPP
#define S21_MAP_TPP
#include "../include/s21_map.h"

template <typename K, typename T>
s21::map<K, T>::map() : m_size(0), root_node(nullptr) {}

template <typename K, typename T>
s21::map<K, T>::map(std::initializer_list<value_type> const& items) : map() {
  for (const value_type* iter = items.begin(); iter != items.end(); ++iter) {
    insert(*iter);
  }
}

template <typename K, typename T>
s21::map<K, T>::map(const map& m) : map() {
  for (iterator iter = m.begin(); iter != m.end(); ++iter) {
    this->insert(*iter);
  }
}

template <typename K, typename T>
s21::map<K, T>::map(map&& m) : map() {
  this->m_size = m.m_size;
  this->root_node = m.root_node;

  m.m_size = 0;
  m.root_node = nullptr;
}

template <typename K, typename T>
s21::map<K, T>::~map() {
  this->clear();
}

template <typename K, typename T>
s21::map<K, T> s21::map<K, T>::operator=(map&& m) {
  this->m_size = m.m_size;
  this->root_node = m.root_node;

  m.m_size = 0;
  m.root_node = nullptr;

  return *this;
}

template <typename K, typename T>
typename s21::map<K, T>::mapped_type& s21::map<K, T>::at(const key_type& key) {
  Node* node = this->search_node(this->root_node, key);
  if (node == nullptr) {
    throw std::out_of_range("Key is not found");
  }
  return node->value;
}

template <typename K, typename T>
typename s21::map<K, T>::mapped_type& s21::map<K, T>::operator[](
    const key_type& key) {
  Node* node = this->search_node(this->root_node, key);
  if (node == nullptr) {
    this->insert(key, mapped_type());
    node = this->search_node(this->root_node, key);
  }
  return node->value;
}

template <typename K, typename T>
typename s21::map<K, T>::iterator s21::map<K, T>::begin() const {
  if (this->m_size == 0) {
    return iterator(this, nullptr);
  }

  return iterator(this, this->get_min(this->root_node));
}

template <typename K, typename T>
typename s21::map<K, T>::iterator s21::map<K, T>::end() const {
  if (this->m_size == 0) {
    return iterator(this, nullptr);
  }

  return iterator(this, this->get_max(this->root_node)->right);
}

template <typename K, typename T>
void s21::map<K, T>::clear() {
  if (this->m_size) this->destroy(this->root_node);
}

template <typename K, typename T>
std::pair<typename s21::map<K, T>::iterator, bool> s21::map<K, T>::insert(
    const value_type& value) {
  return this->insert(value.first, value.second);
}

template <typename K, typename T>
std::pair<typename s21::map<K, T>::iterator, bool> s21::map<K, T>::insert(
    const key_type& key, const mapped_type& obj) {
  if (this->m_size == 0) {
    this->root_node = new Node(key, obj);
    this->m_size++;
    return std::make_pair(iterator(this, this->root_node), true);
  }
  Node* new_node = this->search_node(this->root_node, key);
  if (new_node == nullptr) {
    new_node = this->insert_node(this->root_node, key, obj);
    this->m_size++;
    return std::make_pair(iterator(this, new_node), true);
  } else {
    return std::make_pair(iterator(this, new_node), false);
  }
}

template <typename K, typename T>
std::pair<typename s21::map<K, T>::iterator, bool>
s21::map<K, T>::insert_or_assign(const key_type& key, const mapped_type& obj) {
  Node* new_node = this->search_node(this->root_node, key);
  if (new_node) {
    new_node->value = obj;
    return std::make_pair(iterator(this, new_node), false);
  }

  if (this->m_size == 0) {
    this->root_node = new Node(key, obj);
    new_node = this->root_node;

  } else {
    new_node = this->insert_node(this->root_node, key, obj);
  }
  this->m_size++;

  return std::make_pair(iterator(this, new_node), true);
}

template <typename K, typename T>
void s21::map<K, T>::erase(iterator pos) {
  Node* node = pos.get_node();
  if (!node) return;

  if (!node->left || !node->right) {
    Node* child = node->left ? node->left : node->right;
    if (!node->parent) {
      root_node = child;
    } else {
      if (node == node->parent->left)
        node->parent->left = child;
      else
        node->parent->right = child;
    }
    if (child) child->parent = node->parent;
    delete node;
    node = nullptr;
  } else {
    Node* successor = get_min(node->right);
    node->key = successor->key;
    node->value = successor->value;
    erase(iterator(this, successor));
  }
  --m_size;
}

template <typename K, typename T>
void s21::map<K, T>::swap(map& other) {
  std::swap(this->m_size, other.m_size);
  std::swap(this->root_node, other.root_node);
}

template <typename K, typename T>
void s21::map<K, T>::merge(map& other) {
  if (other.empty()) return;

  for (auto it = other.begin(); it != other.end(); ++it) {
    key_type key = (*it).first;
    mapped_type value = (*it).second;
    this->insert_or_assign(key, value);
  }

  other.clear();
}

template <typename K, typename T>
bool s21::map<K, T>::contains(const key_type& key) {
  bool result = false;
  if (this->search_node(this->root_node, key)) result = true;

  return result;
}

template <typename K, typename T>
void s21::map<K, T>::destroy(Node* root) {
  if (root) {
    destroy(root->left);
    destroy(root->right);

    delete root;
    root = nullptr;
    this->m_size--;
  }
}

template <typename K, typename T>
typename s21::map<K, T>::Node* s21::map<K, T>::insert_node(
    Node* node, const key_type& key, const mapped_type& obj) {
  Node* result = nullptr;
  if (key < node->key) {
    if (node->left == nullptr) {
      node->left = new Node(key, obj);
      node->left->parent = node;
      result = node->left;
    } else
      result = insert_node(node->left, key, obj);
  } else if (key >= node->key) {
    if (node->right == nullptr) {
      node->right = new Node(key, obj);
      node->right->parent = node;
      result = node->right;
    } else
      result = insert_node(node->right, key, obj);
  }

  return result;
}

template <typename K, typename T>
typename s21::map<K, T>::Node* s21::map<K, T>::search_node(
    Node* node, const key_type& key) {
  if (node == nullptr) return nullptr;
  if (node->key == key) return node;
  return (key < node->key) ? this->search_node(node->left, key)
                           : this->search_node(node->right, key);
}

template <typename K, typename T>
typename s21::map<K, T>::Node* s21::map<K, T>::get_min(Node* node) const {
  if (node == nullptr) return nullptr;
  if (node->left == nullptr) return node;
  return this->get_min(node->left);
}

template <typename K, typename T>
typename s21::map<K, T>::Node* s21::map<K, T>::get_max(Node* node) const {
  if (node == nullptr) return nullptr;
  if (node->right == nullptr) return node;
  return this->get_max(node->right);
}

#endif