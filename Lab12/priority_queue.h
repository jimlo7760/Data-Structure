#ifndef priority_queue_h_
#define priority_queue_h_

#include <iostream>
#include <vector>
#include <cassert>


template <class T>
class priority_queue {
private:
  std::vector<T> m_heap;

public:
  priority_queue() {}

  priority_queue( std::vector<T> const& values )
  {
      for (unsigned int i = 0; i < values.size(); i++){
          this ->push(values[i]);
      }
  }

  const T& top() const 
  {
    assert( !m_heap.empty() );
    return m_heap[0]; 
  }

  void push( const T& entry )
  {
      (this -> m_heap).push_back(entry);
      int curPos = (this -> m_heap).size() - 1;
      while (!(this -> check_heap())){
          // swap the last node with its parent
          int parentPos = (curPos - 1) / 2;
          T temp = (this -> m_heap)[parentPos];
          (this -> m_heap)[parentPos] = (this -> m_heap)[curPos];
          (this -> m_heap)[curPos] = temp;
          curPos = parentPos;
      }
  }

  void pop() 
  {
    assert( !m_heap.empty() );
      (this -> m_heap)[0] = (this -> m_heap).back();
      (this -> m_heap).pop_back();
      int curPos = 0;
      while (!(this -> check_heap())){
          int leftChildPos = 2 * curPos + 1;
          int rightChildPos = 2 * curPos + 2;
          T leftChildVal = (this -> m_heap)[leftChildPos];
          T rightChildVal = (this -> m_heap)[rightChildPos];
          T temp = (this -> m_heap)[curPos];
          if (leftChildVal < rightChildVal){
              (this -> m_heap)[curPos] = (this -> m_heap)[leftChildPos];
              (this -> m_heap)[leftChildPos] = temp;
              curPos = leftChildPos;
          }else{
              (this -> m_heap)[curPos] = (this -> m_heap)[rightChildPos];
              (this -> m_heap)[rightChildPos] = temp;
              curPos = rightChildPos;
          }
      }
  }

  int size() { return m_heap.size(); }
  bool empty() { return m_heap.empty(); }


  //  The following three functions are used for debugging.

  //  Check to see that internally the heap property is realized.
  bool check_heap( )
  {
    return this->check_heap( this->m_heap );
  }

  //  Check an external vector to see that the heap property is realized.
  bool check_heap( const std::vector<T>& heap )
  {
      for (unsigned int i = 1; i < heap.size(); i++){
          // get the parent
          T parentVal = heap[(i-1)/2];
          T curVal = heap[i];
          if (parentVal > curVal){
              return false;
          }
      }
      return true;
  }

  //  A utility to print the contents of the heap.  Use it for debugging.
  void print_heap( std::ostream & ostr )
  {
    for ( unsigned int i=0; i<m_heap.size(); ++i )
      ostr << i << ": " << m_heap[i] << std::endl;
  }
  
};


template <class T>
void heap_sort( std::vector<T> & v )
{
    if (v.size() == 0){
        return;
    }
    for (int i = 1; i < v.size(); i++){
        int curPos = i;
        while (curPos >= 0){
            int parentPos = (curPos - 1) / 2;
            if (v[parentPos] > v[curPos]){
                T temp = v[parentPos];
                v[parentPos] = v[curPos];
                v[curPos] = temp;
                curPos = parentPos;
            }else{
                break;
            }
        }
    }

    for (int i = v.size() - 1; i > 0; i--){
        T temp = v[0];
        v[0] = v[i];
        v[i] = temp;
        int curPos = 0;
        int maxPos = i - 1;
        while (curPos < maxPos){
            int leftPos = 2 * curPos + 1;
            int rightPos = 2 * curPos + 2;
            if (leftPos > maxPos){
                break;
            }
            T minChild;
            if (rightPos <= maxPos){
                minChild = std::min(v[leftPos], v[rightPos]);
            }else{
                minChild = v[leftPos];
            }
            if (v[curPos] > minChild){
                if (minChild == v[leftPos]){
                    T temp1 = v[curPos];
                    v[curPos] = v[leftPos];
                    v[leftPos] = temp1;
                    curPos = leftPos;
                }else{
                    T temp2 = v[curPos];
                    v[curPos] = v[rightPos];
                    v[rightPos] = temp2;
                    curPos = rightPos;
                }
            }else{
                break;
            }
        }
    }

    std::sort(v.begin(), v.end());
}

#endif
