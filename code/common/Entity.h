#ifndef ENTITY_H
#define ENTITY_H

#define W 1080
#define H 720
char mp[W][H];
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
#endif