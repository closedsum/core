// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "Types/Enum/CsEnum_uint8.h"
#include "Types/Enum/CsEnumStructMap.h"
// DataTable
#include "Engine/DataTable.h"

#include "CsTypes_Beam.generated.h"

// Beam
#pragma region

USTRUCT(BlueprintType)
struct CSBEAM_API FECsBeam : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

	CS_ENUM_UINT8_BODY(FECsBeam)
};

CS_DEFINE_ENUM_UINT8_GET_TYPE_HASH(FECsBeam)

struct CSBEAM_API EMCsBeam : public TCsEnumStructMap<FECsBeam, uint8>
{
	CS_ENUM_STRUCT_MAP_BODY(EMCsBeam, FECsBeam, uint8)
};

struct FCsBeamDataRootSet;

namespace NCsBeam
{
	typedef EMCsBeam EnumMapType;
	typedef FECsBeam Type;

	FORCEINLINE void Create(const FString& Name, const bool& UserDefinedEnum) { EnumMapType::Get().Create(Name, UserDefinedEnum); }
	FORCEINLINE void CreateCustom(const FString& Name, const FString& DisplayName, const bool& UserDefinedEnum) { EnumMapType::Get().Create(Name, DisplayName, UserDefinedEnum); }
	FORCEINLINE bool IsValidEnum(const FString& Name) { return EnumMapType::Get().IsValidEnum(Name); }
	FORCEINLINE bool IsValidEnumByDisplayName(const FString& DisplayName) { return EnumMapType::Get().IsValidEnumByDisplayName(DisplayName); }

	CSBEAM_API void FromEnumSettings(const FString& Context);

	CSBEAM_API void FromDataTable(const FString& Context, UObject* ContextRoot);

	CSBEAM_API void PopulateEnumMapFromSettings(const FString& Context, UObject* ContextRoot);
}

#pragma endregion Beam

// BeamClass
#pragma region

USTRUCT(BlueprintType)
struct CSBEAM_API FECsBeamClass : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

	CS_ENUM_UINT8_BODY(FECsBeamClass)
};

CS_DEFINE_ENUM_UINT8_GET_TYPE_HASH(FECsBeamClass)

struct CSBEAM_API EMCsBeamClass : public TCsEnumStructMap<FECsBeamClass, uint8>
{
	CS_ENUM_STRUCT_MAP_BODY(EMCsBeamClass, FECsBeamClass, uint8)
};

namespace NCsBeamClass
{
	typedef EMCsBeamClass EnumMapType;
	typedef FECsBeamClass Type;

	FORCEINLINE void Create(const FString& Name, const bool& UserDefinedEnum) { EnumMapType::Get().Create(Name, UserDefinedEnum); }
	FORCEINLINE void CreateCustom(const FString& Name, const FString& DisplayName, const bool& UserDefinedEnum) { EnumMapType::Get().Create(Name, DisplayName, UserDefinedEnum); }
	FORCEINLINE bool IsValidEnum(const FString& Name) { return EnumMapType::Get().IsValidEnum(Name); }
	FORCEINLINE bool IsValidEnumByDisplayName(const FString& DisplayName) { return EnumMapType::Get().IsValidEnumByDisplayName(DisplayName); }

	CSBEAM_API void FromEnumSettings(const FString& Context);

	CSBEAM_API void FromDataTable(const FString& Context, UObject* ContextRoot);

	CSBEAM_API void PopulateEnumMapFromSettings(const FString& Context, UObject* ContextRoot);
}

#pragma endregion Beam

// FCsBeamPtr
#pragma region

class UObject;

USTRUCT(BlueprintType)
struct CSBEAM_API FCsBeamPtr
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsBeam", meta = (MustImplement = "/Script.CsBeam.CsBeam"))
	TSoftClassPtr<UObject> Beam;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsBeam")
	int32 Load_Flags;

	UPROPERTY(Transient, BlueprintReadOnly, Category = "CsBeam")
	UObject* Beam_Internal;

	UPROPERTY(Transient, BlueprintReadOnly, Category = "CsBeam")
	UClass* Beam_Class;

	FCsBeamPtr() :
		Beam(nullptr),
		Load_Flags(0),
		Beam_Internal(nullptr),
		Beam_Class(nullptr)
	{
	}

	FORCEINLINE UObject* Get() const { return Beam_Internal; }

	template<typename T>
	FORCEINLINE T* Get() const
	{
		return Cast<T>(Get());
	}

	FORCEINLINE UClass* GetClass() const { return Beam_Class; }
};

#pragma endregion FCsBeamPtr

// FCsData_BeamPtr
#pragma region

class UObject;

USTRUCT(BlueprintType)
struct CSBEAM_API FCsData_BeamPtr
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsBeam|Data", meta = (MustImplement = "/Script.CsBeam.CsData_Beam"))
	TSoftClassPtr<UObject> Data;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsBeam|Data")
	int32 Load_Flags;

	UPROPERTY(Transient, BlueprintReadOnly, Category = "CsBeam|Data")
	UObject* Data_Internal;

	UPROPERTY(Transient, BlueprintReadOnly, Category = "CsBeam|Data")
	UClass* Data_Class;

	FCsData_BeamPtr() :
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

#pragma endregion FCsData_BeamPtr

// FCsBeamClassEntry
#pragma region

/**
*/
USTRUCT(BlueprintType)
struct CSBEAM_API FCsBeamClassEntry : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	/** The enum (FECsBeam) name for the projectile class. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = DataTable)
	FString Name;

	/** The enum (FECsBeam) display name for the projectile class. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = DataTable)
	FString DisplayName;

	/** Soft Reference to a projectile of type: ICsBeam. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = DataTable)
	FCsBeamPtr Class;

	FCsBeamClassEntry() :
		Name(),
		DisplayName(), 
		Class()
	{
	}
};

#pragma endregion FCsBeamClassEntry

// FCsBeamEntry
#pragma region

/**
*/
USTRUCT(BlueprintType)
struct CSBEAM_API FCsBeamEntry : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	/** The enum (FECsBeam) name for the projectile. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = DataTable)
	FString Name;

	/** The enum (FECsBeam) display name for the projectile. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = DataTable)
	FString DisplayName;

	/** Class Type. This is used to get the actual class from a data table
	    of projectile classes (FCsBeamDataRootSet.BeamClasses). */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = DataTable)
	FECsBeamClass Class;

	/** Soft Reference to a data of type: ICsData_Beam. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = DataTable)
	FCsData_BeamPtr Data;

	FCsBeamEntry() :
		Name(),
		DisplayName(), 
		Class(),
		Data()
	{
	}
};

#pragma endregion FCsBeamEntry