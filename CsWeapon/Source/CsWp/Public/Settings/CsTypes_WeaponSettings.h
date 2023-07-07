// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsWp|Settings")
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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsWp|Settings")
	FECsWeaponState IdleState;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsWp|Settings")
	FECsWeaponState FireState;

	FCsWeaponSettings_ProjectileWeaponImpl() :
		IdleState(),
		FireState()
	{
	}

	bool IsValidChecked(const FString& Context) const;

	static const FCsWeaponSettings_ProjectileWeaponImpl& Get();
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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsWp|Settings")
	FCsDebugDrawTraceShape DrawTrace;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsWp|Settings")
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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsWp|Settings")
	FECsWeaponState IdleState;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsWp|Settings")
	FECsWeaponState FireState;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsWp|Settings")
	FCsWeaponSettings_TraceWeaponImpl_Debug Debug;

	FCsWeaponSettings_TraceWeaponImpl() :
		IdleState(),
		FireState(),
		Debug()
	{

	}
};

#pragma endregion FCsWeaponSettings_TraceWeaponImpl

// FCsWeaponSettings_PointWeaponImpl
#pragma region

/**
*/
USTRUCT(BlueprintType)
struct CSWP_API FCsWeaponSettings_PointWeaponImpl
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsWp|Settings")
	FECsWeaponState IdleState;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsWp|Settings")
	FECsWeaponState FireState;

	FCsWeaponSettings_PointWeaponImpl() :
		IdleState(),
		FireState()
	{
	}

	bool IsValidChecked(const FString& Context) const;

	static const FCsWeaponSettings_PointWeaponImpl& Get();
};

#pragma endregion FCsWeaponSettings_PointWeaponImpl

// FCsWeaponSettings_PointSequenceWeaponImpl
#pragma region

/**
*/
USTRUCT(BlueprintType)
struct CSWP_API FCsWeaponSettings_PointSequenceWeaponImpl
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsWp|Settings")
	FECsWeaponState IdleState;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsWp|Settings")
	FECsWeaponState FireState;

	FCsWeaponSettings_PointSequenceWeaponImpl() :
		IdleState(),
		FireState()
	{
	}

	bool IsValidChecked(const FString& Context) const;

	static const FCsWeaponSettings_PointSequenceWeaponImpl& Get();
};

#pragma endregion FCsWeaponSettings_PointSequenceWeaponImpl