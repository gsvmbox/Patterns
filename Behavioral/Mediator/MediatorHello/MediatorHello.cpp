﻿#include <iostream>
#include <string>
using namespace std;

class Colleague;
class Mediator;
class ConcreteMediator;
class ConcreteColleague1;
class ConcreteColleague2;

class Mediator
{
public:
    virtual void Send(std::string const& message, Colleague* colleague) const = 0;
};

class Colleague
{
protected:
    Mediator* mediator_;

public:
    explicit Colleague(Mediator* mediator) :mediator_(mediator)
    {
    }
};

class ConcreteColleague1 :public Colleague
{
public:
    explicit ConcreteColleague1(Mediator* mediator) :Colleague(mediator)
    {
    }

    void Send(std::string const& message)
    {
        mediator_->Send(message, this);
    }

    void Notify(std::string const& message)
    {
       cout << "Colleague1 gets message '" << message << "'" <<endl;
    }
};

class ConcreteColleague2 :public Colleague
{
public:
    explicit ConcreteColleague2(Mediator* mediator) :Colleague(mediator)
    {
    }

    void Send(std::string const& message)
    {
        mediator_->Send(message, this);
    }

    void Notify(std::string const& message)
    {
       cout << "Colleague2 gets message '" << message << "'" <<endl;
    }
};

class ConcreteMediator :public Mediator
{
protected:
    ConcreteColleague1* m_Colleague1;
    ConcreteColleague2* m_Colleague2;
public:
    void SetColleague1(ConcreteColleague1* c)
    {
        m_Colleague1 = c;
    }

    void SetColleague2(ConcreteColleague2* c)
    {
        m_Colleague2 = c;
    }

    virtual void Send(std::string const& message, Colleague* colleague) const
    {
        if (colleague == m_Colleague1)
        {
            m_Colleague2->Notify(message);
        }
        else if (colleague == m_Colleague2)
        {
            m_Colleague1->Notify(message);
        }
    }
};

int main()
{
    ConcreteMediator m;

    ConcreteColleague1 c1(&m);
    ConcreteColleague2 c2(&m);

    m.SetColleague1(&c1);
    m.SetColleague2(&c2);

    c1.Send("How are you?");
    c2.Send("Fine, thanks");

    return 0;
}

