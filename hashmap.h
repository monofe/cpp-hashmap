#include <iostream>

//every reallocation of the array will double its size by 2.

template <typename Key, typename Value>
class Hashmap{
    typedef struct {
        Key key;
        Value value;
        bool isOccupied;
    } KeyValuePair;

public:
    void insert(Key key, Value value);
    Hashmap<Key, Value>();
    ~Hashmap<Key, Value>();
    Value& operator[](Key key);

private:
    KeyValuePair* arr;
    size_t elementsStored;
    size_t arrSize;

    const int initSize = 32;
    const int sizeIncreaseFactor = 2;

    size_t hash_function(Key key);
    void reallocate_arr();
};


template <typename Key, typename Value>
void Hashmap<Key, Value>::insert(Key key, Value value){
    if(elementsStored + 1 > arrSize/2){
        reallocate_arr();
    }

    size_t index = hash_function(key);

    //should work
    while(arr[index].isOccupied){
        index = hash_function(key);
    }

    KeyValuePair temp = {key, value, true};
    arr[index] = temp;
    ++elementsStored;
}

template <typename Key, typename Value>
size_t Hashmap<Key, Value>::hash_function(Key key){
    size_t temp = reinterpret_cast<size_t&>(key);   //using a reference here works for some reason
    temp *= 4218; //random ass number
    temp %= arrSize;
    return temp;
}

template <typename Key, typename Value>
void Hashmap<Key, Value>::reallocate_arr(){
    //value initialise array    
    KeyValuePair* newArr = new KeyValuePair[arrSize * sizeIncreaseFactor]();
 
    for(size_t i = 0; i < arrSize; ++i){
        if(arr[i].isOccupied){
            size_t newIndex = hash_function(arr[i].key);

            //should work
            while(newArr[newIndex].isOccupied){
                newIndex = hash_function(arr[i].key);
            }

            newArr[newIndex] = arr[i];
        }
    }

    delete[] arr;
    arrSize *= sizeIncreaseFactor;
    arr = newArr;
}


template <typename Key, typename Value>
Hashmap<Key, Value>::Hashmap(){
    //value initialise array
    arr = new KeyValuePair[initSize]();
    arrSize = initSize;
}

template <typename Key, typename Value>
Hashmap<Key, Value>::~Hashmap(){
    delete[] arr;
}

template <typename Key, typename Value>
Value& Hashmap<Key, Value>::operator[](Key key){
    size_t index = hash_function(key);

    //should work
    while(arr[index].key != key){
        index = hash_function(key);
    }

    return arr[index].value;
}