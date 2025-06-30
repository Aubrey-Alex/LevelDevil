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
	GameMap() noexcept
	{
	}
	GameMap(const GameMap&) = delete;
	~GameMap() noexcept
	{
	}

	GameMap& operator=(const GameMap&) = delete;

	void clear() noexcept
	{
		m_entities.clear();
	}

	size_t get_size() const noexcept
	{
		return m_entities.size();
	}

	const Entity& get_at(size_t idx) const noexcept
	{
		return m_entities[idx];
	}
	Entity& get_at(size_t idx) noexcept
	{
		return m_entities[idx];
	}

	void set_size(size_t size)
	{
		m_entities.resize(size);
	}

	void append(const Entity& v)
	{
		m_entities.push_back(v);
	}
	void insert(size_t idx, const Entity& v)
	{
		m_entities.insert(m_entities.begin() + idx, v);
	}
	void remove(size_t idx) noexcept
	{
		m_entities.erase(m_entities.begin() + idx);
	}

private:
    std::vector<Entity> m_entities;
};

#endif