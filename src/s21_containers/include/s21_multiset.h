#ifndef S21_MULTISET_H
#define S21_MULTISET_H

#include <initializer_list>
#include <limits>
#include <utility>

namespace s21 {
template <class T>
class multiset {
 public:
  class iterator;

 private:
  /* Set Member type */

  using key_type = T;
  using value_type = T;
  using reference = value_type&;
  using const_reference = const value_type&;
  using const_iterator = const iterator;
  using size_type = size_t;

 private:
  T* multiset_elements;
  size_type s_size;

 public:
  /* Set Member functions */

  // default constructor, creates empty set
  multiset();
  // initializer list constructor, creates the set initizialized using
  // std::initializer_list
  multiset(std::initializer_list<value_type> const& items);
  // copy constructor
  multiset(const multiset& ms);
  // move constructor
  multiset(multiset&& ms);
  // destructor
  ~multiset();
  // assignment operator overload for moving object
  multiset operator=(multiset&& ms);

  /* Set Iterators */

  // returns an iterator to the beginning
  iterator begin();
  // returns an iterator to the end
  iterator end();

  /* Set Capacity */

  // checks whether the container is empty
  bool empty();
  // returns the number of elements
  size_type size();
  // returns the maximum possible number of elements
  size_type max_size();

  /* Set Modifiers */

  // clears the contents
  void clear();
  // inserts node and returns iterator to where the element is in the container
  // and bool denoting whether the insertion took place
  iterator insert(const value_type& value);
  // erases element at pos
  void erase(iterator pos);
  // swaps the contents
  void swap(multiset& other);
  // splices nodes from another container
  void merge(multiset& other);

  /* Set Lookup */

  // finds element with specific key
  iterator find(const key_type& key);
  // checks if the container contains element with specific key
  bool contains(const key_type& key);
  // sorting elements

  size_type count(const key_type& key);
  std::pair<iterator, iterator> equal_range(const key_type& key);
  iterator lower_bound(const key_type& key);
  iterator upper_bound(const key_type& key);

 private:
  void sort();
};
}  // namespace s21

#include "../impl/s21_multiset.tpp"
#include "../iterators/s21_multisetiterator.h"
#endif
