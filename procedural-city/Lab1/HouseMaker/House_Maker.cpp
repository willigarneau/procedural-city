#include "House_Maker.h" 
#include<iostream>
#include<vector>

using namespace House;

House::House_Maker::House_Maker(void)
{
}

House::House_Maker::~House_Maker(void)
{
}

void House_Maker::creeBase(GLfloat largeur, GLfloat hauteur, GLfloat profondeur, glm::vec3 couleur)
{
	m_hauteurBase = hauteur/2;
	creeSommetsBase(largeur /2, hauteur /2, profondeur /2);
	creeCouleursBase(couleur);
	creeTextureBase();

	GLuint IBOBase;
	glGenBuffers(1, &IBOBase);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBOBase);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(m_indicesBase), m_indicesBase, GL_STATIC_DRAW);

}

void House::House_Maker::creeToit(GLfloat largeur, GLfloat hauteur, GLfloat profondeur, glm::vec3 couleur)
{
	creeSommetsToit(largeur/2, hauteur/2, profondeur/2);
	creeCouleursToit(couleur);
	creeTextureToit();

	GLuint IBOToit;
	glGenBuffers(1, &IBOToit);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBOToit);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(m_indicesToit), m_indicesToit, GL_STATIC_DRAW);
}

void House::House_Maker::creeSurface(GLfloat largeur, GLfloat hauteur, GLfloat profondeur, GLfloat iterations, bool horizontal, bool cote)
{
		creeSommetsSurface(largeur / 2, hauteur, profondeur / 2, horizontal, cote);
		creeTextureSurface(iterations);
	
}



void House::House_Maker::creeSommetsBase(GLfloat largeur, GLfloat hauteur, GLfloat profondeur)
{
	m_sommetsBase[0] = glm::vec3(-largeur, hauteur, -profondeur);
	m_sommetsBase[1] = glm::vec3(largeur, hauteur, -profondeur);
	m_sommetsBase[2] = glm::vec3(-largeur, -hauteur, -profondeur);
	m_sommetsBase[3] = glm::vec3(largeur, -hauteur, -profondeur);
	m_sommetsBase[4] = glm::vec3(-largeur, hauteur, profondeur);
	m_sommetsBase[5] = glm::vec3(largeur, hauteur, profondeur);
	m_sommetsBase[6] = glm::vec3(-largeur, -hauteur, profondeur);
	m_sommetsBase[7] = glm::vec3(largeur, -hauteur, profondeur);
	m_sommetsBase[8] = glm::vec3(largeur/3, -hauteur, -profondeur-0.001);
	m_sommetsBase[9] = glm::vec3(-largeur/3, -hauteur, -profondeur - 0.001);
	m_sommetsBase[10] = glm::vec3(-largeur/3, hauteur/2, -profondeur - 0.001);
	m_sommetsBase[11] = glm::vec3(largeur/3, hauteur/2, -profondeur - 0.001);

	GLuint vertexbuffer;
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(m_sommetsBase), m_sommetsBase, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);
}

void House::House_Maker::creeCouleursBase(glm::vec3 couleur)
{
	for(int i =0; i<4; i++)
	{
		m_couleursBase[i] = glm::vec3(1.0, 0.5, 0.0); 
	}
	for (int i = 4; i<8; i++)
	{
		m_couleursBase[i] = couleur;
	}
	for (int i = 8; i<12; i++)
	{
		m_couleursBase[i] = glm::vec3(0.0, 0.5, 1.0);;
	}
	
	GLuint colorbuffer;
	glGenBuffers(1, &colorbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(m_couleursBase), m_couleursBase, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);

}

void House::House_Maker::creeTextureBase()
{
	m_textureBase[0] = glm::vec2(0.0f, 1.0f);
	m_textureBase[1] = glm::vec2(1.0f, 1.0f);
	m_textureBase[2] = glm::vec2(0.0f, 0.0f);
	m_textureBase[3] = glm::vec2(1.0f, 0.0f);

	m_textureBase[4] = glm::vec2(1.0f, 1.0f);
	m_textureBase[5] = glm::vec2(0.0f, 1.0f);
	m_textureBase[6] = glm::vec2(1.0f, 0.0f);
	m_textureBase[7] = glm::vec2(0.0f, 0.0f);

	GLuint texVBO;
	glGenBuffers(1, &texVBO);
	glBindBuffer(GL_ARRAY_BUFFER, texVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(m_textureBase), m_textureBase, GL_STATIC_DRAW);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(2);


	
}

void House::House_Maker::creeSommetsToit(GLfloat largeur, GLfloat hauteur, GLfloat profondeur)
{
	m_sommetsToit[0] = glm::vec3(0.0, m_hauteurBase+hauteur, -profondeur);
	m_sommetsToit[1] = glm::vec3(-largeur, m_hauteurBase, -profondeur);
	m_sommetsToit[2] = glm::vec3(largeur, m_hauteurBase, -profondeur);;
	m_sommetsToit[3] = glm::vec3(0.0, m_hauteurBase + hauteur, profondeur);;
	m_sommetsToit[4] = glm::vec3(-largeur, m_hauteurBase, profondeur);;
	m_sommetsToit[5] = glm::vec3(largeur, m_hauteurBase, profondeur);;

	GLuint vertexbuffer;
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(m_sommetsToit), m_sommetsToit, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

}

void House::House_Maker::creeCouleursToit(glm::vec3 couleur)
{
	float r, g, b;
	glm::vec3 coul;
	

	for (int i = 0; i < 6; i++)
	{
		coul = couleur;
		r = rand() % 100 / 100.0;
		g = rand() % 100 / 100.0;
		b = rand() % 100 / 100.0;

		if (coul.r == 1.0) 
			coul.r -= r;
		else
			coul.r += r;
		if (coul.g == 1.0) 
			coul.g -= g;
		else
			coul.g += g;
		if (coul.b == 1.0)
			coul.b -= b;
		else
			coul.b += b;

		m_couleursToit[i] = coul;
	}

	GLuint colorbuffer;
	glGenBuffers(1, &colorbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(m_couleursToit), m_couleursToit, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);
	
}

void House::House_Maker::creeTextureToit()
{
	m_textureToit[0] = glm::vec2(0.0f, 1.0f);
	m_textureToit[1] = glm::vec2(0.0f, 0.0f);
	m_textureToit[2] = glm::vec2(0.0f, 0.0f);
	m_textureToit[3] = glm::vec2(1.0f, 1.0f);
	m_textureToit[4] = glm::vec2(1.0f, 0.0f);
	m_textureToit[5] = glm::vec2(1.0f, 0.0f);

	GLuint texVBO;
	glGenBuffers(1, &texVBO);
	glBindBuffer(GL_ARRAY_BUFFER, texVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(m_textureToit), m_textureToit, GL_STATIC_DRAW);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(2);
}

void House::House_Maker::creeSommetsSurface(GLfloat largeur, GLfloat hauteur, GLfloat profondeur, bool horizontal, bool cote)
{
	if (horizontal)
	{
		m_sommetsSurface[0] = glm::vec3(-largeur, hauteur, -profondeur);
		m_sommetsSurface[1] = glm::vec3(largeur, hauteur, -profondeur);
		m_sommetsSurface[2] = glm::vec3(-largeur, hauteur, profondeur);
		m_sommetsSurface[3] = glm::vec3(largeur, hauteur, profondeur);
	}
	else
	{
		if (cote == 0)
		{
			m_sommetsSurface[0] = glm::vec3(-largeur, -m_hauteurBase, profondeur);
			m_sommetsSurface[1] = glm::vec3(largeur, -m_hauteurBase, profondeur);
			m_sommetsSurface[2] = glm::vec3(-largeur, hauteur, profondeur);
			m_sommetsSurface[3] = glm::vec3(largeur, hauteur, profondeur);
		}
		else
		{
			m_sommetsSurface[0] = glm::vec3(-largeur, -m_hauteurBase, -profondeur);
			m_sommetsSurface[1] = glm::vec3(-largeur, -m_hauteurBase, profondeur);
			m_sommetsSurface[2] = glm::vec3(-largeur, hauteur, -profondeur);
			m_sommetsSurface[3] = glm::vec3(-largeur, hauteur, profondeur);
			

		}
	}

	GLuint vertexbuffer;
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(m_sommetsSurface), m_sommetsSurface, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

}


void House::House_Maker::creeTextureSurface(GLfloat iterations)
{
	m_textureSurface[0] = glm::vec2(0.0f, 0.0f);
	m_textureSurface[1] = glm::vec2(iterations, 0.0f);
	m_textureSurface[2] = glm::vec2(0.0f, iterations);
	m_textureSurface[3] = glm::vec2(iterations, iterations);


	GLuint texVBO;
	glGenBuffers(1, &texVBO);
	glBindBuffer(GL_ARRAY_BUFFER, texVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(m_textureSurface), m_textureSurface, GL_STATIC_DRAW);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(2);

}

void House::House_Maker::creeSkybox()
{
	m_sommetsBase[0] = glm::vec3(-1.0, 1.0, -1.0);
	m_sommetsBase[1] = glm::vec3(1.0, 1.0, -1.0);
	m_sommetsBase[2] = glm::vec3(-1.0, -1.0, -1.0);
	m_sommetsBase[3] = glm::vec3(1.0, -1.0, -1.0);
	m_sommetsBase[4] = glm::vec3(-1.0, 1.0, 1.0);
	m_sommetsBase[5] = glm::vec3(1.0, 1.0, 1.0);
	m_sommetsBase[6] = glm::vec3(-1.0, -1.0, 1.0);
	m_sommetsBase[7] = glm::vec3(1.0, -1.0, 1.0);

	GLuint vertexbuffer;
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(m_sommetsBase), m_sommetsBase, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

}

