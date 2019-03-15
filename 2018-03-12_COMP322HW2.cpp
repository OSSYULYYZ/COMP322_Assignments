#include <iostream>
#include <cstdlib>  
#include <time.h>
#include <limits>  

class Node
{
  public:
    int data;
    Node* next;
    Node* previous;
    Node()
    {
      this->data = 0;
      this->next = NULL;
      this->previous = NULL;
    };

    Node(int data, Node* next, Node* previous)
    {
      this->data = data;
      this->next = next;
      this->previous = previous;
    };

    ~Node(){}
};

class DLLStructure
{
  private:
    Node* first;
    Node* last;

  public:
    DLLStructure()
    {
      first = NULL;
      last = NULL;
    };

    DLLStructure(int array[], int size)
    {
      first = new Node(array[0], NULL, NULL);
      last = first; 
      for(int i = 1; i <size; i++)
      {
        last->next = new Node(array[i], NULL, last);
        last = last->next; 
      }
    };

    ~DLLStructure()
    {
      Node* current = first;
	    while(current != NULL)
      {
        first = first->next;
        delete current;
        current = first;
      }
    };

    void PrintDLL()
    {
      for(Node* current = first; current != NULL; current = current->next) std::cout << current->data << " "; 
      std::cout << "\n"; 
    };

    void InsertAfter(int valueToInsertAfter, int valueToBeInserted)
    {
      for(Node* current = first; current != NULL; current = current->next)
        if(current->data == valueToInsertAfter)
        {
          current->next = new Node(valueToBeInserted, current->next, current);
          break;
        }
    }

    // https://www.cs.cmu.edu/~adamchik/15-121/lectures/Linked%20Lists/linked%20lists.html
    void Delete(int value)
    {
      if(first == 0) return;
      if(first->data == value) first = first->next;
      else
      {
        Node* prev = NULL;
        Node* current = first;

        while(current != NULL && current->data != value)
        {
          prev = current;
          current = current->next;
        }

        if(current == NULL) return; 

        prev->next = current->next;
        
      }
    }

    bool IsEmpty()
    {
      if(first == NULL) return true;
      return false;
    }

    int GetHead()
    {
      if(!first) return std::numeric_limits<int>::min();
      return first->data;
    }

    int GetTail()
    {
      if(!last) return std::numeric_limits<int>::min();
      return last->data;
    }

    // Best Implementation: Have an iterator that eeps track of the size. Everytime a new element is added,
    // increment by one.
    int GetSize()
    {
      int count = 0;
      for(Node* current = first; current != NULL; current = current->next) count++;
      return count;
    }

    // Best Implementation: Sort the LL and get the last value.
    // One can sort it at the very beginning and keep it sorted.
    // GetMaxSorted() ~ O(1)
    int GetMax()
    {
      if(this->IsEmpty()) std::cout << "EMPTY"; 
      int max = std::numeric_limits<int>::min();
      for(Node* current = first; current != NULL; current = current->next)
        if(current->data > max) max = current->data;
      return max;
    }

    // Best Implementation: Sort the LL and get the last value.
    // One can sort it at the very beginning and keep it sorted.
    // GetMinSorted() ~ O(1)
    int GetMin()
    {
      if(this->IsEmpty()) std::cout << "EMPTY"; 
      int min = std::numeric_limits<int>::max();
      for(Node* current = first; current != NULL; current = current->next)
        if(current->data < min) min = current->data;
      return min;
    }

    void InsertBefore(int valueToInsertBefore, int valueToBeInserted)
    {
      Node* realFirst = first;
      for(Node* current = first; current != NULL; current = current->next)
        if(current->data == valueToInsertBefore)
        {
          first = current->previous;
          if(first == NULL)
          {
            first = new Node(valueToBeInserted, current, NULL); 
            return;
          }
        }
      InsertAfter(first->data, valueToBeInserted);
      first = realFirst;
    }

    void Sort()
    {
      int sort[1];
      sort[0] = this->GetMax();
      int prevMax = sort[0];

      this->Delete(prevMax);
      DLLStructure sorted(sort, 1);

      while(this->GetSize() != 0)
      {

        int max = this->GetMax();
        this->Delete(max);
        sorted.InsertBefore(prevMax, max);
        prevMax = max;
      }
      
      this->first = new Node(sorted.GetHead(), NULL, NULL);
      int min = sorted.GetHead();      
      sorted.Delete(min);
      Node* current = first;    
 
      while(sorted.GetSize() != 0)
      {
        min = sorted.GetHead();
        sorted.Delete(min);
        current->next = new Node(min, NULL, current);
        current = current->next;
      }
    }
};

int main()
{
  int array[7] = {11, 2, 2, 7, 22, 2, 4};
  DLLStructure dll(array, 7); 
  dll.PrintDLL(); // PascalCasing
  dll.InsertAfter(7, 13); // To insert 13 after the first occurence of 7
  dll.PrintDLL(); // PascalCasing
  dll.InsertBefore(2, 5);
  dll.PrintDLL(); 
  dll.Delete(2);
  dll.PrintDLL();
  dll.Delete(22);
  dll.PrintDLL();
  dll.Delete(30);
  dll.PrintDLL();
  dll.InsertBefore(11, 8);
  dll.PrintDLL();
  DLLStructure e;
  std::cout << "e.IsEmpty(): " << e.IsEmpty() << "\n"; 
  std::cout << "e.GetSize(): " << e.GetSize() << "\n"; 
  std::cout << "e.GetMax(): " << e.GetMax() << "\n"; 
  std::cout << "e.GetMin(): " << e.GetMin() << "\n"; 
  std::cout << "dll.IsEmpty(): " << dll.IsEmpty() << "\n"; 
  std::cout << "dll.GetSize(): " << dll.GetSize() << "\n"; 
  std::cout << "dll.GetMax(): " << dll.GetMax() << "\n"; 
  std::cout << "dll.GetMin(): " << dll.GetMin() << "\n"; 
  dll.Sort();
  dll.PrintDLL();
  return 0;
}
// No. The default copy constructor copies the references, not the values. If you change one, it will change the other.
// For a copy constructor: look at the Sort Function. I had to 'copy' all the values from sorted into this.
