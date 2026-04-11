#include "arraySequence.h"

class Bit{
    private:
        bool value;
    public:
        Bit(bool bit=false) : value(bit){}


        bool Get() const{return value;}
        void Set(bool bit){value=bit;}

        operator bool() const {return value;}//bit->bool
        bool operator&(bool other) const {return value && other;}


};

class BitSequence : public ArraySequence<Bit>{
    public:
        virtual BitSequence* Instance() override { 
            return this; 
        }

        virtual BitSequence* CreateNewArray(Bit* items, int cnt) const override{
            return new BitSequence(items, cnt);
        }

        virtual BitSequence* NewEmpty() const override{
            return new BitSequence;
        }

        BitSequence (Bit* items, int count) : ArraySequence<Bit>(items, count){};
        BitSequence () : ArraySequence<Bit>(){};
        BitSequence (const BitSequence & bitSeq) : ArraySequence<Bit>(bitSeq){};
        BitSequence (int cnt) : ArraySequence<Bit>(cnt){};

        BitSequence operator~() const{
            BitSequence result(*this);
            for (int i=0; i<GetLength();i++){
                result[i] = !result[i];
            }
            return result;
        }
        BitSequence operator&(const BitSequence& right) const{
            int left_size = GetLength();  
            int right_size = right.GetLength();
            const BitSequence& small = left_size<right_size ? *this : right; 
            const BitSequence& big = left_size<right_size ? right : *this;
            int result_size = big.GetLength();
            BitSequence result(result_size);
            int index = big.GetLength() - small.GetLength();

            for (int i=index; i<result_size;i++){
                result[i] = big[i] & small[i-index];
            }
            return result;
        }
        BitSequence operator|(const BitSequence& right) const {
            int left_size  = GetLength();
            int right_size = right.GetLength();
            const BitSequence& small = left_size < right_size ? *this : right;
            const BitSequence& big = left_size < right_size ? right : *this;
            int result_size = big.GetLength();
            BitSequence result(result_size);
            int index = big.GetLength() - small.GetLength();

            for (int i = index; i < result_size; i++) {
                result[i] = big[i] | small[i-index];
            }
            return result;
        }
        BitSequence operator^(const BitSequence& right) const {
            int left_size  = GetLength();
            int right_size = right.GetLength();
            const BitSequence& small = left_size < right_size ? *this : right;
            const BitSequence& big = left_size < right_size ? right : *this;
            int result_size = big.GetLength();
            BitSequence result(result_size);
            int index = big.GetLength() - small.GetLength();

            for (int i = index; i < result_size; i++) {
                result[i] = big[i] ^ small[i-index];
            }
            return result;
        }
};