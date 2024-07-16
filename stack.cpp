#include<initializer_list>   // for std::initilizer_list
#include<iostream>    // for std::cout, std::endl;
template<typename T>  
class stack{             // making a template class 
    private:
    
      size_t sze;  // the size of the stack 
      T*data;    // a pointer that will contain all the elements of the stack

    public:
    
      stack(): sze(0), data(nullptr){} // default constructor
      
      stack(const std::initializer_list<T>&arr){        // a constructor with an initilizer_list to add elements to the stack
          sze = 0;
          data = new T[arr.size()];
          if(data == nullptr) throw std::bad_alloc();    // throwing an error message if the allocation failed
          for(auto&i:arr)
            data[sze++] = i;
      }
      void pop(){    // removing the top element of the stack
          if(sze >=1)    // making sure that the stack is not empty
            data = (T*)realloc(data,--sze * sizeof(T));  // resizing the stack
          else 
            throw std::out_of_range("Out of range!\n");  // throwing an exception in case of trying to pop an empty stack 
      }
      
      const size_t size() const{return sze;}  // returning the size of the stack
      
      const T top() const{
          if (!data or sze<1)  // making sure that the pointer is not corrupted or the stack is empty
            throw std::out_of_range(" Out of range!\n");  // throwing an exception whenever something wrong with
          return data[sze-1];
      }
      
      const bool empty() const{   // to know whether the stack is empty or not
          return (sze == 0);
      }
      
      void push(const T&x){   // pushing a new element to the top of the stack
          if(data == nullptr){
              sze = 0;
              data = new T[++sze];
              if(data == nullptr) throw std::bad_alloc();
              data[0] = x;
          }else{
          data = (T*)realloc(data,++sze * sizeof(T));  // resizing the stack to make sure there is a capacity to the new element
          data[sze-1] = x;
          } 
      }
      stack(const stack&other){  // a copy constructor that performs deep copy
          if(this != &other){
          this->sze = other.sze;
          this->data = new T[sze];
          if(this->data == nullptr) throw std::bad_alloc();
          for(int i = 0; i < sze; i++)
            this->data[i] = other.data[i];
          }
      }
      stack&operator = (const stack&other){  // copy assignment.
        if(this != &other){
          this->sze = other.sze;
          this->data = new T[sze];
          if(this->data == nullptr) throw std::bad_alloc();
          for(int i = 0; i < sze; i++)
            this->data[i] = other.data[i];
          }
        return *this;
    }
        
      stack(stack&&other) noexcept{  // move constructor
          if(this != &other){
          this->sze = other.sze; 
          this->data = new T[sze];
          if(this->data == nullptr) throw std::bad_alloc();
          for(int i = 0; i <sze; i++){
              this->data[i] = other.data[i];
          }
          delete [] other.data;
          other.sze = 0;
          other.data = nullptr;
          }
      }
      stack&operator =(stack && other) noexcept{   // move assignment
          if(this != &other){
          this->sze = other.sze; 
          this->data = new T[sze];
          if(this->data == nullptr) throw std::bad_alloc();
          for(int i = 0; i <sze; i++){
              this->data[i] = other.data[i];
          }
          delete [] other.data;
          other.sze = 0;
          other.data = nullptr;
          }
          return *this;    
      }
      ~stack(){   // a destructor that makes sure to free all the reserved dynamic memory to avoid any memory leaks
          delete [] data;
          data = nullptr;
          sze = 0;
      }
};
int main(){
    stack<int>s1 = {1,5,7,6,3,5,4};    // pushing elements to the stack using the initializer list
    s1.push(15);  // pushing an element using the member function 'push'
    while(!s1.empty()){
        std::cout<<s1.top()<<'\t';  // printing the top element in the stack.
        s1.pop();   // getting rid of the top element.
    }
    std::cout<<std::endl;
    
    std::cout<<"The size of the stack is: "<<s1.size()<<std::endl;
    return EXIT_SUCCESS;
}
