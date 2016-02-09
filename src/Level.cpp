/*
 * Copyright 2015 WebAssembly Community Group
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */


#include "Level.h"
#include "Character.h"

const std::string fragmentShader =
    "uniform sampler2D texture;\n"
    "uniform sampler2D alphaMap;\n"
    "\n"
    "void main()\n"
    "{\n"
    "    // lookup the pixel in the texture\n"
    "    vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);\n"
    "    vec4 alphaPixel = texture2D(alphaMap, gl_TexCoord[0].xy);\n"
    "\n"
    "    // multiply it by the color\n"
    "    gl_FragColor = gl_Color * alphaPixel.w * pixel;\n"
    "}";

void Level::add(Character* object) {
    objects_.push_back(object);
    players_.push_back(object);
}

void Level::render(PlayerViewport& viewport) {
    int x1 = ((int) (viewport.view().getCenter().x - viewport.view().getSize().x / 2) / (int) dirtySprite.getLocalBounds().width);
    int y1 = ((int) (viewport.view().getCenter().y - viewport.view().getSize().y / 2) / (int) dirtySprite.getLocalBounds().height);
    int x2 = ((int) (viewport.view().getCenter().x + viewport.view().getSize().x / 2) / (int) dirtySprite.getLocalBounds().width);
    int y2 = ((int) (viewport.view().getCenter().y + viewport.view().getSize().y / 2) / (int) dirtySprite.getLocalBounds().height);


    for (int x = x1; x <= x2; x++) {
        for (int y = y1; y <= y2; y++) {
            dirtySprite.setPosition(x * dirtySprite.getLocalBounds().width, y * dirtySprite.getLocalBounds().height);
            viewport.window().draw(dirtySprite);
        }
    }

    alphaTexture.clear(sf::Color::Transparent);
    alphaTexture.draw(alphaSprite);
    alphaTexture.display();
    shader.setParameter("alphaMap", alphaTexture.getTexture());
    viewport.window().draw(sandSprite, &shader);

    for (auto iter = objects_.rbegin(); iter != objects_.rend(); iter++) {
        (*iter)->render(viewport);
    }
}

Level::Level() : world_(b2Vec2(0.f, 0.f)) {
    dirtySprite = TextureManager::instance().loadSprite("data/floor/sand.jpg");
    alphaSprite = TextureManager::instance().loadSprite("data/floor/alpha.png");
    sandSprite = TextureManager::instance().loadSprite("data/floor/smoothSand.png");
    world_.SetContactListener(this);

    assert(alphaTexture.create(512, 512));

    shader.loadFromMemory(fragmentShader, sf::Shader::Fragment);
    shader.setParameter("texture", sf::Shader::CurrentTexture);
}

void Level::update(double deltaT) {
    world_.Step(deltaT, 8, 3);
    time_ += deltaT;
    for (GameObject* object : objects_) {
        object->update(*this, deltaT);
    }
}