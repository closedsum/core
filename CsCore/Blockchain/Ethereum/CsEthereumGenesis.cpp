// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "Blockchain/Ethereum/CsEthereumGenesis.h"
#include "CsCore.h"

UCsEthereumGenesis::UCsEthereumGenesis(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	difficulty = TEXT("0x20");
	gasLimit = TEXT("0x2540BE400");
}