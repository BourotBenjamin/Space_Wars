
#pragma once

static const float g_vaisseauVertices[] = {
	-1.f, -1.f, 1.0f,		// 0
	1.f, 0.f, 0.0f,  		// 1
	-1.f, 1.f, 1.0f,		// 3	
	-1.f, -1.f, -1.0f,		// 4
	-1.f, 1.f, -1.0f		// 7
};

static const unsigned short g_vaisseauIndices[] = {

	3, 0, 2, // base
	2, 4, 3,
	0, 1, 2,//
	2, 1, 4,
	4, 1, 3,
	3, 1, 0
};