#include <iostream>
#include <string>

using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");

    cout << "=== ДЕМОНСТРАЦИЯ ТРЁХ СПОСОБОВ ИНИЦИАЛИЗАЦИИ INT ИЗ DOUBLE ===" << endl;
    cout << endl;

    double doubleValue = 3.14159;

    // 1. Инициализация через копирование (copy initialization) - с использованием '='
    cout << "1. Инициализация через копирование (copy initialization):" << endl;
    int copyInit = doubleValue;
    cout << "   doubleValue = " << doubleValue << endl;
    cout << "   int copyInit = doubleValue; -> copyInit = " << copyInit << endl;
    cout << "   Результат: дробная часть отброшена (3)" << endl;
    cout << "   Уровень предупреждения: компилятор может выдать warning C4244" << endl;
    cout << endl;

    // 2. Инициализация через прямую инициализацию (direct initialization) - с использованием '()'
    cout << "2. Прямая инициализация (direct initialization):" << endl;
    int directInit(doubleValue);
    cout << "   doubleValue = " << doubleValue << endl;
    cout << "   int directInit(doubleValue); -> directInit = " << directInit << endl;
    cout << "   Результат: дробная часть отброшена (3)" << endl;
    cout << "   Уровень предупреждения: компилятор может выдать warning C4244" << endl;
    cout << endl;

    // 3. Инициализация через унифицированную инициализацию (uniform initialization) - с использованием '{}'
    cout << "3. Унифицированная инициализация (uniform initialization с фигурными скобками):" << endl;
    cout << "   doubleValue = " << doubleValue << endl;
    // int uniformInit{ doubleValue }; // ЭТА СТРОКА ВЫЗОВЕТ ОШИБКУ КОМПИЛЯЦИИ!
    // Для демонстрации закомментируем, чтобы программа скомпилировалась:
    cout << "   int uniformInit{ doubleValue }; // !!! ОШИБКА КОМПИЛЯЦИИ !!!" << endl;
    cout << "   Компилятор выдаёт: error C2397: преобразование из 'double' в 'int' требует сужающего преобразования" << endl;
    cout << endl;

    // Альтернатива: если всё же нужно скомпилировать с фигурными скобками, 
    // нужно явное приведение типа:
    int uniformInitExplicit{ static_cast<int>(doubleValue) };
    cout << "   (Рабочий вариант с явным приведением типа):" << endl;
    cout << "   int uniformInitExplicit{ static_cast<int>(doubleValue) }; -> uniformInitExplicit = " << uniformInitExplicit << endl;
    cout << endl;

    // Дополнительная демонстрация с разными значениями
    cout << "=== ДОПОЛНИТЕЛЬНЫЕ ТЕСТЫ ===" << endl;
    cout << endl;

    double testValues[] = { 2.1, 2.5, 2.9, -1.7, 123.456 };

    for (double val : testValues) {
        cout << "double = " << val << " -> ";
        int copy = val;
        int direct(val);
        // int uniform{ val }; // ОШИБКА!
        cout << "copy = " << copy << ", direct = " << direct;
        cout << " (дробная часть отбрасывается, а не округляется!)" << endl;
    }

    cout << endl;
    cout << "=== ОТВЕТЫ НА ВОПРОСЫ ===" << endl;
    cout << endl;

    cout << "ВОПРОС 1: Почему инициализация через фигурные скобки более безопасна?" << endl;
    cout << "--------------------------------------------------------------------------------" << endl;
    cout << "Инициализация через фигурные скобки (uniform initialization) более безопасна," << endl;
    cout << "потому что она ЗАПРЕЩАЕТ сужающие преобразования (narrowing conversions)." << endl;
    cout << endl;
    cout << "Сужающее преобразование — это когда при присваивании теряется точность или" << endl;
    cout << "значение может выйти за допустимые пределы. Примеры:" << endl;
    cout << "  - double → int (теряется дробная часть)" << endl;
    cout << "  - long long → int (выход за пределы)" << endl;
    cout << "  - int → char (потеря старших битов)" << endl;
    cout << endl;
    cout << "При использовании {} компилятор выдаёт ОШИБКУ, а не просто предупреждение," << endl;
    cout << "что заставляет программиста явно указать намерение через static_cast<>()." << endl;
    cout << endl;
    cout << "Сравнение:" << endl;
    cout << "  int a = 3.14;      // OK (только warning) - потеря данных" << endl;
    cout << "  int b(3.14);       // OK (только warning) - потеря данных" << endl;
    cout << "  int c{3.14};       // ОШИБКА компиляции - запрещено!" << endl;
    cout << endl;

    cout << "ВОПРОС 2: В каком случае компилятор обязан выдать ошибку или предупреждение согласно заданию?" << endl;
    cout << "--------------------------------------------------------------------------------" << endl;
    cout << "Компилятор ОБЯЗАН выдать ошибку или предупреждение в следующих случаях:" << endl;
    cout << endl;
    cout << "1. Согласно заданию (и стандарту C++11 и новее):" << endl;
    cout << "   - При использовании uniform initialization { } для сужающего преобразования" << endl;
    cout << "     компилятор ОБЯЗАН выдать ОШИБКУ (диагностическое сообщение)." << endl;
    cout << "     Пример: int x{ 3.14 }; // error: narrowing conversion" << endl;
    cout << endl;
    cout << "2. Для других способов инициализации (= и ()):" << endl;
    cout << "   - Компилятор может выдать ПРЕДУПРЕЖДЕНИЕ (warning), но не обязан." << endl;
    cout << "   - В Visual Studio это warning C4244: 'argument': conversion from 'double' to 'int', possible loss of data" << endl;
    cout << "   - В GCC это warning: conversion from 'double' to 'int' changes value" << endl;
    cout << endl;
    cout << "3. Строгие настройки компилятора:" << endl;
    cout << "   - С флагом /WX в MSVC (трактовать warnings как errors) или -Werror в GCC" << endl;
    cout << "     обычные предупреждения становятся ошибками." << endl;
    cout << "   - С флагами /permissive- или -pedantic-errors дополнительные проверки." << endl;
    cout << endl;

    cout << "=== ДОПОЛНИТЕЛЬНАЯ ИНФОРМАЦИЯ ===" << endl;
    cout << "--------------------------------------------------------------------------------" << endl;
    cout << "Почему double → int теряет данные?" << endl;
    cout << "  double хранит число с плавающей точкой (8 байт)." << endl;
    cout << "  int хранит целое число (4 байта)." << endl;
    cout << "  При преобразовании отбрасывается дробная часть, что приводит к потере точности." << endl;
    cout << endl;
    cout << "Что делать, если нужно преобразование с округлением?" << endl;
    cout << "  int rounded = static_cast<int>(std::round(doubleValue));" << endl;
    cout << "  int floor = static_cast<int>(std::floor(doubleValue));" << endl;
    cout << "  int ceil = static_cast<int>(std::ceil(doubleValue));" << endl;
    cout << endl;

    return 0;
}