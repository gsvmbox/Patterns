#include<iostream>
using namespace std;

// Forward Declarations:
class FoodOrder;
class OrderInitiatedState;
class OrderPlacedState;
class FoodPreparationState;
class WaitingToBePickedState;
class OutForDeliveryState;
class DeliveredState;

class FoodOrderState {
public:
    virtual void transitionToNext(FoodOrder* order) = 0;
    virtual void showStatus() = 0;
};

class FoodOrder {
public:
    FoodOrderState* state;

    FoodOrder() {}

    void setState(FoodOrderState* state) {
        this->state = state;
    }

    FoodOrderState* getState() {
        return state;
    }

    void transitionToNextState() {
        state->transitionToNext(this);
    }

    void showCurrentStatus() {
        state->showStatus();
    }

};

class DeliveredState : public FoodOrderState {
public:
    DeliveredState() {}
    void transitionToNext(FoodOrder* order) override {
        cout << "Блюдо  доставлено Заказчику" << endl;
    }

    void showStatus() override {
        cout << "Доставка блюда Заказчику." << endl;
    }
};

class OutForDeliveryState : public FoodOrderState {
public:
    OutForDeliveryState() {}
    void transitionToNext(FoodOrder* order) override {
        DeliveredState* deliveredState = new DeliveredState();
        order->setState(deliveredState);
    }

    void showStatus() override {
        cout << "Блюдо выбрано и готово к доставке, ждем, когда его доставят." << endl;
    }
};

class WaitingToBePickedState : public FoodOrderState {
public:
    WaitingToBePickedState() {}
    void transitionToNext(FoodOrder* order) override {
        OutForDeliveryState* outForDeliveryState = new OutForDeliveryState();
        order->setState(outForDeliveryState);
    }

    void showStatus() override {
        cout << "Блюдо приготовлено, ожидает передачи в доставку . " << endl;
    }
};

class FoodPreparationState : public FoodOrderState {
public:
    FoodPreparationState() {}
    void transitionToNext(FoodOrder* order) override {
        WaitingToBePickedState* waitingToBePickedState = new WaitingToBePickedState();
        order->setState(waitingToBePickedState);
    }

    void showStatus() override {
        cout << "Началось приготовление блюда, ждем, когда оно будет готово." << endl;
    }
};

class OrderPlacedState : public FoodOrderState {
public:
    OrderPlacedState() {}
    void transitionToNext(FoodOrder* order) override {
        FoodPreparationState* foodPreparationState = new FoodPreparationState();
        order->setState(foodPreparationState);
    }

    void showStatus() override {
        cout << "Заказ сделан, ждем, когда начнут готовить блюдо. " << endl;
    }
};

class OrderInitiatedState : public FoodOrderState {
public:
    OrderInitiatedState() {}
    void transitionToNext(FoodOrder* order) override {
        OrderPlacedState* orderPlacedState = new OrderPlacedState();
        order->setState(orderPlacedState);
    }

    void showStatus() override {
        cout << "Заказ принят, ожидаем размещения заказа." << endl;
    }
};


int main() {
    setlocale(LC_ALL, "Russian");

    FoodOrder* order = new FoodOrder();

    FoodOrderState* state = new OrderInitiatedState();
    order->setState(state);

    order->showCurrentStatus();

    order->transitionToNextState();
    order->showCurrentStatus();

    order->transitionToNextState();
    order->showCurrentStatus();

    order->transitionToNextState();
    order->showCurrentStatus();

    order->transitionToNextState();
    order->showCurrentStatus();

    order->transitionToNextState();
    order->showCurrentStatus();

    order->transitionToNextState();

    return 0;
}
