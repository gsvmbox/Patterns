#include <iostream>
#include <vector>
using namespace std;

/*Receiver
Создание устройств, Light и Speaker. Классы Light и Speaker  
будут использовать общий интерфейс Device.*/
class Device
{
public:
    virtual void on() = 0;
    virtual void off() = 0;
    virtual void up() = 0;
    virtual void down() = 0;
};

class Light : public Device
{
public:
    void on() {
        cout << "Turn on light" << endl; }

    void off() {
        cout << "Turn off light" << endl; }

    void up() {
        cout << "Increase brightness" << endl; }

    void down() {
        cout << "Decrease brightness" << endl; }
};

class Speaker : public Device
{
public:
    void on() {
        cout << "Turn on speaker" << endl; }

    void off() {
        cout << "Turn off speaker" << endl; }

    void up() {
        cout << "Increase volume" << endl; }

    void down() {
        cout << "Decrease volume" << endl; }
};

/*Command Interface
Интерфейс Command  задает общий интерфейс для классов конкретных команд.*/
class Command
{
public:
    virtual void execute() = 0;
};

/*Concrete Commands
Классы конкретных команд, реализующих функциональность команд on, off, up и down.*/
class OnCommand : public Command
{
private:
    Device* device;

public:
    OnCommand(Device* device) {
        this->device = device; }

    void execute() {
        this->device->on(); }
};

class OffCommand : public Command
{
private:
    Device* device;

public:
    OffCommand(Device* device) {
        this->device = device; }

    void execute() {
        this->device->off(); }
};

class UpCommand : public Command
{
private:
    Device* device;

public:
    UpCommand(Device* device) {
        this->device = device; }

    void execute() {
        this->device->up(); }
};

class DownCommand : public Command
{
private:
    Device* device;
public:
    DownCommand(Device* device) {
        this->device = device; }
    void execute() {
        this->device->down(); }
};

/*Invoker

Класс Инициатора Invoker  описывает команды, доступные клиенту. 
Invoker принимает конкретные экземпляры команд в качестве параметров конструктора. 
Открытые методы Invoker настроены на вызов метода execute() соответствующих команд*/
class Invoker
{
private:
    Command* onCommand;
    Command* offCommand;
    Command* upCommand;
    Command* downCommand;

public:
    Invoker(Command* onCommand, Command* offCommand, Command* upCommand, Command* downCommand)
    {
        this->onCommand = onCommand;
        this->offCommand = offCommand;
        this->upCommand = upCommand;
        this->downCommand = downCommand;
    }

    void clickOn() {
        this->onCommand->execute(); }

    void clickOff() {
        this->offCommand->execute(); }

    void clickUp() {
        this->upCommand->execute(); }

    void clickDown() {
        this->downCommand->execute(); }
};
/*Client
Клиентский код отвечает за создание  объектов конкретных команд и передачу их Invoker.*/
void ClientCode(Device* dev) {
    Invoker* invoker = new Invoker(new OnCommand(dev), new OffCommand(dev), new UpCommand(dev), new DownCommand(dev));
    invoker->clickOn();
    invoker->clickUp();
    invoker->clickDown();
    invoker->clickOff();
}

int main() {
//Создание устройств
    Light* light = new Light;
    Speaker* sound = new Speaker;
    ClientCode(light);   cout << endl;
    ClientCode(sound);

    delete light;
    delete sound;

   return 0;
};
