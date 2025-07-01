#ifndef OBJECT_H
#define OBJECT_H
#include "../common/entity.h"

class Door : public Entity {
public:
    Door(double x, double y): Entity(x, y) {
        w = 40, h = 40, type = 'D';
    }
};
class Spike : public Entity {
public:
    Spike(double x, double y): Entity(x, y) {
        w = 54, h = 13, type = 'S';
    }
};
class Wall : public Entity {
public:
    Wall(double x, double y, double width, double height): Entity(x, y) {
        w = width, h = height, type = 'W';
    }
};

class Player : public Entity {
#define size_w 26
#define size_h 38
#define fps 60
#define V_Horizontal 40
#define V_Vertical 60
#define Gravity 40
private:
    double v_Vertical, v_Horizontal;
    bool isGrounded;
public:
    Player(double x, double y) : Entity(x, y) {
        v_Horizontal = v_Vertical = 0, isGrounded = 1;
        w = size_w, h = size_h, type = 'P';
    }
    void MoveLeft() {
        v_Horizontal = -V_Horizontal;
    }
    void MoveRight() {
        v_Horizontal = V_Horizontal;
    }
    void Jump() {
        if(!isGrounded) return ;//can't jump in the air
        isGrounded = 0;
        v_Vertical = V_Vertical;
    }
    void Stop() {
        v_Horizontal = 0;
    }
    bool check_spike(int x, int y) {
        return mp[x][y] == 'S' || mp[x+size_w-1][y] == 'S' || mp[x][y+size_h-1] == 'S' || mp[x+size_w-1][y+size_h-1] == 'S';
    }
    bool check_door(int x, int y) {
        return mp[x][y] == 'D' || mp[x+size_w-1][y] == 'D' || mp[x][y+size_h-1] == 'D' || mp[x+size_w-1][y+size_h-1] == 'D';
    }
    bool check_empty(int x, int y) {
        return mp[x][y] == 'E' || mp[x+size_w-1][y] == 'E' || mp[x][y+size_h-1] == 'E' || mp[x+size_w-1][y+size_h-1] == 'E';
    }
    bool check_wall(int x, int y) {
        return mp[x][y] == 'W' || mp[x+size_w-1][y] == 'W' || mp[x][y+size_h-1] == 'W' || mp[x+size_w-1][y+size_h-1] == 'W';
    }
    bool check_up_wall(int x, int y) {
        return mp[x][y+size_h-1] == 'W' || mp[x+size_w-1][y+size_h-1] == 'W';
    }
    bool check_down_wall(int x, int y) {
        return mp[x][y] == 'W' || mp[x+size_w-1][y] == 'W';
    }
    bool check_left_wall(int x, int y) {
        return mp[x][y] == 'W' || mp[x][y+size_h-1] == 'W';
    }
    bool check_right_wall(int x, int y) {
        return mp[x+size_w-1][y] == 'W' || mp[x+size_w-1][y+size_h-1] == 'W';
    }
    void del_player_in_map(int x, int y) {
        rep(i,x,x+size_w-1) rep(j,y,y+size_h-1) mp[i][j] = 'E';
    }
    void add_player_in_map(int x, int y) {
        rep(i,x,x+size_w-1) rep(j,y,y+size_h-1) mp[i][j] = 'P';
    }
    int update() {
        int xx = pos.x + v_Horizontal/fps + 0.5, yy = pos.y + v_Vertical/fps + 0.5;

        if(xx<0 || xx>Weight || yy<0 || yy>Height || check_spike(xx, yy)) {//out of field or crash into spike
            return -1;//return -1 means die
        }
        else if(check_empty(xx, yy)) {//empty place
            if(!isGrounded) v_Vertical -= Gravity/fps;
            del_player_in_map((int)(pos.x+0.5), (int)(pos.y+0.5));
            pos.x += v_Horizontal/fps;
            pos.y += v_Vertical/fps;
            add_player_in_map((int)(pos.x+0.5), (int)(pos.y+0.5));
            return 0;//nothing happen
        }
        else if(check_door(xx, yy)) {//pass this level
            return 1;
        }
        else if(check_wall(xx, yy)) {//Wall
            if(v_Vertical>0 && check_up_wall(xx, yy)) {//head touch the Wall
                v_Vertical *= -1;
            }
            if(v_Horizontal>0 && check_right_wall(xx, yy)) {//right touch the Wall
                v_Horizontal = 0;
            }
            if(v_Horizontal<0 && check_left_wall(xx, yy)) {//left touch the Wall
                v_Horizontal = 0;
            }
            isGrounded = check_down_wall(xx, yy);
            if(!isGrounded) v_Vertical -= Gravity/fps;
            else v_Vertical = 0;
            del_player_in_map((int)(pos.x+0.5), (int)(pos.y+0.5));
            pos.x += v_Horizontal/fps;
            pos.y += v_Vertical/fps;
            add_player_in_map((int)(pos.x+0.5), (int)(pos.y+0.5));
            return 0;
        }
    }
};
#endif