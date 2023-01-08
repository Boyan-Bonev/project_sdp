#ifndef SKIPLIST_HPP
#define SKIPLIST_HPP

#include <stdexcept>

template <typename T>
class Iterator;
template <typename T>
class SkipList;

template <typename T>
struct Node {
    T data;
    Node<T>* pNext;
    Node<T>* pSkip;
    bool toVisit = false;
    Node(T const& _data, Node<T>* _pNext = nullptr, Node<T>* _pSkip = nullptr) : data(_data), pNext(_pNext), pSkip(_pSkip) {}
    operator Iterator<T>() const { return Iterator<T>(this);}
    Node<T>* copy() {
        Node<T>* copied = new Node<T> (data,pNext,pSkip);
        return copied;
    }
};


template <typename T>
class Iterator {
private:
    Node<T>* ptr;
    friend SkipList<T>;
public:
    Iterator ( Node<T>* _ptr = nullptr ) : ptr( _ptr ) {}

    bool operator== (const Iterator<T>& other) const { return ptr == other.ptr; }
    bool operator!= (const Iterator<T>& other) const { return !(other == *this); }
    // current is before other
    bool operator< (const Iterator<T>& other);
    operator Node<T>() const { return ptr;}

    // not skipping wanted locations
    bool skipIsValid();

    bool valid() const { return ptr != nullptr;}
    void nulify() { ptr = nullptr; }
    T& get() {
        if (!valid())
            throw std::runtime_error("get() : Invalid position!");
        return ptr->data;
    }

    const T& get() const {
        if (!valid())
            throw std::runtime_error("get() : Invalid position!");
        return ptr->data;
    }

    Node<T>* getPtr () {
        if (!valid()) 
            throw std::runtime_error("getPtr() : Invalid position!");
        return ptr;
    }

    Node<T>* getPtr () const {
        if (!valid()) 
            throw std::runtime_error("getPtr() : Invalid position!");
        return ptr;
    }

    Iterator<T> next() const {
        if (!valid())
            throw std::runtime_error("next() : Invalid position!");
        return ptr->pNext;
    }

    void addVisit() {
        if (!valid()) {
            return;
        }
        ptr->toVisit = true;
    }

    // current town is to be visited
    bool wantsToVisit() {
        if (!valid() || !ptr->toVisit)
            return false;
        return true;
    }

    Iterator<T> next() {
        if (!valid())
            throw std::runtime_error("next() : Invalid position!");
        return Iterator<T>(ptr->pNext);
    }

    // make skip
    bool skip() {
        if (!valid()) 
            throw std::runtime_error("skip() : Invalid position!");
        if (ptr->pSkip != nullptr) {
            ptr = ptr->pSkip;
            return true;
        }
        return false;
    }

    Iterator<T>  operator++ ( int ) {
        Iterator<T> save = *this;
        ++*this;
        return save;
    }

    Iterator<T>& operator++ () {
        ptr = ptr->pNext;
        return *this;
    }
};

template <typename T>
class SkipList {
public:
    using iter = Iterator<T>;
private:
    Node<T>* front;
    Node<T>* back;
    unsigned size;
    void copy (SkipList<T> const& other);
    void erase();
public:
    iter findPrev (iter pos) const ;
    SkipList() : front(nullptr), back(nullptr), size(0) {}
    SkipList(SkipList<T> const& other) { copy(other); }
    SkipList<T>& operator= (SkipList<T> const& other) {
        if (this != other) {
            erase();
            copy(other);
        }
        return *this;
    }
    ~SkipList () { erase(); }

    bool empty() const {return front == nullptr;}
    Node<T>* getFront() { return front; }
    Node<T>* getBack() { return back; }
    unsigned getSize() const {return size;}
    void print() const;
    void readRoute();
    // bug randomly fixed itself :)
    // for some reason every function that comes around here doesn't exist "in the mind" of SkipList.cpp
    // that's why I've added this random piece of code :)
    //long long functionToFixBug();
    void insertFirst (T const& elem, iter skipPos = nullptr);
    void insertLast(T const& elem);
    bool insertAfter (iter pos, T const& elem, iter skipPos = nullptr);
    T deleteFirst ();
    T deleteLast ();
    T deleteAfter (iter pos);
    bool addSkip(iter pos, iter skipPos);
    bool useSkip(iter& pos);
    Iterator<T> findElem(T const& elem) const;
    SkipList<T> findShortestRoute() const;

    iter begin() const { return iter(front); }
    iter last()  const { return iter(back); }
    iter end()   const { return iter(); }

};

// including it because I can't figure out how to properly link files
#include "skipList.cpp"

#endif