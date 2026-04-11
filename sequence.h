#ifndef SEQUENCE_H
#define SEQUENCE_H

template <class T> class Sequence{
    public:
        virtual T GetFirst() const=0;//абстрактная функция
        virtual T GetLast() const=0;
        virtual T Get(int index) const=0; 
        virtual Sequence<T>*GetSubsequence(int startIndex, int endIndex) const=0;
        virtual int GetLength() const=0;

        virtual Sequence<T>*Append(T item)=0;
        virtual Sequence<T>*Prepend(T item)=0;
        virtual Sequence<T>*InsertAt(T item, int index)=0; 

        virtual ~Sequence(){};

        Sequence<T>* Concat(Sequence<T>* seq) {

            for (int i = 0; i < seq->GetLength(); i++) {
                Append(seq->Get(i));
            }

            return this;
        }

        //virtual Sequence<T>* NewEmpty() const =0;
        virtual Sequence<T>* NewEmpty() const { return nullptr; }

        virtual Sequence <T>* Map(T (*func)(T)) const{
            Sequence <T>* result = this->NewEmpty();

            for (int i = 0; i < GetLength(); i++) {
                result->Append(func(Get(i)));
            }

            return result;

        }

        virtual Sequence <T>* Where(bool (*func)(T)) const{
            Sequence <T>* result = this->NewEmpty();

            for (int i = 0; i < GetLength(); i++) {
                T item = Get(i);
                if (func(item)){
                    result->Append(item);
                }
            }

            return result;

        }

        T Reduce(T init, T (*func)(T,T)) const{
            T res = init;

            for (int i = 0; i < GetLength(); i++) {
                res = func(res, Get(i));
            }

            return res;

        }



        //Option<T> try GetFirst(bool (*func)(T) = 0);
        //Option<T> GetLast(bool (*func)(T)  = 0); 
};

template <class T>std::ostream& operator<<(std::ostream& os, const Sequence<T>& s){
    for (int i = 0; i < s.GetLength(); ++i) {
        os << s.Get(i) << " ";
    }

    return os;
}

#endif