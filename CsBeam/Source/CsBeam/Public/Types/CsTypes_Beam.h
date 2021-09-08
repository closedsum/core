// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Pool/CsTypes_Pool.h"
#include "Types/CsTypes_Load.h"
#include "Engine/DataTable.h"

#include "Managers/Pool/Payload/CsPayload_PooledObject.h"

#include "CsTypes_Beam.generated.h"
#pragma once

// BeamRelevance
#pragma region

UENUM(BlueprintType)
enum class ECsBeamRelevance : uint8
{
	RealVisible					UMETA(DisplayName = "Real Visible"),
	RealInvisible				UMETA(DisplayName = "Real Invisible"),
	Fake						UMETA(DisplayName = "Fake"),
	ECsBeamRelevance_MAX	UMETA(Hidden),
};

struct CSBEAM_API EMCsBeamRelevance : public TCsEnumMap<ECsBeamRelevance>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsBeamRelevance, ECsBeamRelevance)
};

namespace NCsBeamRelevance
{
	typedef ECsBeamRelevance Type;

	namespace Ref
	{
		extern CSBEAM_API const Type RealVisible;
		extern CSBEAM_API const Type RealInvisible;
		extern CSBEAM_API const Type Fake;
		extern CSBEAM_API const Type ECsBeamRelevance_MAX;
	}

	extern CSBEAM_API const uint8 MAX;
}

#pragma endregion BeamRelevance

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
	typedef FECsBeam Type;

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
	typedef FECsBeamClass Type;

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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (MustImplement = "CsBeam"))
	TSoftClassPtr<UObject> Beam;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 Load_Flags;

	UPROPERTY(Transient, BlueprintReadOnly)
	UObject* Beam_Internal;

	UPROPERTY(Transient, BlueprintReadOnly)
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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (MustImplement = "CsData_Beam"))
	TSoftClassPtr<UObject> Data;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 Load_Flags;

	UPROPERTY(Transient, BlueprintReadOnly)
	UObject* Data_Internal;

	UPROPERTY(Transient, BlueprintReadOnly)
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
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString Name;

	/** The enum (FECsBeam) display name for the projectile class. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString DisplayName;

	/** Soft Reference to a projectile of type: ICsBeam. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
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
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString Name;

	/** The enum (FECsBeam) display name for the projectile. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString DisplayName;

	/** Class Type. This is used to get the actual class from a data table
	    of projectile classes (FCsBeamDataRootSet.BeamClasses). */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FECsBeamClass Class;

	/** Soft Reference to a data of type: ICsData_Beam. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
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