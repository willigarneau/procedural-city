#pragma once

#include "..\Dependencies\glew\glew.h"
#include "..\Dependencies\freeglut\freeglut.h"
#include "..\Dependencies\glm\glm\glm.hpp"
#include <iostream>

namespace House
{
	class House_Maker
	{
	public:
		House_Maker(void);
		~House_Maker(void);
				
		void creeBase(GLfloat largeur, GLfloat hauteur, GLfloat profondeur, glm::vec3 couleur);
		
		void creeToit(GLfloat largeur, GLfloat hauteur, GLfloat profondeur, glm::vec3 couleur);
	
		void creeSurface(GLfloat largeur, GLfloat hauteur, GLfloat profondeur, GLfloat iterations, bool Horizontal, bool cote);

		void creeSkybox(void);


	private:
		float m_hauteurBase;
		glm::vec3 m_sommetsBase[8];
		glm::vec3 m_couleursBase[8];
		glm::vec2 m_textureBase[8];
		const unsigned int m_indicesBase[36] = {
			0,1,2,
			1,2,3,
			4,5,6,
			5,6,7,
			2,6,7,
			2,3,7,
			0,4,5,
			0,1,5,
			1,5,7,
			1,3,7,
			0,2,4,
			2,4,6
		};

		glm::vec3 m_sommetsToit[6];
		glm::vec3 m_couleursToit[6];
		glm::vec2 m_textureToit[6];
		const unsigned int m_indicesToit[18] = {
			0,1,2,
			3,4,5,
			0,5,2,
			0,3,5,
			0,4,1,
			0,3,4
		};
		
		glm::vec3 m_sommetsSurface[4];
		glm::vec3 m_couleursSurface[4];
		glm::vec2 m_textureSurface[4];
	
		void creeSommetsBase(GLfloat largeur, GLfloat hauteur, GLfloat profondeur);
		void creeCouleursBase(glm::vec3 couleur);
		void creeTextureBase();

		void creeSommetsToit(GLfloat largeur, GLfloat hauteur, GLfloat profondeur);
		void creeCouleursToit(glm::vec3 couleur);
		void creeTextureToit();

		void creeSommetsSurface(GLfloat largeur, GLfloat hauteur, GLfloat profondeur, bool horizontal, bool cote);
		void creeTextureSurface(GLfloat iterations);

		void creeSommetsSkybox();

		

	};
}


