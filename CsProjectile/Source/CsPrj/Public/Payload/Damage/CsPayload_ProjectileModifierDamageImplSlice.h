// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Payload/Damage/CsPayload_ProjectileModifierDamage.h"
#include "Reset/CsReset.h"

#pragma once

class UObject;
struct FCsInterfaceMap;

/**
* 
*/
struct CSPRJ_API FCsPayload_ProjectileModifierDamageImplSlice : public ICsPayload_ProjectileModifierDamage,
																public ICsReset
{
public:

	static const FName Name;

private:

	// ICsGetInterfaceMap

	FCsInterfaceMap* InterfaceMap;

public:

	// ICsPayload_ProjectileModifierDamage

	TArray<ICsDamageModifier*> Modifiers;

public:

	FCsPayload_ProjectileModifierDamageImplSlice();

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

	FORCEINLINE const TArray<ICsDamageModifier*>& GetDamageModifiers() const
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

	bool CopyFrom(const FCsPayload_ProjectileModifierDamageImplSlice* From);
};