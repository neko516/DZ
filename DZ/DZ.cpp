#include <iostream>
#include <memory>
#include <vector>

using namespace std;

// Базовый класс Person
class Person {
public:
    virtual ~Person() {
        cout << "🗑️ Уничтожен объект Person" << endl;
    }

    virtual void CheckPassport() const {
        cout << "📋 Проверка паспортных данных (базовый класс)" << endl;
    }
};

// Класс-наследник: мигрант из Бангладеша
class BangladeshMigrant : public Person {
public:
    ~BangladeshMigrant() override {
        cout << "🗑️ Уничтожен мигрант из Бангладеша" << endl;
    }

    void CheckPassport() const override {
        cout << "❌ ПАСПОРТНЫЕ ДАННЫЕ НЕ ВЕРНЫ! Документы отсутствуют или просрочены." << endl;
        cout << "   ⚠️ Мигрант из Бангладеша: паспорт недействителен!" << endl;
    }

    void Run() const {
        cout << "🏃‍♂️💨 МИГРАНТ ПЫТАЕТСЯ УБЕЖАТЬ! Задержите нарушителя!" << endl;
    }
};

// Класс-наследник: коренной москвич
class NativeMuscovite : public Person {
public:
    ~NativeMuscovite() override {
        cout << "🗑️ Уничтожен коренной москвич" << endl;
    }

    void CheckPassport() const override {
        cout << "✅ ПАСПОРТНЫЕ ДАННЫЕ ВЕРНЫ! Гражданин РФ, Москва." << endl;
        cout << "   📍 Коренной москвич: все документы в порядке." << endl;
    }
};

// Дополнительный класс для демонстрации - турист (для расширения примера)
class Tourist : public Person {
private:
    string country;

public:
    Tourist(const string& c) : country(c) {}

    ~Tourist() override {
        cout << "🗑️ Уничтожен турист из " << country << endl;
    }

    void CheckPassport() const override {
        cout << "🛂 ПАСПОРТНЫЕ ДАННЫЕ НА ПРОВЕРКЕ... Турист из " << country << endl;
        cout << "   ✅ Виза действительна, паспорт в порядке." << endl;
    }

    void ShowVisa() const {
        cout << "   📄 Виза туриста из " << country << " действительна до 31.12.2025" << endl;
    }
};

int main() {
    setlocale(LC_ALL, "Russian");

    cout << "================================================" << endl;
    cout << "       ПАСПОРТНЫЙ КОНТРОЛЬ В АЭРОПОРТУ" << endl;
    cout << "================================================" << endl;
    cout << "Добро пожаловать в зону паспортного контроля!" << endl;
    cout << endl;

    // Создаем массив из уникальных указателей на Person
    vector<unique_ptr<Person>> people;

    // Добавляем объекты классов-наследников
    people.push_back(make_unique<BangladeshMigrant>());
    people.push_back(make_unique<NativeMuscovite>());
    people.push_back(make_unique<BangladeshMigrant>());
    people.push_back(make_unique<NativeMuscovite>());
    people.push_back(make_unique<BangladeshMigrant>());

    // Добавляем туриста для дополнительной демонстрации
    people.push_back(make_unique<Tourist>("Италия"));
    people.push_back(make_unique<Tourist>("Япония"));

    cout << "👥 Всего людей в очереди: " << people.size() << endl;
    cout << "================================================" << endl;
    cout << endl;

    // Проходим по очереди паспортного контроля
    int counter = 1;
    for (const auto& person : people) {
        cout << "🔹 ПАССАЖИР #" << counter++ << ":" << endl;
        cout << "----------------------------------------" << endl;

        // Вызываем функцию CheckPassport (полиморфизм)
        person->CheckPassport();

        // С помощью dynamic_cast определяем, является ли объект мигрантом из Бангладеша
        BangladeshMigrant* migrant = dynamic_cast<BangladeshMigrant*>(person.get());

        if (migrant) {
            // Если это мигрант, вызываем функцию Run()
            cout << "🔴 ВНИМАНИЕ: Обнаружен нелегальный мигрант!" << endl;
            migrant->Run();
        }
        else {
            // Проверяем, может быть это турист (дополнительная демонстрация)
            Tourist* tourist = dynamic_cast<Tourist*>(person.get());
            if (tourist) {
                cout << "🟢 Турист проходит дополнительную проверку:" << endl;
                tourist->ShowVisa();
            }
            else {
                cout << "🟢 Пассажир успешно прошел паспортный контроль." << endl;
            }
        }

        cout << "----------------------------------------" << endl;
        cout << endl;
    }

    // Дополнительная демонстрация: статистика
    cout << "================================================" << endl;
    cout << "           СТАТИСТИКА ПРОВЕРКИ" << endl;
    cout << "================================================" << endl;

    int migrantCount = 0;
    int nativeCount = 0;
    int touristCount = 0;

    for (const auto& person : people) {
        if (dynamic_cast<BangladeshMigrant*>(person.get())) {
            migrantCount++;
        }
        else if (dynamic_cast<NativeMuscovite*>(person.get())) {
            nativeCount++;
        }
        else if (dynamic_cast<Tourist*>(person.get())) {
            touristCount++;
        }
    }

    cout << "📊 Результаты паспортного контроля:" << endl;
    cout << "   • Мигрантов из Бангладеша: " << migrantCount << endl;
    cout << "   • Коренных москвичей: " << nativeCount << endl;
    cout << "   • Туристов: " << touristCount << endl;
    cout << "   • Всего проверено: " << people.size() << endl;

    // Демонстрация работы с raw pointer (альтернативный способ)
    cout << "\n================================================" << endl;
    cout << "     ДОПОЛНИТЕЛЬНАЯ ДЕМОНСТРАЦИЯ" << endl;
    cout << "================================================" << endl;
    cout << "Проверка отдельного пассажира (raw pointer):" << endl;
    cout << "----------------------------------------" << endl;

    Person* rawPerson = new BangladeshMigrant();
    rawPerson->CheckPassport();

    BangladeshMigrant* rawMigrant = dynamic_cast<BangladeshMigrant*>(rawPerson);
    if (rawMigrant) {
        rawMigrant->Run();
    }

    delete rawPerson;

    cout << "\n================================================" << endl;
    cout << "              КОНЕЦ ПРОВЕРКИ" << endl;
    cout << "================================================" << endl;
    cout << "Паспортный контроль завершен. Спасибо за внимание!" << endl;

    // Умные указатели автоматически удалят все объекты
    return 0;
}