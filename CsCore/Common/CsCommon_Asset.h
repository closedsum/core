// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"

#if WITH_EDITOR
#include "AssetRegistryModule.h"
#include "Developer/AssetTools/Public/AssetToolsModule.h"
#include "Editor/ContentBrowser/Public/ContentBrowserModule.h"

#include "Classes/Factories/BlueprintFactory.h"
#endif WITH_EDITOR

#include "CsCommon_Asset.generated.h"

UCLASS()
class CSCORE_API UCsCommon_Asset : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()

// Asset Registry
#pragma region

#if WITH_EDITOR

	template<typename T>
	static void SetObjectFromAssetData(FAssetData& InAssetData, const FName& AssetName, T*& OutObject, FString& OutPackagePath)
	{
		if (InAssetData.AssetName == AssetName)
		{
			OutObject = Cast<T>(InAssetData.GetAsset());
			OutPackagePath = InAssetData.PackagePath.ToString();
		}
	}

	template<typename T>
	static void SetObjectFromAssetData(FAssetData& InAssetData, const FName& AssetName, T*& OutObject)
	{
		if (InAssetData.AssetName == AssetName)
			OutObject = Cast<T>(InAssetData.GetAsset());
	}

	template<typename T>
	static UBlueprint* CreateBlueprintAsset(const FString &Name, const FString &PackagePath)
	{
		UBlueprintFactory* Factory			= NewObject<UBlueprintFactory>();
		Factory->ParentClass				= T::StaticClass();
		FAssetToolsModule& AssetToolsModule = FModuleManager::GetModuleChecked<FAssetToolsModule>("AssetTools");
		UBlueprint* Bp						= Cast<UBlueprint>(AssetToolsModule.Get().CreateAsset(Name, PackagePath, UBlueprint::StaticClass(), Factory));

		TArray<UObject*> ObjectsToSync;
		ObjectsToSync.Add(Bp);

		FContentBrowserModule& ContentBrowserModule = FModuleManager::LoadModuleChecked<FContentBrowserModule>("ContentBrowser");
		ContentBrowserModule.Get().SyncBrowserToAssets(ObjectsToSync);

		return Bp;
	}

	template<typename T>
	static T* GetAsset(const FString &Name)
	{
		FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>(FName("AssetRegistry"));
		IAssetRegistry& AssetRegistry = AssetRegistryModule.Get();

		TArray<FAssetData> OutAssetData;

		AssetRegistry.GetAssetsByClass(T::StaticClass()->GetFName(), OutAssetData);

		const int32 AssetCount = OutAssetData.Num();

		for (int32 I = 0; I < AssetCount; I++)
		{
			const FString AssetStringName = OutAssetData[I].AssetName.ToString().ToLower();

			if (Name == AssetStringName)
			{
				return Cast<T>(OutAssetData[I].GetAsset());
			}
		}
		return NULL;
	}

	template<typename T>
	static T* GetAsset(const TArray<FString> &KeywordsOR)
	{
		FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>(FName("AssetRegistry"));
		IAssetRegistry& AssetRegistry = AssetRegistryModule.Get();

		TArray<FAssetData> OutAssetData;

		AssetRegistry.GetAssetsByClass(T::StaticClass()->GetFName(), OutAssetData);

		const int32 AssetCount = OutAssetData.Num();
		const int32 Count	   = KeywordsOR.Num();

		for (int32 I = 0; I < AssetCount; I++)
		{
			const FString AssetStringName = OutAssetData[I].AssetName.ToString().ToLower();

			for (int32 J = 0; J < Count; J++)
			{
				if (KeywordsOR[J] == AssetStringName)
				{
					return Cast<T>(OutAssetData[I].GetAsset());
				}
			}
		}
		return NULL;
	}

	template<typename T>
	static void GetAssets(const FString &Name, TArray<T*> &OutAssets)
	{
		OutAssets.Reset();

		FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>(FName("AssetRegistry"));
		IAssetRegistry& AssetRegistry = AssetRegistryModule.Get();

		TArray<FAssetData> OutAssetData;

		AssetRegistry.GetAssetsByClass(T::StaticClass()->GetFName(), OutAssetData);

		const FString NameLower = Name.ToLower();

		const int32 AssetCount = OutAssetData.Num();

		for (int32 I = 0; I < AssetCount; I++)
		{
			const FString AssetStringName = OutAssetData[I].AssetName.ToString().ToLower();

			if (NameLower == AssetStringName)
				OutAssets.Add(Cast<T>(OutAssetData[I].GetAsset()));
		}
	}

	template<typename T>
	static void GetAssets(const FName &Name, TArray<T*> &OutAssets)
	{
		GetAssets<T>(Name.ToString(), OutAssets);
	}

	template<typename T>
	static void GetAssets(const TArray<FString> &KeywordsAND, TArray<T*> &OutAssets)
	{
		OutAssets.Reset();

		FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>(FName("AssetRegistry"));
		IAssetRegistry& AssetRegistry			  = AssetRegistryModule.Get();

		TArray<FAssetData> OutAssetData;

		AssetRegistry.GetAssetsByClass(T::StaticClass()->GetFName(), OutAssetData);

		const int32 AssetCount = OutAssetData.Num();
		const int32 KeywordCount = KeywordsAND.Num();

		for (int32 I = 0; I < AssetCount; I++)
		{
			const FString AssetStringName = OutAssetData[I].AssetName.ToString().ToLower();
			
			bool Pass = true;

			for (int32 I = 0; I < KeywordCount; I++)
			{
				Pass &= AssetStringName.Contains(KeywordsAND[I]);
			}

			if (Pass)
			{
				OutAssets.Add(Cast<T>(OutAssetData[I].GetAsset()));
			}
		}
	}

	template<typename T>
	static void GetAssets(const FString &Name, TArray<T*> &OutAssets, TArray<FString> &OutPackagePaths)
	{
		OutAssets.Reset();
		OutPackagePaths.Reset();

		FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>(FName("AssetRegistry"));
		IAssetRegistry& AssetRegistry = AssetRegistryModule.Get();

		TArray<FAssetData> OutAssetData;

		AssetRegistry.GetAssetsByClass(T::StaticClass()->GetFName(), OutAssetData);

		const FString NameLower = Name.ToLower();

		const int32 AssetCount = OutAssetData.Num();

		for (int32 I = 0; I < AssetCount; I++)
		{
			const FString AssetStringName = OutAssetData[I].AssetName.ToString().ToLower();

			if (NameLower == AssetStringName)
			{
				OutAssets.Add(Cast<T>(OutAssetData[I].GetAsset()));
				OutPackagePaths.Add(OutAssetData[I].PackagePath.ToString());
			}
		}
	}

	template<typename T>
	static void GetAssets(const FName &Name, TArray<T*> &OutAssets, TArray<FName> &OutPackagePaths)
	{
		OutAssets.Reset();
		OutPackagePaths.Reset();

		FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>(FName("AssetRegistry"));
		IAssetRegistry& AssetRegistry			  = AssetRegistryModule.Get();

		TArray<FAssetData> OutAssetData;

		AssetRegistry.GetAssetsByClass(T::StaticClass()->GetFName(), OutAssetData);

		const int32 AssetCount = OutAssetData.Num();

		for (int32 I = 0; I < AssetCount; I++)
		{
			if (Name == OutAssetData[I].AssetName)
			{
				OutAssets.Add(Cast<T>(OutAssetData[I].GetAsset()));
				OutPackagePaths.Add(OutAssetData[I].PackagePath);
			}
		}
	}

	template<typename T>
	static T* GetBlueprintDefaultObject(const FString &Name)
	{
		UBlueprint* Bp = GetAsset<UBlueprint>(Name);

		return Bp ? Cast<UBlueprintCore>(Bp)->GeneratedClass->GetDefaultObject<T>() : NULL;
	}

	template<typename T>
	static T* GetBlueprintDefaultObject(const FName &Name)
	{
		return GetBlueprintDefaultObject<T>(Name.ToString());
	}

	template<typename T>
	static void GetBlueprintDefaultObjects(TArray<T*> &OutDefaultObjects, const TArray<FString>& KeywordsAND)
	{
		TArray<UBlueprint*> OutAssets;
		GetAssets<UBlueprint>(OutAssets, KeywordsAND);

		OutDefaultObjects.Reset();

		const uint32 Count = OutAssets.Num();

		for (uint32 I = 0; I < Count; I++)
		{
			if (T* DOb = Cast<UBlueprintCore>(OutAssets[I])->GeneratedClass->GetDefaultObject<T>())
				OutDefaultObjects.Add(DOb);
		}
	}

	static void SyncBrowserToAsset(UObject* InObject);
	static void SyncBrowserToAssets(TArray<UObject*> Objects);

	static class UFactory* GetFactory(UClass* ClassToSpawn);
	static class UObject* CreateAsset(UClass* ClassToSpawn, const FString &Name, const FString &PackagePath);

	static class ULevelSequence* CreateLevelSequence(const FString &Name, const FString &PackagePath);

	static class UAnimSequence* CreateAnimSequence(class USkeletalMesh* Mesh, const FString &Name, const FString &PackagePath);
	static void InitAnimSequence(class UAnimSequence* Anim, class USkeletalMeshComponent* Mesh);
	static void InitAnimSequence(class UAnimSequence* Anim, class UPoseableMeshComponent* Mesh);

#endif // #if WITH_EDITOR

#pragma endregion Asset Registry
};