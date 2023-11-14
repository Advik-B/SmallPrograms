#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <random>


//#define CHANGE_VELOCITY_ON_WALLHIT

#include "physicsEngine.cpp"

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void DrawRect(const glm::vec2& position, float width, float height) {
    glBegin(GL_QUADS);
    glVertex2f(position.x - width / 2, position.y + height / 2);
    glVertex2f(position.x - width / 2, position.y - height / 2);
    glVertex2f(position.x + width / 2, position.y - height / 2);
    glVertex2f(position.x + width / 2, position.y + height / 2);
    glEnd();
}

int main() {
    GLFWwindow* window;

    if (!glfwInit())
        return -1;

    window = glfwCreateWindow(640, 480, "Bouncing Rectangle", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    std::mt19937 rng(std::random_device{}());
    std::uniform_real_distribution<float> distribution(-180.0f, 180.0f);
    float initialDirection = distribution(rng); // Random initial rotation

    PhysicsEngine pEngine(0.0f, 0.0f, 0.5f, 0.5f, 0.7f, initialDirection);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        pEngine.update(0.016f); // Update with a fixed time step (60 FPS)

        DrawRect(pEngine.getPosition(), 0.5f, 0.5f);

        glfwSwapBuffers(window);
        glfwPollEvents();

    }

    glfwTerminate();
    return 0;
}
