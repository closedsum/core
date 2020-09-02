// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Projectile/Payload/CsPayload_ProjectileModifierStatusEffect.h"
#include "Reset/CsReset.h"

#pragma once

class UObject;
struct FCsInterfaceMap;
struct ICsStatusEffectModifier;

/**
* 
*/
struct CSSE_API FCsPayload_ProjectileModifierStatusEffectImplSlice : public ICsPayload_ProjectileModifierStatusEffect,
																	 public ICsReset
{
public:

	static const FName Name;

private:

	// ICsGetInterfaceMap

	FCsInterfaceMap* InterfaceMap;

public:

	// ICsPayload_ProjectileModifierDamage

	TArray<ICsStatusEffectModifier*> Modifiers;

public:

	FCsPayload_ProjectileModifierStatusEffectImplSlice();

// ICsGetInterfaceMap
#pragma region
public:

	FORCEINLINE FCsInterfaceMap* GetInterfaceMap() const
	{
		return InterfaceMap;
	}

#pragma endregion ICsGetInterfaceMap

public:

	void SetInterfaceMap(FCsInterfaceMap* InInterfaceMap);

// ICsPayload_ProjectileModifierDamage
#pragma region
public:

	FORCEINLINE const TArray<ICsStatusEffectModifier*>& GetDamageModifiers() const
	{
		return Modifiers;
	}

#pragma endregion ICsPayload_ProjectileModifierDamage

// ICsReset
#pragma region
public:

	void Reset();

#pragma endregion ICsReset

public:

	bool CopyFrom(const FCsPayload_ProjectileModifierStatusEffectImplSlice* From);
};