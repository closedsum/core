// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "Blockchain/CsBlockchainGenesis.h"
#include "CsEthereumGenesis.generated.h"

USTRUCT(BlueprintType)
struct FCsEthereumGenesisConfig
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blockchain Genesis")
	int32 chainId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blockchain Genesis")
	int32 homesteadBlock;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blockchain Genesis")
	int32 eip155Block;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blockchain Genesis")
	int32 eip158Block;

	FCsEthereumGenesisConfig()
	{
		chainId = 15;
		homesteadBlock = 0;
		eip155Block = 0;
		eip158Block = 0;
	}
	~FCsEthereumGenesisConfig(){}

	FCsEthereumGenesisConfig& operator=(const FCsEthereumGenesisConfig& B)
	{
		chainId = B.chainId;
		homesteadBlock = B.homesteadBlock;
		eip155Block = B.eip155Block;
		eip158Block = B.eip158Block;
		return *this;
	}

	bool operator==(const FCsEthereumGenesisConfig& B) const
	{
		if (chainId != B.chainId)
			return false;
		if (homesteadBlock != B.homesteadBlock)
			return false;
		if (eip155Block != B.eip155Block)
			return false;
		if (eip158Block != B.eip158Block)
			return false;
		return true;
	}

	bool operator!=(const FCsEthereumGenesisConfig& B) const
	{
		return !(*this == B);
	}
};

USTRUCT(BlueprintType)
struct FCsEthereumGenesisAddressBalance
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blockchain Genesis")
	FString balance;

	FCsEthereumGenesisAddressBalance(){}
	FCsEthereumGenesisAddressBalance(const FString &_balance)
	{
		balance = _balance;
	}
	~FCsEthereumGenesisAddressBalance(){}

	FCsEthereumGenesisAddressBalance& operator=(const FCsEthereumGenesisAddressBalance& B)
	{
		balance = B.balance;
		return *this;
	}

	bool operator==(const FCsEthereumGenesisAddressBalance& B) const
	{
		return balance != B.balance;
	}

	bool operator!=(const FCsEthereumGenesisAddressBalance& B) const
	{
		return !(*this == B);
	}
};

UCLASS(transient)
class CSCORE_API UCsEthereumGenesis : public UCsBlockchainGenesis
{
	GENERATED_UCLASS_BODY()

// Interface
#pragma region
public:

	virtual FString ToString() override;

	virtual void Parse(const FString &Str) override;

	virtual void ParseFromFilePath(const FString &Path) override;

#pragma endregion Interface

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blockchain Genesis")
	FCsEthereumGenesisConfig config;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blockchain Genesis")
	FString difficulty;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blockchain Genesis")
	FString gasLimit;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blockchain Genesis")
	TMap<FString, FCsEthereumGenesisAddressBalance> alloc;
};