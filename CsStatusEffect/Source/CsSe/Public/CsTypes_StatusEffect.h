// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Types/Enum/CsEnum_uint8.h"
#include "Types/Enum/CsEnumStructMap.h"

#include "CsTypes_StatusEffect.generated.h"

// StatusEffect
#pragma region

/**
*/
USTRUCT(BlueprintType)
struct CSSE_API FECsStatusEffect : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

		CS_ENUM_UINT8_BODY(FECsStatusEffect)
};

CS_DEFINE_ENUM_UINT8_GET_TYPE_HASH(FECsStatusEffect)

struct CSSE_API EMCsStatusEffect : public TCsEnumStructMap<FECsStatusEffect, uint8>
{
	CS_ENUM_STRUCT_MAP_BODY(EMCsStatusEffect, FECsStatusEffect, uint8)
};

class UObject;

namespace NCsStatusEffect
{
	typedef FECsStatusEffect Type;
	typedef EMCsStatusEffect EnumMapType;

	CSSE_API void FromDataTable(const FString& Context, UObject* ContextRoot);

	CSSE_API void PopulateEnumMapFromSettings(const FString& Context, UObject* ContextRoot);
}

#pragma endregion StatusEffect

// StatusEffectEvent
#pragma region

/**
*/
USTRUCT(BlueprintType)
struct CSSE_API FECsStatusEffectEvent : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

	CS_ENUM_UINT8_BODY(FECsStatusEffectEvent)
};

CS_DEFINE_ENUM_UINT8_GET_TYPE_HASH(FECsStatusEffectEvent)

struct CSSE_API EMCsStatusEffectEvent : public TCsEnumStructMap<FECsStatusEffectEvent, uint8>
{
	CS_ENUM_STRUCT_MAP_BODY(EMCsStatusEffectEvent, FECsStatusEffectEvent, uint8)
};

namespace NCsStatusEffectEvent
{
	typedef FECsStatusEffectEvent Type;
	typedef EMCsStatusEffectEvent EnumMapType;

	extern CSSE_API const Type Default;
	extern CSSE_API const Type Damage;
}

#pragma endregion StatusEffectEvent

// FCsData_StatusEffectPtr
#pragma region

/**
*/
USTRUCT(BlueprintType)
struct CSSE_API FCsData_StatusEffectPtr
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (MustImplement = "CsData_StatusEffect"))
	TSoftClassPtr<UObject> Data;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 Data_LoadFlags;

	UPROPERTY(Transient, BlueprintReadOnly)
	UObject* Data_Internal;

	UPROPERTY(Transient, BlueprintReadOnly)
	UClass* Data_Class;

	FCsData_StatusEffectPtr() :
		Data(nullptr),
		Data_LoadFlags(0),
		Data_Internal(nullptr),
		Data_Class(nullptr)
	{
	}

	FORCEINLINE UObject* Get() const { return Data_Internal; }

	template<typename T>
	FORCEINLINE T* Get() const
	{
		return Cast<T>(Get());
	}

	FORCEINLINE UObject* GetChecked(const FString& Context) const
	{
		checkf(Data_Internal, TEXT("%s: Data_Internal is NULL."), *Context);

		return Data_Internal;
	}

	template<typename T>
	FORCEINLINE T* GetChecked(const FString& Context) const
	{
		return Cast<T>(GetChecked(Context));
	}

	FORCEINLINE UClass* GetClass() const { return Data_Class; }
};

#pragma endregion FCsData_StatusEffectPtr