// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "CsMacro_StructOps.h"
#include "Types/CsTypes_Damage.h"
// Data
#include "Data/CsTableRowBase_Data.h"
// Log
#include "Utility/CsDmgLog.h"

#include "CsTypes_Data_Damage.generated.h"

// DamageData
#pragma region

USTRUCT(BlueprintType)
struct CSDMG_API FECsDamageData : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

	CS_ENUM_UINT8_BODY(FECsDamageData)
};

CS_DEFINE_ENUM_UINT8_GET_TYPE_HASH(FECsDamageData)

struct CSDMG_API EMCsDamageData : public TCsEnumStructMap<FECsDamageData, uint8>
{
	CS_ENUM_STRUCT_MAP_BODY(EMCsDamageData, FECsDamageData, uint8)
};

namespace NCsDamageData
{
	typedef FECsDamageData Type;
	typedef EMCsDamageData EnumMapType;

	FORCEINLINE void Create(const FString& Name, const bool& UserDefinedEnum) { EnumMapType::Get().Create(Name, UserDefinedEnum); }
	FORCEINLINE void CreateCustom(const FString& Name, const FString& DisplayName, const bool& UserDefinedEnum) { EnumMapType::Get().Create(Name, DisplayName, UserDefinedEnum); }
	FORCEINLINE bool IsValidEnum(const FString& Name) { return EnumMapType::Get().IsValidEnum(Name); }
	FORCEINLINE bool IsValidEnumByDisplayName(const FString& DisplayName) { return EnumMapType::Get().IsValidEnumByDisplayName(DisplayName); }

	CSDMG_API void FromDataTable(const FString& Context, UObject* ContextRoot);

	CSDMG_API void PopulateEnumMapFromSettings(const FString& Context, UObject* ContextRoot);
}

#pragma endregion DamageData

// FCsData_ECsDamageData
#pragma region

USTRUCT(BlueprintType)
struct CSDMG_API FCsData_ECsDamageData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsDmg")
	FECsDamageData Value;

	FCsData_ECsDamageData() :
		Value()
	{
	}

	FORCEINLINE FECsDamageData* GetPtr() { return &Value; }

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsDamage::FLog::Warning) const;
};

#pragma endregion FCsData_ECsDamageData

// FCsData_DamagePtr
#pragma region

class UObject;
class UClass;

USTRUCT(BlueprintType)
struct CSDMG_API FCsData_DamagePtr
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsDmg", meta = (MustImplement = "/Script/CsDmg.CsData_Damage"))
	TSoftClassPtr<UObject> Data;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsDmg")
	int32 Load_Flags;

	UPROPERTY(Transient, BlueprintReadOnly, Category = "CsDmg")
	UObject* Data_Internal;

	UPROPERTY(Transient, BlueprintReadOnly, Category = "CsDmg")
	UClass* Data_Class;

	FCsData_DamagePtr() :
		Data(nullptr),
		Load_Flags(0),
		Data_Internal(nullptr),
		Data_Class(nullptr)
	{
	}

	FORCEINLINE UObject* Get() const { return Data_Internal; }

	template<typename T>
	FORCEINLINE T* Get() const { return Cast<T>(Get()); }

	FORCEINLINE UClass* GetClass() const { return Data_Class; }

	UObject* SafeLoadSoftClass(const FString& Context, void(*Log)(const FString&) = &NCsDamage::FLog::Warning);

	CS_STRUCT_OPS_DATA_UNLOAD(FCsData_DamagePtr)

	void Unload();
};

#pragma endregion FCsData_DamagePtr

// FCsDamageDataEntry
#pragma region

/**
*/
USTRUCT(BlueprintType)
struct CSDMG_API FCsDamageDataEntry : public FCsTableRowBase_Data
{
	GENERATED_USTRUCT_BODY()

	/** The enum (FECsDamageData) name for the damage data. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = DataTable)
	FString Name;

	/** The enum (FECsDamageData) display name for the damage data. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = DataTable)
	FString DisplayName;

	/** Soft Reference to a data of type: ICsData_Damage. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = DataTable)
	FCsData_DamagePtr Data;

	FCsDamageDataEntry() :
		Name(),
		DisplayName(),
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

	CS_STRUCT_OPS_DATA_UNLOAD(FCsDamageDataEntry)
};

#pragma endregion FCsDamageDataEntry