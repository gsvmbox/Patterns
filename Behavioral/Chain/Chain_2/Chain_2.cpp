#include <iostream>
#include <string>
using namespace std;
/*Паттерн Цепочка обязанностей
 *Модель посльзователя со счетами в нескольких банках
*/
class Account
{
public:
    Account(void)
        : name_("empty account"), balance_(0), successor_()
    {
    }

    void setNext(Account* account)
    {
        successor_ = account;
    }

    void pay(float amount)
    {
        if (canPay(amount)) {
            cout << "Paid " << amount << " using " << name_ << "."
                << endl;
            balance_ -= amount;
        }
        else if (successor_) {
            cout << "Cannot pay using " << name_ << ". Proceeding ..."
                << endl;
            successor_->pay(amount);
        }
        else {
            cout << "None of the accounts have enough balance." << endl;
        }
    }

    bool canPay(float amount)
    {
        return balance_ >= amount;
    }

protected:
    string name_;
    float balance_;
    Account* successor_;
};

class Bank_1 : public Account
{
public:
    Bank_1(float balance)
    {
        name_ = "Bank_1";
        balance_ = balance;
    }
};

class Bank_2 : public Account
{
public:
    Bank_2(float balance)
    {
        name_ = "Bank_2";
        balance_ = balance;
    }
};

class Bank_3 : public Account
{
public:
    Bank_3(float balance)
    {
        name_ = "Bank_3";
        balance_ = balance;
    }
};

int main()
{
    // Создане цепочки: bank_1->bank_2->bank_3.

    // Предварительно создадим счета
 
   Bank_1* bank_1 = new Bank_1(100);
   Bank_2* bank_2 = new Bank_2(200);
   Bank_3* bank_3 = new Bank_3(300);


    // Очередь в виде цепочки обработчиков
    bank_1->setNext(bank_2);
    bank_2->setNext(bank_3);
  
    // Попытка совершить платеж, начиная с приоритетного счета (т.е. Bank_1).
    bank_1->pay(350);
   
    return 0;
}