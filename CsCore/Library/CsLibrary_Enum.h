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

	UFUNCTION(BlueprintCallable, Category = "Library Enum")
	FECsProcess GetECsProcess(const FString& Name);

	UFUNCTION(BlueprintCallable, Category = "Library Enum")
	FECsProcess GetECsProcessByIndex(const int32& Index);

// Blockchain
#pragma region

	UFUNCTION(BlueprintCallable, Category = "Library Enum")
	FECsBlockchainCommand GetECsBlockchainCommand(const FString& Name);

	UFUNCTION(BlueprintCallable, Category = "Library Enum")
	FECsBlockchainCommand GetECsBlockchainCommandByIndex(const int32& Index);

	UFUNCTION(BlueprintCallable, Category = "Library Enum")
	FECsBlockchainContract GetECsBlockchainContract(const FString& Name);

	UFUNCTION(BlueprintCallable, Category = "Library Enum")
	FECsBlockchainContract GetECsBlockchainContractByIndex(const int32& Index);

	UFUNCTION(BlueprintCallable, Category = "Library Enum")
	FECsBlockchainContractFunction GetECsBlockchainContractFunction(const FString& Name);

	UFUNCTION(BlueprintCallable, Category = "Library Enum")
	FECsBlockchainContractFunction GetECsBlockchainContractFunctionByIndex(const int32& Index);

	UFUNCTION(BlueprintCallable, Category = "Library Enum")
	FECsEthereumJavascript GetECsEthereumJavascript(const FString& Name);

	UFUNCTION(BlueprintCallable, Category = "Library Enum")
	FECsEthereumJavascript GetECsEthereumJavascriptByIndex(const int32& Index);

#pragma endregion Blockchain
};