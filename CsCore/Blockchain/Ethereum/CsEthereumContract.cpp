// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
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

// Cache
#pragma region

namespace NCsEthereumContractCache
{
	namespace Str
	{
		const FString Name = TEXT("Name");
		const FString Address = TEXT("Address");
		const FString ContractVariableName = TEXT("ContractVariableName");
		const FString InstanceVariableName = TEXT("InstanceVariableName");
		const FString ABI = TEXT("ABI");

		const FString constant = TEXT("constant");
		const FString inputs = TEXT("inputs");
		const FString name = TEXT("name");
		const FString outputs = TEXT("outputs");
		const FString payable = TEXT("payable");
		const FString stateMutability = TEXT("stateMutability");
		const FString type = TEXT("type");
	}
}

#pragma endregion Cache

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
	FString OutputString;
	TSharedRef<TJsonWriter<TCHAR>> JsonWriter = TJsonWriterFactory<>::Create(&OutputString);

	JsonWriter->WriteObjectStart();

	// Name
	JsonWriter->WriteValue(NCsEthereumContractCache::Str::Name, Name);
	// Address
	JsonWriter->WriteValue(NCsEthereumContractCache::Str::Address, Address);
	// ContractVariableName
	JsonWriter->WriteValue(NCsEthereumContractCache::Str::ContractVariableName, ContractVariableName);
	// InstanceVariableName
	JsonWriter->WriteValue(NCsEthereumContractCache::Str::InstanceVariableName, InstanceVariableName);

	// ABI
	{
		JsonWriter->WriteArrayStart(NCsEthereumContractCache::Str::ABI);

		for (const FCsEthereumABI& A : ABI)
		{
			JsonWriter->WriteObjectStart();

			// constant
			JsonWriter->WriteValue(NCsEthereumContractCache::Str::constant, A.constant);
			// inputs
			{
				JsonWriter->WriteArrayStart(NCsEthereumContractCache::Str::inputs);

				for (const FCsEthereumABIInput& Input : A.inputs)
				{
					JsonWriter->WriteObjectStart();

					// name
					JsonWriter->WriteValue(NCsEthereumContractCache::Str::name, Input.name);
					// type
					JsonWriter->WriteValue(NCsEthereumContractCache::Str::type, Input.type);

					JsonWriter->WriteObjectEnd();
				}

				JsonWriter->WriteArrayEnd();
			}
			// name
			JsonWriter->WriteValue(NCsEthereumContractCache::Str::name, A.name);
			// outputs
			{
				JsonWriter->WriteArrayStart(NCsEthereumContractCache::Str::outputs);

				for (const FCsEthereumABIOutput& Output : A.outputs)
				{
					JsonWriter->WriteObjectStart();

					// name
					JsonWriter->WriteValue(NCsEthereumContractCache::Str::name, Output.name);
					// type
					JsonWriter->WriteValue(NCsEthereumContractCache::Str::type, Output.type);

					JsonWriter->WriteObjectEnd();
				}

				JsonWriter->WriteArrayEnd();
			}
			// payable
			JsonWriter->WriteValue(NCsEthereumContractCache::Str::payable, A.payable);
			// stateMutability
			JsonWriter->WriteValue(NCsEthereumContractCache::Str::stateMutability, A.stateMutability);
			// type
			JsonWriter->WriteValue(NCsEthereumContractCache::Str::type, A.type);

			JsonWriter->WriteObjectEnd();
		}

		JsonWriter->WriteArrayEnd();
	}

	JsonWriter->WriteObjectEnd();

	JsonWriter->Close();

	return OutputString;
}

void CsEthereumContract::Parse(const FString &Str)
{
	TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(Str);

	TSharedPtr<FJsonObject> JsonParsed;

	if (FJsonSerializer::Deserialize(JsonReader, JsonParsed) && JsonParsed.IsValid())
	{

		// Name
		Name = JsonParsed->GetStringField(NCsEthereumContractCache::Str::Name);
		// Address
		Address		 = JsonParsed->GetStringField(NCsEthereumContractCache::Str::Address);
		AddressAsArg = TEXT("'0x") + Address + TEXT("'");
		// ContractVariableName
		ContractVariableName = JsonParsed->GetStringField(NCsEthereumContractCache::Str::ContractVariableName);
		// InstanceVariableName
		InstanceVariableName = JsonParsed->GetStringField(NCsEthereumContractCache::Str::InstanceVariableName);
		// ABI
		{
			ABI.Reset();

			const TArray<TSharedPtr<FJsonValue>>& JsonArray = JsonParsed->Values.Find(NCsEthereumContractCache::Str::ABI)->Get()->AsArray();

			const int32 Count = JsonArray.Num();

			for (int32 I = 0; I < Count; ++I)
			{
				ABI.AddDefaulted();

				const TSharedPtr<FJsonValue>& JsonValue	  = JsonArray[I];
				const TSharedPtr<FJsonObject>& JsonObject = JsonValue->AsObject();

				// constant
				JsonObject->TryGetBoolField(NCsEthereumContractCache::Str::constant, ABI[I].constant);
				// inputs
				{
					ABI[I].inputs.Reset();

					const TArray<TSharedPtr<FJsonValue>>* ArrayPtr;
					
					if (JsonObject->TryGetArrayField(NCsEthereumContractCache::Str::inputs, ArrayPtr))
					{
						const TArray<TSharedPtr<FJsonValue>>& Array = *ArrayPtr;

						const int32 ArrayCount = Array.Num();

						for (int32 J = 0; J < ArrayCount; ++J)
						{
							ABI[I].inputs.AddDefaulted();

							const TSharedPtr<FJsonValue>& Value   = Array[J];
							const TSharedPtr<FJsonObject>& Object = Value->AsObject();

							// name
							ABI[I].inputs[J].name = Object->GetStringField(NCsEthereumContractCache::Str::name);
							// type
							ABI[I].inputs[J].type = Object->GetStringField(NCsEthereumContractCache::Str::type);
						}
					}
				}
				// name
				JsonObject->TryGetStringField(NCsEthereumContractCache::Str::name, ABI[I].name);
				// outputs
				{
					ABI[I].outputs.Reset();

					const TArray<TSharedPtr<FJsonValue>>* ArrayPtr;

					if (JsonObject->TryGetArrayField(NCsEthereumContractCache::Str::outputs, ArrayPtr))
					{
						const TArray<TSharedPtr<FJsonValue>>& Array = *ArrayPtr;

						const int32 ArrayCount = Array.Num();

						for (int32 J = 0; J < ArrayCount; ++J)
						{
							ABI[I].outputs.AddDefaulted();

							const TSharedPtr<FJsonValue>& Value = Array[J];
							const TSharedPtr<FJsonObject>& Object = Value->AsObject();

							// name
							ABI[I].outputs[J].name = Object->GetStringField(NCsEthereumContractCache::Str::name);
							// type
							ABI[I].outputs[J].type = Object->GetStringField(NCsEthereumContractCache::Str::type);
						}
					}
				}
				// payable
				JsonObject->TryGetBoolField(NCsEthereumContractCache::Str::payable, ABI[I].payable);
				// stateMutability
				JsonObject->TryGetStringField(NCsEthereumContractCache::Str::stateMutability, ABI[I].stateMutability);
				// type
				JsonObject->TryGetStringField(NCsEthereumContractCache::Str::type, ABI[I].type);
			}
		}
	}
	else
	{
		UE_LOG(LogCs, Warning, TEXT("CsEthereumContract::Parse: Input string is NOT a Valid Genesis string."));
	}
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
		UE_LOG(LogCs, Warning, TEXT("CsEthereumContract::ParseFromFilePath: Path %s does NOT Exist."), *Path);
	}
}

const FString& CsEthereumContract::GetAddressAsArg()
{
	return AddressAsArg;
}