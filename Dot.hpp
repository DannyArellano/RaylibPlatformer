#ifndef DOT_HPP
#define DOT_HPP

#include "raylib.h"

class Dot {
public:
    Dot();
    void Update(float deltaTime);
    void Draw();
    void Activate(Vector2 position);
    void Deactivate();
    bool IsActive() const;
    void SetDirection(Vector2 direction);
    void SetSpeed(float speed);

private:
    Vector2 position;
    Vector2 direction;
    float speed;
    bool active;
};

#endif // DOT_HPP