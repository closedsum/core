// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Types
#include "Managers/Damage/CsTypes_Damage.h"
#include "Engine/DataTable.h"

#include "CsTypes_Data_Damage.generated.h"

// DamageData
#pragma region

USTRUCT(BlueprintType)
struct CSCORE_API FECsDamageData : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

	CS_ENUM_UINT8_BODY(FECsDamageData)
};

CS_DEFINE_ENUM_UINT8_GET_TYPE_HASH(FECsDamageData)

struct CSCORE_API EMCsDamageData : public TCsEnumStructMap<FECsDamageData, uint8>
{
	CS_ENUM_STRUCT_MAP_BODY(EMCsDamageData, FECsDamageData, uint8)
};

namespace NCsDamageData
{
	typedef FECsDamageData Type;
	typedef EMCsDamageData EnumMapType;

	CSCORE_API void FromDataTable(const FString& Context, UObject* ContextRoot);

	CSCORE_API void PopulateEnumMapFromSettings(const FString& Context, UObject* ContextRoot);
}

#pragma endregion DamageData

// FCsData_DamagePtr
#pragma region

class UObject;
class UClass;

USTRUCT(BlueprintType)
struct CSCORE_API FCsData_DamagePtr
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (MustImplement = "CsData_Damage"))
	TSoftClassPtr<UObject> Data;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 Load_Flags;

	UPROPERTY(Transient, BlueprintReadOnly)
	UObject* Data_Internal;

	UPROPERTY(Transient, BlueprintReadOnly)
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
};

#pragma endregion FCsData_DamagePtr

// FCsDamageDataEntry
#pragma region

/**
*/
USTRUCT(BlueprintType)
struct CSCORE_API FCsDamageDataEntry : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	/** The enum (FECsDamageData) name for the damage data. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString Name;

	/** The enum (FECsDamageData) display name for the damage data. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString DisplayName;

	/** Soft Reference to a data of type: ICsData_Damage. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FCsData_DamagePtr Data;

	FCsDamageDataEntry() :
		Name(),
		DisplayName(),
		Data()
	{
	}
};

#pragma endregion FCsDamageDataEntry