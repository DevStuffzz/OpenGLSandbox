#pragma once
#include "Buffers/VertexArray.h"


class Primitives {
private:
    Primitives();
public:
    static std::unique_ptr<VertexArray> Quad() {
        std::vector<float> vertices = {
            // positions          // colors           // texture coords
             0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 1.0f,   1.0f, 1.0f,   // top right
             0.5f, -0.5f, 0.0f,   1.0f, 1.0f, 1.0f,   1.0f, 0.0f,   // bottom right
            -0.5f, -0.5f, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f, 0.0f,   // bottom left
            -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f, 1.0f    // top left 
        };
        std::vector<unsigned int> elements = {
            0, 1, 2,
            2, 3, 0
        };

        return std::make_unique<VertexArray>(vertices, elements);
    }

    static std::unique_ptr<VertexArray> Triangle() {
        std::vector<float> vertices = {
            // positions          // colors           // texture coords
             0.0f,  0.5f, 0.0f,   1.0f, 1.0f, 1.0f,   0.5f, 1.0f,   // top
             0.5f, -0.5f, 0.0f,   1.0f, 1.0f, 1.0f,   1.0f, 0.0f,   // bottom right
            -0.5f, -0.5f, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f, 0.0f    // bottom left
        };
        std::vector<unsigned int> elements = {
            0, 1, 2
        };

        return std::make_unique<VertexArray>(vertices, elements);
    }


    static std::unique_ptr<VertexArray> Sphere(float radius, unsigned int sectorCount, unsigned int stackCount) {
        std::vector<float> vertices;
        std::vector<unsigned int> elements;

        float x, y, z, xy;                              // vertex position
        float nx, ny, nz, lengthInv = 1.0f / radius;    // normal
        float s, t;                                     // texCoord
        float M_PI = 3.1415269;
        float sectorStep = 2 * M_PI / sectorCount;
        float stackStep = M_PI / stackCount;
        float sectorAngle, stackAngle;

        for (unsigned int i = 0; i <= stackCount; ++i) {
            stackAngle = M_PI / 2 - i * stackStep;        // from pi/2 to -pi/2
            xy = radius * cosf(stackAngle);             // r * cos(u)
            z = radius * sinf(stackAngle);              // r * sin(u)

            for (unsigned int j = 0; j <= sectorCount; ++j) {
                sectorAngle = j * sectorStep;           // from 0 to 2pi

                // vertex position (x, y, z)
                x = xy * cosf(sectorAngle);             // r * cos(u) * cos(v)
                y = xy * sinf(sectorAngle);             // r * cos(u) * sin(v)
                vertices.push_back(x);
                vertices.push_back(y);
                vertices.push_back(z);

                // vertex color (r, g, b)
                vertices.push_back(1.0f); // red
                vertices.push_back(1.0f); // green
                vertices.push_back(1.0f); // blue

                // vertex tex coord (s, t)
                s = (float)j / sectorCount;
                t = (float)i / stackCount;
                vertices.push_back(s);
                vertices.push_back(t);
            }
        }

        unsigned int k1, k2;
        for (unsigned int i = 0; i < stackCount; ++i) {
            k1 = i * (sectorCount + 1);     // beginning of current stack
            k2 = k1 + sectorCount + 1;      // beginning of next stack

            for (unsigned int j = 0; j < sectorCount; ++j, ++k1, ++k2) {
                // 2 triangles per sector excluding the first and last stacks
                // k1 => k2 => k1+1
                if (i != 0) {
                    elements.push_back(k1);
                    elements.push_back(k2);
                    elements.push_back(k1 + 1);
                }

                // k1+1 => k2 => k2+1
                if (i != (stackCount - 1)) {
                    elements.push_back(k1 + 1);
                    elements.push_back(k2);
                    elements.push_back(k2 + 1);
                }
            }
        }

        return std::make_unique<VertexArray>(vertices, elements);
    }

    static std::unique_ptr<VertexArray> Cube() {
        std::vector<float> vertices = {
            // positions          // colors           // texture coords
            // Front face
             0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f,  1.0f, 1.0f,  // top right
             0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 1.0f,  1.0f, 0.0f,  // bottom right
            -0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 1.0f,  0.0f, 0.0f,  // bottom left
            -0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f,  0.0f, 1.0f,  // top left

            // Back face
             0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f,  1.0f, 1.0f,  // top right
             0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f,  1.0f, 0.0f,  // bottom right
            -0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f,  0.0f, 0.0f,  // bottom left
            -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f,  0.0f, 1.0f,  // top left

            // Left face
            -0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f,  1.0f, 1.0f,  // top right
            -0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 1.0f,  1.0f, 0.0f,  // bottom right
            -0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f,  0.0f, 0.0f,  // bottom left
            -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f,  0.0f, 1.0f,  // top left

            // Right face
             0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f,  1.0f, 1.0f,  // top right
             0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 1.0f,  1.0f, 0.0f,  // bottom right
             0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f,  0.0f, 0.0f,  // bottom left
             0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f,  0.0f, 1.0f,  // top left

             // Top face
              0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f,  1.0f, 1.0f,  // top right
              0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f,  1.0f, 0.0f,  // bottom right
             -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f,  0.0f, 0.0f,  // bottom left
             -0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f,  0.0f, 1.0f,  // top left

             // Bottom face
              0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 1.0f,  1.0f, 1.0f,  // top right
              0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f,  1.0f, 0.0f,  // bottom right
             -0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f,  0.0f, 0.0f,  // bottom left
             -0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 1.0f,  0.0f, 1.0f   // top left
        };

        std::vector<unsigned int> elements = {
            // Front face
            0, 1, 2,
            2, 3, 0,
            // Back face
            4, 5, 6,
            6, 7, 4,
            // Left face
            8, 9, 10,
            10, 11, 8,
            // Right face
            12, 13, 14,
            14, 15, 12,
            // Top face
            16, 17, 18,
            18, 19, 16,
            // Bottom face
            20, 21, 22,
            22, 23, 20
        };

        return std::make_unique<VertexArray>(vertices, elements);
    }
};
