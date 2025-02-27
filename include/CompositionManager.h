#pragma once
#include <map>
#include <string>
#include <memory>
#include "../include/Composition.h"

class CompositionManager {
public:
    void create_composition(const std::string& name);
    void remove_composition(const std::string& name);
    std::shared_ptr<Composition> get_composition(const std::string& name);
    std::shared_ptr<Composition> get_current_composition() const;
    void set_current_composition(const std::string& name);
    void draw_current_composition(SDL_Renderer* renderer);
    void draw_all_compositions(SDL_Renderer* renderer) const;
    void save_all_compositions(const std::string& filename) const;
    void load_all_compositions(const std::string& filename);
    

private:
    std::map<std::string, std::shared_ptr<Composition>> _compositions;
    std::shared_ptr<Composition> _current_composition;
};
