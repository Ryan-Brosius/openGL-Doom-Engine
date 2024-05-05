#include "State.h"

State::State(){}

void State::generateTextureMap(Shader* shader)
{
	textureMap = new TextureMap(shader);
}

extern State* state;