#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include <chrono>
#include <iomanip>
#include <sstream>
#include "weekly.h"
#include "txtEditor.h"

using namespace std;

//THINGS TO CHANGE/Fix:
//1.SPRITE PNGS AND SIZES REFORMATTING
//2.NEEDS A CURSOR TO SHOW WHERE USER IS TYPING (Might be something with font)
//4.NEEDS TO OPEN NEW WINDOW WHEN W IS PRESSED ON SCREEN
//5.FIGURE OUT A WAY TO STRUCTURE IT TO SEE A WEEKLY VIEW WITH ALL DAILY TO DO LISTS
//so currently it is only on a daily basis i would like to just make it so you
//can see the week and itll be empty ofc

//TRY PUTTING THE TEXT SPRITE VECTOR CREATOR INTO TEXT EDITOR TO CLEAN MORE CODE
int main() {
    //Startup reads to do list
    ifstream todo;
    todo.open("resources/todo.txt");
    vector<string> thingsToDo;

    float screenWidth = 1600;
    float screenHeight = 1200;
    //pink 255, 192, 203
    //blue 204, 225, 242
    sf::Color background(204, 225, 242);

    //Sprites and such
    sf::Texture toDo;
    toDo.loadFromFile("resources/addToDo.png");
    sf::Sprite toDoButton(toDo);
    toDoButton.setPosition((screenWidth/ 3) - 400, (screenHeight / 2) + 300);
    auto toDoLoc = toDoButton.getGlobalBounds();

    sf::Font font;
    font.loadFromFile("resources/fontToUse.ttf");

    sf::Text name("Add a To Do ",font,100);
    name.setStyle(sf::Text::Bold);
    name.setFillColor(sf::Color::Black);
    name.setPosition((screenWidth/ 3) - 300,(screenHeight / 2) + 250);
    auto nameLoc = name.getGlobalBounds();

    sf::Texture deleterTex;
    deleterTex.loadFromFile("resources/delete.png");
    sf::Sprite deleter(deleterTex);
    deleter.setPosition(0,0);

    //Text for D/W/M
    sf::Text daily("D",font,70);
    sf::Text weekly("W",font,70);
    sf::Text monthly("M",font,70);
    daily.setStyle(sf::Text::Bold);
    weekly.setStyle(sf::Text::Bold);
    monthly.setStyle(sf::Text::Bold);
    daily.setPosition((screenWidth / 3) - 450, screenHeight / 8 - 100);
    weekly.setPosition((screenWidth / 3) - 300, screenHeight / 8 - 100);
    monthly.setPosition((screenWidth / 3) - 150, screenHeight / 8 - 100);
    daily.setFillColor(sf::Color::Black);
    weekly.setFillColor(sf::Color::Black);
    monthly.setFillColor(sf::Color::Black);
    auto dLoc = daily.getGlobalBounds();
    auto wLoc = weekly.getGlobalBounds();
    auto mLoc = monthly.getGlobalBounds();

    sf::Text clock("",font,100);
    clock.setPosition(screenWidth/2 - 185,screenHeight / 8 - 150);
    clock.setFillColor(sf::Color::Black);
    clock.setStyle(sf::Text::Bold | sf::Text::Underlined | sf::Text:: Italic);
    //VARIABLES THAT ARE NEEDED IN WHILE LOOP AND DEFAULTS
    bool typeMode = false;
    string playerInput = "";
    bool firstClick = true;
    sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight), "SFML Window");
    vector<sf::Text> toDoStrings;
    int mouseX = 0;
    int mouseY = 0;
    string mode = "d";
    int iToDelete = 0;
    txtEditor textManager;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            auto deleterLoc = deleter.getGlobalBounds();
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    mouseX = event.mouseButton.x;
                    mouseY = event.mouseButton.y;
                    cout << mouseX << " " << mouseY << "\n";

                    //long if else if chain checks where the user clicked
                    if (firstClick and nameLoc.contains(mouseX,mouseY)) {
                        name.setString("");
                        window.draw(name);
                        firstClick = false;
                        typeMode = true;
                    }else if (toDoLoc.contains(mouseX,mouseY)){
                        if (playerInput.empty()){
                            cout << "input is empty" << "\n";
                        }
                        else{
                            textManager.addTex(playerInput);
                        }
                    } else if (dLoc.contains(mouseX,mouseY)){
                        mode = "d";
                    }
                    else if (wLoc.contains(mouseX,mouseY)){
                        mode = "w";
                    }
                    else if (mLoc.contains(mouseX,mouseY)){
                        mode = "m";
                    }else if (deleterLoc.contains(mouseX,mouseY)){
                        iToDelete = mouseY - 100;
                        iToDelete /= 100;
                    }
                }
            }
            if (typeMode) {
                if (event.type == sf::Event::TextEntered) {
                    playerInput = name.getString();
                    if ((isalpha(event.text.unicode))) {
                        playerInput += event.text.unicode;
                    }
                    name.setString(playerInput);
                    if (sf::Keyboard::isKeyPressed((sf::Keyboard::BackSpace))) {
                        if (playerInput == "") {
                        } else {
                            string temp = playerInput;
                            temp.pop_back();
                            playerInput = temp;
                            name.setString(playerInput);
                        }
                    }
                    if (sf::Keyboard::isKeyPressed((sf::Keyboard::Enter))) {
                        if (!playerInput.empty()){
                            textManager.addTex(playerInput);
                        }
                    }
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                        playerInput += " ";
                        name.setString(playerInput);
                    }
                }
            }
        }
        int i = 1;
        thingsToDo = textManager.getVector();
        for (int j = 0; j < thingsToDo.size(); j++){
            sf::Text temp(thingsToDo[j],font,50);
            temp.setFillColor(sf::Color::Black);
            temp.setPosition(screenWidth / 3 - 300,((screenHeight / 10) + (i * 100)));
            toDoStrings.push_back(temp);
            i++;
        }

        window.clear(background);


        if (iToDelete > 0){
            textManager.removeTex(iToDelete);
            toDoStrings.erase(toDoStrings.begin() + iToDelete - 1);
            iToDelete = 0;
        }

        for (auto element : toDoStrings){
            auto elementLoc = element.getGlobalBounds();
            if (elementLoc.contains(mouseX,mouseY)){
                element.setFillColor(sf::Color::White);
                element.setStyle(sf::Text::Bold | sf::Text::Underlined);
                deleter.setPosition(element.getPosition().x - 100,element.getPosition().y);
                window.draw(deleter);
            }
            window.draw(element);
        }
        toDoStrings.clear();
        //THIS COULD USE OPTIMIZATION
        if (mode == "w"){
            weekly.setFillColor(sf::Color::White);
            monthly.setFillColor(sf::Color::Black);
            daily.setFillColor(sf::Color::Black);

        }else if (mode == "m"){
            monthly.setFillColor(sf::Color::White);
            weekly.setFillColor(sf::Color::Black);
            daily.setFillColor(sf::Color::Black);
        }else {
            daily.setFillColor(sf::Color::White);
            weekly.setFillColor(sf::Color::Black);
            monthly.setFillColor(sf::Color::Black);
        }

        window.draw(daily);
        window.draw(weekly);
        window.draw(monthly);

        window.draw(toDoButton);
        window.draw(name);

        //THIS DRAWS THE CLOCK
        auto now = chrono::system_clock::now();
        time_t current_time = chrono::system_clock::to_time_t(now);
        tm* local_time = std::localtime(&current_time);
        stringstream time_ss;
        time_ss << put_time(local_time, "%H:%M:%S");
        string time_str = time_ss.str();
        clock.setString(time_str);
        window.draw(clock);

        window.display();





    }
    todo.close();
    return 0;
}