#include "LevelArea.h"
#include "TextureManager.h"
#include "Constants.h"

#include <SFML/Graphics/Shader.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include <levelgen/AreaDistributor.h>
#include <iostream>

void LevelArea::draw(sf::RenderTarget& renderTarget, sf::Shader& alphaShader, sf::RenderTexture& alphaTexture) {
    alphaTexture.clear(sf::Color::Transparent);
    alphaTexture.draw(*shape_.get());
    alphaTexture.display();

    alphaShader.setParameter("alphaMap", alphaTexture.getTexture());

    for (float x = shape_->getPosition().x; x < shape_->getPosition().x + shape_->getLocalBounds().width; x += groundTexture.getLocalBounds().width) {
        for (float y = shape_->getPosition().y; y < shape_->getPosition().y + shape_->getLocalBounds().height; y += groundTexture.getLocalBounds().height) {
            groundTexture.setPosition(sf::Vector2f(x, y));
            renderTarget.draw(groundTexture, &alphaShader);
        }
    }
}

LevelArea::LevelArea() {
    shape_.reset(new sf::RectangleShape(sf::Vector2f(0, 0)));
}

LevelArea::LevelArea(Area& area) {
    sf::RectangleShape* rect;
    shape_.reset(rect = new sf::RectangleShape(sf::Vector2f((float) (area.width() * SCALE),
                                                            (float) (area.height() * SCALE))));
    rect->setPosition((float) (area.x() * SCALE),
                      (float) (area.y() * SCALE));

    std::string tex;
    switch(rand() % 3) {
        case 0:
            tex = "data/floor/asphalt.png";
            break;
        case 1:
            tex = "data/floor/forest.png";
            break;
        case 2:
            tex = "data/floor/stoneroad.png";
            break;
    }
    groundTexture = TextureManager::instance().loadSprite(tex);

    std::cout << (int) rect->getPosition().x << "," << (int) rect->getPosition().y << "|" << (int) rect->getSize().x << "," << (int) rect->getSize().y << std::endl;

}