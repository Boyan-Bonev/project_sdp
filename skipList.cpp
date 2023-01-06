#include "skipList.h"
#include <iostream>

template <typename T>
bool Iterator<T>::operator< (const Iterator<T>& other) {
    if (*this == other || !this->valid() || !other.valid()) {
        return false;
    }
    Iterator<T> copy = *this;
    while (copy.valid()) {
        if (copy == other) {
            return true;
        }
        copy++;
    }
    return false;
}

template <typename T>
bool Iterator<T>::skipIsValid () {
    if (!ptr || !ptr->pSkip) {
        return false;
    }
    Iterator<T> copy = *this;
    Iterator<T> skipLocation = Iterator(ptr->pSkip);
    while (copy.next() != skipLocation) {
        if (copy.next().wantsToVisit()) {
            return false;
        }
        copy++;
    }
    return true;
}

template <typename T>
void SkipList<T>:: copy (SkipList<T> const& other) {
    if (other.empty()) {
        return;
    }
    back = front = new Node<T> (other.front->data);
    Node<T>* next = other.front;
    size = 1;
    while (next->pNext != nullptr) {
        next = next->pNext;
        back->pNext = new Node<T> (next->data);
        back = back->pNext;
        ++size;
    }
}

template <typename T>
void SkipList<T>:: erase() {
    Node<T>* toDel = front;
    while (front != nullptr) {
        front = front->pNext;
        delete toDel;
        toDel = front;
    }
    back = nullptr;
    size = 0;
}

template <typename T>
Iterator<T> SkipList<T>:: findPrev (iter pos) const {
    iter result = front;
    while (result.valid() && result.next() != pos) {
        result++;
    }
    return result;
    // !result.valid() -> returns nullptr
    // result.next() == pos -> returns result
}

template <typename T>
void SkipList<T>::print () const {
    iter it = begin();
    for (;it.valid();it++) {
        std::cout << it.get();
        if (it.next().valid()) {
            std::cout << " -> ";
        }
    }
    std::cout << '\n';
}

template <typename T>
T SkipList<T>:: deleteFirst () {
    if (empty()) 
        throw std::runtime_error ("deleteFirst() : Empty List!");
    Node<T>* toDel = front;
    T deletedData = toDel->data;
    front = front->pNext;
    --size;
    delete toDel;
    toDel = nullptr;
    return deletedData;
}

template <typename T>
T SkipList<T>:: deleteLast () {
    if (empty()) {
        throw std::runtime_error ("deleteLast() : Empty List!");
    }
    if (front == back) {
        T deletedData = front->data;
        delete front;
        front = back = nullptr;
        --size;
        return deletedData;
    }
    else {
        iter last = iter(back);
        //remove skips to last
        iter start = begin();
        while (start != last) {
            if (start.ptr->pSkip == last.ptr) {
                start.ptr->pSkip = nullptr;
            }
            start++;
        }

        iter secondToLast = findPrev(last);
        back = secondToLast.ptr;
        return deleteAfter(secondToLast);
    }
}

template <typename T>
T SkipList<T>:: deleteAfter (iter pos) {
    if (empty() || !pos.valid() || !pos.next().valid()) {
        throw std::runtime_error ("deleteAfter() : Empty List/Incorrect Position");
    }
    
    // remove skips to current location
    iter start = begin();
    iter next = pos.next();
    while (start != next) {
        if (start.ptr->pSkip == next.ptr) {
            start.ptr->pSkip = nullptr;
        }
        start++;
    }
    
    Node<T>* toDel = next.ptr;
    T deletedData = toDel->data;
    pos.ptr->pNext = toDel ->pNext;
    delete toDel;
    toDel = nullptr;
    --size;
    return deletedData;
}

template <typename T>
void SkipList<T>:: insertFirst (T const& elem, iter skipPos) {
    Node<T>* newNode = new Node<T> (elem, front, skipPos.ptr);
    if (empty()) {
    front = back = newNode;
    }
    else 
        front = newNode;
    ++size;
}

template <typename T>
void SkipList<T>:: insertLast(T const& elem) {
    Node<T>* newNode = new Node<T> (elem);
    ++size;
    if (empty()) {
        front = back = newNode;
    }
    else {
        back->pNext = newNode;
        back = back->pNext;
    }
}

template <typename T>
bool SkipList<T>:: insertAfter (iter pos, T const& elem, iter skipPos) {
    if (empty()) {
        insertFirst(elem);
    }
    else {
        Node<T>* newNode = new Node<T> (elem,pos.next().ptr, skipPos.ptr);
        pos.ptr->pNext = newNode;
        if (pos.ptr == back) {
            back = newNode;
        }
        ++size;
    }
    return true;
}

template <typename T>
bool SkipList<T>::addSkip (iter pos, iter to) {
    if (pos.valid() && to.valid() && pos < to) {
        pos.ptr->pSkip = to.ptr;
        return true;
    }
    return false;
}

template <typename T>
bool SkipList<T>::useSkip(iter& pos) {
    return pos.skip();
}

template <typename T>
Iterator<T> SkipList<T>::findElem(T const& elem) const {
    iter it = begin();
    while (it.valid() && it.get() != elem) {
        it++;
    }
    return it;
}

template <typename T>
SkipList<T> SkipList<T>::findShortestRoute() const {
    if (empty()) {
        return SkipList<T>();
    }
    SkipList<T> result;
    iter it = begin();
    result.insertFirst(it.get());
    while (it.valid()) {
        if(it.skipIsValid()) {
            it.skip(); // make skip
            result.insertLast(it.get()); // insert current
        }
        else {
            it++;
            if (it.valid()) {
                result.insertLast(it.get()); // insert next
            }
        }
    }
    return result;
}