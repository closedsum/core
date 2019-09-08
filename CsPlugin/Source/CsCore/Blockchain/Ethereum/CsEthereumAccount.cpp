// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Blockchain/Ethereum/CsEthereumAccount.h"
#include "CsCore.h"

#include "Json.h"
#include "JsonObjectConverter.h"

#include "Runtime/Core/Public/HAL/FileManagerGeneric.h"

CsEthereumAccount::CsEthereumAccount() : ICsBlockchainAccount()
{
}

CsEthereumAccount::CsEthereumAccount(const FString &nickname, const FString &address, const FString &passphrase)
{
	Nickname = nickname;
	Address = address;
	Passphrase = passphrase;

	AddressAsHex = TEXT("0x") + Address;
	AddressAsArg = TEXT("'") + AddressAsHex + TEXT("'");
}

CsEthereumAccount::~CsEthereumAccount(){}

// Interface
#pragma region

const FString& CsEthereumAccount::GetNickname() { return Nickname; }

FString CsEthereumAccount::ToString()
{
	FString OutputString;
	TSharedRef<TJsonWriter<TCHAR>> JsonWriter = TJsonWriterFactory<>::Create(&OutputString);

	JsonWriter->WriteObjectStart();

		// Nickname
		JsonWriter->WriteValue(TEXT("Nickname"), Nickname);
		// Address
		JsonWriter->WriteValue(TEXT("Address"), Address);
		// Passphrase
		JsonWriter->WriteValue(TEXT("Passphrase"), Passphrase);

	JsonWriter->WriteObjectEnd();

	JsonWriter->Close();

	return OutputString;
}

void CsEthereumAccount::Parse(const FString &Str)
{
	TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(Str);

	TSharedPtr<FJsonObject> JsonParsed;

	if (FJsonSerializer::Deserialize(JsonReader, JsonParsed) && JsonParsed.IsValid())
	{
		// Nickname
		Nickname = JsonParsed->GetStringField(TEXT("Nickname"));
		// Address
		Address = JsonParsed->GetStringField(TEXT("Address"));
		AddressAsHex = TEXT("0x") + Address;
		AddressAsArg = TEXT("'") + AddressAsHex + TEXT("'");
		// Passphrase
		Passphrase = JsonParsed->GetStringField(TEXT("Passphrase"));
	}
	else
	{
		UE_LOG(LogCs, Warning, TEXT("CsEthereumAccount::Parse: Input string is NOT a Valid Account string."));
	}
}

void CsEthereumAccount::ParseFromFilePath(const FString &Path)
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
		UE_LOG(LogCs, Warning, TEXT("CsEthereumAccount::ParseFromFilePath: Path %s does NOT Exist."), *Path);
	}
}

#pragma endregion Interface

void CsEthereumAccount::CreateUnlockArguments(TArray<FCsBlockchainCommandArgument> &OutArgs)
{
	const uint8 ARGUMENTS = 3;
	const uint8 ADDRESS = 0;
	const uint8 PASSPHRASE = 1;
	const uint8 TIME = 2;

	OutArgs.SetNum(ARGUMENTS);
	OutArgs[ADDRESS].Set(ECsBlockchainCommandArgumentType::StringString, Address);
	OutArgs[PASSPHRASE].Set(ECsBlockchainCommandArgumentType::StringString, Passphrase);
	OutArgs[TIME].Set(ECsBlockchainCommandArgumentType::Int32, 0);
}

const FString& CsEthereumAccount::GetAddressAsHex()
{
	return AddressAsHex;
}

const FString& CsEthereumAccount::GetAddressAsArg()
{
	return AddressAsArg;
}