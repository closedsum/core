// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Settings/CsDeveloperSettings.h"
#include "CsCore.h"

#if WITH_EDITOR
// Library
#include "Library/CsLibrary_Property.h"
// Settings
#include "Settings/ProjectPackagingSettings.h"
#endif // #if WITH_EDITOR

// Cached
#pragma region

namespace NCsDeveloperSettings
{
	namespace Str
	{
		CSCORE_API CS_DEFINE_CACHED_STRING(InputActionMap, "UCsDeveloperSettings::InputActionMap");
		CSCORE_API CS_DEFINE_CACHED_STRING(GameEvent, "UCsDeveloperSettings::GameEvent");
		CSCORE_API CS_DEFINE_CACHED_STRING(FX, "UCsDeveloperSettings::FX");
		CSCORE_API CS_DEFINE_CACHED_STRING(Sound, "UCsDeveloperSettings::Sound");
		CSCORE_API CS_DEFINE_CACHED_STRING(SkeletalMeshActor, "UCsDeveloperSettings::SkeletalMeshActor");
	}
}

#pragma endregion Cached

UCsDeveloperSettings::UCsDeveloperSettings(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

UObject* UCsDeveloperSettings::SafeLoadDataRootSet(const FString& Context)
{
	const FSoftObjectPath& SoftPath = DataRootSet.ToSoftObjectPath();

	if (!SoftPath.IsValid())
	{
		UE_LOG(LogCs, Warning, TEXT("%s: DataRootSet's Path is NOT Valid."), *Context);
		return nullptr;
	}

	UClass* Class = DataRootSet.LoadSynchronous();

	if (!Class)
	{
		UE_LOG(LogCs, Warning, TEXT("%s: Failed to load DataRootSet @ Path: %s."), *Context, *(SoftPath.ToString()));
		return nullptr;
	}

	UObject* DOb = Class->GetDefaultObject();

	if (!DOb)
	{
		UE_LOG(LogCs, Warning, TEXT("%s: Failed to get Default Object from DataRootSet @ Path: %s with Class: %s."), *Context, *(SoftPath.ToString()), *(Class->GetName()));
		return nullptr;
	}
	return DOb;
}

#if WITH_EDITOR

void UCsDeveloperSettings::PostEditChangeProperty(struct FPropertyChangedEvent& e)
{
	const FName PropertyName	   = (e.Property != NULL) ? e.Property->GetFName() : NAME_None;
	const FName MemberPropertyName = (e.MemberProperty != NULL) ? e.MemberProperty->GetFName() : NAME_None;

	Super::PostEditChangeProperty(e);
}

void UCsDeveloperSettings::PostEditChangeChainProperty(FPropertyChangedChainEvent& e)
{
	const FName PropertyFName	   = (e.Property != NULL) ? e.Property->GetFName() : NAME_None;
	const FString PropertyName	   = (e.Property != NULL) ? e.Property->GetName() : TEXT("");
	const FName MemberPropertyName = (e.MemberProperty != NULL) ? e.MemberProperty->GetFName() : NAME_None;

	//int32 Index;

	typedef NCsProperty::FLibrary PropertyLibrary;

	TSet<FString> PropertyNames;
	PropertyLibrary::GetPropertyNamesInChain(e, PropertyNames);

	typedef NCsEnum::NSettings::FLibrary EnumSettingsLibrary;

	// Data
	{
		if (PropertyNames.Contains("DataRootSets") ||
			PropertyNames.Contains("bApply"))
		{
			UProjectPackagingSettings* PackageSettings = GetMutableDefault< UProjectPackagingSettings>();

			const int32 Count = (int32)ECsPlatform::ECsPlatform_MAX;

			int32 Index = INDEX_NONE;

			// Add to DirectoriesToAlwaysCook
			for (int32 I = 0; I < Count; ++I)
			{
				FCsSettings_DataRootSet& Set = DataRootSets[I];

				if (Set.bApply)
				{
					DataRootSet = DataRootSets[I].DataRootSet;

					if (PackageSettings->DirectoriesToAlwaysCook.Num() == CS_EMPTY)
					{
						PackageSettings->DirectoriesToAlwaysCook.AddDefaulted();
					}
					PackageSettings->DirectoriesToAlwaysCook[CS_FIRST] = DataRootSets[I].DirectoryToAlwaysCook;

					Index = I;
					break;
				}
			}
			// Add to DirectoriesToNeverCook

				// First remove all directories in DataRootSets
			for (int32 I = 0; I < Count; ++I)
			{
				const FDirectoryPath& D1 = DataRootSets[I].DirectoryToAlwaysCook;

				int32 Num = PackageSettings->DirectoriesToNeverCook.Num();

				for (int32 J = Num - 1; J >= 0; --J)
				{
					FDirectoryPath& D2 = PackageSettings->DirectoriesToNeverCook[J];

					if (D2.Path == D1.Path)
					{
						PackageSettings->DirectoriesToNeverCook.RemoveAt(J);
					}
				}
			}
				// Get all directories to add to DirectoriesToNeverCook
			TArray<int32> PathsToAdd;

			for (int32 I = 0; I < Count; ++I)
			{
				if (DataRootSets[I].bApply)
					continue;

				if (PathsToAdd.Num() == CS_EMPTY)
				{
					PathsToAdd.Add(I);
				}
				else
				{
					bool Add = true;

					for (const int32& J : PathsToAdd)
					{	
						const FString& P  = DataRootSets[Index].DirectoryToAlwaysCook.Path;
						const FString& P1 = DataRootSets[I].DirectoryToAlwaysCook.Path;
						const FString& P2 = DataRootSets[J].DirectoryToAlwaysCook.Path;

						if (P1 == P ||
							P1 == P2)
						{
							Add = false;
						}
					}

					if (Add)
						PathsToAdd.Add(I);
				}
			}
				// Add directors to DirectoriesToNeverCook
			for (const int32& I : PathsToAdd)
			{
				PackageSettings->DirectoriesToNeverCook.Add(DataRootSets[I].DirectoryToAlwaysCook);
			}
			DataRootSets[Index].bApply = false;
		}
	}
	// Input
	{
		// ECsInputActionMap
		if (PropertyName == TEXT("ECsInputActionMap"))
		{
			EnumSettingsLibrary::PopulateArrayFromString(ECsInputActionMap_Internal, ECsInputActionMap, EMCsInputActionMap::Get().GetEnumName());
		}
		// ECsGameEvent
		if (PropertyName == TEXT("ECsGameEvent"))
		{
			EnumSettingsLibrary::PopulateArrayFromString(ECsGameEvent_Internal, ECsGameEvent, EMCsGameEvent::Get().GetEnumName());
		}
		// Input
		if (PropertyNames.Contains("Input"))
		{
			Input.OnPostEditChange(PropertyName, PropertyNames);
		}
	}

	Super::PostEditChangeChainProperty(e);
}

#endif // #if WITH_EDITOR