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


#ifndef SHOOTER_CHARACTER_H
#define SHOOTER_CHARACTER_H

#include <iostream>
#include "GameObject.h"
#include "TextureManager.h"
#include "Level.h"
#include "Ground.h"
#include "Weapon.h"


class Character : public GameObject {

    sf::Sprite sprite_;
    sf::Sprite footSprite_;

    const float friction = 99.1f;
    const float speed = 850.0f;

    float controlX = 0;
    float controlY = 0;

    Weapon weapon;

public:
    Character(Level &level, float x, float y) : GameObject(&level), weapon(&level) {
        sprite_ = TextureManager::instance().loadSprite("data/character.png");
        footSprite_ = TextureManager::instance().loadSprite("data/characterFoot.png");

        b2BodyDef BodyDef;
        BodyDef.position = b2Vec2(x / SCALE, y / SCALE);
        BodyDef.type = b2_dynamicBody;
        BodyDef.linearDamping = 9;
        b2Body *Body = level.world().CreateBody(&BodyDef);
        Body->SetFixedRotation(true);

        b2CircleShape Shape;
        Shape.m_radius = 16/SCALE;
        b2FixtureDef FixtureDef;
        FixtureDef.density = 15.f;
        FixtureDef.friction = friction;
        FixtureDef.shape = &Shape;
        FixtureDef.userData = this;
        Body->CreateFixture(&FixtureDef);

        body(Body);
        level.add(this);
    }



    virtual void render(PlayerViewport &viewport) override {
        footSprite_.setOrigin(16, 26);
        footSprite_.setPosition(SCALE * body()->GetPosition().x, SCALE * body()->GetPosition().y);
        footSprite_.setRotation(body()->GetAngle() * 180 / b2_pi);
        footSprite_.setScale((float) std::cos(level().time() * 10), 1);
        viewport.window().draw(footSprite_);

        sprite_.setOrigin(16, 26);
        sprite_.setPosition(SCALE * body()->GetPosition().x, SCALE * body()->GetPosition().y);
        sprite_.setRotation(body()->GetAngle() * 180 / b2_pi);
        viewport.window().draw(sprite_);

        viewport.view().setCenter(SCALE * body()->GetPosition().x, SCALE * body()->GetPosition().y);

        auto mousePos = sf::Mouse::getPosition(viewport.window());
        auto internalPos = viewport.window().mapPixelToCoords(mousePos);
        body()->SetTransform(body()->GetPosition(), atan2(internalPos.y / SCALE - body()->GetPosition().y, internalPos.x / SCALE - body()->GetPosition().x));
    }

    virtual void update(Level &level) override {
        for (unsigned i = 0; i < 8; i++) {
            if (sf::Joystick::isConnected(i)) {
                controlX = sf::Joystick::getAxisPosition(i, sf::Joystick::Axis::X) / 100;
                controlY = sf::Joystick::getAxisPosition(i, sf::Joystick::Axis::Y) / 100;
                float acceleration = std::sqrt(controlX * controlX + controlY * controlY);
                if (acceleration > 1)
                    acceleration = 1;

                if (acceleration > 0.2f) {
                    double rotation = std::atan2(controlY, controlX);
                    body()->ApplyForce(b2Vec2((float32) (std::cos(rotation) * speed * acceleration), (float32) (std::cos(rotation - M_PI / 2) * speed * acceleration)), body()->GetWorldCenter(), true);
                    body()->SetTransform(body()->GetPosition(), (float32) rotation);
                }

                for (unsigned j = 0; j < sf::Joystick::getButtonCount(i); j++) {
                    if (sf::Joystick::isButtonPressed(i, j)) {
                        if (j == 6) {
                            weapon.tryShoot(body()->GetPosition(), body()->GetAngle());
                        } else {

                            std::cout << "FOO " << j << std::endl;
                        }
                    }
                }
            } else {
                if (i != 0)
                    return;
                break;
            }
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            weapon.tryShoot(body()->GetPosition(), body()->GetAngle());
        }

        {
            bool keyPressed = false;
            controlX = 0;
            controlY = 0;

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
                keyPressed = true;
                controlX -= 1;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                keyPressed = true;
                controlX += 1;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
                keyPressed = true;
                controlY -= 1;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
                keyPressed = true;
                controlY += 1;
            }

            if (keyPressed) {
                double rotation = std::atan2(controlY, controlX);
                body()->ApplyForce(b2Vec2((float32) (std::cos(rotation) * speed), (float32) (std::cos(rotation - M_PI / 2) * speed)), body()->GetWorldCenter(), true);
                // TODO was replaced my mouse, delete this? body()->SetTransform(body()->GetPosition(), (float32) rotation);
            }
        }

    }
};


#endif //SHOOTER_CHARACTER_H
