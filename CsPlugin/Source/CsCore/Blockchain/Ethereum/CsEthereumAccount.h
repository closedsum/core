// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "Blockchain/CsBlockchainAccount.h"
#include "Blockchain/CsBlockchainCommand.h"

class CSCORE_API CsEthereumAccount : public ICsBlockchainAccount
{
// Interface
#pragma region
public:

	CsEthereumAccount();
	~CsEthereumAccount();

	FString Nickname;

	virtual const FString& GetNickname();

	virtual FString ToString();
	virtual void Parse(const FString &Str);
	virtual void ParseFromFilePath(const FString &Path);

#pragma endregion Interface

public:

	CsEthereumAccount(const FString& nickname, const FString &address, const FString &passphrase);

	FString Address;
	FString Passphrase;

private:
	FString AddressAsHex;
public:
	const FString& GetAddressAsHex();
private:
	FString AddressAsArg;
public:
	const FString& GetAddressAsArg();

	void CreateUnlockArguments(TArray<FCsBlockchainCommandArgument> &OutArgs);
};