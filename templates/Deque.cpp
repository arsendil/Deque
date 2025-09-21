#include "../headers/Deque.hpp"
#include <algorithm>
#include <cassert>
#include <limits>

template <typename T>
Deque<T>::Deque()
{}

template <typename T>
Deque<T>::Deque(const size_type newSize, const_reference initialValue)
{
    resize(newSize, initialValue);
}

template <typename T>
Deque<T>::Deque(const int newSize, const_reference initialValue)
{
    resize(newSize, initialValue);
}

template <typename T>
template <typename InputIterator>
Deque<T>::Deque(InputIterator first, InputIterator last)
{
    for (InputIterator it = first; it != last; ++it) {
        push_back(*it);
    }
}

template <typename T>
Deque<T>::Deque(const Deque<T>& rhv)
{
    if (this == &rhv) return;
    for (const_iterator it = rhv.begin(); it < rhv.end(); ++it) {
        push_back(*it);     
    }
}

template <typename T>
Deque<T>::~Deque()
{
    clear();
}

template <typename T>
Deque<T>&
Deque<T>::operator=(const Deque<T>& rhv)
{
    if (*this == rhv) return *this;
    clear();
    front_ = rhv.front_;
    back_ = rhv.back_;
    return *this;
}

template <typename T>
bool
Deque<T>::operator==(const Deque<T>& rhv) const
{
    if (this == &rhv)         return true;
    if (size() != rhv.size()) return false;
    const size_type newSize = size();
    for (size_type i = 0; i < newSize; ++i) {
        if (*this[i] != rhv[i]) return false;
    }
    return true;
}

template <typename T>
bool
Deque<T>::operator!=(const Deque<T>& rhv) const
{
    return !(*this == rhv);
}

template <typename T>
bool
Deque<T>::operator<(const Deque<T>& rhv) const
{
    const_iterator start1 = begin();
    const_iterator start2 = rhv.begin();
    for (; start1 != end() && start2 != rhv.end(); ++start1, ++start2) {
        if (*start1 < *start2) return true;
        if (*start1 > *start2) return false;
    }
    return start1 == end() && start2 != rhv.end();
}

template <typename T>
bool
Deque<T>::operator>(const Deque<T>& rhv) const
{
    return rhv < *this;
}

template <typename T>
bool
Deque<T>::operator<=(const Deque<T>& rhv) const
{
    return !(*this > rhv);
}

template <typename T>
bool
Deque<T>::operator>=(const Deque<T>& rhv) const
{
    return !(*this < rhv);
}
 
template <typename T>
typename Deque<T>::reference
Deque<T>::operator[](const size_type index)
{
    if (index < front_.size()) {
        return front_[size() - index - 1];
    }
    return back_[index - front_.size()];
}

template <typename T>
typename Deque<T>::const_reference
Deque<T>::operator[](const size_type index) const
{
    if (index < front_.size()) {
        return front_[size() - index - 1];
    }
    return back_[index - front_.size()];
}

template <typename T>
typename Deque<T>::iterator
Deque<T>::insert(iterator position, const_reference value)
{
    if (position <= front_.end() && position >= back_.end()) {
        return front_.insert(front_.end() - position, value);
    }
    return back_.insert(back_.begin() + (position - front_.size()), value);
}

template <typename T>
void
Deque<T>::insert(iterator position, size_type size, const_reference value)
{
    for (size_type i = 0; i < size; ++i) {
        insert(position, value);
    }
}

template <typename T>
template <typename InputIterator>
void
Deque<T>::insert(iterator position, InputIterator first, InputIterator last)
{
    while (first != last) {
        position = insert(position, *first);
        ++first;
        ++position;
    }
}

template <typename T>
typename Deque<T>::iterator
Deque<T>::erase(iterator position)
{
    if (position <= front_.end() && position >= back_.end()) {
        return front_.erase(front_.end() - position);
    }
    return back_.erase(back_.begin() + (position - front_.size()));
}

template <typename T>
typename Deque<T>::iterator
Deque<T>::erase(iterator first, iterator last)
{
    while (first != last) {
        first = erase(first);
        --last;
    }
    return first;
}

template <typename T>
void
Deque<T>::push_front(const_reference value)
{
    if (!front_.empty()) {
        front_.push_back(value);
        return;
    }
    back_.insert(back_.begin(), value);
}

template <typename T>
void
Deque<T>::push_back(const_reference value)
{
    if (!back_.empty()) {
        back_.push_back(value);
        return;
    }
    front_.insert(front_.begin(), value);
}

template <typename T>
void
Deque<T>::pop_front()
{
    assert(!empty());
    if (!front_.empty()) {
        front_.pop_back();
        return;
    }
    back_.erase(back_.begin());
}

template <typename T>
void
Deque<T>::pop_back()
{
    assert(!empty());
    if (!back_.empty()) {
        back_.pop_back();
        return;
    }
    front_.erase(front_.begin());
}

template <typename T>
typename Deque<T>::reference
Deque<T>::front()
{
    assert(!empty());
    if (!front_.empty()) {
        return front_.back();
    }
    return back_.front();
}

template <typename T>
typename Deque<T>::const_reference
Deque<T>::front() const
{
    assert(!empty());
    if (!front_.empty()) {
        return front_.back();
    }
    return back_.front();
}

template <typename T>
typename Deque<T>::reference
Deque<T>::back()
{
    assert(!empty());
    if (!back_.empty()) {
        return back_.back();
    }
    return front_.front();
}

template <typename T>
typename Deque<T>::const_reference
Deque<T>::back() const
{
    assert(!empty());
    if (!back_.empty()) {
        return back_.back();
    }
    return front_.front();
}

template <typename T>
void
Deque<T>::resize(const size_type newSize, const_reference initialValue)
{
    const size_type currentSize = size();
    if (newSize == currentSize) return;

    for (size_type i = newSize; i < currentSize; ++i) {
        pop_back();
    }
    for (size_type i = currentSize; i < newSize; ++i) {
        push_back(initialValue);
    }
}

template <typename T>
typename Deque<T>::size_type
Deque<T>::max_size() const
{
    return std::numeric_limits<size_type>::max() / sizeof(T);
}

template <typename T>
typename Deque<T>::size_type
Deque<T>::size() const
{
    return front_.size() + back_.size();
}

template <typename T>
bool
Deque<T>::empty() const
{
    return back_.empty() && front_.empty();
}

template <typename T>
void
Deque<T>::clear()
{
    back_.clear();
    front_.clear();
}

template <typename T>
void
Deque<T>::swap(Deque<T>& rhv)
{
    front_.swap(rhv.front_);
    back_.swap(rhv.back_);
}

template <typename T>
typename Deque<T>::iterator 
Deque<T>::begin() 
{
    return iterator(this, (!front_.empty()) ? &front_.back() : &back_.front());
}

template <typename T>
typename Deque<T>::iterator 
Deque<T>::end()
{
    return iterator(this, (!back_.empty()) ? &back_.back() : &front_.front());
}

template <typename T>
typename Deque<T>::const_iterator 
Deque<T>::begin() const
{
    return const_iterator(this, (!front_.empty()) ? &front_.back() : &back_.front());
}

template <typename T>
typename Deque<T>::const_iterator 
Deque<T>::end() const
{
    return const_iterator(this, (!back_.empty()) ? &back_.back() : &front_.front());
}

template <typename T>
typename Deque<T>::reverse_iterator
Deque<T>::rbegin()
{
    return reverse_iterator(this, (!back_.empty()) ? &back_.back() : &front_.front());
}

template <typename T>
typename Deque<T>::reverse_iterator
Deque<T>::rend()
{
    return reverse_iterator(this, (!front_.empty()) ? &front_.back() : &back_.front());
}

template <typename T>
typename Deque<T>::const_reverse_iterator
Deque<T>::rbegin() const
{
    return const_reverse_iterator(this, (!back_.empty()) ? &back_.back() : &front_.front());
}

template <typename T>
typename Deque<T>::const_reverse_iterator
Deque<T>::rend() const
{
    return const_reverse_iterator(this, (!front_.empty()) ? &front_.back() : &back_.front());
}

template <typename T>
typename Deque<T>::reference
Deque<T>::at_index(const size_type index)
{
    return (*this)[index];
}

template <typename T>
typename Deque<T>::const_reference
Deque<T>::at_index(const size_type index) const
{
    return (*this)[index];
}

///==================================CONST_ITERATOR======================

template <typename T>
Deque<T>::const_iterator::const_iterator()
    : deque_(NULL)
    , ptr_(NULL)
{}

template <typename T>
Deque<T>::const_iterator::const_iterator(const const_iterator& rhv)
    : deque_(rhv.deque_)
    , ptr_(rhv.ptr_)
{}

template <typename T>
Deque<T>::const_iterator::~const_iterator()
{
    deque_ = NULL;
    ptr_   = NULL;
}

template <typename T>
Deque<T>::const_iterator::const_iterator(const Deque<T>* deque, const_pointer ptr)
    : deque_(deque)
    , ptr_(ptr)
{}

template <typename T>
typename Deque<T>::const_iterator&
Deque<T>::const_iterator::operator=(const const_iterator& rhv)
{
    if (this == &rhv) return *this;
    deque_ = rhv.deque_;
    ptr_ = rhv.ptr_;
    return *this;
}

template <typename T>
typename Deque<T>::const_reference
Deque<T>::const_iterator::operator*() const
{
     return const_cast<reference>(*(this->getPtr())); 
}

template <typename T>
typename Deque<T>::const_pointer
Deque<T>::const_iterator::operator->() const
{
    return const_cast<pointer>(this->getPtr());
}

template <typename T>
typename Deque<T>::const_reference
Deque<T>::const_iterator::operator[](const size_type index) const
{
    if (index < &deque_->front_.size()) {
        return &deque_->front_[&deque_->size() - index - 1];
    }
    return &deque_->back_[index - &deque_->front_.size()];
}

template <typename T>
typename Deque<T>::const_iterator&
Deque<T>::const_iterator::operator++()
{
    if (ptr_ == &deque_->back_.back()) return *this;

    if (ptr_ == (&deque_->front_.front())) {
        ptr_ = &deque_->back_.front();
        return *this;
    }
    if (ptr_ > &deque_->front_.front() && ptr_ < &deque_->front_.back() + 1) {
        --ptr_;
        return *this;
    }
    ++ptr_;
    return *this;
}

template <typename T>
typename Deque<T>::const_iterator
Deque<T>::const_iterator::operator++(int)
{
    const_iterator temp(*this);
    ++(*this);
    return temp;
}

template <typename T>
typename Deque<T>::const_iterator&
Deque<T>::const_iterator::operator--()
{
    if (ptr_ == &deque_->front_.back()) return *this;
 
    if (ptr_ == (&deque_->back_.front())) {
        ptr_ = &deque_->front_.front();
        return *this;
    }

    if (ptr_ > &deque_->front_.front() && ptr_ < &deque_->front_.back() + 1) {
        ++ptr_;
        return *this;
    }
    --ptr_;
    return *this;
}

template <typename T>
typename Deque<T>::const_iterator
Deque<T>::const_iterator::operator--(int)
{
    const_iterator temp(*this);
    --(*this);
    return temp;
}

template <typename T>
typename Deque<T>::const_iterator
Deque<T>::const_iterator::operator+(const size_type index) const
{
    if (ptr_ == &deque_->back_.back()) return const_iterator(ptr_);

    pointer newPtr = ptr_ - index;
    if (newPtr > &deque_->front_.front() && newPtr < &deque_->front_.back() + 1) {
        return const_iterator(newPtr);
    }

    if (ptr_ > &deque_->front_.front() && ptr_ < &deque_->front_.back() + 1 && newPtr > &deque_->front_.back() + 1) {
        return const_iterator(&deque_->back_.front() + (index - (&deque_->front_.back() - 1 - ptr_)));  
    }
    return const_iterator(&deque_->back_.front() + index);
}

template <typename T>
typename Deque<T>::const_iterator
Deque<T>::const_iterator::operator-(const size_type index) const
{
    if (ptr_ == &deque_->front_.back()) return *this;

    pointer newPtr = ptr_ + index;
    if (newPtr > &deque_->back_.front() && newPtr < &deque_->back_.back() + 1) {
        return const_iterator(newPtr);
    }

    if (ptr_ > &deque_->back_.front() && ptr_ < &deque_->back_.back() + 1 && newPtr < &deque_->back_.front()) {
        return const_iterator(&deque_->front_.back() + 1 - (index - (ptr_ - &deque_->back_.front())));  
    }
    return const_iterator(&deque_->front_.back() + 1 - index);

}

template <typename T>
typename Deque<T>::const_iterator&
Deque<T>::const_iterator::operator+=(const size_type size)
{
    ptr_ = ptr_ + size;
    return *this;
}

template <typename T>
typename Deque<T>::const_iterator&
Deque<T>::const_iterator::operator-=(const size_type size)
{
    ptr_ = ptr_ - size;
    return *this;
}

template <typename T>
bool
Deque<T>::const_iterator::operator==(const const_iterator& rhv) const
{
    return ptr_ == rhv.ptr_ && deque_ == rhv.deque_;
}

template <typename T>
bool
Deque<T>::const_iterator::operator!=(const const_iterator& rhv) const
{
    return !(*this == rhv);
}

template <typename T>
bool
Deque<T>::const_iterator::operator<(const const_iterator& rhv) const
{
    return ptr_ < rhv.ptr_;
}

template <typename T>
bool
Deque<T>::const_iterator::operator>(const const_iterator& rhv) const
{
    return rhv < *this;
}

template <typename T>
bool
Deque<T>::const_iterator::operator<=(const const_iterator& rhv) const 
{
    return !(*this > rhv);
}

template <typename T>
bool
Deque<T>::const_iterator::operator>=(const const_iterator& rhv) const
{ 
    return !(*this < rhv);
}

template <typename T>
const Deque<T>*
Deque<T>::const_iterator::getDeque() const
{
    return deque_;
}

template <typename T>
typename Deque<T>::const_pointer
Deque<T>::const_iterator::getPtr() const
{
    return ptr_;
}

///====================================================ITERATOR==============================================

template <typename T>
Deque<T>::iterator::iterator()
    : const_iterator()
{}

template <typename T>
Deque<T>::iterator::iterator(const iterator& rhv)
    : const_iterator(rhv.getDeque(), rhv.getPtr())
{}

template <typename T>
Deque<T>::iterator::~iterator()
{}

template <typename T>
Deque<T>::iterator::iterator(const Deque<T>* deque, pointer ptr)
    : const_iterator(deque, ptr)
{}

template <typename T>
typename Deque<T>::reference
Deque<T>::iterator::operator*() const
{
    return const_cast<reference>(*this->getPtr());
}

template <typename T>
typename Deque<T>::pointer
Deque<T>::iterator::operator->() const
{
    return const_cast<pointer>(this->getPtr());
}

template <typename T>
typename Deque<T>::reference
Deque<T>::iterator::operator[](const size_type index) const
{
    if (index < this->deque_->front_.size()) {
        return const_cast<reference>(this->deque_->front_[this->deque_->size() - index - 1]);
    }
    return const_cast<reference>(this->deque_->back_[index - this->deque_->front_.size()]);

}

template <typename T>
typename Deque<T>::iterator
Deque<T>::iterator::operator+(const size_type size) const
{
    if (this->ptr_ == &this->deque_->back_.back()) return iterator(this->getDeque(), const_cast<pointer>(this->getPtr()));

    pointer newPtr = const_cast<pointer>(this->ptr_ - size);
    if (newPtr > &this->deque_->front_.front() && newPtr < &this->deque_->front_.back() + 1) {
        return iterator(this->getDeque(), const_cast<pointer>(newPtr)) ;
    }
    const_pointer first = &this->deque_->front_.front();
    const_pointer first_back = &this->deque_->front_.back();
    if (this->ptr_ > first && this->ptr_ < first_back && newPtr > first_back + 1) {
        return iterator(this->getDeque(), const_cast<pointer>(&this->deque_->back_.front() + (size - (&this->deque_->front_.back() + 1 - this->ptr_))));  
    }
    return iterator(this->getDeque(), const_cast<pointer>(&this->deque_->back_.front() + size));

}

template <typename T>
typename Deque<T>::iterator
Deque<T>::iterator::operator-(const size_type size) const
{
    if (this->ptr_ == &this->deque_->front_.back()) return *this;

    pointer newPtr = const_cast<pointer>(this->ptr_ + size);
    if (newPtr > &this->deque_->back_.front() && newPtr < &this->deque_->back_.back()) {
        return iterator(this->getDeque(), const_cast<pointer>(newPtr));
    }

    if (this->ptr_ > &this->deque_->back_.front() && this->ptr_ < &this->deque_->back_.back() + 1 && newPtr < &this->deque_->back_.front()) {
        return iterator(this->getDeque(), const_cast<pointer>(&this->deque_->front_.back() + 1 - (size - (this->ptr_ - &this->deque_->back_.front()))));  
    }
    return iterator(this->getDeque(), const_cast<pointer>(&this->deque_->front_.back() + 1 - size));

}

///==================================CONST_REVERSE_ITERATOR======================

template <typename T>
Deque<T>::const_reverse_iterator::const_reverse_iterator()
    : deque_(NULL)
    , ptr_(NULL)
{}

template <typename T>
Deque<T>::const_reverse_iterator::const_reverse_iterator(const const_reverse_iterator& rhv)
    : deque_(rhv.deque_)
    , ptr_(rhv.ptr_)
{}

template <typename T>
Deque<T>::const_reverse_iterator::~const_reverse_iterator()
{
    deque_ = NULL;
    ptr_   = NULL;
}

template <typename T>
Deque<T>::const_reverse_iterator::const_reverse_iterator(const Deque<T>* deque, const_pointer ptr)
    : deque_(deque)
    , ptr_(ptr)
{}

template <typename T>
typename Deque<T>::const_reverse_iterator&
Deque<T>::const_reverse_iterator::operator=(const const_reverse_iterator& rhv)
{
    if (this == &rhv) return *this;
    deque_ = rhv.deque_;
    ptr_ = rhv.ptr_;
    return *this;
}

template <typename T>
typename Deque<T>::const_reference
Deque<T>::const_reverse_iterator::operator*() const
{
     return const_cast<reference>(*(this->getPtr())); 
}

template <typename T>
typename Deque<T>::const_pointer
Deque<T>::const_reverse_iterator::operator->() const
{
    return const_cast<pointer>(this->getPtr());
}

template <typename T>
typename Deque<T>::const_reference
Deque<T>::const_reverse_iterator::operator[](const size_type index) const
{
    if (index < &deque_->front_.size()) {
        return &deque_->front_[&deque_->size() - index - 1];
    }
    return &deque_->back_[index - &deque_->front_.size()];
}

template <typename T>
typename Deque<T>::const_reverse_iterator&
Deque<T>::const_reverse_iterator::operator++()
{
    if (ptr_ == &deque_->front_.back()) return *this;
 
    if (ptr_ == (&deque_->back_.front())) {
        ptr_ = &deque_->front_.front();
        return *this;
    }

    if (ptr_ > &deque_->front_.front() && ptr_ < &deque_->front_.back() + 1) {
        ++ptr_;
        return *this;
    }
    --ptr_;
    return *this;

}

template <typename T>
typename Deque<T>::const_reverse_iterator
Deque<T>::const_reverse_iterator::operator++(int)
{
    const_reverse_iterator temp(*this);
    ++(*this);
    return temp;
}

template <typename T>
typename Deque<T>::const_reverse_iterator&
Deque<T>::const_reverse_iterator::operator--()
{
    if (ptr_ == &deque_->back_.back()) return *this;

    if (ptr_ == (&deque_->front_.front())) {
        ptr_ = &deque_->back_.front();
        return *this;
    }
    if (ptr_ > &deque_->front_.front() && ptr_ < &deque_->front_.back() + 1) {
        --ptr_;
        return *this;
    }
    ++ptr_;
    return *this;

}

template <typename T>
typename Deque<T>::const_reverse_iterator
Deque<T>::const_reverse_iterator::operator--(int)
{
    const_reverse_iterator temp(*this);
    --(*this);
    return temp;
}

template <typename T>
typename Deque<T>::const_reverse_iterator
Deque<T>::const_reverse_iterator::operator+(const size_type index) const
{
    if (ptr_ == &deque_->front_.back()) return *this;

    pointer newPtr = ptr_ + index;
    if (newPtr > &deque_->back_.front() && newPtr < &deque_->back_.back() + 1) {
        return const_reverse_iterator(newPtr);
    }

    if (ptr_ > &deque_->back_.front() && ptr_ < &deque_->back_.back() + 1 && newPtr < &deque_->back_.front()) {
        return const_reverse_iterator(&deque_->front_.back() + 1 - (index - (ptr_ - &deque_->back_.front())));  
    }
    return const_reverse_iterator(&deque_->front_.back() + 1 - index);

}

template <typename T>
typename Deque<T>::const_reverse_iterator
Deque<T>::const_reverse_iterator::operator-(const size_type index) const
{
    if (ptr_ == &deque_->back_.back()) return const_reverse_iterator(ptr_);

    pointer newPtr = ptr_ - index;
    if (newPtr > &deque_->front_.front() && newPtr < &deque_->front_.back() + 1) {
        return const_reverse_iterator(newPtr);
    }

    if (ptr_ > &deque_->front_.front() && ptr_ < &deque_->front_.back() + 1 && newPtr > &deque_->front_.back() + 1) {
        return const_reverse_iterator(&deque_->back_.front() + (index - (&deque_->front_.back() - 1 - ptr_)));  
    }
    return const_reverse_iterator(&deque_->back_.front() + index);

}

template <typename T>
typename Deque<T>::const_reverse_iterator&
Deque<T>::const_reverse_iterator::operator+=(const size_type size)
{
    ptr_ = ptr_ - size;
    return *this;
}

template <typename T>
typename Deque<T>::const_reverse_iterator&
Deque<T>::const_reverse_iterator::operator-=(const size_type size)
{
    ptr_ = ptr_ + size;
    return *this;
}

template <typename T>
bool
Deque<T>::const_reverse_iterator::operator==(const const_reverse_iterator& rhv) const
{
    return ptr_ == rhv.ptr_ && deque_ == rhv.deque_;
}

template <typename T>
bool
Deque<T>::const_reverse_iterator::operator!=(const const_reverse_iterator& rhv) const
{
    return !(*this == rhv);
}

template <typename T>
bool
Deque<T>::const_reverse_iterator::operator<(const const_reverse_iterator& rhv) const
{
    return ptr_ < rhv.ptr_;
}

template <typename T>
bool
Deque<T>::const_reverse_iterator::operator>(const const_reverse_iterator& rhv) const
{
    return rhv < *this;
}

template <typename T>
bool
Deque<T>::const_reverse_iterator::operator<=(const const_reverse_iterator& rhv) const 
{
    return !(*this > rhv);
}

template <typename T>
bool
Deque<T>::const_reverse_iterator::operator>=(const const_reverse_iterator& rhv) const
{ 
    return !(*this < rhv);
}

template <typename T>
const Deque<T>*
Deque<T>::const_reverse_iterator::getDeque() const
{
    return deque_;
}

template <typename T>
typename Deque<T>::const_pointer
Deque<T>::const_reverse_iterator::getPtr() const
{
    return ptr_;
}

///====================================================reverse_iterator==============================================

template <typename T>
Deque<T>::reverse_iterator::reverse_iterator()
    : const_reverse_iterator()
{}

template <typename T>
Deque<T>::reverse_iterator::reverse_iterator(const reverse_iterator& rhv)
    : const_reverse_iterator(rhv.getDeque(), rhv.getPtr())
{}

template <typename T>
Deque<T>::reverse_iterator::~reverse_iterator()
{}

template <typename T>
Deque<T>::reverse_iterator::reverse_iterator(const Deque<T>* deque, pointer ptr)
    : const_reverse_iterator(deque, ptr)
{}

template <typename T>
typename Deque<T>::reference
Deque<T>::reverse_iterator::operator*() const
{
    return const_cast<reference>(*this->getPtr());
}

template <typename T>
typename Deque<T>::pointer
Deque<T>::reverse_iterator::operator->() const
{
    return const_cast<pointer>(this->getPtr());
}

template <typename T>
typename Deque<T>::reference
Deque<T>::reverse_iterator::operator[](const size_type index) const
{
    if (index < this->deque_->front_.size()) {
        return const_cast<reference>(this->deque_->front_[this->deque_->size() - index - 1]);
    }
    return const_cast<reference>(this->deque_->back_[index - this->deque_->front_.size()]);

}

template <typename T>
typename Deque<T>::reverse_iterator
Deque<T>::reverse_iterator::operator+(const size_type size) const
{
    if (this->ptr_ == &this->deque_->front_.back()) return *this;

    pointer newPtr = const_cast<pointer>(this->ptr_ + size);
    if (newPtr > &this->deque_->back_.front() && newPtr < &this->deque_->back_.back()) {
        return reverse_iterator(this->getDeque(), const_cast<pointer>(newPtr));
    }

    if (this->ptr_ > &this->deque_->back_.front() && this->ptr_ < &this->deque_->back_.back() + 1 && newPtr < &this->deque_->back_.front()) {
        return reverse_iterator(this->getDeque(), const_cast<pointer>(&this->deque_->front_.back() + 1 - (size - (this->ptr_ - &this->deque_->back_.front()))));  
    }
    return reverse_iterator(this->getDeque(), const_cast<pointer>(&this->deque_->front_.back() + 1 - size));

}

template <typename T>
typename Deque<T>::reverse_iterator
Deque<T>::reverse_iterator::operator-(const size_type size) const
{
    if (this->ptr_ == &this->deque_->back_.back()) return reverse_iterator(this->getDeque(), const_cast<pointer>(this->getPtr()));

    pointer newPtr = const_cast<pointer>(this->ptr_ - size);
    if (newPtr > &this->deque_->front_.front() && newPtr < &this->deque_->front_.back() + 1) {
        return reverse_iterator(this->getDeque(), const_cast<pointer>(newPtr)) ;
    }
    const_pointer first = &this->deque_->front_.front();
    const_pointer first_back = &this->deque_->front_.back();
    if (this->ptr_ > first && this->ptr_ < first_back && newPtr > first_back + 1) {
        return reverse_iterator(this->getDeque(), const_cast<pointer>(&this->deque_->back_.front() + (size - (&this->deque_->front_.back() + 1 - this->ptr_))));  
    }
    return reverse_iterator(this->getDeque(), const_cast<pointer>(&this->deque_->back_.front() + size));

}

