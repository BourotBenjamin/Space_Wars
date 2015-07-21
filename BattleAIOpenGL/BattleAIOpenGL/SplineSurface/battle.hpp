#ifndef _BATTLE_HPP_
#define _BATTLE_HPP_
#include "Army.hpp"

class MyGLWidget;

//Run a fight between the two given armies, and store their score in the given variable.
void fight(const Army& a, const Army& b, int& scoreA, int& scoreB, MyGLWidget* gl, bool log = false);



#endif