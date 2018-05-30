// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "Library/CsLibrary_Enum.h"
#include "CsCore.h"

UCsLibrary_Enum::UCsLibrary_Enum(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

FECsProcess UCsLibrary_Enum::GetECsProcess(const FString& Name)
{
	if (EMCsProcess::Get().IsValidEnum(Name))
		return EMCsProcess::Get()[Name];

	UE_LOG(LogCs, Warning, TEXT("UCsLibrary_Enum::GetECsProcess: Enum of type FECsProcess and Name: %s does NOT exist."), *Name);
	return FECsProcess(0, ECsCached::Str::INVALID);
}

FECsProcess UCsLibrary_Enum::GetECsProcessByIndex(const int32& Index)
{
	const int32& Count = EMCsProcess::Get().Num();

	if (Index < Count)
		return EMCsProcess::Get().GetEnumAt(Index);

	UE_LOG(LogCs, Warning, TEXT("UCsLibrary_Enum::GetECsProcessByIndex: Enum of type FECsProcess and Index: %d (%d >= %d) does NOT exist."), Index, Index, Count);
	return FECsProcess(0, ECsCached::Str::INVALID);
}

FString UCsLibrary_Enum::ECsProcessToString(const FECsProcess& Enum)
{
	return Enum.ToString();
}

// Blockchain
#pragma region

FECsBlockchainCommand UCsLibrary_Enum::GetECsBlockchainCommand(const FString& Name)
{
	if (EMCsBlockchainCommand::Get().IsValidEnum(Name))
		return EMCsBlockchainCommand::Get()[Name];

	UE_LOG(LogCs, Warning, TEXT("UCsLibrary_Enum::GetECsBlockchainCommand: Enum of type FECsBlockchainCommand and Name: %s does NOT exist."), *Name);
	return FECsBlockchainCommand(0, ECsCached::Str::INVALID);
}

FECsBlockchainCommand UCsLibrary_Enum::GetECsBlockchainCommandByIndex(const int32& Index)
{
	const int32& Count = EMCsBlockchainCommand::Get().Num();

	if (Index < Count)
		return EMCsBlockchainCommand::Get().GetEnumAt(Index);

	UE_LOG(LogCs, Warning, TEXT("UCsLibrary_Enum::GetECsBlockchainCommandByIndex: Enum of type FECsBlockchainCommand and Index: %d (%d >= %d) does NOT exist."), Index, Index, Count);
	return FECsBlockchainCommand(0, ECsCached::Str::INVALID);
}

FString UCsLibrary_Enum::ECsBlockchainCommandToString(const FECsBlockchainCommand& Enum)
{
	return Enum.ToString();
}

FECsBlockchainContract UCsLibrary_Enum::GetECsBlockchainContract(const FString& Name)
{
	if (EMCsBlockchainContract::Get().IsValidEnum(Name))
		return EMCsBlockchainContract::Get()[Name];

	UE_LOG(LogCs, Warning, TEXT("UCsLibrary_Enum::GetECsBlockchainContract: Enum of type FECsBlockchainContract and Name: %s does NOT exist."), *Name);
	return FECsBlockchainContract(0, ECsCached::Str::INVALID);
}

FECsBlockchainContract UCsLibrary_Enum::GetECsBlockchainContractByIndex(const int32& Index)
{
	const int32& Count = EMCsBlockchainContract::Get().Num();

	if (Index < Count)
		return EMCsBlockchainContract::Get().GetEnumAt(Index);

	UE_LOG(LogCs, Warning, TEXT("UCsLibrary_Enum::GetECsBlockchainContractByIndex: Enum of type FECsBlockchainContract and Index: %d (%d >= %d) does NOT exist."), Index, Index, Count);
	return FECsBlockchainContract(0, ECsCached::Str::INVALID);
}

FString UCsLibrary_Enum::ECsBlockchainContractToString(const FECsBlockchainContract& Enum)
{
	return Enum.ToString();
}

FECsBlockchainContractFunction UCsLibrary_Enum::GetECsBlockchainContractFunction(const FString& Name)
{
	if (EMCsBlockchainContractFunction::Get().IsValidEnum(Name))
		return EMCsBlockchainContractFunction::Get()[Name];

	UE_LOG(LogCs, Warning, TEXT("UCsLibrary_Enum::GetECsBlockchainContractFunction: Enum of type FECsBlockchainContractFunction and Name: %s does NOT exist."), *Name);
	return FECsBlockchainContractFunction(0, ECsCached::Str::INVALID);
}

FECsBlockchainContractFunction UCsLibrary_Enum::GetECsBlockchainContractFunctionByIndex(const int32& Index)
{
	const int32& Count = EMCsBlockchainContractFunction::Get().Num();

	if (Index < Count)
		return EMCsBlockchainContractFunction::Get().GetEnumAt(Index);

	UE_LOG(LogCs, Warning, TEXT("UCsLibrary_Enum::GetECsBlockchainContractFunctionByIndex: Enum of type EMCsBlockchainContractFunction and Index: %d (%d >= %d) does NOT exist."), Index, Index, Count);
	return FECsBlockchainContractFunction(0, ECsCached::Str::INVALID);
}

FString UCsLibrary_Enum::ECsBlockchainContractFunctionToString(const FECsBlockchainContractFunction& Enum)
{
	return Enum.ToString();
}

FECsEthereumJavascript UCsLibrary_Enum::GetECsEthereumJavascript(const FString& Name)
{
	if (EMCsEthereumJavascript::Get().IsValidEnum(Name))
		return EMCsEthereumJavascript::Get()[Name];

	UE_LOG(LogCs, Warning, TEXT("UCsLibrary_Enum::GetECsEthereumJavascript: Enum of type FECsEthereumJavascript and Name: %s does NOT exist."), *Name);
	return FECsEthereumJavascript(0, ECsCached::Str::INVALID);
}

FECsEthereumJavascript UCsLibrary_Enum::GetECsEthereumJavascriptByIndex(const int32& Index)
{
	const int32& Count = EMCsEthereumJavascript::Get().Num();

	if (Index < Count)
		return EMCsEthereumJavascript::Get().GetEnumAt(Index);

	UE_LOG(LogCs, Warning, TEXT("UCsLibrary_Enum::GetECsEthereumJavascriptByIndex: Enum of type FECsEthereumJavascript and Index: %d (%d >= %d) does NOT exist."), Index, Index, Count);
	return FECsEthereumJavascript(0, ECsCached::Str::INVALID);
}

FString UCsLibrary_Enum::ECsEthereumJavascriptToString(const FECsEthereumJavascript& Enum)
{
	return Enum.ToString();
}

#pragma endregion Blockchain