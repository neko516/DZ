#include <iostream>
#include <vector>
#include <memory>
#include <string>

using namespace std;

// Базовый абстрактный класс для всех устройств
class SmartDevice {
public:
    virtual ~SmartDevice() = default;
    virtual void TurnOn() = 0;
    virtual void TurnOff() = 0;
    virtual string getDeviceName() const = 0;
};

// Класс Light (свет)
class Light : public SmartDevice {
private:
    string location;
    int brightness;

public:
    Light(const string& loc = "Комната") : location(loc), brightness(0) {}

    void TurnOn() override {
        brightness = 100;
        cout << "💡 " << location << ": Свет включен. Яркость: " << brightness << "%" << endl;
    }

    void TurnOff() override {
        brightness = 0;
        cout << "💡 " << location << ": Свет выключен" << endl;
    }

    string getDeviceName() const override {
        return "Свет в " + location;
    }
};

// Класс Thermostat (термостат)
class Thermostat : public SmartDevice {
private:
    int temperature;
    string mode;

public:
    Thermostat() : temperature(20), mode("OFF") {}

    void TurnOn() override {
        temperature = 22;
        mode = "HEATING";
        cout << "🌡️ Термостат: Включен. Температура установлена на " << temperature << "°C. Режим: " << mode << endl;
    }

    void TurnOff() override {
        temperature = 15;
        mode = "OFF";
        cout << "🌡️ Термостат: Выключен. Температура: " << temperature << "°C. Режим: " << mode << endl;
    }

    string getDeviceName() const override {
        return "Термостат";
    }
};

// Класс Radio (радио)
class Radio : public SmartDevice {
private:
    double frequency;
    string station;
    int volume;

public:
    Radio() : frequency(98.7), station("Europe Plus"), volume(0) {}

    void TurnOn() override {
        volume = 30;
        cout << "📻 Радио: Включено. Станция: " << station << " (" << frequency << " FM). Громкость: " << volume << "%" << endl;
    }

    void TurnOff() override {
        volume = 0;
        cout << "📻 Радио: Выключено" << endl;
    }

    string getDeviceName() const override {
        return "Радио";
    }
};

// Класс SmartHome (умный дом) - класс-контейнер
class SmartHome {
private:
    vector<unique_ptr<SmartDevice>> devices;
    bool nightMode;

public:
    SmartHome() : nightMode(false) {
        cout << "🏠 Система 'Умный дом' инициализирована" << endl;
        cout << "========================================" << endl;
    }

    // Добавление устройства в дом
    void addDevice(unique_ptr<SmartDevice> device) {
        cout << "➕ Добавлено устройство: " << device->getDeviceName() << endl;
        devices.push_back(move(device));
    }

    // Включение ночного режима
    void EnableNightMode() {
        if (nightMode) {
            cout << "🌙 Ночной режим уже активен!" << endl;
            return;
        }

        nightMode = true;
        cout << "\n🌙 ВКЛЮЧЕНИЕ НОЧНОГО РЕЖИМА" << endl;
        cout << "----------------------------------------" << endl;

        for (auto& device : devices) {
            device->TurnOn();
        }

        cout << "----------------------------------------" << endl;
        cout << "✅ Ночной режим активирован" << endl << endl;
    }

    // Выключение ночного режима
    void DisableNightMode() {
        if (!nightMode) {
            cout << "☀️ Ночной режим уже выключен!" << endl;
            return;
        }

        nightMode = false;
        cout << "\n☀️ ВЫКЛЮЧЕНИЕ НОЧНОГО РЕЖИМА" << endl;
        cout << "----------------------------------------" << endl;

        for (auto& device : devices) {
            device->TurnOff();
        }

        cout << "----------------------------------------" << endl;
        cout << "✅ Ночной режим деактивирован" << endl << endl;
    }

    // Показать статус всех устройств (дополнительный метод для демонстрации)
    void ShowStatus() {
        cout << "\n📊 ТЕКУЩИЙ СТАТУС УСТРОЙСТВ:" << endl;
        cout << "----------------------------------------" << endl;
        cout << "Режим: " << (nightMode ? "🌙 Ночной" : "☀️ Дневной") << endl;
        cout << "Количество устройств: " << devices.size() << endl;
        cout << "----------------------------------------" << endl;
    }

    // Получить статус ночного режима
    bool isNightMode() const {
        return nightMode;
    }
};

int main() {
    setlocale(LC_ALL, "Russian");

    cout << "========================================" << endl;
    cout << "      СИСТЕМА 'УМНЫЙ ДОМ' v1.0" << endl;
    cout << "========================================" << endl << endl;

    // Создаем умный дом
    SmartHome myHome;

    // Добавляем устройства
    cout << "\n📦 УСТАНОВКА УСТРОЙСТВ:" << endl;
    cout << "----------------------------------------" << endl;

    myHome.addDevice(make_unique<Light>("Гостиная"));
    myHome.addDevice(make_unique<Light>("Спальня"));
    myHome.addDevice(make_unique<Light>("Кухня"));
    myHome.addDevice(make_unique<Thermostat>());
    myHome.addDevice(make_unique<Radio>());

    cout << "----------------------------------------" << endl;
    cout << "✅ Все устройства установлены" << endl << endl;

    // Демонстрация работы
    cout << "========================================" << endl;
    cout << "        ДЕМОНСТРАЦИЯ РАБОТЫ" << endl;
    cout << "========================================" << endl;

    // Показываем начальный статус
    myHome.ShowStatus();

    // Включаем ночной режим
    cout << "\n🎬 ДЕЙСТВИЕ: Включение ночного режима" << endl;
    myHome.EnableNightMode();

    // Небольшая пауза (имитация работы)
    cout << "💤 Ночь прошла спокойно..." << endl << endl;

    // Выключаем ночной режим
    cout << "🎬 ДЕЙСТВИЕ: Выключение ночного режима" << endl;
    myHome.DisableNightMode();

    // Показываем финальный статус
    myHome.ShowStatus();

    // Дополнительная демонстрация: повторное включение/выключение
    cout << "\n🔄 ДОПОЛНИТЕЛЬНЫЕ ТЕСТЫ:" << endl;
    cout << "========================================" << endl;

    cout << "\n▶ Попытка включить ночной режим повторно:" << endl;
    myHome.EnableNightMode();

    cout << "\n▶ Попытка выключить ночной режим повторно:" << endl;
    myHome.DisableNightMode();

    cout << "\n========================================" << endl;
    cout << "      ПРОГРАММА ЗАВЕРШЕНА" << endl;
    cout << "========================================" << endl;

    return 0;
}