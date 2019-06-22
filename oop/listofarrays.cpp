#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

class ListOfArrays
{

    class ArrayNode
    {

      public:
        int *data_;
        int size_;
        ArrayNode *next_;
        ArrayNode *prev_;

        ArrayNode(int *data = 0, int size = 0)
            : data_(data), size_(size), next_(0), prev_(0) {}

        ~ArrayNode()
        {
            delete[] data_;
        }
        bool operator>(const ArrayNode &other) const
        {
            int smallerSize = size_ < other.size_ ? size_ : other.size_;
            for (int i = 0; i < smallerSize; i++)
            {
                if (data_[i] > other.data_[i])
                    return true;
                else if (data_[i] < other.data_[i])
                    return false;
            }
            return size_ > other.size_;
        }
        bool operator<(const ArrayNode &other) const
        {
            return other > *this;
        }
    };

    int size_;
    ArrayNode *head_;

  public:
    class Iterator
    {

        friend class ListOfArrays;

        ListOfArrays &list_;
        ArrayNode *current_;

      public:
        Iterator(ListOfArrays &list, ArrayNode *current)
            : list_(list), current_(current) {}

        bool operator==(const Iterator &other)
        {
            return current_->data_ == other.current_->data_;
        }

        bool operator!=(const Iterator &other)
        {
            return !operator==(other);
        }

        Iterator &operator++()
        {
            current_ = current_->next_;
            return *this;
        }

        Iterator operator++(int)
        {
            current_ = current_->next_;
            return Iterator(list_, current_->prev_);
        }

        int &operator[](const int &index)
        {
            return current_->data_[index];
        }

        int size()
        {
            return current_->size_;
        }

        void show()
        {
            for (int i = 0; i < current_->size_; i++)
            {
                cout << current_->data_[i];
                if (i < current_->size_ - 1)
                {
                    cout << " ";
                }
            }
        }

        double average()
        {
            return (double)sum() / current_->size_;
        }

        double median()
        {
            int *arr = ordered().current_->data_;
            int size = current_->size_;
            return size % 2
                       ? arr[size / 2]
                       : (double)(arr[size / 2] + arr[size / 2 - 1]) / 2;
        }

        int sum()
        {
            int sum = 0;
            for (int j = 0; j < current_->size_; j++)
            {
                sum += current_->data_[j];
            }
            return sum;
        }

        Iterator &ordered(bool ascending = true)
        {
            for (int i = 1; i < current_->size_; i++)
            {
                int cur = current_->data_[i];
                int j = i - 1;
                for (; j >= 0 &&
                       (ascending
                            ? current_->data_[j] > cur
                            : current_->data_[j] < cur);
                     j--)
                {
                    current_->data_[j + 1] = current_->data_[j];
                }
                current_->data_[j + 1] = cur;
            }
            return *this;
        }
    };

    ListOfArrays()
        : size_(0), head_(new ArrayNode(0, 0))
    {
        head_->next_ = head_;
        head_->prev_ = head_;
    }

    ~ListOfArrays()
    {
        remove_all();
        delete head_;
    }

    ListOfArrays(const ListOfArrays &other)
        : size_(0), head_(new ArrayNode(0, 0))
    {
        head_->next_ = head_;
        head_->prev_ = head_;
        const ArrayNode *cur = other.head_->next_;
        for (int i = 0; i < other.size_; i++)
        {
            push(cur->data_, 0, cur->size_);
            cur = cur->next_;
        }
    }

    ListOfArrays &operator=(const ListOfArrays &other)
    {
        remove_all();
        const ArrayNode *cur = other.head_->next_;
        for (int i = 0; i < other.size_; i++)
        {
            push(cur->data_, 0, cur->size_);
            cur = cur->next_;
        }
        return *this;
    }

    int size()
    {
        return size_;
    }

    void push(int array[], int position, int length)
    {
        int *data = new int[length];
        for (int i = 0; i < length; i++)
        {
            data[i] = array[position + i];
        }
        ArrayNode *new_node = new ArrayNode(data, length);
        ArrayNode *last = head_->prev_;
        last->next_ = new_node;
        head_->prev_ = new_node;
        new_node->next_ = head_;
        new_node->prev_ = last;
        size_++;
    }
    void averages(double averages[])
    {
        Iterator it = begin();
        for (int i = 0; i < size_; ++i, ++it)
        {
            averages[i] = it.average();
        }
    }

    void medians(double medians[])
    {
        Iterator it = begin();
        for (int i = 0; i < size_; i++, it++)
        {
            medians[i] = it.median();
        }
    }

    void sizes(int sizes[])
    {
        Iterator it = begin();
        for (int i = 0; i < size_; ++i, ++it)
        {
            sizes[i] = it.size();
        }
    }

    void sums(int sums[])
    {
        Iterator it = begin();
        for (int i = 0; i < size_; ++i, ++it)
        {
            sums[i] = it.sum();
        }
    }

    Iterator begin()
    {
        return Iterator(*this, head_->next_);
    }

    Iterator end()
    {
        return Iterator(*this, head_);
    }

    ListOfArrays &ordered(bool ascending = true)
    {
        for (Iterator i = begin(); i != end(); ++i)
        {
            i.ordered(ascending);
        }
        ListOfArrays sorted;
        ArrayNode max = ArrayNode();
        int total_size = size_;
        for (int i = 0; i < total_size; i++)
        {
            ArrayNode *max_ptr = &max;
            for (Iterator j = begin(); j != end(); ++j)
            {
                if (*j.current_ > *max_ptr)
                {
                    max_ptr = j.current_;
                }
            }
            if (ascending)
                sorted.push_front(max_ptr->data_, 0, max_ptr->size_);
            else
                sorted.push(max_ptr->data_, 0, max_ptr->size_);
            remove(max_ptr);
        }
        operator=(sorted);
        return *this;
    }

    ListOfArrays &operator*=(const int &coef)
    {
        Iterator it = begin();
        for (int i = 0; i < size_; i++, it++)
        {
            for (int j = 0; j < it.size(); j++)
            {
                it[j] *= coef;
            }
        }
        return *this;
    }

    ListOfArrays &operator+=(const int &value)
    {
        Iterator it = begin();
        for (int i = 0; i < size_; i++, ++it)
        {
            for (int j = 0; j < it.size(); j++)
            {
                it[j] += value;
            }
        }
        return *this;
    }

    void show()
    {
        for (ListOfArrays::Iterator i = begin();;)
        {
            i.show();
            if (++i == end())
                break;
            cout << "; ";
        }
    }

  private:
    void pop()
    {
        remove(head_->prev_);
    }
    void remove(ArrayNode *node)
    {
        ArrayNode *next = node->next_;
        ArrayNode *prev = node->prev_;
        prev->next_ = next;
        next->prev_ = prev;
        delete node;
        size_--;
    }
    void remove_all()
    {
        ArrayNode *cur = head_->next_;
        for (; size_ != 0; size_--)
        {
            cur = cur->next_;
            delete cur->prev_;
        }
        head_->next_ = head_;
        head_->prev_ = head_;
    }
    void push_front(int array[], int position, int length)
    {
        int *data = new int[length];
        for (int i = 0; i < length; i++)
        {
            data[i] = array[position + i];
        }
        ArrayNode *new_node = new ArrayNode(data, length);
        ArrayNode *first = head_->next_;
        first->prev_ = new_node;
        head_->next_ = new_node;
        new_node->prev_ = head_;
        new_node->next_ = first;
        size_++;
    }
};

void parseListOfArrays(ListOfArrays &li, const string &str)
{
    vector<vector<int>> arrays;
    istringstream arrays_stream(str);
    string array_string;
    for (int i = 0; getline(arrays_stream, array_string, ';'); i++)
    {

        arrays.push_back(vector<int>());
        istringstream numbers_stream(array_string);
        string number_string;
        while (getline(numbers_stream, number_string, ' '))
        {
            if (!number_string.empty())
            {
                arrays[i].push_back(atoi(number_string.c_str()));
            }
        }
    }
    for (unsigned int i = 0; i < arrays.size(); i++)
    {
        li.push(arrays[i].data(), 0, arrays[i].size());
    }
}

class Command
{
  public:
    string type;
    int param;
    bool isOutput()
    {
        return type == "sizes" || type == "averages" || type == "medians" || type == "sums" ||
               type == "at" || type == "average" || type == "median" || type == "sum" ||
               type == "size" || type == "show";
    }
    bool printsDoubles()
    {
        return type == "averages" || type == "medians";
    }
    bool printsInts()
    {
        return type == "sums" || type == "sizes";
    }
    bool operator==(const char *string)
    {
        return type == string;
    }
};

void ParseCommandSequence(vector<Command> &commands, const string &str)
{
    istringstream commands_stream(str);
    string command_string;
    for (int i = 0; getline(commands_stream, command_string, '.'); i++)
    {
        struct Command command;
        stringstream(command_string) >> command_string;
        size_t delimiter_pos = command_string.find(":");
        command.type = command_string.substr(0, delimiter_pos);
        command.param = atoi(command_string.substr(delimiter_pos + 1).c_str());
        if (!command.type.empty())
            commands.push_back(command);
    }
}

int main()
{
    ListOfArrays original;
    bool first_line = true;
    while (1)
    {
        string line;
        cout << "> ";
        if (!getline(cin, line))
            break;
        if (first_line)
        {
            parseListOfArrays(original, line);
            first_line = false;
            continue;
        }
        ListOfArrays result = original;
        vector<Command> commands;
        int pos;
        while ((pos = line.find("true")) != (int)string::npos) //replaces all "true" with "1"
        {
            line.replace(pos, 4, "1");
        }
        ParseCommandSequence(commands, line);
        ListOfArrays::Iterator iter = result.begin();
        bool list_mode = true;
        for (unsigned int i = 0; i < commands.size(); i++)
        {
            Command cmd = commands[i];
            int param = commands[i].param;
            if (i == 0 && cmd == "begin")
            {
                list_mode = false;
                continue;
            }
            if (cmd == "quit")
            {
                return 0;
            }
            if (list_mode)
            { //list mode
                if (cmd == "show")
                    result.show();
                else if (cmd == "ordered")
                    result.ordered(param);
                else if (cmd == "mul")
                    result *= param;
                else if (cmd == "add")
                    result += param;
                else if (cmd == "size")
                    cout << result.size();
                else if (cmd.printsDoubles())
                {
                    double results[result.size()];
                    if (cmd == "averages")
                        result.averages(results);
                    else
                        result.medians(results);
                    for (int i = 0; i < result.size(); cout << results[i++] << " ")
                        ;
                }
                else if (cmd.printsInts())
                {
                    int results[result.size()];
                    if (cmd == "sizes")
                        result.sizes(results);
                    else
                        result.sums(results);
                    for (int i = 0; i < result.size(); cout << results[i++] << " ")
                        ;
                }
                else
                {
                    cout << "ERROR: Unknown operation" << endl;
                    break;
                }
            }
            else
            { //iterator mode
                if (cmd == "next")
                {
                    if (++iter == result.end())
                    {
                        cout << "ERROR: End of iteration" << endl;
                        break;
                    }
                }
                else if (cmd == "show")
                {
                    iter.show();
                }
                else if (cmd == "size")
                    cout << iter.size();
                else if (cmd == "average")
                    cout << iter.average();
                else if (cmd == "median")
                    cout << iter.median();
                else if (cmd == "sum")
                    cout << iter.sum();
                else if (cmd == "ordered")
                    iter.ordered(param);
                else if (cmd == "at")
                {
                    if (param >= iter.size() || param < 0)
                        cout << "ERROR: Index out of bounds";
                    else
                        cout << iter[param];
                }
                else
                {
                    cout << "ERROR: Unknown operation" << endl;
                    break;
                }
            }
            if (cmd.isOutput())
            {
                cout << endl;
            }
        }
    }
    return 0;
}