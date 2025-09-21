#ifndef __DEQUE_HPP__
#define __DEQUE_HPP__

#include <cstdlib>
#include <vector>

template <typename T>
class Deque
{
public:
    typedef size_t         size_type;
    typedef T              value_type;
    typedef T&             reference;
    typedef const T&       const_reference;
    typedef T*             pointer;
    typedef const T*       const_pointer;
    typedef std::ptrdiff_t difference_type;
                                          ///====CONST_ITERATOR====
public:
    class const_iterator {
    friend class Deque<T>;
    public:
        const_iterator();
        const_iterator(const const_iterator& rhv);
        ~const_iterator();
    
        const_iterator& operator=(const const_iterator& rhv);    
        const_reference operator*()                            const;
        const_pointer   operator->()                           const;
        const_reference operator[](const size_type index)    const;
        const_iterator& operator++();
        const_iterator  operator++(int);
        const_iterator& operator--();
        const_iterator  operator--(int);
        const_iterator  operator+(const size_type size)   const;
        const_iterator  operator-(const size_type size)   const;
        const_iterator& operator+=(const size_type size);
        const_iterator& operator-=(const size_type size);
        bool            operator==(const const_iterator& rhv)  const;
        bool            operator!=(const const_iterator& rhv)  const;
        bool            operator<(const const_iterator& rhv)   const;
        bool            operator>(const const_iterator& rhv)   const;
        bool            operator<=(const const_iterator& rhv)  const;
        bool            operator>=(const const_iterator& rhv)  const;

    protected:
        const Deque<T>* getDeque() const;
        const_pointer   getPtr()   const;

    private:
        explicit const_iterator(const Deque<T>* deque, const_pointer index);

    private:
        const Deque* deque_;
        const_pointer ptr_;
    };
                                        /// ====ITERATOR====
public:
    class iterator : public const_iterator {
    friend class Deque<T>;
    public:
        iterator();
        iterator(const iterator& rhv);
        ~iterator();
        
        reference       operator*()                       const;
        pointer         operator->()                      const;
        reference       operator[](const size_type index) const;
        iterator        operator+(const size_type size)   const;
        iterator        operator-(const size_type size)   const;

    private:
        explicit iterator(const Deque<T>* deque, pointer ptr);
    };
                            ///====CONST_REVERSE_ITERATOR====
public:
    class const_reverse_iterator {
    friend class Deque<T>;
    public:
        const_reverse_iterator();
        const_reverse_iterator(const const_reverse_iterator& rhv);
        ~const_reverse_iterator();
    
        const_reverse_iterator& operator=(const const_reverse_iterator& rhv);    
        const_reference         operator*()                            const;
        const_pointer           operator->()                           const;
        const_reference         operator[](const size_type index)    const;
        const_reverse_iterator& operator++();
        const_reverse_iterator  operator++(int);
        const_reverse_iterator& operator--();
        const_reverse_iterator  operator--(int);
        const_reverse_iterator  operator+(const size_type size)   const;
        const_reverse_iterator  operator-(const size_type size)   const;
        const_reverse_iterator& operator+=(const size_type size);
        const_reverse_iterator& operator-=(const size_type size);
        bool                    operator==(const const_reverse_iterator& rhv)  const;
        bool                    operator!=(const const_reverse_iterator& rhv)  const;
        bool                    operator<(const const_reverse_iterator& rhv)   const;
        bool                    operator>(const const_reverse_iterator& rhv)   const;
        bool                    operator<=(const const_reverse_iterator& rhv)  const;
        bool                    operator>=(const const_reverse_iterator& rhv)  const;

    protected:
        const Deque<T>* getDeque() const;
        const_pointer   getPtr()   const;

    private:
        explicit const_reverse_iterator(const Deque<T>* deque, const_pointer index);

    private:
        const Deque* deque_;
        const_pointer ptr_;
    };
                                        /// ====REVERSE_ITERATOR====
public:
    class reverse_iterator : public const_reverse_iterator {
    friend class Deque<T>;
    public:
        reverse_iterator();
        reverse_iterator(const reverse_iterator& rhv);
        ~reverse_iterator();
        
        reference        operator*()                       const;
        pointer          operator->()                      const;
        reference        operator[](const size_type index) const;
        reverse_iterator operator+(const size_type size)   const;
        reverse_iterator operator-(const size_type size)   const;

    private:
        explicit reverse_iterator(const Deque<T>* deque, pointer ptr);
    };

            ///======DEQUE======
public:
    Deque();
    Deque(const size_type newSize, const_reference initialValue = T()); 
    Deque(const int newSize, const_reference initialValue = T()); 
    Deque(const Deque<T>& rhv);
    template <typename InputIterator>
    Deque(InputIterator first, InputIterator last);
    ~Deque();

    Deque<T>&       operator=(const Deque<T>& rhv);
    bool            operator==(const Deque<T>& rhv)   const;
    bool            operator!=(const Deque<T>& rhv)   const;
    bool            operator<(const Deque<T>& rhv)    const;
    bool            operator>(const Deque<T>& rhv)    const;
    bool            operator<=(const Deque<T>& rhv)   const;
    bool            operator>=(const Deque<T>& rhv)   const;
    reference       operator[](const size_type index);
    const_reference operator[](const size_type index) const;
    
    template <typename InputIterator>
    void     insert(iterator position, InputIterator first, InputIterator last);
    iterator insert(iterator position, const_reference value);
    void     insert(iterator position, size_type size, const_reference value);
    iterator erase(iterator position);
    iterator erase(iterator first, iterator last);
    void push_front(const_reference value);
    void push_back(const_reference value); 
    void pop_front();
    void pop_back();
    reference       front();
    const_reference front() const;
    reference       back();
    const_reference back()  const; 

    void      resize(const size_type newSize, const_reference initialValue = T());
    size_type max_size() const;
    size_type size()     const;
    bool      empty()    const;
    void      clear();
    void      swap(Deque<T>& rhv);

    const_iterator         begin()  const; 
    const_iterator         end()    const;
    const_reverse_iterator rbegin() const;
    const_reverse_iterator rend()   const;

    iterator         begin();
    iterator         end();
    reverse_iterator rbegin();
    reverse_iterator rend();

private:
     reference       at_index(const size_type index);
     const_reference at_index(const size_type index) const;

private:
    std::vector<T> front_; 
    std::vector<T> back_; 

};

#include "../templates/Deque.cpp"

#endif /// __DEQUE_HPP__

