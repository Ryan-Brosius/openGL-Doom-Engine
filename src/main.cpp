#include "Window.h"

#include "TextureMap.h"
#include "LinearAlgebraUtils.h"
#include <glm/glm.hpp>

#include "DoubleLinkedList.h"
#include "GFXObjectFactory.h"
#include <memory>

int main(void)
{
    //std::shared_ptr<DoubleLinkedList<glm::vec3>> d = std::make_shared<DoubleLinkedList<glm::vec3>>();
    //d->add(glm::vec3(2, 3, 4));
    //GFXObjectFactory::createVertexArray(d);


    Window window;
    window.window_loop();
}