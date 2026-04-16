#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <string>
#include <memory>
#include <algorithm>

using namespace std;

// Класс Creature (существо)
class Creature {
private:
    string name;
    set<string> genes;          // множество генов
    vector<Creature*> children; // вектор детей (указатели)

public:
    // Конструктор
    Creature(const string& n, const set<string>& g) : name(n), genes(g) {
        cout << "✅ Создано существо: " << name << " (генов: " << genes.size() << ")" << endl;
    }

    // Деструктор
    ~Creature() {
        cout << "❌ Уничтожено существо: " << name << endl;
    }

    // Функция добавления ребенка
    void addChild(Creature* child) {
        if (child != nullptr) {
            children.push_back(child);
            cout << "   👶 У " << name << " появился ребенок: " << child->getName() << endl;
        }
    }

    // Геттеры
    string getName() const { return name; }
    const set<string>& getGenes() const { return genes; }
    const vector<Creature*>& getChildren() const { return children; }

    // Вывод информации о существе
    void printInfo(int indent = 0) const {
        string indentStr(indent, ' ');
        cout << indentStr << "📌 " << name << endl;

        // Вывод генов
        cout << indentStr << "   🧬 Гены: ";
        if (genes.empty()) {
            cout << "нет";
        }
        else {
            int count = 0;
            for (const auto& gene : genes) {
                if (count++ > 0) cout << ", ";
                cout << gene;
            }
        }
        cout << endl;

        // Вывод детей
        if (!children.empty()) {
            cout << indentStr << "   👨‍👩‍👧 Дети (" << children.size() << "): ";
            for (size_t i = 0; i < children.size(); i++) {
                if (i > 0) cout << ", ";
                cout << children[i]->getName();
            }
            cout << endl;
        }
    }

    // Рекурсивный вывод всех потомков
    void printDescendants(int indent = 2) const {
        string indentStr(indent, ' ');
        for (Creature* child : children) {
            cout << indentStr << "├─ " << child->getName() << endl;
            child->printDescendants(indent + 2);
        }
    }

    // Получение всех потомков (рекурсивно)
    void getAllDescendants(vector<Creature*>& result) const {
        for (Creature* child : children) {
            result.push_back(child);
            child->getAllDescendants(result);
        }
    }

    // Проверка, является ли это существо предком другого
    bool isAncestorOf(const Creature* other) const {
        if (this == other) return true;
        for (Creature* child : children) {
            if (child->isAncestorOf(other)) return true;
        }
        return false;
    }
};

// Класс GenTree (генеалогическое дерево)
class GenTree {
private:
    map<string, Creature*> registry; // карта: id (имя) -> указатель на существо

public:
    // Конструктор
    GenTree() {
        cout << "\n🌳 СОЗДАНО ГЕНЕАЛОГИЧЕСКОЕ ДЕРЕВО" << endl;
        cout << "====================================" << endl;
    }

    // Деструктор
    ~GenTree() {
        cout << "\n💀 УНИЧТОЖЕНИЕ ГЕНЕАЛОГИЧЕСКОГО ДЕРЕВА" << endl;
        cout << "====================================" << endl;

        // Удаляем всех существ
        for (auto& pair : registry) {
            delete pair.second;
        }
        registry.clear();
        cout << "Все существа удалены" << endl;
    }

    // Метод добавления существа
    bool addCreature(const string& name, const set<string>& genes) {
        // Проверяем, нет ли уже существа с таким именем
        if (registry.find(name) != registry.end()) {
            cout << "⚠️ Ошибка: Существо с именем '" << name << "' уже существует!" << endl;
            return false;
        }

        // Создаем новое существо
        Creature* newCreature = new Creature(name, genes);
        registry[name] = newCreature;
        return true;
    }

    // Метод связывания родителя и ребенка
    bool linkParentChild(const string& parentName, const string& childName) {
        // Проверяем существование обоих существ
        auto parentIt = registry.find(parentName);
        auto childIt = registry.find(childName);

        if (parentIt == registry.end()) {
            cout << "⚠️ Ошибка: Родитель '" << parentName << "' не найден!" << endl;
            return false;
        }

        if (childIt == registry.end()) {
            cout << "⚠️ Ошибка: Ребенок '" << childName << "' не найден!" << endl;
            return false;
        }

        Creature* parent = parentIt->second;
        Creature* child = childIt->second;

        // Проверяем, не создаст ли это цикл
        if (child->isAncestorOf(parent)) {
            cout << "⚠️ Ошибка: Добавление этой связи создаст цикл в генеалогическом дереве!" << endl;
            return false;
        }

        // Добавляем ребенка родителю
        parent->addChild(child);
        return true;
    }

    // Поиск существа по имени
    Creature* findCreature(const string& name) {
        auto it = registry.find(name);
        if (it != registry.end()) {
            return it->second;
        }
        return nullptr;
    }

    // Поиск всех потомков предка
    vector<Creature*> findDescendants(const string& ancestorName) {
        vector<Creature*> descendants;
        Creature* ancestor = findCreature(ancestorName);

        if (ancestor == nullptr) {
            cout << "⚠️ Предок '" << ancestorName << "' не найден!" << endl;
            return descendants;
        }

        ancestor->getAllDescendants(descendants);
        return descendants;
    }

    // Вывод всех потомков предка
    void printDescendantsOf(const string& ancestorName) {
        cout << "\n🔍 ПОИСК ПОТОМКОВ: " << ancestorName << endl;
        cout << "----------------------------------------" << endl;

        Creature* ancestor = findCreature(ancestorName);
        if (ancestor == nullptr) {
            cout << "❌ Предок не найден!" << endl;
            return;
        }

        cout << "📊 " << ancestor->getName() << ":" << endl;
        ancestor->printDescendants();

        vector<Creature*> descendants = findDescendants(ancestorName);
        cout << "\n📈 Всего потомков: " << descendants.size() << endl;
    }

    // Вывод всей информации о генеалогическом дереве
    void printGenTreeInfo() const {
        cout << "\n🌳 ГЕНЕАЛОГИЧЕСКОЕ ДЕРЕВО ПИТОМЦЕВ" << endl;
        cout << "====================================" << endl;
        cout << "Всего существ в базе: " << registry.size() << endl;
        cout << "------------------------------------" << endl;

        // Находим корневых существ (тех, у кого нет родителей)
        // Для этого нужно определить, кто является чьим-то ребенком
        set<Creature*> hasParent;
        for (const auto& pair : registry) {
            for (Creature* child : pair.second->getChildren()) {
                hasParent.insert(child);
            }
        }

        // Выводим корневых существ и их потомков
        bool hasRoot = false;
        for (const auto& pair : registry) {
            if (hasParent.find(pair.second) == hasParent.end()) {
                if (!hasRoot) {
                    cout << "\n👑 ГЛАВНЫЕ ПРЕДКИ (корневые существа):" << endl;
                    hasRoot = true;
                }
                cout << "\n";
                pair.second->printInfo();
                if (!pair.second->getChildren().empty()) {
                    cout << "   👇 Потомки:" << endl;
                    pair.second->printDescendants(4);
                }
            }
        }

        // Выводим существ, у которых есть родители (не корневые)
        cout << "\n📋 ВСЕ СУЩЕСТВА ПО АЛФАВИТУ:" << endl;
        cout << "------------------------------------" << endl;
        for (const auto& pair : registry) {
            pair.second->printInfo();
            cout << endl;
        }
    }

    // Статистика по генам
    void printGeneStats() const {
        cout << "\n🧬 СТАТИСТИКА ГЕНОВ" << endl;
        cout << "------------------------------------" << endl;

        map<string, int> geneFrequency;
        for (const auto& pair : registry) {
            for (const auto& gene : pair.second->getGenes()) {
                geneFrequency[gene]++;
            }
        }

        cout << "Частота встречаемости генов:" << endl;
        for (const auto& pair : geneFrequency) {
            cout << "   " << pair.first << ": " << pair.second << " существ(а)" << endl;
        }
    }
};

int main() {
    setlocale(LC_ALL, "Russian");

    // Создаем генеалогическое дерево
    GenTree familyTree;

    // Демонстрация 1: Добавление существ
    cout << "\n📝 ДОБАВЛЕНИЕ ПИТОМЦЕВ" << endl;
    cout << "------------------------------------" << endl;

    // Собачки
    familyTree.addCreature("Рекс", { "шерсть", "хвост", "лай", "охранник" });
    familyTree.addCreature("Белка", { "шерсть", "хвост", "лай", "быстрая" });
    familyTree.addCreature("Шарик", { "шерсть", "хвост", "лай", "игривый" });
    familyTree.addCreature("Дружок", { "шерсть", "хвост", "лай", "смелый" });
    familyTree.addCreature("Тузик", { "шерсть", "хвост", "лай", "маленький" });

    // Кошечки
    familyTree.addCreature("Мурка", { "шерсть", "хвост", "мяуканье", "охотник" });
    familyTree.addCreature("Барсик", { "шерсть", "хвост", "мяуканье", "полосатый" });
    familyTree.addCreature("Снежок", { "шерсть", "хвост", "мяуканье", "белый" });

    // Попугаи
    familyTree.addCreature("Кеша", { "перья", "клюв", "говорун", "умный" });
    familyTree.addCreature("Гоша", { "перья", "клюв", "говорун", "веселый" });

    // Хомяки
    familyTree.addCreature("Хома", { "шерсть", "грызун", "ночной", "пухлый" });

    cout << "\n🔗 УСТАНОВКА РОДИТЕЛЬСКИХ СВЯЗЕЙ" << endl;
    cout << "------------------------------------" << endl;

    // Собачья семья
    familyTree.linkParentChild("Рекс", "Шарик");
    familyTree.linkParentChild("Рекс", "Дружок");
    familyTree.linkParentChild("Белка", "Шарик");
    familyTree.linkParentChild("Белка", "Дружок");
    familyTree.linkParentChild("Шарик", "Тузик");

    // Кошачья семья
    familyTree.linkParentChild("Мурка", "Барсик");
    familyTree.linkParentChild("Мурка", "Снежок");

    // Попугаи
    familyTree.linkParentChild("Кеша", "Гоша");

    // Межвидовые связи (приемыши)
    familyTree.linkParentChild("Мурка", "Кеша"); // Кошка воспитала попугая :)

    // Попробуем создать цикл (должно быть отклонено)
    cout << "\n🧪 ТЕСТ ЗАЩИТЫ ОТ ЦИКЛОВ:" << endl;
    cout << "------------------------------------" << endl;
    familyTree.linkParentChild("Тузик", "Рекс"); // Попытка сделать прадедушку внуком

    // Демонстрация поиска потомков
    cout << "\n🔍 ПОИСК ПОТОМКОВ" << endl;
    cout << "====================================" << endl;

    familyTree.printDescendantsOf("Рекс");
    familyTree.printDescendantsOf("Мурка");
    familyTree.printDescendantsOf("Кеша");
    familyTree.printDescendantsOf("Снежок"); // Бездетный

    // Вывод всей информации о дереве
    familyTree.printGenTreeInfo();

    // Статистика по генам
    familyTree.printGeneStats();

    // Дополнительная демонстрация: работа с отдельными существами
    cout << "\n🎯 ИНДИВИДУАЛЬНАЯ ИНФОРМАЦИЯ О СУЩЕСТВЕ" << endl;
    cout << "====================================" << endl;

    Creature* rex = familyTree.findCreature("Рекс");
    if (rex) {
        cout << "\nИнформация о Рексе:" << endl;
        rex->printInfo();

        vector<Creature*> descendants = familyTree.findDescendants("Рекс");
        cout << "\nПрямые потомки Рекса: ";
        for (Creature* desc : descendants) {
            cout << desc->getName() << " ";
        }
        cout << "(" << descendants.size() << ")" << endl;
    }

    // Поиск несуществующего существа
    cout << "\n🔍 ПОИСК НЕСУЩЕСТВУЮЩЕГО СУЩЕСТВА:" << endl;
    cout << "------------------------------------" << endl;
    Creature* unknown = familyTree.findCreature("Васька");
    if (unknown == nullptr) {
        cout << "❌ Существо 'Васька' не найдено в генеалогическом дереве" << endl;
    }

    cout << "\n✅ ПРОГРАММА ЗАВЕРШЕНА" << endl;
    cout << "====================================" << endl;

    return 0;
}