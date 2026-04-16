#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Класс Дерево
class Tree {
private:
    int branchCount;
    string species;

public:
    // Конструктор
    Tree(int branches, const string& type) : branchCount(branches), species(type) {
        cout << "🌳 СОЗДАНО дерево: " << species
            << " с " << branchCount << " ветками (адрес: " << this << ")" << endl;
    }

    // Деструктор
    ~Tree() {
        cout << "❌ УНИЧТОЖЕНО дерево: " << species
            << " (адрес: " << this << ")" << endl;
    }

    // Метод для вывода информации о дереве
    void displayInfo() const {
        cout << "Дерево: " << species << ", веток: " << branchCount;
    }

    // Геттеры
    int getBranchCount() const { return branchCount; }
    string getSpecies() const { return species; }
};

// Класс Лес (контейнер для деревьев)
class Forest {
private:
    // Агрегация: храним указатели на деревья (не владеем ими)
    vector<Tree*> trees;

public:
    // Конструктор
    Forest() {
        cout << "🏞️ СОЗДАН лес (адрес: " << this << ")" << endl;
    }

    // Деструктор
    ~Forest() {
        cout << "🔥 УНИЧТОЖЕН лес (адрес: " << this << ")" << endl;
        cout << "   Лес уничтожен, но деревья продолжают существовать!" << endl;
        // НЕ удаляем деревья! Они существуют отдельно от леса
    }

    // Метод добавления дерева в лес (получает указатель извне)
    void addTree(Tree* tree) {
        if (tree != nullptr) {
            trees.push_back(tree);
            cout << "   ➕ Дерево добавлено в лес: ";
            tree->displayInfo();
            cout << endl;
        }
    }

    // Метод вывода всех деревьев в лесу
    void displayForest() const {
        if (trees.empty()) {
            cout << "   Лес пуст" << endl;
            return;
        }

        cout << "   В лесу " << trees.size() << " деревьев:" << endl;
        for (size_t i = 0; i < trees.size(); i++) {
            cout << "      " << i + 1 << ". ";
            trees[i]->displayInfo();
            cout << endl;
        }
    }

    // Получить количество деревьев
    size_t getTreeCount() const { return trees.size(); }
};

// Дополнительный класс для демонстрации композиции (для сравнения)
class ComposedForest {
private:
    // Композиция: храним объекты по значению (владеем ими)
    vector<Tree> ownedTrees;

public:
    ComposedForest() {
        cout << "🏞️ СОЗДАН лес с композицией (адрес: " << this << ")" << endl;
    }

    ~ComposedForest() {
        cout << "🔥 УНИЧТОЖЕН лес с композицией (адрес: " << this << ")" << endl;
        // Деревья будут уничтожены автоматически вместе с лесом!
        cout << "   ⚠️ ДЕРЕВЬЯ УНИЧТОЖЕНЫ вместе с лесом!" << endl;
    }

    void addTree(const Tree& tree) {
        ownedTrees.push_back(tree);
        cout << "   ➕ Дерево добавлено в лес (композиция)" << endl;
    }
};

int main() {
    setlocale(LC_ALL, "Russian");

    cout << "================================================" << endl;
    cout << "    ДЕМОНСТРАЦИЯ АГРЕГАЦИИ VS КОМПОЗИЦИИ" << endl;
    cout << "================================================" << endl << endl;

    // ===== ЧАСТЬ 1: АГРЕГАЦИЯ (лес хранит указатели) =====
    cout << "🔹 ЧАСТЬ 1: АГРЕГАЦИЯ (лес хранит УКАЗАТЕЛИ)" << endl;
    cout << "------------------------------------------------" << endl;

    // Создаем деревья вне леса
    cout << "\n1. Создаем деревья ВНЕ леса:" << endl;
    Tree* oak = new Tree(150, "Дуб");
    Tree* pine = new Tree(80, "Сосна");
    Tree* birch = new Tree(120, "Береза");

    cout << "\n2. Создаем лес:" << endl;
    Forest* myForest = new Forest();

    cout << "\n3. Добавляем деревья в лес:" << endl;
    myForest->addTree(oak);
    myForest->addTree(pine);
    myForest->addTree(birch);

    cout << "\n4. Выводим содержимое леса:" << endl;
    myForest->displayForest();

    cout << "\n5. Удаляем лес:" << endl;
    delete myForest;

    cout << "\n6. Проверяем, существуют ли деревья после удаления леса:" << endl;
    cout << "   Дуб (адрес: " << oak << "): ";
    oak->displayInfo();
    cout << endl;
    cout << "   Сосна (адрес: " << pine << "): ";
    pine->displayInfo();
    cout << endl;
    cout << "   Береза (адрес: " << birch << "): ";
    birch->displayInfo();
    cout << endl;

    cout << "\n7. Очищаем деревья вручную:" << endl;
    delete oak;
    delete pine;
    delete birch;

    // ===== ЧАСТЬ 2: КОМПОЗИЦИЯ (для сравнения) =====
    cout << "\n\n🔸 ЧАСТЬ 2: КОМПОЗИЦИЯ (лес хранит объекты ПО ЗНАЧЕНИЮ)" << endl;
    cout << "--------------------------------------------------------" << endl;

    {
        cout << "\n1. Создаем лес с композицией:" << endl;
        ComposedForest composedForest;

        cout << "\n2. Создаем и добавляем деревья:" << endl;
        Tree apple(50, "Яблоня");
        Tree cherry(40, "Вишня");

        composedForest.addTree(apple);
        composedForest.addTree(cherry);

        cout << "\n3. Выход из области видимости - лес будет уничтожен" << endl;
    } // Здесь composedForest уничтожается, а вместе с ним и деревья

    cout << "\n   (Деревья Яблоня и Вишня уничтожены вместе с лесом)" << endl;

    // ===== ЧАСТЬ 3: ДОПОЛНИТЕЛЬНАЯ ДЕМОНСТРАЦИЯ =====
    cout << "\n\n🔹 ЧАСТЬ 3: ДОПОЛНИТЕЛЬНАЯ ДЕМОНСТРАЦИЯ" << endl;
    cout << "------------------------------------------------" << endl;

    cout << "\nСоздаем новый лес и добавляем деревья:" << endl;
    Forest* anotherForest = new Forest();

    Tree* maple = new Tree(90, "Клен");
    Tree* ash = new Tree(70, "Ясень");

    anotherForest->addTree(maple);
    anotherForest->addTree(ash);

    cout << "\nСодержимое леса:" << endl;
    anotherForest->displayForest();

    cout << "\nУдаляем лес:" << endl;
    delete anotherForest;

    cout << "\nДеревья всё ещё существуют:" << endl;
    cout << "   ";
    maple->displayInfo();
    cout << endl;
    cout << "   ";
    ash->displayInfo();
    cout << endl;

    cout << "\nОчищаем деревья:" << endl;
    delete maple;
    delete ash;

    // ===== ОТВЕТЫ НА ВОПРОСЫ =====
    cout << "\n\n================================================" << endl;
    cout << "    ОТВЕТЫ НА ВОПРОСЫ" << endl;
    cout << "================================================" << endl;

    cout << "\nВОПРОС: Объяснить продолжительность жизни объектов" << endl;
    cout << "в классе-контейнере при композиции и агрегации." << endl;
    cout << "Учитывать ситуации по значению и указатели." << endl;
    cout << "\n================================================" << endl;

    cout << "\n📚 КОМПОЗИЦИЯ (COMPOSITION) - 'часть-целое', сильная связь:" << endl;
    cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << endl;
    cout << "• Объекты хранятся ПО ЗНАЧЕНИЮ (как поля или в векторе<объектов>)" << endl;
    cout << "• Контейнер ВЛАДЕЕТ объектами" << endl;
    cout << "• Время жизни объектов = время жизни контейнера" << endl;
    cout << "• При создании контейнера создаются и объекты" << endl;
    cout << "• При уничтожении контейнера уничтожаются и объекты" << endl;
    cout << "• Объекты не могут существовать без контейнера" << endl;
    cout << "• Пример: класс House и класс Room (комнаты не существуют без дома)" << endl;
    cout << endl;
    cout << "  Пример кода:" << endl;
    cout << "  class House {" << endl;
    cout << "      Room rooms[5];  // композиция - по значению" << endl;
    cout << "  };" << endl;
    cout << "  // При удалении House, удаляются и Room" << endl;

    cout << "\n📎 АГРЕГАЦИЯ (AGGREGATION) - 'целое и часть', слабая связь:" << endl;
    cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << endl;
    cout << "• Объекты хранятся по УКАЗАТЕЛЯМ (или ссылкам)" << endl;
    cout << "• Контейнер НЕ ВЛАДЕЕТ объектами" << endl;
    cout << "• Объекты создаются ВНЕ контейнера" << endl;
    cout << "• Время жизни объектов НЕ ЗАВИСИТ от контейнера" << endl;
    cout << "• При уничтожении контейнера объекты продолжают существовать" << endl;
    cout << "• Контейнер только использует объекты, но не управляет их памятью" << endl;
    cout << "• Пример: класс University и класс Student (студенты существуют без вуза)" << endl;
    cout << endl;
    cout << "  Пример кода:" << endl;
    cout << "  class University {" << endl;
    cout << "      vector<Student*> students;  // агрегация - указатели" << endl;
    cout << "  };" << endl;
    cout << "  // При удалении University, Student продолжают существовать" << endl;

    cout << "\n📊 СРАВНИТЕЛЬНАЯ ТАБЛИЦА:" << endl;
    cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << endl;
    cout << "Характеристика          | Композиция     | Агрегация" << endl;
    cout << "────────────────────────┼────────────────┼────────────────" << endl;
    cout << "Способ хранения         | По значению    | По указателю/ссылке" << endl;
    cout << "Владеет ли контейнер?   | Да             | Нет" << endl;
    cout << "Время жизни объектов    | Как у контейнера| Независимое" << endl;
    cout << "Объекты могут существовать без контейнера? | Нет | Да" << endl;
    cout << "Ответственность за память| Контейнер     | Внешний код" << endl;
    cout << "Удаление контейнера     | Удаляет объекты| НЕ удаляет объекты" << endl;

    cout << "\n⚠️ ВАЖНЫЕ МОМЕНТЫ:" << endl;
    cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << endl;
    cout << "1. При композиции (по значению):" << endl;
    cout << "   - Объекты создаются автоматически в конструкторе" << endl;
    cout << "   - Деструктор контейнера автоматически вызывает деструкторы объектов" << endl;
    cout << "   - Нельзя случайно 'потерять' объекты или вызвать утечку памяти" << endl;
    cout << endl;
    cout << "2. При агрегации (по указателям):" << endl;
    cout << "   - Нужно вручную управлять памятью (new/delete)" << endl;
    cout << "   - Может возникнуть проблема 'висячих указателей' (dangling pointers)" << endl;
    cout << "   - Контейнер не должен удалять объекты в своем деструкторе" << endl;
    cout << "   - Объекты могут принадлежать нескольким контейнерам одновременно" << endl;
    cout << endl;
    cout << "3. Современные подходы:" << endl;
    cout << "   - Для композиции: хранить объекты по значению" << endl;
    cout << "   - Для агрегации: использовать shared_ptr для автоматического управления" << endl;
    cout << "   - Для наблюдения: использовать weak_ptr (если нужно избежать циклических ссылок)" << endl;

    cout << "\n✅ ВЫВОД из программы:" << endl;
    cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << endl;
    cout << "• В демонстрации выше лес хранил указатели на деревья (АГРЕГАЦИЯ)" << endl;
    cout << "• После удаления леса деревья продолжили существовать" << endl;
    cout << "• Деревья были удалены только после явного вызова delete" << endl;
    cout << "• При композиции деревья были бы удалены автоматически" << endl;

    return 0;
}