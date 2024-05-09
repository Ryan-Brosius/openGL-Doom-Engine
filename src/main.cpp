#include "Window.h"

#include "TextureMap.h"
#include "LinearAlgebraUtils.h"
#include <glm/glm.hpp>

int main(void)
{
    //std::cout << angleCCW(glm::vec3(-1, 10, 0), glm::vec3(0, 0, 0), glm::vec3(1, 10, 0)) << std::endl;
    //std::cout << angleCCW(glm::vec3(1, 0, 0), glm::vec3(0, 0, 0), glm::vec3(0, -1, 0)) << std::endl;

    for (int x = -3; x < 3; x++)
    {
        for (int y = -3; y < 3; y++)
        {
            for (int z = -3; z < 3; z++)
            {
                if (insideTriangle(glm::vec3(3, 0, 0), glm::vec3(0, 0, 0), glm::vec3(0, -3, 0), glm::vec3(x, y, z)))
                {
                    std::cout << x << " " << y << " " << z << " is in triangle!" << std::endl;
                }
            }
        }
    }

    exit(1);
    Window window;
    window.window_loop();
}