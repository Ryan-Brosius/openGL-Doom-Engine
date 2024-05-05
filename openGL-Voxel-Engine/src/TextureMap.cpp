#include "TextureMap.h"

TextureMap::TextureMap(Shader* shader)
{
    for (const auto& entry : fs::directory_iterator(path)) {
        if (fs::is_regular_file(entry.path())) {
            std::string name = entry.path().filename().string();
            map.emplace(std::make_pair(name, std::make_shared<Texture>(name.c_str(), GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE)));
            get(name)->texUnit(*shader, "tex0", 0);
        }
    }
}

Texture* TextureMap::get(std::string texture)
{
    if (map.find(texture) == map.end())
    {
        return get("missing_texture.png");
    }
    return map.at(texture).get();
}