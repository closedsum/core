// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Level/CsLevelScriptActor.h"
#include "CsCore.h"
#include "CsCVars.h"

// Library
#include "Library/Load/CsLibrary_Load.h"
// Managers
#include "Managers/Data/CsManager_Data.h"
// Settings
#include "Settings/CsDeveloperSettings.h"
// Data
#include "Data/CsDataRootSet.h"

#if WITH_EDITOR
#include "Engine/World.h"
#endif // #if WITH_EDITOR

// Cached
#pragma region

namespace NCsLevelScriptActorCached
{
	namespace Str
	{
		const FString PopulatePayloadLevels = TEXT("ACsLevelScriptActor::PopulatePayloadLevels");
	}
}

#pragma endregion Cached

ACsLevelScriptActor::ACsLevelScriptActor(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

// UObject Interface
#pragma region

void ACsLevelScriptActor::PreSave(const ITargetPlatform* TargetPlatform)
{
	Super::PreSave(TargetPlatform);

#if WITH_EDITOR
	SetupOnSubLevelSavedDelegate();
	PopulatePayloadLevels();
	PopulatePayloadCombined();
#endif // #if WITH_EDITOR
 }

void ACsLevelScriptActor::PostLoad()
{
	Super::PostLoad();

#if WITH_EDITOR
	SetupOnSubLevelSavedDelegate();
#endif // #if WITH_EDITOR
}

void ACsLevelScriptActor::BeginDestroy()
{
	Super::BeginDestroy();

#if WITH_EDITOR
	// Get Default Object
	ACsLevelScriptActor* DOb = GetClass()->GetDefaultObject<ACsLevelScriptActor>();

	// Remove delegate to listen for Sub-Levels being saved
	if (FCoreUObjectDelegates::OnObjectSaved.IsBoundToObject(DOb) &&
		DOb->OnSubLevelSavedHandle.IsValid())
	{
		FCoreUObjectDelegates::OnObjectSaved.Remove(DOb->OnSubLevelSavedHandle);

		DOb->OnSubLevelSavedHandle.Reset();
	}
#endif // #if WITH_EDITOR
}

#pragma endregion UObject Interface

// AActor Interface
#pragma region

void ACsLevelScriptActor::PostInitializeComponents()
{
	Super::PostInitializeComponents();

#if WITH_EDITOR
	UWorld* World = GetWorld();

	// For Test Levels, force load the Payloads

	// NOTE: If Editor world is needed, some work is needed to properly
	//		 setup UCsManager_Data

	if (bTest &&
		World &&
		World->IsPlayInEditor())
	{
		UCsManager_Data* Manager_Data = UCsManager_Data::Get(World->GetGameInstance());

		const FName LevelName = World->GetFName();

		Manager_Data->AddPayload(LevelName, Payload_Combined);
		Manager_Data->LoadPayload(LevelName);
	}
#endif // #if WITH_EDITOR
}

void ACsLevelScriptActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

#pragma endregion AActor Interface

// Level
#pragma region

const FString ACsLevelScriptActor::GetLevelName()
{
	ACsLevelScriptActor* DOb = GetClass()->GetDefaultObject<ACsLevelScriptActor>();
	FString Name = DOb->GetName();
	Name.RemoveFromStart(TEXT("Default__"));
	Name.RemoveFromEnd(TEXT("_C"));
	
	return Name;
}

const FName ACsLevelScriptActor::GetLevelFName()
{
	return FName(*GetLevelName());
}

#pragma endregion Level

// SubLevel
#pragma region

#if WITH_EDITOR

void ACsLevelScriptActor::SetupOnSubLevelSavedDelegate()
{
	// Get Default Object
	ACsLevelScriptActor* DOb = GetClass()->GetDefaultObject<ACsLevelScriptActor>();

	// Bind delegate to listen for Sub-Levels being saved
	if (!FCoreUObjectDelegates::OnObjectSaved.IsBoundToObject(DOb))
	{
		OnSubLevelSavedHandle = FCoreUObjectDelegates::OnObjectSaved.AddUObject(DOb, &ACsLevelScriptActor::OnSubLevelSaved);
	}
}

void ACsLevelScriptActor::OnSubLevelSaved(UObject* Object)
{
	if (ULevel* Level = Cast<ULevel>(Object))
	{
		if (Level->OwningWorld)
		{
			const FName SubLevelName = Level->OwningWorld->GetFName();
			const int32 Index		 = SubLevelNames.Find(SubLevelName);

			if (Index != INDEX_NONE)
			{
				PopulatePayload(Level);
				PopulatePayloadCombined();
			}
		}
	}
}

#endif // #if WITH_EDITOR

#pragma endregion SubLevel

// Payload
#pragma region

#if WITH_EDITOR

void ACsLevelScriptActor::PopulatePayload(ULevel* Level)
{
	UWorld* LevelWorld	  = Cast<UWorld>(Level->GetOuter());
	const FName LevelName = LevelWorld->GetFName();

	FCsPayload& Payload_Level = Payload_Levels.FindOrAdd(LevelName);
	// NOTE: For now, just get Objects that implement IData and DataTable
	//		 It's a bit more difficult to manage arbitrary collection of individual assets
	//		 since ultimately in use a hard reference is needed to the asset. Using some
	//		 sort of "grouping" makes it clearer and easier to use.

	if (FCsCVarLogMap::Get().IsShowing(NCsCVarLog::LogLevelPayloadPopulate))
	{
		UE_LOG(LogCs, Warning, TEXT("ACsLevelScriptActor::PopulatePayload: Setting up payload for Level: %s."), *(LevelName.ToString()));
	}

	// Get DataTables
	TMap<FName, UDataTable*> OutDataTableMap;
	UCsLibrary_Load::GetDataTables(Level, OutDataTableMap);

	if (FCsCVarLogMap::Get().IsShowing(NCsCVarLog::LogLevelPayloadPopulate))
	{
		const int32 Count = OutDataTableMap.Num();

		if (Count > CS_EMPTY)
		{
			UE_LOG(LogCs, Warning, TEXT("- %d DataTables found."), Count);

			for (TPair<FName, UDataTable*>& Pair : OutDataTableMap)
			{
				const FName& Name	  = Pair.Key;
				UDataTable* DataTable = Pair.Value;
				const FString Path	  = DataTable->GetPathName();

				UE_LOG(LogCs, Warning, TEXT("-- %s @ %s."), *(Name.ToString()), *Path);
			}
		}
	}

	Payload_Level.Reset();
	Payload_Level.Append(OutDataTableMap, true);
	Payload_Level.BuildFromMaps();
	Payload_Level.Populate();
}

void ACsLevelScriptActor::PopulatePayloadLevels()
{
	if (UWorld* World = GetWorld())
	{
		ACsLevelScriptActor* DOb = GetClass()->GetDefaultObject<ACsLevelScriptActor>();

		const TArray<ULevel*>& Levels = World->GetLevels();

		for (ULevel* Level : Levels)
		{
			UWorld* LevelWorld   = Cast<UWorld>(Level->GetOuter());
			const FName LevelName = LevelWorld->GetFName();

			// Sub-Level
			if (!Level->IsPersistentLevel())
			{
				DOb->SubLevelNames.Add(LevelName);
			}

			DOb->PopulatePayload(Level);
		}
	}
}

void ACsLevelScriptActor::PopulatePayloadCombined()
{
	Payload_Combined.Reset();
	Payload_Combined.Append(Payload);
	Payload_Combined.Append(Payload_Levels);
	Payload_Combined.BuildFromMaps();
	Payload_Combined.Populate();

	if (FCsCVarLogMap::Get().IsShowing(NCsCVarLog::LogLevelPayloadPopulate))
	{
		UE_LOG(LogCs, Warning, TEXT("ACsLevelScriptActor::PopulatePayloadCombined: %s."), *GetName());

		// Payload
		{
			UE_LOG(LogCs, Warning, TEXT("- Payload"));

			const TArray<FCsSoftObjectPath>& Paths = Payload.Paths.Paths;
			const int32 Count					   = Paths.Num();

			if (Count > CS_EMPTY)
			{
				UE_LOG(LogCs, Warning, TEXT("-- %d Paths [%s]."), Count, *(Payload.Paths.Size.ToString()));

				for (int32 I = 0; I < Count; ++I)
				{
					const FCsSoftObjectPath& Path = Paths[I];

					UE_LOG(LogCs, Warning, TEXT("--- [%d] %s."), I, *(Path.ToString()));
				}
			}
		}
		// Payload_Levels
		{
			UE_LOG(LogCs, Warning, TEXT("- Levels"));

			for (const TPair<FName, FCsPayload>& Pair : Payload_Levels)
			{
				const FName& Name				= Pair.Key;
				const FCsPayload& Payload_Level = Pair.Value;

				UE_LOG(LogCs, Warning, TEXT("-- %s"), *(Name.ToString()));

				const TArray<FCsSoftObjectPath>& Paths = Payload_Level.Paths.Paths;
				const int32 Count				 = Paths.Num();

				if (Count > CS_EMPTY)
				{
					UE_LOG(LogCs, Warning, TEXT("--- %d Paths [%s]."), Count, *(Payload_Level.Paths.Size.ToString()));

					for (int32 I = 0; I < Count; ++I)
					{
						const FCsSoftObjectPath& Path = Paths[I];

						UE_LOG(LogCs, Warning, TEXT("---- [%d] %s."), I, *(Path.ToString()));
					}
				}
			}
		}
		// Combined
		{
			UE_LOG(LogCs, Warning, TEXT("- Combined"));

			const TArray<FCsSoftObjectPath>& Paths = Payload_Combined.Paths.Paths;
			const int32 Count					   = Paths.Num();

			if (Count > CS_EMPTY)
			{
				UE_LOG(LogCs, Warning, TEXT("-- %d Paths [%s]."), Count, *(Payload_Combined.Paths.Size.ToString()));

				for (int32 I = 0; I < Count; ++I)
				{
					const FCsSoftObjectPath& Path = Paths[I];

					UE_LOG(LogCs, Warning, TEXT("--- [%d] %s."), I, *(Path.ToString()));
				}
			}
		}
	}
	
	// Update Settings if the level is NOT a test level
	if (!bTest)
	{
		const FName LevelName = GetLevelFName();

		UCsDeveloperSettings* Settings = GetMutableDefault<UCsDeveloperSettings>();

		UCsLibrary_Load::LoadStruct(Settings, UCsDeveloperSettings::StaticClass(), NCsLoadFlags::All, NCsLoadCodes::None);
		
		// DataRootSet
		if (UObject* Object = Settings->DataRootSet.LoadSynchronous())
		{
			ICsDataRootSet* DataRootSet = Cast<ICsDataRootSet>(Object);

			checkf(DataRootSet, TEXT("ACsLevelScriptActor::PopulatePayloadCombined: Object: %s @ %s does NOT implement interface: ICsDataRootSet."));

			// Datas
			if (UDataTable* Datas = DataRootSet->GetDatas())
			{
				if (Payload_Combined.Datas.Num() > CS_EMPTY)
					Datas->MarkPackageDirty();

				for (const FCsPayload_Data& Payload_Data : Payload_Combined.Datas)
				{
					const FName& DataName = Payload_Data.Name;

					if (FCsDataEntry_Data* RowPtr = Datas->FindRow<FCsDataEntry_Data>(DataName, NCsLevelScriptActorCached::Str::PopulatePayloadLevels))
					{
						RowPtr->Paths = Payload_Data.Paths;
					}
					else
					{
						FCsDataEntry_Data Entry;
						Entry.Name = DataName;
						Entry.Data = Payload_Data.Data;
						Entry.Paths = Payload_Data.Paths;

						Datas->AddRow(DataName, Entry);
					}
				}
			}
			// DataTables
			if (UDataTable* DataTables = DataRootSet->GetDataTables())
			{
				if (Payload_Combined.DataTables.Num() > CS_EMPTY)
					DataTables->MarkPackageDirty();

				for (const FCsPayload_DataTable& Payload_DataTable : Payload_Combined.DataTables)
				{
					const FName& DataTableName = Payload_DataTable.Name;

					if (FCsDataEntry_DataTable* RowPtr = DataTables->FindRow<FCsDataEntry_DataTable>(DataTableName, NCsLevelScriptActorCached::Str::PopulatePayloadLevels))
					{
						RowPtr->Paths = Payload_DataTable.Paths;
					}
					else
					{
						FCsDataEntry_DataTable Entry;
						Entry.Name		= DataTableName;
						Entry.DataTable = Payload_DataTable.DataTable;
						Entry.Paths		= Payload_DataTable.Paths;

						DataTables->AddRow(DataTableName, Entry);
					}
				}
			}
			// Payloads
			if (UDataTable* Payloads = DataRootSet->GetPayloads())
			{
				if (Payload_Combined.DataTables.Num() > CS_EMPTY)
					Payloads->MarkPackageDirty();

				if (FCsPayload* RowPtr = Payloads->FindRow<FCsPayload>(LevelName, NCsLevelScriptActorCached::Str::PopulatePayloadLevels))
				{
					*RowPtr = Payload_Combined;
				}
				else
				{
					Payloads->AddRow(LevelName, Payload_Combined);
				}
			}
		}
	}
}

#endif // #if WITH_EDITOR

#pragma endregion

// Editor
#pragma region
#if WITH_EDITOR

void ACsLevelScriptActor::PostEditChangeProperty(FPropertyChangedEvent& e)
{
	const FName PropertyName	   = (e.Property != NULL) ? e.Property->GetFName() : NAME_None;
	const FName MemberPropertyName = (e.MemberProperty != NULL) ? e.MemberProperty->GetFName() : NAME_None;

	// bTest - TODO: Need to make sure if bTest = false to remove Payload from Settings->Payloads
	// Payload
	{
		// Payload.DataTable
		/*
		if (PropertyName == GET_MEMBER_NAME_CHECKED(ACsLevelScriptActor, Payload) &&
			MemberPropertyName == GET_MEMBER_NAME_CHECKED(FCsPayload, DataTable))
		{

		}
		*/
	}

	Super::PostEditChangeProperty(e);
}

void ACsLevelScriptActor::PostEditChangeChainProperty(FPropertyChangedChainEvent& e)
{
	const FName PropertyName	   = (e.Property != NULL) ? e.Property->GetFName() : NAME_None;
	const FName MemberPropertyName = (e.MemberProperty != NULL) ? e.MemberProperty->GetFName() : NAME_None;

	// Payload
	{
		// Payload.DataTables[Index]
		{
			const int32 Index = e.GetArrayIndex(TEXT("DataTables"));

			if (Index != INDEX_NONE)
			{
				if (Index < Payload.DataTables.Num())
				{
					FCsPayload_DataTable& Entry = Payload.DataTables[Index];

					if (Entry.IsValid())
						Entry.Populate();
					else
						Entry.Reset();
					Payload.BuildMaps();
					Payload.Populate();
					PopulatePayloadCombined();
				}
			}
		}
	}
	Super::PostEditChangeChainProperty(e);
}

#endif // #if WITH_EDITOR
#pragma endregion Editor