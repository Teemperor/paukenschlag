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
    "    vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);\n"
    "    vec4 alphaPixel = texture2D(alphaMap, gl_TexCoord[0].xy);\n"
    "    gl_FragColor = gl_Color * alphaPixel.w * pixel;\n" //  gl_Color * alphaPixel.w * pixel
    "}";

void Level::add(Character* object) {
    objects_.push_back(object);
    players_.push_back(object);
}

void Level::render(PlayerViewport& viewport) {

    alphaTexture.setView(viewport.window().getView());


    renderTexture.setView(viewport.window().getView());
    sf::View viewBak = viewport.window().getView();
    viewport.window().setView(viewport.window().getDefaultView());

    for (LevelArea& area : areas_) {
        area.draw(renderTexture, viewport.window(), shader, alphaTexture);
    }
    viewport.window().setView(viewBak);

    //viewport.window().draw(sf::Sprite(alphaTexture.getTexture()));

    for (auto iter = objects_.rbegin(); iter != objects_.rend(); iter++) {
        (*iter)->render(viewport);
    }

}

Level::Level() : world_(b2Vec2(0.f, 0.f)) {
    dirtySprite = TextureManager::instance().loadSprite("data/floor/asphalt.png");
    alphaSprite = TextureManager::instance().loadSprite("data/floor/alpha.png");
    sandSprite = TextureManager::instance().loadSprite("data/floor/sand.png");
    world_.SetContactListener(this);

    assert(alphaTexture.create(1700, 900));
    assert(renderTexture.create(1700, 900));

    shader.loadFromMemory(fragmentShader, sf::Shader::Fragment);
}

void Level::update(double deltaT) {
    world_.Step((float32) deltaT, 8, 3);
    time_ += deltaT;
    for (GameObject* object : objects_) {
        object->update(*this, deltaT);
    }
}