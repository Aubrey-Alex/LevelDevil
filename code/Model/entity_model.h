#ifndef ENTITY_MODEL_H
#define ENTITY_MODEL_H
#include "object.h"
#include "../common/game_map.h"
#include "../common/frame.h"
#include <nlohmann/json.hpp>
#include <fstream>
#include <memory>
class Entity_Model:IModel {
private:
    std::shared_ptr<GameMap> sp_GameMap;
public:
    Entity_Model(): sp_GameMap(std::make_shared<GameMap>()) {}
    std::shared_ptr<GameMap> getGameMap() { return sp_GameMap; }
    void loadMapFromJson(const std::string& filename) {
        std::ifstream file(filename);
        nlohmann::json jsonData;
        file >> jsonData;
        
        auto wallsJson = jsonData["entities"]["walls"];
        for (const auto& wallJson : wallsJson) {
            auto pos = wallJson["position"];
            auto size = wallJson["size"];
            int x = pos["x"].get<int>();
            int y = pos["y"].get<int>();
            int w = size["width"].get<int>();
            int h = size["height"].get<int>();
            auto wall = std::make_shared<Wall>(x, y, w, h);
            sp_GameMap->append(wall);
        }
        auto spikesJson = jsonData["entities"]["spikes"];
        for (const auto& spikeJson : spikesJson) {
            auto pos = spikeJson["position"];
            int x = pos["x"].get<int>();
            int y = pos["y"].get<int>();
            auto spike = std::make_shared<Spike>(x, y);
            sp_GameMap->append(spike);
        }
        auto playerJson = jsonData["entities"]["player"]; {
            auto pos = playerJson["position"];
            int x = pos["x"].get<int>();
            int y = pos["y"].get<int>();
            auto player = std::make_shared<Player>(x, y);
            sp_GameMap->append(player);
        }
        auto doorJson = jsonData["entities"]["door"]; {
            auto pos = doorJson["position"];
            int x = pos["x"].get<int>();
            int y = pos["y"].get<int>();
            auto door = std::make_shared<Door>(x, y);
            sp_GameMap->append(door);
        }
    }
    void newLevel(int level) {
        if(level == 1) {
            loadMapFromJson("C:/Users/20690/Desktop/Tringmo/files/university/courses/C++_project_manager/LevelDevil/LevelDevil/code/Model/level1.json");
        }
    }
    void update(float deltaTime) override {
        for (size_t i = 0; i < sp_GameMap->get_size(); ++i) {
            auto& entity = sp_GameMap->get_at(i);
            if (entity.type == 'P') {
                auto* player = static_cast<Player*>(&entity);
                Position oldPos = player->pos;
                int result = player->update();//game state
                if (player->pos.x != oldPos.x || player->pos.y != oldPos.y) 
                    fire(PropertyID::PlayerPositionChanged);//pos change
                if (result == -1) 
                    fire(PropertyID::GameStateChanged);//die
                else if (result == 1) 
                    fire(PropertyID::LevelStateChanged);//next level
            }
        }
    }
};
#endif