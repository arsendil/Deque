# Deque

The `Deque` class implements a **double-ended queue (deque)** that allows insertion and deletion at both the front and the back in **amortized constant time**.  
It is a **template class**, supporting any data type `T`.

---

## Features

- **Double-ended access:** Efficiently push and pop elements at both ends: `push_front`, `push_back`, `pop_front`, `pop_back`.
- **Random access:** Supports `operator[]` and `at_index()` for direct access to elements by position.
- **Iterators:** Supports normal, reverse, const, and const-reverse iterators for full traversal flexibility.
- **Resizable:** `resize()` to grow or shrink the deque with a given initial value.
- **Capacity functions:** `size()`, `empty()`, `max_size()`.
- **Modifiers:** `clear()`, `swap()`, `insert()`, `erase()`.
- **Comparison operators:** `==`, `!=`, `<`, `>`, `<=`, `>=`.

---

## Constructors

- `Deque()` – default constructor, creates an empty deque.
- `Deque(size_type newSize, const_reference initialValue)` – creates a deque of size `newSize`, initializing elements with `initialValue`.
- `Deque(InputIterator first, InputIterator last)` – constructs deque from a range `[first, last)`.
- `Deque(const Deque<T>& rhv)` – copy constructor.
- Destructor `~Deque()` clears all elements.

---

## Element Access

- `front()` / `back()` – access first/last element.
- `operator[]` / `at_index()` – random access to elements.

---

## Modifiers

- `push_front(const_reference value)` – add element at the front.
- `push_back(const_reference value)` – add element at the back.
- `pop_front()` – remove element from front.
- `pop_back()` – remove element from back.
- `insert(iterator pos, value)` – insert element(s) at a specific position.
- `erase(iterator pos)` – erase element(s) at a specific position.
- `clear()` – remove all elements.
- `swap(Deque<T>& rhv)` – exchange contents with another deque.
- `resize(size_type newSize, const_reference value)` – resize the deque with optional initialization.

---

## Iterators

- `begin()` / `end()` – normal iterators.
- `rbegin()` / `rend()` – reverse iterators.
- Const versions: `begin() const`, `end() const`, `rbegin() const`, `rend() const`.
- Iterators support `++`, `--`, `+`, `-`, `+=`, `-=`, `[]`.

---

## Capacity

- `size()` – returns the number of elements in the deque.
- `empty()` – checks whether the deque is empty.
- `max_size()` – returns the theoretical maximum number of elements.

---

## Comparison Operators

- `==`, `!=`, `<`, `>`, `<=`, `>=` – compare two deques element-wise.

---

## Example Usage

```cpp
#include "Deque.hpp"
#include <iostream>

int main() {
    Deque<int> dq;

    // Push elements at both ends
    dq.push_back(10);
    dq.push_front(5);
    dq.push_back(15);

    // Access elements
    std::cout << "Front: " << dq.front() << "\n"; // 5
    std::cout << "Back: " << dq.back() << "\n";   // 15
    std::cout << "Element at index 1: " << dq[1] << "\n"; // 10

    // Iteration
    for (Deque<int>::iterator it = dq.begin(); it != dq.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\n";

    // Pop elements
    dq.pop_front();
    dq.pop_back();

    // Size
    std::cout << "Size after pop: " << dq.size() << "\n"; // 1

    return 0;
}
