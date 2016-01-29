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


#include "Character.h"
#include "Hideaway.h"

void Character::startContact(GameObject* other) {
    if (dynamic_cast<Hideaway*>(other)) {
        usedHideaways++;
    }
}

void Character::endContact(GameObject* other) {
    if (dynamic_cast<Hideaway*>(other)) {
        usedHideaways--;
    }
}

void Character::update(Level &level, double deltaT) {
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
                body()->ApplyForce(b2Vec2((float32) (std::cos(rotation) * speed * acceleration), (float32) (std::cos(rotation - M_PI / 2) * speed * acceleration)), body()->GetWorldCenter(), true);
                body()->SetTransform(body()->GetPosition(), (float32) rotation);
            }

            for (unsigned j = 0; j < sf::Joystick::getButtonCount(i); j++) {
                if (sf::Joystick::isButtonPressed(i, j)) {
                    if (j == 6) {
                        currentItem().tryUse(level, body()->GetPosition(), body()->GetAngle());
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
        currentItem().tryUse(level, body()->GetPosition(), body()->GetAngle());
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
            body()->ApplyForce(b2Vec2((float32) (std::cos(rotation) * speed), (float32) (std::cos(rotation - M_PI / 2) * speed)), body()->GetWorldCenter(), true);
            // TODO was replaced my mouse, delete this? body()->SetTransform(body()->GetPosition(), (float32) rotation);
        }
        if (controlX != 0 || controlY != 0)
            legAnimation_.state(LegAnimation::State::Running);
        else
            legAnimation_.state(LegAnimation::State::Standing);
    }
}