#ifndef S21_ARRAY_H
#define S21_ARRAY_H
#include <initializer_list>
#include <utility>

namespace s21 {
template <class T, size_t N>
class array {
 private:
  /* Array Member type */

  using value_type = T;
  using reference = value_type &;
  using const_reference = const reference;
  using iterator = value_type *;
  using const_iterator = const iterator;
  using size_type = size_t;

 private:
  value_type *m_arr;
  size_t m_size = N;

 public:
  /* Array Member functions */

  // default constructor, creates empty array
  array();
  // initializer list constructor, creates array initizialized using
  // std::initializer_list
  array(std::initializer_list<value_type> const &items);
  // copy constructor
  array(const array &a);
  // move constructor
  array(array &&a);
  // destructor
  ~array();
  // assignment operator overload for moving object
  array operator=(array &&a);

  /* Array Element access */

  // access specified element with bounds checking
  reference at(size_type pos);
  // access specified element
  reference operator[](size_type pos);
  // access the first element
  inline const_reference front() { return this->m_arr[0]; }
  // access the last element
  inline const_reference back() { return this->m_arr[this->m_size - 1]; }
  // direct access to the underlying array
  inline iterator data() { return this->m_arr; }

  /* Array Iterators */

  // returns an iterator to the beginning
  iterator begin();
  // returns an iterator to the end
  iterator end();

  /* Array Capacity */

  // checks whether the container is empty
  inline bool empty() const { return !this->m_size; }
  // returns the number of elements
  inline size_type size() const { return this->m_size; }
  // returns the maximum possible number of elements
  inline size_t max_size() const { return N; }

  /* Array Modifiers */

  // swaps the contents
  void swap(array &other);
  // assigns the given value value to all elements in the container.
  void fill(const_reference value);
};
}  // namespace s21

#include "../impl/s21_array.tpp"
#endif