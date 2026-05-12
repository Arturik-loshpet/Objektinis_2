#include <algorithm>
#include <chrono>
#include <cctype>
#include <cstddef>
#include <deque>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <limits>
#include <list>
#include <random>
#include <sstream>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>


template <typename T>
class MyVector{
    private:
        size_t size;
        size_t capacity;
        T* data;
        void resize(){ //padidina capacity vektoriui
            capacity = capacity * 2;
            T * newData = new T[capacity];
            for(size_t i=0; i<size; i++){
                newData[i] = data[i];
            }
            delete[] data;
            data = newData;
        }
    public:
        MyVector(): //vektoriaus konstruktorius
        size(0),
        capacity(1),
        data(new T[capacity]){}

        void push_back(T val){ //Iraso nauja kintamaji i vektorio funkcija
            if (size == capacity) resize();
            data[size] = val;
            size++;
        }

        void pop_back(){ //istrina nari vektoriaus gale
            if(size > 0) size--;
        }

        bool empty(){ //patikrina ar vektorius tuscias
            return size == 0;
        }

        size_t get_size(){ //grazina vektoriaus dydi
            return size;
        }

        void clear(){ //isvalo vektoriu
            size = 0;
            capacity = 0;
        }

        T & operator[](size_t index){ //grazina vektoriaus reiksme duotam indexe
            return data[index];
        }

        size_t begin(){ //grazina pirma vektoriaus reiksme
            return data[0];
        }

        size_t end(){ //grazina paskutinia reiksme
            return data[size - 1]; 
        }

        ~MyVector(){ //destruktorius
            delete[] data;
            size = 0;
            capacity = 0;
        }
};

int main(){
    MyVector<int> vec;
    for(int i=1; i<5; i++){
        vec.push_back(i);
    }
    std::cout << vec.end();
}