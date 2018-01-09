// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "GameFramework/Actor.h"
#include "Types/CsTypes.h"
#include "Types/CsTypes_Coroutine.h"
#include "CsJavascriptEntryPoint.generated.h"

// Enums
#pragma region

UENUM(BlueprintType)
namespace ECsRoutineJavascriptEntryPoint
{
	enum Type
	{
		Setup_Internal						UMETA(DisplayName = "Setup_Internal"),
		ECsRoutineJavascriptEntryPoint_MAX	UMETA(Hidden),
	};
}

namespace ECsRoutineJavascriptEntryPoint
{
	typedef TCsPrimitiveType_MultiValue_FString_Enum_ThreeParams TCsString;

	namespace Str
	{
		const TCsString Setup_Internal = TCsString(TEXT("Setup_Internal"), TEXT("setup_internal"), TEXT("setup internal"));
	}

	FORCEINLINE FString ToString(const Type &EType)
	{
		if (EType == Type::Setup_Internal) { return Str::Setup_Internal.Value; }
		return CS_INVALID_ENUM_TO_STRING;
	}

	FORCEINLINE Type ToType(const FString &String)
	{
		if (String == Str::Setup_Internal) { return Type::Setup_Internal; }
		return Type::ECsRoutineJavascriptEntryPoint_MAX;
	}
}

#define EMBO_ROUTINE_JAVASCRIPT_ENTRY_POINT_MAX (uint8)ECsRoutineJavascriptEntryPoint::ECsRoutineJavascriptEntryPoint_MAX
typedef TEnumAsByte<ECsRoutineJavascriptEntryPoint::Type> TCsRoutineJavascriptEntryPoint;

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
	void AddRoutine_Internal(struct FCsRoutine* Routine, const TCsRoutineJavascriptEntryPoint &Type);

	static void RemoveRoutine(UObject* InJavascriptEntryPoint, struct FCsRoutine* Routine, const uint8 &Type);
	void RemoveRoutine_Internal(struct FCsRoutine* Routine, const TCsRoutineJavascriptEntryPoint &Type);

#pragma endregion Routines

	void Run();
};