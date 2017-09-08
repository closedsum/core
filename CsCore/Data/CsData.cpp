// Copyright 2017 Closed Sum Games, LLC. All Rights Reserved.
#include "Data/CsData.h"
#include "CsCore.h"
#include "CsCVars.h"
#include "CsCommon.h"

#if WITH_EDITOR
#include "Data/CsDataMapping.h"
#include "Data/CsData_Payload.h"

#include "AssetRegistryModule.h"
#include "Developer/AssetTools/Public/AssetToolsModule.h"
#include "Editor/ContentBrowser/Public/ContentBrowserModule.h"
#include "Developer/SourceControl/Public/SourceControlHelpers.h"
#endif WITH_EDITOR

ACsData::ACsData(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick		   = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	GetAssetReferencesFromObject_Internal = nullptr;
	LoadObjectWithTAssetPtrs_Internal = nullptr;
	WriteObjectToJson_Internal = nullptr;
	ReadObjectFromJson_Internal = nullptr;

	DataMappingName = TEXT("bp_data_mapping");

#if WITH_EDITOR
	DataMappingClass = ACsDataMapping::StaticClass();
#endif // #if WITH_EDITOR
}

void ACsData::PostLoad()
{
	Super::PostLoad();
	LoadFromJson();
}

void ACsData::PreSave(const class ITargetPlatform* TargetPlatform)
{
	Super::PreSave(TargetPlatform);

#if WITH_EDITOR
	OnPreSave();
	PopulateAssetReferences(true);
	UCsCommon::GetCategoryMemberAssociations(this, GetClass(), CategoryMemberAssociations);
	SaveToJson();
#endif WITH_EDITOR
}

#if WITH_EDITOR
void ACsData::OnPreSave(){}
#endif WITH_EDITOR

bool ACsData::IsValid(const ECsLoadFlags &LoadFlags /*=ECsLoadFlags::All*/)
{
	bool Pass = true;
	const FString AssetName = GetName();

	if (ShortCode == CS_INVALID_SHORT_CODE || ShortCode == NAME_None)
	{
		UE_LOG(LogCs, Warning, TEXT("ACsData::IsValid (%s): No ShortCode was set"), *AssetName);
		Pass = false;
	}

	ShortCodeAsString = ShortCode.ToString();

	if (Name == CS_INVALID_SHORT_CODE || Name == NAME_None)
	{
		UE_LOG(LogCs, Warning, TEXT("ACsData::IsValid (%s): No Name was set"), *AssetName);
	}
	return Pass;
}

void ACsData::PopulateAssetReferences(const bool &CalculateResourceSizes)
{
	const int32 Count = ECsLoadFlags_Editor::ECsLoadFlags_Editor_MAX;

	for (int32 I = 0; I < Count; I++)
	{
		AssetReferences[I].References.Reset();

		UCsCommon::GetAssetReferencesFromObject(this, GetClass(), (ECsLoadFlags)I, CalculateResourceSizes, AssetReferences[I].References, GetAssetReferencesFromObject_Internal);
		
		AssetReferences[I].CalculateSize();
	}
}

void ACsData::Load(const ECsLoadFlags &LoadFlags /*=ECsLoadFlags::All*/)
{
	const FString DataName = ShortCode.ToString();

	if (!HasLoadedFromJson)
		LoadFromJson();

	UCsCommon::LoadObjectWithTAssetPtrs(DataName, (void*)this, GetClass(), LoadFlags, LoadObjectWithTAssetPtrs_Internal);
}

void ACsData::UnLoad()
{
	UCsCommon::UnLoadObjectWithTAssetPtrs((void*)this, GetClass());
}

bool ACsData::IsLoaded()
{
	const FString DataName = ShortCode.ToString();

	return UCsCommon::IsLoadedObjectWithTAssetPtrs(DataName, (void*)this, GetClass());
}

FString ACsData::GetAbsolutePath()
{
	const FString AssetName	   = ShortCode.ToString() + TEXT(".");
	const FString InternalName = GetName();
	FString PathName		   = GetPathName();

	PathName = PathName.Replace(*InternalName, TEXT(""));
	PathName = PathName.Replace(*AssetName, TEXT(""));
	PathName = PathName.Replace(TEXT("/Game/"), TEXT(""));

	const FString GameContentDir = FPaths::ConvertRelativePathToFull(FPaths::GameContentDir());
	const FString JsonDir		 = TEXT("Json/");
	return GameContentDir + JsonDir + PathName;
}

void ACsData::SaveToJson()
{
	FString OutputString;
	TSharedRef<TJsonWriter<TCHAR>> JsonWriter = TJsonWriterFactory<>::Create(&OutputString);

	JsonWriter->WriteObjectStart();

	UCsCommon::WriteObjectToJson(JsonWriter, (void*)this, GetClass(), CategoryMemberAssociations, WriteObjectToJson_Internal);
	
	JsonWriter->WriteObjectEnd();

	JsonWriter->Close();

	const FString Filename = GetAbsolutePath() + ShortCode.ToString() + TEXT(".json");
	
	FFileHelper::SaveStringToFile(OutputString, *Filename);

#if WITH_EDITOR
	FText ErrorMessage;

	SourceControlHelpers::CheckoutOrMarkForAdd(Filename, FText::FromString(Filename), NULL, ErrorMessage);
#endif // #if WITH_EDITOR
}

void ACsData::LoadFromJson()
{
	const FString AssetName = GetName();
	const FString Filename  = GetAbsolutePath() + ShortCode.ToString() + TEXT(".json");

	if (CsCVarLogJsonDataFilenames->GetInt() == CS_CVAR_SHOW_LOG)
		UE_LOG(LogCs, Warning, TEXT("ACsData::LoadFromJson (%s): Filename: %s"), *AssetName, *Filename);

	FString DataJson;

	if (FFileHelper::LoadFileToString(DataJson, *Filename))
	{
		TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(DataJson);

		TSharedPtr<FJsonObject> JsonParsed;

		if (FJsonSerializer::Deserialize(JsonReader, JsonParsed) && JsonParsed.IsValid())
		{
			if (CategoryMemberAssociations.Num() == 0)
			{
				UE_LOG(LogCs, Warning, TEXT("ACsData::LoadFromJson (%s): Data needs to be saved at least ONCE to generate CategoryMemberAssociations"), *AssetName);
				return;
			}
			UCsCommon::ReadObjectFromJson(JsonParsed, this, GetClass(), CategoryMemberAssociations, ReadObjectFromJson_Internal);
		}
		else
		{
			UE_LOG(LogCs, Warning, TEXT("ACsData::LoadFromJson (%s): %s is NOT Valid"), *AssetName, *Filename);
			return;
		}
	}
	else
	{
		UE_LOG(LogCs, Warning, TEXT("ACsData::LoadFromJson (%s): %s NOT found"), *AssetName, *Filename);
		return;
	}
	HasLoadedFromJson = true;
}

// 99 Data Mapping
#pragma region

#if WITH_EDITOR

ACsDataMapping* ACsData::GetDataMapping()
{
	FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>(FName("AssetRegistry"));
	IAssetRegistry& AssetRegistry			  = AssetRegistryModule.Get();

	TArray<FAssetData> OutAssetData;

	AssetRegistry.GetAssetsByClass(UBlueprint::StaticClass()->GetFName(), OutAssetData);

	const int32 AssetCount = OutAssetData.Num();

	TArray<UBlueprint*> Bps;

	for (int32 K = 0; K < AssetCount; K++)
	{
		const FString AssetStringName = OutAssetData[K].AssetName.ToString().ToLower();

		if (AssetStringName == DataMappingName)
		{
			Bps.Add(Cast<UBlueprint>(OutAssetData[K].GetAsset()));
			break;
		}
	}

	const int32 Count = Bps.Num();

	if (Count > 1)
	{
		UE_LOG(LogCs, Warning, TEXT("ACsData::GetDataMapping (%s): More than one asset named %s"), *(ShortCode.ToString()), *DataMappingName);

		for (int32 I = 0; I < Count; I++)
		{
			UE_LOG(LogCs, Warning, TEXT("ACsData::GetDataMapping (%s): Asset at %s"), *(ShortCode.ToString()), *(Bps[I]->GetPathName()));
		}
	}
	else
	{
		if (ACsDataMapping* DataMapping = Cast<UBlueprintCore>(Bps[0])->GeneratedClass->GetDefaultObject<ACsDataMapping>())
		{
			return DataMapping;
		}
		else
		{
			UE_LOG(LogCs, Warning, TEXT("ACsData::GetDataMapping (%s): Asset: %s is NOT of type CsDataMapping."), *(ShortCode.ToString()), *DataMappingName);
		}
	}
	return nullptr;
}

ACsData_Payload* ACsData::GetPayload()
{
	TArray<UBlueprint*> Bps;

	UCsCommon::GetAssets<UBlueprint>(Bps, FName(*PayloadName));

	const int32 Count = Bps.Num();

	if (Count > 1)
	{
		UE_LOG(LogCs, Warning, TEXT("ACsData::GetPayload (%s): More than one asset named %s"), *(ShortCode.ToString()), *PayloadName);

		for (int32 I = 0; I < Count; I++)
		{
			UE_LOG(LogCs, Warning, TEXT("ACsData::GetPayload (%s): Asset at %s"), *(ShortCode.ToString()), *(Bps[I]->GetPathName()));
		}
	}
	else
	{
		if (ACsData_Payload* Payload = Cast<UBlueprintCore>(Bps[0])->GeneratedClass->GetDefaultObject<ACsData_Payload>())
		{
			return Payload;
		}
		else
		{
			UE_LOG(LogCs, Warning, TEXT("ACsData::GetPayload (%s): Asset: %s is NOT of type CsData_Payload."), *(ShortCode.ToString()), *PayloadName);
		}
	}
	return nullptr;
}

void ACsData::PostEditChangeProperty(struct FPropertyChangedEvent& e)
{
	FName PropertyName = (e.Property != NULL) ? e.Property->GetFName() : NAME_None;

	// Add to DataMapping
	if (PropertyName == GET_MEMBER_NAME_CHECKED(FCsDataAddToDataMapping, Add))
	{
		if (Type == Type_MAX)
		{
			AddToDataMapping.Add = false;
			Super::PostEditChangeProperty(e);
			return;
		}

		ACsDataMapping* DataMapping = GetDataMapping();

		DataMapping->PerformAddEntry(ShortCode, Type, AddToDataMapping.LoadFlags, AddToDataMapping.Message, AddToDataMapping.Output);
	
		AddToDataMapping.Add = false;
	}
	// Add to Payload

	// Load From Json
	if (PropertyName == GET_MEMBER_NAME_CHECKED(FCsDataLoadFromJson, Load))
	{
		if (GetName().StartsWith(TEXT("Default__")))
			LoadFromJson();

		PerformLoadFromJson.Load = false;
	}
	Super::PostEditChangeProperty(e);
}

#endif // #if WITH_EDITOR

#pragma endregion 99 Data Mapping