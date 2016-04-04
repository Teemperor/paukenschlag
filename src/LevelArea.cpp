#include "LevelArea.h"
#include "TextureManager.h"
#include "Constants.h"

#include <SFML/Graphics/Shader.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include <levelgen/AreaDistributor.h>
#include <iostream>

void LevelArea::draw(sf::RenderTexture& tmpRender, sf::RenderTarget& renderTarget, sf::Shader& alphaShader, sf::RenderTexture& alphaTexture) {

    sf::Vector2f topLeftCorner = tmpRender.getView().getCenter();
    topLeftCorner.x -= tmpRender.getView().getSize().x / 2;
    topLeftCorner.y -= tmpRender.getView().getSize().y / 2;

    sf::FloatRect viewRect = sf::FloatRect(topLeftCorner, tmpRender.getView().getSize());

    if (viewRect.intersects(outline_)) {
        alphaTexture.clear(sf::Color::Transparent);

        alphaTexture.draw(*shape_.get());
        alphaTexture.display();

        alphaShader.setParameter("alphaMap", alphaTexture.getTexture());
        alphaShader.setParameter("texture", sf::Shader::CurrentTexture);

        tmpRender.clear(sf::Color::Transparent);

        tmpRender.draw(groundTexture);

        tmpRender.display();

        renderTarget.draw(sf::Sprite(tmpRender.getTexture()), &alphaShader);
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

    outline_ = sf::FloatRect(area.x() * SCALE, area.y() * SCALE, area.width() * SCALE, area.height() * SCALE);

    std::string tex = "data/floor/" + area.background() + ".png";

    groundTexture = TextureManager::instance().loadSprite(tex, true);

    sf::IntRect intRect(0, 0, (int) (area.width() * SCALE), (int) (area.height() * SCALE));
    groundTexture.setTextureRect(intRect);
    groundTexture.setPosition(sf::Vector2f(rect->getPosition().x, rect->getPosition().y));

    std::cout << "SHAPE[" << shape_->getPosition().x << "," << shape_->getPosition().y << ";" << shape_->getLocalBounds().width << "," << shape_->getLocalBounds().height << "]" << std::endl;
}