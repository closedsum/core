// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Data/CsData_Impl.h"
#include "CsCore.h"
#include "CsCVars.h"

// Library
#include "Library/CsLibrary_Load.h"
#include "Library/CsLibrary_Asset.h"
#include "Library/CsLibrary_Common.h"

#if WITH_EDITOR
#include "Data/CsDataMapping.h"
#include "Data/CsData_Payload.h"

#include "AssetRegistryModule.h"
#include "Developer/AssetTools/Public/AssetToolsModule.h"
#include "Editor/ContentBrowser/Public/ContentBrowserModule.h"
#include "Developer/SourceControl/Public/SourceControlHelpers.h"
#endif WITH_EDITOR

UCsData_Impl::UCsData_Impl(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	GetAssetReferencesFromObject_Internal = nullptr;
	LoadObjectWithTSoftObjectPtrs_Internal = nullptr;
	WriteObjectToJson_Internal = nullptr;
	ReadObjectFromJson_Internal = nullptr;

	DataMappingName = TEXT("bp_data_mapping");
	PayloadName		= TEXT("bp_payload");

#if WITH_EDITOR
	DataMappingClass = UCsDataMapping::StaticClass();
#endif // #if WITH_EDITOR
}

void UCsData_Impl::PostLoad()
{
	Super::PostLoad();

	ShortCodeAsString = ShortCode.ToString();

#if WITH_EDITOR
	if (UCsLibrary_Common::IsAnyWorldContextEditorOrEditorPreview())
	{
		VerifyJsonIntegrity();
	}
#endif WITH_EDITOR
	LoadFromJson();
}

void UCsData_Impl::PreSave(const class ITargetPlatform* TargetPlatform)
{
	Super::PreSave(TargetPlatform);

#if WITH_EDITOR
	OnPreSave();
	PopulateAssetReferences(true);
	UCsLibrary_Load::GetCategoryMemberAssociations(this, GetClass(), CategoryMemberAssociations);
	SaveToJson();
#endif WITH_EDITOR
}

#if WITH_EDITOR
void UCsData_Impl::OnPreSave(){}
#endif WITH_EDITOR

bool UCsData_Impl::IsValid(const ECsLoadFlags& LoadFlags /*=ECsLoadFlags::All*/)
{
	bool Pass = true;
	const FString AssetName = GetName();

	if (ShortCode == CS_INVALID_SHORT_CODE || ShortCode == NAME_None)
	{
		UE_LOG(LogCs, Warning, TEXT("UCsData_Impl::IsValid (%s): No ShortCode was set"), *AssetName);
		Pass = false;
	}

	ShortCodeAsString = ShortCode.ToString();

	if (Name == CS_INVALID_SHORT_CODE || Name == NAME_None)
	{
		UE_LOG(LogCs, Warning, TEXT("UCsData_Impl::IsValid (%s): No Name was set"), *AssetName);
	}
	return Pass;
}

void UCsData_Impl::PopulateAssetReferences(const bool& CalculateResourceSizes)
{
	const int32 Count = ECsLoadFlags_Editor::ECsLoadFlags_Editor_MAX;

	for (int32 I = 0; I < Count; ++I)
	{
		AssetReferences[I].References.Reset();

		int32 LoadCodes = 0;

		if (CalculateResourceSizes)
			CS_SET_BLUEPRINT_BITFLAG(LoadCodes, ECsLoadCode::CalculateResourceSizes);
		if (I == Count - 1)
			CS_SET_BLUEPRINT_BITFLAG(LoadCodes, ECsLoadCode::SuppressLoadFlagsAllWarning);

		UCsLibrary_Load::GetAssetReferencesFromObject(this, GetClass(), (ECsLoadFlags)I, AssetReferences[I].References, GetAssetReferencesFromObject_Internal, LoadCodes);
		
		AssetReferences[I].CalculateSize();
	}
}

#if WITH_EDITOR

void UCsData_Impl::VerifyJsonIntegrity()
{
	const FString AssetName = GetName();

	// Get Latest CategoryMemberAssociations. Check for changes do to Code updates
	TArray<FCsCategoryMemberAssociation> LatestCategoryMemberAssociations;

	UCsLibrary_Load::GetCategoryMemberAssociations(this, GetClass(), LatestCategoryMemberAssociations);

	// Check for change in number of categories
	const int32 LatestCount  = LatestCategoryMemberAssociations.Num();
	const int32 CurrentCount = CategoryMemberAssociations.Num();

	if (LatestCount != CurrentCount)
	{
		UE_LOG(LogCs, Warning, TEXT("UCsData_Impl::VerifyJsonIntegrity (%s): Change in category count %d -> %d. Regenerating Json."), *AssetName, CurrentCount, LatestCount);

		CategoryMemberAssociations.Reset();

		for (int32 I = 0; I < LatestCount; ++I)
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
	for (int32 I = 0; I < CurrentCount; ++I)
	{
		// Change in category name
		const FString LatestCategory  = LatestCategoryMemberAssociations[I].Category;
		const FString CurrentCategory = CategoryMemberAssociations[I].Category;

		if (LatestCategory != CurrentCategory)
		{
			RegenerateJson |= true;

			UE_LOG(LogCs, Warning, TEXT("UCsData_Impl::VerifyJsonIntegrity (%s): Change in category name %s -> %s. Regenerating Json."), *AssetName, *CurrentCategory, *LatestCategory);
			continue;
		}

		const int32 LatestMemberCount  = LatestCategoryMemberAssociations[I].Members.Num();
		const int32 CurrentMemberCount = CategoryMemberAssociations[I].Members.Num();
		// Change in number of members for a category
		if (LatestMemberCount != CurrentMemberCount)
		{
			RegenerateJson |= true;

			UE_LOG(LogCs, Warning, TEXT("UCsData_Impl::VerifyJsonIntegrity (%s): Change in category (%s) member count %d -> %d. Regenerating Json."), *AssetName, *CurrentCategory, CurrentMemberCount, LatestMemberCount);
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

				UE_LOG(LogCs, Warning, TEXT("UCsData_Impl::VerifyJsonIntegrity (%s): Change in category (%s) member name %s -> %s. Regenerating Json."), *AssetName, *CurrentCategory, *CurrentMember, *LatestMember);
			}
		}
	}

	if (RegenerateJson)
	{
		CategoryMemberAssociations.Reset();

		for (int32 I = 0; I < LatestCount; ++I)
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

void UCsData_Impl::Load(const ECsLoadFlags& LoadFlags /*=ECsLoadFlags::All*/)
{
	ShortCodeAsString = ShortCode.ToString();

	if (!HasLoadedFromJson)
		LoadFromJson();

	UCsLibrary_Load::LoadObjectWithTSoftObjectPtrs(ShortCodeAsString, (void*)this, GetClass(), LoadFlags, LoadObjectWithTSoftObjectPtrs_Internal);
}

void UCsData_Impl::UnLoad()
{
	UCsLibrary_Load::UnLoadObjectWithTSoftObjectPtrs((void*)this, GetClass());
}

bool UCsData_Impl::IsLoaded()
{
	const FString DataName = ShortCode.ToString();

	return UCsLibrary_Load::IsLoadedObjectWithTSoftObjectPtrs(DataName, (void*)this, GetClass());
}

FString UCsData_Impl::GetAbsolutePath()
{
	const FString AssetName	   = ShortCode.ToString() + TEXT(".");
	const FString InternalName = GetName();
	FString PathName		   = GetPathName();

	PathName = PathName.Replace(*InternalName, TEXT(""));
	PathName = PathName.Replace(*AssetName, TEXT(""));
	PathName = PathName.Replace(TEXT("/Game/"), TEXT(""));

	const FString ProjectContentDir = FPaths::ConvertRelativePathToFull(FPaths::ProjectContentDir());
	const FString JsonDir		    = TEXT("Json/");
	return ProjectContentDir + JsonDir + PathName;
}

void UCsData_Impl::SaveToJson()
{
	FString OutputString;
	TSharedRef<TJsonWriter<TCHAR>> JsonWriter = TJsonWriterFactory<>::Create(&OutputString);

	JsonWriter->WriteObjectStart();

	UCsLibrary_Load::WriteObjectToJson(JsonWriter, (void*)this, GetClass(), CategoryMemberAssociations, WriteObjectToJson_Internal);
	
	JsonWriter->WriteObjectEnd();

	JsonWriter->Close();

	const FString Filename = GetAbsolutePath() + ShortCode.ToString() + TEXT(".json");
	
	FFileHelper::SaveStringToFile(OutputString, *Filename);

#if WITH_EDITOR
	FText ErrorMessage;

	SourceControlHelpers::CheckoutOrMarkForAdd(Filename, FText::FromString(Filename), NULL, ErrorMessage);
#endif // #if WITH_EDITOR
}

void UCsData_Impl::LoadFromJson()
{
	const FString AssetName = GetName();
	const FString Filename  = GetAbsolutePath() + ShortCode.ToString() + TEXT(".json");

	if (CsCVarLogJsonDataFilenames->GetInt() == CS_CVAR_SHOW_LOG)
		UE_LOG(LogCs, Warning, TEXT("UCsData_Impl::LoadFromJson (%s): Filename: %s"), *AssetName, *Filename);

	FString DataJson;

	if (FFileHelper::LoadFileToString(DataJson, *Filename))
	{
		TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(DataJson);

		TSharedPtr<FJsonObject> JsonParsed;

		if (FJsonSerializer::Deserialize(JsonReader, JsonParsed) && JsonParsed.IsValid())
		{
			if (CategoryMemberAssociations.Num() == 0)
			{
				UE_LOG(LogCs, Warning, TEXT("UCsData_Impl::LoadFromJson (%s): Data needs to be saved at least ONCE to generate CategoryMemberAssociations"), *AssetName);
				return;
			}
#if WITH_EDITOR
			VerifyJsonIntegrity();
#endif // #if WITH_EDITOR
			UCsLibrary_Load::ReadObjectFromJson(JsonParsed, this, GetClass(), CategoryMemberAssociations, ReadObjectFromJson_Internal);
		}
		else
		{
			UE_LOG(LogCs, Warning, TEXT("UCsData_Impl::LoadFromJson (%s): %s is NOT Valid"), *AssetName, *Filename);
			return;
		}
	}
	else
	{
		UE_LOG(LogCs, Warning, TEXT("UCsData_Impl::LoadFromJson (%s): %s NOT found"), *AssetName, *Filename);
		return;
	}
	HasLoadedFromJson = true;
}

// 99 Data Mapping
#pragma region

#if WITH_EDITOR

UCsDataMapping* UCsData_Impl::GetDataMapping()
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
		UE_LOG(LogCs, Warning, TEXT("UCsData_Impl::GetDataMapping (%s): More than one asset named %s"), *(ShortCode.ToString()), *DataMappingName);

		for (int32 I = 0; I < Count; ++I)
		{
			UE_LOG(LogCs, Warning, TEXT("UCsData_Impl::GetDataMapping (%s): Asset at %s"), *(ShortCode.ToString()), *(Bps[I]->GetPathName()));
		}
		return nullptr;
	}

	if (Count == CS_EMPTY)
	{
		UE_LOG(LogCs, Warning, TEXT("UCsData_Impl::GetDataMapping (%s): Failed to find Data Mapping named %s"), *(ShortCode.ToString()), *DataMappingName);
		return nullptr;
	}

	if (UCsDataMapping* DataMapping = Cast<UBlueprintCore>(Bps[0])->GeneratedClass->GetDefaultObject<UCsDataMapping>())
	{
		return DataMapping;
	}

	UE_LOG(LogCs, Warning, TEXT("UCsData_Impl::GetDataMapping (%s): Asset: %s is NOT of type CsDataMapping."), *(ShortCode.ToString()), *DataMappingName);
	return nullptr;
}

UCsData_Payload* UCsData_Impl::GetPayload()
{
	TArray<UBlueprint*> Bps;

	UCsLibrary_Asset::GetAssets<UBlueprint>(PayloadName, ECsStringCompare::Equals, Bps);

	const int32 Count = Bps.Num();

	if (Count > 1)
	{
		UE_LOG(LogCs, Warning, TEXT("UCsData_Impl::GetPayload (%s): More than one asset named %s"), *(ShortCode.ToString()), *PayloadName);

		for (int32 I = 0; I < Count; ++I)
		{
			UE_LOG(LogCs, Warning, TEXT("UCsData_Impl::GetPayload (%s): Asset at %s"), *(ShortCode.ToString()), *(Bps[I]->GetPathName()));
		}
	}

	if (Count == CS_EMPTY)
	{
		UE_LOG(LogCs, Warning, TEXT("UCsData_Impl::GetPayload (%s): Failed to find Payload named %s"), *(ShortCode.ToString()), *PayloadName);
		return nullptr;
	}

	if (UCsData_Payload* Payload = Cast<UBlueprintCore>(Bps[0])->GeneratedClass->GetDefaultObject<UCsData_Payload>())
	{
		return Payload;
	}

	UE_LOG(LogCs, Warning, TEXT("UCsData_Impl::GetPayload (%s): Asset: %s is NOT of type CsData_Payload."), *(ShortCode.ToString()), *PayloadName);
	return nullptr;
}

void UCsData_Impl::PostEditChangeProperty(struct FPropertyChangedEvent& e)
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

		if (!EMCsDataType::Get().IsValidEnum(Type))
		{
			AddToDataMapping.Message = TEXT("INVALID Type.");
			AddToDataMapping.Output  = TEXT("ERROR");

			if (UCsLibrary_Common::IsDefaultObject(this))
			{
				UCsLibrary_Common::DisplayNotificationInfo(AddToDataMapping.Output, TEXT("Data"), TEXT("AddToDataMappingOutput"), 5.0f);
				UCsLibrary_Common::DisplayNotificationInfo(AddToDataMapping.Message, TEXT("DataMapping"), TEXT("AddToDataMappingMessage"), 5.0f);
			}

			AddToDataMapping.AddToDataMapping = false;
			Super::PostEditChangeProperty(e);
			return;
		}

		UCsDataMapping* DataMapping = GetDataMapping();

		DataMapping->PerformAddEntry(ShortCode, Type, AddToDataMapping.LoadFlags, AddToDataMapping.Message, AddToDataMapping.Output);
		DataMapping->GenerateMaps();

		if (UCsLibrary_Common::IsDefaultObject(this))
		{
			UCsLibrary_Common::DisplayNotificationInfo(AddToDataMapping.Output, TEXT("Data"), TEXT("AddToDataMappingOutput"), 5.0f);
			UCsLibrary_Common::DisplayNotificationInfo(AddToDataMapping.Message, TEXT("Data"), TEXT("AddToDataMappingMessage"), 5.0f);
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

		if (!EMCsDataType::Get().IsValidEnum(Type))
		{
			AddToPayload.Message = TEXT("INVALID Type.");
			AddToPayload.Output = TEXT("ERROR");

			if (UCsLibrary_Common::IsDefaultObject(this))
			{
				UCsLibrary_Common::DisplayNotificationInfo(AddToPayload.Output, TEXT("Data"), TEXT("AddToPayloadOutput"), 5.0f);
				UCsLibrary_Common::DisplayNotificationInfo(AddToPayload.Message, TEXT("Data"), TEXT("AddToPayloadMessage"), 5.0f);
			}

			AddToPayload.AddToPayload = false;
			Super::PostEditChangeProperty(e);
			return;
		}

		UCsData_Payload* Payload = GetPayload();

		Payload->PerformAddEntry(ShortCode, AddToPayload.LoadAssetsType, AddToPayload.LoadFlags, AddToPayload.Message, AddToPayload.Output);

		if (UCsLibrary_Common::IsDefaultObject(this))
		{
			UCsLibrary_Common::DisplayNotificationInfo(AddToPayload.Output, TEXT("Data"), TEXT("AddToPayloadOutput"), 5.0f);
			UCsLibrary_Common::DisplayNotificationInfo(AddToPayload.Message, TEXT("Data"), TEXT("AddToPayloadMessage"), 5.0f);
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

		if (UCsLibrary_Common::IsDefaultObject(this))
		{
			LoadFromJson();
			UCsLibrary_Common::DisplayNotificationInfo(TEXT("COMPLETE"), TEXT("Data"), TEXT("LoadFromJsonMessage"), 5.0f);
		}

		PerformLoadFromJson.Load = false;
	}
	Super::PostEditChangeProperty(e);
}

#endif // #if WITH_EDITOR

#pragma endregion 99 Data Mapping