#include <iostream>
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
        // например:
        // director->SetNext(engineer)->SetNext(hr);
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
class Engineer : public AbstractHandler {
public:
    string Handle(string request) override {
        if (request == "Компьютер") {
            return "ИНЖЕНЕР: Мне нужен " + request + ".\n";
        }
        else {
            return AbstractHandler::Handle(request);
        }
    }
};
class Director : public AbstractHandler {
public:
    string Handle(string request) override {
        if (request == "Автомобиль") {
            return "ДИРЕКТОР: Мне нужен " + request + ".\n";
        }
        else {
            return AbstractHandler::Handle(request);
        }
    }
};
class HR : public AbstractHandler {
public:
    string Handle(string request) override {
        if (request == "Принтер") {
            return "КАДРЫ: Мне нужен " + request + ".\n";
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
    vector<string> equipment = { "Компьютер", "Автомобиль", "Принтер", "Кондиционер"};
    for (const string& f : equipment) {
        cout << "Client: Кому нужен " << f << "?\n";
        const string result = handler.Handle(f);
        if (!result.empty()) {
            cout << "  " << result;
        }
        else {
            cout << "  " << f << " никому не нужен.\n";
        }
    }
}
/**
 * Другая часть клиентского кода создает саму цепочку.
 */
int main() {
    setlocale(LC_ALL, "Russian");
    Director* director = new Director;
    Engineer* engineer = new Engineer;
    HR* hr = new HR;
    director->SetNext(engineer)->SetNext(hr);

    /**
     * Клиент должен иметь возможность отправлять запрос любому обработчику, а не
     * только первому в цепочке.
     */
    cout << "Цепочка: Директор > Инженер > Кадры\n\n";
    ClientCode(*director);
    cout << "\n";
    cout << "Цепочка: Инженер > Кадры\n\n";
    ClientCode(*engineer);

    delete director;
    delete engineer;
    delete hr;

    return 0;
}