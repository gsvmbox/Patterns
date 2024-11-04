﻿#include <iostream>
#include <vector>
using namespace std;

/**
 * Интерфейс Обработчика объявляет метод построения цепочки обработчиков. Он
 * также объявляет метод для выполнения запроса.
 */
class Handler {
public:
    virtual Handler* SetNext(Handler* handler) = 0;
    virtual string Handle(string request) = 0;
};
/**
 * Поведение цепочки по умолчанию может быть реализовано внутри базового класса
 * обработчика.
 */
class AbstractHandler : public Handler {
    /**
     * @var Handler
     */
private:
    Handler* next_handler_;

public:
    AbstractHandler() : next_handler_(nullptr) {
    }
    Handler* SetNext(Handler* handler) override {
        this->next_handler_ = handler;
        // Возврат обработчика отсюда позволит связать обработчики простым способом,
        // вот так:
        // $monkey->setNext($squirrel)->setNext($dog);
        return handler;
    }
    string Handle(string request) override {
        if (this->next_handler_) {
            return this->next_handler_->Handle(request);
        }

        return {};
    }
};
/**
 * Все Конкретные Обработчики либо обрабатывают запрос, либо передают его
 * следующему обработчику в цепочке.
 */
class MonkeyHandler : public AbstractHandler {
public:
    string Handle(string request) override {
        if (request == "Banana") {
            return "Monkey: I'll eat the " + request + ".\n";
        }
        else {
            return AbstractHandler::Handle(request);
        }
    }
};
class SquirrelHandler : public AbstractHandler {
public:
    string Handle(string request) override {
        if (request == "Nut") {
            return "Squirrel: I'll eat the " + request + ".\n";
        }
        else {
            return AbstractHandler::Handle(request);
        }
    }
};
class DogHandler : public AbstractHandler {
public:
    string Handle(string request) override {
        if (request == "MeatBall") {
            return "Dog: I'll eat the " + request + ".\n";
        }
        else {
            return AbstractHandler::Handle(request);
        }
    }
};
/**
 * Обычно клиентский код приспособлен для работы с единственным обработчиком. В
 * большинстве случаев клиенту даже неизвестно, что этот обработчик является
 * частью цепочки.
 */
void ClientCode(Handler& handler) {
    vector<string> food = { "Nut", "Banana", "Cup of coffee" };
    for (const string& f : food) {
        cout << "Client: Who wants a " << f << "?\n";
        const string result = handler.Handle(f);
        if (!result.empty()) {
            cout << "  " << result;
        }
        else {
            cout << "  " << f << " was left untouched.\n";
        }
    }
}
/**
 * Другая часть клиентского кода создает саму цепочку.
 */
int main() {
    MonkeyHandler* monkey = new MonkeyHandler;
    SquirrelHandler* squirrel = new SquirrelHandler;
    DogHandler* dog = new DogHandler;
    monkey->SetNext(squirrel)->SetNext(dog);

    /**
     * Клиент должен иметь возможность отправлять запрос любому обработчику, а не
     * только первому в цепочке.
     */
    cout << "Chain: Monkey > Squirrel > Dog\n\n";
    ClientCode(*monkey);
    cout << "\n";
    cout << "Subchain: Squirrel > Dog\n\n";
    ClientCode(*squirrel);

    delete monkey;
    delete squirrel;
    delete dog;

    return 0;
}