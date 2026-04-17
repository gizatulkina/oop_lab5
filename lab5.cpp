#include <iostream>
using namespace std;

class Base {
public:
    Base() {
        cout << "[Base] Конструктор без параметров\n";
    }

    virtual ~Base() {
        cout << "[Base] Деструктор\n";
    }

    void method1NonVirtual() {
        method2NonVirtual();
    }

    void method2NonVirtual() {
        cout << "[Base] method2NonVirtual\n";
    }

    virtual void method1Virtual() {
        method2Virtual();
    }

    virtual void method2Virtual() {
        cout << "[Base] method2Virtual\n";
    }

    virtual string className() const {
        return "Base";
    }

    virtual bool isA(const string& name) const {
        return name == "Base";
    }
};

class Desc : public Base {
public:
    string className() const override {
        return "Desc";
    }

    bool isA(const string& name) const override {
        return name == "Desc" || Base::isA(name);
    }

    void method2Virtual() override {
        cout << "[Desc] method2Virtual\n";
    }
};

int main() {
    Base* b = new Desc();

    cout << "Тип: " << b->className() << endl;

    if (b->isA("Desc")) {
        cout << "Это Desc\n";
    }

    delete b;
}