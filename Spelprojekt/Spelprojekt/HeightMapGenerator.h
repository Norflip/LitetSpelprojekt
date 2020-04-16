#pragma once

#include <string>
#include "Mesh.h"




class TerrainGenerator
{


public:
	void generateFromHeightMap(std::string textureName, Mesh*& mesh, ID3D11Device* device);
	int getHeight() { return this->height; };
	int getWidth() { return this->width; };
	int getXzScale(){ return this->xzScale; };
	int getVerticalScaling() { return this->verticalScaling; };
	Mesh* getMesh() { return this->mesh; };
private:
	float xzScale = 1; //defines how large plane to generate
	float verticalScaling = 11.f; // height of the vertecies
	int width;
	int height;
	Mesh* mesh;
	
};