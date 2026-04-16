#include <iostream>
#include <string>

using namespace std;

// Шаблонный класс Box (коробка)
template <typename T>
class Box {
private:
    T item;  // Приватная переменная типа T

public:
    // Конструктор для инициализации
    Box(const T& value) : item(value) {
        cout << "Создана коробка с элементом!" << endl;
    }

    // Конструктор по умолчанию
    Box() : item() {}

    // Set метод - устанавливает значение
    void setItem(const T& value) {
        item = value;
    }

    // Get метод - возвращает значение
    T getItem() const {
        return item;
    }

    // Метод для вывода информации (демонстрационный)
    void display() const {
        cout << "Коробка содержит: " << item << endl;
    }
};

int main() {
    setlocale(LC_ALL, "Russian");

    cout << "=== ДЕМОНСТРАЦИЯ РАБОТЫ ШАБЛОННОГО КЛАССА BOX ===" << endl;
    cout << endl;

    // 1. Коробка с типом int
    cout << "--- Коробка с типом int ---" << endl;
    Box<int> intBox(42);
    intBox.display();
    cout << "Получение значения через getItem(): " << intBox.getItem() << endl;
    intBox.setItem(100);
    cout << "После setItem(100): " << intBox.getItem() << endl;
    cout << endl;

    // 2. Коробка с типом double
    cout << "--- Коробка с типом double ---" << endl;
    Box<double> doubleBox(3.14159);
    doubleBox.display();
    cout << "Получение значения через getItem(): " << doubleBox.getItem() << endl;
    doubleBox.setItem(2.71828);
    cout << "После setItem(2.71828): " << doubleBox.getItem() << endl;
    cout << endl;

    // 3. Коробка с типом string
    cout << "--- Коробка с типом string ---" << endl;
    Box<string> stringBox("Привет, мир!");
    stringBox.display();
    cout << "Получение значения через getItem(): " << stringBox.getItem() << endl;
    stringBox.setItem("C++ шаблоны");
    cout << "После setItem(\"C++ шаблоны\"): " << stringBox.getItem() << endl;
    cout << endl;

    // 4. Дополнительная демонстрация - создание коробки без начального значения
    cout << "--- Коробка с типом char (создана без начального значения) ---" << endl;
    Box<char> charBox;
    charBox.setItem('A');
    charBox.display();
    cout << endl;

    // 5. Коробка с типом float
    cout << "--- Коробка с типом float ---" << endl;
    Box<float> floatBox(9.99f);
    floatBox.display();
    cout << endl;

    // 6. Демонстрация работы с несколькими коробками одновременно
    cout << "--- Работа с несколькими коробками ---" << endl;
    Box<int> box1(10);
    Box<double> box2(20.5);
    Box<string> box3("Тест");

    cout << "box1: " << box1.getItem() << endl;
    cout << "box2: " << box2.getItem() << endl;
    cout << "box3: " << box3.getItem() << endl;

    return 0;
}