#include <stdexcept>

template <class T> class DynamicArray{
    private:
        T* data;
        int size; 

    public:
        DynamicArray(T* items, int count){
            if (count < 0){
                throw std::out_of_range("NegativeCount");
            }
            data =  new T [count];
            size = count;
            for (int i=0; i<size; i++){
                data[i] = items[i];
            }
        }

        DynamicArray(int size){
            if (size < 0){
                throw std::out_of_range("NegativeSize");
            }
            data = new T [size];
            this->size = size;
        }

        DynamicArray(const DynamicArray<T> & dynamicArray){
            data = new T [dynamicArray.size];
            size = dynamicArray.size;
            for (int i=0; i<size; i++){
                data[i] = dynamicArray.data[i];
            }    
        }

        ~DynamicArray(){
            delete [] data;
        }

        T Get(int index) const{
            if (index < 0 || index >= size){
                throw std::out_of_range("IndexOutOfRange");
            }
            return data[index];
        }

        T& operator[](int index){
            if (index<0 || index >= size){
                throw std::out_of_range("IndexOutOfRange");
            }
            return data[index];
        }

        const T& operator[](int index) const{
            if (index<0 || index >= size){
                throw std::out_of_range("IndexOutOfRange");
            }
            return data[index];
        }

        int GetSize() const{
            return size;
        }

        void Set(int index, T value){
            if (index < 0 || index >= size){
                throw std::out_of_range("IndexOutOfRange");
            }
            data[index] = value;
        }

        void Resize(int newSize){
            if (newSize > size){
                T* result = new T [newSize];
                for (int i=0; i<size; i++){
                    result[i] = data[i];
                }
                delete [] data;
                size = newSize;
                data = result;

            }
            else{
                size = newSize;
            }
        }

};