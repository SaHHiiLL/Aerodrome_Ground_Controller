//
// Created by Sahil on 9/18/24.
//

#ifndef AERODROME_GROUND_CONTROLLER_GAMEOBJECT_H
#define AERODROME_GROUND_CONTROLLER_GAMEOBJECT_H


class GameObject {
public:
    virtual void update() = 0;

    virtual void draw() = 0;
};


#endif //AERODROME_GROUND_CONTROLLER_GAMEOBJECT_H
