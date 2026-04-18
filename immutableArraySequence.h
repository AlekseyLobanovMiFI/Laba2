#ifndef IMMUTABLE_ARRAY_SEQUENCE_H
#define IMMUTABLE_ARRAY_SEQUENCE_H

#include "arraySequence.h"

template<class T> class ImmutableArraySequence : public ArraySequence<T>{
    private:
    
    public:
        virtual ImmutableArraySequence<T>* Instance() override { 
            return new ImmutableArraySequence(*this); 
        }

        virtual ImmutableArraySequence<T>* CreateNewArray(T* items, int cnt) const override{
            return new ImmutableArraySequence<T>(items, cnt);
        }

        virtual ImmutableArraySequence<T>* NewEmpty() const override {
            return new ImmutableArraySequence<T>();
        }

        ImmutableArraySequence (T* items, int count) : ArraySequence<T>(items, count){};
        ImmutableArraySequence () : ArraySequence<T>(){};
        ImmutableArraySequence (const ImmutableArraySequence & seq) : ArraySequence<T>(seq){};
        ImmutableArraySequence (int cnt) : ArraySequence<T>(cnt){};

};

#endif