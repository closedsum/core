// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "Struct/CsTypes_StructOps.h"
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

	UPROPERTY(BlueprintReadOnly, Category = "CsCore|Material", meta = (Bitmask, BitmaskEnum = "/Script/CsCore.ECsLoadFlags"))
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
		checkf(Material.ToSoftObjectPath().IsValid(), TEXT("FCsMaterialInterface::GetChecked: Material is NULL."));
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

	CS_STRUCT_OPS_IS_VALID_CHECKED(FCsMaterialInterface)
	CS_STRUCT_OPS_IS_VALID(FCsMaterialInterface)
	CS_STRUCT_OPS_IS_TOP_VALID_CHECKED(FCsMaterialInterface)
	CS_STRUCT_OPS_IS_TOP_VALID(FCsMaterialInterface)

	FORCEINLINE bool IsValidChecked(const FString& Context) const
	{
		check(GetChecked(Context));
		return true;
	}

	FORCEINLINE bool IsValid(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const
	{
		if (!GetSafe(Context, Log))
			return false;
		return true;
	}

	FORCEINLINE bool IsTopValidChecked(const FString& Context) const
	{
		checkf(Material.ToSoftObjectPath().IsValid(), TEXT("%s: Material's Path is NOT Valid."), *Context);
		return true;
	}

	FORCEINLINE bool IsTopValid(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const
	{
		if (!Material.ToSoftObjectPath().IsValid())
		{
			if (Log)
				Log(FString::Printf(TEXT("%s: Material's Path is NOT Valid."), *Context));
			return false;
		}
		return true;
	}

	UMaterialInterface* LoadChecked(const FString& Context);

	UMaterialInterface* SafeLoad(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning);

	FORCEINLINE UMaterialInterface* SafeLoad(const FString& Context, bool& OutSuccess, void(*Log)(const FString&) = &FCsLog::Warning)
	{
		UMaterialInterface* Result = SafeLoad(Context, Log);
		OutSuccess				   = Result != nullptr;
		return Result;
	}

	CS_STRUCT_OPS_DATA_UNLOAD(FCsMaterialInterface)

	FORCEINLINE void Unload() 
	{ 
		Material.ResetWeakPtr();
		Material_Internal = nullptr;
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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Material", meta = (Bitmask, BitmaskEnum = "/Script/CsCore.ECsLoadFlags"))
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

	/**
	* Get the Hard reference to the UMaterialInstance asset.
	*
	* return Material
	*/
	FORCEINLINE UMaterialInstance* Get() const
	{
		return Material_Internal;
	}

	/**
	* Get the pointer to the Hard reference to the UMaterialInstance asset.
	*
	* return Material
	*/
	FORCEINLINE UMaterialInstance** GetPtr() { return &Material_Internal; }

	/**
	* Get the Hard reference to the UMaterialInstance asset.
	*
	* @param Context	The calling context.
	* return			Material
	*/
	FORCEINLINE UMaterialInstance* GetChecked() const 
	{
		checkf(Material.ToSoftObjectPath().IsValid(), TEXT("FCsMaterialInstance::GetChecked: Material's Path is NOT Valid."));
		checkf(Material_Internal, TEXT("FCsMaterialInstance::GetChecked: Material has NOT been loaded from Path @ %s."), *(Material.ToSoftObjectPath().ToString()));

		return Material_Internal;
	}

	/**
	* Get the Hard reference to the UMaterialInstance asset.
	*
	* return Material
	*/
	FORCEINLINE UMaterialInstance* GetChecked(const FString& Context) const
	{
		checkf(Material.ToSoftObjectPath().IsValid(), TEXT("%s: Material's Path is NOT Valid."), *Context);
		checkf(Material_Internal, TEXT("%s: Material has NOT been loaded from Path @ %s."), *Context, *(Material.ToSoftObjectPath().ToString()));

		return Material_Internal;
	}

	/**
	* Safely get the Hard reference to the UMaterialInstance asset.
	*
	* @param Context	The calling context.
	* @param Log		(optional)
	* return			Material
	*/
	UMaterialInstance* GetSafe(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const
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
	* Safely get the Hard reference to the UMaterialInstance asset.
	*
	* return Material
	*/
	UMaterialInstance* GetSafe()
	{
		if (!Material.ToSoftObjectPath().IsValid())
			return nullptr;
		return Material_Internal;
	}

	CS_STRUCT_OPS_IS_VALID_CHECKED(FCsMaterialInstance)
	CS_STRUCT_OPS_IS_VALID(FCsMaterialInstance)
	CS_STRUCT_OPS_IS_TOP_VALID_CHECKED(FCsMaterialInstance)
	CS_STRUCT_OPS_IS_TOP_VALID(FCsMaterialInstance)

	FORCEINLINE bool IsValidChecked(const FString& Context) const
	{
		check(GetChecked(Context));
		return true;
	}

	FORCEINLINE bool IsValid(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const
	{
		if (!GetSafe(Context, Log))
			return false;
		return true;
	}

	FORCEINLINE bool IsTopValidChecked(const FString& Context) const
	{
		checkf(Material.ToSoftObjectPath().IsValid(), TEXT("%s: Material's Path is NOT Valid."), *Context);
		return true;
	}

	FORCEINLINE bool IsTopValid(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const
	{
		if (!Material.ToSoftObjectPath().IsValid())
		{
			if (Log)
				Log(FString::Printf(TEXT("%s: Material's Path is NOT Valid."), *Context));
			return false;
		}
		return true;
	}

	CS_STRUCT_OPS_DATA_UNLOAD(FCsMaterialInstance)

	FORCEINLINE void Unload()
	{
		Material.ResetWeakPtr();
		Material_Internal = nullptr;
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

	UPROPERTY(BlueprintReadOnly, Category = "CsCore|Material", meta = (Bitmask, BitmaskEnum = "/Script/CsCore.ECsLoadFlags"))
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

	/**
	* Get the Hard reference to the UMaterialInstanceConstant asset.
	*
	* return Material
	*/
	FORCEINLINE UMaterialInstanceConstant* Get() const
	{
		return Material_Internal;
	}

	/**
	* Get the pointer to the Hard reference to the UMaterialInstanceConstant asset.
	*
	* return Material
	*/
	FORCEINLINE UMaterialInstanceConstant** GetPtr() { return &Material_Internal; }

	/**
	* Get the Hard reference to the UMaterialInstanceConstant asset.
	*
	* @param Context	The calling context.
	* return			Material
	*/
	FORCEINLINE UMaterialInstanceConstant* GetChecked() const 
	{
		checkf(Material.ToSoftObjectPath().IsValid(), TEXT("FCsMaterialInstanceConstant::GetChecked: Material's Path is NOT Valid."));
		checkf(Material_Internal, TEXT("FCsMaterialInstanceConstant::GetChecked: Material has NOT been loaded from Path @ %s."), *(Material.ToSoftObjectPath().ToString()));

		return Material_Internal;
	}

	/**
	* Get the Hard reference to the UMaterialInstanceConstant asset.
	*
	* return Material
	*/
	FORCEINLINE UMaterialInstanceConstant* GetChecked(const FString& Context) const
	{
		checkf(Material.ToSoftObjectPath().IsValid(), TEXT("%s: Material's Path is NOT Valid."), *Context);
		checkf(Material_Internal, TEXT("%s: Material has NOT been loaded from Path @ %s."), *Context, *(Material.ToSoftObjectPath().ToString()));

		return Material_Internal;
	}

	/**
	* Safely get the Hard reference to the UMaterialInstanceConstant asset.
	*
	* @param Context	The calling context.
	* @param Log		(optional)
	* return			Material
	*/
	UMaterialInstanceConstant* GetSafe(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const
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
	* Safely get the Hard reference to the UMaterialInstanceConstant asset.
	*
	* return Material
	*/
	UMaterialInstanceConstant* GetSafe()
	{
		if (!Material.ToSoftObjectPath().IsValid())
			return nullptr;
		return Material_Internal;
	}

	CS_STRUCT_OPS_IS_VALID_CHECKED(FCsMaterialInstanceConstant)
	CS_STRUCT_OPS_IS_VALID(FCsMaterialInstanceConstant)
	CS_STRUCT_OPS_IS_TOP_VALID_CHECKED(FCsMaterialInstanceConstant)
	CS_STRUCT_OPS_IS_TOP_VALID(FCsMaterialInstanceConstant)

	FORCEINLINE bool IsValidChecked(const FString& Context) const
	{
		check(GetChecked(Context));
		return true;
	}

	FORCEINLINE bool IsValid(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const
	{
		if (!GetSafe(Context, Log))
			return false;
		return true;
	}

	FORCEINLINE bool IsTopValidChecked(const FString& Context) const
	{
		checkf(Material.ToSoftObjectPath().IsValid(), TEXT("%s: Material's Path is NOT Valid."), *Context);
		return true;
	}

	FORCEINLINE bool IsTopValid(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const
	{
		if (!Material.ToSoftObjectPath().IsValid())
		{
			if (Log)
				Log(FString::Printf(TEXT("%s: Material's Path is NOT Valid."), *Context));
			return false;
		}
		return true;
	}

	CS_STRUCT_OPS_DATA_UNLOAD(FCsMaterialInstanceConstant)

	FORCEINLINE void Unload()
	{
		Material.ResetWeakPtr();
		Material_Internal = nullptr;
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

	UPROPERTY(BlueprintReadWrite, Category = "CsCore|Material", meta = (Bitmask, BitmaskEnum = "/Script/CsCore.ECsLoadFlags"))
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

	/**
	* Safely get the Hard reference to the Material at Index of type: UMaterialInterface.
	*
	* @param Context	The calling context.
	* @param Index
	* @param Log		(optional)
	* return			Materials
	*/
	UMaterialInterface* GetSafeAt(const FString& Context, const int32& Index, void(*Log)(const FString&) = &FCsLog::Warning) const
	{
		if (Index < 0)
		{
			if (Log)
				Log(FString::Printf(TEXT("%s: Index: %d is NOT Valid."), *Context, Index));
			return nullptr;
		}

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

		if (Index > Materials.Num())
		{
			if (Log)
				Log(FString::Printf(TEXT("%s: Index: %d > number (%d) of Materials."), *Context, Index, Materials.Num()));
			return nullptr;
		}

		const TSoftObjectPtr<UMaterialInterface>& SoftObject = Materials[Index];

		if (!SoftObject.ToSoftObjectPath().IsValid())
		{
			if (Log)
				Log(FString::Printf(TEXT("%s: Materials[%d] is NULL."), *Context, Index));
			return nullptr;
		}

		UMaterialInterface* Material = Materials_Internal[Index];

		if (!Material)
		{
			if (Log)
				Log(FString::Printf(TEXT("%s: Materials[%d] has NOT been loaded from Path @ %s."), *Context, Index, *(SoftObject.ToSoftObjectPath().ToString())));
			return nullptr;
		}
		return Material;
	}

	void SetChecked(const FString& Context, UPrimitiveComponent* Component) const;

	bool SetSafe(const FString& Context, UPrimitiveComponent* Component, void(*Log)(const FString&) = &FCsLog::Warning) const;

	CS_STRUCT_OPS_IS_VALID_CHECKED(FCsTArrayMaterialInterface)
	CS_STRUCT_OPS_IS_VALID(FCsTArrayMaterialInterface)
	CS_STRUCT_OPS_IS_TOP_VALID_CHECKED(FCsTArrayMaterialInterface)
	CS_STRUCT_OPS_IS_TOP_VALID(FCsTArrayMaterialInterface)

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

	bool IsTopValidChecked(const FString& Context) const
	{
		checkf(Materials.Num() > CS_EMPTY, TEXT("%s: No Materials set."), *Context);
		const int32 Count = Materials.Num();

		for (int32 I = 0; I < Count; ++I)
		{
			const TSoftObjectPtr<UMaterialInterface>& SoftObject = Materials[I];

			checkf(SoftObject.ToSoftObjectPath().IsValid(), TEXT("%s: Materials[%d]'s Path is NOT Valid."), *Context, I);
		}
		return true;
	}

	bool IsTopValid(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const
	{
		if (Materials.Num() == CS_EMPTY)
		{
			if (Log)
				Log(FString::Printf(TEXT("%s: No Materials set."), *Context));
			return false;
		}

		const int32 Count = Materials.Num();

		for (int32 I = 0; I < Count; ++I)
		{
			const TSoftObjectPtr<UMaterialInterface>& SoftObject = Materials[I];

			if (!SoftObject.ToSoftObjectPath().IsValid())
			{
				if (Log)
					Log(FString::Printf(TEXT("%s: Materials[%d]'s Path is NOT Valid."), *Context, I));
				return false;
			}
		}
		return true;
	}

	CS_STRUCT_OPS_DATA_UNLOAD(FCsTArrayMaterialInterface)

	FORCEINLINE void Unload()
	{
		for (TSoftObjectPtr<UMaterialInterface>& Material : Materials)
		{
			Material.ResetWeakPtr();
		}
		Materials_Internal.Reset();
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

	UPROPERTY(BlueprintReadOnly, Category = "CsCore|Material", meta = (Bitmask, BitmaskEnum = "/Script/CsCore.ECsLoadFlags"))
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

	/**
	* Get the Hard references to the array of Materials of type: UMaterialInstanceConstant.
	*
	* @param Context	The calling context.
	* return			Materials
	*/
	FORCEINLINE const TArray<UMaterialInstanceConstant*>& GetChecked(const FString& Context) const
	{ 
		checkf(Materials.Num() > CS_EMPTY, TEXT("%s: No Materials set."), *Context);
		checkf(Materials.Num() == Materials_Internal.Num(), TEXT("%s: Mismatch between Soft and Hard references to materials, %d != %d."), *Context, Materials.Num(), Materials_Internal.Num());

		const int32 Count = Materials.Num();

		for (int32 I = 0; I < Count; ++I)
		{
			const TSoftObjectPtr<UMaterialInstanceConstant>& SoftObject = Materials[I];

			checkf(SoftObject.ToSoftObjectPath().IsValid(), TEXT("%s: Materials[%d] is NULL."), *Context, I);

			UMaterialInstanceConstant* Material = Materials_Internal[I];
	
			checkf(Material, TEXT("%s: Materials[%d] has NOT been loaded from Path @ %s."), *Context, I, *(SoftObject.ToSoftObjectPath().ToString()));
		}
		return Materials_Internal; 
	}

	/**
	* Get the Hard references to the array of Materials of type: UMaterialInstanceConstant.
	*
	* @param Context	The calling context.
	* return			Materials
	*/
	FORCEINLINE const TArray<UMaterialInstanceConstant*>& GetChecked() const
	{
		checkf(Materials.Num() > CS_EMPTY, TEXT("FCsTArrayMaterialInstanceConstant::GetChecked: No Materials set."));
		checkf(Materials.Num() == Materials_Internal.Num(), TEXT("FCsTArrayMaterialInstanceConstant::GetChecked: Mismatch between Soft and Hard references to materials, %d != %d."), Materials.Num(), Materials_Internal.Num());

		const int32 Count = Materials.Num();

		for (int32 I = 0; I < Count; ++I)
		{
			const TSoftObjectPtr<UMaterialInstanceConstant>& SoftObject = Materials[I];

			checkf(SoftObject.ToSoftObjectPath().IsValid(), TEXT("FCsTArrayMaterialInstanceConstant::GetChecked: Materials[%d] is NULL."), I);

			UMaterialInstanceConstant* Material = Materials_Internal[I];

			checkf(Material, TEXT("FCsTArrayMaterialInstanceConstant::GetChecked: Materials[%d] has NOT been loaded from Path @ %s."), I, *(SoftObject.ToSoftObjectPath().ToString()));
		}
		return Materials_Internal;
	}

	/**
	* Get the Hard reference to the Material at Index of type: UMaterialInstanceConstant.
	*
	* @param Context	The calling context.
	* @param Index
	* return			Material
	*/
	FORCEINLINE UMaterialInstanceConstant* GetChecked(const FString& Context, const int32& Index) const
	{
		checkf(Index >= 0 && Index < Materials_Internal.Num(), TEXT("%s: Index: %d is NOT in the range [0, %d)."), *Context, Index, Materials_Internal.Num());
		return GetChecked(Context)[Index];
	}

	/**
	* Safely get the Hard reference to the array of Materials of type: UMaterialInstanceConstant.
	*
	* @param Context	The calling context.
	* @param Log		(optional)
	* return			Materials
	*/
	const TArray<UMaterialInstanceConstant*>* GetSafe(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const
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
			const TSoftObjectPtr<UMaterialInstanceConstant>& SoftObject = Materials[I];

			if (!SoftObject.ToSoftObjectPath().IsValid())
			{
				if (Log)
					Log(FString::Printf(TEXT("%s: Materials[%d] is NULL."), *Context, I));
				return nullptr;
			}

			UMaterialInstanceConstant* Material = Materials_Internal[I];

			if (!Material)
			{
				if (Log)
					Log(FString::Printf(TEXT("%s: Materials[%d] has NOT been loaded from Path @ %s."), *Context, I, *(SoftObject.ToSoftObjectPath().ToString())));
				return nullptr;
			}
		}
		return &Materials_Internal;
	}

	/**
	* Safely get the Hard reference to the Material at Index of type: UMaterialInstanceConstant.
	*
	* @param Context	The calling context.
	* @param Index
	* @param Log		(optional)
	* return			Materials
	*/
	UMaterialInstanceConstant* GetSafeAt(const FString& Context, const int32& Index, void(*Log)(const FString&) = &FCsLog::Warning) const
	{
		if (Index < 0)
		{
			if (Log)
				Log(FString::Printf(TEXT("%s: Index: %d is NOT Valid."), *Context, Index));
			return nullptr;
		}

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

		if (Index > Materials.Num())
		{
			if (Log)
				Log(FString::Printf(TEXT("%s: Index: %d > number (%d) of Materials."), *Context, Index, Materials.Num()));
			return nullptr;
		}

		const TSoftObjectPtr<UMaterialInstanceConstant>& SoftObject = Materials[Index];

		if (!SoftObject.ToSoftObjectPath().IsValid())
		{
			if (Log)
				Log(FString::Printf(TEXT("%s: Materials[%d] is NULL."), *Context, Index));
			return nullptr;
		}

		UMaterialInstanceConstant* Material = Materials_Internal[Index];

		if (!Material)
		{
			if (Log)
				Log(FString::Printf(TEXT("%s: Materials[%d] has NOT been loaded from Path @ %s."), *Context, Index, *(SoftObject.ToSoftObjectPath().ToString())));
			return nullptr;
		}
		return Material;
	}

	CS_STRUCT_OPS_IS_VALID_CHECKED(FCsTArrayMaterialInstanceConstant)
	CS_STRUCT_OPS_IS_VALID(FCsTArrayMaterialInstanceConstant)
	CS_STRUCT_OPS_IS_TOP_VALID_CHECKED(FCsTArrayMaterialInstanceConstant)
	CS_STRUCT_OPS_IS_TOP_VALID(FCsTArrayMaterialInstanceConstant)

	bool IsValidChecked(const FString& Context) const
	{
		checkf(Materials.Num() > CS_EMPTY, TEXT("%s: No Materials set."), *Context);
		checkf(Materials.Num() == Materials_Internal.Num(), TEXT("%s: Mismatch between Soft and Hard references to materials, %d != %d."), *Context, Materials.Num(), Materials_Internal.Num());

		const int32 Count = Materials.Num();

		for (int32 I = 0; I < Count; ++I)
		{
			const TSoftObjectPtr<UMaterialInstanceConstant>& SoftObject = Materials[I];

			checkf(SoftObject.ToSoftObjectPath().IsValid(), TEXT("%s: Materials[%d] is NULL."), *Context, I);

			UMaterialInstanceConstant* Material = Materials_Internal[I];

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
			const TSoftObjectPtr<UMaterialInstanceConstant>& SoftObject = Materials[I];

			if (!SoftObject.ToSoftObjectPath().IsValid())
			{
				if (Log)
					Log(FString::Printf(TEXT("%s: Materials[%d] is NULL."), *Context, I));
				return false;
			}

			UMaterialInstanceConstant* Material = Materials_Internal[I];

			if (!Material)
			{
				if (Log)
					Log(FString::Printf(TEXT("%s: Materials[%d] has NOT been loaded from Path @ %s."), *Context, I, *(SoftObject.ToSoftObjectPath().ToString())));
				return false;
			}
		}
		return true;
	}

	bool IsTopValidChecked(const FString& Context) const
	{
		checkf(Materials.Num() > CS_EMPTY, TEXT("%s: No Materials set."), *Context);
		const int32 Count = Materials.Num();

		for (int32 I = 0; I < Count; ++I)
		{
			const TSoftObjectPtr<UMaterialInstanceConstant>& SoftObject = Materials[I];

			checkf(SoftObject.ToSoftObjectPath().IsValid(), TEXT("%s: Materials[%d]'s Path is NOT Valid."), *Context, I);
		}
		return true;
	}

	bool IsTopValid(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const
	{
		if (Materials.Num() == CS_EMPTY)
		{
			if (Log)
				Log(FString::Printf(TEXT("%s: No Materials set."), *Context));
			return false;
		}

		const int32 Count = Materials.Num();

		for (int32 I = 0; I < Count; ++I)
		{
			const TSoftObjectPtr<UMaterialInstanceConstant>& SoftObject = Materials[I];

			if (!SoftObject.ToSoftObjectPath().IsValid())
			{
				if (Log)
					Log(FString::Printf(TEXT("%s: Materials[%d]'s Path is NOT Valid."), *Context, I));
				return false;
			}
		}
		return true;
	}

	CS_STRUCT_OPS_DATA_UNLOAD(FCsTArrayMaterialInstanceConstant)

	FORCEINLINE void Unload()
	{
		for (TSoftObjectPtr<UMaterialInstanceConstant>& Material : Materials)
		{
			Material.ResetWeakPtr();
		}
		Materials_Internal.Reset();
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

	UPROPERTY(EditAnywhere, Category = "CsCore|Material", meta = (Bitmask, BitmaskEnum = "/Script/CsCore.ECsLoadFlags"))
	int32 Materials1P_LoadFlags;

	UPROPERTY(EditAnywhere, Category = "CsCore|Material", meta = (Bitmask, BitmaskEnum = "/Script/CsCore.ECsLoadFlags"))
	int32 Materials3P_LoadFlags;

	UPROPERTY(EditAnywhere, Category = "CsCore|Material", meta = (Bitmask, BitmaskEnum = "/Script/CsCore.ECsLoadFlags"))
	int32 Materials3P_Low_LoadFlags;

	UPROPERTY(EditAnywhere, Category = "CsCore|Material", meta = (Bitmask, BitmaskEnum = "/Script/CsCore.ECsLoadFlags"))
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

	CS_STRUCT_OPS_DATA_UNLOAD(FCsFpsTArrayMaterialInstanceConstant)

	FORCEINLINE void Unload()
	{
		for (TSoftObjectPtr<UMaterialInstanceConstant>& Material : Materials1P)
		{
			Material.ResetWeakPtr();
		}
		for (TSoftObjectPtr<UMaterialInstanceConstant>& Material : Materials3P)
		{
			Material.ResetWeakPtr();
		}
		for (TSoftObjectPtr<UMaterialInstanceConstant>& Material : Materials3P_Low)
		{
			Material.ResetWeakPtr();
		}
		for (TSoftObjectPtr<UMaterialInstanceConstant>& Material : MaterialsVR)
		{
			Material.ResetWeakPtr();
		}
		Materials1P_Internal.Reset();
		Materials3P_Internal.Reset();
		Materials3P_Low_Internal.Reset();
		MaterialsVR_Internal.Reset();
	}
};

#pragma endregion FCsFpsTArrayMaterialInstanceConstant

// FCsMaterialParameterFloat
#pragma region

// NCsMaterial::NParameter::NFloat::FValue
CS_FWD_DECLARE_STRUCT_NAMESPACE_3(NCsMaterial, NParameter, NFloat, FValue)

class UMaterialInterface;
class UMaterialInstanceDynamic;

/**
* Describes a Material Float Parameters (Scalar as float).
*/
USTRUCT(BlueprintType)
struct CSCORE_API FCsMaterialParameterFloat
{
	GENERATED_USTRUCT_BODY()

	/** The name of the scalar parameter */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Material")
	FName Name;

	/** The scalar value */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Material")
	float Value;

	FCsMaterialParameterFloat() :
		Name(NAME_None),
		Value(0.0f)
	{
	}

#define ParamsType NCsMaterial::NParameter::NFloat::FValue
	void CopyToParams(ParamsType* Params);
	void CopyToParamsAsValue(ParamsType* Params) const;
#undef ParamsType

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const;

	bool IsValidChecked(const FString& Context, UMaterialInterface* Material) const;
	bool IsValid(const FString& Context, UMaterialInterface* Material, void(*Log)(const FString&) = &FCsLog::Warning) const;

	void SetChecked(const FString& Context, UMaterialInstanceDynamic* MID) const;
	bool SetSafe(const FString& Context, UMaterialInstanceDynamic* MID, void(*Log)(const FString&) = &FCsLog::Warning) const;
};

namespace NCsMaterial
{
	namespace NParameter
	{
		namespace NFloat
		{
			/**
			* Describes a Material Float Parameters (Scalar as float).
			*/
			struct CSCORE_API FValue final
			{
			private:

				/** The name of the scalar parameter */
				CS_DECLARE_MEMBER_WITH_PROXY(Name, FName)

					/** The scalar value */
				CS_DECLARE_MEMBER_WITH_PROXY(Value, float)

			public:

				FValue() :
					CS_CTOR_INIT_MEMBER_WITH_PROXY(Name, NAME_None),
					CS_CTOR_INIT_MEMBER_WITH_PROXY(Value, 0.0f)
				{
					CS_CTOR_SET_MEMBER_PROXY(Name);
					CS_CTOR_SET_MEMBER_PROXY(Value);
				}

				CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Name, FName)
				CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Value, float)
	
				bool IsValidChecked(const FString& Context) const;
				bool IsValid(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const;

				bool IsValidChecked(const FString& Context, UMaterialInterface* Material) const;
				bool IsValid(const FString& Context, UMaterialInterface* Material, void(*Log)(const FString&) = &FCsLog::Warning) const;

				void CopyAsValue(const FValue& From)
				{
					SetName(From.GetName());
					SetValue(From.GetValue());
				}

				void SetChecked(const FString& Context, UMaterialInstanceDynamic* MID) const;
				bool SetSafe(const FString& Context, UMaterialInstanceDynamic* MID, void(*Log)(const FString&) = &FCsLog::Warning) const;
			};
		}
	}
}

#pragma endregion FCsMaterialParameterFloat

// FCsMaterialParameterFloatRange
#pragma region

// NCsMaterial::NParameter::NFloat::FRange
CS_FWD_DECLARE_STRUCT_NAMESPACE_3(NCsMaterial, NParameter, NFloat, FRange)

class UMaterialInterface;
class UMaterialInstanceDynamic;

/**
* Describes a Material Float Parameters (Scalar as float) with
* a Min and Max value.
*/
USTRUCT(BlueprintType)
struct CSCORE_API FCsMaterialParameterFloatRange
{
	GENERATED_USTRUCT_BODY()

	/** The name of scalar parameter */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Material")
	FName Name;

	/** The minimum scalar value */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Material")
	float Min;

	/** The maximum scalar value */
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
			/**
			* Describes a Material Float Parameters (Scalar as float) with
			* a Min and Max value.
			*/
			struct CSCORE_API FRange final
			{
			private:

				/** The name of scalar parameter */
				CS_DECLARE_MEMBER_WITH_PROXY(Name, FName)

				/** The minimum scalar value */
				CS_DECLARE_MEMBER_WITH_PROXY(Min, float)

				/** The maximum scalar value */
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

// NCsMaterial::NParameter::NColor::FValue
CS_FWD_DECLARE_STRUCT_NAMESPACE_3(NCsMaterial, NParameter, NColor, FValue)

class UMaterialInterface;
class UMaterialInstanceDynamic;

/**
* Describes a Material Color Parameter (Vector as FLinearColor).
*/
USTRUCT(BlueprintType)
struct CSCORE_API FCsMaterialParameterColor
{
	GENERATED_USTRUCT_BODY()

	/** The name of vector parameter */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Material")
	FName Name;

	/** The vector value */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Material")
	FLinearColor Value;

	FCsMaterialParameterColor() :
		Name(NAME_None),
		Value(FLinearColor::White)
	{
	}

#define ParamsType NCsMaterial::NParameter::NColor::FValue
	void CopyToParams(ParamsType* Params);
	void CopyToParamsAsValue(ParamsType* Params) const;
#undef ParamsType

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const;

	bool IsValidChecked(const FString& Context, UMaterialInterface* Material) const;
	bool IsValid(const FString& Context, UMaterialInterface* Material, void(*Log)(const FString&) = &FCsLog::Warning) const;

	void SetChecked(const FString& Context, UMaterialInstanceDynamic* MID) const;
	bool SetSafe(const FString& Context, UMaterialInstanceDynamic* MID, void(*Log)(const FString&) = &FCsLog::Warning) const;
};

namespace NCsMaterial
{
	namespace NParameter
	{
		namespace NColor
		{
			/**
			* Describes a Material Color Parameters (Vector as FLinearColor).
			*/
			struct CSCORE_API FValue final
			{
			private:

				/** The name of vector parameter */
				CS_DECLARE_MEMBER_WITH_PROXY(Name, FName)

				/** The vector value */
				CS_DECLARE_MEMBER_WITH_PROXY(Value, FLinearColor)

			public:

				FValue() :
					CS_CTOR_INIT_MEMBER_WITH_PROXY(Name, NAME_None),
					CS_CTOR_INIT_MEMBER_WITH_PROXY(Value, FLinearColor::White)
				{
					CS_CTOR_SET_MEMBER_PROXY(Name);
					CS_CTOR_SET_MEMBER_PROXY(Value);
				}

				CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Name, FName)
				CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Value, FLinearColor)
	
				bool IsValidChecked(const FString& Context) const;
				bool IsValid(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const;

				bool IsValidChecked(const FString& Context, UMaterialInterface* Material) const;
				bool IsValid(const FString& Context, UMaterialInterface* Material, void(*Log)(const FString&) = &FCsLog::Warning) const;

				void CopyAsValue(const FValue& From)
				{
					SetName(From.GetName());
					SetValue(From.GetValue());
				}

				void SetChecked(const FString& Context, UMaterialInstanceDynamic* MID) const;
				bool SetSafe(const FString& Context, UMaterialInstanceDynamic* MID, void(*Log)(const FString&) = &FCsLog::Warning) const;
			};
		}
	}
}

#pragma endregion FCsMaterialParameterColor

// FCsMaterialParameterColorRange
#pragma region

// NCsMaterial::NParameter::NColor::FRange
CS_FWD_DECLARE_STRUCT_NAMESPACE_3(NCsMaterial, NParameter, NColor, FRange)

class UMaterialInstanceDynamic;

/**
* Describes a Material Color Parameters (Vector as FLinearColor) with
* a From and To value.
*/
USTRUCT(BlueprintType)
struct CSCORE_API FCsMaterialParameterColorRange
{
	GENERATED_USTRUCT_BODY()

	/** The name of vector parameter */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Material")
	FName Name;

	/** The "from" or start value used in a lerp */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Material")
	FLinearColor From;

	/** The "to" or end value used in a lerp */
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
			/**
			* Describes a Material Color Parameters (Vector as FLinearColor) with
			* a From and To value.
			*/
			struct CSCORE_API FRange final
			{
			private:

				/** The name of vector parameter */
				CS_DECLARE_MEMBER_WITH_PROXY(Name, FName)

				/** The "from" or start value used in a lerp */
				CS_DECLARE_MEMBER_WITH_PROXY(From, FLinearColor)

				/** The "to" or end value used in a lerp */
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

// FCsMaterialInterface_WithParameters
#pragma region

// NCsMaterial::NInterface::FWithParameters
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsMaterial, NInterface, FWithParameters)

class UPrimitiveComponent;
class UMaterialInstanceDynamic;

/**
* Wrapper for a reference to a Material with Parameters.
*/
USTRUCT(BlueprintType)
struct CSCORE_API FCsMaterialInterface_WithParameters
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Material")
	FCsMaterialInterface Material;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Material")
	TArray<FCsMaterialParameterFloat> FloatParameters;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Material")
	TArray<FCsMaterialParameterColor> ColorParameters;

	FCsMaterialInterface_WithParameters() :
		Material(),
		FloatParameters(),
		ColorParameters()
	{
	}

#define MaterialType NCsMaterial::NInterface::FWithParameters
	void CopyToMaterial(MaterialType* Mat);
	void CopyToMaterialAsValue(MaterialType* Mat) const;
#undef MaterialType

	CS_STRUCT_OPS_IS_VALID_CHECKED(FCsMaterialInterface_WithParameters)
	CS_STRUCT_OPS_IS_VALID(FCsMaterialInterface_WithParameters)
	CS_STRUCT_OPS_IS_TOP_VALID_CHECKED(FCsMaterialInterface_WithParameters)
	CS_STRUCT_OPS_IS_TOP_VALID(FCsMaterialInterface_WithParameters)

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const;
	bool IsTopValidChecked(const FString& Context) const;
	bool IsTopValid(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const;

	void SetChecked(const FString& Context, UPrimitiveComponent* Component, const int32& Index, UMaterialInstanceDynamic*& OutMID) const;
	bool SetSafe(const FString& Context, UPrimitiveComponent* Component, const int32& Index, UMaterialInstanceDynamic*& OutMID, void(*Log)(const FString&) = &FCsLog::Warning) const;

	CS_STRUCT_OPS_DATA_UNLOAD(FCsMaterialInterface_WithParameters)

	FORCEINLINE void Unload()
	{
		Material.Unload();
	}
};

class UMaterialInterface;

namespace NCsMaterial
{
	namespace NInterface
	{
		/**
		* Wrapper for a reference to a Material with Parameters with defined ranges.
		*  Usually the Material is set on a Primitive Component with Parameters set with
		*  random values within the defined ranges.
		*/
		struct CSCORE_API FWithParameters final
		{
		#define FloatParameterType NCsMaterial::NParameter::NFloat::FValue
		#define ColorParameterType NCsMaterial::NParameter::NColor::FValue

		private:

			CS_DECLARE_MEMBER_WITH_PROXY(Material, UMaterialInterface*)
			CS_DECLARE_MEMBER_WITH_PROXY(FloatParameters, TArray<FloatParameterType>)
			CS_DECLARE_MEMBER_WITH_PROXY(ColorParameters, TArray<ColorParameterType>)

		public:

			FWithParameters() :
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

			void CopyAsValue(const FWithParameters& From)
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

			void SetChecked(const FString& Context, UPrimitiveComponent* Component, const int32& Index) const;
			bool SetSafe(const FString& Context, UPrimitiveComponent* Component, const int32& Index, void(*Log)(const FString&) = &FCsLog::Warning) const;

		#undef FloatParameterType
		#undef ColorParameterType
		};
	}
}

#pragma endregion FCsMaterialInterface_WithParameters

// FCsMaterialInterface_WithRangeParameters
#pragma region

// NCsMaterial::NInterface::FWithRangeParameters
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsMaterial, NInterface, FWithRangeParameters)

class UPrimitiveComponent;
class UMaterialInstanceDynamic;

/**
* Wrapper for a reference to a Material with Parameters with defined ranges.
*  Usually the Material is set on a Primitive Component with Parameters set with
*  random values within the defined ranges.
*/
USTRUCT(BlueprintType)
struct CSCORE_API FCsMaterialInterface_WithRangeParameters
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Material")
	FCsMaterialInterface Material;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Material")
	TArray<FCsMaterialParameterFloatRange> FloatParameters;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Material")
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

	CS_STRUCT_OPS_IS_VALID_CHECKED(FCsMaterialInterface_WithRangeParameters)
	CS_STRUCT_OPS_IS_VALID(FCsMaterialInterface_WithRangeParameters)
	CS_STRUCT_OPS_IS_TOP_VALID_CHECKED(FCsMaterialInterface_WithRangeParameters)
	CS_STRUCT_OPS_IS_TOP_VALID(FCsMaterialInterface_WithRangeParameters)

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const;
	bool IsTopValidChecked(const FString& Context) const;
	bool IsTopValid(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const;

	void SetChecked(const FString& Context, UPrimitiveComponent* Component, const int32& Index, UMaterialInstanceDynamic*& OutMID) const;
	bool SetSafe(const FString& Context, UPrimitiveComponent* Component, const int32& Index, UMaterialInstanceDynamic*& OutMID, void(*Log)(const FString&) = &FCsLog::Warning) const;

	CS_STRUCT_OPS_DATA_UNLOAD(FCsMaterialInterface_WithRangeParameters)

	FORCEINLINE void Unload()
	{
		Material.Unload();
	}
};

class UMaterialInterface;

namespace NCsMaterial
{
	namespace NInterface
	{
		/**
		* Wrapper for a reference to a Material with Parameters with defined ranges.
		*  Usually the Material is set on a Primitive Component with Parameters set with
		*  random values within the defined ranges.
		*/
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

			void SetChecked(const FString& Context, UPrimitiveComponent* Component, const int32& Index) const;
			bool SetSafe(const FString& Context, UPrimitiveComponent* Component, const int32& Index, void(*Log)(const FString&) = &FCsLog::Warning) const;

		#undef FloatParameterType
		#undef ColorParameterType
		};
	}
}

#pragma endregion FCsMaterialInterface_WithRangeParameters

// FCsMaterialParameterCollection
#pragma region

class UMaterialParameterCollection;

USTRUCT(BlueprintType)
struct CSCORE_API FCsMaterialParameterCollection
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Material")
	TSoftObjectPtr<UMaterialParameterCollection> Collection;

	UPROPERTY(BlueprintReadOnly, Category = "CsCore|Material", meta = (Bitmask, BitmaskEnum = "/Script/CsCore.ECsLoadFlags"))
	int32 Collection_LoadFlags;

	UPROPERTY(Transient, BlueprintReadOnly, Category = "CsCore|Material")
	UMaterialParameterCollection* Collection_Internal;

public:

	FCsMaterialParameterCollection() :
		Collection(nullptr),
		Collection_LoadFlags(0),
		Collection_Internal(nullptr)
	{
	}

	/**
	* Get the Hard reference to the UMaterialParameterCollection asset.
	*
	* return Material Parameter Collection
	*/
	FORCEINLINE UMaterialParameterCollection* Get() const { return Collection_Internal; }

	/**
	* Get the pointer to the Hard reference to the UMaterialParameterCollection asset.
	*
	* return Material Parameter Collection
	*/
	FORCEINLINE UMaterialParameterCollection** GetPtr() { return &Collection_Internal; }

	/**
	* Get the Hard reference to the UMaterialParameterCollection asset.
	*
	* @param Context	The calling context.
	* return			Material Parameter Collection
	*/
	FORCEINLINE UMaterialParameterCollection* GetChecked(const FString& Context) const
	{
		checkf(Collection.ToSoftObjectPath().IsValid(), TEXT("%s: Collection's Path is NOT Valid."), *Context);
		checkf(Collection_Internal, TEXT("%s: Collection has NOT been loaded from Path @ %s."), *Context, *(Collection.ToSoftObjectPath().ToString()));

		return Collection_Internal;
	}

	/**
	* Get the Hard reference to the UMaterialParameterCollection asset.
	*
	* return Material Parameter Collection
	*/
	FORCEINLINE UMaterialParameterCollection* GetChecked() const
	{
		checkf(Collection.ToSoftObjectPath().IsValid(), TEXT("FCsMaterialParameterCollection::GetChecked: Collection's Path is NOT Valid."));
		checkf(Collection_Internal, TEXT("FCsMaterialParameterCollection::GetChecked: Collection has NOT been loaded from Path @ %s."), *(Collection.ToSoftObjectPath().ToString()));

		return Collection_Internal;
	}

	/**
	* Safely get the Hard reference to the UMaterialParameterCollection asset.
	*
	* @param Context	The calling context.
	* @param Log		(optional)
	* return			Material Parameter Collection
	*/
	UMaterialParameterCollection* GetSafe(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const
	{
		if (!Collection.ToSoftObjectPath().IsValid())
		{
			if (Log)
				Log(FString::Printf(TEXT("%s: Collection's Path is NOT Valid."), *Context));
			return nullptr;
		}

		if (!Collection_Internal)
		{
			if (Log)
				Log(FString::Printf(TEXT("%s: Collection has NOT been loaded from Path @ %s."), *Context, *(Collection.ToSoftObjectPath().ToString())));
		}
		return Collection_Internal;
	}

	/**
	* Safely get the Hard reference to the UMaterialParameterCollection asset.
	*
	* return Material Parameter Collection
	*/
	UMaterialParameterCollection* GetSafe()
	{
		if (!Collection.ToSoftObjectPath().IsValid())
			return nullptr;
		return Collection_Internal;
	}

	CS_STRUCT_OPS_IS_VALID_CHECKED(FCsMaterialParameterCollection)
	CS_STRUCT_OPS_IS_VALID(FCsMaterialParameterCollection)
	CS_STRUCT_OPS_IS_TOP_VALID_CHECKED(FCsMaterialParameterCollection)
	CS_STRUCT_OPS_IS_TOP_VALID(FCsMaterialParameterCollection)

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

	bool IsTopValidChecked(const FString& Context) const
	{
		checkf(Collection.ToSoftObjectPath().IsValid(), TEXT("%s: Collection's Path is NOT Valid."), *Context);
		return true;
	}

	bool IsTopValid(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const
	{
		if (!Collection.ToSoftObjectPath().IsValid())
		{
			if (Log)
				Log(FString::Printf(TEXT("%s: Collection's Path is NOT Valid."), *Context));
			return false;
		}
		return true;
	}

	CS_STRUCT_OPS_DATA_UNLOAD(FCsMaterialParameterCollection)

	FORCEINLINE void Unload()
	{
		Collection.ResetWeakPtr();
		Collection_Internal = nullptr;
	}
};

#pragma endregion FCsMaterialParameterCollection