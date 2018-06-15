// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Kismet/BlueprintFunctionLibrary.h"

// Managers
#include "Managers/Process/CsProcess.h"
// Blockchain
#include "Blockchain/CsBlockchainCommand.h"
#include "Blockchain/CsBlockchainContract.h"
#include "Blockchain/Ethereum/CsEthereum.h"

#include "CsLibrary_Enum.generated.h"

UCLASS()
class CSCORE_API UCsLibrary_Enum : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()

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
};