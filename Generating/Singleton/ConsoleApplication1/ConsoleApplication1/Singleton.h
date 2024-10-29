#pragma once
class Singleton
{
private:
    static Singleton* p_instance;
    int a;
    // ������������ � �������� ������������ ���������� ��������
    Singleton() {}
    Singleton(const Singleton&);
    Singleton& operator=(Singleton&);
public:
    static Singleton* getInstance() {
        if (!p_instance) 
            p_instance = new Singleton();
            
        return p_instance;
    }

    
};

