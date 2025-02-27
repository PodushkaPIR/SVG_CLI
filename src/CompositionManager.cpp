#include <map>
#include <string>
#include <memory>
#include <fstream>
#include <iostream>

#include "../include/CompositionManager.h"
#include "../include/Composition.h"

void CompositionManager::create_composition(const std::string& name) {
    _compositions[name] = std::make_shared<Composition>(name);
}

void CompositionManager::remove_composition(const std::string& name) {
    _compositions.erase(name);
}

std::shared_ptr<Composition> CompositionManager::get_composition(const std::string& name) {
    return _compositions[name];
}

std::shared_ptr<Composition> CompositionManager::get_current_composition() const {
    return _current_composition;
}

void CompositionManager::set_current_composition(const std::string& name) {
    _current_composition = _compositions[name];
}

void CompositionManager::draw_current_composition(SDL_Renderer* renderer) {
    if (_current_composition) {
        _current_composition->draw(renderer);
    }
}

void CompositionManager::draw_all_compositions(SDL_Renderer* renderer) const {
    for (const auto& [name, composition] : _compositions) {
        composition->draw(renderer);
    }
}

void CompositionManager::save_all_compositions(const std::string& filename) const {
    json json_file;
    json_file["compositions"] = json::array();
    for (const auto& [name, composition] : _compositions) {
        json comp_json;
        composition->save_to_file(comp_json);
        json_file["compositions"].push_back(comp_json);
    }

    std::ofstream out_file(filename);
    out_file << json_file.dump(4);
}

void CompositionManager::load_all_compositions(const std::string& filename) {
    std::ifstream input_file(filename);
    json json_file;
    input_file >> json_file;

    // ПРОБЛЕМА ЗДЕСЬ
    // _compositions.clear();
    // _current_composition = nullptr;

    for (auto& comp_json : json_file["compositions"]) {
        auto composition = std::make_shared<Composition>("");
        composition->load_from_file(comp_json);
        _compositions[composition->get_name()] = composition;
    }

    if (!_compositions.empty()) {
        _current_composition = _compositions.begin()->second;
    } 

    else {
        std::cout << "No compositions loaded from file!" << std::endl;
    }
}
