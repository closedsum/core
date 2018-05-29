// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "Blockchain/Ethereum/CsEthereumContract.h"
#include "CsCore.h"

#include "Json.h"
#include "JsonObjectConverter.h"

#include "Runtime/Core/Public/HAL/FileManagerGeneric.h"

// Web3DeployLink
#pragma region

FCsEthereumWeb3DeployLink::FCsEthereumWeb3DeployLink() {}
FCsEthereumWeb3DeployLink::FCsEthereumWeb3DeployLink(const FECsBlockchainContract &InContract, const FString &InLink)
{
	Contract = InContract;
	Link = InLink;
}

FCsEthereumWeb3DeployLink::~FCsEthereumWeb3DeployLink() {}

FCsEthereumWeb3DeployLink& FCsEthereumWeb3DeployLink::operator=(const FCsEthereumWeb3DeployLink& B)
{
	Contract = B.Contract;
	Link = B.Link;
	return *this;
}

bool FCsEthereumWeb3DeployLink::operator==(const FCsEthereumWeb3DeployLink& B) const
{
	return Contract == B.Contract && Link == B.Link;
}

bool FCsEthereumWeb3DeployLink::operator!=(const FCsEthereumWeb3DeployLink& B) const
{
	return !(*this == B);
}

void FCsEthereumWeb3DeployLink::Set(const FECsBlockchainContract &InContract, const FString &InLink)
{
	Contract = InContract;
	Link = InLink;
}

#pragma endregion Web3DeployLink

CsEthereumContract::CsEthereumContract() : ICsBlockchainContract()
{
}

CsEthereumContract::CsEthereumContract(const FString &name)
{
	Address = TEXT("");
	ContractVariableName = name.ToLower() + TEXT("Contract");
	InstanceVariableName = name.ToLower() + TEXT("Instance");
}

CsEthereumContract::~CsEthereumContract(){}

const FString& CsEthereumContract::GetName() { return Name; }

bool CsEthereumContract::IsValid()
{
	return false;
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
	IFileManager& FileManager = FFileManagerGeneric::Get();

	if (FileManager.FileExists(*Path))
	{
		FString Str;
		FFileHelper::LoadFileToString(Str, *Path);

		Parse(Str);
	}
	else
	{
		UE_LOG(LogCs, Warning, TEXT("UCsEthereumGenesis::ParseFromFilePath: Path %s does NOT Exist."), *Path);
	}
}

FString CsEthereumContract::GetAddressAsArg()
{
	return TEXT("'0x") + Address + TEXT("'");
}