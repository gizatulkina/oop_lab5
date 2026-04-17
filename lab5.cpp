
#include <iostream>
#include <memory>
using namespace std;

class Base {
public:
    Base() {
        cout << "[Base] Конструктор без параметров\n";
    }

    Base(Base* obj) {
        cout << "[Base] Конструктор из указателя\n";
    }

    Base(Base& obj) {
        cout << "[Base] Конструктор из ссылки\n";
    }

    Base(const Base& obj) {
        cout << "[Base] Конструктор копирования\n";
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

    virtual string className() const {
        return "Base";
    }

    virtual bool isA(const string& name) const {
        return name == "Base";
    }

    virtual Base* clone() const {
        cout << "[Base] clone() создаётся копия Base\n";
        return new Base(*this);
    }
};

class Desc : public Base {
public:
    Desc() {
        cout << "[Desc] Конструктор без параметров\n";
    }

    Desc(Desc* obj) : Base(obj) {
        cout << "[Desc] Конструктор из указателя\n";
    }

    Desc(Desc& obj) : Base(obj) {
        cout << "[Desc] Конструктор из ссылки\n";
    }

    Desc(const Desc& obj) : Base(obj) {
        cout << "[Desc] Конструктор копирования\n";
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

    string className() const override {
        return "Desc";
    }

    bool isA(const string& name) const override {
        return name == "Desc" || Base::isA(name);
    }

    Base* clone() const override {
        cout << "[Desc] clone() создаётся копия Desc\n";
        return new Desc(*this);
    }
};


void testCast() {
    cout << "\nПРОВЕРКА ПРИВЕДЕНИЯ ТИПОВ\n";

    cout << "Создаём объект Desc через указатель Base*\n";
    Base* b = new Desc();

    cout << "Определение типа через className(): " << b->className() << endl;

    cout << "Проверка через isA(\"Desc\"):\n";
    if (b->isA("Desc")) {
        cout << "Объект действительно является Desc\n";
    }

    cout << "\nБезопасное приведение dynamic_cast:\n";
    Desc* d1 = dynamic_cast<Desc*>(b);
    cout << "Результат: " << d1 << endl;

    cout << "\nОпасное приведение (C-style cast):\n";
    Desc* d2 = (Desc*)b;
    cout << "Результат: " << d2 << endl;

    delete b;
}

void testVirtual() {
    cout << "\nВИРТУАЛЬНЫЕ И НЕВИРТУАЛЬНЫЕ МЕТОДЫ\n";

    Base* b = new Desc();

    cout << "\nВызов НЕвиртуального метода:\n";
    b->method1NonVirtual();

    cout << "\nВызов ВИРТУАЛЬНОГО метода:\n";
    b->method1Virtual();

    delete b;
}

void func1(Base obj) {
    cout << "[func1] Передача ПО ЗНАЧЕНИЮ (создаётся копия объекта)\n";
}

void func2(Base* obj) {
    cout << "[func2] Передача УКАЗАТЕЛЯ (копии нет)\n";
}

void func3(Base& obj) {
    cout << "[func3] Передача ССЫЛКИ (копии нет)\n";
}

void testPass() {
    cout << "\n ПЕРЕДАЧА ОБЪЕКТОВ В ФУНКЦИИ \n";

    Desc d;

    cout << "\nПередаём объект Desc:\n";
    func1(d);
    func2(&d);
    func3(d);
}

Base f1() {
    static Base b;
    cout << "[f1] Возврат ПО ЗНАЧЕНИЮ (локальный static объект)\n";
    return b;
}

Base* f2() {
    static Base b;
    cout << "[f2] Возврат УКАЗАТЕЛЯ на static объект\n";
    return &b;
}

Base& f3() {
    static Base b;
    cout << "[f3] Возврат ССЫЛКИ на static объект\n";
    return b;
}

Base f4() {
    cout << "[f4] Возврат ПО ЗНАЧЕНИЮ \n";
    Base* b = new Base();
    return *b;
}

Base* f5() {
    cout << "[f5] Возврат УКАЗАТЕЛЯ на динамический объект\n";
    return new Base();
}

Base& f6() {
    cout << "[f6] Возврат ССЫЛКИ на динамический объект\n";
    Base* b = new Base();
    return *b;
}

void testReturn() {
    cout << "\n ВОЗВРАТ ОБЪЕКТОВ \n";

    Base a = f1();
    Base* b = f2();
    Base& c = f3();

    Base d = f4();

    Base* e = f5();
    delete e;

    Base& f = f6();
    delete &f;
}

void testSmart() {
    cout << "\n УМНЫЕ УКАЗАТЕЛИ \n";

    cout << "\nunique_ptr (один владелец):\n";
    {
        unique_ptr<Base> p = make_unique<Desc>();
        p->method1Virtual();
    }

    cout << "\nshared_ptr (несколько владельцев):\n";
    {
        shared_ptr<Base> p1 = make_shared<Desc>();
        cout << "Счётчик ссылок: " << p1.use_count() << endl;

        {
            shared_ptr<Base> p2 = p1;
            cout << "Счётчик ссылок после копирования: " << p1.use_count() << endl;
        }

        cout << "После выхода из блока: " << p1.use_count() << endl;
    }
}

int main() {
    setlocale(LC_ALL, "Russian");

    testVirtual();
    testCast();
    testPass();
    testReturn();
    testSmart();

    return 0;
}