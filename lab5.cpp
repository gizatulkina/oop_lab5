#include <iostream>
using namespace std;

class Base {
public:
    Base() {
        cout << "[Base] Конструктор\n";
    }

    virtual ~Base() {
        cout << "[Base] Деструктор\n";
    }
};

class Desc : public Base {
public:
    Desc() {
        cout << "[Desc] Конструктор\n";
    }

    ~Desc() override {
        cout << "[Desc] Деструктор\n";
    }
};

void func1(Base obj) {
    cout << "[func1] передача по значению (копия)\n";
}

void func2(Base* obj) {
    cout << "[func2] передача по указателю\n";
}

void func3(Base& obj) {
    cout << "[func3] передача по ссылке\n";
}

void testPass() {
    cout << "\nПЕРЕДАЧА В ФУНКЦИИ\n";

    Desc d;

    func1(d);
    func2(&d);
    func3(d);
}

int main() {
    testPass();
    return 0;
}