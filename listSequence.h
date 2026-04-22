#ifndef LIST_SEQUENCE_H
#define LIST_SEQUENCE_H

#include "sequence.h"
#include "linkedList.h"

template <class T> class ListSequence : public Sequence<T>{
private:
    LinkedList<T> list;

public:
    T GetFirst() const override{
        return list.GetFirst();
    }

    T GetLast() const override{
        return list.GetLast();
    }

    T Get(int index) const override{
        return list.Get(index);
    }

    ListSequence<T>* GetSubsequence(int startIndex, int endIndex) const override {
        if (startIndex < 0 || endIndex >= list.GetLength() || startIndex > endIndex) {
            throw std::out_of_range("IndexOutOfRange");
        }

        LinkedList<T>* subList = list.GetSubList(startIndex, endIndex);
        ListSequence<T>* result = new ListSequence<T>(*subList);
        return result;
}

    int GetLength()const override{
        return list.GetLength();
    }

    ListSequence<T>* Append(const T& item) override{
        list.Append(item);
        return this;
    }

    ListSequence<T>* Prepend(const T& item) override{
        list.Prepend(item);
        return this;
    } 

    ListSequence<T>* InsertAt(const T& item, int index) override{
        list.InsertAt(item, index);
        return this;
    }

    ListSequence<T>* NewEmpty() const override{
        return new ListSequence<T>();
    }

    using ListPosition = typename LinkedList<T>::ListPosition;
    virtual ListSequence<T>* Concat(ListSequence<T>* const lst) {
        ListPosition current = lst->list.GetFirstPos();
        while(LinkedList<T>::IsNotLastPos(current)){
            Append(LinkedList<T>::Get(current));
            current = LinkedList<T>::GetNextPos(current);
        }

        return this;
    }
    
    ListSequence (const T* items, int count) : list(items, count){} 
    ListSequence () : list(){}
    ListSequence (const ListSequence<T> & listSeq) : list(listSeq.list){}
    ListSequence (const LinkedList<T> & listLink) : list(listLink){}

};

#endif