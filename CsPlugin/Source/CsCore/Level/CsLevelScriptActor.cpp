// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Level/CsLevelScriptActor.h"
#include "CsCore.h"

// Library
#include "Library/CsLibrary_Load.h"

#if WITH_EDITOR
#include "Settings/CsDeveloperSettings.h"
#include "Engine/BlueprintGeneratedClass.h"
#include "Engine/LevelScriptBlueprint.h"
#endif // #if WITH_EDITOR

ACsLevelScriptActor::ACsLevelScriptActor(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

// Editor
#pragma region
#if WITH_EDITOR

void ACsLevelScriptActor::PostEditChangeProperty(FPropertyChangedEvent& e)
{
	const FName PropertyName	   = (e.Property != NULL) ? e.Property->GetFName() : NAME_None;
	const FName MemberPropertyName = (e.MemberProperty != NULL) ? e.MemberProperty->GetFName() : NAME_None;

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
				FCsPayload_DataTable& Entry = Payload.DataTables[Index];

				if (Entry.IsValid())
					Entry.Populate();
				else
					Entry.Reset();
				Payload.Populate();

				// Get Level Name
				UBlueprintGeneratedClass* BpClass = Cast<UBlueprintGeneratedClass>(GetOuter());
				ULevelScriptBlueprint* LevelBp	  = Cast<ULevelScriptBlueprint>(BpClass->ClassGeneratedBy);
				FString LevelName				  = LevelBp->GetFriendlyName();

				UWorld* World = GetWorld();

				/*
				const FString ClassName = GetOuter()->GetName();

				const FString Name = GetName();
				FString LevelName;

				// Default
				if (Name.StartsWith(TEXT("Default__")))
				{
					LevelName = Name;
					LevelName.RemoveFromStart(TEXT("Default__"));
					LevelName.RemoveFromEnd(TEXT("_C"));
				}
				else
				{
					LevelName = Name;

					const int32 I = LevelName.Find(TEXT("_C_"));

					if (I != INDEX_NONE)
					{
						LevelName = LevelName.Left(I);
					}
				}
				*/
				// Update Payloads in Settings
				if (Entry.IsValid())
				{
					UCsDeveloperSettings* Settings = GetMutableDefault<UCsDeveloperSettings>();

					UCsLibrary_Load::LoadStruct(Settings, UCsDeveloperSettings::StaticClass());

					if (UDataTable* Payloads = Settings->Payloads.Get())
					{
						//Payloads->FindRow
					}
				}
			}
		}
	}
	Super::PostEditChangeChainProperty(e);
}

#endif // #if WITH_EDITOR
#pragma endregion Editor