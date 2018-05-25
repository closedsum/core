// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "Blockchain/CsBlockchainContract.h"

EMCsBlockchainContract* EMCsBlockchainContract::Instance;

EMCsBlockchainContract& EMCsBlockchainContract::Get()
{
	if (!Instance)
		Instance = new EMCsBlockchainContract();
	return *Instance;
}

EMCsBlockchainContractFunction* EMCsBlockchainContractFunction::Instance;

EMCsBlockchainContractFunction& EMCsBlockchainContractFunction::Get()
{
	if (!Instance)
		Instance = new EMCsBlockchainContractFunction();
	return *Instance;
}

ICsBlockchainContract::ICsBlockchainContract(){}
ICsBlockchainContract::ICsBlockchainContract(const FString &InName){}
ICsBlockchainContract::~ICsBlockchainContract(){}