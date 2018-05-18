// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "Blockchain/CsBlockchainAccount.h"
#include "Blockchain/CsBlockchainCommand.h"

class CsEthereumAccount : ICsBlockchainAccount
{
// Interface
#pragma region
public:

	CsEthereumAccount();
	~CsEthereumAccount();

	FString Nickname;

	virtual const FString& GetNamename() = 0;

	virtual FString ToString() = 0;
	virtual void Parse(const FString &Str) = 0;
	virtual void ParseFromFilePath(const FString &Path) = 0;

#pragma endregion Interface

public:

	FString Address;
	FString PassPhrase;

	CsEthereumAccount(const FString& nickname, const FString &address, const FString &passphrase);

	void CreateUnlockArguments(TArray<FCsBlockchainCommandArgument> &OutArgs);

	FString AddressAsArg();
};