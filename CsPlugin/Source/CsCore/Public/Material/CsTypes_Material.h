// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Types
#include "Types/CsTypes_View.h"
// Log
#include "Utility/CsLog.h"

#include "CsTypes_Material.generated.h"

// FCsMaterialInterface
#pragma region

class UMaterialInterface;

USTRUCT(BlueprintType)
struct CSCORE_API FCsMaterialInterface
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Material")
	TSoftObjectPtr<UMaterialInterface> Material;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Material", meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 Material_LoadFlags;

	UPROPERTY(Transient, BlueprintReadOnly, Category = "CsCore|Material")
	UMaterialInterface* Material_Internal;

public:

	FCsMaterialInterface() :
		Material(nullptr),
		Material_LoadFlags(0),
		Material_Internal(nullptr)
	{
	}

	/**
	* Get the Hard reference to the UMaterialInterface asset.
	*
	* return Material
	*/
	FORCEINLINE UMaterialInterface* Get() const { return Material_Internal; }

	/**
	* Get the pointer to the Hard reference to the UMaterialInterface asset.
	*
	* return Material
	*/
	FORCEINLINE UMaterialInterface** GetPtr() { return &Material_Internal; }

	/**
	* Get the Hard reference to the UMaterialInterface asset.
	*
	* @param Context	The calling context.
	* return			Material
	*/
	FORCEINLINE UMaterialInterface* GetChecked(const FString& Context) const
	{
		checkf(Material.ToSoftObjectPath().IsValid(), TEXT("%s: Material is NULL."), *Context);

		checkf(Material_Internal, TEXT("%s: Material has NOT been loaded from Path @ %s."), *Context, *(Material.ToSoftObjectPath().ToString()));

		return Material_Internal;
	}

	/**
	* Get the Hard reference to the UMaterialInterface asset.
	*
	* return Material
	*/
	FORCEINLINE UMaterialInterface* GetChecked() const
	{
		checkf(Material.ToSoftObjectPath().IsValid(), TEXT("FCsMaterialInterface::GetChecked: Mesh is NULL."));

		checkf(Material_Internal, TEXT("FCsMaterialInterface::GetChecked: Material has NOT been loaded from Path @ %s."), *(Material.ToSoftObjectPath().ToString()));

		return Material_Internal;
	}

	/**
	* Safely get the Hard reference to the UMaterialInterface asset.
	*
	* @param Context	The calling context.
	* @param Log		(optional)
	* return			Material
	*/
	UMaterialInterface* GetSafe(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const
	{
		if (!Material.ToSoftObjectPath().IsValid())
		{
			if (Log)
				Log(FString::Printf(TEXT("%s: Material is NULL."), *Context));
			return nullptr;
		}

		if (!Material_Internal)
		{
			if (Log)
				Log(FString::Printf(TEXT("%s: Material has NOT been loaded from Path @ %s."), *Context, *(Material.ToSoftObjectPath().ToString())));
		}
		return Material_Internal;
	}

	/**
	* Safely get the Hard reference to the UMaterialInterface asset.
	*
	* return Material
	*/
	UMaterialInterface* GetSafe()
	{
		if (!Material.ToSoftObjectPath().IsValid())
			return nullptr;
		return Material_Internal;
	}

	bool IsValidChecked(const FString& Context) const
	{
		check(GetChecked(Context));
		return true;
	}

	bool IsValid(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const
	{
		if (!GetSafe(Context, Log))
			return false;
		return true;
	}
};

#pragma endregion FCsMaterialInterface

// FCsMaterialInstance
#pragma region

class UMaterialInstance;

USTRUCT(BlueprintType)
struct CSCORE_API FCsMaterialInstance
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Material")
	TSoftObjectPtr<UMaterialInstance> Material;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Material", meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 Material_LoadFlags;

	UPROPERTY(Transient, BlueprintReadOnly, Category = "CsCore|Material")
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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Material")
	TSoftObjectPtr<UMaterialInstanceConstant> Material;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Material", meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 Material_LoadFlags;

	UPROPERTY(Transient, BlueprintReadOnly, Category = "CsCore|Material")
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
class UPrimitiveComponent;

/**
*/
USTRUCT(BlueprintType)
struct CSCORE_API FCsTArrayMaterialInterface
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Material")
	TArray<TSoftObjectPtr<UMaterialInterface>> Materials;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Material", meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 Materials_LoadFlags;

	UPROPERTY(Transient, BlueprintReadWrite, Category = "CsCore|Material")
	TArray<UMaterialInterface*> Materials_Internal;

public:

	FCsTArrayMaterialInterface() :
		Materials(),
		Materials_LoadFlags(0),
		Materials_Internal()
	{
	}

	FORCEINLINE const TArray<UMaterialInterface*>& Get() const { return Materials_Internal; }

	FORCEINLINE TArray<UMaterialInterface*>* GetPtr() { return &Materials_Internal; }
	FORCEINLINE const TArray<UMaterialInterface*>* GetPtr() const { return &Materials_Internal; }

	/**
	* Get the Hard references to the array of Materials of type: UMaterialInterface.
	*
	* @param Context	The calling context.
	* return			Materials
	*/
	FORCEINLINE const TArray<UMaterialInterface*>& GetChecked(const FString& Context) const
	{ 
		checkf(Materials.Num() > CS_EMPTY, TEXT("%s: No Materials set."), *Context);

		checkf(Materials.Num() == Materials_Internal.Num(), TEXT("%s: Mismatch between Soft and Hard references to materials, %d != %d."), *Context, Materials.Num(), Materials_Internal.Num());

		const int32 Count = Materials.Num();

		for (int32 I = 0; I < Count; ++I)
		{
			const TSoftObjectPtr<UMaterialInterface>& SoftObject = Materials[I];

			checkf(SoftObject.ToSoftObjectPath().IsValid(), TEXT("%s: Materials[%d] is NULL."), *Context, I);

			UMaterialInterface* Material = Materials_Internal[I];
	
			checkf(Material, TEXT("%s: Materials[%d] has NOT been loaded from Path @ %s."), *Context, I, *(SoftObject.ToSoftObjectPath().ToString()));
		}
		return Materials_Internal; 
	}

	/**
	* Get the Hard references to the array of Materials of type: UMaterialInterface.
	*
	* @param Context	The calling context.
	* return			Materials
	*/
	FORCEINLINE const TArray<UMaterialInterface*>& GetChecked() const
	{
		checkf(Materials.Num() > CS_EMPTY, TEXT("FCsTArrayMaterialInterface::GetChecked: No Materials set."));

		checkf(Materials.Num() == Materials_Internal.Num(), TEXT("FCsTArrayMaterialInterface::GetChecked: Mismatch between Soft and Hard references to materials, %d != %d."), Materials.Num(), Materials_Internal.Num());

		const int32 Count = Materials.Num();

		for (int32 I = 0; I < Count; ++I)
		{
			const TSoftObjectPtr<UMaterialInterface>& SoftObject = Materials[I];

			checkf(SoftObject.ToSoftObjectPath().IsValid(), TEXT("FCsTArrayMaterialInterface::GetChecked: Materials[%d] is NULL."), I);

			UMaterialInterface* Material = Materials_Internal[I];

			checkf(Material, TEXT("FCsTArrayMaterialInterface::GetChecked: Materials[%d] has NOT been loaded from Path @ %s."), I, *(SoftObject.ToSoftObjectPath().ToString()));
		}
		return Materials_Internal;
	}

	/**
	* Get the Hard reference to the Material at Index of type: UMaterialInterface.
	*
	* @param Context	The calling context.
	* @param Index
	* return			Material
	*/
	FORCEINLINE UMaterialInterface* GetChecked(const FString& Context, const int32& Index) const
	{
		checkf(Index >= 0 && Index < Materials_Internal.Num(), TEXT("%s: Index: %d is NOT in the range [0, %d)."), *Context, Index, Materials_Internal.Num());

		return GetChecked(Context)[Index];
	}

	/**
	* Safely get the Hard reference to the array of Materials of type: UMaterialInterface.
	*
	* @param Context	The calling context.
	* @param Log		(optional)
	* return			Materials
	*/
	const TArray<UMaterialInterface*>* GetSafe(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const
	{
		if (Materials.Num() == CS_EMPTY)
		{
			if (Log)
				Log(FString::Printf(TEXT("%s: No Materials set."), *Context));
			return nullptr;
		}

		if (Materials.Num() != Materials_Internal.Num())
		{
			if (Log)
				Log(FString::Printf(TEXT("%s: Mismatch between Soft and Hard references to materials, %d != %d."), *Context, Materials.Num(), Materials_Internal.Num()));
			return nullptr;
		}

		const int32 Count = Materials.Num();

		for (int32 I = 0; I < Count; ++I)
		{
			const TSoftObjectPtr<UMaterialInterface>& SoftObject = Materials[I];

			if (!SoftObject.ToSoftObjectPath().IsValid())
			{
				if (Log)
					Log(FString::Printf(TEXT("%s: Materials[%d] is NULL."), *Context, I));
				return nullptr;
			}

			UMaterialInterface* Material = Materials_Internal[I];

			if (!Material)
			{
				if (Log)
					Log(FString::Printf(TEXT("%s: Materials[%d] has NOT been loaded from Path @ %s."), *Context, I, *(SoftObject.ToSoftObjectPath().ToString())));
				return nullptr;
			}
		}
		return &Materials_Internal;
	}

	void SetChecked(const FString& Context, UPrimitiveComponent* Component) const;

	bool SetSafe(const FString& Context, UPrimitiveComponent* Component, void(*Log)(const FString&) = &FCsLog::Warning) const;

	bool IsValidChecked(const FString& Context) const
	{
		checkf(Materials.Num() > CS_EMPTY, TEXT("%s: No Materials set."), *Context);

		checkf(Materials.Num() == Materials_Internal.Num(), TEXT("%s: Mismatch between Soft and Hard references to materials, %d != %d."), *Context, Materials.Num(), Materials_Internal.Num());

		const int32 Count = Materials.Num();

		for (int32 I = 0; I < Count; ++I)
		{
			const TSoftObjectPtr<UMaterialInterface>& SoftObject = Materials[I];

			checkf(SoftObject.ToSoftObjectPath().IsValid(), TEXT("%s: Materials[%d] is NULL."), *Context, I);

			UMaterialInterface* Material = Materials_Internal[I];

			checkf(Material, TEXT("%s: Materials[%d] has NOT been loaded from Path @ %s."), *Context, I, *(SoftObject.ToSoftObjectPath().ToString()));
		}
		return true;
	}

	bool IsValid(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const
	{
		if (Materials.Num() == CS_EMPTY)
		{
			if (Log)
				Log(FString::Printf(TEXT("%s: No Materials set."), *Context));
			return false;
		}

		if (Materials.Num() != Materials_Internal.Num())
		{
			if (Log)
				Log(FString::Printf(TEXT("%s: Mismatch between Soft and Hard references to materials, %d != %d."), *Context, Materials.Num(), Materials_Internal.Num()));
			return false;
		}

		const int32 Count = Materials.Num();

		for (int32 I = 0; I < Count; ++I)
		{
			const TSoftObjectPtr<UMaterialInterface>& SoftObject = Materials[I];

			if (!SoftObject.ToSoftObjectPath().IsValid())
			{
				if (Log)
					Log(FString::Printf(TEXT("%s: Materials[%d] is NULL."), *Context, I));
				return false;
			}

			UMaterialInterface* Material = Materials_Internal[I];

			if (!Material)
			{
				if (Log)
					Log(FString::Printf(TEXT("%s: Materials[%d] has NOT been loaded from Path @ %s."), *Context, I, *(SoftObject.ToSoftObjectPath().ToString())));
				return false;
			}
		}
		return true;
	}
};

#pragma endregion FCsTArrayMaterialInterface

// FCsTArrayMaterialInstanceConstant
#pragma region

class UMaterialInstanceConstant;

USTRUCT(BlueprintType)
struct CSCORE_API FCsTArrayMaterialInstanceConstant
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Material")
	TArray<TSoftObjectPtr<UMaterialInstanceConstant>> Materials;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Material", meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 Materials_LoadFlags;

	UPROPERTY(Transient, BlueprintReadOnly, Category = "CsCore|Material")
	TArray<UMaterialInstanceConstant*> Materials_Internal;

public:

	FCsTArrayMaterialInstanceConstant() :
		Materials(),
		Materials_LoadFlags(0),
		Materials_Internal()
	{
	}

	FORCEINLINE const TArray<UMaterialInstanceConstant*>& Get() const { return Materials_Internal; }

	FORCEINLINE TArray<UMaterialInstanceConstant*>* GetPtr() { return &Materials_Internal; }
	FORCEINLINE const TArray<UMaterialInstanceConstant*>* GetPtr() const { return &Materials_Internal; }

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

	UPROPERTY(EditAnywhere, Category = "CsCore|Material")
	TArray<TSoftObjectPtr<UMaterialInstanceConstant>> Materials1P;

	UPROPERTY(EditAnywhere, Category = "CsCore|Material")
	TArray<TSoftObjectPtr<UMaterialInstanceConstant>> Materials3P;

	UPROPERTY(EditAnywhere, Category = "CsCore|Material")
	TArray<TSoftObjectPtr<UMaterialInstanceConstant>> Materials3P_Low;

	UPROPERTY(EditAnywhere, Category = "CsCore|Material")
	TArray<TSoftObjectPtr<UMaterialInstanceConstant>> MaterialsVR;

	UPROPERTY(EditAnywhere, Category = "CsCore|Material", meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 Materials1P_LoadFlags;

	UPROPERTY(EditAnywhere, Category = "CsCore|Material", meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 Materials3P_LoadFlags;

	UPROPERTY(EditAnywhere, Category = "CsCore|Material", meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 Materials3P_Low_LoadFlags;

	UPROPERTY(EditAnywhere, Category = "CsCore|Material", meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Material")
	FName Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Material")
	float Value;

	FCsMaterialParameterFloat() :
		Name(NAME_None),
		Value(0.0f)
	{
	}

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const;
};

#pragma endregion FCsMaterialParameterFloat

// FCsMaterialParameterFloatRange
#pragma region

// NCsMaterial::NParameter::NFloat::FRange
CS_FWD_DECLARE_STRUCT_NAMESPACE_3(NCsMaterial, NParameter, NFloat, FRange)

class UMaterialInterface;
class UMaterialInstanceDynamic;

USTRUCT(BlueprintType)
struct CSCORE_API FCsMaterialParameterFloatRange
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Material")
	FName Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Material")
	float Min;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Material")
	float Max;

	FCsMaterialParameterFloatRange() :
		Name(NAME_None),
		Min(0.0f),
		Max(0.0f)
	{
	}

#define ParamsType NCsMaterial::NParameter::NFloat::FRange
	void CopyToParams(ParamsType* Params);
	void CopyToParamsAsValue(ParamsType* Params) const;
#undef ParamsType

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const;

	bool IsValidChecked(const FString& Context, UMaterialInterface* Material) const;
	bool IsValid(const FString& Context, UMaterialInterface* Material, void(*Log)(const FString&) = &FCsLog::Warning) const;

	FORCEINLINE float CalculateValue() const
	{
		return FMath::Lerp(Min, Max, FMath::RandRange(0.0f, 1.0f));
	}

	void SetChecked(const FString& Context, UMaterialInstanceDynamic* MID) const;
	bool SetSafe(const FString& Context, UMaterialInstanceDynamic* MID, void(*Log)(const FString&) = &FCsLog::Warning) const;
};

namespace NCsMaterial
{
	namespace NParameter
	{
		namespace NFloat
		{
			struct CSCORE_API FRange final
			{
			private:

				CS_DECLARE_MEMBER_WITH_PROXY(Name, FName)
				CS_DECLARE_MEMBER_WITH_PROXY(Min, float)
				CS_DECLARE_MEMBER_WITH_PROXY(Max, float)

			public:

				FRange() :
					CS_CTOR_INIT_MEMBER_WITH_PROXY(Name, NAME_None),
					CS_CTOR_INIT_MEMBER_WITH_PROXY(Min, 0.0f),
					CS_CTOR_INIT_MEMBER_WITH_PROXY(Max, 0.0f)
				{
					CS_CTOR_SET_MEMBER_PROXY(Name);
					CS_CTOR_SET_MEMBER_PROXY(Min);
					CS_CTOR_SET_MEMBER_PROXY(Max);
				}

				CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Name, FName)
				CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Min, float)
				CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Max, float)
	
				bool IsValidChecked(const FString& Context) const;
				bool IsValid(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const;

				bool IsValidChecked(const FString& Context, UMaterialInterface* Material) const;
				bool IsValid(const FString& Context, UMaterialInterface* Material, void(*Log)(const FString&) = &FCsLog::Warning) const;

				void CopyAsValue(const FRange& From)
				{
					SetName(From.GetName());
					SetMin(From.GetMin());
					SetMax(From.GetMax());
				}

				FORCEINLINE float CalculateValue() const
				{
					return FMath::Lerp(GetMin(), GetMax(), FMath::RandRange(0.0f, 1.0f));
				}

				void SetChecked(const FString& Context, UMaterialInstanceDynamic* MID) const;
				bool SetSafe(const FString& Context, UMaterialInstanceDynamic* MID, void(*Log)(const FString&) = &FCsLog::Warning) const;
			};
		}
	}
}

#pragma endregion FCsMaterialParameterFloatRange

// FCsMaterialParameterColor
#pragma region

USTRUCT(BlueprintType)
struct CSCORE_API FCsMaterialParameterColor
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Material")
	FName Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Material")
	FLinearColor Value;

	FCsMaterialParameterColor() :
		Name(NAME_None),
		Value(FLinearColor::White)
	{
	}

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const;
};

#pragma endregion FCsMaterialParameterColor

// FCsMaterialParameterColorRange
#pragma region

// NCsMaterial::NParameter::NColor::FRange
CS_FWD_DECLARE_STRUCT_NAMESPACE_3(NCsMaterial, NParameter, NColor, FRange)

class UMaterialInstanceDynamic;

USTRUCT(BlueprintType)
struct CSCORE_API FCsMaterialParameterColorRange
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Material")
	FName Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Material")
	FLinearColor From;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Material")
	FLinearColor To;

	FCsMaterialParameterColorRange() :
		Name(NAME_None),
		From(FLinearColor::White),
		To(FLinearColor::White)
	{
	}

#define ParamsType NCsMaterial::NParameter::NColor::FRange
	void CopyToParams(ParamsType* Params);
	void CopyToParamsAsValue(ParamsType* Params) const;
#undef ParamsType

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const;

	bool IsValidChecked(const FString& Context, UMaterialInterface* Material) const;
	bool IsValid(const FString& Context, UMaterialInterface* Material, void(*Log)(const FString&) = &FCsLog::Warning) const;

	FORCEINLINE FLinearColor CalculateValue() const
	{
		return FMath::Lerp(From, To, FMath::RandRange(0.0f, 1.0f));
	}

	void SetChecked(const FString& Context, UMaterialInstanceDynamic* MID) const;
	bool SetSafe(const FString& Context, UMaterialInstanceDynamic* MID, void(*Log)(const FString&) = &FCsLog::Warning) const;
};

namespace NCsMaterial
{
	namespace NParameter
	{
		namespace NColor
		{
			struct CSCORE_API FRange final
			{
			private:

				CS_DECLARE_MEMBER_WITH_PROXY(Name, FName)
				CS_DECLARE_MEMBER_WITH_PROXY(From, FLinearColor)
				CS_DECLARE_MEMBER_WITH_PROXY(To, FLinearColor)

			public:

				FRange() :
					CS_CTOR_INIT_MEMBER_WITH_PROXY(Name, NAME_None),
					CS_CTOR_INIT_MEMBER_WITH_PROXY(From, FLinearColor::White),
					CS_CTOR_INIT_MEMBER_WITH_PROXY(To, FLinearColor::White)
				{
					CS_CTOR_SET_MEMBER_PROXY(Name);
					CS_CTOR_SET_MEMBER_PROXY(From);
					CS_CTOR_SET_MEMBER_PROXY(To);
				}

				CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Name, FName)
				CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(From, FLinearColor)
				CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(To, FLinearColor)
	
				bool IsValidChecked(const FString& Context) const;
				bool IsValid(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const;

				bool IsValidChecked(const FString& Context, UMaterialInterface* Material) const;
				bool IsValid(const FString& Context, UMaterialInterface* Material, void(*Log)(const FString&) = &FCsLog::Warning) const;

				void CopyAsValue(const FRange& Value)
				{
					SetName(Value.GetName());
					SetFrom(Value.GetFrom());
					SetTo(Value.GetTo());
				}

				FORCEINLINE FLinearColor CalculateValue() const
				{
					return FMath::Lerp(GetFrom(), GetTo(), FMath::RandRange(0.0f, 1.0f));
				}

				void SetChecked(const FString& Context, UMaterialInstanceDynamic* MID) const;
				bool SetSafe(const FString& Context, UMaterialInstanceDynamic* MID, void(*Log)(const FString&) = &FCsLog::Warning) const;
			};
		}
	}
}

#pragma endregion FCsMaterialParameterColorRange

// FCsMaterialInterface_WithRangeParameters
#pragma region

// NCsMaterial::NInterface::FWithRangeParameters
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsMaterial, NInterface, FWithRangeParameters)

class UPrimitiveComponent;
class UMaterialInstanceDynamic;

USTRUCT(BlueprintType)
struct CSCORE_API FCsMaterialInterface_WithRangeParameters
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Material")
	FCsMaterialInterface Material;

	UPROPERTY(Transient, BlueprintReadOnly, Category = "CsCore|Material")
	TArray<FCsMaterialParameterFloatRange> FloatParameters;

	UPROPERTY(Transient, BlueprintReadOnly, Category = "CsCore|Material")
	TArray<FCsMaterialParameterColorRange> ColorParameters;

	FCsMaterialInterface_WithRangeParameters() :
		Material(),
		FloatParameters(),
		ColorParameters()
	{
	}

#define MaterialType NCsMaterial::NInterface::FWithRangeParameters
	void CopyToMaterial(MaterialType* Mat);
	void CopyToMaterialAsValue(MaterialType* Mat) const;
#undef MaterialType

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const;

	void SetChecked(const FString& Context, UPrimitiveComponent* Component, const int32& Index, UMaterialInstanceDynamic*& OutMID) const;
	bool SetSafe(const FString& Context, UPrimitiveComponent* Component, const int32& Index, UMaterialInstanceDynamic*& OutMID, void(*Log)(const FString&) = &FCsLog::Warning) const;
};

class UMaterialInterface;

namespace NCsMaterial
{
	namespace NInterface
	{
		struct CSCORE_API FWithRangeParameters final
		{
		#define FloatParameterType NCsMaterial::NParameter::NFloat::FRange
		#define ColorParameterType NCsMaterial::NParameter::NColor::FRange

		private:

			CS_DECLARE_MEMBER_WITH_PROXY(Material, UMaterialInterface*)
			CS_DECLARE_MEMBER_WITH_PROXY(FloatParameters, TArray<FloatParameterType>)
			CS_DECLARE_MEMBER_WITH_PROXY(ColorParameters, TArray<ColorParameterType>)

		public:

			FWithRangeParameters() :
				CS_CTOR_INIT_MEMBER_WITH_PROXY(Material, nullptr),
				CS_CTOR_INIT_MEMBER_STRUCT_WITH_PROXY(FloatParameters),
				CS_CTOR_INIT_MEMBER_STRUCT_WITH_PROXY(ColorParameters)
			{
				CS_CTOR_SET_MEMBER_PROXY(Material);
				CS_CTOR_SET_MEMBER_PROXY(FloatParameters);
				CS_CTOR_SET_MEMBER_PROXY(ColorParameters);
			}

			CS_DEFINE_SET_GET_MEMBER_PTR_WITH_PROXY(Material, UMaterialInterface)
			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(FloatParameters, TArray<FloatParameterType>)
			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(ColorParameters, TArray<ColorParameterType>)

			bool IsValidChecked(const FString& Context) const;
			bool IsValid(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const;

			void CopyAsValue(const FWithRangeParameters& From)
			{
				SetMaterial(From.GetMaterial());

				// Float
				{
					TArray<FloatParameterType>* Params = GetFloatParametersPtr();

					Params->Reset(From.GetFloatParameters().Num());

					for (const FloatParameterType& Param : From.GetFloatParameters())
					{
						FloatParameterType& P = Params->AddDefaulted_GetRef();
						P.CopyAsValue(Param);
					}
				}
				// Color
				{
					TArray<ColorParameterType>* Params = GetColorParametersPtr();

					Params->Reset(From.GetFloatParameters().Num());

					for (const ColorParameterType& Param : From.GetColorParameters())
					{
						ColorParameterType& P = Params->AddDefaulted_GetRef();
						P.CopyAsValue(Param);
					}
				}
			}

			void SetChecked(const FString& Context, UPrimitiveComponent* Component, const int32& Index, UMaterialInstanceDynamic*& OutMID) const;
			bool SetSafe(const FString& Context, UPrimitiveComponent* Component, const int32& Index, UMaterialInstanceDynamic*& OutMID, void(*Log)(const FString&) = &FCsLog::Warning) const;

		#undef FloatParameterType
		#undef ColorParameterType
		};
	}
}

#pragma endregion FCsMaterialInterface_WithRangeParameters