//every reallocation of the array will double its size by 2.
//since the array should never be full, i dont think i have to count control the while(arr[index].isOccupied) loops

//Should maybe figure out better way to value initialise array in clear() method without using new operator
//with the current implement, any Key used must overload operator!=
//operator[] method has no error checking to check if key is actually in the hashmap

template <typename Key, typename Value>
class Hashmap{
    typedef struct {
        Key key;
        Value value;
        bool isOccupied;
    } KeyValuePair;

public:
    Hashmap<Key, Value>();
    ~Hashmap<Key, Value>();

    void insert(Key key, Value value);
    bool erase(Key key);
    void clear();

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
void Hashmap<Key, Value>::insert(Key key, Value value){
    if(elementsStored + 1 > arrSize/sizeIncreaseFactor){
        reallocate_arr();
    }

    size_t index = hash_function(key);

    while(arr[index].isOccupied){
        index = (index + 1) % arrSize;
    }

    KeyValuePair temp = {key, value, true};
    arr[index] = temp;
    ++elementsStored;
}

template <typename Key, typename Value>
bool Hashmap<Key, Value>::erase(Key key){
    size_t index = hash_function(key);
    size_t i = 0;

    while(i < arrSize && arr[index].key != key){
        index = (index + 1) % arrSize;
    }

    if(i < arrSize){
        arr[index].isOccupied = false;
        return true;
    } else {
        return false;
    }
}

template <typename Key, typename Value>
void Hashmap<Key, Value>::clear(){
    delete[] arr;
    //Value initialise
    arr = new KeyValuePair[arrSize]();
}


template <typename Key, typename Value>
Value& Hashmap<Key, Value>::operator[](Key key){
    size_t index = hash_function(key);

    while(arr[index].key != key){
        index = (index + 1) % arrSize;
    }

    return arr[index].value;
}


template <typename Key, typename Value>
size_t Hashmap<Key, Value>::hash_function(Key key){
    size_t temp = reinterpret_cast<size_t&>(key);   //using a reference here works for some reason
    temp *= 3853; //random ass prime number
    temp %= arrSize;
    return temp;
}

template <typename Key, typename Value>
void Hashmap<Key, Value>::reallocate_arr(){
    //value initialise array 
    size_t newArrSize = arrSize * sizeIncreaseFactor;    
    KeyValuePair* newArr = new KeyValuePair[newArrSize]();
 
    for(size_t i = 0; i < arrSize; ++i){
        if(arr[i].isOccupied){
            size_t newIndex = hash_function(arr[i].key);

            while(newArr[newIndex].isOccupied){
                newIndex = (newIndex + 1) & newArrSize;
            }

            newArr[newIndex] = arr[i];
        }
    }

    delete[] arr;
    arrSize = newArrSize;
    arr = newArr;
}