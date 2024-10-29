#pragma once

class Singleton;

class SingletonDestroyer
{
private:
	Singleton* p_instance;
public:
	~SingletonDestroyer() { delete p_instance; }
	void initialize(Singleton* p) { p_instance = p; };
};


class Singleton
{
private:
	static Singleton* p_instance;
	static SingletonDestroyer destroyer;
protected:
	Singleton() {}
	Singleton(const Singleton&);//копирующий конструктор
	Singleton& operator = (Singleton&);  //и операцию присваивания лучше запретить
	~Singleton() {}
	friend class SingletonDestroyer;
public:
	static Singleton* getInstance() {
		if (!p_instance)
		{
			p_instance = new Singleton();
			destroyer.initialize(p_instance);
		}
		return p_instance;
	}
};

