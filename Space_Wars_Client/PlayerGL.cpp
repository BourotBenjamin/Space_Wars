#include "PlayerGL.h"


PlayerGL::PlayerGL()
{
}


PlayerGL::~PlayerGL()
{
}

void PlayerGL::moveBackward()
{
	pos -= orientation;
}