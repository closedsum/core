// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "Blockchain/Ethereum/CsEthereumAccount.h"

CsEthereumAccount::CsEthereumAccount() : ICsBlockchainAccount()
{
}

CsEthereumAccount::CsEthereumAccount(const FString &nickname, const FString &address, const FString &passphrase)
{
	Nickname = nickname;
	Address = address;
	PassPhrase = passphrase;
}

CsEthereumAccount::~CsEthereumAccount(){}

// Interface
#pragma region

const FString& CsEthereumAccount::GetNickname() { return Nickname; }

FString CsEthereumAccount::ToString()
{
	return ECsCachedString::Str::Empty;
}

void CsEthereumAccount::Parse(const FString &Str)
{

}

void CsEthereumAccount::ParseFromFilePath(const FString &Path)
{

}

#pragma endregion Interface

void CsEthereumAccount::CreateUnlockArguments(TArray<FCsBlockchainCommandArgument> &OutArgs)
{
	OutArgs.Add(FCsBlockchainCommandArgument(ECsBlockchainCommandArgumentType::StringString, Address));
	OutArgs.Add(FCsBlockchainCommandArgument(ECsBlockchainCommandArgumentType::StringString, PassPhrase));
	OutArgs.Add(FCsBlockchainCommandArgument(ECsBlockchainCommandArgumentType::Int32, 0));
}

FString CsEthereumAccount::AddressAsHex()
{
	return TEXT("0x") + Address;
}

FString CsEthereumAccount::AddressAsArg()
{
	return TEXT("'") + AddressAsHex() + TEXT("'");
}