#pragma once
#include "Transform.h"
//#include "Renderer.h"
#include "Mesh.h"
#include "Material.h"
#include "AABB.h"
class Renderer;


enum class ObjectLayer
{
	None = 0,
	Enviroment = 1 << 0,
	Enemy = 1 << 1,
	Projectile = 1 << 2,
	Player = 1 << 3,
	Pickups = 1 << 4,
	Any = Enviroment | Enemy | Projectile | Player | Pickups
};

class Object
{
public:

	Object();
	Object(const Object& other);
	Object(ObjectLayer layer, Mesh* mesh, Material* material);
	virtual ~Object();

	const Transform& GetTransform() const  { return this->transform; }
	Transform& GetTransform() { return this->transform; }
	void SetMaterial(Material* material) { this->material = material; }
	Material* GetMaterial() const { return this->material; }
	void SetMesh(Mesh* mesh);
	Mesh* GetMesh() const { return this->mesh; }

	AABB GetLocalBounds() const { return this->localBounds; }
	AABB GetWorldBounds() const;

	void UpdateLocalBounds();
	size_t GetID() const { return this->id; }

	virtual void Render(Renderer*, DirectX::XMMATRIX view, DirectX::XMMATRIX projection);
	virtual void Update(const float& deltaTime) {};
	virtual void FixedUpdate(const float& fixedDeltaTime) {};

	ObjectLayer GetLayer() { return this->layer; }
	void SetLayer(ObjectLayer layer) { this->layer = layer; }

	void SetEnabled(bool enabled) { this->enabled = enabled; }
	bool IsEnabled() const { return this->enabled; }

	bool isWater = false;
	
private:
	Transform transform;
	AABB localBounds;
	ObjectLayer layer;
	Material* material;
	Mesh* mesh;
	size_t id;
	bool enabled;
};

static size_t object_id_counter = 0;
