/*
 * author: Dylan Campbell
 * contact: campbell.dyl@gmail.com
 * project: 2d game engine
 *
 * This program contains source code from Gustavo Pezzi's "C++ 2D Game Engine
 * Development" course, found here: https://pikuma.com/courses
*/

// -----------------------------------------------------------------------------
// healthcomponent.h
// header file for Health Component
// -----------------------------------------------------------------------------
#ifndef HEALTHCOMPONENT_H
#define HEALTHCOMPONENT_H

struct HealthComponent {
    int healthPercentage;

    HealthComponent(int healthPercentage = 0) {
        this->healthPercentage = healthPercentage;
    }
};

#endif
