//Выбор стратигий сортировки массива чисел

#include <iostream>
#include <vector>
using namespace std;

class Strategy
{
public:
    virtual vector<int> Sort(vector<int>) const = 0;
    virtual ~Strategy() {}
};

class Context
{
private:
    Strategy* strategy_;
    
public:
      
    explicit  Context(Strategy* strategy) : strategy_(strategy)
    {}
    virtual ~Context() {}

    void set_strategy(Strategy* strategy)
    {
        strategy_ = strategy;
    }

    vector<int> Sort(vector<int> mass) const
    {
       return this->strategy_->Sort(mass);
    }
    
    void PrintArray(vector<int> mass)
    {
        for (int i = 0; i < mass.size(); i++)
            cout<<mass[i]<<" ";
        cout<<endl;
    }
};


// Пузырьковая сортировка.
class BubbleSort : public Strategy
{
public:
     vector<int> Sort(vector<int> mass) const override
    {
        cout<<"BubbleSort"<<endl;
        for (int i = 0; i < mass.size(); i++)
        {
            for (int j = mass.size() - 1; j > i; j--)
            {
                if (mass[j] < mass[j - 1])
                {
                    int temp = mass[j];
                    mass[j] = mass[j-1];
                    mass[j - 1] = temp;
                }
            }
        }
        return mass;
    }
};

// Сортировка выбором.
class SelectionSort : public Strategy
{
    vector<int> Sort(vector<int> mass) const override
    {
        cout << "SelectionSort" << endl;
        for (int i = 0; i < mass.size() - 1; i++)
        {
            int k = i;
            for (int j = i + 1; j < mass.size(); j++)
                if (mass[k] > mass[j])
                    k = j;
            if (k != i)
            {
                int temp = mass[k];
                mass[k] = mass[i];
                mass[i] = temp;
            }
        }
        return mass;
    }
};

class InsertionSort : public Strategy
{
    vector<int> Sort(vector<int> mass) const override
    {
        cout << "InsertionSort" << endl;
        for (int i = 1; i < mass.size(); i++)
        {
            int j = 0;
            int buffer = mass[i];
            for (j = i - 1; j >= 0; j--)
            {
                if (mass[j] < buffer)
                    break;
                mass[j + 1] = mass[j];
            }
            mass[j + 1] = buffer;
        }
        return mass;
    }
};

int main()
{
    vector<int> mass{ 3, 5, 1, 2, 4 };
    vector<int> sorted;

    Context* context = new Context(new BubbleSort);
    context->PrintArray(mass);
    sorted = context->Sort(mass);
    context->PrintArray(sorted);

    context->set_strategy(new SelectionSort);
    sorted = context->Sort(mass);
    context->PrintArray(sorted);

    context->set_strategy(new InsertionSort);
    sorted = context->Sort(mass);
    context->PrintArray(sorted);
    
    return 0;
}

