#include <iostream>

using namespace std;

//(работает)
class Wallet {
private:
    unsigned int money;

public:
    // Конструктор без explicit - позволяет неявное преобразование int -> Wallet
    Wallet(unsigned int amount) {
        money = amount;
        cout << "Создан кошелек с деньгами: " << money << " руб." << endl;
    }

    unsigned int getMoney() const {
        return money;
    }
};

// Функция оплаты
void pay(Wallet wallet) {
    cout << "Оплата прошла успешно! Сумма: " << wallet.getMoney() << " руб." << endl;
}

// ============================================
// Раскомментируйте эту часть, чтобы проверить explicit
// ============================================
/*
class Wallet {
private:
    unsigned int money;

public:
    // explicit запрещает неявное преобразование
    explicit Wallet(unsigned int amount) {
        money = amount;
        cout << "Создан кошелек с деньгами: " << money << " руб." << endl;
    }

    unsigned int getMoney() const {
        return money;
    }
};

void pay(Wallet wallet) {
    cout << "Оплата прошла успешно! Сумма: " << wallet.getMoney() << " руб." << endl;
}
*/
// ============================================

int main() {
    setlocale(LC_ALL, "Russian");

    cout << "=== ВЕРСИЯ БЕЗ explicit ===" << endl;
    cout << "Вызов pay(400):" << endl;
    pay(400);  // 400 неявно преобразуется в Wallet(400)

    cout << "\nВызов с явным созданием объекта:" << endl;
    Wallet myWallet(1000);
    pay(myWallet);

    cout << "\n========================================" << endl;
    cout << "ОПИСАНИЕ ОШИБКИ ПРИ explicit:" << endl;
    cout << "========================================" << endl;
    cout << "При добавлении explicit к конструктору:" << endl;
    cout << "explicit Wallet(unsigned int amount)" << endl;
    cout << endl;
    cout << "Ошибка Visual Studio будет выглядеть так:" << endl;
    cout << "\"error C2664: 'void pay(Wallet)': cannot convert argument 1 from 'int' to 'Wallet'\"" << endl;
    cout << endl;
    cout << "Текст ошибки:" << endl;
    cout << "------------------------" << endl;
    cout << "E0415   не существует подходящей функции для преобразования \"int\" в \"Wallet\"" << endl;
    cout << "C2664   'void pay(Wallet)': невозможно преобразовать аргумент 1 из 'int' в 'Wallet'" << endl;
    cout << "------------------------" << endl;
    cout << endl;
    cout << "Почему возникает ошибка:" << endl;
    cout << "1. Конструктор помечен как explicit, что запрещает неявные преобразования." << endl;
    cout << "2. Функция pay() ожидает объект типа Wallet, но получает int (400)." << endl;
    cout << "3. Компилятор не может автоматически создать Wallet из int." << endl;
    cout << "4. Нужно явно вызвать конструктор: pay(Wallet(400))" << endl;

    return 0;
}