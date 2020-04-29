#pragma once
#include "Texture.h"
#include "Shader.h"
#include <unordered_map>
#include "ConstantBuffers.h"

enum class PIXEL_TYPE
{
	VERTEX,
	PIXEL
};

constexpr size_t ALBEDO_MATERIAL_TYPE = 0;
constexpr size_t NORMAL_MATERIAL_TYPE = 1;

class Material
{
	const int CONSTANT_BUFFER_SLOT = 2;

public:
	
	Material(Shader* shader, DX11Handler& dx11);
	virtual ~Material();

	size_t GetID() const { return this->id; }

	void SetMaterialData(MaterialData materialData) { this->materialData = materialData; }
	MaterialData& GetMaterialData() { return this->materialData; }

	void SetTexture(size_t index, Texture* texture, PIXEL_TYPE type);
	Texture* GetTexture(size_t index) const;

	Shader* GetShader() const { return this->shader; }
	void Bind(ID3D11DeviceContext*);
	void Unbind(ID3D11DeviceContext*);

private:

	size_t id;
	Shader* shader;
	ID3D11Buffer* buffer;
	MaterialData materialData;

	std::unordered_map<size_t, std::pair<Texture*, PIXEL_TYPE>> textureMap;
};

static size_t material_id_counter = 0;
