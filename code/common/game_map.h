#ifndef __GAME_MAP_H__
#define __GAME_MAP_H__

#include <vector>
#include <memory>
#include "property_ids.h"

struct Position {
	double x, y;
	Position(double x, double y): x(x), y(y) {}
};

// 游戏实体基类
class Entity {
public:
    char type;               // 实体类型
    Position pos;           // 位置
    double w, h;  // 大小
    Entity(double x, double y): pos(x, y) {}
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
		return *m_entities[idx];
	}
	Entity& get_at(size_t idx) noexcept
	{
		return *m_entities[idx];
	}

	void set_size(size_t size)
	{
		m_entities.resize(size);
	}

	void append(std::shared_ptr<Entity> v)
	{
		m_entities.push_back(v);
	}
	void insert(size_t idx, std::shared_ptr<Entity> v)
	{
		m_entities.insert(m_entities.begin() + idx, v);
	}
	void remove(size_t idx) noexcept
	{
		m_entities.erase(m_entities.begin() + idx);
	}

private:
    std::vector<std::shared_ptr<Entity>> m_entities;
};

#endif
