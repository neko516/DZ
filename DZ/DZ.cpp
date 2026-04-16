#include <iostream>
#include <future>
#include <chrono>
#include <thread>
#include <vector>
#include <atomic>
#include <iomanip>
#include <mutex>

using namespace std;
using namespace chrono;

// Структура для хранения информации о файле
struct FileInfo {
    int id;
    int downloadTime;
    int progress;
    bool completed;
    string name;

    FileInfo(int i, int time) : id(i), downloadTime(time), progress(0), completed(false) {
        name = "Файл_" + to_string(id) + ".dat";
    }
};

// Глобальные переменные для отслеживания прогресса
vector<FileInfo> files;
mutex progressMutex;

// Функция загрузки файла с обновлением прогресса
string downloadFileWithProgress(int fileNumber, int downloadTime) {
    for (int progress = 10; progress <= 100; progress += 10) {
        this_thread::sleep_for(milliseconds(downloadTime / 10));

        // Обновляем прогресс в общем списке
        {
            lock_guard<mutex> lock(progressMutex);
            for (auto& file : files) {
                if (file.id == fileNumber) {
                    file.progress = progress;
                    if (progress == 100) {
                        file.completed = true;
                    }
                    break;
                }
            }
        }
    }

    return "Файл " + to_string(fileNumber) + " (" + to_string(downloadTime / 100) + " MB)";
}

// Функция для отображения текущего прогресса
void displayProgress() {
    lock_guard<mutex> lock(progressMutex);
    cout << "\r";
    for (const auto& file : files) {
        if (file.completed) {
            cout << "✅ " << file.name << ": 100%   ";
        }
        else {
            cout << "📥 " << file.name << ": " << setw(3) << file.progress << "%   ";
        }
    }
    cout << flush;
}

int main() {
    setlocale(LC_ALL, "Russian");

    cout << "═══════════════════════════════════════════════════════════" << endl;
    cout << "           СИМУЛЯТОР ПАРАЛЛЕЛЬНОЙ ЗАГРУЗКИ ФАЙЛОВ          " << endl;
    cout << "═══════════════════════════════════════════════════════════" << endl;
    cout << endl;

    // Инициализация файлов со случайным временем загрузки
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(3000, 7000);

    files.emplace_back(1, dist(gen));
    files.emplace_back(2, dist(gen));
    files.emplace_back(3, dist(gen));

    cout << "📋 Информация о файлах:" << endl;
    for (const auto& file : files) {
        cout << "   " << file.name << " - " << file.downloadTime / 1000.0 << " сек." << endl;
    }
    cout << endl;

    cout << "🚀 Запуск асинхронной загрузки (std::async)..." << endl;
    cout << "💡 Основной поток НЕ ЗАБЛОКИРОВАН и может выполнять другие задачи" << endl;
    cout << endl;

    auto startTime = steady_clock::now();

    // Запускаем асинхронные задачи
    future<string> future1 = async(launch::async, downloadFileWithProgress, 1, files[0].downloadTime);
    future<string> future2 = async(launch::async, downloadFileWithProgress, 2, files[1].downloadTime);
    future<string> future3 = async(launch::async, downloadFileWithProgress, 3, files[2].downloadTime);

    // Основной поток: выводим прогресс каждые 0.5 секунды
    cout << "📊 Прогресс загрузки:" << endl;

    bool allCompleted = false;
    int counter = 0;

    while (!allCompleted) {
        // Проверяем статус всех задач
        bool done1 = future1.wait_for(milliseconds(0)) == future_status::ready;
        bool done2 = future2.wait_for(milliseconds(0)) == future_status::ready;
        bool done3 = future3.wait_for(milliseconds(0)) == future_status::ready;
        allCompleted = done1 && done2 && done3;

        // Обновляем отображение прогресса
        displayProgress();

        if (!allCompleted) {
            // Каждые 2 секунды выводим дополнительное сообщение о том, что поток не заблокирован
            if (counter % 4 == 0 && counter > 0) {
                cout << "\n💬 [Основной поток активен] Выполняем фоновые задачи..." << string(30, ' ') << endl;
                cout << "📊 Прогресс загрузки:" << endl;
            }
            this_thread::sleep_for(milliseconds(500));
            counter++;
        }
    }

    cout << "\n\n✅ ЗАГРУЗКА ЗАВЕРШЕНА!" << endl << endl;

    // Получаем результаты
    string result1 = future1.get();
    string result2 = future2.get();
    string result3 = future3.get();

    auto endTime = steady_clock::now();
    auto totalTime = duration_cast<milliseconds>(endTime - startTime);

    cout << "═══════════════════════════════════════════════════════════" << endl;
    cout << "📦 РЕЗУЛЬТАТЫ ЗАГРУЗКИ:" << endl;
    cout << "   " << result1 << endl;
    cout << "   " << result2 << endl;
    cout << "   " << result3 << endl;
    cout << endl;
    cout << "⏱️  ОБЩЕЕ ВРЕМЯ ЗАГРУЗКИ: " << fixed << setprecision(2)
        << totalTime.count() / 1000.0 << " секунд" << endl;

    // Статистика
    int maxTime = max({ files[0].downloadTime, files[1].downloadTime, files[2].downloadTime });
    cout << endl;
    cout << "📈 СТАТИСТИКА:" << endl;
    cout << "   Самый долгий файл: " << maxTime / 1000.0 << " сек." << endl;
    cout << "   Общее время загрузки (параллельно): " << totalTime.count() / 1000.0 << " сек." << endl;
    cout << "   Время при последовательной загрузке: " << (files[0].downloadTime + files[1].downloadTime + files[2].downloadTime) / 1000.0 << " сек." << endl;
    cout << "   ⚡ Ускорение: " << fixed << setprecision(2)
        << (files[0].downloadTime + files[1].downloadTime + files[2].downloadTime) / (double)maxTime << "x" << endl;

    cout << endl;
    cout << "═══════════════════════════════════════════════════════════" << endl;

    return 0;
}