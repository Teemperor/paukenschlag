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


#include <Hideaway.h>
#include "Soldier.h"
#include "Utils.h"


void Soldier::update(Level& level, double deltaT) {

    if (isPlayer_) {

        Utils::animateTo(alpha_, hidden() ? 0.55 : 1, deltaT, 3);

        for (unsigned i = 0; i < 8; i++) {
            if (sf::Joystick::isConnected(i)) {
                controlX = sf::Joystick::getAxisPosition(i, sf::Joystick::Axis::X) / 100;
                controlY = sf::Joystick::getAxisPosition(i, sf::Joystick::Axis::Y) / 100;
                float acceleration = std::sqrt(controlX * controlX + controlY * controlY);
                if (acceleration > 1)
                    acceleration = 1;

                if (acceleration > 0.2f) {
                    double rotation = std::atan2(controlY, controlX);
                    walkAngle = rotation;
                    body()->ApplyForce(b2Vec2((float32) (std::cos(rotation) * runSpeed * acceleration), (float32) (std::cos(rotation - M_PI / 2) *
                                                                                                                   runSpeed * acceleration)), body()->GetWorldCenter(), true);
                    body()->SetTransform(body()->GetPosition(), (float32) rotation);
                }

                for (unsigned j = 0; j < sf::Joystick::getButtonCount(i); j++) {
                    if (sf::Joystick::isButtonPressed(i, j)) {
                        if (j == 6) {
                            b2Vec2 target = position();
                            target.x += std::cos(body()->GetAngle());
                            target.y += std::sin(body()->GetAngle());
                            currentItem().tryUse(level, body()->GetPosition(), target);
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
            if (currentItem().isAutomatic())
                currentItem().tryUse(level, body()->GetPosition(), aimTarget);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) {
            selectedItem_ = 0;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) {
            selectedItem_ = 1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) {
            selectedItem_ = 2;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4)) {
            selectedItem_ = 3;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
            currentItem().reload(level);
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
                walkAngle = rotation;

                double speed = walkSpeed;
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
                    speed = runSpeed;

                body()->ApplyForce(b2Vec2((float32) (std::cos(rotation) * speed),
                                          (float32) (std::cos(rotation - M_PI / 2) * speed)), body()->GetWorldCenter(), true);

                // TODO was replaced my mouse, delete this? body()->SetTransform(body()->GetPosition(), (float32) rotation);

            }
            if (controlX != 0 || controlY != 0) {

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
                    legAnimation_.state(LegAnimation::State::Walking);
                else
                    legAnimation_.state(LegAnimation::State::Running);
            }
            else
                legAnimation_.state(LegAnimation::State::Standing);
        }
    } else {
        if (usedHideaways != 0) {
            bool playerNear = false;

            for (Soldier* player : level.players()) {
                if (Utils::distance(player->position(), position()) < 5) {
                    playerNear = true;
                }
            }
            if (!playerNear)
                visible_ = false;
        }

        Utils::animateTo(alpha_, visible_ ? 1 : 0, deltaT, 3);

        if (!dead_) {
            suspicionIndicator_.update(level, deltaT);

            ai_.update(*this, level, deltaT);
            double headRotationDiff = headRotationTarget - headRotation;

            double headRotationChange = deltaT;

            if (std::abs(headRotationDiff) < headRotationChange) {
                headRotation = headRotationTarget;
            } else {
                if (headRotationTarget > headRotation) {
                    headRotation += headRotationChange;
                } else {
                    headRotation -= headRotationChange;
                }
            }
        }
    }

}

void Soldier::shoot(b2Vec2 target) {
    currentItem().tryUse(level(), position(), target);
}

void Soldier::initBodyAnimation() {
    sf::Sprite idleSprite = TextureManager::instance().loadSprite("data/guard/idle.png");
    idleSprite.setOrigin(20, 20);
    bodyAnimation_.idleSprite(idleSprite);

    sf::Sprite pistolSprite = TextureManager::instance().loadSprite("data/guard/pistol.png");
    pistolSprite.setOrigin(19, 19);
    bodyAnimation_.pistolSprite(pistolSprite, {24, 6});

    sf::Sprite rifleSprite = TextureManager::instance().loadSprite("data/guard/rifle.png");
    rifleSprite.setOrigin(19, 19);
    bodyAnimation_.rifleSprite(rifleSprite, {21, 9});

    sf::Sprite knifeSprite = TextureManager::instance().loadSprite("data/guard/knife.png");
    knifeSprite.setOrigin(19, 19);
    bodyAnimation_.knifeSprite(knifeSprite, {17, 0});
}

void Soldier::startContact(GameObject* other) {
    if (dynamic_cast<Hideaway*>(other)) {
        usedHideaways++;
    }
}

void Soldier::endContact(GameObject* other) {
    if (dynamic_cast<Hideaway*>(other)) {
        usedHideaways--;
    }
}

Soldier::Soldier(Level &level, float x, float y) : GameObject(&level), legAnimation_("data/guard/legs.png", 14, 12) {
    sprite_ = TextureManager::instance().loadSprite("data/guard/idle.png");
    sprite_.setOrigin(20, 20);

    headSprite_ = TextureManager::instance().loadSprite("data/guard/helmet.png");
    headSprite_.setOrigin(9, 8);

    deadSprite_ = TextureManager::instance().loadSprite("data/guard/dead.png");
    deadSprite_.setOrigin(40, 45);

    initBodyAnimation();

    b2BodyDef BodyDef;
    BodyDef.position = b2Vec2(x / SCALE, y / SCALE);
    BodyDef.type = b2_dynamicBody;
    BodyDef.linearDamping = 9;
    b2Body *Body = level.world().CreateBody(&BodyDef);
    Body->SetFixedRotation(true);

    b2CircleShape Shape;
    Shape.m_radius = 16 / SCALE;
    b2FixtureDef FixtureDef;
    FixtureDef.density = 15.f;
    FixtureDef.filter.categoryBits = objectCategory::ENEMY;
    FixtureDef.filter.maskBits = ~objectCategory::ENEMY;
    FixtureDef.friction = friction;
    FixtureDef.shape = &Shape;
    FixtureDef.userData = this;
    Body->CreateFixture(&FixtureDef);

    body(Body);
    level.add(this);
}

void Soldier::render(PlayerViewport &viewport) {
    if (dead_) {
        deadSprite_.setPosition(SCALE * body()->GetPosition().x, SCALE * body()->GetPosition().y);
        deadSprite_.setRotation(body()->GetAngle() * 180 / b2_pi);
        viewport.window().draw(deadSprite_);
    } else {
        if (!isPlayer_)
            fovIndicator.render(viewport, position(), getViewDirection(), ai_.fieldOfView(), ai_.suspicion(), alpha_);

        legAnimation_.render(position(), body()->GetAngle(), viewport, alpha_);

        bodyAnimation_.draw(currentItem(), viewport, position(), body()->GetAngle(), alpha_);

        headSprite_.setPosition(SCALE * body()->GetPosition().x, SCALE * body()->GetPosition().y);
        headSprite_.setRotation((body()->GetAngle() + headRotation) * 180 / b2_pi);
        headSprite_.setColor(sf::Color(255, 255, 255, (sf::Uint8) (255 * alpha_)));
        viewport.window().draw(headSprite_);

        if (isPlayer_) {

            auto mousePos = sf::Mouse::getPosition(viewport.window());
            auto internalPos = viewport.window().mapPixelToCoords(mousePos);
            aimTarget.x = internalPos.x / SCALE;
            aimTarget.y = internalPos.y / SCALE;
            body()->SetTransform(body()->GetPosition(), std::atan2(internalPos.y / SCALE - body()->GetPosition().y, internalPos.x / SCALE - body()->GetPosition().x));

        }

        //suspicionIndicator_.draw(viewport, SCALE * body()->GetPosition().x, SCALE * body()->GetPosition().y - 40, ai_.suspicion());
    }
}

void Soldier::setIsPlayer(bool isPlayer) {
    if (isPlayer == isPlayer_)
        return;

    isPlayer_ = isPlayer;
    if (isPlayer) {
        level().addPlayer(this);
    }
}