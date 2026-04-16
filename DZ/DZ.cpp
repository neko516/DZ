#include <iostream>
#include <string>

using namespace std;

// Предварительное объявление класса BankAccount (для дружественного класса)
class BankAccount;

// Класс менеджера банка (дружественный класс)
class BankManager {
public:
    // Метод системы быстрых платежей
    // Принимает ссылки на два счета и сумму перевода
    static void FastPaymentSystem(BankAccount& fromAccount, BankAccount& toAccount, double amount) {
        // Проверка на положительную сумму
        if (amount <= 0) {
            cout << "❌ Ошибка: Сумма перевода должна быть положительной!" << endl;
            return;
        }

        // Проверка достаточности средств
        if (fromAccount.balance < amount) {
            cout << "❌ Ошибка: Недостаточно средств на счете отправителя!" << endl;
            cout << "   Баланс отправителя: " << fromAccount.balance << " руб." << endl;
            cout << "   Требуется: " << amount << " руб." << endl;
            return;
        }

        // Выполняем перевод
        fromAccount.balance -= amount;
        toAccount.balance += amount;

        cout << "✅ Перевод выполнен успешно!" << endl;
        cout << "   Сумма перевода: " << amount << " руб." << endl;
        cout << "   Отправитель: " << fromAccount.ownerName << endl;
        cout << "   Получатель: " << toAccount.ownerName << endl;
    }

    // Дополнительный метод для проверки баланса (через дружественный доступ)
    static void ShowBalance(const BankAccount& account);
};

// Класс банковского счета
class BankAccount {
private:
    string ownerName;   // владелец счета
    double balance;     // баланс счета

public:
    // Конструктор для инициализации счета
    BankAccount(const string& name, double initialBalance)
        : ownerName(name), balance(initialBalance) {
        cout << "🏦 Создан банковский счет!" << endl;
        cout << "   Владелец: " << ownerName << endl;
        cout << "   Начальный баланс: " << balance << " руб." << endl;
        cout << "----------------------------------------" << endl;
    }

    // Метод для отображения информации о счете
    void DisplayInfo() const {
        cout << "📋 Информация о счете:" << endl;
        cout << "   Владелец: " << ownerName << endl;
        cout << "   Баланс: " << balance << " руб." << endl;
    }

    // Геттер для баланса (для безопасного доступа извне)
    double GetBalance() const {
        return balance;
    }

    // Геттер для имени владельца
    string GetOwnerName() const {
        return ownerName;
    }

    // Объявляем BankManager дружественным классом
    // Это позволяет BankManager получать доступ к приватным полям BankAccount
    friend class BankManager;
};

// Реализация метода ShowBalance (после определения класса BankAccount)
void BankManager::ShowBalance(const BankAccount& account) {
    cout << "💰 Баланс счета " << account.ownerName << ": " << account.balance << " руб." << endl;
}

// Дополнительный класс для демонстрации (еще один способ)
// Можно также сделать дружественную функцию
class BankInspector {
public:
    // Дружественная функция может получить доступ к приватным полям
    static void InspectAccount(const BankAccount& account) {
        // Обычный класс не имеет доступа к приватным полям BankAccount
        // Но если объявить эту функцию дружественной, то будет доступ
        // cout << account.balance; // Ошибка! Нет доступа
        cout << "🔍 Инспекция счета (через публичный интерфейс):" << endl;
        cout << "   Владелец: " << account.GetOwnerName() << endl;
        cout << "   Баланс: " << account.GetBalance() << " руб." << endl;
    }
};

int main() {
    setlocale(LC_ALL, "Russian");

    cout << "================================================" << endl;
    cout << "       СИСТЕМА БЫСТРЫХ ПЛАТЕЖЕЙ v1.0" << endl;
    cout << "================================================" << endl;
    cout << endl;

    // Создаем два банковских счета
    cout << "🏦 ОТКРЫТИЕ СЧЕТОВ:" << endl;
    cout << "================================================" << endl;

    BankAccount account1("Иван Петров", 50000.0);
    BankAccount account2("Мария Сидорова", 30000.0);

    cout << endl;

    // Выводим информацию о счетах до перевода
    cout << "📊 СОСТОЯНИЕ СЧЕТОВ ДО ПЕРЕВОДА:" << endl;
    cout << "================================================" << endl;
    account1.DisplayInfo();
    account2.DisplayInfo();

    cout << endl;

    // Используем класс менеджера банка для перевода средств
    cout << "💸 ВЫПОЛНЕНИЕ ПЕРЕВОДОВ:" << endl;
    cout << "================================================" << endl;

    // Перевод 10000 рублей с первого счета на второй
    cout << "\n1️⃣ Перевод 10000 руб. со счета Ивана на счет Марии:" << endl;
    cout << "----------------------------------------" << endl;
    BankManager::FastPaymentSystem(account1, account2, 10000);

    cout << "\n2️⃣ Перевод 5000 руб. со счета Марии на счет Ивана:" << endl;
    cout << "----------------------------------------" << endl;
    BankManager::FastPaymentSystem(account2, account1, 5000);

    cout << "\n3️⃣ Попытка перевода 100000 руб. (недостаточно средств):" << endl;
    cout << "----------------------------------------" << endl;
    BankManager::FastPaymentSystem(account1, account2, 100000);

    cout << "\n4️⃣ Попытка перевода отрицательной суммы:" << endl;
    cout << "----------------------------------------" << endl;
    BankManager::FastPaymentSystem(account1, account2, -500);

    cout << endl;

    // Выводим информацию о счетах после переводов
    cout << "📊 СОСТОЯНИЕ СЧЕТОВ ПОСЛЕ ПЕРЕВОДОВ:" << endl;
    cout << "================================================" << endl;
    account1.DisplayInfo();
    account2.DisplayInfo();

    cout << endl;

    // Демонстрация работы дружественного класса
    cout << "🔧 ДОПОЛНИТЕЛЬНАЯ ДЕМОНСТРАЦИЯ:" << endl;
    cout << "================================================" << endl;
    cout << "\nИспользование метода ShowBalance из BankManager:" << endl;
    BankManager::ShowBalance(account1);
    BankManager::ShowBalance(account2);

    cout << "\n================================================" << endl;
    cout << "              ПРОГРАММА ЗАВЕРШЕНА" << endl;
    cout << "================================================" << endl;

    return 0;
}