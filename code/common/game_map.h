// In D:\work\duanxueqi\SJDXQcourseware\project\code\common\game_map.h

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

// 游戏地图类
class GameMap {
public:
	GameMap() noexcept {}
	GameMap(const GameMap&) = delete;
	~GameMap() noexcept {}

	GameMap& operator=(const GameMap&) = delete;

	void clear() noexcept {
		m_entities.clear();
	}

	size_t get_size() const noexcept {
		return m_entities.size();
	}

	const Entity& get_at(size_t index) const {
		return *m_entities[index];
	}

    // 新增：添加实体到地图
    void add_entity(std::unique_ptr<Entity> entity) {
        m_entities.push_back(std::move(entity));
    }

    // 新增：获取可变实体指针（用于修改地图中的实体，例如更新玩家位置）
    Entity* get_entity_mutable_at(size_t index) {
        if (index < m_entities.size()) {
            return m_entities[index].get();
        }
        return nullptr; // 或者抛出异常
    }

private:
	std::vector<std::unique_ptr<Entity>> m_entities;
};

#endif // __GAME_MAP_H__