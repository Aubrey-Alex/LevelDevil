#ifndef PROPERTY_IDS_H
#define PROPERTY_IDS_H

/**
 * @brief 定义了用于观察者模式通知的属性ID。
 *
 * 这个枚举类是整个MVVM架构中数据绑定的"契约"之一。
 * 当一个Subject（如ViewModel或Model）的状态发生变化时，它会通过
 * notify(PropertyID)方法，使用此枚举中的一个值来精确告知
 * 所有的Observer（观察者），是哪一个具体的数据属性发生了更新。
 * 这种方式比使用字符串或整数ID更类型安全，也更易于维护。
 */
enum class PropertyID {
    // 玩家相关
    PlayerPositionChanged,    // 玩家位置变化
    PlayerStateChanged,       // 玩家状态变化（站立、跳跃、下落等）
    PlayerDirectionChanged,   // 玩家朝向变化
    
    // 游戏状态相关
    GameStateChanged,         // 游戏状态变化（开始、暂停、结束等）
    LevelStateChanged,        // 关卡状态变化（加载中、进行中、完成等）
    
    // 碰撞检测相关
    CollisionDetected,        // 发生碰撞
    TriggerEntered,          // 进入触发区域（如终点门）
    
    // UI相关
    UIStateChanged,          // UI状态变化
    ScoreChanged,           // 分数变化
    
    // 调试相关
    DebugInfoChanged,       // 调试信息变化
    
    MapUpdated // Added for explicit map redraws
};

#endif
