
#include "GeometryPrimitives.h"

#include <glm/geometric.hpp>

#include <vector>

std::vector<Vertex> GeometryPrimitives::createCubeVertices()
{
    std::vector<Vertex> cubeVertices;

    const glm::vec3 positions[] = {
        {-0.5f, -0.5f, -0.5f},
        { 0.5f, -0.5f, -0.5f},
        { 0.5f,  0.5f, -0.5f},
        {-0.5f,  0.5f, -0.5f},
        {-0.5f, -0.5f,  0.5f},
        { 0.5f, -0.5f,  0.5f},
        { 0.5f,  0.5f,  0.5f},
        {-0.5f,  0.5f,  0.5f}
    };

    const glm::vec3 normals[] = {
        { 0.0f,  0.0f, -1.0f},
        { 0.0f,  0.0f,  1.0f},
        {-1.0f,  0.0f,  0.0f},
        { 1.0f,  0.0f,  0.0f},
        { 0.0f, -1.0f,  0.0f},
        { 0.0f,  1.0f,  0.0f}
    };

    const glm::vec3 colors[] = {
        {1.0f, 0.0f, 0.0f},
        {0.0f, 1.0f, 0.0f},
        {0.0f, 0.0f, 1.0f},
        {1.0f, 1.0f, 0.0f},
        {1.0f, 0.0f, 1.0f},
        {0.0f, 1.0f, 1.0f}
    };

    const unsigned int indices[] = {
        0, 1, 2,  2, 3, 0,
        4, 5, 6,  6, 7, 4,
        0, 3, 7,  7, 4, 0,
        1, 5, 6,  6, 2, 1,
        0, 1, 5,  5, 4, 0,
        3, 2, 6,  6, 7, 3
    };

    for (int i = 0; i < 36; ++i)
    {
        const unsigned int index = indices[i];
        const int face = i / 6;

        Vertex vertex;
        vertex.position = positions[index];
        vertex.normal = normals[face];
        vertex.color = colors[face];

        cubeVertices.push_back(vertex);
    }

    return cubeVertices;
}

std::vector<Vertex> GeometryPrimitives::createPyramidVertices()
{
    std::vector<Vertex> vertices;

    const glm::vec3 a(-0.5f, 0.0f, -0.5f);
    const glm::vec3 b( 0.5f, 0.0f, -0.5f);
    const glm::vec3 c( 0.5f, 0.0f,  0.5f);
    const glm::vec3 d(-0.5f, 0.0f,  0.5f);
    const glm::vec3 top(0.0f, 1.0f, 0.0f);

    auto addTriangle = [&vertices](
        const glm::vec3& p1,
        const glm::vec3& p2,
        const glm::vec3& p3,
        const glm::vec3& color)
    {
        glm::vec3 normal =
            glm::normalize(glm::cross(p2 - p1, p3 - p1));

        Vertex v1;
        v1.position = p1;
        v1.normal = normal;
        v1.color = color;
        vertices.push_back(v1);

        Vertex v2;
        v2.position = p2;
        v2.normal = normal;
        v2.color = color;
        vertices.push_back(v2);

        Vertex v3;
        v3.position = p3;
        v3.normal = normal;
        v3.color = color;
        vertices.push_back(v3);
    };

    // Four side faces
    addTriangle(a, top, b, glm::vec3(1.0f, 0.0f, 0.0f));
    addTriangle(b, top, c, glm::vec3(0.0f, 1.0f, 0.0f));
    addTriangle(c, top, d, glm::vec3(0.0f, 0.0f, 1.0f));
    addTriangle(d, top, a, glm::vec3(1.0f, 1.0f, 0.0f));

    // Square base, split into two triangles
    const glm::vec3 baseColor(1.0f, 0.0f, 1.0f);
    addTriangle(a, b, c, baseColor);
    addTriangle(a, c, d, baseColor);

    return vertices;
}
