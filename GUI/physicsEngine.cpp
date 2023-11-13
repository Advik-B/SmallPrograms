#include <iostream>

class PhysicsEngine {
public:
    PhysicsEngine(
            float initialX,
            float initialY,
            float width,
            float height,
            float initialSpeed,
            float initialDirection
            ) :
            position( { initialX, initialY }),
            velocity(initialSpeed * cos(glm::radians(initialDirection)),
                     initialSpeed * sin(glm::radians(initialDirection))),
            width(width), height(height), hitCornerTimer(0.0f) {


    }

    void changeVelocity(float newSpeed, float newDirection) {
        velocity.x = newSpeed * cos(glm::radians(newDirection));
        velocity.y = newSpeed * sin(glm::radians(newDirection));
    }

    void update(float deltaTime) {
        // Update hit corner timer
        hitCornerTimer += deltaTime;

        // Update position based on velocity
        position.x += velocity.x * deltaTime;
        position.y += velocity.y * deltaTime;

        // Check and handle collisions with walls
        if (position.x - width / 2 <= -1.0f || position.x + width / 2 >= 1.0f) {
            velocity.x = -velocity.x; // Invert the horizontal velocity on collision
            handleEdgeHit();
        }
        if (position.y - height / 2 <= -1.0f || position.y + height / 2 >= 1.0f) {
            velocity.y = -velocity.y; // Invert the vertical velocity on collision
            handleEdgeHit();
        }
    }

    [[nodiscard]] const glm::vec2& getPosition() const {
        return position;
    }


private:
    glm::vec2 position;
    glm::vec2 velocity;
    float width;
    float height;
    float hitCornerTimer;

    void handleEdgeHit();
};



#ifdef CHANGE_VELOCITY_ON_WALLHIT
void PhysicsEngine::handleEdgeHit() {
    // If the rectangle has hit a corner in the last 0.5 seconds, invert the velocity again
    hitCornerTimer = 0.0f;
    // Change the initial speed to a random value between 0.5 and 1.0
    std::mt19937 rng(std::random_device{}());
    std::uniform_real_distribution<float> distribution(0.3f, 1.0f);
    // Change velocity (keep the same direction)
    changeVelocity(distribution(rng), glm::degrees(atan2(velocity.y, velocity.x)));
}
#else
void PhysicsEngine::handleEdgeHit() {}
#endif
