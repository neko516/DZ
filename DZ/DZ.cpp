#include <iostream>
#include <string>
#include <random>
#include <stdexcept>
#include <limits>

using namespace std;

// Класс для исключения "нехватка денег"
class InsufficientFundsException : public exception {
private:
    string message;
public:
    InsufficientFundsException(double required, double given) {
        message = "Недостаточно средств! Требуется: " + to_string(required) +
            " руб. Внесено: " + to_string(given) + " руб.";
    }
    const char* what() const noexcept override {
        return message.c_str();
    }
};

// Класс для исключения "некорректный номер напитка"
class InvalidDrinkException : public exception {
public:
    const char* what() const noexcept override {
        return "Ошибка: Некорректный номер напитка! Пожалуйста, выберите напиток из списка.";
    }
};

// Класс для исключения "поломка автомата"
class MachineBrokenException : public exception {
public:
    const char* what() const noexcept override {
        return "КРИТИЧЕСКАЯ ОШИБКА: Автомат сломался! Обратитесь к администратору. Ваши деньги возвращены.";
    }
};

// Структура для хранения информации о напитке
struct Drink {
    string name;
    double price;
};

// Класс автомата с газировкой
class SodaMachine {
private:
    vector<Drink> drinks;
    double insertedMoney;
    random_device rd;
    mt19937 gen;
    uniform_int_distribution<> dist;

public:
    // Конструктор
    SodaMachine() : insertedMoney(0), gen(rd()), dist(1, 5) {
        // Инициализация напитков (минимум 3)
        drinks.push_back({ "Кока-Кола", 80.0 });
        drinks.push_back({ "Спрайт", 70.0 });
        drinks.push_back({ "Фанта", 75.0 });
        drinks.push_back({ "Пепси", 80.0 });
        drinks.push_back({ "Тархун", 65.0 });
    }

    // Метод для проверки поломки (шанс 1/5)
    bool isBroken() {
        return dist(gen) == 1; // 20% шанс поломки
    }

    // Метод для внесения денег
    void insertMoney(double money) {
        if (money < 0) {
            throw invalid_argument("Сумма денег не может быть отрицательной!");
        }
        insertedMoney = money;
    }

    // Метод для покупки напитка
    void buyDrink(int drinkNumber) {
        // Проверка корректности номера напитка
        if (drinkNumber < 1 || drinkNumber > drinks.size()) {
            throw InvalidDrinkException();
        }

        Drink& selectedDrink = drinks[drinkNumber - 1];

        // Проверка наличия достаточной суммы
        if (insertedMoney < selectedDrink.price) {
            throw InsufficientFundsException(selectedDrink.price, insertedMoney);
        }

        // Проверка поломки автомата (шанс 1/5)
        if (isBroken()) {
            throw MachineBrokenException();
        }

        // Успешная покупка
        double change = insertedMoney - selectedDrink.price;
        cout << "\n✅ Успех! Вы приобрели: " << selectedDrink.name << endl;
        cout << "💰 Стоимость: " << selectedDrink.price << " руб." << endl;
        cout << "🔄 Сдача: " << change << " руб." << endl;
        insertedMoney = 0;
    }

    // Метод для отображения меню
    void showMenu() const {
        cout << "\n========== МЕНЮ НАПИТКОВ ==========" << endl;
        for (size_t i = 0; i < drinks.size(); i++) {
            cout << i + 1 << ". " << drinks[i].name << " - " << drinks[i].price << " руб." << endl;
        }
        cout << "=====================================" << endl;
    }

    // Метод для получения внесенной суммы
    double getInsertedMoney() const {
        return insertedMoney;
    }

    // Метод для возврата денег
    void refund() {
        cout << "\n💸 Возврат денег: " << insertedMoney << " руб." << endl;
        insertedMoney = 0;
    }
};

// Функция для безопасного ввода числа
double safeInputDouble(const string& prompt) {
    double value;
    cout << prompt;
    cin >> value;

    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        throw invalid_argument("Ошибка: Введено некорректное значение! Требуется число.");
    }

    if (value < 0) {
        throw invalid_argument("Ошибка: Сумма не может быть отрицательной!");
    }

    return value;
}

// Функция для безопасного ввода целого числа
int safeInputInt(const string& prompt) {
    int value;
    cout << prompt;
    cin >> value;

    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        throw invalid_argument("Ошибка: Введено некорректное значение! Требуется целое число.");
    }

    return value;
}

int main() {
    setlocale(LC_ALL, "Russian");

    SodaMachine machine;
    bool continueShopping = true;

    cout << "=== ДОБРО ПОЖАЛОВАТЬ В АВТОМАТ С ГАЗИРОВКОЙ ===" << endl;
    cout << "Автомат может сломаться с вероятностью 20% при каждой покупке!" << endl;

    while (continueShopping) {
        machine.showMenu();

        double money = 0;
        int drinkChoice = 0;

        try {
            // Ввод суммы денег с обработкой ошибок
            money = safeInputDouble("\nВведите сумму денег (руб.): ");
            machine.insertMoney(money);
            cout << "💰 Внесено: " << machine.getInsertedMoney() << " руб." << endl;

            // Ввод номера напитка
            drinkChoice = safeInputInt("Выберите номер напитка: ");

            // Попытка покупки
            machine.buyDrink(drinkChoice);

        }
        catch (const InvalidDrinkException& e) {
            cout << "\n⚠️ " << e.what() << endl;
            machine.refund();
        }
        catch (const InsufficientFundsException& e) {
            cout << "\n⚠️ " << e.what() << endl;
            machine.refund();
        }
        catch (const MachineBrokenException& e) {
            cout << "\n🔧 " << e.what() << endl;
            machine.refund();
            cout << "Автомат требует ремонта. Работа программы завершена." << endl;
            break;
        }
        catch (const invalid_argument& e) {
            cout << "\n❌ " << e.what() << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Пожалуйста, попробуйте снова." << endl;
            continue;
        }
        catch (const exception& e) {
            cout << "\n⚠️ Неизвестная ошибка: " << e.what() << endl;
            machine.refund();
        }
        catch (...) {
            cout << "\n💥 КРИТИЧЕСКАЯ ОШИБКА! Непредвиденное исключение!" << endl;
            cout << "Программа будет завершена." << endl;
            break;
        }

        // Спрашиваем, хочет ли пользователь продолжить
        char choice;
        cout << "\nХотите продолжить покупки? (y/n): ";
        cin >> choice;
        if (choice != 'y' && choice != 'Y') {
            continueShopping = false;
            cout << "\nСпасибо за использование автомата! До свидания!" << endl;
        }
    }

    return 0;
}