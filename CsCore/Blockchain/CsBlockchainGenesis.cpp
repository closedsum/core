// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Blockchain/CsBlockchainGenesis.h"
#include "CsCore.h"

UCsBlockchainGenesis::UCsBlockchainGenesis(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

FString UCsBlockchainGenesis::ToString()
{
	return NCsCached::Str::Empty;
}

void UCsBlockchainGenesis::Parse(const FString &Str){}

void UCsBlockchainGenesis::ParseFromFilePath(const FString &Path){}