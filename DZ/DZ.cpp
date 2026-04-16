#include <iostream>
#include <string>

using namespace std;

class BankAccount {
private:
    string ownerName;
    double balance;

public:
    // Конструктор
    BankAccount(string ownerName, double balance) {
        this->ownerName = ownerName;
        this->balance = balance;
    }

    // Внести сумму
    void deposit(double amount) {
        if (amount > 0) {
            this->balance += amount;
            cout << "Внесено: " << amount << " руб." << endl;
        }
        else {
            cout << "Сумма должна быть положительной!" << endl;
        }
    }

    // Снять сумму - возвращает ссылку на текущий объект
    BankAccount& withdraw(double amount) {
        if (amount > 0 && amount <= this->balance) {
            this->balance -= amount;
            cout << "Снято: " << amount << " руб." << endl;
        }
        else if (amount > this->balance) {
            cout << "Недостаточно средств! Доступно: " << this->balance << " руб." << endl;
        }
        else {
            cout << "Сумма должна быть положительной!" << endl;
        }
        return *this;
    }

    // Вывод информации о счете
    void displayInfo() const {
        cout << "Владелец счета: " << ownerName << endl;
        cout << "Текущий баланс: " << balance << " руб." << endl;
        cout << "------------------------" << endl;
    }

    // Метод сравнения счетов (основное задание)
    // Сравнивает текущий счет с другим счетом по балансу
    void compareBalance(const BankAccount& other) const {
        cout << "Сравнение счетов:" << endl;
        cout << "  " << this->ownerName << ": " << this->balance << " руб." << endl;
        cout << "  " << other.ownerName << ": " << other.balance << " руб." << endl;

        if (this->balance > other.balance) {
            cout << "Результат: У " << this->ownerName << " баланс больше на "
                << (this->balance - other.balance) << " руб." << endl;
        }
        else if (this->balance < other.balance) {
            cout << "Результат: У " << other.ownerName << " баланс больше на "
                << (other.balance - this->balance) << " руб." << endl;
        }
        else {
            cout << "Результат: Балансы равны!" << endl;
        }
        cout << "------------------------" << endl;
    }

    // Альтернативный вариант: метод, возвращающий результат сравнения
    bool hasLargerBalance(const BankAccount& other) const {
        return this->balance > other.balance;
    }
};

int main() {
    setlocale(LC_ALL, "Russian");

    // Создание счетов
    BankAccount account1("Иван Петров", 5000);
    BankAccount account2("Мария Сидорова", 3000);
    BankAccount account3("Алексей Иванов", 5000);

    cout << "=== ИНФОРМАЦИЯ О СЧЕТАХ ===" << endl;
    account1.displayInfo();
    account2.displayInfo();
    account3.displayInfo();

    // Демонстрация работы методов управления счетом
    cout << "=== ОПЕРАЦИИ СО СЧЕТАМИ ===" << endl;
    account1.deposit(1500);
    account1.displayInfo();

    account2.withdraw(1000).withdraw(500); // цепочка вызовов (благодаря возврату ссылки)
    account2.displayInfo();

    // Демонстрация метода сравнения счетов
    cout << "=== СРАВНЕНИЕ СЧЕТОВ ===" << endl;
    account1.compareBalance(account2);
    account2.compareBalance(account3);
    account1.compareBalance(account3);

    // Альтернативная демонстрация с возвратом bool
    cout << "=== АЛЬТЕРНАТИВНОЕ СРАВНЕНИЕ (bool) ===" << endl;
    if (account1.hasLargerBalance(account2)) {
        cout << account1 << " имеет больший баланс, чем " << account2 << endl;
    }
    else {
        cout << "У " << account1 << " баланс не больше, чем у " << account2 << endl;
    }

    return 0;
}