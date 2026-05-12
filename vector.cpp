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
#include <stdexcept>



template <typename T>
class MyVector{
    private:
        size_t size_;
        size_t capacity_;
        T* data;
        void resize(){ //padidina capacity_ vektoriui
            if(capacity_ == 0) capacity_ = 1;
            else capacity_ = capacity_ * 2;
            T * newData = new T[capacity_];
            for(size_t i=0; i<size_; i++){
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
        size_(0),
        capacity_(1),
        data(new T[capacity_]){}

        MyVector(const MyVector& other): //copy konstruktorius
            size_(other.size_),
            capacity_(other.capacity_),
            data(new T[other.capacity_]){
                for(size_t i =0; i< size_; i++){
                    data[i] = other.data[i];
                }
            }

        MyVector(MyVector&& other): // move konstruktorius
            size_(other.size_),
            capacity_(other.capacity_),
            data(other.data)
            {
                other.size_ = 0;
                other.capacity_ = 0;
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
                size_ = other.size_;
                capacity_ = other.capacity_;
                data = new T[other.capacity_];{
                    for(size_t i =0; i< size_; i++){
                        data[i] = other.data[i];
                    }
                }
            }
            return *this;
        }

        MyVector& operator=(MyVector&& other) { //move assignment operatorius
            if (this != &other) {
                delete[] data;

                size_ = other.size_;
                capacity_ = other.capacity_;
                data = other.data;

                other.size_ = 0;
                other.capacity_ = 0;
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

        void push_back(const T& val){ //Iraso nauja kintamaji i vektorio funkcija
            if (size_ == capacity_) resize();
            data[size_] = val;
            size_++;
        }

        void pop_back(){ //istrina nari vektoriaus gale
            if(size_ > 0) size_--;
        }

        bool empty(){ //patikrina ar vektorius tuscias
            return size_ == 0;
        }

        bool empty() const{ //const versija sios funkcijos
            return size_ == 0;
        }

        size_t size(){ //grazina vektoriaus dydi
            return size_;
        }

        size_t size() const{ //konstanta
            return size_;
        }

        size_t capacity() const { //grazina vektoriaus capacity_
            return capacity_;
        }
         size_t capacity() const{
            return capacity_;
         }

        void clear(){ //isvalo vektoriu
            size_ = 0;
        }

        void shrink_to_fit(){ //sumazina vektoriaus capacity_ iki uzpildyto vektoriaus dydzio
            if(capacity_ > size_){
                T* newData = new T[size_];

                for(size_t i =0; i<size_; i++){
                    newData[i] = data[i];
                }

                delete[] data;
                data = newData;
                capacity_ = size_;
            }
        }

        T* begin() {
            return data;
        }

        T* end() {
            return data + size_;
        }

        const T* begin() const {
            return data;
        }

        const T* end() const {
            return data + size_;
        }

        T& back(){
            return data[size_ - 1];
        }

        const T& back() const{
            return data[size_ - 1];
        }

        T& front(){
            return data[0];
        }

        const T& front() const{
            return data[0];
        }

        T* erase(T* first, T* last){
            std::move(last, end(), first);
            size_ -= last - first;
            return first;
        }

        T* erase(T* pos) {
            return erase(pos, pos + 1);
        }

        T& at(size_t index){ //patikrina vektoriaus ribas
            if(size_ <= index){
                throw std::out_of_range("MyVector index out of range");
            }
            return data[index];
        }

        const T& at(size_t index) const {
            if (index >= size_) {
                throw std::out_of_range("MyVector index out of range");
            }

            return data[index];
        }

        

        ~MyVector(){ //destruktorius
            delete[] data;
            size_ = 0;
            capacity_ = 0;
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