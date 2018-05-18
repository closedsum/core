// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "Blockchain/CsBlockchainContract.h"

struct FCsEthereumABI
{
public:

	bool constant;
	TArray<FString> inputs;
	FString name;
	TArray<FString> outputs;
	bool payable;
	FString stateMutability;
	FString type;

	FCsEthereumABI(){}
	~FCsEthereumABI(){}
}

public struct CgEthereumWeb3DeployLink
{
	public readonly ECgBlockchainContract Contract;
	public readonly string Link;

	public CgEthereumWeb3DeployLink(ECgBlockchainContract contract, string link)
	{
		Contract = contract;
		Link = link;
	}
}

class CsEthereumContract : ICsBlockchainContract
{
// Interface
#pragma region

public:

	FString Name;

	virtual const FString& GetName() override;

	virtual bool IsValid() override;
	virtual FString ToString() override;
	virtual void Parse(const FString &Str) override;
	virtual void ParseFromFilePath(const FString &Path) override;

#pragma endregion Interface

public:

	CsEthereumContract(const FString &name);

	TArray<FCsEthereumABI> ABI;
	FString Address;
	FString ContractVariableName;
	FString InstanceVariableName;

	FString AddressAsArg();
};