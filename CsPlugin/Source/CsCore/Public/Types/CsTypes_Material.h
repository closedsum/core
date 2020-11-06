// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/CsTypes_View.h"

#include "CsTypes_Material.generated.h"
#pragma once

// FCsMaterialInstance
#pragma region

class UMaterialInstance;

USTRUCT(BlueprintType)
struct CSCORE_API FCsMaterialInstance
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSoftObjectPtr<UMaterialInstance> Material;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 Material_LoadFlags;

	UPROPERTY(Transient, BlueprintReadOnly)
	UMaterialInstance* Material_Internal;

public:

	FCsMaterialInstance() :
		Material(nullptr),
		Material_LoadFlags(0),
		Material_Internal(nullptr)
	{
	}

	FORCEINLINE UMaterialInstance* Get() const
	{
		return Material_Internal;
	}

	FORCEINLINE UMaterialInstance* GetChecked() const 
	{
		checkf(Material_Internal, TEXT("FCsMaterialInstance::GetChecked: Material_Internal is NULL."));

		return Material_Internal;
	}

	FORCEINLINE UMaterialInstance* GetChecked(const FString& Context) const
	{
		checkf(Material_Internal, TEXT("%s: Material_Internal is NULL."), *Context);

		return Material_Internal;
	}
};

#pragma endregion FCsMaterialInstance

// FCsMaterialInstanceConstant
#pragma region

class UMaterialInstanceConstant;

USTRUCT(BlueprintType)
struct CSCORE_API FCsMaterialInstanceConstant
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSoftObjectPtr<UMaterialInstanceConstant> Material;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 Material_LoadFlags;

	UPROPERTY(Transient, BlueprintReadOnly)
	UMaterialInstanceConstant* Material_Internal;

public:
	FCsMaterialInstanceConstant() :
		Material(nullptr),
		Material_LoadFlags(0),
		Material_Internal(nullptr)
	{
	}

	FORCEINLINE UMaterialInstanceConstant* Get() const
	{
		return Material_Internal;
	}
};

#pragma endregion FCsMaterialInstanceConstant

// FCsTArrayMaterialInterface
#pragma region

class UMaterialInterface;

/**
*/
USTRUCT(BlueprintType)
struct CSCORE_API FCsTArrayMaterialnterface
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<TSoftObjectPtr<UMaterialInterface>> Materials;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 Materials_LoadFlags;

	UPROPERTY(Transient, BlueprintReadOnly)
	TArray<UMaterialInterface*> Materials_Internal;

public:

	FCsTArrayMaterialnterface() :
		Materials(),
		Materials_LoadFlags(0),
		Materials_Internal()
	{
	}

	FORCEINLINE const TArray<UMaterialInterface*>& Get() const
	{
		return Materials_Internal;
	}
};

#pragma endregion FCsTArrayMaterialnterface

// FCsTArrayMaterialInstanceConstant
#pragma region

class UMaterialInstanceConstant;

USTRUCT(BlueprintType)
struct CSCORE_API FCsTArrayMaterialInstanceConstant
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<TSoftObjectPtr<UMaterialInstanceConstant>> Materials;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 Materials_LoadFlags;

	UPROPERTY(Transient, BlueprintReadOnly)
	TArray<UMaterialInstanceConstant*> Materials_Internal;

public:

	FCsTArrayMaterialInstanceConstant() :
		Materials(),
		Materials_LoadFlags(0),
		Materials_Internal()
	{
	}

	FORCEINLINE const TArray<UMaterialInstanceConstant*>& Get()
	{
		return Materials_Internal;
	}

	FORCEINLINE UMaterialInstanceConstant* Get(const int32 Index)
	{
		return Index < Materials_Internal.Num() ? Materials_Internal[Index] : nullptr;
	}
};

#pragma endregion FCsTArrayMaterialInstanceConstant

// FCsFpsTArrayMaterialInstanceConstant
#pragma region

class UMaterialInstanceConstant;

USTRUCT(BlueprintType)
struct CSCORE_API FCsFpsTArrayMaterialInstanceConstant
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, Category = "Material")
	TArray<TSoftObjectPtr<UMaterialInstanceConstant>> Materials1P;

	UPROPERTY(EditAnywhere, Category = "Material")
	TArray<TSoftObjectPtr<UMaterialInstanceConstant>> Materials3P;

	UPROPERTY(EditAnywhere, Category = "Material")
	TArray<TSoftObjectPtr<UMaterialInstanceConstant>> Materials3P_Low;

	UPROPERTY(EditAnywhere, Category = "Material")
	TArray<TSoftObjectPtr<UMaterialInstanceConstant>> MaterialsVR;

	UPROPERTY(EditAnywhere, Category = "Material", meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 Materials1P_LoadFlags;

	UPROPERTY(EditAnywhere, Category = "Material", meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 Materials3P_LoadFlags;

	UPROPERTY(EditAnywhere, Category = "Material", meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 Materials3P_Low_LoadFlags;

	UPROPERTY(EditAnywhere, Category = "Material", meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 MaterialsVR_LoadFlags;

	UPROPERTY(Transient)
	TArray<UMaterialInstanceConstant*> Materials1P_Internal;

	UPROPERTY(Transient)
	TArray<UMaterialInstanceConstant*> Materials3P_Internal;

	UPROPERTY(Transient)
	TArray<UMaterialInstanceConstant*> Materials3P_Low_Internal;

	UPROPERTY(Transient)
	TArray<UMaterialInstanceConstant*> MaterialsVR_Internal;

public:

	FCsFpsTArrayMaterialInstanceConstant() :
		Materials1P(),
		Materials3P(),
		Materials3P_Low(),
		MaterialsVR(),
		Materials1P_LoadFlags(0),
		Materials3P_LoadFlags(0),
		Materials3P_Low_LoadFlags(0),
		MaterialsVR_LoadFlags(0),
		Materials1P_Internal(),
		Materials3P_Internal(),
		Materials3P_Low_Internal(),
		MaterialsVR_Internal()
	{
	}

	FORCEINLINE const TArray<UMaterialInstanceConstant*>& Get(const ECsViewType& ViewType, const bool& IsLow = false)
	{
		if (ViewType == ECsViewType::FirstPerson)
			return Materials1P_Internal;
		if (ViewType == ECsViewType::ThirdPerson)
			return IsLow ? Materials3P_Low_Internal : Materials3P_Internal;
		if (ViewType == ECsViewType::VR)
			return MaterialsVR_Internal;
		return Materials3P_Internal;
	}

	FORCEINLINE UMaterialInstanceConstant* Get(const ECsViewType& ViewType, const int32& Index, const bool& IsLow = false)
	{
		if (ViewType == ECsViewType::FirstPerson)
			return Index < Materials1P_Internal.Num() ? Materials1P_Internal[Index] : NULL;
		if (ViewType == ECsViewType::ThirdPerson)
		{
			if (IsLow)
				return Index < Materials3P_Low_Internal.Num() ? Materials3P_Low_Internal[Index] : NULL;
			else
				return Index < Materials3P_Internal.Num() ? Materials3P_Internal[Index] : NULL;
		}
		if (ViewType == ECsViewType::VR)
			return Index < MaterialsVR_Internal.Num() ? MaterialsVR_Internal[Index] : NULL;
		return NULL;
	}
};

#pragma endregion FCsFpsTArrayMaterialInstanceConstant

// FCsMaterialParameterFloat
#pragma region

USTRUCT(BlueprintType)
struct CSCORE_API FCsMaterialParameterFloat
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Value;

	FCsMaterialParameterFloat() :
		Name(NAME_None),
		Value(0.0f)
	{
	}
};

#pragma endregion FCsMaterialParameterFloat

// FCsMaterialParameterColor
#pragma region

USTRUCT(BlueprintType)
struct CSCORE_API FCsMaterialParameterColor
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FColor Value;

	FCsMaterialParameterColor() :
		Name(NAME_None),
		Value(FColor::White)
	{
	}
};

#pragma endregion FCsMaterialParameterColor