// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "GameFramework/Actor.h"
#include "Types/CsTypes.h"
#include "Types/CsTypes_Coroutine.h"
#include "CsJavascriptEntryPoint.generated.h"

// Enums
#pragma region

USTRUCT(BlueprintType)
struct CSCORE_API FECsJavascriptEntryPointRoutine : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

	CS_ENUM_UINT8_BODY(FECsJavascriptEntryPointRoutine)
};

CS_DEFINE_ENUM_UINT8_GET_TYPE_HASH(FECsJavascriptEntryPointRoutine)

struct CSCORE_API EMCsJavascriptEntryPointRoutine : public TCsEnumStructMap<FECsJavascriptEntryPointRoutine, uint8>
{
	CS_DECLARE_ENUM_STRUCT_MAP_BODY(EMCsJavascriptEntryPointRoutine)
};

namespace ECsJavascriptEntryPointRoutine
{
	extern CSCORE_API const FECsJavascriptEntryPointRoutine Setup_Internal;
}

#pragma endregion Enums

UCLASS()
class CSCORE_API ACsJavascriptEntryPoint : public AActor
{
	GENERATED_UCLASS_BODY()

public:

	UPROPERTY(Transient)
	UObject* Isolate;

	UPROPERTY(Transient)
	UObject* Context;

#if WITH_EDITOR

	void Setup();
	static char Setup_Internal(FCsRoutine* r);
	FCsRoutine* Setup_Internal_Routine;

	virtual bool HasCompletedAdditionalSetup();

	bool HasCompletedSetup;

#endif WITH_EDITOR

	FString EditorFile;

	UPROPERTY()
	bool IsRunningEditorFile;

	UPROPERTY()
	bool DoPerformCleanUpOnEditorFile;

	UFUNCTION(BlueprintCallable, Category = "World")
	float GetTimeSeconds();

// Routines
#pragma region
public:

	static void AddRoutine(UObject* InJavascriptEntryPoint, struct FCsRoutine* Routine, const uint8 &Type);
	void AddRoutine_Internal(struct FCsRoutine* Routine, const uint8 &Type);

	static void RemoveRoutine(UObject* InJavascriptEntryPoint, struct FCsRoutine* Routine, const uint8 &Type);
	void RemoveRoutine_Internal(struct FCsRoutine* Routine, const uint8 &Type);

#pragma endregion Routines

	void Run();
};