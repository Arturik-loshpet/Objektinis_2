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
        T* data_;
        void grow(){ //padidina capacity_ vektoriui
            if(capacity_ == 0) capacity_ = 1;
            else capacity_ = capacity_ * 2;
            T * newData = new T[capacity_];
            for(size_t i=0; i<size_; i++){
                newData[i] = data_[i];
            }
            delete[] data_;
            data_ = newData;
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
        data_(new T[capacity_]){}

        MyVector(const MyVector& other): //copy konstruktorius
            size_(other.size_),
            capacity_(other.capacity_),
            data_(new T[other.capacity_]){
                for(size_t i =0; i< size_; i++){
                    data_[i] = other.data_[i];
                }
            }

        MyVector(MyVector&& other): // move konstruktorius
            size_(other.size_),
            capacity_(other.capacity_),
            data_(other.data_)
            {
                other.size_ = 0;
                other.capacity_ = 0;
                other.data_ = nullptr;
            }

        /*
        ---------------------------------------------------
        Operatoriai
        */

        T & operator[](size_t index){ //grazina vektoriaus reiksme duotam indexe
            return data_[index];
        }

        MyVector& operator=(const MyVector& other){ // lygu operatorius :(
            if(this != &other){
                delete[] data_;
                size_ = other.size_;
                capacity_ = other.capacity_;
                data_ = new T[other.capacity_];{
                    for(size_t i =0; i< size_; i++){
                        data_[i] = other.data_[i];
                    }
                }
            }
            return *this;
        }

        MyVector& operator=(MyVector&& other) { //move assignment operatorius
            if (this != &other) {
                delete[] data_;

                size_ = other.size_;
                capacity_ = other.capacity_;
                data_ = other.data_;

                other.size_ = 0;
                other.capacity_ = 0;
                other.data_ = nullptr;
            }

        return *this;
        }

        const T& operator[](size_t index) const{
            return data_[index];
        }

        /*
        ---------------------------------------------------
        Funkcijos
        */

        void push_back(const T& val){ //Iraso nauja kintamaji i vektorio funkcija
            if (size_ == capacity_) grow();
            data_[size_] = val;
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

        size_t capacity() { //grazina vektoriaus capacity_
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
                    newData[i] = data_[i];
                }

                delete[] data_;
                data_ = newData;
                capacity_ = size_;
            }
        }

        T* begin() {
            return data_;
        }

        T* end() {
            return data_ + size_;
        }

        const T* begin() const {
            return data_;
        }

        const T* end() const {
            return data_ + size_;
        }

        T& back(){
            return data_[size_ - 1];
        }

        const T& back() const{
            return data_[size_ - 1];
        }

        T& front(){
            return data_[0];
        }

        const T& front() const{
            return data_[0];
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
            return data_[index];
        }

        const T& at(size_t index) const {
            if (index >= size_) {
                throw std::out_of_range("MyVector index out of range");
            }

            return data_[index];
        }

        void reserve(size_t newCapacity){ //pakeisti vektoriaus capacity
            if(newCapacity <= capacity_){
                return;
            }

            T* newData = new T[newCapacity];
            for(size_t i=0; i<size_; i++){
                newData[i] = data_[i];
            }

            delete[] data_;
            data_ = newData;
            capacity_ = newCapacity;
        }

        void resize(size_t newSize){  //resizina vektoriu iki tam tikro dydzio
            if(newSize > capacity_) reserve(newSize);

            for(size_t i=size_; i<newSize; i++){
                data_[i] = T();
            }

            size_ = newSize;
        }

        void resize(size_t newSize, const T& value) { //resizina vektoriu iki naudotujui reikalingo dydzio ir tuscius laukus uzpildo duotom reiksmes
            if (newSize > capacity_) reserve(newSize);

            for (size_t i = size_; i < newSize; i++) {
                data_[i] = value;
            }

            size_ = newSize;
        }

        T* data(){ //vektoriaus pradzios adresas
            return data_;
        }
        T* cbegin() const{ //vektoriaus pradzios adreas
            return data_;
        }
        const T* cend() const { //bektoriaus pabaigos adresas
            return data_ + size_;
        }
        void swap(MyVector& other) { //apkeicia vektorius nariais, vietoj move ar copy
            std::swap(size_, other.size_);
            std::swap(capacity_, other.capacity_);
            std::swap(data_, other.data_);
        }
        void assign(size_t count, const T& value){ //priskiria vektoriui reiksme
            if(count > capacity_) reserve(count);
            for(size_t i = 0; i<count; i++){
                data_[i] = value;
            }
            size_ = count;
        }

        T* insert(T* pos, const T& value) { //ideda nauja reiksme i nauja indexa vektoriuje
            size_t index = pos - begin();

            if (size_ == capacity_) grow();

            for (size_t i = size_; i > index; i--) {
                data_[i] = data_[i - 1];
            }

            data_[index] = value;
            size_++;

            return data_ + index;
        }

        ~MyVector(){ //destruktorius
            delete[] data_;
            size_ = 0;
            capacity_ = 0;
        }
};

int main(){
    MyVector<int> vec;
    vec.assign(5, 2);
    for(int i=0; i<5; i++) std::cout << vec[i] << " ";
}   