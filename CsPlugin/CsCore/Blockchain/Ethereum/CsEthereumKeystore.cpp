// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Blockchain/Ethereum/CsEthereumKeystore.h"
#include "CsCore.h"

#include "Json.h"
#include "JsonObjectConverter.h"

#include "Runtime/Core/Public/HAL/FileManagerGeneric.h"

FCsEthereumKeystore::FCsEthereumKeystore() :
	address(),
	crypto(),
	id(),
	version(0)
{
}

FCsEthereumKeystore::~FCsEthereumKeystore(){}

void FCsEthereumKeystore::Parse(const FString &Str)
{
	TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(Str);

	TSharedPtr<FJsonObject> JsonParsed;

	if (FJsonSerializer::Deserialize(JsonReader, JsonParsed) && JsonParsed.IsValid())
	{
		// address
		address = JsonParsed->GetStringField(TEXT("address"));
		// crypto
		{
			TSharedPtr<FJsonObject> JsonObject = JsonParsed->Values.Find(TEXT("crypto"))->Get()->AsObject();

			// cipher
			crypto.cipher = JsonObject->GetStringField(TEXT("cipher"));
			// ciphertext
			crypto.ciphertext = JsonObject->GetStringField(TEXT("ciphertext"));
			// cipherparams
			{
				TSharedPtr<FJsonObject> Object = JsonObject->GetObjectField(TEXT("cipherparams"));

				// iv
				crypto.cipherparams.iv = Object->GetStringField(TEXT("iv"));
			}
			// kdf
			crypto.kdf = JsonObject->GetStringField(TEXT("kdf"));
			// kdfparams
			{
				TSharedPtr<FJsonObject> Object = JsonObject->GetObjectField(TEXT("kdfparams"));

				// dklen
				crypto.kdfparams.dklen = Object->GetIntegerField(TEXT("dklen"));
				// n
				crypto.kdfparams.n = Object->GetIntegerField(TEXT("n"));
				// p
				crypto.kdfparams.p = Object->GetIntegerField(TEXT("p"));
				// r
				crypto.kdfparams.r = Object->GetIntegerField(TEXT("r"));
				// salt
				crypto.kdfparams.salt = Object->GetStringField(TEXT("salt"));
			}
			// mac
			crypto.mac = JsonObject->GetStringField(TEXT("mac"));
		}
		// id
		id = JsonParsed->GetStringField(TEXT("id"));
		// version
		version = JsonParsed->GetIntegerField(TEXT("version"));
	}
	else
	{
		UE_LOG(LogCs, Warning, TEXT("FCsEthereumKeystore::Parse: Input string is NOT a Valid Genesis string."));
	}
}

void FCsEthereumKeystore::ParseFromFilePath(const FString &Path)
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
		UE_LOG(LogCs, Warning, TEXT("FCsEthereumKeystore::ParseFromFilePath: Path %s does NOT Exist."), *Path);
	}
}