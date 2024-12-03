#include <iostream>
#include <algorithm>

using namespace std;

/**
 * Интерфейс Стратегии объявляет операции, общие для всех поддерживаемых версий
 * некоторого алгоритма.
 *
 * Контекст использует этот интерфейс для вызова алгоритма, определённого
 * Конкретными Стратегиями.
 */
class Strategy
{
public:
    virtual ~Strategy() = default;
    virtual string doAlgorithm(const string data) const = 0;
};

/**
 * Контекст определяет интерфейс, представляющий интерес для клиентов.
 */

class Context
{
    /**
     * @var Strategy Контекст хранит ссылку на один из объектов Стратегии.
     * Контекст не знает конкретного класса стратегии. Он должен работать со
     * всеми стратегиями через интерфейс Стратегии.
     */
private:
    Strategy* strategy_;
    /**
     * Обычно Контекст принимает стратегию через конструктор, а также
     * предоставляет сеттер для её изменения во время выполнения.
     */
public:
    explicit Context(Strategy* strategy) : strategy_(strategy)
    {
    }
    /**
     * Обычно Контекст позволяет заменить объект Стратегии во время выполнения.
     */
    void set_strategy(Strategy* strategy)
    {
        strategy_ = strategy;
    }
    /**
     * Вместо того, чтобы самостоятельно реализовывать множественные версии
     * алгоритма, Контекст делегирует некоторую работу объекту Стратегии.
     */
    void doSomeBusinessLogic() const
    {
        if (strategy_) {
            cout << "Context: Сортировка данных по алгоритму, который реализует стратегия\n";
            string result = strategy_->doAlgorithm("cxhkjhvseth");
            cout << result << "\n";
        }
        else {
            cout << "Context: Стратегия не задана\n";
        }
    }
};

/**
 * Конкретные Стратегии реализуют алгоритм, следуя базовому интерфейсу
 * Стратегии. Этот интерфейс делает их взаимозаменяемыми в Контексте.
 */
class ConcreteStrategyA : public Strategy
{
public:
    string doAlgorithm(const string data) const override
    {
        string result(data);
        sort(begin(result), end(result));

        return result;
    }
};
class ConcreteStrategyB : public Strategy
{
    string doAlgorithm(const string data) const override
    {
        string result(data);
        sort(begin(result), end(result), greater<>());

        return result;
    }
};
/**
 * Клиентский код выбирает конкретную стратегию и передаёт её в контекст. Клиент
 * должен знать о различиях между стратегиями, чтобы сделать правильный выбор.
 */

void clientCode()
{
    Context* context = new Context(new ConcreteStrategyA);
    cout << "Client: Стратегия сортировки - по возрастанию.\n";
    context->doSomeBusinessLogic();
    cout << "\n";
    cout << "Client: Стратегия сортировки - по убыванию.\n";
    context->set_strategy(new ConcreteStrategyB);
    context->doSomeBusinessLogic();
}

int main()
{
    setlocale(LC_ALL, "Russian");
    clientCode();
    return 0;
}