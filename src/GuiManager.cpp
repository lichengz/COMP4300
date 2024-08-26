//
// Created by white on 2024-08-18.
//

#include "GuiManager.h"

#include <imgui-SFML.h>
#include <imgui.h>
#include <iostream>

GuiManager::GuiManager(sf::RenderWindow & window, const std::shared_ptr<EntityManager> & entityManager) : m_entityManager(entityManager) {
    auto window_inited = ImGui::SFML::Init(window);
    if(!window_inited) {
        std::cerr << "Failed to initialize ImGui" << std::endl;
    }
    ImGui::GetStyle().ScaleAllSizes(1.0f);
}

void GuiManager::update(GameSettings& settings, sf::RenderWindow& window, const sf::Time& deltaTime) {
    ImGui::SFML::Update(window, deltaTime);

    ImGui::Begin("Geometry Wars");

    if (ImGui::CollapsingHeader("Entities by Tag")) {
        for(const auto& tag : m_entityManager-> getEntityMap()) {
            if (ImGui::CollapsingHeader(tag.first.c_str())) {
                for(const auto& entity : tag.second) {
                    ImGui::Text("Entity %d", entity->m_id);
                    // ImGui::Text("Tag: %s", entity->m_tag.c_str());
                    ImGui::Text("Active: %s", entity->m_active ? "true" : "false");
                    ImGui::Separator();
                }
            }
        }
    }
    if (ImGui::CollapsingHeader("All Entities")) {
        for(const auto& entity : m_entityManager->getEntities()) {
            ImGui::Text("Entity %d", entity->m_id);
            // ImGui::Text("Tag: %s", entity->m_tag.c_str());
            ImGui::Text("Active: %s", entity->m_active ? "true" : "false");
            ImGui::Separator();
        }
    }
    // std::vector<std::string> shape_items;
    // for(const auto& shape : settings.shapes) {
    //     shape_items.push_back(shape->name);
    // }
    // static int item_current_idx = 0; // Here we store our selection data as an index.
    // const std::string combo_preview_value = shape_items[item_current_idx];  // Pass in the preview value visible before opening the combo (it could be anything)
    // if (ImGui::BeginCombo("Shape", combo_preview_value.c_str()))
    // {
    //     for (int n = 0; n < shape_items.size(); n++)
    //     {
    //         const bool is_selected = (item_current_idx == n);
    //         if (ImGui::Selectable(shape_items[n].c_str(), is_selected))
    //             item_current_idx = n;
    //
    //         // Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
    //         if (is_selected)
    //             ImGui::SetItemDefaultFocus();
    //     }
    //     ImGui::EndCombo();
    // }
    // auto& selected_shape = settings.shapes[item_current_idx];
    // ImGui::Checkbox("Draw Shape", &selected_shape->isDrawn);
    // ImGui::SliderFloat("Scale", &selected_shape->scale, 0.1, 2.0f);
    // ImGui::ColorEdit3("Color", selected_shape->color);

    ImGui::End();
}
