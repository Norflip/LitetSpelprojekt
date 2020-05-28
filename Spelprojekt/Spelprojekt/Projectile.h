#pragma once
#include "Weapon.h"
#include "Gamemanager.h"
#include "Player.h"
//#include "SoundHandler.h"

class Player;

class Projectile :
	public Weapon 
{
public:
	Projectile(AssimpHandler::AssimpData modelData, WorldContext* context);
	Projectile(const Projectile& other);
	virtual ~Projectile();

	void Update(const float& deltaTime) override;

	GUIActionbar* GetWeaponSprite() override { return this->weaponSprite; } 	
	void TriggerAttack(DirectX::XMVECTOR pos, DirectX::XMVECTOR rot) override;
	void RotateProjectile(float deltaTime);	
	void PlaySoundEffect() override;
	void SetWeaponSpeed(int value) override { this->movementspeed = value; };
	float AttackDamage() override { return this->damage; }
};

