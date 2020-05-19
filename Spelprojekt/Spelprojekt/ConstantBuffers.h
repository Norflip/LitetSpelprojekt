#pragma once
#include <DirectXMath.h>
#define MAX_LIGHTS 32

const int WORLD_CONSTANT_BUFFER_SLOT = 0;
__declspec(align(16))
struct WorldData
{
	DirectX::XMMATRIX mvp;
	DirectX::XMMATRIX world;
	DirectX::XMMATRIX invWorld;
	DirectX::XMMATRIX invView;
	DirectX::XMMATRIX shadowTransform;

	float time;
	float pad[3];
};

__declspec(align(16))
struct PointLight
{
	DirectX::XMFLOAT4 color;
	DirectX::XMFLOAT3 position;
	float radius;
};

const int LIGHT_CONSTANT_BUFFER_SLOT = 1;
__declspec(align(16))
struct LightData
{
	DirectX::XMMATRIX worldToView;
	DirectX::XMFLOAT4 sunColor;
	DirectX::XMFLOAT3 sunDirection;
	float sunIntensity;

	DirectX::XMMATRIX sunView;
	DirectX::XMMATRIX sunProjection;
	DirectX::XMMATRIX shadowTransform;

	DirectX::XMFLOAT3 eyePosition;
	int pointLightCount;
	PointLight pointLights[MAX_LIGHTS];

	// SSAO
	DirectX::XMFLOAT2 screenSize;
	float ssao_radius;
	float ssao_scale;
	float ssao_bias;
	float ssao_intensity;

	float ld_pad[2];
};

const int MATERIAL_CONSTANT_BUFFER_SLOT = 2;
__declspec(align(16))
struct MaterialData
{
	DirectX::XMFLOAT4 ambient;
	DirectX::XMFLOAT4 diffuse;
	DirectX::XMFLOAT4 specular;
	//DirectX::XMFLOAT4 emissive;

	float shininess;
	float md_pad[3];

	//float reflectivity;

	// bools f�r vilka textures som anv�nds
	bool hasAlbedoTexture;
	bool hasNormalTexture;

};
