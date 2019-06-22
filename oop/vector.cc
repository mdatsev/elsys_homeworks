#include <cstdlib>
#include <iostream>

using namespace std;

class Vector
{
    int capacity_;
    int size_;
    int *data_;

  public:
    class iterator
    {
        friend class Vector;
        int *elem_;
        iterator(int &elem)
            : elem_(&elem)
        {
        }

      public:
        iterator operator++()
        {
            elem_++;
        }
        iterator operator++(int)
        {
            elem_++;
        }
        bool operator==(const iterator &other) const
        {
            return elem_ == other.elem_;
        }
        bool operator!=(const iterator &other) const
        {
            return !operator==(other);
        }
        int &operator*()
        {
            return *elem_;
        }
    };
    iterator begin()
    {
        return iterator(front());
    }
    iterator end()
    {
        return iterator(data_[size_]);
    }
    static const int default_size = 2;
    Vector(int capacity = default_size)
        : capacity_(capacity),
          size_(0),
          data_((int *)malloc(capacity_ * sizeof(int)))
    {
    }

    Vector(const Vector &other)
        : capacity_(other.capacity_),
          size_(other.size_),
          data_((int *)malloc(capacity_ * sizeof(int)))
    {
        for (int i = 0; i < capacity_; i++)
            data_[i] = other.data_[i];
    }

    Vector &operator=(const Vector &other)
    {
        capacity_ = other.capacity_;
        size_ = other.size_;
        data_ = (int *)malloc(capacity_ * sizeof(int));
        for (int i = 0; i < capacity_; i++)
            data_[i] = other.data_[i];
    }

    ~Vector()
    {
        free(data_);
    }

    int size() const
    {
        return size_;
    }

    bool empty() const
    {
        return size_ == 0;
    }
    int &operator[](int n)
    {
        if (n >= size_ || n < 0)
            throw "Index out of range";
        return data_[n];
    }
    const int &operator[](int n) const
    {
        if (n >= size_ || n < 0)
            throw "Index out of range";
        return data_[n];
    }
    void clear()
    {
        size_ = 0;
    }
    int capacity() const
    {
        return capacity_;
    }
    int &front()
    {
        if (empty())
            throw "Front of empty vector";
        return data_[0];
    }
    const int &front() const
    {
        if (empty())
            throw "Front of empty vector";
        return data_[0];
    }
    void push_back(const int &value)
    {
        if (size_ == capacity_)
        {
            capacity_ *= 2;
            data_ = (int *)realloc(data_, capacity_ * sizeof(int));
        }
        data_[size_++] = value;
    }
    void pop_back()
    {
        if (empty())
            throw "Pop back of empty vector";
        size_--;
    }
};

int main()
{
    Vector myIntVector;

    // Add some elements to myIntVector
    myIntVector.push_back(1);
    myIntVector.push_back(4);
    myIntVector.push_back(8);

    for (Vector::iterator it = myIntVector.begin();
         it != myIntVector.end();
         it++)
    {
        cout << *it << " ";
        //Should output 1 4 8
    }
}