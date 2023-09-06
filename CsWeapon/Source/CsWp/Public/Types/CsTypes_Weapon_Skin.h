// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Types
#include "Types/Enum/CsEnum_uint8.h"
#include "Types/Enum/CsEnumStructMap.h"
// Log
#include "Utility/CsWpLog.h"
// Engine
#include "Engine/DataTable.h"

#include "CsTypes_Weapon_Skin.generated.h"

// WeaponSkin
#pragma region

/**
*/
USTRUCT(BlueprintType)
struct CSWP_API FECsWeaponSkin : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

	CS_ENUM_UINT8_BODY(FECsWeaponSkin)
};

CS_DEFINE_ENUM_UINT8_GET_TYPE_HASH(FECsWeaponSkin)

struct CSWP_API EMCsWeaponSkin : public TCsEnumStructMap<FECsWeaponSkin, uint8>
{
	CS_ENUM_STRUCT_MAP_BODY(EMCsWeaponSkin, FECsWeaponSkin, uint8)
};

class UObject;

namespace NCsWeaponSkin
{
	typedef EMCsWeaponSkin EnumMapType;
	typedef FECsWeaponSkin Type;

	FORCEINLINE void Create(const FString& Name, const bool& UserDefinedEnum) { EnumMapType::Get().Create(Name, UserDefinedEnum); }
	FORCEINLINE void CreateCustom(const FString& Name, const FString& DisplayName, const bool& UserDefinedEnum) { EnumMapType::Get().Create(Name, DisplayName, UserDefinedEnum); }
	FORCEINLINE bool IsValidEnum(const FString& Name) { return EnumMapType::Get().IsValidEnum(Name); }
	FORCEINLINE bool IsValidEnumByDisplayName(const FString& DisplayName) { return EnumMapType::Get().IsValidEnumByDisplayName(DisplayName); }

	CSWP_API void FromDataTable(const FString& Context, UObject* ContextRoot);

	CSWP_API void PopulateEnumMapFromSettings(const FString& Context, UObject* ContextRoot);
}

#pragma endregion CharacterSkin

// FCsData_ECsWeaponSkin
#pragma region

USTRUCT(BlueprintType)
struct CSWP_API FCsData_ECsWeaponSkin
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsWp")
	FECsWeaponSkin Value;

	FCsData_ECsWeaponSkin() :
		Value()
	{
	}

	FORCEINLINE FECsWeaponSkin* GetPtr() { return &Value; }
};

#pragma endregion FCsData_ECsWeaponSkin

// FCsData_Weapon_SkinPtr
#pragma region

class UObject;

// NCsWeapon::NData::NSkin::ISkin
CS_FWD_DECLARE_STRUCT_NAMESPACE_3(NCsWeapon, NData, NSkin, ISkin)

USTRUCT(BlueprintType)
struct CSWP_API FCsData_Weapon_SkinPtr : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = DataTable, meta = (MustImplement = "/Script.CsWp.CsData_Weapon_Skin"))
	TSoftClassPtr<UObject> Data;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = DataTable)
	int32 Data_LoadFlags;

	UPROPERTY(Transient, BlueprintReadOnly, Category = DataTable)
	UObject* Data_Internal;

	UPROPERTY(Transient, BlueprintReadOnly, Category = DataTable)
	UClass* Data_Class;

	FCsData_Weapon_SkinPtr() :
		Data(nullptr),
		Data_LoadFlags(0),
		Data_Internal(nullptr),
		Data_Class(nullptr)
	{
	}

	FORCEINLINE UObject* Get() const { return Data_Internal; }

	template<typename T>
	FORCEINLINE T* Get() const { return Cast<T>(Get()); }

	#define DataType NCsWeapon::NData::NSkin::ISkin

	DataType* GetChecked(const FString& Context) const;

	DataType* GetSafe(const FString& Context) const;

	DataType* SafeLoad(const FString& Context, void(*Log)(const FString&) = &NCsWeapon::FLog::Warning);
	DataType* SafeLoad();

	#undef DataType

	UObject* SafeLoadSoftClass(const FString& Context, void(*Log)(const FString&) = &NCsWeapon::FLog::Warning);

	FORCEINLINE UClass* GetClass() const { return Data_Class; }
};

#pragma endregion FCsData_Weapon_SkinPtr

// FCsWeaponSkinEntry
#pragma region

/**
*/
USTRUCT(BlueprintType)
struct CSWP_API FCsWeaponSkinEntry : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	/** The enum (FECsWeaponSkin) name for the Weapon Skin. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = DataTable)
	FString Name;

	/** The enum (FECsWeaponSkin) display name for the Weapon Skin. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = DataTable)
	FString DisplayName;

	/** Soft Reference to a data of type: ICsData_Weapon_Skin. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = DataTable)
	FCsData_Weapon_SkinPtr Data;

	FCsWeaponSkinEntry() :
		Name(),
		DisplayName(), 
		Data()
	{
	}
};

#pragma endregion FCsWeaponSkinEntry