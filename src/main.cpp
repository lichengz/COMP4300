#include <SFML/Graphics.hpp>
#include <imgui-SFML.h>
#include <imgui.h>
#include <imgui_internal.h>
#include <iostream>

int main() {
    const int wWidth = 1280;
    const int wHeight = 720;
    sf::RenderWindow window(sf::VideoMode(wWidth, wHeight), "SFML ImGui");
    window.setFramerateLimit(60);

    ImGui::SFML::Init(window);
    sf::Clock deltaClock;

    ImGui::GetStyle().ScaleAllSizes(1.0f);

    float c[3] = {0.0f, 1.0f, 1.0f};

    float circleRadius = 50.0f;
    int circleSegments = 32;
    float circleSpeedX = 10.0f;
    float circleSpeedY = 5.0f;
    bool drawCircle = true;
    bool drawText = true;

    sf::CircleShape circle(circleRadius, circleSegments);
    circle.setPosition(circleRadius, circleRadius);

    sf::Font myFont;
    if(!myFont.loadFromFile("fonts/Arial.ttf")) {
        std::cerr << "Error loading font" << std::endl;
        exit(-1);
    }
    sf::Text text("Sample Text", myFont , 24);
    text.setPosition(0, wHeight - (float)text.getCharacterSize());

    char displayString[255] = "Hello World!";

    while(window.isOpen()) {
        sf::Event event;
        while(window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(window, event);

            if(event.type == sf::Event::Closed) {
                window.close();
            }

            if(event.type == sf::Event::KeyPressed) {
                std::cout << "Key Pressed: " << event.key.code << std::endl;
                if(event.key.code == sf::Keyboard::Escape) {
                    window.close();
                }

                if(event.key.code == sf::Keyboard::X) {
                    circleSpeedX *= -1.0f;
                }
            }
        }

        ImGui::SFML::Update(window, deltaClock.restart());

        ImGui::Begin("Window title");
        ImGui::Text("Hello, world!");
        ImGui::Checkbox("Draw Circle", &drawCircle);
        ImGui::SameLine();
        ImGui::Checkbox("Draw Text", &drawText);
        ImGui::SliderFloat("Circle Radius", &circleRadius, 10.0f, 100.0f);
        ImGui::SliderInt("Circle Segments", &circleSegments, 3, 100);
        ImGui::ColorEdit3("Color Circle", c);
        ImGui::InputText("Display Text", displayString, 255);
        if(ImGui::Button("Set Text")) {
            text.setString(displayString);
        }
        ImGui::SameLine();
        if(ImGui::Button("Reset Circle")) {
            circle.setPosition(0.0f, 0.0f);
        }
        ImGui::End();

        circle.setFillColor(sf::Color(c[0] * 255, c[1] * 255, c[2] * 255));
        circle.setPointCount(circleSegments);
        circle.setRadius(circleRadius);

        circle.setPosition(circle.getPosition().x + circleSpeedX, circle.getPosition().y + circleSpeedY);
        if(circle.getPosition().x + circleRadius > wWidth || circle.getPosition().x - circleRadius < 0) {
            circleSpeedX *= -1.0f;
        }
        if(circle.getPosition().y + circleRadius > wHeight || circle.getPosition().y - circleRadius < 0) {
            circleSpeedY *= -1.0f;
        }

        window.clear();
        if(drawCircle) {
            window.draw(circle);
        }
        if(drawText) {
            window.draw(text);
        }
        ImGui::SFML::Render(window);
        window.display();
    }

    return 0;
}
