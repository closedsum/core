// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "Managers/Sound/CsTypes_SoundPooled.h"
#include "Managers/Time/CsTypes_Update.h"

#include "CsSettings_Manager_Sound.generated.h"

// FCsSettings_Manager_Sound_PoolParams
#pragma region

/**
* Describes any pool parameters (i.e. class, pool size, payload size, ... etc) for each Sound type.
* These parameters are used when initially creating the pool.
*/
USTRUCT(BlueprintType)
struct CSSOUND_API FCsSettings_Manager_Sound_PoolParams
{
	GENERATED_USTRUCT_BODY()

public:

	/** The class of the pooled Sound. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Managers|Sound", meta = (MustImplement = "/Script/CsSound.CsSoundPooled"))
	TSoftClassPtr<UObject> Class; 
	/** The maximum size of the pool. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Managers|Sound", meta = (ClampMin = "4", UIMin = "4"))
	int32 PoolSize;
	/** The maximum payload size. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Managers|Sound", meta = (ClampMin = "4", UIMin = "4"))
	int32 PayloadSize;

	FCsSettings_Manager_Sound_PoolParams() :
		Class(nullptr),
		PoolSize(4),
		PayloadSize(4)
	{
	}
};

#pragma endregion FCsSettings_Manager_Sound_PoolParams

// FCsSettings_Manager_Sound_TypeArray
#pragma region

USTRUCT(BlueprintType)
struct CSSOUND_API FCsSettings_Manager_Sound_TypeArray
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Managers|Sound")
	TArray<FECsSound> Types;

	FCsSettings_Manager_Sound_TypeArray() :
		Types()
	{
	}
};

#pragma endregion FCsSettings_Manager_Sound_TypeArray

// FCsSettings_Manager_Sound
#pragma region

class UObject;
class UClass;
class UCsManager_Sound;

USTRUCT(BlueprintType)
struct CSSOUND_API FCsSettings_Manager_Sound
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Managers|Sound")
	TSoftClassPtr<UCsManager_Sound> Class;

	/** Mapping between Update Groups, the "tick" / update group, and Sound types. This
		is important to indicate when a particular Sound type WILL or will NOT get "ticked" or updated. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Managers|Sound")
	TMap<FECsUpdateGroup, FCsSettings_Manager_Sound_TypeArray> TypesByUpdateGroupMap;

	/** Describes any pool parameters (i.e. class, pool size, payload size, ... etc) for each Sound type. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Managers|Sound")
	TMap<FECsSound, FCsSettings_Manager_Sound_PoolParams> PoolParams;

	FCsSettings_Manager_Sound();

	static const FCsSettings_Manager_Sound& Get();

	bool IsValidChecked(const FString& Context) const;

	UClass* LoadClassChecked(const FString& Context) const;
};

#pragma endregion FCsSettings_Manager_Sound

// FCsSettings_Manager_Sound_UnitTest
#pragma region

class UObject;
class UClass;

USTRUCT(BlueprintType)
struct CSSOUND_API FCsSettings_Manager_Sound_UnitTest
{
	GENERATED_USTRUCT_BODY()

public:

	/** Map used for testing. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Managers|Sound", meta = (AllowedClasses = "/Script/Engine.World"))
	FSoftObjectPath Map;

	/** Native class that implements the interfaces: ICsPooledObject, ICsUpdate, and ICsSoundPooled */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Managers|Sound", meta = (MustImplement = "/Script/CsSound.CsSoundPooled"))
	TSoftClassPtr<UObject> ClassA;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Managers|Sound", meta = (MustImplement = "/Script/CsSound.CsSoundPooled"))
	TSoftClassPtr<UObject> ClassB;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Managers|Sound", meta = (MustImplement = "/Script/CsSound.CsSoundPooled"))
	TSoftClassPtr<UObject> ClassC;

	FCsSettings_Manager_Sound_UnitTest() :
		Map(),
		ClassA(nullptr),
		ClassB(nullptr),
		ClassC(nullptr)
	{
	}
};

#pragma endregion FCsSettings_Manager_Sound_UnitTest