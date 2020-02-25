// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Library/CsBlockchainLibrary_Blueprint_Enum.h"
#include "CsBlockchain.h"

// Library
#include "Library/CsLibrary_Enum.h"

// Cache
#pragma region

namespace NCsBlockchainLibraryBlueprintEnumCached
{
	namespace Str
	{
		// Blockchain

			// Command
		const FString FECsBlockchainCommand = TEXT("FECsBlockchainCommand");
		const FString GetECsBlockchainCommand = TEXT("GetECsBlockchainCommand");
		const FString GetECsBlockchainCommandByIndex = TEXT("GetECsBlockchainCommandByIndex");
			// Contract
		const FString FECsBlockchainContract = TEXT("FECsBlockchainContract");
		const FString GetECsBlockchainContract = TEXT("GetECsBlockchainContract");
		const FString GetECsBlockchainContractByIndex = TEXT("GetECsBlockchainContractByIndex");
			// Contract Function
		const FString FECsBlockchainContractFunction = TEXT("FECsBlockchainContractFunction");
		const FString GetECsBlockchainContractFunction = TEXT("GetECsBlockchainContractFunction");
		const FString GetECsBlockchainContractFunctionByIndex = TEXT("GetECsBlockchainContractFunctionByIndex");
			// Ethereum

				// Javascript
		const FString FECsEthereumJavascript = TEXT("FECsEthereumJavascript");
		const FString GetECsEthereumJavascript = TEXT("GetECsEthereumJavascript");
		const FString GetECsEthereumJavascriptByIndex = TEXT("GetECsEthereumJavascriptByIndex");
	}
}

#pragma endregion Cache

UCsBlockchainLibrary_Blueprint_Enum::UCsBlockchainLibrary_Blueprint_Enum(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

// Blockchain
#pragma region

	// Command
#pragma region

FECsBlockchainCommand UCsBlockchainLibrary_Blueprint_Enum::GetECsBlockchainCommand(const FString& Name)
{
	return UCsLibrary_Enum::GetEnum<EMCsBlockchainCommand, FECsBlockchainCommand>(NCsBlockchainLibraryBlueprintEnumCached::Str::GetECsBlockchainCommand, NCsBlockchainLibraryBlueprintEnumCached::Str::FECsBlockchainCommand, Name);
}

FECsBlockchainCommand UCsBlockchainLibrary_Blueprint_Enum::GetECsBlockchainCommandByIndex(const int32& Index)
{
	return UCsLibrary_Enum::GetEnumByIndex<EMCsBlockchainCommand, FECsBlockchainCommand>(NCsBlockchainLibraryBlueprintEnumCached::Str::GetECsBlockchainCommandByIndex, NCsBlockchainLibraryBlueprintEnumCached::Str::FECsBlockchainCommand, Index);
}

FString UCsBlockchainLibrary_Blueprint_Enum::ECsBlockchainCommandToString(const FECsBlockchainCommand& Enum)
{
	return Enum.ToString();
}

uint8 UCsBlockchainLibrary_Blueprint_Enum::GetECsBlockchainCommandCount()
{
	return EMCsBlockchainCommand::Get().Num();
}

void UCsBlockchainLibrary_Blueprint_Enum::GetAllECsBlockchainCommand(TArray<FECsBlockchainCommand>& OutTypes)
{
	UCsLibrary_Enum::GetAllEnum<EMCsBlockchainCommand, FECsBlockchainCommand>(OutTypes);
}

#pragma endregion Command

	// Contract
#pragma region

FECsBlockchainContract UCsBlockchainLibrary_Blueprint_Enum::GetECsBlockchainContract(const FString& Name)
{
	return UCsLibrary_Enum::GetEnum<EMCsBlockchainContract, FECsBlockchainContract>(NCsBlockchainLibraryBlueprintEnumCached::Str::GetECsBlockchainContract, NCsBlockchainLibraryBlueprintEnumCached::Str::FECsBlockchainContract, Name);
}

FECsBlockchainContract UCsBlockchainLibrary_Blueprint_Enum::GetECsBlockchainContractByIndex(const int32& Index)
{
	return UCsLibrary_Enum::GetEnumByIndex<EMCsBlockchainContract, FECsBlockchainContract>(NCsBlockchainLibraryBlueprintEnumCached::Str::GetECsBlockchainContractByIndex, NCsBlockchainLibraryBlueprintEnumCached::Str::FECsBlockchainContract, Index);
}

FString UCsBlockchainLibrary_Blueprint_Enum::ECsBlockchainContractToString(const FECsBlockchainContract& Enum)
{
	return Enum.ToString();
}

uint8 UCsBlockchainLibrary_Blueprint_Enum::GetECsBlockchainContractCount()
{
	return EMCsBlockchainContract::Get().Num();
}

void UCsBlockchainLibrary_Blueprint_Enum::GetAllECsBlockchainContract(TArray<FECsBlockchainContract>& OutTypes)
{
	UCsLibrary_Enum::GetAllEnum<EMCsBlockchainContract, FECsBlockchainContract>(OutTypes);
}

#pragma endregion Contract

	// Contract Function
#pragma region

FECsBlockchainContractFunction UCsBlockchainLibrary_Blueprint_Enum::GetECsBlockchainContractFunction(const FString& Name)
{
	return UCsLibrary_Enum::GetEnum<EMCsBlockchainContractFunction, FECsBlockchainContractFunction>(NCsBlockchainLibraryBlueprintEnumCached::Str::GetECsBlockchainContractFunction, NCsBlockchainLibraryBlueprintEnumCached::Str::FECsBlockchainContractFunction, Name);
}

FECsBlockchainContractFunction UCsBlockchainLibrary_Blueprint_Enum::GetECsBlockchainContractFunctionByIndex(const int32& Index)
{
	return UCsLibrary_Enum::GetEnumByIndex<EMCsBlockchainContractFunction, FECsBlockchainContractFunction>(NCsBlockchainLibraryBlueprintEnumCached::Str::GetECsBlockchainContractFunctionByIndex, NCsBlockchainLibraryBlueprintEnumCached::Str::FECsBlockchainContractFunction, Index);
}

FString UCsBlockchainLibrary_Blueprint_Enum::ECsBlockchainContractFunctionToString(const FECsBlockchainContractFunction& Enum)
{
	return Enum.ToString();
}

uint8 UCsBlockchainLibrary_Blueprint_Enum::GetECsBlockchainContractFunctionCount()
{
	return EMCsBlockchainContractFunction::Get().Num();
}

void UCsBlockchainLibrary_Blueprint_Enum::GetAllECsBlockchainContractFunction(TArray<FECsBlockchainContractFunction>& OutTypes)
{
	UCsLibrary_Enum::GetAllEnum<EMCsBlockchainContractFunction, FECsBlockchainContractFunction>(OutTypes);
}

#pragma endregion Contract Function

	// Ethereum
#pragma region

		// Javascript
#pragma region

FECsEthereumJavascript UCsBlockchainLibrary_Blueprint_Enum::GetECsEthereumJavascript(const FString& Name)
{
	return UCsLibrary_Enum::GetEnum<EMCsEthereumJavascript, FECsEthereumJavascript>(NCsBlockchainLibraryBlueprintEnumCached::Str::GetECsEthereumJavascript, NCsBlockchainLibraryBlueprintEnumCached::Str::FECsEthereumJavascript, Name);
}

FECsEthereumJavascript UCsBlockchainLibrary_Blueprint_Enum::GetECsEthereumJavascriptByIndex(const int32& Index)
{
	return UCsLibrary_Enum::GetEnumByIndex<EMCsEthereumJavascript, FECsEthereumJavascript>(NCsBlockchainLibraryBlueprintEnumCached::Str::GetECsEthereumJavascriptByIndex, NCsBlockchainLibraryBlueprintEnumCached::Str::FECsEthereumJavascript, Index);
}

FString UCsBlockchainLibrary_Blueprint_Enum::ECsEthereumJavascriptToString(const FECsEthereumJavascript& Enum)
{
	return Enum.ToString();
}

uint8 UCsBlockchainLibrary_Blueprint_Enum::GetECsEthereumJavascriptCount()
{
	return EMCsEthereumJavascript::Get().Num();
}

void UCsBlockchainLibrary_Blueprint_Enum::GetAllECsEthereumJavascript(TArray<FECsEthereumJavascript>& OutTypes)
{
	UCsLibrary_Enum::GetAllEnum<EMCsEthereumJavascript, FECsEthereumJavascript>(OutTypes);
}

#pragma endregion Javascript

#pragma endregion Ethereum

#pragma endregion Blockchain