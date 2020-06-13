// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/Enum/CsEnum_uint8.h"
#include "Types/Enum/CsEnumStructMap.h"

#include "Engine/DataTable.h"

#include "CsTypes_Weapon.generated.h"
#pragma once

// WeaponState
#pragma region

USTRUCT(BlueprintType)
struct CSWP_API FECsWeaponState : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

	CS_ENUM_UINT8_BODY(FECsWeaponState)
};

CS_DEFINE_ENUM_UINT8_GET_TYPE_HASH(FECsWeaponState)

struct CSWP_API EMCsWeaponState : public TCsEnumStructMap<FECsWeaponState, uint8>
{
	CS_ENUM_STRUCT_MAP_BODY(EMCsWeaponState, FECsWeaponState, uint8)
};

namespace NCsWeaponState
{
	typedef FECsWeaponState Type;
}

#pragma endregion WeaponState

// WeaponSlot
#pragma region

USTRUCT(BlueprintType)
struct CSWP_API FECsWeaponSlot : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

	CS_ENUM_UINT8_BODY(FECsWeaponSlot)
};

CS_DEFINE_ENUM_UINT8_GET_TYPE_HASH(FECsWeaponSlot)

struct CSWP_API EMCsWeaponSlot : public TCsEnumStructMap<FECsWeaponSlot, uint8>
{
	CS_ENUM_STRUCT_MAP_BODY(EMCsWeaponSlot, FECsWeaponSlot, uint8)
};

namespace NCsWeaponSlot
{
	typedef FECsWeaponSlot Type;
}

#pragma endregion WeaponSlot

// WeaponFireMode
#pragma region

USTRUCT(BlueprintType)
struct CSWP_API FECsWeaponFireMode : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

	CS_ENUM_UINT8_BODY(FECsWeaponFireMode)
};

CS_DEFINE_ENUM_UINT8_GET_TYPE_HASH(FECsWeaponFireMode)

struct CSWP_API EMCsWeaponFireMode : public TCsEnumStructMap<FECsWeaponFireMode, uint8>
{
	CS_ENUM_STRUCT_MAP_BODY(EMCsWeaponFireMode, FECsWeaponFireMode, uint8)
};

namespace NCsWeaponFireMode 
{
	typedef FECsWeaponFireMode Type;
}

#pragma endregion WeaponFireMode

// WeaponGrip
#pragma region

USTRUCT(BlueprintType)
struct CSWP_API FECsWeaponGrip : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

	CS_ENUM_UINT8_BODY(FECsWeaponGrip)
};

CS_DEFINE_ENUM_UINT8_GET_TYPE_HASH(FECsWeaponGrip)

struct CSWP_API EMCsWeaponGrip : public TCsEnumStructMap<FECsWeaponGrip, uint8>
{
	CS_ENUM_STRUCT_MAP_BODY(EMCsWeaponGrip, FECsWeaponGrip, uint8)
};

namespace NCsWeaponGrip
{
	typedef FECsWeaponGrip Type;
}

#pragma endregion WeaponGrip

// WeaponAnim
#pragma region

USTRUCT(BlueprintType)
struct CSWP_API FECsWeaponAnim : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

	CS_ENUM_UINT8_BODY(FECsWeaponAnim)
};

CS_DEFINE_ENUM_UINT8_GET_TYPE_HASH(FECsWeaponAnim)

struct CSWP_API EMCsWeaponAnim : public TCsEnumStructMap<FECsWeaponAnim, uint8>
{
	CS_ENUM_STRUCT_MAP_BODY(EMCsWeaponAnim, FECsWeaponAnim, uint8)
};

namespace NCsWeaponAnim
{
	typedef FECsWeaponAnim Type;
}

#pragma endregion WeaponAnim

// WeaponBlendSpace
#pragma region

USTRUCT(BlueprintType)
struct CSWP_API FECsWeaponBlendSpace : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

	CS_ENUM_UINT8_BODY(FECsWeaponBlendSpace)
};

CS_DEFINE_ENUM_UINT8_GET_TYPE_HASH(FECsWeaponBlendSpace)

struct CSWP_API EMCsWeaponBlendSpace : public TCsEnumStructMap<FECsWeaponBlendSpace, uint8>
{
	CS_ENUM_STRUCT_MAP_BODY(EMCsWeaponBlendSpace, FECsWeaponBlendSpace, uint8)
};

namespace NCsWeaponBlendSpace
{
	typedef FECsWeaponBlendSpace Type;
}

#pragma endregion WeaponBlendSpace

// WeaponAnimBlueprint
#pragma region

USTRUCT(BlueprintType)
struct CSWP_API FECsWeaponAnimBlueprint : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

	CS_ENUM_UINT8_BODY(FECsWeaponAnimBlueprint)
};

CS_DEFINE_ENUM_UINT8_GET_TYPE_HASH(FECsWeaponAnimBlueprint)

struct CSWP_API EMCsWeaponAnimBlueprint : public TCsEnumStructMap<FECsWeaponAnimBlueprint, uint8>
{
	CS_ENUM_STRUCT_MAP_BODY(EMCsWeaponAnimBlueprint, FECsWeaponAnimBlueprint, uint8)
};

namespace NCsWeaponAnimBlueprint
{
	typedef FECsWeaponSound Type;
}

#pragma endregion WeaponAnimBlueprint

// WeaponSound
#pragma region

USTRUCT(BlueprintType)
struct CSWP_API FECsWeaponSound : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

	CS_ENUM_UINT8_BODY(FECsWeaponSound)
};

CS_DEFINE_ENUM_UINT8_GET_TYPE_HASH(FECsWeaponSound)

struct CSWP_API EMCsWeaponSound : public TCsEnumStructMap<FECsWeaponSound, uint8>
{
	CS_ENUM_STRUCT_MAP_BODY(EMCsWeaponSound, FECsWeaponSound, uint8)
};

namespace NCsWeaponSound
{
	typedef FECsWeaponSound Type;
}

#pragma endregion WeaponSound

// WeaponOwner
#pragma region

USTRUCT(BlueprintType)
struct CSWP_API FECsWeaponOwner : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

	CS_ENUM_UINT8_BODY(FECsWeaponOwner)
};

CS_DEFINE_ENUM_UINT8_GET_TYPE_HASH(FECsWeaponOwner)

struct CSWP_API EMCsWeaponOwner : public TCsEnumStructMap<FECsWeaponOwner, uint8>
{
	CS_ENUM_STRUCT_MAP_BODY(EMCsWeaponOwner, FECsWeaponOwner, uint8)
};

namespace NCsWeaponOwner
{
	typedef FECsWeaponOwner Type;
}

#pragma endregion WeaponOwner

// FCsWeaponPtr
#pragma region

class UObject;

USTRUCT(BlueprintType)
struct CSWP_API FCsWeaponPtr
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (MustImplement = "CsWeapon"))
	TSoftObjectPtr<UObject> Weapon;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 Load_Flags;

	UPROPERTY(Transient, BlueprintReadOnly)
	UObject* Weapon_Internal;

	FCsWeaponPtr() :
		Weapon(nullptr),
		Load_Flags(0),
		Weapon_Internal(nullptr)
	{
	}

	FORCEINLINE UObject* Get() const { return Weapon_Internal; }
};

#pragma endregion FCsWeaponPtr

// FCsWeaponEntry
#pragma region

USTRUCT(BlueprintType)
struct CSWP_API FCsWeaponEntry : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString DisplayName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FCsWeaponPtr Weapon;

	FCsWeaponEntry() :
		Name(),
		DisplayName(),
		Weapon()
	{
	}
};

#pragma endregion FCsWeaponEntry