// Copyright 2017 Closed Sum Games, LLC. All Rights Reserved.
#include "Data/CsData.h"
#include "CsCore.h"
#include "CsCVars.h"
#include "Common/CsCommon_Load.h"
#include "Common/CsCommon_Asset.h"
#include "Common/CsCommon.h"

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
	PayloadName		= TEXT("bp_payload");

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
	UCsCommon_Load::GetCategoryMemberAssociations(this, GetClass(), CategoryMemberAssociations);
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

		int32 LoadCodes = 0;

		if (CalculateResourceSizes)
			CS_SET_BLUEPRINT_BITFLAG(LoadCodes, ECsLoadCode::CalculateResourceSizes);
		if (I == Count - 1)
			CS_SET_BLUEPRINT_BITFLAG(LoadCodes, ECsLoadCode::SuppressLoadFlagsAllWarning);

		UCsCommon_Load::GetAssetReferencesFromObject(this, GetClass(), (ECsLoadFlags)I, AssetReferences[I].References, GetAssetReferencesFromObject_Internal, LoadCodes);
		
		AssetReferences[I].CalculateSize();
	}
}

#if WITH_EDITOR

void ACsData::VerifyJsonIntegrity()
{
	const FString AssetName = GetName();

	// Get Latest CategoryMemberAssociations. Check for changes do to Code updates
	TArray<FCsCategoryMemberAssociation> LatestCategoryMemberAssociations;

	UCsCommon_Load::GetCategoryMemberAssociations(this, GetClass(), LatestCategoryMemberAssociations);

	// Check for change in number of categories
	const int32 LatestCount  = LatestCategoryMemberAssociations.Num();
	const int32 CurrentCount = CategoryMemberAssociations.Num();

	if (LatestCount != CurrentCount)
	{
		UE_LOG(LogCs, Warning, TEXT("ACsData::VerifyJsonIntegrity (%s): Change in category count %d -> %d. Regenerating Json."), *AssetName, CurrentCount, LatestCount);

		CategoryMemberAssociations.Reset();

		for (int32 I = 0; I < LatestCount; I++)
		{
			CategoryMemberAssociations.AddDefaulted();

			CategoryMemberAssociations[I].Category = LatestCategoryMemberAssociations[I].Category;

			const int32 LatestMemberCount = LatestCategoryMemberAssociations[I].Members.Num();

			for (int32 J = 0; J < LatestMemberCount; J++)
			{
				CategoryMemberAssociations[I].Members.AddDefaulted();
				CategoryMemberAssociations[I].Members[J] = LatestCategoryMemberAssociations[I].Members[J];
			}
		}
		SaveToJson();
		return;
	}

	bool RegenerateJson = false;

	// Check for change in categories names, number of members, or member names
	for (int32 I = 0; I < CurrentCount; I++)
	{
		// Change in category name
		const FString LatestCategory  = LatestCategoryMemberAssociations[I].Category;
		const FString CurrentCategory = CategoryMemberAssociations[I].Category;

		if (LatestCategory != CurrentCategory)
		{
			RegenerateJson |= true;

			UE_LOG(LogCs, Warning, TEXT("ACsData::VerifyJsonIntegrity (%s): Change in category name %s -> %s. Regenerating Json."), *AssetName, *CurrentCategory, *LatestCategory);
			continue;
		}

		const int32 LatestMemberCount  = LatestCategoryMemberAssociations[I].Members.Num();
		const int32 CurrentMemberCount = CategoryMemberAssociations[I].Members.Num();
		// Change in number of members for a category
		if (LatestMemberCount != CurrentMemberCount)
		{
			RegenerateJson |= true;

			UE_LOG(LogCs, Warning, TEXT("ACsData::VerifyJsonIntegrity (%s): Change in category (%s) member count %d -> %d. Regenerating Json."), *AssetName, *CurrentCategory, CurrentMemberCount, LatestMemberCount);
			continue;
		}
		
		for (int32 J = 0; J < CurrentMemberCount; J++)
		{
			// Change in member name
			const FString LatestMember  = LatestCategoryMemberAssociations[I].Members[J];
			const FString CurrentMember = CategoryMemberAssociations[I].Members[J];

			if (LatestCategory != CurrentCategory)
			{
				RegenerateJson |= true;

				UE_LOG(LogCs, Warning, TEXT("ACsData::VerifyJsonIntegrity (%s): Change in category (%s) member name %s -> %s. Regenerating Json."), *AssetName, *CurrentCategory, *CurrentMember, *LatestMember);
			}
		}
	}

	if (RegenerateJson)
	{
		CategoryMemberAssociations.Reset();

		for (int32 I = 0; I < LatestCount; I++)
		{
			CategoryMemberAssociations.AddDefaulted();

			CategoryMemberAssociations[I].Category = LatestCategoryMemberAssociations[I].Category;

			const int32 LatestMemberCount = LatestCategoryMemberAssociations[I].Members.Num();

			for (int32 J = 0; J < LatestMemberCount; J++)
			{
				CategoryMemberAssociations[I].Members.AddDefaulted();
				CategoryMemberAssociations[I].Members[J] = LatestCategoryMemberAssociations[I].Members[J];
			}
		}
		SaveToJson();
	}
}

#endif // #if WITH_EDITOR

void ACsData::Load(const ECsLoadFlags &LoadFlags /*=ECsLoadFlags::All*/)
{
	const FString DataName = ShortCode.ToString();

	if (!HasLoadedFromJson)
		LoadFromJson();

	UCsCommon_Load::LoadObjectWithTAssetPtrs(DataName, (void*)this, GetClass(), LoadFlags, LoadObjectWithTAssetPtrs_Internal);
}

void ACsData::UnLoad()
{
	UCsCommon_Load::UnLoadObjectWithTAssetPtrs((void*)this, GetClass());
}

bool ACsData::IsLoaded()
{
	const FString DataName = ShortCode.ToString();

	return UCsCommon_Load::IsLoadedObjectWithTAssetPtrs(DataName, (void*)this, GetClass());
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

	UCsCommon_Load::WriteObjectToJson(JsonWriter, (void*)this, GetClass(), CategoryMemberAssociations, WriteObjectToJson_Internal);
	
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
#if WITH_EDITOR
			VerifyJsonIntegrity();
#endif // #if WITH_EDITOR
			UCsCommon_Load::ReadObjectFromJson(JsonParsed, this, GetClass(), CategoryMemberAssociations, ReadObjectFromJson_Internal);
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
		return nullptr;
	}

	if (Count == CS_EMPTY)
	{
		UE_LOG(LogCs, Warning, TEXT("ACsData::GetDataMapping (%s): Failed to find Data Mapping named %s"), *(ShortCode.ToString()), *DataMappingName);
		return nullptr;
	}

	if (ACsDataMapping* DataMapping = Cast<UBlueprintCore>(Bps[0])->GeneratedClass->GetDefaultObject<ACsDataMapping>())
	{
		return DataMapping;
	}

	UE_LOG(LogCs, Warning, TEXT("ACsData::GetDataMapping (%s): Asset: %s is NOT of type CsDataMapping."), *(ShortCode.ToString()), *DataMappingName);
	return nullptr;
}

ACsData_Payload* ACsData::GetPayload()
{
	TArray<UBlueprint*> Bps;

	UCsCommon_Asset::GetAssets<UBlueprint>(FName(*PayloadName), Bps);

	const int32 Count = Bps.Num();

	if (Count > 1)
	{
		UE_LOG(LogCs, Warning, TEXT("ACsData::GetPayload (%s): More than one asset named %s"), *(ShortCode.ToString()), *PayloadName);

		for (int32 I = 0; I < Count; I++)
		{
			UE_LOG(LogCs, Warning, TEXT("ACsData::GetPayload (%s): Asset at %s"), *(ShortCode.ToString()), *(Bps[I]->GetPathName()));
		}
	}

	if (Count == CS_EMPTY)
	{
		UE_LOG(LogCs, Warning, TEXT("ACsData::GetPayload (%s): Failed to find Payload named %s"), *(ShortCode.ToString()), *PayloadName);
		return nullptr;
	}

	if (ACsData_Payload* Payload = Cast<UBlueprintCore>(Bps[0])->GeneratedClass->GetDefaultObject<ACsData_Payload>())
	{
		return Payload;
	}

	UE_LOG(LogCs, Warning, TEXT("ACsData::GetPayload (%s): Asset: %s is NOT of type CsData_Payload."), *(ShortCode.ToString()), *PayloadName);
	return nullptr;
}

void ACsData::PostEditChangeProperty(struct FPropertyChangedEvent& e)
{
	FName PropertyName = (e.Property != NULL) ? e.Property->GetFName() : NAME_None;

	// Add to DataMapping
	if (PropertyName == GET_MEMBER_NAME_CHECKED(FCsDataAddToDataMapping, AddToDataMapping))
	{
		if (!AddToDataMapping.AddToDataMapping)
		{
			Super::PostEditChangeProperty(e);
			return;
		}

		AddToDataMapping.Message = TEXT("");
		AddToDataMapping.Output  = TEXT("");

		if (Type == Type_MAX)
		{
			AddToDataMapping.Message = TEXT("INVALID Type.");
			AddToDataMapping.Output  = TEXT("ERROR");

			if (UCsCommon::IsDefaultObject(this))
			{
				UCsCommon::DisplayNotificationInfo(AddToDataMapping.Output, TEXT("Data"), TEXT("AddToDataMappingOutput"), 5.0f);
				UCsCommon::DisplayNotificationInfo(AddToDataMapping.Message, TEXT("DataMapping"), TEXT("AddToDataMappingMessage"), 5.0f);
			}

			AddToDataMapping.AddToDataMapping = false;
			Super::PostEditChangeProperty(e);
			return;
		}

		ACsDataMapping* DataMapping = GetDataMapping();

		DataMapping->PerformAddEntry(ShortCode, Type, AddToDataMapping.LoadFlags, AddToDataMapping.Message, AddToDataMapping.Output);
	
		if (UCsCommon::IsDefaultObject(this))
		{
			UCsCommon::DisplayNotificationInfo(AddToDataMapping.Output, TEXT("Data"), TEXT("AddToDataMappingOutput"), 5.0f);
			UCsCommon::DisplayNotificationInfo(AddToDataMapping.Message, TEXT("Data"), TEXT("AddToDataMappingMessage"), 5.0f);
		}
		AddToDataMapping.AddToDataMapping = false;
	}
	// Add to Payload
	if (PropertyName == GET_MEMBER_NAME_CHECKED(FCsDataAddToPayload, AddToPayload))
	{
		if (!AddToPayload.AddToPayload)
		{
			Super::PostEditChangeProperty(e);
			return;
		}

		AddToPayload.Message = TEXT("");
		AddToPayload.Output  = TEXT("");

		if (Type == Type_MAX)
		{
			AddToPayload.Message = TEXT("INVALID Type.");
			AddToPayload.Output = TEXT("ERROR");

			if (UCsCommon::IsDefaultObject(this))
			{
				UCsCommon::DisplayNotificationInfo(AddToPayload.Output, TEXT("Data"), TEXT("AddToPayloadOutput"), 5.0f);
				UCsCommon::DisplayNotificationInfo(AddToPayload.Message, TEXT("Data"), TEXT("AddToPayloadMessage"), 5.0f);
			}

			AddToPayload.AddToPayload = false;
			Super::PostEditChangeProperty(e);
			return;
		}

		ACsData_Payload* Payload = GetPayload();

		Payload->PerformAddEntry(ShortCode, (*StringToLoadAssetsType)(AddToPayload.LoadAssetsType), AddToPayload.LoadFlags, AddToPayload.Message, AddToPayload.Output);

		if (UCsCommon::IsDefaultObject(this))
		{
			UCsCommon::DisplayNotificationInfo(AddToPayload.Output, TEXT("Data"), TEXT("AddToPayloadOutput"), 5.0f);
			UCsCommon::DisplayNotificationInfo(AddToPayload.Message, TEXT("Data"), TEXT("AddToPayloadMessage"), 5.0f);
		}
		AddToPayload.AddToPayload = false;
	}
	// Load From Json
	if (PropertyName == GET_MEMBER_NAME_CHECKED(FCsDataLoadFromJson, Load))
	{
		if (!PerformLoadFromJson.Load)
		{
			Super::PostEditChangeProperty(e);
			return;
		}

		if (UCsCommon::IsDefaultObject(this))
		{
			LoadFromJson();
			UCsCommon::DisplayNotificationInfo(TEXT("COMPLETE"), TEXT("Data"), TEXT("LoadFromJsonMessage"), 5.0f);
		}

		PerformLoadFromJson.Load = false;
	}
	Super::PostEditChangeProperty(e);
}

#endif // #if WITH_EDITOR

#pragma endregion 99 Data Mapping