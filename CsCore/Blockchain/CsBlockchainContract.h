// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "CsBlockchainContract.generated.h"

USTRUCT(BlueprintType)
struct FECsBlockchainContract : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

public:
	FECsBlockchainContract() {}
	FECsBlockchainContract(const uint8 &InValue, const FString &InName) : FECsEnum_uint8(InValue, InName) {}
	~FECsBlockchainContract() {}
};

FORCEINLINE uint32 GetTypeHash(const FECsBlockchainContract& b)
{
	return FCrc::MemCrc_DEPRECATED(&b, sizeof(FECsBlockchainContract));
}

struct EMCsBlockchainContract : public TCsEnumMap<FECsBlockchainContract, uint8>
{
protected:
	EMCsBlockchainContract() {}
	EMCsBlockchainContract(const EMCsBlockchainContract &) = delete;
	EMCsBlockchainContract(EMCsBlockchainContract &&) = delete;
public:
	~EMCsBlockchainContract() {}

	static EMCsBlockchainContract& Get()
	{
		static EMCsBlockchainContract Instance;
		return Instance;
	}
};

class ICsBlockchainContract
{
public:

	ICsBlockchainContract();
	virtual ~ICsBlockchainContract();

	virtual const FString& GetName() = 0;

	virtual bool IsValid() = 0;
	virtual FString ToString() = 0;
	virtual void Parse(const FString &Str) = 0;
	virtual void ParseFromFilePath(const FString &Path) = 0;
};