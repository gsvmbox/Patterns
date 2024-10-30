
#include <iostream>
#include <string>
#include<vector>
using namespace std;

class Observer {
public:
	virtual void update() = 0;
};

class Observable {
protected:
	vector<Observer*> _observers;
public:
	void addObserver(Observer* observer) {
		_observers.push_back(observer);
	}
	void notifyUpdate() {
		int size = _observers.size();
		for (int i = 0; i < size; i++) {
			_observers[i]->update();
		}
	}
};

class StudentModel : public Observable {
private:
	string group;
	string name;
public:
	string getGroup() {
		return group;
	}
	void setGroup(string group) {
		this->group = group;
		notifyUpdate();
	}
	string getName() {
		return name;
	}
	void setName(string name) {
		this->name = name;
		notifyUpdate();
	}
};

class StudentView : public Observer {
private:
	StudentModel* model;
public:
	StudentView(StudentModel* model) {
		this->model = model;
		this->model->addObserver(this);
	}
	void update() {
		cout << "-=-=(view1 update)=-=-" << endl;
		print();
	}
	void print() {
		cout << "Student" << endl;
		cout << "Name: " << model->getName();
		cout << " Group: " << model->getGroup() << endl << endl;
	}
};

class StudentView2 : public Observer {
private:
	StudentModel* model;
public:
	StudentView2(StudentModel* model)
	{
		this->model = model;
		this->model->addObserver(this);
	}
	void update() {
		cout << "-=-=(view2 update)=-=-" << endl;
		print();
	}
	void print() {
		cout << "Student" << endl;
		cout << "--- NAME: " << model->getName() << endl;
		cout << "--- GROUP: " << model->getGroup() << endl << endl;
	}
};

class StudentController {
private:
	StudentModel* model = new StudentModel();
	StudentView* view = new StudentView(model);
public:
	StudentController(StudentModel* model, StudentView* view) {
		this->model = model;
		this->view = view;
	}
	void setStudentName(string name) {
		model->setName(name);
	}
	void setStudentGroup(string group) {
		model->setGroup(group);
	}
};

int main()
{
	StudentModel* student = new StudentModel();
	student->setName("Robert");
	student->setGroup("10");
	StudentView* view = new StudentView(student);
	StudentView2* view2 = new StudentView2(student);
	view->print();
	view2->print();
	StudentController controller(student, view);
	controller.setStudentGroup("20");
	// приведет к автоматическому обновлению модели
	// и изменению представлений
	controller.setStudentName("John");
	// приведет к автоматическому обновлению модели
	// и изменению представлений
}