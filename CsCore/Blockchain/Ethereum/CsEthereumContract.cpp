// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "Blockchain/Ethereum/CsEthereumContract.h"

CsEthereumContract::CsEthereumContract(const FString &name)
{
	Address = TEXT("");
	ContractVariableName = name.ToLower() + TEXT("Contract");
	InstanceVariableName = name.ToLower() + TEXT("Instance");
}

const FString& CsEthereumContract::GetName() { return Name; }

bool CsEthereumContract::IsValid()
{

}

FString CsEthereumContract::ToString()
{
	return TEXT("");
}

void CsEthereumContract::Parse(const FString &Str)
{
}

void CsEthereumContract::ParseFromFilePath(const FString &Path)
{
}

FString CsEthereumContract::AddressAsArg()
{
	return TEXT("'0x") + Address + TEXT("'");
}