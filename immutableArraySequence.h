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

        //virtual ImmutableArraySequence<T>* NewEmpty() const override{
            //return new ImmutableArraySequence<T>;
        //}
        virtual Sequence<T>* NewEmpty() const override {
            return new ImmutableArraySequence<T>();
        }

        Sequence<T>* Map(T (*func)(T)) const override {
        int n = this->GetLength();
        if (n == 0) return ArraySequence<T>::NewEmpty(); // или new ImmutableArraySequence<T>;

        
        ImmutableArraySequence<T> result(n);
        for (int i = 0; i < n; ++i) {
            result[i] = func(this->Get(i));
        }
        return new ImmutableArraySequence<T>(result);
    }

    Sequence<T>* Where(bool (*func)(T)) const override {
        int n = this->GetLength();
        if (n == 0) return ArraySequence<T>::NewEmpty();

    
        MutableArraySequence<T> buffer;
        for (int i = 0; i < n; ++i) {
            T item = this->Get(i);
            if (func(item)) {
                buffer.Append(item);
            }
        }

        
        if (buffer.GetLength() == 0) {
            return new ImmutableArraySequence<T>();
        }

        
        ImmutableArraySequence<T> result(buffer.GetLength());
        for (int i = 0; i < buffer.GetLength(); ++i) {
            result[i] = buffer.Get(i);
        }
        return new ImmutableArraySequence<T>(result);
    }

        ImmutableArraySequence (T* items, int count) : ArraySequence<T>(items, count){};
        ImmutableArraySequence () : ArraySequence<T>(){};
        ImmutableArraySequence (const ImmutableArraySequence & seq) : ArraySequence<T>(seq){};
        ImmutableArraySequence (int cnt) : ArraySequence<T>(cnt){};

};
