/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#include <ResourceManager.h>

#include <iostream>
#include <sstream>
#include <fstream>

#include <soil.h>
#include "utils/filesystem.h"

// Instantiate static variables
std::map<std::string, Texture>    ResourceManager::Textures;
std::map<std::string, Shader>       ResourceManager::Shaders;

std::list<std::string> supported_texture_extensions = { ".jpg", ".png", ".bmp" };

std::map<std::string, Texture> ResourceManager::GetTexturesBank()
{
	return Textures;
}

unsigned int ResourceManager::CountTextures()
{
	return Textures.size();
}

int ResourceManager::LoadTextures(const std::string& path)
{
	std::string texture_filename;
	std::string texture_extension;
	unsigned int texture_count = 0;

	for (auto & filepath : GetRecursiveFilePathsFromDirectory(path))
	{
		bool is_extension_valid = false;

		if (!filepath.has_extension()) continue;

		texture_filename = filepath.filename().string();
		texture_extension = filepath.extension().string();

		// TODO: make a supported extensions list
		for (auto &supported_extension : supported_texture_extensions)
		{
			if (texture_extension == supported_extension) // extension found
			{
				is_extension_valid = true; // valid extension
			}
		}

		if (!is_extension_valid) continue;

		ResourceManager::LoadTexture((filepath).string().c_str(), GL_TRUE, remove_extension(texture_filename));
		texture_count++;
	}

	return texture_count++;
}

int ResourceManager::LoadShaders(const std::string& path)
{
	// Load Shaders (program, vertex, fragment)
	std::string vertex_filename;
	std::string fragment_filename;
	unsigned int file_counter = 0;
	unsigned int shaders_count = 0;

	for (auto & filepath : GetFilePathsFromDirectory(path))
	{
		if (filepath.extension().string() == ".vert")
		{
			vertex_filename = filepath.filename().string();
		}
		else if (filepath.extension().string() == ".frag")
		{
			fragment_filename = filepath.filename().string();
		}

		file_counter++;

		if (vertex_filename.empty() || fragment_filename.empty() || file_counter != 2) {}
		else
		{
			ResourceManager::LoadShader((path + "\\" + vertex_filename).c_str(), (path + "\\" + fragment_filename).c_str(), nullptr, remove_extension(filepath.filename().string()));
			shaders_count++;
		}

		if (file_counter == 2)
		{
			vertex_filename = "";
			fragment_filename = "";
			file_counter = 0;
		}

		/*std::cout << i.string() << std::endl;
		std::cout << i.filename() << std::endl;
		std::cout << remove_extension(i.filename().string()) << std::endl;
		std::cout << i.extension() << std::endl;
		std::cout << "------------" << std::endl;*/
	}

	return shaders_count;
}

Shader ResourceManager::LoadShader(const GLchar *vShaderFile, const GLchar *fShaderFile, const GLchar *gShaderFile, std::string name)
{
	Shaders[name] = loadShaderFromFile(vShaderFile, fShaderFile, gShaderFile);
	return Shaders[name];
}

Shader ResourceManager::GetShader(std::string name)
{
	return Shaders[name];
}

Texture ResourceManager::LoadTexture(const GLchar *file, GLboolean alpha, std::string name)
{
	Textures[name] = loadTextureFromFile(file, alpha);
	return Textures[name];
}

Texture ResourceManager::GetTexture(std::string name)
{
	return Textures[name];
}

void ResourceManager::Clear()
{
	// (Properly) delete all shaders	
	for (auto iter : Shaders)
		glDeleteProgram(iter.second.ID);
	// (Properly) delete all textures
	for (auto iter : Textures)
		glDeleteTextures(1, &iter.second.ID);
}

Shader ResourceManager::loadShaderFromFile(const GLchar *vShaderFile, const GLchar *fShaderFile, const GLchar *gShaderFile)
{
	// 1. Retrieve the vertex/fragment source code from filePath
	std::string vertexCode;
	std::string fragmentCode;
	std::string geometryCode;
	try
	{
		// Open files
		std::ifstream vertexShaderFile(vShaderFile);
		std::ifstream fragmentShaderFile(fShaderFile);
		std::stringstream vShaderStream, fShaderStream;
		// Read file's buffer contents into streams
		vShaderStream << vertexShaderFile.rdbuf();
		fShaderStream << fragmentShaderFile.rdbuf();
		// close file handlers
		vertexShaderFile.close();
		fragmentShaderFile.close();
		// Convert stream into string
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
		// If geometry shader path is present, also load a geometry shader
		if (gShaderFile != nullptr)
		{
			std::ifstream geometryShaderFile(gShaderFile);
			std::stringstream gShaderStream;
			gShaderStream << geometryShaderFile.rdbuf();
			geometryShaderFile.close();
			geometryCode = gShaderStream.str();
		}
	}
	catch (std::exception e)
	{
		std::cout << "ERROR::SHADER: Failed to read shader files" << std::endl;
	}
	const GLchar *vShaderCode = vertexCode.c_str();
	const GLchar *fShaderCode = fragmentCode.c_str();
	const GLchar *gShaderCode = geometryCode.c_str();
	// 2. Now create shader object from source code
	Shader shader;
	shader.Compile(vShaderCode, fShaderCode, gShaderFile != nullptr ? gShaderCode : nullptr);
	return shader;
}

Texture ResourceManager::loadTextureFromFile(const GLchar *file, GLboolean alpha)
{
	// Create Texture object
	Texture texture;
	if (alpha)
	{
		texture.Internal_Format = GL_RGBA;
		texture.Image_Format = GL_RGBA;
	}
	// Load image
	int width, height, num_channels; // TODO: Include this in Texture structure
	unsigned char* image = SOIL_load_image(file, &width, &height, &num_channels, texture.Image_Format == GL_RGBA ? SOIL_LOAD_RGBA : SOIL_LOAD_RGB);
	// Now generate texture
	texture.Generate(width, height, image);
	// And finally free image data
	SOIL_free_image_data(image);
	return texture;
}