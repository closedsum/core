// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Kismet/BlueprintFunctionLibrary.h"

// Blockchain
#include "Blockchain/CsBlockchainCommand.h"
#include "Blockchain/CsBlockchainContract.h"
#include "Blockchain/Ethereum/CsEthereum.h"

#include "CsBlockchainLibrary_Blueprint_Enum.generated.h"

UCLASS()
class CSBLOCKCHAIN_API UCsBlockchainLibrary_Blueprint_Enum : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()

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
};