 #ifndef __GAME_MAP_H__
#define __GAME_MAP_H__

#include <vector>
#include <memory>
#include "property_ids.h"

// 游戏实体类型
enum class EntityType {
    Player,         // 玩家
    Wall,       // 墙
    Door,          // 终点门
    Spike          // 尖刺
};

// 实体的物理属性
struct PhysicsProperties {
    bool has_collision = true;      // 是否有碰撞
    bool is_trigger = false;        // 是否是触发器
    bool is_static = true;         // 是否是静态物体
    float gravity_scale = 1.0f;    // 重力系数
};

// 游戏实体基类
struct Entity {
    EntityType type;               // 实体类型
    float x = 0, y = 0;           // 位置
    float width = 0, height = 0;  // 大小
    PhysicsProperties physics;     // 物理属性
    
    Entity(EntityType t) : type(t) {}
    virtual ~Entity() = default;
};

// 玩家实体
struct Player : public Entity {
    float velocity_x = 0, velocity_y = 0;  // 速度
    bool is_grounded = false;              // 是否在地面上
    bool facing_right = true;              // 朝向
    
    Player() : Entity(EntityType::Player) {
        physics.is_static = false;
        physics.has_collision = true;
        width = 32;  // 根据实际像素大小调整
        height = 32;
    }
};

// 墙实体
struct Wall : public Entity {
    Wall() : Entity(EntityType::Wall) {
        physics.is_static = true;
        physics.has_collision = true;
    }
};

// 终点门实体
struct Door : public Entity {
    bool is_open = false;
    
    Door() : Entity(EntityType::Door) {
        physics.is_static = true;
        physics.is_trigger = true;
        physics.has_collision = false;
    }
};

// 游戏地图类
class GameMap {
public:
    GameMap() = default;
    GameMap(const GameMap&) = delete;
    ~GameMap() = default;
    
    GameMap& operator=(const GameMap&) = delete;
    
    // 地图管理
    void clear() { m_entities.clear(); }
    size_t get_entity_count() const { return m_entities.size(); }
    
    // 实体访问
    std::shared_ptr<Entity> get_entity(size_t idx) { 
        return idx < m_entities.size() ? m_entities[idx] : nullptr; 
    }
    
    // 实体管理
    void add_entity(std::shared_ptr<Entity> entity) {
        m_entities.push_back(entity);
    }
    
    void remove_entity(size_t idx) {
        if (idx < m_entities.size()) {
            m_entities.erase(m_entities.begin() + idx);
        }
    }
    
    // 获取玩家实体
    std::shared_ptr<Player> get_player() {
        for (auto& entity : m_entities) {
            if (entity->type == EntityType::Player) {
                return std::static_pointer_cast<Player>(entity);
            }
        }
        return nullptr;
    }

private:
    std::vector<std::shared_ptr<Entity>> m_entities;
};

#endif