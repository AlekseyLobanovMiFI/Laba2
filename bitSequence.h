#include <climits>
#include "Sequence.h"
#include "dynamicArray.h"


class BitSequence : public Sequence<bool>{
    private:

        typedef unsigned int BlockType;
        DynamicArray<BlockType> blocks;
        static const unsigned int bit_per_block = sizeof(BlockType) * CHAR_BIT;
        int length;

        static int GetBlock(int index){
            return index / bit_per_block;
        }

        static int GetBitBlock(int index){//просто вызываются без this
            return index % bit_per_block;
        }


    public:

        bool operator[](int index) const{return Get(index);}


        BitSequence (bool* items, int cnt) : blocks(GetBlock(cnt + (bit_per_block - 1))), length(cnt){
            for (int i=0; i<cnt; i++){
                blocks[GetBlock(i)] |= items[i]<<GetBitBlock(i); //происходит побитовое сложение и все элементы кроме итого остаются
            }
        };
        BitSequence () : blocks(0), length(0){};
        BitSequence (int cnt) : blocks(GetBlock(cnt + (bit_per_block - 1))), length(cnt){};

        virtual ~BitSequence(){};

        virtual bool GetFirst() const override;
        virtual bool GetLast() const override;
        virtual bool Get(int index) const override; 
        virtual BitSequence* GetSubsequence(int startIndex, int endIndex) const override;
        virtual int GetLength() const override;

        virtual BitSequence* Append(bool item) override;
        virtual BitSequence* Prepend(bool item) override;
        virtual BitSequence* InsertAt(bool item, int index) override;

        virtual BitSequence* NewEmpty() const override{
            return new BitSequence;
        }

        BitSequence operator~() const{
            BitSequence result(*this);
            for (int i=0; i<GetLength();i++){
                //result[i] = !result[i];
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
                //result[i] = big[i] & small[i-index];
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
                //result[i] = big[i] | small[i-index];
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
                //result[i] = big[i] ^ small[i-index];
            }
            return result;
        }
};