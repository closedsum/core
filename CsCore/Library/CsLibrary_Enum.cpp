// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Library/CsLibrary_Enum.h"
#include "CsCore.h"

// Cache
#pragma region

namespace ECsLibraryEnumCached
{
	namespace Str
	{
		// Process
		const FString FECsProcess = TEXT("FECsProcess");
		const FString GetECsProcess = TEXT("GetECsProcess");
		const FString GetECsProcessByIndex = TEXT("GetECsProcessByIndex");
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
		// AI

			// Type
		const FString FECsAIType = TEXT("FECsAIType");
		const FString GetECsAIType = TEXT("GetECsAIType");
		const FString GetECsAITypeByIndex = TEXT("GetECsAITypeByIndex");
			// State
		const FString FECsAIState = TEXT("FECsAIState");
		const FString GetECsAIState = TEXT("GetECsAIState");
		const FString GetECsAIStateByIndex = TEXT("GetECsAIStateByIndex");
			// Setup
		const FString FECsAISetup = TEXT("FECsAISetup");
		const FString GetECsAISetup = TEXT("GetECsAISetup");
		const FString GetECsAISetupByIndex = TEXT("GetECsAISetupByIndex");
	}
}

#pragma endregion Cache

UCsLibrary_Enum::UCsLibrary_Enum(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

// Process
#pragma region

FECsProcess UCsLibrary_Enum::GetECsProcess(const FString& Name)
{
	return GetEnum<EMCsProcess, FECsProcess>(ECsLibraryEnumCached::Str::GetECsProcess, ECsLibraryEnumCached::Str::FECsProcess, Name);
}

FECsProcess UCsLibrary_Enum::GetECsProcessByIndex(const int32& Index)
{
	return GetEnumByIndex<EMCsProcess, FECsProcess>(ECsLibraryEnumCached::Str::GetECsProcessByIndex, ECsLibraryEnumCached::Str::FECsProcess, Index);
}

FString UCsLibrary_Enum::ECsProcessToString(const FECsProcess& Enum)
{
	return Enum.ToString();
}

uint8 UCsLibrary_Enum::GetECsProcessCount()
{
	return EMCsProcess::Get().Num();
}

void UCsLibrary_Enum::GetAllECsProcess(TArray<FECsProcess> &OutTypes)
{
	GetAllEnum<EMCsProcess, FECsProcess>(OutTypes);
}

#pragma endregion Process

// Blockchain
#pragma region

	// Command
#pragma region

FECsBlockchainCommand UCsLibrary_Enum::GetECsBlockchainCommand(const FString& Name)
{
	return GetEnum<EMCsBlockchainCommand, FECsBlockchainCommand>(ECsLibraryEnumCached::Str::GetECsBlockchainCommand, ECsLibraryEnumCached::Str::FECsBlockchainCommand, Name);
}

FECsBlockchainCommand UCsLibrary_Enum::GetECsBlockchainCommandByIndex(const int32& Index)
{
	return GetEnumByIndex<EMCsBlockchainCommand, FECsBlockchainCommand>(ECsLibraryEnumCached::Str::GetECsBlockchainCommandByIndex, ECsLibraryEnumCached::Str::FECsBlockchainCommand, Index);
}

FString UCsLibrary_Enum::ECsBlockchainCommandToString(const FECsBlockchainCommand& Enum)
{
	return Enum.ToString();
}

uint8 UCsLibrary_Enum::GetECsBlockchainCommandCount()
{
	return EMCsBlockchainCommand::Get().Num();
}

void UCsLibrary_Enum::GetAllECsBlockchainCommand(TArray<FECsBlockchainCommand> &OutTypes)
{
	GetAllEnum<EMCsBlockchainCommand, FECsBlockchainCommand>(OutTypes);
}

#pragma endregion Command

	// Contract
#pragma region

FECsBlockchainContract UCsLibrary_Enum::GetECsBlockchainContract(const FString& Name)
{
	return GetEnum<EMCsBlockchainContract, FECsBlockchainContract>(ECsLibraryEnumCached::Str::GetECsBlockchainContract, ECsLibraryEnumCached::Str::FECsBlockchainContract, Name);
}

FECsBlockchainContract UCsLibrary_Enum::GetECsBlockchainContractByIndex(const int32& Index)
{
	return GetEnumByIndex<EMCsBlockchainContract, FECsBlockchainContract>(ECsLibraryEnumCached::Str::GetECsBlockchainContractByIndex, ECsLibraryEnumCached::Str::FECsBlockchainContract, Index);
}

FString UCsLibrary_Enum::ECsBlockchainContractToString(const FECsBlockchainContract& Enum)
{
	return Enum.ToString();
}

uint8 UCsLibrary_Enum::GetECsBlockchainContractCount()
{
	return EMCsBlockchainContract::Get().Num();
}

void UCsLibrary_Enum::GetAllECsBlockchainContract(TArray<FECsBlockchainContract> &OutTypes)
{
	GetAllEnum<EMCsBlockchainContract, FECsBlockchainContract>(OutTypes);
}

#pragma endregion Contract

	// Contract Function
#pragma region

FECsBlockchainContractFunction UCsLibrary_Enum::GetECsBlockchainContractFunction(const FString& Name)
{
	return GetEnum<EMCsBlockchainContractFunction, FECsBlockchainContractFunction>(ECsLibraryEnumCached::Str::GetECsBlockchainContractFunction, ECsLibraryEnumCached::Str::FECsBlockchainContractFunction, Name);
}

FECsBlockchainContractFunction UCsLibrary_Enum::GetECsBlockchainContractFunctionByIndex(const int32& Index)
{
	return GetEnumByIndex<EMCsBlockchainContractFunction, FECsBlockchainContractFunction>(ECsLibraryEnumCached::Str::GetECsBlockchainContractFunctionByIndex, ECsLibraryEnumCached::Str::FECsBlockchainContractFunction, Index);
}

FString UCsLibrary_Enum::ECsBlockchainContractFunctionToString(const FECsBlockchainContractFunction& Enum)
{
	return Enum.ToString();
}

uint8 UCsLibrary_Enum::GetECsBlockchainContractFunctionCount()
{
	return EMCsBlockchainContractFunction::Get().Num();
}

void UCsLibrary_Enum::GetAllECsBlockchainContractFunction(TArray<FECsBlockchainContractFunction> &OutTypes)
{
	GetAllEnum<EMCsBlockchainContractFunction, FECsBlockchainContractFunction>(OutTypes);
}

#pragma endregion Contract Function

	// Ethereum
#pragma region

		// Javascript
#pragma region

FECsEthereumJavascript UCsLibrary_Enum::GetECsEthereumJavascript(const FString& Name)
{
	return GetEnum<EMCsEthereumJavascript, FECsEthereumJavascript>(ECsLibraryEnumCached::Str::GetECsEthereumJavascript, ECsLibraryEnumCached::Str::FECsEthereumJavascript, Name);
}

FECsEthereumJavascript UCsLibrary_Enum::GetECsEthereumJavascriptByIndex(const int32& Index)
{
	return GetEnumByIndex<EMCsEthereumJavascript, FECsEthereumJavascript>(ECsLibraryEnumCached::Str::GetECsEthereumJavascriptByIndex, ECsLibraryEnumCached::Str::FECsEthereumJavascript, Index);
}

FString UCsLibrary_Enum::ECsEthereumJavascriptToString(const FECsEthereumJavascript& Enum)
{
	return Enum.ToString();
}

uint8 UCsLibrary_Enum::GetECsEthereumJavascriptCount()
{
	return EMCsEthereumJavascript::Get().Num();
}

void UCsLibrary_Enum::GetAllECsEthereumJavascript(TArray<FECsEthereumJavascript> &OutTypes)
{
	GetAllEnum<EMCsEthereumJavascript, FECsEthereumJavascript>(OutTypes);
}

#pragma endregion Javascript

#pragma endregion Ethereum

#pragma endregion Blockchain

// AI
#pragma region

	// Type
#pragma region

FECsAIType UCsLibrary_Enum::GetECsAIType(const FString& Name)
{
	return GetEnum<EMCsAIType, FECsAIType>(ECsLibraryEnumCached::Str::GetECsAIType, ECsLibraryEnumCached::Str::FECsAIType, Name);
}

FECsAIType UCsLibrary_Enum::GetECsAITypeByIndex(const int32& Index)
{
	return GetEnumByIndex<EMCsAIType, FECsAIType>(ECsLibraryEnumCached::Str::GetECsAITypeByIndex, ECsLibraryEnumCached::Str::FECsAIType, Index);
}

FString UCsLibrary_Enum::ECsAITypeToString(const FECsAIType& Enum)
{
	return Enum.ToString();
}

uint8 UCsLibrary_Enum::GetECsAITypeCount()
{
	return EMCsAIType::Get().Num();
}

void UCsLibrary_Enum::GetAllECsAIType(TArray<FECsAIType> &OutTypes)
{
	GetAllEnum<EMCsAIType, FECsAIType>(OutTypes);
}

#pragma endregion Type

	// State
#pragma region

FECsAIState UCsLibrary_Enum::GetECsAIState(const FString& Name)
{
	return GetEnum<EMCsAIState, FECsAIState>(ECsLibraryEnumCached::Str::GetECsAIState, ECsLibraryEnumCached::Str::FECsAIState, Name);
}

FECsAIState UCsLibrary_Enum::GetECsAIStateByIndex(const int32& Index)
{
	return GetEnumByIndex<EMCsAIState, FECsAIState>(ECsLibraryEnumCached::Str::GetECsAIStateByIndex, ECsLibraryEnumCached::Str::FECsAIState, Index);
}

FString UCsLibrary_Enum::ECsAIStateToString(const FECsAIState& Enum)
{
	return Enum.ToString();
}

uint8 UCsLibrary_Enum::GetECsAIStateCount()
{
	return EMCsAIState::Get().Num();
}

void UCsLibrary_Enum::GetAllECsAIState(TArray<FECsAIState> &OutTypes)
{
	GetAllEnum<EMCsAIState, FECsAIState>(OutTypes);
}

#pragma endregion State

	// Setup
#pragma region

FECsAISetup UCsLibrary_Enum::GetECsAISetup(const FString& Name)
{
	return GetEnum<EMCsAISetup, FECsAISetup>(ECsLibraryEnumCached::Str::GetECsAISetup, ECsLibraryEnumCached::Str::FECsAISetup, Name);
}

FECsAISetup UCsLibrary_Enum::GetECsAISetupByIndex(const int32& Index)
{
	return GetEnumByIndex<EMCsAISetup, FECsAISetup>(ECsLibraryEnumCached::Str::GetECsAISetupByIndex, ECsLibraryEnumCached::Str::FECsAISetup, Index);
}

FString UCsLibrary_Enum::ECsAISetupToString(const FECsAISetup& Enum)
{
	return Enum.ToString();
}

uint8 UCsLibrary_Enum::GetECsAISetupCount()
{
	return EMCsAISetup::Get().Num();
}

void UCsLibrary_Enum::GetAllECsAISetup(TArray<FECsAISetup> &OutTypes)
{
	GetAllEnum<EMCsAISetup, FECsAISetup>(OutTypes);
}

#pragma endregion Setup

#pragma endregion AI