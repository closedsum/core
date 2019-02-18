// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "Blockchain/CsBlockchainContract.h"
#include "CsEthereumContract.generated.h"

USTRUCT(BlueprintType)
struct CSCORE_API FCsEthereumABIInput
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ethereum")
	FString name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ethereum")
	FString type;

	FCsEthereumABIInput() {}
	~FCsEthereumABIInput() {}

	FORCEINLINE FCsEthereumABIInput& operator=(const FCsEthereumABIInput& B)
	{
		name = B.name;
		type = B.type;
		return *this;
	}

	FORCEINLINE bool operator==(const FCsEthereumABIInput& B) const
	{
		return name == B.name && type == B.type;
	}

	FORCEINLINE bool operator!=(const FCsEthereumABIInput& B) const
	{
		return !(*this == B);
	}
};

USTRUCT(BlueprintType)
struct CSCORE_API FCsEthereumABIOutput
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ethereum")
	FString name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ethereum")
	FString type;

	FCsEthereumABIOutput() {}
	~FCsEthereumABIOutput() {}

	FORCEINLINE FCsEthereumABIOutput& operator=(const FCsEthereumABIOutput& B)
	{
		name = B.name;
		type = B.type;
		return *this;
	}

	FORCEINLINE bool operator==(const FCsEthereumABIOutput& B) const
	{
		return name == B.name && type == B.type;
	}

	FORCEINLINE bool operator!=(const FCsEthereumABIOutput& B) const
	{
		return !(*this == B);
	}
};

USTRUCT(BlueprintType)
struct CSCORE_API FCsEthereumABI
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ethereum")
	bool constant;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ethereum")
	TArray<FCsEthereumABIInput> inputs;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ethereum")
	FString name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ethereum")
	TArray<FCsEthereumABIOutput> outputs;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ethereum")
	bool payable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ethereum")
	FString stateMutability;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ethereum")
	FString type;

	FCsEthereumABI() :
		constant(false),
		name(),
		payable(false),
		stateMutability(),
		type()
	{
	}

	~FCsEthereumABI(){}

	FORCEINLINE FCsEthereumABI& operator=(const FCsEthereumABI& B)
	{
		constant = B.constant;

		inputs.Reset();

		for (const FCsEthereumABIInput& input : B.inputs)
		{
			inputs.Add(input);
		}

		name = B.name;

		outputs.Reset();

		for (const FCsEthereumABIOutput& output : B.outputs)
		{
			outputs.Add(output);
		}

		payable = B.payable;
		stateMutability = B.stateMutability;
		type = B.type;
		return *this;
	}

	FORCEINLINE bool operator==(const FCsEthereumABI& B) const
	{
		if (constant != B.constant)
			return false;

		if (inputs.Num() != B.inputs.Num())
			return false;

		const int32 InputCount = inputs.Num();

		for (int32 I = 0; I < InputCount; ++I)
		{
			if (inputs[I] != B.inputs[I])
				return false;
		}

		if (name != B.name)
			return false;

		if (outputs.Num() != B.outputs.Num())
			return false;

		const int32 OutputCount = outputs.Num();

		for (int32 I = 0; I < OutputCount; ++I)
		{
			if (outputs[I] != B.outputs[I])
				return false;
		}

		if (payable != B.payable)
			return false;

		if (stateMutability != B.stateMutability)
			return false;

		if (type != B.type)
			return false;
		return true;
	}

	FORCEINLINE bool operator!=(const FCsEthereumABI& B) const
	{
		return !(*this == B);
	}
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

	FString Address;
private:
	FString AddressAsArg;
public:
	FString ContractVariableName;
	FString InstanceVariableName;
	TArray<FCsEthereumABI> ABI;

	const FString& GetAddressAsArg();
};