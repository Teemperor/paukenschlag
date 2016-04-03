#include "LevelArea.h"
#include "TextureManager.h"
#include "Constants.h"

#include <SFML/Graphics/Shader.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include <levelgen/AreaDistributor.h>
#include <iostream>

void LevelArea::draw(sf::RenderTexture& tmpRender, sf::RenderTarget& renderTarget, sf::Shader& alphaShader, sf::RenderTexture& alphaTexture) {

    alphaTexture.clear(sf::Color::Transparent);

    alphaTexture.draw(*shape_.get());
    alphaTexture.display();

    alphaShader.setParameter("alphaMap", alphaTexture.getTexture());
    alphaShader.setParameter("texture", sf::Shader::CurrentTexture);

    float startX = shape_->getPosition().x;
    float endX = shape_->getPosition().x + shape_->getLocalBounds().width;
    float deltaX = groundTexture.getLocalBounds().width;

    float startY = shape_->getPosition().y;
    float endY = shape_->getPosition().y + shape_->getLocalBounds().height;
    float deltaY = groundTexture.getLocalBounds().height;

    tmpRender.setView(renderTarget.getView());
    tmpRender.clear(sf::Color::Transparent);

    for (float x = startX; x < endX; x += deltaX) {
        for (float y = startY; y < endY; y += deltaY) {
            groundTexture.setPosition(sf::Vector2f(x, y));
            //renderTarget.draw(groundTexture);
            tmpRender.draw(groundTexture);
        }
    }

    tmpRender.display();

    sf::View viewBak = renderTarget.getView();
    renderTarget.setView(renderTarget.getDefaultView());
    renderTarget.draw(sf::Sprite(tmpRender.getTexture()), &alphaShader);
    renderTarget.setView(viewBak);
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
    switch(rand() % 2) {
        case 0:
            tex = "data/floor/asphalt.png";
            break;
        //case 1:
            tex = "data/floor/forest.png";
        //    break;
        case 1:
            tex = "data/floor/stoneroad.png";
            break;
    }
    groundTexture = TextureManager::instance().loadSprite(tex);

    std::cout << "SHAPE[" << shape_->getPosition().x << "," << shape_->getPosition().y << ";" << shape_->getLocalBounds().width << "," << shape_->getLocalBounds().height << "]" << std::endl;
}