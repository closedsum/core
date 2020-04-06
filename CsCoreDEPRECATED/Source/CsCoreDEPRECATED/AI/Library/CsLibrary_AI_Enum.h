// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Kismet/BlueprintFunctionLibrary.h"

// AI
#include "AI/CsTypes_AI.h"

#include "CsLibrary_AI_Enum.generated.h"

UCLASS()
class CSCOREDEPRECATED_API UCsLibrary_AI_Enum : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()

public:

// AI
#pragma region
public:

	// Type
#pragma region
public:

	UFUNCTION(BlueprintCallable, Category = "Library Enum")
	static FECsAIType GetECsAIType(const FString& Name);

	UFUNCTION(BlueprintCallable, Category = "Library Enum")
	static FECsAIType GetECsAITypeByIndex(const int32& Index);

	UFUNCTION(BlueprintCallable, Category = "Library Enum")
	static FString ECsAITypeToString(const FECsAIType& Enum);

	UFUNCTION(BlueprintCallable, Category = "Library Enum")
	static uint8 GetECsAITypeCount();

	UFUNCTION(BlueprintCallable, Category = "Library Enum")
	static void GetAllECsAIType(TArray<FECsAIType>& OutTypes);

#pragma endregion Type

	// State
#pragma region
public:

	UFUNCTION(BlueprintCallable, Category = "Library Enum")
	static FECsAIState GetECsAIState(const FString& Name);

	UFUNCTION(BlueprintCallable, Category = "Library Enum")
	static FECsAIState GetECsAIStateByIndex(const int32& Index);

	UFUNCTION(BlueprintCallable, Category = "Library Enum")
	static FString ECsAIStateToString(const FECsAIState& Enum);

	UFUNCTION(BlueprintCallable, Category = "Library Enum")
	static uint8 GetECsAIStateCount();

	UFUNCTION(BlueprintCallable, Category = "Library Enum")
	static void GetAllECsAIState(TArray<FECsAIState>& OutTypes);

#pragma endregion State

	// Setup
#pragma region
public:

	UFUNCTION(BlueprintCallable, Category = "Library Enum")
	static FECsAISetup GetECsAISetup(const FString& Name);

	UFUNCTION(BlueprintCallable, Category = "Library Enum")
	static FECsAISetup GetECsAISetupByIndex(const int32& Index);

	UFUNCTION(BlueprintCallable, Category = "Library Enum")
	static FString ECsAISetupToString(const FECsAISetup& Enum);

	UFUNCTION(BlueprintCallable, Category = "Library Enum")
	static uint8 GetECsAISetupCount();

	UFUNCTION(BlueprintCallable, Category = "Library Enum")
	static void GetAllECsAISetup(TArray<FECsAISetup>& OutTypes);

#pragma endregion Setup

#pragma endregion AI
};