// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
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

public:
	FECsJavascriptEntryPointRoutine() {}
	FECsJavascriptEntryPointRoutine(const uint8 &InValue, const FString &InName, const FString &InDisplayName) : FECsEnum_uint8(InValue, InName, InDisplayName) {}
	FECsJavascriptEntryPointRoutine(const uint8 &InValue, const FString &InName) : FECsEnum_uint8(InValue, InName) {}
	~FECsJavascriptEntryPointRoutine() {}

	FORCEINLINE virtual FString ToString() const override { return FECsEnum_uint8::ToString(); }
};

FORCEINLINE uint32 GetTypeHash(const FECsJavascriptEntryPointRoutine& b)
{
	return GetTypeHash(b.Name) ^ GetTypeHash(b.Value);
}

struct CSCORE_API EMCsJavascriptEntryPointRoutine : public TCsEnumStructMap<FECsJavascriptEntryPointRoutine, uint8>
{
protected:
	EMCsJavascriptEntryPointRoutine() {}
	EMCsJavascriptEntryPointRoutine(const EMCsJavascriptEntryPointRoutine &) = delete;
	EMCsJavascriptEntryPointRoutine(EMCsJavascriptEntryPointRoutine &&) = delete;
public:
	~EMCsJavascriptEntryPointRoutine() {}
private:
	static EMCsJavascriptEntryPointRoutine* Instance;

public:
	static EMCsJavascriptEntryPointRoutine& Get();
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