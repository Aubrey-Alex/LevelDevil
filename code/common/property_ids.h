#ifndef PROPERTY_IDS_H
#define PROPERTY_IDS_H

enum class PropertyID {
    // Player related
    PlayerPositionChanged,
    PlayerStateChanged,
    PlayerDirectionChanged,
    
    // Game state
    GameStateChanged,
    LevelStateChanged,
    
    // Collision
    CollisionDetected,
    TriggerEntered,
    
    // UI
    UIStateChanged,
    ScoreChanged,
    
    // Debug
    DebugInfoChanged
};

#endif