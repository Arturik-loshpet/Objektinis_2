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
            if(capacity == 0) capacity = 1;
            else capacity = capacity * 2;
            T * newData = new T[capacity];
            for(size_t i=0; i<size; i++){
                newData[i] = data[i];
            }
            delete[] data;
            data = newData;
        }
    public:

        using value_type = T;

        /*
        ---------------------------------------------------
        Konstruktoriai
        */
        MyVector(): //vektoriaus konstruktorius
        size(0),
        capacity(1),
        data(new T[capacity]){}

        MyVector(const MyVector& other): //copy konstruktorius
            size(other.size),
            capacity(other.capacity),
            data(new T[other.capacity]){
                for(size_t i =0; i< size; i++){
                    data[i] = other.data[i];
                }
            }

        MyVector(MyVector&& other): // move konstruktorius
            size(other.size),
            capacity(other.capacity),
            data(other.data)
            {
                other.size = 0;
                other.capacity = 0;
                other.data = nullptr;
            }

        /*
        ---------------------------------------------------
        Operatoriai
        */

        T & operator[](size_t index){ //grazina vektoriaus reiksme duotam indexe
            return data[index];
        }

        MyVector& operator=(const MyVector& other){ // lygu operatorius :(
            if(this != &other){
                delete[] data;
                size = other.size;
                capacity = other.capacity;
                data = new T[other.capacity];{
                    for(size_t i =0; i< size; i++){
                        data[i] = other.data[i];
                    }
                }
            }
            return *this;
        }

        MyVector& operator=(MyVector&& other) { //move assignment operatorius
            if (this != &other) {
                delete[] data;

                size = other.size;
                capacity = other.capacity;
                data = other.data;

                other.size = 0;
                other.capacity = 0;
                other.data = nullptr;
            }

        return *this;
        }

        const T& operator[](size_t index) const{
            return data[index];
        }

        /*
        ---------------------------------------------------
        Funkcijos
        */

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

        bool empty() const{ //const versija sios funkcijos
            return size == 0;
        }

        size_t get_size(){ //grazina vektoriaus dydi
            return size;
        }

        size_t get_size() const{ //konstanta
            return size;
        }

        size_t get_capacity() const { //grazina vektoriaus capacity
            return capacity;
        }

        void clear(){ //isvalo vektoriu
            size = 0;
        }

        void shrink_to_fit(){ //sumazina vektoriaus capacity iki uzpildyto vektoriaus dydzio
            if(capacity > size){
                T* newData = new T[size];

                for(size_t i =0; i<size; i++){
                    newData[i] = data[i];
                }

                delete[] data;
                data = newData;
                capacity = size;
            }
        }

        T* begin() {
            return data;
        }

        T* end() {
            return data + size;
        }

        const T* begin() const {
            return data;
        }

        const T* end() const {
            return data + size;
        }

        T& back(){
            return data[size - 1];
        }

        const T& back() const{
            return data[size - 1];
        }

        T& front(){
            return data[0];
        }

        const T& front() const{
            return data[0];
        }

        void erase(T* first, T* last){
            T* newEnd = std::move(last, end(), first);
            size -= last - first;
            return first;
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

    MyVector<int> vec2;
    vec2 = vec;
    std::cout << vec2.end();
}   