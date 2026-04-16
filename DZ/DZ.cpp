#include <iostream>
#include <iomanip>

using namespace std;

class Time {
private:
    int hours;
    int minutes;

    // Вспомогательный метод для нормализации времени (приведение минут к часам)
    void normalize() {
        if (minutes >= 60) {
            hours += minutes / 60;
            minutes %= 60;
        }
        else if (minutes < 0) {
            // На случай отрицательных минут (необязательно для данной задачи)
            int extraHours = minutes / 60;
            hours += extraHours;
            minutes %= 60;
            if (minutes < 0) {
                minutes += 60;
                hours--;
            }
        }

        // Часы могут быть любыми (не ограничиваем 24, т.к. не сказано в задании)
        // При желании можно добавить hours %= 24 для 24-часового формата
    }

public:
    // Конструкторы
    Time() : hours(0), minutes(0) {}

    Time(int h, int m) : hours(h), minutes(m) {
        normalize();
    }

    // Геттеры
    int getHours() const { return hours; }
    int getMinutes() const { return minutes; }

    // Перегрузка оператора '+'
    Time operator+(const Time& other) const {
        Time result;
        result.hours = this->hours + other.hours;
        result.minutes = this->minutes + other.minutes;
        result.normalize();
        return result;
    }

    // Перегрузка оператора '=='
    bool operator==(const Time& other) const {
        // Приводим оба времени к общему знаменателю (минутам от начала)
        // Или просто сравниваем часы и минуты
        return (this->hours == other.hours) && (this->minutes == other.minutes);
    }

    // Дружественная функция для перегрузки оператора '<<'
    friend ostream& operator<<(ostream& os, const Time& t);
};

// Перегрузка оператора вывода '<<'
ostream& operator<<(ostream& os, const Time& t) {
    // Выводим часы и минуты с ведущими нулями (формат ЧЧ:ММ)
    os << setw(2) << setfill('0') << t.hours << ":"
        << setw(2) << setfill('0') << t.minutes;
    return os;
}

int main() {
    setlocale(LC_ALL, "Russian");

    cout << "=== ДЕМОНСТРАЦИЯ РАБОТЫ КЛАССА Time ===" << endl;
    cout << endl;

    // Создание объектов времени
    Time t1(2, 45);      // 2 часа 45 минут
    Time t2(1, 30);      // 1 час 30 минут
    Time t3(3, 45);      // 3 часа 45 минут
    Time t4(2, 45);      // 2 часа 45 минут (такое же как t1)

    // Вывод времени с помощью оператора '<<'
    cout << "Время t1: " << t1 << endl;
    cout << "Время t2: " << t2 << endl;
    cout << "Время t3: " << t3 << endl;
    cout << "Время t4: " << t4 << endl;
    cout << endl;

    // Демонстрация оператора '+'
    cout << "=== ОПЕРАТОР '+' ===" << endl;
    Time sum1 = t1 + t2;
    cout << t1 << " + " << t2 << " = " << sum1 << endl;

    Time sum2 = t2 + t3;
    cout << t2 << " + " << t3 << " = " << sum2 << endl;

    // Проверка преобразования минут в часы
    Time t5(0, 45);      // 0 часов 45 минут
    Time t6(0, 35);      // 0 часов 35 минут
    Time sum3 = t5 + t6;
    cout << t5 << " + " << t6 << " = " << sum3 << " (проверка: 45+35=80 минут = 1 час 20 минут)" << endl;

    Time t7(5, 50);      // 5 часов 50 минут
    Time t8(0, 30);      // 0 часов 30 минут
    Time sum4 = t7 + t8;
    cout << t7 << " + " << t8 << " = " << sum4 << " (проверка: 5:50 + 30 минут = 6:20)" << endl;
    cout << endl;

    // Демонстрация оператора '=='
    cout << "=== ОПЕРАТОР '==' ===" << endl;
    cout << t1 << " == " << t2 << " ? " << (t1 == t2 ? "Да" : "Нет") << endl;
    cout << t1 << " == " << t3 << " ? " << (t1 == t3 ? "Да" : "Нет") << endl;
    cout << t1 << " == " << t4 << " ? " << (t1 == t4 ? "Да" : "Нет") << endl;
    cout << t2 << " == " << t3 << " ? " << (t2 == t3 ? "Да" : "Нет") << endl;
    cout << endl;

    // Дополнительные тесты
    cout << "=== ДОПОЛНИТЕЛЬНЫЕ ТЕСТЫ ===" << endl;

    // Сложение трех объектов
    Time t9(0, 50);
    Time t10(0, 40);
    Time t11(0, 30);
    Time sum5 = t9 + t10 + t11;
    cout << t9 << " + " << t10 << " + " << t11 << " = " << sum5
        << " (50+40+30=120 минут = 2 часа)" << endl;

    // Сложение с большим количеством часов
    Time t12(23, 50);
    Time t13(1, 20);
    Time sum6 = t12 + t13;
    cout << t12 << " + " << t13 << " = " << sum6 << " (24 часа 70 минут = 25 часов 10 минут)" << endl;

    // Проверка на граничных значениях
    Time t14(0, 59);
    Time t15(0, 1);
    Time sum7 = t14 + t15;
    cout << t14 << " + " << t15 << " = " << sum7 << " (59+1=60 минут = 1 час)" << endl;

    return 0;
}