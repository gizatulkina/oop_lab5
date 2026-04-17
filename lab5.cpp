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
};

void testCast() {
    cout << "\nПРОВЕРКА ПРИВЕДЕНИЯ ТИПОВ\n";

    Base* b = new Desc();

    cout << "className(): " << b->className() << endl;

    if (b->isA("Desc")) {
        cout << "Объект — Desc\n";
    }

    cout << "\ndynamic_cast:\n";
    Desc* d1 = dynamic_cast<Desc*>(b);
    cout << "d1 = " << d1 << endl;

    cout << "\nC-style cast:\n";
    Desc* d2 = (Desc*)b;
    cout << "d2 = " << d2 << endl;

    delete b;
}

int main() {
    testCast();
    return 0;
}