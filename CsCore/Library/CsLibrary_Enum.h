// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Kismet/BlueprintFunctionLibrary.h"

// Managers
#include "Managers/Process/CsProcess.h"
// Blockchain
#include "Blockchain/CsBlockchainCommand.h"
#include "Blockchain/CsBlockchainContract.h"
#include "Blockchain/Ethereum/CsEthereum.h"
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

		UE_LOG(LogCs, Warning, TEXT("UCsLibrary_Enum::%s: Enum of type %s and Name: %s does NOT exist."), *FunctionName, *EnumStructName, *Name);
		return EnumStruct(0, ECsCached::Str::INVALID);
	}

	template<typename EnumStructMap, typename EnumStruct>
	static EnumStruct GetEnumByIndex(const FString& FunctionName, const FString& EnumStructName, const int32& Index)
	{
		const int32& Count = EnumStructMap::Get().Num();

		if (Index < Count)
			return EnumStructMap::Get().GetEnumAt(Index);

		UE_LOG(LogCs, Warning, TEXT("UCsLibrary_Enum::%s: Enum of type %s and Index: %d (%d >= %d) does NOT exist."), *FunctionName, *EnumStructName, Index, Index, Count);
		return EnumStruct(0, ECsCached::Str::INVALID);
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

	UFUNCTION(BlueprintCallable, Category = "Library Enum")
	static FECsProcess GetECsProcess(const FString& Name);

	UFUNCTION(BlueprintCallable, Category = "Library Enum")
	static FECsProcess GetECsProcessByIndex(const int32& Index);

	UFUNCTION(BlueprintCallable, Category = "Library Enum")
	static FString ECsProcessToString(const FECsProcess& Enum);

	UFUNCTION(BlueprintCallable, Category = "Library Enum")
	static uint8 GetECsProcessCount();

	UFUNCTION(BlueprintCallable, Category = "Library Enum")
	static void GetAllECsProcess(TArray<FECsProcess>& OutTypes);

#pragma endregion Process

// Blockchain
#pragma region
public:

	// Command
#pragma region
public:

	UFUNCTION(BlueprintCallable, Category = "Library Enum")
	static FECsBlockchainCommand GetECsBlockchainCommand(const FString& Name);

	UFUNCTION(BlueprintCallable, Category = "Library Enum")
	static FECsBlockchainCommand GetECsBlockchainCommandByIndex(const int32& Index);

	UFUNCTION(BlueprintCallable, Category = "Library Enum")
	static FString ECsBlockchainCommandToString(const FECsBlockchainCommand& Enum);

	UFUNCTION(BlueprintCallable, Category = "Library Enum")
	static uint8 GetECsBlockchainCommandCount();

	UFUNCTION(BlueprintCallable, Category = "Library Enum")
	static void GetAllECsBlockchainCommand(TArray<FECsBlockchainCommand>& OutTypes);

#pragma endregion Command

	// Contract
#pragma region
public:

	UFUNCTION(BlueprintCallable, Category = "Library Enum")
	static FECsBlockchainContract GetECsBlockchainContract(const FString& Name);

	UFUNCTION(BlueprintCallable, Category = "Library Enum")
	static FECsBlockchainContract GetECsBlockchainContractByIndex(const int32& Index);

	UFUNCTION(BlueprintCallable, Category = "Library Enum")
	static FString ECsBlockchainContractToString(const FECsBlockchainContract& Enum);

	UFUNCTION(BlueprintCallable, Category = "Library Enum")
	static uint8 GetECsBlockchainContractCount();

	UFUNCTION(BlueprintCallable, Category = "Library Enum")
	static void GetAllECsBlockchainContract(TArray<FECsBlockchainContract>& OutTypes);

#pragma endregion Contract

	// Contract Function
#pragma region
public:

	UFUNCTION(BlueprintCallable, Category = "Library Enum")
	static FECsBlockchainContractFunction GetECsBlockchainContractFunction(const FString& Name);

	UFUNCTION(BlueprintCallable, Category = "Library Enum")
	static FECsBlockchainContractFunction GetECsBlockchainContractFunctionByIndex(const int32& Index);

	UFUNCTION(BlueprintCallable, Category = "Library Enum")
	static FString ECsBlockchainContractFunctionToString(const FECsBlockchainContractFunction& Enum);

	UFUNCTION(BlueprintCallable, Category = "Library Enum")
	static uint8 GetECsBlockchainContractFunctionCount();

	UFUNCTION(BlueprintCallable, Category = "Library Enum")
	static void GetAllECsBlockchainContractFunction(TArray<FECsBlockchainContractFunction>& OutTypes);

#pragma endregion Contract Function

	// Ethereum
#pragma region
public:

		// Javascript
#pragma region
public:

	UFUNCTION(BlueprintCallable, Category = "Library Enum")
	static FECsEthereumJavascript GetECsEthereumJavascript(const FString& Name);

	UFUNCTION(BlueprintCallable, Category = "Library Enum")
	static FECsEthereumJavascript GetECsEthereumJavascriptByIndex(const int32& Index);

	UFUNCTION(BlueprintCallable, Category = "Library Enum")
	static FString ECsEthereumJavascriptToString(const FECsEthereumJavascript& Enum);

	UFUNCTION(BlueprintCallable, Category = "Library Enum")
	static uint8 GetECsEthereumJavascriptCount();

	UFUNCTION(BlueprintCallable, Category = "Library Enum")
	static void GetAllECsEthereumJavascript(TArray<FECsEthereumJavascript>& OutTypes);

#pragma endregion Javascript

#pragma endregion Ethereum

#pragma endregion Blockchain

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