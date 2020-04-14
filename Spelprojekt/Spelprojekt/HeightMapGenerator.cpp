#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "HeightMapGenerator.h"
#include "DX11Handler.h"
void TerrainGenerator::generateFromHeightMap(std::string textureName, Mesh*& mesh, ID3D11Device* device)
{
	// follow this shit to the dot https://www.braynzarsoft.net/viewtutorial/q16390-30-heightmap-terrain
	int bpp = sizeof(uint8_t) * 4;
	width = 200;
	height = 200;
	bpp = sizeof(uint8_t) * 4; //RGBA, bits per pixel
	uint8_t* rgb_image = stbi_load(textureName.data(), &width, &height, &bpp, 1);
	float sizeMultiplier = scaling;
	DirectX::XMFLOAT3 temp0;
	std::vector<MeshVertex> vertList;
	MeshVertex test;
	std::vector<unsigned int> indexList;
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			test.position.x = x * sizeMultiplier; //Vertex locations on x and y axis loaded here.
			test.position.z = y * sizeMultiplier;
			
			test.position.y = (float)rgb_image[y * width + x + 0] / 255.f;  //Load in height of said vertex, only returns 0-1.
			test.position.y *= verticalScaling;
			test.position.y -= 10;
			test.normal = DirectX::XMFLOAT3(0.0f, 1.0f, 0.0f); // needs to be calculated when we create a quad
			test.uv = DirectX::XMFLOAT2(0.0f, 0.0f); // needs to be calculated when we create a quad
			test.tangent = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);

			vertList.push_back(test);
			indexList.push_back((height * y) + x);
		}

	}
	delete rgb_image;

	int NumVertices = width * height;
	int NumFaces = (width - 1) * (height - 1) * 2;
	//std::vector<int> indices(NumFaces * 3);
	int k = 0;
	int texUIndex = 0;
	int texVIndex = 0;
	for (int i = 0; i < width - 1; i++)
	{
		for (int j = 0; j < height - 1; j++)
		{
			//indices[k] = i * height + j;        // Bottom left of quad

			vertList.at(i * height + j).uv = DirectX::XMFLOAT2(texUIndex + 0.0f, texVIndex + 1.0f);

			vertList.at(i * height + j + 1).uv = DirectX::XMFLOAT2(texUIndex + 1.0f, texVIndex + 1.0f);

			vertList.at((i + 1) * height + j).uv = DirectX::XMFLOAT2(texUIndex + 0.0f, texVIndex + 0.0f);

			vertList.at((i + 1) * height + j).uv = DirectX::XMFLOAT2(texUIndex + 0.0f, texVIndex + 0.0f);

			vertList.at(i * height + j + 1).uv = DirectX::XMFLOAT2(texUIndex + 1.0f, texVIndex + 1.0f);

			vertList.at((i + 1) * height + j + 1).uv = DirectX::XMFLOAT2(texUIndex + 1.0f, texVIndex + 0.0f);

			k += 6; // next quad

			texUIndex++;
		}
		texUIndex = 0;
		texVIndex++;
	}

	mesh = MeshCreator::CreateMesh(vertList, indexList, device);

	//Compute vertex normals (normal Averaging)
	/*DirectX::XMVECTOR normalSum = DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
	int facesUsing = 0;
	float tX;
	float tY;
	float tZ;*/

}
