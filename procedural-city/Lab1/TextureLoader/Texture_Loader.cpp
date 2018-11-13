
#include<iostream>
#include<fstream>
#include "Texture_Loader.h"

using namespace texCore;

Texture_Loader::Texture_Loader(void) {}
Texture_Loader::~Texture_Loader(void) {}


unsigned char* Texture_Loader::ReadImage(char * filename)
{
	
	unsigned char* image = SOIL_load_image(filename, &width, &height, &canaux, SOIL_LOAD_AUTO);
	if (0 == image)
	{
		std::cout << "SOIL loading error: '%s'\n";
		std::cout << SOIL_last_result();
	}

	return image;
}



GLuint texCore::Texture_Loader::CreateTexture2D(char * textureImageName, GLint wrapS, GLint wrapT, GLint minFilter, GLint magFilter, GLint imgFormat)
{
	GLuint newTexture;
	unsigned char* image;
	
	glGenTextures(1, &newTexture);
	glBindTexture(GL_TEXTURE_2D, newTexture); 
	//Texture wrapping				
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapS);	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapT);
	// texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);
	// Load, create texture and generate mipmaps
	image = ReadImage(textureImageName);
	glTexImage2D(GL_TEXTURE_2D, 0, canaux, width, height, 0, imgFormat, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture 

	return newTexture;
}


GLuint texCore::Texture_Loader::CreateSkyboxTexture(std::vector<char*> faces)
{
	
	GLuint textureID;
	unsigned char* image;

	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

	//wrapping
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	//filtering
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);


	for (GLuint i = 0; i < faces.size(); i++)
	{
		image = ReadImage(faces[i]);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, canaux, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
		SOIL_free_image_data(image);
	}

	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

	return textureID;

}

