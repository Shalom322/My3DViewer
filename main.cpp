
#include "ViewerWindow.h"
#include "OpenglRenderSystem.h"
#include "GeometryPrimitives.h"

#include <glm/gtc/matrix_transform.hpp>

void renderScene(OpenglRenderSystem& rs)
{
    static const auto data = GeometryPrimitives::createPyramidVertices();
    rs.renderTriangleSoup(data);
}

void rotatePyramid(
    OpenglRenderSystem& rs,
    float angle,
    const glm::vec3& axis)
{
    rs.setViewMatrix(
        glm::rotate(rs.getViewMatrix(), angle, axis));
}

int main()
{
    constexpr int width = 640;
    constexpr int height = 480;

    OpenglRenderSystem rs;
    ViewerWindow window("My 3D Viewer", width, height);

    rs.init();

    const glm::vec3 cameraPosition(0.0f, 0.0f, -3.0f);
    const glm::vec3 lookAtCenter(0.0f, 0.0f, 0.0f);
    const glm::vec3 cameraUpVector(0.0f, 1.0f, 0.0f);

    const glm::mat4 viewMatrix = glm::lookAt(
        cameraPosition, lookAtCenter, cameraUpVector);

    rs.setViewMatrix(viewMatrix);

    const glm::mat4 projMatrix = glm::perspective(
        glm::radians(60.0f),
        static_cast<float>(width) / static_cast<float>(height),
        0.1f,
        500.0f);

    rs.setProjectionMatrix(projMatrix);

    rs.setupLight(
        0,
        glm::vec3(0.0f, 5.0f, 0.0f),
        glm::vec3(1.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 1.0f, 0.0f),
        glm::vec3(0.0f, 0.0f, 1.0f));

    rs.turnLight(0, true);

    window.setKeyCallback([&rs](
        KeyCode key, Action action, Modifier mods)
    {
        (void)mods;

        if (action != Action::Press && action != Action::Repeat)
        {
            return;
        }

        const float angle = glm::radians(5.0f);

        if (key == KeyCode::UP)
        {
            rotatePyramid(rs, angle, glm::vec3(1.0f, 0.0f, 0.0f));
        }
        else if (key == KeyCode::DOWN)
        {
            rotatePyramid(rs, -angle, glm::vec3(1.0f, 0.0f, 0.0f));
        }
        else if (key == KeyCode::LEFT)
        {
            rotatePyramid(rs, angle, glm::vec3(0.0f, 1.0f, 0.0f));
        }
        else if (key == KeyCode::RIGHT)
        {
            rotatePyramid(rs, -angle, glm::vec3(0.0f, 1.0f, 0.0f));
        }
    });

    while (!glfwWindowShouldClose(window.getGLFWHandle()))
    {
        rs.setViewport(
            0, 0,
            window.getWidth(),
            window.getHeight());

        rs.clearDisplay(0.5f, 0.5f, 0.5f);
        renderScene(rs);

        glfwSwapBuffers(window.getGLFWHandle());
        glfwWaitEvents();
    }

    return 0;
}
