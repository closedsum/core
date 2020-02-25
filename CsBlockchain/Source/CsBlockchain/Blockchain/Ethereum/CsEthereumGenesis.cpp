// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Blockchain/Ethereum/CsEthereumGenesis.h"
#include "CsBlockchain.h"

#include "Json.h"
#include "JsonObjectConverter.h"

#include "Runtime/Core/Public/HAL/FileManagerGeneric.h"

// Config
#pragma region

FCsEthereumGenesisConfig::FCsEthereumGenesisConfig()
{
	chainId = 15;
	homesteadBlock = 0;
	eip155Block = 0;
	eip158Block = 0;
}
FCsEthereumGenesisConfig::~FCsEthereumGenesisConfig() {}

FCsEthereumGenesisConfig& FCsEthereumGenesisConfig::operator=(const FCsEthereumGenesisConfig& B)
{
	chainId = B.chainId;
	homesteadBlock = B.homesteadBlock;
	eip155Block = B.eip155Block;
	eip158Block = B.eip158Block;
	return *this;
}

bool FCsEthereumGenesisConfig::operator==(const FCsEthereumGenesisConfig& B) const
{
	if (chainId != B.chainId)
		return false;
	if (homesteadBlock != B.homesteadBlock)
		return false;
	if (eip155Block != B.eip155Block)
		return false;
	if (eip158Block != B.eip158Block)
		return false;
	return true;
}

bool FCsEthereumGenesisConfig::operator!=(const FCsEthereumGenesisConfig& B) const
{
	return !(*this == B);
}

#pragma endregion Config

// Address Balance
#pragma region

FCsEthereumGenesisAddressBalance::FCsEthereumGenesisAddressBalance() {}
FCsEthereumGenesisAddressBalance::FCsEthereumGenesisAddressBalance(const FString &_balance)
{
	balance = _balance;
}
FCsEthereumGenesisAddressBalance::~FCsEthereumGenesisAddressBalance() {}

FCsEthereumGenesisAddressBalance& FCsEthereumGenesisAddressBalance::operator=(const FCsEthereumGenesisAddressBalance& B)
{
	balance = B.balance;
	return *this;
}

bool FCsEthereumGenesisAddressBalance::operator==(const FCsEthereumGenesisAddressBalance& B) const
{
	return balance != B.balance;
}

bool FCsEthereumGenesisAddressBalance::operator!=(const FCsEthereumGenesisAddressBalance& B) const
{
	return !(*this == B);
}

#pragma endregion Address Balance

UCsEthereumGenesis::UCsEthereumGenesis(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	difficulty = TEXT("0x20");
	gasLimit = TEXT("0x2540BE400");
}

// Interface
#pragma region

FString UCsEthereumGenesis::ToString()
{
	FString OutputString;
	TSharedRef<TJsonWriter<TCHAR>> JsonWriter = TJsonWriterFactory<>::Create(&OutputString);

	JsonWriter->WriteObjectStart();

	// config
	{
		JsonWriter->WriteObjectStart(TEXT("config"));

		// chainId
		JsonWriter->WriteValue(TEXT("chainId"), config.chainId);
		// homesteadBlock
		JsonWriter->WriteValue(TEXT("homesteadBlock"), config.homesteadBlock);
		// eip155Block
		JsonWriter->WriteValue(TEXT("eip155Block"), config.eip155Block);
		// eip158Block
		JsonWriter->WriteValue(TEXT("eip158Block"), config.eip158Block);

		JsonWriter->WriteObjectEnd();
	}
	// difficulty
	JsonWriter->WriteValue(TEXT("difficulty"), difficulty);
	// gasLimit
	JsonWriter->WriteValue(TEXT("gasLimit"), gasLimit);
	// alloc
	{
		JsonWriter->WriteObjectStart(TEXT("alloc"));

		TArray<FString> Keys;
		alloc.GetKeys(Keys);

		const int32 Count = Keys.Num();

		for (int32 I = 0; I < Count; ++I)
		{
			const FString& Key = Keys[I];

			JsonWriter->WriteObjectStart(Key);

			// balance
			JsonWriter->WriteValue(TEXT("balance"), alloc[Key].balance);

			JsonWriter->WriteObjectEnd();
		}

		JsonWriter->WriteObjectEnd();
	}

	JsonWriter->WriteObjectEnd();

	JsonWriter->Close();

	return OutputString;
}

void UCsEthereumGenesis::Parse(const FString &Str)
{
	TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(Str);

	TSharedPtr<FJsonObject> JsonParsed;

	if (FJsonSerializer::Deserialize(JsonReader, JsonParsed) && JsonParsed.IsValid())
	{
		// config
		{
			TSharedPtr<FJsonObject> JsonObject = JsonParsed->Values.Find(TEXT("config"))->Get()->AsObject();

			// chainId
			config.chainId = JsonObject->GetIntegerField(TEXT("chainId"));
			// homesteadBlock
			config.homesteadBlock = JsonObject->GetIntegerField(TEXT("homesteadBlock"));
			// eip155Block
			config.eip155Block = JsonObject->GetIntegerField(TEXT("eip155Block"));
			// eip158Block
			config.eip158Block = JsonObject->GetIntegerField(TEXT("eip158Block"));
		}
		// difficulty
		difficulty = JsonParsed->GetStringField(TEXT("difficulty"));
		// gasLimit
		difficulty = JsonParsed->GetStringField(TEXT("gasLimit"));
		// alloc
		{
			alloc.Reset();

			TSharedPtr<FJsonObject> JsonObject = JsonParsed->Values.Find(TEXT("alloc"))->Get()->AsObject();

			TArray<FString> Keys;
			JsonObject->Values.GetKeys(Keys);

			const int32 Count = Keys.Num();

			for (int32 I = 0; I < Count; ++I)
			{
				const FString& Key = Keys[I];

				TSharedPtr<FJsonValue> JsonValue = JsonObject->Values[Key];
				
				FCsEthereumGenesisAddressBalance Balance(JsonValue->AsString());

				alloc.Add(Key, Balance);
			}
		}
	}
	else
	{
		UE_LOG(LogCsBlockchain, Warning, TEXT("UCsEthereumGenesis::Parse: Input string is NOT a Valid Genesis string."));
	}
}

void UCsEthereumGenesis::ParseFromFilePath(const FString &Path)
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
		UE_LOG(LogCsBlockchain, Warning, TEXT("UCsEthereumGenesis::ParseFromFilePath: Path %s does NOT Exist."), *Path);
	}
}

#pragma endregion Interface
