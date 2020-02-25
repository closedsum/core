// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Kismet/BlueprintFunctionLibrary.h"

// Managers
#include "Managers/Process/CsProcess.h"
// AI
#include "Types/CsTypes_AI.h"

#include "CsLibrary_Enum.generated.h"

UCLASS()
class CSCORE_API UCsLibrary_Enum : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()

public:

	template<typename EnumStructMap, typename EnumStruct>
	static EnumStruct GetEnum(const FString& FunctionName, const FString& EnumStructName, const FString& Name)
	{
		if (EnumStructMap::Get().IsValidEnum(Name))
			return EnumStructMap::Get()[Name];

		//UE_LOG(Log, Warning, TEXT("UCsLibrary_Enum::%s: Enum of type %s and Name: %s does NOT exist."), *FunctionName, *EnumStructName, *Name);
		return EnumStruct(0, NCsCached::Str::INVALID);
	}

	template<typename EnumStructMap, typename EnumStruct>
	static EnumStruct GetEnumByIndex(const FString& FunctionName, const FString& EnumStructName, const int32& Index)
	{
		const int32& Count = EnumStructMap::Get().Num();

		if (Index < Count)
			return EnumStructMap::Get().GetEnumAt(Index);

		//UE_LOG(Log, Warning, TEXT("UCsLibrary_Enum::%s: Enum of type %s and Index: %d (%d >= %d) does NOT exist."), *FunctionName, *EnumStructName, Index, Index, Count);
		return EnumStruct(0, NCsCached::Str::INVALID);
	}

	template<typename EnumStructMap, typename EnumStruct>
	static void GetAllEnum(TArray<EnumStruct> &OutTypes)
	{
		const int32& Count = EnumStructMap::Get().Num();

		for (int32 I = 0; I < Count; ++I)
		{
			OutTypes.Add(EnumStructMap::Get().GetEnumAt(I));
		}
	}

// Asset
#pragma region

#pragma endregion Asset

// Input
#pragma region

#pragma endregion Input

// SurfaceType
#pragma region

#pragma endregion SurfaceType

// GestureType
#pragma region

#pragma endregion SurfaceType

// Character
#pragma region

#pragma endregion Character

// Weapon
#pragma region

#pragma endregion Weapon


// Process
#pragma region
public:

	UFUNCTION(BlueprintCallable, Category = "Library Enum", meta = (DisplayName="ECsProcess - Get", AutoCreateRefTerm="Name"))
	static FECsProcess ECsProcess_Get(const FString& Name);

	UFUNCTION(BlueprintCallable, Category = "Library Enum", meta = (DisplayName = "ECsProcess - Get by Index", AutoCreateRefTerm = "Index"))
	static FECsProcess ECsProcess_GetByIndex(const int32& Index);

	UFUNCTION(BlueprintCallable, Category = "Library Enum", meta = (DisplayName = "ECsProcess - To String", AutoCreateRefTerm = "Enum"))
	static FString ECsProcess_ToString(const FECsProcess& Enum);

	UFUNCTION(BlueprintCallable, Category = "Library Enum", meta = (DisplayName = "ECsProcess - Get Count"))
	static uint8 ECsProcess_GetCount();

	UFUNCTION(BlueprintCallable, Category = "Library Enum", meta = (DisplayName = "ECsProcess - Get All"))
	static void ECsProcess_GetAll(TArray<FECsProcess>& OutTypes);

#pragma endregion Process

// Item
#pragma region

#pragma endregion Item

// Crafting
#pragma region

#pragma endregion Crafting

// Damage
#pragma region

#pragma endregion Damage

// Interactive
#pragma region

#pragma endregion Interactive

// Sound
#pragma region

#pragma endregion Sound

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