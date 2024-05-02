#ifndef S21_MAP_H
#define S21_MAP_H
#include <initializer_list>
#include <limits>
#include <utility>

namespace s21 {
template <class K, class T>
class map {
 public:
  class iterator;

 private:
  /* Map Member type */
  using key_type = K;
  using mapped_type = T;
  using value_type = std::pair<const key_type, mapped_type>;
  using reference = value_type&;
  using const_reference = const value_type&;
  using const_iterator = const iterator;
  using size_type = size_t;

  struct Node {
    key_type key;
    mapped_type value;

    Node* parent;
    Node* left;
    Node* right;

    Node(const key_type key, mapped_type value)
        : key(key),
          value(value),
          parent(nullptr),
          left(nullptr),
          right(nullptr) {}
  };

 private:
  size_type m_size;
  Node* root_node;

 public:
  /* Map Member functions */

  // default constructor, creates empty map
  map();
  // initializer list constructor, creates the map initizialized using
  // std::initializer_list
  map(std::initializer_list<value_type> const& items);
  // copy constructor
  map(const map& m);
  // move constructor
  map(map&& m);
  // destructor
  ~map();
  // assignment operator overload for moving object
  map operator=(map&& m);

  /* Map Element access */

  //  access specified element with bounds checking
  mapped_type& at(const key_type& key);
  // access or insert specified element
  mapped_type& operator[](const key_type& key);

  /* Map Iterators */
  // returns an iterator to the beginning
  iterator begin() const;
  // returns an iterator to the end
  iterator end() const;

  /* Map Capacity */

  // checks whether the container is empty
  inline bool empty() { return !this->m_size; }
  // returns the number of elements
  inline size_type size() { return this->m_size; }
  // returns the maximum possible number of elements
  inline size_type max_size() {
    return std::numeric_limits<size_type>::max() / sizeof(Node);
  }

  /* Map Modifiers */

  // clears the contents
  void clear();
  // inserts node and returns iterator to where
  // the element is in the container and bool
  // denoting whether the insertion took place
  std::pair<iterator, bool> insert(const value_type& value);
  // inserts value by key and returns iterator to where the
  // element is in the container and bool denoting whether
  // the insertion took place
  std::pair<iterator, bool> insert(const key_type& key, const mapped_type& obj);
  // inserts an element or assigns to the current element if
  // the key already exists
  std::pair<iterator, bool> insert_or_assign(const key_type& key,
                                             const mapped_type& obj);
  // erases element at pos
  void erase(iterator pos);
  // swaps the contents
  void swap(map& other);
  // splices nodes from another container
  void merge(map& other);

  /* Map Lookup */

  // checks if there is an element with key
  // equivalent to key in the container
  bool contains(const key_type& key);

 private:
  void destroy(Node* root);
  Node* insert_node(Node* node, const key_type& key, const mapped_type& obj);
  Node* search_node(Node* node, const key_type& key);
  Node* get_min(Node* node) const;
  Node* get_max(Node* node) const;
};
}  // namespace s21

#include "../impl/s21_map.tpp"
#include "../iterators/s21_mapiterator.h"
#endif