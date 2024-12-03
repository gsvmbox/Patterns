#include <iostream>
using namespace std;

class Strategy
{
public:
	virtual ~Strategy() {}
	virtual void use() = 0;
};

class Strategy_1 : public Strategy
{
public:
	void use() {
		cout << "Strategy_1" << endl;
	}
};

class Strategy_2 : public Strategy
{
public:
	void use() {
		cout << "Strategy_2" << endl;
	}
};

class Strategy_3 : public Strategy
{
public:
	void use() {
		cout << "Strategy_3" << endl;
	}
};

class Context
{
protected:
	Strategy* operation;

public:
	virtual ~Context() {}
	virtual void useStrategy() = 0;
	virtual void setStrategy(Strategy* v) = 0;
};

class Client : public Context
{
public:
	void useStrategy()
	{
		operation->use();
	}

	void setStrategy(Strategy* strateg)
	{
		operation = strateg;
	}
};

int main()
{
	Client customClient;
	Strategy_1 str1;
	Strategy_2 str2;
	Strategy_3 str3;

	customClient.setStrategy(&str1);
	customClient.useStrategy();
	customClient.setStrategy(&str2);
	customClient.useStrategy();
	customClient.setStrategy(&str3);
	customClient.useStrategy();

	return 0;
}