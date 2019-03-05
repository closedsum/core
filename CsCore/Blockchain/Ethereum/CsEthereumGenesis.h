// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
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

	FCsEthereumGenesisConfig();
	~FCsEthereumGenesisConfig();

	FCsEthereumGenesisConfig& operator=(const FCsEthereumGenesisConfig& B);
	bool operator==(const FCsEthereumGenesisConfig& B) const;
	bool operator!=(const FCsEthereumGenesisConfig& B) const;
};

USTRUCT(BlueprintType)
struct FCsEthereumGenesisAddressBalance
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blockchain Genesis")
	FString balance;

	FCsEthereumGenesisAddressBalance();
	FCsEthereumGenesisAddressBalance(const FString &_balance);
	~FCsEthereumGenesisAddressBalance();

	FCsEthereumGenesisAddressBalance& operator=(const FCsEthereumGenesisAddressBalance& B);
	bool operator==(const FCsEthereumGenesisAddressBalance& B) const;
	bool operator!=(const FCsEthereumGenesisAddressBalance& B) const;
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