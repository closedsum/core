// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Types
#include "CsMacro_StructOps.h"
#include "Types/Enum/CsEnum_uint8.h"
#include "Types/Enum/CsEnumStructMap.h"
// Log
#include "Utility/CsWpLog.h"
// Data
#include "Data/CsTableRowBase_Data.h"

#include "CsTypes_Weapon.generated.h"

// Weapon
#pragma region

USTRUCT(BlueprintType)
struct CSWP_API FECsWeapon : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

	CS_ENUM_UINT8_BODY(FECsWeapon)
};

CS_DEFINE_ENUM_UINT8_GET_TYPE_HASH(FECsWeapon)

struct CSWP_API EMCsWeapon : public TCsEnumStructMap<FECsWeapon, uint8>
{
	CS_ENUM_STRUCT_MAP_BODY(EMCsWeapon, FECsWeapon, uint8)
};

class UObject;

namespace NCsWeapon
{
	typedef EMCsWeapon EnumMapType;
	typedef FECsWeapon Type;

	FORCEINLINE void Create(const FString& Name, const bool& UserDefinedEnum) { EnumMapType::Get().Create(Name, UserDefinedEnum); }
	FORCEINLINE void CreateCustom(const FString& Name, const FString& DisplayName, const bool& UserDefinedEnum) { EnumMapType::Get().Create(Name, DisplayName, UserDefinedEnum); }
	FORCEINLINE bool IsValidEnum(const FString& Name) { return EnumMapType::Get().IsValidEnum(Name); }
	FORCEINLINE bool IsValidEnumByDisplayName(const FString& DisplayName) { return EnumMapType::Get().IsValidEnumByDisplayName(DisplayName); }

	CSWP_API void FromEnumSettings(const FString& Context);

	CSWP_API void FromDataTable(const FString& Context, UObject* ContextRoot);

	CSWP_API void PopulateEnumMapFromSettings(const FString& Context, UObject* ContextRoot);

	CSWP_API void GetSafeFromLevel(const FString& Context, const UObject* WorldContext, TSet<FECsWeapon>& OutWeaponTypes, void(*Log)(const FString&) = &NCsWeapon::FLog::Warning);
}

#pragma endregion Weapon

// FCsData_ECsWeapon
#pragma region

USTRUCT(BlueprintType)
struct CSWP_API FCsData_ECsWeapon
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsWp")
	FECsWeapon Value;

	FCsData_ECsWeapon() :
		Value()
	{
	}

	FORCEINLINE FECsWeapon* GetPtr() { return &Value; }
};

#pragma endregion FCsData_ECsWeapon

// WeaponClass
#pragma region

USTRUCT(BlueprintType)
struct CSWP_API FECsWeaponClass : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

	CS_ENUM_UINT8_BODY(FECsWeaponClass)
};

CS_DEFINE_ENUM_UINT8_GET_TYPE_HASH(FECsWeaponClass)

struct CSWP_API EMCsWeaponClass : public TCsEnumStructMap<FECsWeaponClass, uint8>
{
	CS_ENUM_STRUCT_MAP_BODY(EMCsWeaponClass, FECsWeaponClass, uint8)
};

class UObject;

namespace NCsWeaponClass
{
	typedef EMCsWeaponClass EnumMapType;
	typedef FECsWeaponClass Type;

	FORCEINLINE void Create(const FString& Name, const bool& UserDefinedEnum) { EnumMapType::Get().Create(Name, UserDefinedEnum); }
	FORCEINLINE void CreateCustom(const FString& Name, const FString& DisplayName, const bool& UserDefinedEnum) { EnumMapType::Get().Create(Name, DisplayName, UserDefinedEnum); }
	FORCEINLINE bool IsValidEnum(const FString& Name) { return EnumMapType::Get().IsValidEnum(Name); }
	FORCEINLINE bool IsValidEnumByDisplayName(const FString& DisplayName) { return EnumMapType::Get().IsValidEnumByDisplayName(DisplayName); }

	CSWP_API void FromEnumSettings(const FString& Context);

	CSWP_API void FromDataTable(const FString& Context, UObject* ContextRoot);

	CSWP_API void PopulateEnumMapFromSettings(const FString& Context, UObject* ContextRoot);
}

#pragma endregion WeaponClass

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
	typedef EMCsWeaponState EnumMapType;
	typedef FECsWeaponState Type;

	FORCEINLINE void Create(const FString& Name, const bool& UserDefinedEnum) { EnumMapType::Get().Create(Name, UserDefinedEnum); }
	FORCEINLINE void CreateCustom(const FString& Name, const FString& DisplayName, const bool& UserDefinedEnum) { EnumMapType::Get().Create(Name, DisplayName, UserDefinedEnum); }
	FORCEINLINE bool IsValidEnum(const FString& Name) { return EnumMapType::Get().IsValidEnum(Name); }
	FORCEINLINE bool IsValidEnumByDisplayName(const FString& DisplayName) { return EnumMapType::Get().IsValidEnumByDisplayName(DisplayName); }

	CSWP_API void FromEnumSettings(const FString& Context);

	CSWP_API void PopulateEnumMapFromSettings(const FString& Context, UObject* ContextRoot);
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

// WeaponData
#pragma region

USTRUCT(BlueprintType)
struct CSWP_API FECsWeaponData : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

	CS_ENUM_UINT8_BODY(FECsWeaponData)
};

CS_DEFINE_ENUM_UINT8_GET_TYPE_HASH(FECsWeaponData)

struct CSWP_API EMCsWeaponData : public TCsEnumStructMap<FECsWeaponData, uint8>
{
	CS_ENUM_STRUCT_MAP_BODY(EMCsWeaponData, FECsWeaponData, uint8)
};

namespace NCsWeaponData
{
	typedef FECsWeaponData Type;
	typedef EMCsWeaponData EnumMapType;

	extern CSWP_API const Type Weapon;
	extern CSWP_API const Type ProjectileWeapon;
	extern CSWP_API const Type ProjectileWeaponSound;
}

#pragma endregion WeaponData

// FCsWeaponPtr
#pragma region

class UObject;

USTRUCT(BlueprintType)
struct CSWP_API FCsWeaponPtr
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsWp", meta = (MustImplement = "/Script.CsWp.CsWeapon"))
	TSoftClassPtr<UObject> Weapon;

	UPROPERTY(BlueprintReadOnly, Category = "CsWp")
	int32 Weapon_LoadFlags;

	UPROPERTY(Transient, BlueprintReadOnly, Category = "CsWp")
	UObject* Weapon_Internal;

	UPROPERTY(Transient, BlueprintReadOnly, Category = "CsWp")
	UClass* Weapon_Class;

	FCsWeaponPtr() :
		Weapon(nullptr),
		Weapon_LoadFlags(0),
		Weapon_Internal(nullptr),
		Weapon_Class(nullptr)
	{
	}

	FORCEINLINE UObject* Get() const { return Weapon_Internal; }

	FORCEINLINE UClass* GetClass() const { return Weapon_Class; }

	CS_STRUCT_OPS_DATA_UNLOAD(FCsWeaponPtr)

	FORCEINLINE void Unload()
	{
		Weapon.ResetWeakPtr();
		Weapon_Internal = nullptr;
		Weapon_Class = nullptr;
	}
};

#pragma endregion FCsWeaponPtr

// FCsData_WeaponPtr
#pragma region

class UObject;

USTRUCT(BlueprintType)
struct CSWP_API FCsData_WeaponPtr
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsWp", meta = (MustImplement = "/Script.CsWp.CsData_Weapon"))
	TSoftClassPtr<UObject> Data;

	UPROPERTY(BlueprintReadOnly, Category = "CsWp")
	int32 Data_LoadFlags;

	UPROPERTY(Transient, BlueprintReadOnly, Category = "CsWp")
	UObject* Data_Internal;

	UPROPERTY(Transient, BlueprintReadOnly, Category = "CsWp")
	UClass* Data_Class;

	FCsData_WeaponPtr() :
		Data(nullptr),
		Data_LoadFlags(0),
		Data_Internal(nullptr),
		Data_Class(nullptr)
	{
	}

	FORCEINLINE UObject* Get() const { return Data_Internal; }

	template<typename T>
	FORCEINLINE T* Get() const { return Cast<T>(Get()); }

	FORCEINLINE UClass* GetClass() const { return Data_Class; }

	UObject* SafeLoad(const FString& Context, void(*Log)(const FString&) = &NCsWeapon::FLog::Warning);

	UObject* SafeLoadSoftClass(const FString& Context, void(*Log)(const FString&) = &NCsWeapon::FLog::Warning);

	CS_STRUCT_OPS_DATA_UNLOAD(FCsData_WeaponPtr)

	void Unload();
};

#pragma endregion FCsData_WeaponPtr

// FCsWeaponClassEntry
#pragma region

USTRUCT(BlueprintType)
struct CSWP_API FCsWeaponClassEntry : public FCsTableRowBase_Data
{
	GENERATED_USTRUCT_BODY()

	/** The enum (FECsWeapon) name for the weapon class. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = DataTable)
	FString Name;

	/** The enum (FECsWeapon) display name for the weapon class. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = DataTable)
	FString DisplayName;

	/** Soft Reference to a weapon of type: ICsWeapon. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = DataTable)
	FCsWeaponPtr Class;

	FCsWeaponClassEntry() :
		Name(),
		DisplayName(),
		Class()
	{
	}

	// FCsTableRowBase_Data
#pragma region
public:

	virtual void Unload() override
	{
		Class.Unload();
	}

#pragma endregion FCsTableRowBase_Data

	CS_STRUCT_OPS_DATA_UNLOAD(FCsWeaponClassEntry)
};

#pragma endregion FCsWeaponClassEntry

// FCsWeaponEntry
#pragma region

USTRUCT(BlueprintType)
struct CSWP_API FCsWeaponEntry : public FCsTableRowBase_Data
{
	GENERATED_USTRUCT_BODY()

	/** The enum (FECsWeapon) name for the weapon. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = DataTable)
	FString Name;

	/** The enum (FECsWeapon) display name for the weapon. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = DataTable)
	FString DisplayName;

	/** Class Type. This is used to get the actual class from a data table
		of weapon classes (FCsWpDataRootSet.WeaponClasses). */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = DataTable)
	FECsWeaponClass Class;

	/** Soft Reference to a weapon data of type: ICsData_Weapon. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = DataTable)
	FCsData_WeaponPtr Data;

	FCsWeaponEntry() :
		Name(),
		DisplayName(),
		Class(),
		Data()
	{
	}

	// FCsTableRowBase_Data
#pragma region
public:

	virtual void Unload() override
	{
		Data.Unload();
	}

#pragma endregion FCsTableRowBase_Data

	CS_STRUCT_OPS_DATA_UNLOAD(FCsWeaponEntry)
};

#pragma endregion FCsWeaponEntry