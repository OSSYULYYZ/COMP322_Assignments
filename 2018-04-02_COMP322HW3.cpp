/* Q1
   http://en.cppreference.com/w/cpp/memory
   "Smart pointers enable automatic, exception-safe, object lifetime management."
   unique_ptr has specific ownership. 
   shared_ptr has shared ownership.
   weak_ptr points to an object managed by std::shared_ptr 
   auto_ptr has strict object ownership semantics 
   owner_less provides mixed-type owner-based ordering different pointers
   enable_shared_from_this grants objects to create a shared_ptr referring to itself 
   bad_weak_ptr throws exception when accessing a weak_ptr which refers to already destroyed object 
   default_delete is a destructor or deleter for unique_ptr 
*/  
#include <iostream>
#include <cstdlib> 

template <typename T> class SmartPointer
{
  private:
    T *data;
  public:
    SmartPointer() {  this->data = new T(0.0);  }
    SmartPointer(T data) {  setValue(data);  }
    void setValue(T data)
    {
      try
      {
        if(data < 0) throw std::numeric_limits<int>::min();
        this->data = new T(data);
      }
      // http://en.cppreference.com/w/cpp/memory/new/bad_alloc
      catch(const std::bad_alloc& e) {  std::cout << e.what() << '\n';  }
      catch(int e) {  std::cerr << "NegativeNumberError" << e << "\n";  }
    }
    T getValue() {  return *data;  }
    friend SmartPointer operator+(SmartPointer<T> &a, SmartPointer<T> &b)
    {  return SmartPointer<T>(*a.data + *b.data);  }
    friend SmartPointer operator-(SmartPointer<T> &a, SmartPointer<T> &b)
    {  return SmartPointer<T>(*a.data - *b.data);  }
    friend SmartPointer operator*(SmartPointer<T> &a, SmartPointer<T> &b)
    {  return SmartPointer<T>(*a.data * *b.data);  }
    ~SmartPointer()
    {
      delete data;
    };
};

template <typename T> class SmartArray
{
  private:
    T *data;
    int size;
  public:
    SmartArray()
    {
      this->number = new T[1]();
      this->size = 1;
    }
    SmartArray(T datum[], int size)
    {
      this->size = size;
      this->data = new T[size];
      for(int i = 0; i < size; i++) *(data + i) = datum[i];
    }
    ~SmartArray() {  delete[] this->data;  }
    T getValue(int i)
    {
      T value = *(data + i);
      return value;
    }
    void setValue(T data, int i)
    {
      if(i > size)
      {
        std::cout << "CHECK INDEX. OUT OF BOUNDS\n";
        return;
      } 
      *(this->data + i) = data;
    }
};

int main()
{
  std::cout << "Q2\nSmartPointer<int> sPointer1;\n"; 
  std::cout << "sPointer1.setValue(133);\n";
  SmartPointer<int> sPointer1;
  sPointer1.setValue(133);
  std::cout << "sPointer1.getValue() = " << sPointer1.getValue() <<"\n";    
  std::cout << "Q3\nsPointer1.setValue(-5)\n";
  sPointer1.setValue(-5);
  std::cout << "Q4\nSmartPointer<float> sPointer2;\n"; 
  std::cout << "sPointer2.setValue(13.31);\n";
  SmartPointer<float> sPointer2;
  sPointer2.setValue(13.31);
  std::cout << "Q5\nSmartPointer<int> sPointer322(322);\n"; 
  std::cout << "SmartPointer<int> sPointer133(133);\n";
  std::cout << "SmartPointer<int> sum = sPointer322 + sPointer133;\n";  
  SmartPointer<int> sPointer322(322); 
  SmartPointer<int> sPointer133(133);
  SmartPointer<int> sum = sPointer322 + sPointer133;
  std::cout << "sum.getValue() = " << sum.getValue() <<"\n";
  std::cout << "Q6\nint foo[] = { 16, 2, 77, 40, 12071 };\nSmartArray<int> d(foo, 5);\n";
  int foo[] = { 16, 2, 77, 40, 12071 };
  SmartArray<int> d(foo, 5);
  std::cout << "d.getValue(2) = " << d.getValue(2) <<"\n";
  return 0;
}