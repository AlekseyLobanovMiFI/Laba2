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
        ListSequence<T>* GetSubsequence(int startIndex, int endIndex)const override{
            LinkedList<T>* temp = list.GetSubList(startIndex, endIndex);
            ListSequence<T>* result = new  ListSequence<T>(*temp);
            delete temp;
            return result;
        }
        int GetLength()const override{
            return list.GetLength();
        }
        ListSequence<T>* Append(T item) override{
            list.Append(item);
            return this;
        }
        ListSequence<T>* Prepend(T item) override{
            list.Prepend(item);
            return this;
        } 
        ListSequence<T>* InsertAt(T item, int index) override{
            list.InsertAt(item, index);
            return this;
        }

        ListSequence<T>* NewEmpty() const override{
            return new ListSequence<T>();
        }
        
        ListSequence (T* items, int count) : list(items, count){} 
        ListSequence () : list(){}
        ListSequence (const ListSequence<T> & listSeq) : list(listSeq.list){}
        ListSequence (const LinkedList<T> & listLink) : list(listLink){}

};