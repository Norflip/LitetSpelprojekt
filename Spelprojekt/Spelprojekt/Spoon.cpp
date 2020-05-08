#include "Spoon.h"

Spoon::Spoon(const char* name, Terrain* terrain, DX11Handler& dx11, Shader* defaultShader, DirectX::XMVECTOR position, DirectX::XMVECTOR rotation)
{
	GetTransform().SetPosition(position);
	GetTransform().SetRotation(rotation);
	Object* slev = AssimpHandler::loadFbxObject(name, dx11, defaultShader);
	SetMesh(slev->GetMesh());
	SetMaterial(slev->GetMaterial());
	//this->movementspeeds = 3;
	this->direction = rotation; // makes us shoot in the direction of the object initial rotation

	this->weaponSprite = new GUIActionbar(dx11, "Sprites/Slev.png", 0.0f, 0.0f);
	this->attack = false;
	this->damage = 5.0f;
	this->WeaponTypeName = "Slev";
}

Spoon::Spoon(const Spoon& other)
{
	GetTransform().SetPosition(other.GetTransform().GetPosition());
	GetTransform().SetRotation(other.GetTransform().GetRotation());
	this->SetMesh(other.GetMesh());
	this->SetMaterial(other.GetMaterial());
	this->direction = other.direction;

	this->weaponSprite = other.weaponSprite;
	this->attack = false;
	this->damage = other.damage;
	this->WeaponTypeName = other.WeaponTypeName;
}

Spoon::~Spoon()
{
	
}

void Spoon::HasAttacked(DirectX::XMVECTOR pos, DirectX::XMVECTOR rot)
{
	GetTransform().SetPosition(pos);
	GetTransform().SetRotation(rot);	

	this->attack = true;
}

void Spoon::MeleeAttack(float deltaTime)
{
	// do melee stuff here
	nextPos = { (GetTransform().GetPosition().m128_f32[0] + (-std::sinf(direction.m128_f32[1]) * 30) * deltaTime) ,GetTransform().GetPosition().m128_f32[1], (GetTransform().GetPosition().m128_f32[2] + (-std::cosf(direction.m128_f32[1]) * 30) * deltaTime) };	// 30 = speed
	GetTransform().SetPosition(nextPos);
}

void Spoon::FollowPlayer(DirectX::XMVECTOR pos, DirectX::XMVECTOR rot)
{
	GetTransform().SetPosition(pos);
	GetTransform().SetRotation(rot);
}

void Spoon::Update(const float& deltaTime)
{	
	//if (attack)
	//	MeleeAttack(deltaTime);
}