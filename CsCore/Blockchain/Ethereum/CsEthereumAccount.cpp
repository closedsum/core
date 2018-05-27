// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
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
		// chainId
		Nickname = JsonParsed->GetStringField(TEXT("chainId"));
		// Address
		Address = JsonParsed->GetStringField(TEXT("Address"));
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
	OutArgs.Add(FCsBlockchainCommandArgument(ECsBlockchainCommandArgumentType::StringString, Address));
	OutArgs.Add(FCsBlockchainCommandArgument(ECsBlockchainCommandArgumentType::StringString, Passphrase));
	OutArgs.Add(FCsBlockchainCommandArgument(ECsBlockchainCommandArgumentType::Int32, 0));
}

FString CsEthereumAccount::AddressAsHex()
{
	return TEXT("0x") + Address;
}

FString CsEthereumAccount::AddressAsArg()
{
	return TEXT("'") + AddressAsHex() + TEXT("'");
}