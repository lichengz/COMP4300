//
// Created by white on 2024-08-23.
//

#ifndef ACTION_H
#define ACTION_H

enum class ActionType {
    MOVE_LEFT,
    MOVE_RIGHT,
    JUMP,
    SHOOT
};

enum class ActionState {
    START,
    END
};

class Action {
    ActionType m_type;
    ActionState m_state;
public:
    Action(ActionType type, ActionState state) : m_type(type), m_state(state) {}
    ActionType getType() const { return m_type; }
    ActionState getState() const { return m_state; }
};



#endif //ACTION_H
