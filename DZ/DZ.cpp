#include <iostream>
#include <string>

using namespace std;

// Шаблонная функция для обмена значениями двух переменных
template <typename T>
void swapValues(T& a, T& b) {
    T temp = a;
    a = b;
    b = temp;
}

// Дополнительная шаблонная функция с двумя разными шаблонными параметрами
// (меняет местами значения разных типов - требует совместимости типов)
template <typename T1, typename T2>
void swapDifferentTypes(T1& a, T2& b) {
    T1 temp = a;
    a = static_cast<T1>(b);
    b = static_cast<T2>(temp);
}

int main() {
    setlocale(LC_ALL, "Russian");

    cout << "=== ДЕМОНСТРАЦИЯ РАБОТЫ ШАБЛОННОЙ ФУНКЦИИ ОБМЕНА ===" << endl;
    cout << endl;

    // 1. Обмен значениями типа int
    cout << "--- Обмен int ---" << endl;
    int x = 10, y = 25;
    cout << "До обмена: x = " << x << ", y = " << y << endl;
    swapValues(x, y);
    cout << "После обмена: x = " << x << ", y = " << y << endl;
    cout << endl;

    // 2. Обмен значениями типа double
    cout << "--- Обмен double ---" << endl;
    double a = 3.14159, b = 2.71828;
    cout << "До обмена: a = " << a << ", b = " << b << endl;
    swapValues(a, b);
    cout << "После обмена: a = " << a << ", b = " << b << endl;
    cout << endl;

    // 3. Обмен значениями типа string
    cout << "--- Обмен string ---" << endl;
    string str1 = "Привет", str2 = "Мир";
    cout << "До обмена: str1 = \"" << str1 << "\", str2 = \"" << str2 << "\"" << endl;
    swapValues(str1, str2);
    cout << "После обмена: str1 = \"" << str1 << "\", str2 = \"" << str2 << "\"" << endl;
    cout << endl;

    // 4. Обмен значениями типа char
    cout << "--- Обмен char ---" << endl;
    char c1 = 'A', c2 = 'Z';
    cout << "До обмена: c1 = " << c1 << ", c2 = " << c2 << endl;
    swapValues(c1, c2);
    cout << "После обмена: c1 = " << c1 << ", c2 = " << c2 << endl;
    cout << endl;

    // 5. Обмен значениями типа bool
    cout << "--- Обмен bool ---" << endl;
    bool b1 = true, b2 = false;
    cout << "До обмена: b1 = " << (b1 ? "true" : "false") << ", b2 = " << (b2 ? "true" : "false") << endl;
    swapValues(b1, b2);
    cout << "После обмена: b1 = " << (b1 ? "true" : "false") << ", b2 = " << (b2 ? "true" : "false") << endl;
    cout << endl;

    // 6. Демонстрация работы с разными типами (int и double)
    cout << "--- Обмен разными типами (int и double) ---" << endl;
    int intValue = 42;
    double doubleValue = 99.99;
    cout << "До обмена: intValue = " << intValue << ", doubleValue = " << doubleValue << endl;
    swapDifferentTypes(intValue, doubleValue);
    cout << "После обмена: intValue = " << intValue << ", doubleValue = " << doubleValue << endl;
    cout << "(Примечание: происходит преобразование типов)" << endl;
    cout << endl;

    // 7. Демонстрация работы с разными типами (int и string - требует осторожности)
    cout << "--- Обмен разными типами (int и string) ---" << endl;
    int num = 100;
    string text = "123";
    cout << "До обмена: num = " << num << ", text = \"" << text << "\"" << endl;

    // Преобразование string в int (если возможно)
    // Внимание: это демонстрация, в реальном коде нужно проверять возможность преобразования
    try {
        int tempNum = num;
        num = stoi(text);
        text = to_string(tempNum);
        cout << "После обмена: num = " << num << ", text = \"" << text << "\"" << endl;
    }
    catch (const invalid_argument& e) {
        cout << "Ошибка: невозможно преобразовать строку в число!" << endl;
    }
    cout << endl;

    // 8. Использование стандартной функции swap (для сравнения)
    cout << "--- Сравнение с std::swap ---" << endl;
    int p = 7, q = 14;
    cout << "До std::swap: p = " << p << ", q = " << q << endl;
    std::swap(p, q);
    cout << "После std::swap: p = " << p << ", q = " << q << endl;
    cout << "Наша функция swapValues работает аналогично!" << endl;

    return 0;
}