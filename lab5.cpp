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
        cout << "[Base] method1NonVirtual вызывает method2NonVirtual\n";
        method2NonVirtual();
    }

    void method2NonVirtual() {
        cout << "[Base] method2NonVirtual\n";
    }

    virtual void method1Virtual() {
        cout << "[Base] method1Virtual вызывает method2Virtual\n";
        method2Virtual();
    }

    virtual void method2Virtual() {
        cout << "[Base] method2Virtual\n";
    }
};

class Desc : public Base {
public:
    Desc() {
        cout << "[Desc] Конструктор без параметров\n";
    }

    ~Desc() override {
        cout << "[Desc] Деструктор\n";
    }

    void method2NonVirtual() {
        cout << "[Desc] method2NonVirtual (перекрытие)\n";
    }

    void method1Virtual() override {
        cout << "[Desc] method1Virtual вызывает method2Virtual\n";
        method2Virtual();
    }

    void method2Virtual() override {
        cout << "[Desc] method2Virtual\n";
    }
};

int main() {
    Base* b = new Desc();

    cout << "\nНЕВИРТУАЛЬНЫЕ МЕТОДЫ\n";
    b->method1NonVirtual();

    cout << "\nВИРТУАЛЬНЫЕ МЕТОДЫ\n";
    b->method1Virtual();

    delete b;
}