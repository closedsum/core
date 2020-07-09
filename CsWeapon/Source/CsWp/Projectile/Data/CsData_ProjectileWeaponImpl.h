// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Data/CsData_Weapon.h"
#include "Projectile/Data/CsData_ProjectileWeapon.h"

struct FCsInterfaceMap;

struct CSWP_API FCsData_ProjectileWeaponImpl : public ICsData_Weapon,
											   public ICsData_ProjectileWeapon
{
public:

	static const FName Name;

private:

	FCsInterfaceMap* InterfaceMap;

	bool* bDoFireOnRelease;

	bool* bFullAuto;

	int32* MaxAmmo;

	int32* ProjectilesPerShot;

	float* TimeBetweenShots;

	float* TimeBetweenAutoShots;

	float* TimeBetweenProjectilesPerShot;

public:

	FCsData_ProjectileWeaponImpl();
	~FCsData_ProjectileWeaponImpl();

	FORCEINLINE void SetDoFireOnRelease(bool* Value)
	{
		bDoFireOnRelease = Value;
	}

	FORCEINLINE void SetFullAuto(bool* Value)
	{
		bFullAuto = Value;
	}

	FORCEINLINE void SetMaxAmmo(int32* Value)
	{
		MaxAmmo = Value;
	}

	FORCEINLINE void SetProjectilesPerShot(int32* Value)
	{
		ProjectilesPerShot = Value;
	}

	FORCEINLINE void SetTimeBetweenShots(float* Value)
	{
		TimeBetweenShots = Value;
	}

	FORCEINLINE void SetTimeBetweenAutoShots(float* Value)
	{
		TimeBetweenAutoShots = Value;
	}

	FORCEINLINE void SetTimeBetweenProjectilesPerShot(float* Value)
	{
		TimeBetweenProjectilesPerShot = Value;
	}

	FORCEINLINE UObject* _getUObject() const { return nullptr; }

	// ICsGetInterfaceMap
#pragma region
public:

	FORCEINLINE FCsInterfaceMap* GetInterfaceMap() const
	{
		return InterfaceMap;
	}

#pragma endregion ICsGetInterfaceMap

	// ICsData_Weapon
#pragma region
public:

#pragma endregion ICsData_Weapon

	// ICsData_ProjectileWeapon
#pragma region
public:

	FORCEINLINE const bool& DoFireOnRelease() const
	{
		return *bDoFireOnRelease;
	}

	FORCEINLINE const bool& IsFullAuto() const
	{
		return *bFullAuto;
	}

	FORCEINLINE const int32& GetMaxAmmo() const
	{
		return *MaxAmmo;
	}

	FORCEINLINE const int32& GetProjectilesPerShot() const
	{
		return *ProjectilesPerShot;
	}

	FORCEINLINE const float& GetTimeBetweenShots() const
	{
		return *TimeBetweenShots;
	}

	FORCEINLINE const float& GetTimeBetweenAutoShots() const
	{
		return *TimeBetweenAutoShots;
	}

	FORCEINLINE const float& GetTimeBetweenProjectilesPerShot() const
	{
		return *TimeBetweenProjectilesPerShot;
	}

#pragma endregion ICsData_ProjectileWeapon
};