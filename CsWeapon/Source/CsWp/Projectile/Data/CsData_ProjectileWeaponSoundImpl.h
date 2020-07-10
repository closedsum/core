// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Projectile/Data/CsData_ProjectileWeaponSound.h"
#include "Managers/Sound/CsTypes_Sound.h"

struct FCsInterfaceMap;

struct CSWP_API FCsData_ProjectileWeaponSoundImpl : public ICsData_ProjectileWeaponSound
{
public:

	static const FName Name;

private:

	FCsInterfaceMap* InterfaceMap;

	FCsSound* FireSound;

public:

	FCsData_ProjectileWeaponSoundImpl();
	~FCsData_ProjectileWeaponSoundImpl();

	FORCEINLINE UObject* _getUObject() const { return nullptr; }

public:

	FORCEINLINE void SetInterfaceMap(FCsInterfaceMap* Map)
	{
		InterfaceMap = Map;
	}

// ICsGetInterfaceMap
#pragma region
public:

	FORCEINLINE FCsInterfaceMap* GetInterfaceMap() const
	{
		return InterfaceMap;
	}

#pragma endregion ICsGetInterfaceMap

public:

	FORCEINLINE void SetFireSound(FCsSound* Value)
	{
		FireSound = Value;
	}

// ICsData_ProjectileWeaponSound
#pragma region
public:

	FORCEINLINE const FCsSound& GetFireSound() const
	{
		return *FireSound;
	}

#pragma endregion ICsData_ProjectileWeaponSound
};