#include <iostream>
#include <string>
#include <sstream>
#include <TGUI/TGUI.hpp>
#include "src/apple.hpp"
#include "src/snake.hpp"

enum class Condition {menu, single_player, multi_player, game_over};

bool main_menu(tgui::Gui& gui, Condition& condition, Obstacle& obstacle, sf::RenderWindow &win)
{
    try
    {
        tgui::Panel::Ptr main_menu = tgui::Panel::create();
        main_menu->setSize(win.getSize().x, win.getSize().y);
        main_menu->setBackgroundColor(sf::Color::Black);
        main_menu->setPosition(0, 0);
        gui.add(main_menu, "main menu");

        tgui::Button::Ptr single = tgui::Button::create();
        single->setSize(100, 100);
        single->setPosition(100, 100);
        single->setText("single_player");
        single->connect("pressed", [&]{
                                condition = Condition::single_player;
                                gui.get("main menu")->hide();
                            });
        main_menu->add(single);

        tgui::Button::Ptr multi = tgui::Button::create();
        multi->setSize(100, 100);
        multi->setPosition(100, 300);
        multi->setText("multi player");
        multi->connect("pressed", [&]{
                                condition = Condition::multi_player;
                                gui.get("main menu")->hide();
                            });
        main_menu->add(multi);
    }
    catch(const tgui::Exception& e)
    {
         std::cerr << "TGUI Exception: " << e.what() << std::endl;
         return false;
    }
    return true;
}

bool gameover_menu(tgui::Gui& gui, Condition& condition, Obstacle& obstacle, sf::RenderWindow &win)
{
    try
    {
        tgui::Panel::Ptr gameover = tgui::Panel::create();
        gameover->setSize(win.getSize().x, win.getSize().y);
        gameover->setBackgroundColor(sf::Color::Black);
        gameover->setPosition(0, 0);
        gui.add(gameover, "gameover menu");

        tgui::Button::Ptr return_to_menu = tgui::Button::create();
    }
    catch(const tgui::Exception& e)
    {
         std::cerr << "TGUI Exception: " << e.what() << std::endl;
         return false;
    }
    return true;
}

int main()
{
    sf::RenderWindow win{sf::VideoMode{600, 400}, "testing window"};

    Condition condition = Condition::menu;

    tgui::Gui gui{win};

    const int size = 5;
    int snake_length = 3;
    sf::Color blue = sf::Color::Blue;
    sf::Color red = sf::Color::Red;
    sf::Color generic = sf::Color::Green;
    sf::Time snake_speed = sf::milliseconds(100);
    Apple apple{win.getSize().x, win.getSize().y, size};
    apple.setColor(sf::Color::Red);

    Snake snake1{win.getSize().x - (size * 2), win.getSize().y, size * 2, snake_length, blue, generic, snake_speed};
    Snake snake2{0, win.getSize().y, size * 2, snake_length, red, generic, snake_speed};
    Obstacle obstacle{5, size * 2, win.getSize().x, win.getSize().y};
    sf::Clock clock;

    if (main_menu(gui, condition, obstacle, win) == false) return EXIT_FAILURE;

    while (win.isOpen())
    {
        sf::Event event;
        while (win.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) win.close();
            else if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Escape) win.close();
            }
            gui.handleEvent(event);
        }
        if (condition == Condition::menu)
        {
            win.clear();
            gui.draw();
            win.display();
        }
        else if (condition == Condition::multi_player)
        {
            snake1.action(sf::Keyboard::Up, sf::Keyboard::Down, sf::Keyboard::Left, sf::Keyboard::Right);
            snake2.action(sf::Keyboard::W, sf::Keyboard::S, sf::Keyboard::A, sf::Keyboard::D);
            sf::Time getElapsed = clock.restart();
            snake1.update(getElapsed);
            snake2.update(getElapsed);
            snake1.collision(apple, snake2, obstacle, true);
            snake2.collision(apple, snake1, obstacle, true);

            if (snake2.getCondition() == "lose")
            {
                std::cout << "snake blue win\n";
                snake1.reinit();
                snake2.reinit();
                obstacle.reinit(win.getSize().x, win.getSize().y);
            }
            else if (snake1.getCondition() == "lose")
            {
                std::cout << "snake red win\n";
                snake1.reinit();
                snake2.reinit();
                obstacle.reinit(win.getSize().x, win.getSize().y);
            }
            else if ((snake1.getCondition() == "draw") && (snake2.getCondition() == "draw"))
            {
                std::cout << "draw";
                snake1.reinit();
                snake2.reinit();
                obstacle.reinit(win.getSize().x, win.getSize().y);
            }
            win.clear();
            win.draw(apple.getShape());
            win.draw(snake1);
            win.draw(snake2);
            win.draw(obstacle);
            win.display();
        }
        else if (condition == Condition::single_player)
        {
            snake1.action(sf::Keyboard::Up, sf::Keyboard::Down, sf::Keyboard::Left, sf::Keyboard::Right);
            sf::Time getElapsed = clock.restart();
            snake1.update(getElapsed);
            snake1.collision(apple, snake2, obstacle, false);
            if (snake1.getCondition() == "lose")
            {
                std::cout << "you lost, loser";
                snake1.reinit();
                snake2.reinit();
                obstacle.reinit(win.getSize().x, win.getSize().y);
            }
            win.clear();
            win.draw(apple.getShape());
            win.draw(snake1);
            win.draw(obstacle);
            win.display();
        }
    }
}
