#ifndef STACK_H
#define STACK_H

#include <memory>
#include <algorithm>

using std::allocator;
using std::uninitialized_fill;
using std::max;
using std::uninitialized_copy;

template <class T> class Stack {
public:
  typedef T * iterator;
  typedef const T * const_iterator;
  typedef size_t size_type;
  typedef T value_type;
  typedef T& reference;
  typedef const T& const_reference;

  Stack() {
    create();
  }

  explicit Stack(size_type size) {
    create(size);
  }

  Stack(const Stack& stack) {
    create(stack.begin(), stack.end());
  }

  Stack<T>& operator=(const_reference);

  ~Stack() {
    uncreate();
  }

  void push(const_reference element) {
    if (avail == limit) {
      grow();
    }

    unchecked_push(element);
  }

  const_reference peek() {
    return *(avail - 1);
  }

  value_type pop();

  size_type size() const {
    return avail - data;
  }

  iterator begin() {
    return data;
  }

  const_iterator begin() const {
    return data;
  }

  iterator end() {
    return avail;
  }

  const_iterator end() const {
    return avail;
  }
private:
  iterator data;
  iterator avail;
  iterator limit;

  allocator<value_type> alloc;

  void create();
  void create(size_type);
  void create(const_iterator, const_iterator);

  void uncreate();

  void grow();
  void unchecked_push(const_reference);
};

template <class T>
void Stack<T>::create() {
  data = avail = limit = 0;
}

template <class T>
void Stack<T>::create(size_type size) {
  data = alloc.allocate(size);
  limit = avail = data + size;
  uninitialized_fill(data, limit, value_type());
}

template <class T>
void Stack<T>::create(const_iterator i, const_iterator j) {
  data = alloc.allocate(j - i);
  limit = avail = uninitialized_copy(i, j, data);
}

template <class T>
void Stack<T>::uncreate() {
  if (data) {
    iterator it = avail;
    while (it != data) {
      alloc.destroy(--it);
    }

    alloc.deallocate(data, limit - data);
  }

  data = limit = avail = 0;
}

template <class T>
void Stack<T>::grow() {
  size_type new_size = max(2 * (limit - data), ptrdiff_t(1));

  iterator new_data = alloc.allocate(new_size);
  iterator new_avail = uninitialized_copy(data, avail, new_data);

  uncreate();

  data = new_data;
  avail = new_avail;
  limit = data + new_size;
}

template <class T>
void Stack<T>::unchecked_push(const_reference element) {
  alloc.construct(avail++, element);
}

template <class T>
Stack<T>& Stack<T>::operator=(const_reference other) {
  if (&other != this) {
    uncreate();
    create(other.begin(), other.end());
  }

  return *this;
}

template <class T>
T Stack<T>::pop() {
  value_type popped = *(--avail);
  alloc.destroy(avail);

  return popped;
}

#endif