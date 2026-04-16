#include <SFML/Graphics.hpp>

int main()
{
    // Создаём окно
    sf::RenderWindow window(sf::VideoMode(300, 500), "Traffic Light");
    window.setFramerateLimit(60);

    // Цвета для кругов (обычные и яркие)
    sf::Color redNormal(150, 0, 0);
    sf::Color redBright(255, 0, 0);

    sf::Color yellowNormal(150, 150, 0);
    sf::Color yellowBright(255, 255, 0);

    sf::Color greenNormal(0, 150, 0);
    sf::Color greenBright(0, 255, 0);

    // Корпус светофора
    sf::RectangleShape body(sf::Vector2f(120.f, 300.f));
    body.setFillColor(sf::Color(50, 50, 50));
    body.setOutlineThickness(3.f);
    body.setOutlineColor(sf::Color::Black);
    body.setPosition(90.f, 100.f);

    // Круги
    float radius = 35.f;
    sf::CircleShape redLight(radius);
    sf::CircleShape yellowLight(radius);
    sf::CircleShape greenLight(radius);

    redLight.setPosition(110.f, 115.f);
    yellowLight.setPosition(110.f, 200.f);
    greenLight.setPosition(110.f, 285.f);

    // Начальные цвета
    redLight.setFillColor(redBright);   // Начинаем с красного (яркий)
    yellowLight.setFillColor(yellowNormal);
    greenLight.setFillColor(greenNormal);

    int activeLight = 0; // 0 - красный, 1 - жёлтый, 2 - зелёный

    // Главный цикл
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            // Нажатие пробела
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
            {
                // Сначала делаем все цвета тусклыми
                redLight.setFillColor(redNormal);
                yellowLight.setFillColor(yellowNormal);
                greenLight.setFillColor(greenNormal);

                // Переключаем активный цвет
                activeLight = (activeLight + 1) % 3;

                // Делаем активный цвет ярким
                switch (activeLight)
                {
                case 0:
                    redLight.setFillColor(redBright);
                    break;
                case 1:
                    yellowLight.setFillColor(yellowBright);
                    break;
                case 2:
                    greenLight.setFillColor(greenBright);
                    break;
                }
            }
        }

        // Отрисовка
        window.clear(sf::Color(200, 200, 200)); // Серый фон
        window.draw(body);
        window.draw(redLight);
        window.draw(yellowLight);
        window.draw(greenLight);
        window.display();
    }

    return 0;
}
