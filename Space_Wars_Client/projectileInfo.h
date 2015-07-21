#pragma once

static const float g_projectileVertices[] = {
	-0.2f, -0.2f, 1.0f,		// 0
	0.2f, -0.2f, 1.0f,  	// 1	
	0.2f, 0.2f, 1.0f,		// 2
	-0.2f, 0.2f, 1.0f,		// 3	
	-0.2f, -0.2f, -3.0f,	// 4
	0.2f, -0.2f, -3.0f,		// 5
	0.2f, 0.2f, -3.0f,		// 6
	-0.2f, 0.2f, -3.0f		// 7
};

static const unsigned short g_projectileIndices[] = { 
	0, 1, 2, // avant
	2, 3, 0,
	3, 2, 6, // haut
	6, 7, 3,
	7, 6, 5, // arriere
	5, 4, 7,
	1, 5, 6, // droite
	6, 2, 1,		
	4, 0, 3, // gauche
	3, 7, 4,
	4, 5, 1, // bas
	1, 0, 4
};