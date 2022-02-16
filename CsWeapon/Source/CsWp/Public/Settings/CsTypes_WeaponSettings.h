// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Types/CsTypes_Weapon.h"
#include "Debug/CsTypes_Debug.h"

#include "CsTypes_WeaponSettings.generated.h"

// FCsWeaponSettings_WeaponsRowName
#pragma region

/**
*/
USTRUCT(BlueprintType)
struct CSWP_API FCsWeaponSettings_WeaponsRowName
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName Name;

	FCsWeaponSettings_WeaponsRowName() :
		Name(NAME_None)
	{
	}
};

#pragma endregion FCsWeaponSettings_WeaponsRowName

// FCsWeaponSettings_ProjectileWeaponImpl
#pragma region

/**
*/
USTRUCT(BlueprintType)
struct CSWP_API FCsWeaponSettings_ProjectileWeaponImpl
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FECsWeaponState IdleState;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FECsWeaponState FireState;

	FCsWeaponSettings_ProjectileWeaponImpl() :
		IdleState(),
		FireState()
	{
	}

	bool IsValidChecked(const FString& Context) const
	{
		// Check IdleState is Valid.
		check(EMCsWeaponState::Get().IsValidEnumChecked(Context, IdleState));
		// Check FireState is Valid.
		check(EMCsWeaponState::Get().IsValidEnumChecked(Context, FireState));
		return true;
	}
};

#pragma endregion FCsWeaponSettings_ProjectileWeaponImpl

// FCsWeaponSettings_TraceWeaponImpl_Debug
#pragma region

/**
*/
USTRUCT(BlueprintType)
struct CSWP_API FCsWeaponSettings_TraceWeaponImpl_Debug
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FCsDebugDrawTraceShape DrawTrace;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FCsDebugDrawTraceLine DrawLineTrace;

	FCsWeaponSettings_TraceWeaponImpl_Debug() :
		DrawTrace(),
		DrawLineTrace()
	{
	}
};

#pragma endregion FCsWeaponSettings_TraceWeaponImpl_Debug

// FCsWeaponSettings_TraceWeaponImpl
#pragma region

/**
*/
USTRUCT(BlueprintType)
struct CSWP_API FCsWeaponSettings_TraceWeaponImpl
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FECsWeaponState IdleState;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FECsWeaponState FireState;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FCsWeaponSettings_TraceWeaponImpl_Debug Debug;

	FCsWeaponSettings_TraceWeaponImpl() :
		IdleState(),
		FireState(),
		Debug()
	{

	}
};

#pragma endregion FCsWeaponSettings_TraceWeaponImpl