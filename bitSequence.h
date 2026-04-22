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


    BitSequence (const bool* items, int cnt) : blocks(GetBlock(cnt + (bit_per_block - 1))), length(cnt){
        for (int i=0; i<cnt; i++){
            blocks[GetBlock(i)] |= items[i]<<GetBitBlock(i); //происходит побитовое сложение и все элементы кроме итого остаются
        }
    };
    BitSequence () : blocks(0), length(0){};
    BitSequence (int cnt) : blocks(GetBlock(cnt + (bit_per_block - 1))), length(cnt){};

    virtual ~BitSequence(){};

    virtual bool GetFirst() const override{return 0;}
    virtual bool GetLast() const override{return 0;}
    virtual bool Get(int index) const override{
        if (index < 0 || index >= length){
            throw std::out_of_range("IndexOutOfRange");
        }
        return (blocks[GetBlock(index)] & (1<<GetBitBlock(index))) != 0;
    } 
    virtual BitSequence* GetSubsequence(int startIndex, int endIndex) const override{
        return nullptr;
    }

    virtual int GetLength() const override{
        return length;
    }

    virtual BitSequence* Append(const bool& item) override{
        if (!GetBitBlock(length+1)){
            blocks.Resize(blocks.GetSize()+1);
        }
        blocks[GetBlock(length)] |= (item<<GetBitBlock(length));
        length++; 
    }
    
    virtual BitSequence* Prepend(const bool& item) override{return nullptr;}
    virtual BitSequence* InsertAt(const bool& item, int index) override{return nullptr;}

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