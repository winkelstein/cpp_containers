#ifndef S21_VECTOR_H
#define S21_VECTOR_H
#include <exception>
#include <initializer_list>
#include <limits>
#include <stdexcept>

namespace s21 {
template <class T>
class vector {
 public:
  class iterator;

 private:
  /* Vector Member type */

  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using const_iterator = const iterator;
  using size_type = size_t;

 private:
  value_type *m_arr;
  size_type m_size;
  size_type m_capacity;

 public:
  /* Vector Member functions */

  // default constructor, creates empty vector
  vector();
  // parameterized constructor, creates the vector of size n
  vector(size_type n);
  // initializer list constructor, creates vector initizialized using
  // std::initializer_list
  vector(std::initializer_list<value_type> const &items);
  // copy constructor
  vector(const vector &v);
  // move constructor
  vector(vector &&v);
  // destructor
  ~vector();
  // assignment operator overload for moving object
  vector operator=(vector &&v);

  /* Vector Element access */

  // access specified element with bounds checking
  reference at(size_type pos);
  // access specified element
  reference operator[](size_type pos);
  // access the first element
  const_reference front();
  // access the last element
  const_reference back();
  // direct access to the underlying array
  T *data();

  /* Vector Iterators */

  // returns an iterator to the beginning
  iterator begin();
  // returns an iterator to the end
  iterator end();

  /* Vector Capacity */

  // checks whether the container is empty
  bool empty();
  // returns the number of elements
  size_type size();
  // returns the maximum possible number of elements
  size_type max_size();
  // allocate storage of size elements and copies current array elements to a
  // newely allocated array
  void reserve(size_type size);
  // returns the number of elements that can be held in currently allocated
  // storage
  size_type capacity();
  // reduces memory usage by freeing unused memory
  void shrink_to_fit();

  /* Vector Modifiers */

  // clears the contents
  void clear();
  // inserts elements into concrete pos and returns the iterator that points to
  // the new element
  iterator insert(iterator pos, const_reference value);
  // erases element at pos
  void erase(iterator pos);
  // adds an element to the end
  void push_back(const_reference value);
  // removes the last element
  void pop_back();
  // swaps the contents
  void swap(vector &other);

 private:
  void realloc(size_type new_capacity);
};
}  // namespace s21

#include "../impl/s21_vector.tpp"
#include "../iterators/s21_vectoriterator.h"
#endif