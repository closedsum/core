// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "Blockchain/CsBlockchainContract.h"
#include "CsEthereumContract.generated.h"

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
};

USTRUCT(BlueprintType)
struct CSCORE_API FCsEthereumWeb3DeployLink
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ethereum")
	FECsBlockchainContract Contract;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ethereum")
	FString Link;

	FCsEthereumWeb3DeployLink();
	FCsEthereumWeb3DeployLink(const FECsBlockchainContract &InContract, const FString &InLink);
	~FCsEthereumWeb3DeployLink();

	FCsEthereumWeb3DeployLink& operator=(const FCsEthereumWeb3DeployLink& B);
	bool operator==(const FCsEthereumWeb3DeployLink& B) const;
	bool operator!=(const FCsEthereumWeb3DeployLink& B) const;

	void Set(const FECsBlockchainContract &InContract, const FString &InLink);
};

class CSCORE_API CsEthereumContract : public ICsBlockchainContract
{
// Interface
#pragma region

public:

	CsEthereumContract();
	CsEthereumContract(const FString &InName);
	~CsEthereumContract();

	FString Name;

	virtual const FString& GetName() override;

	virtual bool IsValid() override;
	virtual FString ToString() override;
	virtual void Parse(const FString &Str) override;
	virtual void ParseFromFilePath(const FString &Path) override;

#pragma endregion Interface

public:

	TArray<FCsEthereumABI> ABI;
	FString Address;
	FString ContractVariableName;
	FString InstanceVariableName;

	FString GetAddressAsArg();
};