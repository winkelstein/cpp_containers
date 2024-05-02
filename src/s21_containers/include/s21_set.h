#ifndef S21_SET_H
#define S21_SET_H

#include <initializer_list>
#include <limits>
#include <utility>

namespace s21 {
template <class T>
class set {
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
  T* set_elements;
  size_type s_size;

 public:
  /* Set Member functions */

  // default constructor, creates empty set
  set();
  // initializer list constructor, creates the set initizialized using
  // std::initializer_list
  set(std::initializer_list<value_type> const& items);
  // copy constructor
  set(const set& s);
  // move constructor
  set(set&& s);
  // destructor
  ~set();
  // assignment operator overload for moving object
  set operator=(set&& s);

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
  std::pair<iterator, bool> insert(const value_type& value);
  // erases element at pos
  void erase(iterator pos);
  // swaps the contents
  void swap(set& other);
  // splices nodes from another container
  void merge(set& other);

  /* Set Lookup */

  // finds element with specific key
  iterator find(const key_type& key);
  // checks if the container contains element with specific key
  bool contains(const key_type& key);
  // sorting elements

 private:
  void sort();
};
}  // namespace s21

#include "../impl/s21_set.tpp"
#include "../iterators/s21_setiterator.h"
#endif
