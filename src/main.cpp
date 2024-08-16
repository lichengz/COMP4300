#include <fstream>
#include <SFML/Graphics.hpp>
#include <imgui-SFML.h>
#include <imgui.h>
#include <imgui_internal.h>
#include <iostream>
#include <memory>

enum class ShapeType {
    CIRCLE,
    RECTANGLE,
    TRIANGLE
};

class ShapeProperties {
public:
    virtual ~ShapeProperties() = default;

    ShapeType type = ShapeType::CIRCLE;
    std::string name = "Shape";
    float initPosX = 0.0f;
    float initPosY = 0.0f;
    float speedX = 0.0f;
    float speedY = 0.0f;
    float color[3] = {1.0f, 1.0f, 1.0f};
    float scale = 1.0f;
    bool isDrawn = false;

    ShapeProperties() = default;
    ShapeProperties(ShapeType type, const std::string& name, bool isDrawn, float scale, float speedX, float speedY, const float* color)
        : type(type), name(name), isDrawn(isDrawn), scale(scale), speedX(speedX), speedY(speedY), color{color[0], color[1], color[2]} {}

    virtual float get_boundary() const {
        return 0.0f;
    }
};

class CircleProperties : public ShapeProperties {
public:
    float radius = 50.0f;
    int segments = 32;
    float get_boundary() const override{
        return radius;
    }
};

class RectangleProperties : public ShapeProperties {
public:
    float width = 100.0f;
    float height = 50.0f;
    float get_boundary() const override{
        return std::max(width / 2, height / 2);
    }
};

class GameSettings {
public:
    int windowWidth = 1280;
    int windowHeight = 720;
    std::string fontPath = "fonts/Arial.ttf";
    int fontSize = 24;
    sf::Color fontColor = sf::Color::White;
    std::vector<std::shared_ptr<ShapeProperties>> shapes;
    std::map<std::shared_ptr<sf::Shape>, std::shared_ptr<ShapeProperties>> sf_shapes_properties_map;
};

void readConfigFile(GameSettings& settings) {
    // Read config file
    std::ifstream configFile("bin/config.txt");
    int r = 255;
    int g = 255;
    int b = 255;
    if(configFile.is_open()) {
        std::string word;
        while(configFile >> word) {
            std::cout << word << std::endl;
            if(word == "Window") {
                configFile >> settings.windowWidth >> settings.windowHeight;
            }else if(word == "Font") {
                configFile >> settings.fontPath >> settings.fontSize >> r >> g >> b;
                settings.fontColor = sf::Color(r, g, b);
            }else if(word == "Circle") {
                auto circle = std::make_shared<CircleProperties>();
                configFile >> circle->name >> circle->initPosX >> circle->initPosY >> circle->speedX >> circle->speedY;
                configFile >> r >> g >> b;
                circle->color[0] = float(r) / 255.0f;
                circle->color[1] = float(g) / 255.0f;
                circle->color[2] = float(b) / 255.0f;
                configFile >> circle->radius;
                circle->type = ShapeType::CIRCLE;
                circle->isDrawn = true;
                settings.shapes.push_back(circle);
            }else if(word == "Rectangle") {
                auto rectangle = std::make_shared<RectangleProperties>();
                configFile >> rectangle->name >> rectangle->initPosX >> rectangle->initPosY >> rectangle->speedX >> rectangle->speedY;
                configFile >> r >> g >> b;
                rectangle->color[0] = float(r) / 255.0f;
                rectangle->color[1] = float(g) / 255.0f;
                rectangle->color[2] = float(b) / 255.0f;
                configFile >> rectangle->width >> rectangle->height;
                rectangle->type = ShapeType::RECTANGLE;
                rectangle->isDrawn = true;
                settings.shapes.push_back(rectangle);
            }
        }
        configFile.close();
    } else {
        std::cerr << "Error opening config file" << std::endl;
    }
}

void init_shapes(GameSettings& settings) {
    for(const auto& shape : settings.shapes) {
        if(shape->isDrawn) {
            switch(shape->type) {
                case ShapeType::CIRCLE: {
                    auto circle_ptr = std::static_pointer_cast<CircleProperties>(shape);
                    sf::CircleShape circle_shape(circle_ptr->radius);
                    circle_shape.setFillColor(sf::Color(circle_ptr->color[0] * 255.0f, circle_ptr->color[1] * 255.0f, circle_ptr->color[2] * 255.0f));
                    circle_shape.setPosition(circle_ptr->initPosX, circle_ptr->initPosY);
                    circle_shape.setOrigin(circle_ptr->radius, circle_ptr->radius);
                    settings.sf_shapes_properties_map[std::make_shared<sf::CircleShape>(circle_shape)] = circle_ptr;
                    break;
                }
                case ShapeType::RECTANGLE: {
                    auto rectangle_ptr = std::static_pointer_cast<RectangleProperties>(shape);
                    sf::RectangleShape rectangle_shape(sf::Vector2f(rectangle_ptr->width, rectangle_ptr->height));
                    rectangle_shape.setFillColor(sf::Color(rectangle_ptr->color[0] * 255.0f, rectangle_ptr->color[1] * 255.0f, rectangle_ptr->color[2] * 255.0f));
                    rectangle_shape.setPosition(rectangle_ptr->initPosX, rectangle_ptr->initPosY);
                    rectangle_shape.setOrigin(rectangle_ptr->width / 2.0f, rectangle_ptr->height / 2.0f);
                    settings.sf_shapes_properties_map[std::make_shared<sf::RectangleShape>(rectangle_shape)] = rectangle_ptr;
                    break;
                }
                default: break;
            }
        }
    }
}

void InitImGui(GameSettings& settings, sf::RenderWindow& window, const sf::Time& deltaTime) {
    ImGui::SFML::Update(window, deltaTime);

    ImGui::Begin("Shape Properties");
    std::vector<std::string> shape_items;
    for(const auto& shape : settings.shapes) {
        shape_items.push_back(shape->name);
    }
    static int item_current_idx = 0; // Here we store our selection data as an index.
    const std::string combo_preview_value = shape_items[item_current_idx];  // Pass in the preview value visible before opening the combo (it could be anything)
    if (ImGui::BeginCombo("Shape", combo_preview_value.c_str()))
    {
        for (int n = 0; n < shape_items.size(); n++)
        {
            const bool is_selected = (item_current_idx == n);
            if (ImGui::Selectable(shape_items[n].c_str(), is_selected))
                item_current_idx = n;

            // Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
            if (is_selected)
                ImGui::SetItemDefaultFocus();
        }
        ImGui::EndCombo();
    }
    auto& selected_shape = settings.shapes[item_current_idx];
    ImGui::Checkbox("Draw Shape", &selected_shape->isDrawn);
    ImGui::SliderFloat("Scale", &selected_shape->scale, 0.1, 2.0f);
    ImGui::ColorEdit3("Color", selected_shape->color);
    // ImGui::InputText("Display Text", displayString, 255);
    // if(ImGui::Button("Set Text")) {
    //     text.setString(displayString);
    // }
    // ImGui::SameLine();
    // if(ImGui::Button("Reset Circle")) {
    //     circle.setPosition(0.0f, 0.0f);
    // }

    ImGui::End();
}

int main() {
    GameSettings settings;
    readConfigFile(settings);
    init_shapes(settings);

    sf::RenderWindow window(sf::VideoMode(settings.windowWidth, settings.windowHeight), "SFML ImGui");
    window.setFramerateLimit(60);

    ImGui::SFML::Init(window);
    sf::Clock deltaClock;

    ImGui::GetStyle().ScaleAllSizes(1.0f);

    sf::Font myFont;
    if(!myFont.loadFromFile(settings.fontPath)) {
        std::cerr << "Error loading font" << std::endl;
        exit(-1);
    }

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

                }
            }
        }

        InitImGui(settings, window, deltaClock.restart());

        window.clear();

        for(const auto& shape_pair : settings.sf_shapes_properties_map) {
            const auto& shape = shape_pair.first;
            const auto& properties = shape_pair.second;
            shape->setScale(properties->scale, properties->scale);
            shape->setFillColor(sf::Color(properties->color[0] * 255.0f, properties->color[1] * 255.0f, properties->color[2] * 255.0f));

            shape->setPosition(shape->getPosition() + sf::Vector2f(properties->speedX, properties->speedY));
            if(shape->getPosition().x + properties->get_boundary() > settings.windowWidth || shape->getPosition().x - properties->get_boundary() < 0) {
                properties->speedX *= -1.0f;
            }
            if(shape->getPosition().y + properties->get_boundary() > settings.windowHeight || shape->getPosition().y - properties->get_boundary() < 0) {
                properties->speedY *= -1.0f;
            }
            sf::Text name_text(properties->name, myFont , settings.fontSize);
            sf::FloatRect textBounds = name_text.getLocalBounds();
            // Adjust the origin to be the center of the text
            name_text.setOrigin(textBounds.left + textBounds.width / 2.0f,
                                textBounds.top + textBounds.height / 2.0f);
            name_text.setPosition(shape->getPosition().x, shape->getPosition().y);

            if(properties->isDrawn) {
                window.draw(*shape);
                window.draw(name_text);
            }
        }

        sf::Text text("Sample Text", myFont , 24);
        text.setPosition(0, settings.windowHeight - (float)text.getCharacterSize());
        window.draw(text);


        ImGui::SFML::Render(window);
        window.display();
    }

    return 0;
}
