#ifndef SHOOTER_LEVELAREA_H
#define SHOOTER_LEVELAREA_H


#include <SFML/Graphics/ConvexShape.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <memory>
#include "TextureManager.h"

class Area;

class LevelArea {

public:

    LevelArea();

    LevelArea(Area& area);

    void draw(sf::RenderTexture& tmpRender, sf::RenderTarget& renderTarget, sf::Shader& alphaShader, sf::RenderTexture& alphaTex);

    void shape(sf::Shape* shape) {
        shape_.reset(shape);
    }

    sf::Shape* shape() {
        return shape_.get();
    }

    void texture(const std::string& texture) {
        groundTexture = TextureManager::instance().loadSprite(texture.c_str());
    }

private:

    std::unique_ptr<sf::Shape> shape_;
    sf::Sprite groundTexture;

};


#endif //SHOOTER_LEVELAREA_H
