#include <iostream>
#include <vector>
using namespace std;

/*Receiver
We create two devices, Light and Speaker. We create the Light and the Speaker classes 
that implement the Device interface.*/
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
We create the Command interface which will be implemented by the concrete command classes.*/
class Command
{
public:
    virtual void execute() = 0;
};

/*Concrete Commands
Lets create the concrete commands for the functionalities on, off, up and down.*/
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

Now we create the Invoker class and assign all the commands it can execute. 
The Invoker accepts the concrete command instances as the constructor parameters. 
The public methods of the Invoker are configured to call the execute() method of the respective commands.*/
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

Finally, we create the client class RemoteApplication responsible for creating the concrete command objects
and assigning them to the Invoker.*/
class RemoteApplication
{
public:
    static void main(vector<string>& args)
    {
        Light* light = new Light();
        Speaker* sound = new Speaker;

        //Invoker* invoker = new Invoker(new OnCommand(light), new OffCommand(light), new UpCommand(light), new DownCommand(light));
        Invoker* invoker = new Invoker(new OnCommand(sound), new OffCommand(sound), new UpCommand(sound), new DownCommand(sound));

        invoker->clickOn();
        invoker->clickOff();
        invoker->clickUp();
        invoker->clickDown();
    }
};

int main(int argc, char** argv) {
    vector<string> parameter(argv + 1, argv + argc);
    RemoteApplication::main(parameter);
    return 0;
};
