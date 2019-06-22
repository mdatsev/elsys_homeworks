#include <iostream>
using namespace std;

class ListError
{
};

class List
{
    struct Node
    {
        int data_;
        Node *next_;
        Node *prev_;

        Node(int val)
            : data_(val),
              next_(0),
              prev_(0) {}
    };
    Node *head_;

  public:
    class iterator
    {
        friend class List;
        List *list_;
        Node *current_;
        iterator(List *list, Node *current)
            : list_(list),
              current_(current) {}

      public:
        bool operator==(const iterator &other) const
        {
            return list_ == other.list_ &&
                   current_ == other.current_;
        }
        bool operator!=(const iterator &other) const
        {
            return !operator==(other);
        }
        iterator &operator++()
        {
            current_ = current_->next_;
            return *this;
        }
        iterator operator++(int)
        {
            iterator previous(list_, current_);
            current_ = current_->next_;
            return previous;
        }
        int &operator*()
        {
            return current_->data_;
        }
    };
    class reverse_iterator
    {
        friend class List;
        List *list_;
        Node *current_;
        reverse_iterator(List *list, Node *current)
            : list_(list),
              current_(current) {}

      public:
        bool operator==(const reverse_iterator &other) const
        {
            return list_ == other.list_ &&
                   current_ == other.current_;
        }
        bool operator!=(const reverse_iterator &other) const
        {
            return !operator==(other);
        }
        reverse_iterator &operator++()
        {
            current_ = current_->prev_;
            return *this;
        }
        reverse_iterator operator++(int)
        {
            reverse_iterator previous(list_, current_);
            current_ = current_->prev_;
            return previous;
        }
        int &operator*()
        {
            return current_->data_;
        }
    };
    iterator begin()
    {
        return iterator(this, head_->next_);
    }
    iterator end()
    {
        return iterator(this, head_);
    }
    reverse_iterator rbegin()
    {
        return reverse_iterator(this, head_->prev_);
    }
    reverse_iterator rend()
    {
        return reverse_iterator(this, head_);
    }
    List()
        : head_(new Node(0))
    {
        head_->next_ = head_;
        head_->prev_ = head_;
    }
    ~List()
    {
        while (!empty())
        {
            pop_back();
        }
        delete head_;
    }
    bool empty() const
    {
        return head_->next_ == head_;
    }
    void push_back(int val)
    {
        Node *ptr = new Node(val);
        Node *back = head_->prev_;
        back->next_ = ptr;
        ptr->prev_ = back;
        head_->prev_ = ptr;
        ptr->next_ = head_;
    }
    void pop_back()
    {
        Node *ptr = head_->prev_;
        Node *back = ptr->prev_;
        back->next_ = head_;
        head_->prev_ = back;
        delete ptr;
    }
    void pop_front()
    {
        Node *ptr = head_->next_;
        Node *next = ptr->next_;
        next->prev_ = head_;
        head_->next_ = next;
        delete ptr;
    }
    int front() const
    {
        if (empty())
        {
            throw ListError();
        }
        return head_->next_->data_;
    }

    int back() const
    {
        if (empty())
        {
            throw ListError();
        }
        return head_->prev_->data_;
    }
    void insert(iterator position, int value)
    {
        Node *new_node = new Node(value);
        Node *next_node = position.current_;
        new_node->prev_ = next_node->prev_;
        next_node->prev_->next_ = new_node;
        next_node->prev_ = new_node;
        new_node->next_ = next_node;
    }
    void insert(iterator position, iterator b, iterator e)
    {
        for (List::iterator it1 = position, it2 = b; it2 != e; ++it2)
        {
            insert(it1, *it2);
        }
    }
};
int main()
{
    List l1;
    List l2;
    for (int i = 0; i < 10; i++)
    {
        l1.push_back(i * 10);
    }
    for (int i = 1; i < 6; i++)
    {
        l2.push_back(i);
    }
    List::iterator test = l1.begin();
    test++;
    test++;
    test++;
    l1.insert(test, l2.begin(), l2.end());
    for (List::reverse_iterator it = l1.rbegin(); it != l1.rend(); ++it)
    {
        cout << *it << endl;
    }
    return 0;
}
//homework: push_front; pop_front; copy constructor; operator=