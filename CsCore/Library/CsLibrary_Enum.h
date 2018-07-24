// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
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
	EnumStruct GetEnum(const FString& FunctionName, const FString& EnumStructName, const FString& Name)
	{
		if (EnumStructMap::Get().IsValidEnum(Name))
			return EnumStructMap::Get()[Name];

		UE_LOG(LogCs, Warning, TEXT("UCsLibrary_Enum::%s: Enum of type %s and Name: %s does NOT exist."), *FunctionName, *EnumStructName, *Name);
		return EnumStruct(0, ECsCached::Str::INVALID);
	}

	template<typename EnumStructMap, typename EnumStruct>
	EnumStruct GetEnumByIndex(const FString& FunctionName, const FString& EnumStructName, const int32& Index)
	{
		const int32& Count = EnumStructMap::Get().Num();

		if (Index < Count)
			return EnumStructMap::Get().GetEnumAt(Index);

		UE_LOG(LogCs, Warning, TEXT("UCsLibrary_Enum::%s: Enum of type %s and Index: %d (%d >= %d) does NOT exist."), *FunctionName, *EnumStructName, Index, Index, Count);
		return EnumStruct(0, ECsCached::Str::INVALID);
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

	UFUNCTION(BlueprintCallable, Category = "Library Enum")
	FECsProcess GetECsProcess(const FString& Name);

	UFUNCTION(BlueprintCallable, Category = "Library Enum")
	FECsProcess GetECsProcessByIndex(const int32& Index);

	UFUNCTION(BlueprintCallable, Category = "Library Enum")
	FString ECsProcessToString(const FECsProcess& Enum);

#pragma endregion Process

// Blockchain
#pragma region

	UFUNCTION(BlueprintCallable, Category = "Library Enum")
	FECsBlockchainCommand GetECsBlockchainCommand(const FString& Name);

	UFUNCTION(BlueprintCallable, Category = "Library Enum")
	FECsBlockchainCommand GetECsBlockchainCommandByIndex(const int32& Index);

	UFUNCTION(BlueprintCallable, Category = "Library Enum")
	FString ECsBlockchainCommandToString(const FECsBlockchainCommand& Enum);

	UFUNCTION(BlueprintCallable, Category = "Library Enum")
	FECsBlockchainContract GetECsBlockchainContract(const FString& Name);

	UFUNCTION(BlueprintCallable, Category = "Library Enum")
	FECsBlockchainContract GetECsBlockchainContractByIndex(const int32& Index);

	UFUNCTION(BlueprintCallable, Category = "Library Enum")
	FString ECsBlockchainContractToString(const FECsBlockchainContract& Enum);

	UFUNCTION(BlueprintCallable, Category = "Library Enum")
	FECsBlockchainContractFunction GetECsBlockchainContractFunction(const FString& Name);

	UFUNCTION(BlueprintCallable, Category = "Library Enum")
	FECsBlockchainContractFunction GetECsBlockchainContractFunctionByIndex(const int32& Index);

	UFUNCTION(BlueprintCallable, Category = "Library Enum")
	FString ECsBlockchainContractFunctionToString(const FECsBlockchainContractFunction& Enum);

	UFUNCTION(BlueprintCallable, Category = "Library Enum")
	FECsEthereumJavascript GetECsEthereumJavascript(const FString& Name);

	UFUNCTION(BlueprintCallable, Category = "Library Enum")
	FECsEthereumJavascript GetECsEthereumJavascriptByIndex(const int32& Index);

	UFUNCTION(BlueprintCallable, Category = "Library Enum")
	FString ECsEthereumJavascriptToString(const FECsEthereumJavascript& Enum);

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
	FECsAIType GetECsAIType(const FString& Name);

	UFUNCTION(BlueprintCallable, Category = "Library Enum")
	FECsAIType GetECsAITypeByIndex(const int32& Index);

	UFUNCTION(BlueprintCallable, Category = "Library Enum")
	FString ECsAITypeToString(const FECsAIType& Enum);

#pragma endregion Type

	// State
#pragma region
public:

	UFUNCTION(BlueprintCallable, Category = "Library Enum")
	FECsAIState GetECsAIState(const FString& Name);

	UFUNCTION(BlueprintCallable, Category = "Library Enum")
	FECsAIState GetECsAIStateByIndex(const int32& Index);

	UFUNCTION(BlueprintCallable, Category = "Library Enum")
	FString ECsAIStateToString(const FECsAIState& Enum);

#pragma endregion State

	// Setup
#pragma region
public:



#pragma endregion Setup

#pragma endregion AI
};