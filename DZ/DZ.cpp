#include <iostream>
#include <regex>
#include <string>
#include <vector>

int main() {
    setlocale(LC_ALL, "Ru");

    std::string text = "В недрах тундры выдры в гетрах тырят в вёдра ядра кедров "
        "Вызрав с выдры в тундре гетры, вытру выдрой ядра кедра, "
        "вытру гетрой выдре морду — выдру в тундру, ядра в вёдра.";

    // Регулярное выражение для поиска слов, содержащих "вид"
    // \b - граница слова, [а-яА-ЯёЁ]* - буквы до и после "вид"
    std::regex pattern(R"(\b[а-яА-ЯёЁ]*вид[а-яА-ЯёЁ]*\b)");

    std::smatch match;
    std::string::const_iterator searchStart(text.cbegin());

    std::cout << "Слова, содержащие подстроку \"вид\":\n";
    std::cout << "----------------------------------------\n";

    bool found = false;
    while (std::regex_search(searchStart, text.cend(), match, pattern)) {
        std::cout << match[0] << std::endl;
        searchStart = match[0].second;
        found = true;
    }

    if (!found) {
        std::cout << "Слова не найдены.\n";
    }

    std::cout << "----------------------------------------\n";

    return 0;
}