// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "Blockchain/CsBlockchainGenesis.h"
#include "CsCore.h"

UCsBlockchainGenesis::UCsBlockchainGenesis(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

FString UCsBlockchainGenesis::ToString()
{
	return ECsCachedString::Str::Empty;
}

void UCsBlockchainGenesis::Parse(const FString &Str){}

void UCsBlockchainGenesis::ParseFromFilePath(const FString &Path){}