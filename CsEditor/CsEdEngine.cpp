// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "CsEdEngine.h"
#include "CsEditor.h"

#include "Common/CsCommon_Asset.h"

// Asset Registry
#include "AssetRegistryModule.h"
#include "Developer/AssetTools/Public/AssetToolsModule.h"
#include "Editor/ContentBrowser/Public/ContentBrowserModule.h"

#include "Classes/Factories/BlueprintFactory.h"
// Data
#include "Data/CsData.h"

DECLARE_LOG_CATEGORY_CLASS(LogCsEditor, Log, All);

void UCsEdEngine::Init(IEngineLoop* InEngineLoop)
{
	Super::Init(InEngineLoop);
}

bool UCsEdEngine::Exec(UWorld* InWorld, const TCHAR* Stream, FOutputDevice& Ar)
{
	if (Super::Exec(InWorld, Stream, Ar))
		return true;

	// Data
	{
		if (Check_MarkAllDatasDirty(Stream))
			return true;
	}
	return true;
}

// Data
#pragma region

bool UCsEdEngine::Check_MarkAllDatasDirty(const TCHAR* Stream)
{
	const FString Command	 = TEXT("MarkAllDatasDirty");
	const FString Parameters = TEXT("");
	const FString Format	 = Command + TEXT(" ") + Parameters;

	if (FParse::Command(&Stream, *Command))
	{
		MarkAllDatasDirty();
		return true;
	}
	return false;
}

void UCsEdEngine::MarkAllDatasDirty()
{
	IAssetRegistry& AssetRegistry = UCsCommon_Asset::GetAssetRegistry();

	TArray<FAssetData> OutAssetDatas;

	AssetRegistry.GetAssetsByClass(UBlueprint::StaticClass()->GetFName(), OutAssetDatas);

	const int32 AssetCount = OutAssetDatas.Num();

	for (int32 I = 0; I < AssetCount; ++I)
	{
		const FString Name = OutAssetDatas[I].AssetName.ToString();

		if (!Name.StartsWith(TEXT("bp")))
			continue;

		if (UBlueprint* Bp = Cast<UBlueprint>(OutAssetDatas[I].GetAsset()))
		{
			UBlueprintCore* BpC = Cast<UBlueprintCore>(Bp);

			if (!BpC)
				continue;
			if (!BpC->GeneratedClass)
				continue;

			if (ACsData* Data = BpC->GeneratedClass->GetDefaultObject<ACsData>())
			{
				Data->MarkPackageDirty();

				const FString Path		  = OutAssetDatas[I].PackagePath.ToString();
				const FString NameAndPath = Path + Name;

				UE_LOG(LogCsEditor, Log, TEXT("MarkAllDatasDirty: %s is marked DIRTY."), *NameAndPath);
			}
		}
	}
}

#pragma endregion Data