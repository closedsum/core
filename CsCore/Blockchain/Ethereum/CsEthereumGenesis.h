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
};

USTRUCT(BlueprintType)
struct FCsEthereumGenesisAddressBalance
{
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blockchain Genesis")
	FString balance;

	FCsEthereumGenesisAddressBalance(){}
	FCsEthereumGenesisAddressBalance(const FString &_balance)
	{
		balance = _balance;
	}
	~FCsEthereumGenesisAddressBalance(){}
}

UCLASS(transient)
class CSCORE_API UCsEthereumGenesis : public UCsBlockchainGenesis
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blockchain Genesis")
	FCsEthereumGenesisConfig config;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blockchain Genesis")
	FString difficulty;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blockchain Genesis")
	FString gasLimit;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blockchain Genesis")
	TMap<FString, FCsEthereumGenesisAddressBalance> alloc;
};