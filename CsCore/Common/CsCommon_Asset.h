// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Types/CsTypes_Primitive.h"

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

	static IAssetRegistry& GetAssetRegistry();

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
	static T* GetAsset(const FString &Name, const TCsStringCompare& CompareType)
	{
		IAssetRegistry& AssetRegistry = GetAssetRegistry();

		TArray<FAssetData> OutAssetData;

		AssetRegistry.GetAssetsByClass(T::StaticClass()->GetFName(), OutAssetData);

		const FString NameLower = Name.ToLower();
		const int32 AssetCount  = OutAssetData.Num();

		for (int32 I = 0; I < AssetCount; ++I)
		{
			const FString AssetStringName = OutAssetData[I].AssetName.ToString().ToLower();

			if (ECsStringCompare::Compare(AssetStringName, NameLower, CompareType))
				return Cast<T>(OutAssetData[I].GetAsset());
		}
		return nullptr;
	}

	template<typename T>
	static T* GetAsset(const TArray<FString> &KeywordsOR, const TCsStringCompare& CompareType)
	{
		IAssetRegistry& AssetRegistry = GetAssetRegistry();

		TArray<FAssetData> OutAssetDatas;

		AssetRegistry.GetAssetsByClass(T::StaticClass()->GetFName(), OutAssetDatas);

		const int32 AssetCount   = OutAssetDatas.Num();
		const int32 KeywordCount = KeywordsOR.Num();

		TArray<FString> KeywordsORLower;

		for (int32 I = 0; I < KeywordCount; ++I)
		{
			KeywordsORLower.Add(KeywordsOR[I].ToLower());
		}

		for (int32 I = 0; I < AssetCount; ++I)
		{
			const FString AssetStringName = OutAssetDatas[I].AssetName.ToString().ToLower();
			bool Pass = false;

			for (int32 J = 0; J < KeywordCount; ++J)
			{
				Pass |= ECsStringCompare::Compare(AssetStringName, KeywordsORLower[J], CompareType);

				if (Pass)
					break;
			}

			if (Pass)
				return Cast<T>(OutAssetData[I].GetAsset());
		}
		return nullptr;
	}

	template<typename T>
	static void GetAssets(const FString &Name, TArray<T*> &OutAssets, const TCsStringCompare& CompareType)
	{
		OutAssets.Reset();

		IAssetRegistry& AssetRegistry = GetAssetRegistry();

		TArray<FAssetData> OutAssetData;

		AssetRegistry.GetAssetsByClass(T::StaticClass()->GetFName(), OutAssetData);

		const FString NameLower = Name.ToLower();
		const int32 AssetCount  = OutAssetData.Num();

		for (int32 I = 0; I < AssetCount; ++I)
		{
			const FString AssetStringName = OutAssetData[I].AssetName.ToString().ToLower();
			
			if (ECsStringCompare::Compare(AssetStringName, NameLower, CompareType))
				OutAssets.Add(Cast<T>(OutAssetData[I].GetAsset()));
		}
	}

	template<typename T>
	static void GetAssets(const FName &Name, TArray<T*> &OutAssets, const TCsStringCompare& CompareType)
	{
		GetAssets<T>(Name.ToString(), OutAssets, CompareType);
	}

	template<typename T>
	static void GetAssets(const TArray<FString> &KeywordsAND, TArray<T*> &OutAssets, const TCsStringCompare& CompareType)
	{
		OutAssets.Reset();

		IAssetRegistry& AssetRegistry = GetAssetRegistry();

		TArray<FAssetData> OutAssetData;

		AssetRegistry.GetAssetsByClass(T::StaticClass()->GetFName(), OutAssetData);

		const int32 AssetCount   = OutAssetData.Num();
		const int32 KeywordCount = KeywordsAND.Num();

		TArray<FString> KeywordsANDLower;

		for (int32 I = 0; I < KeywordCount; ++I)
		{
			KeywordsANDLower.Add(KeywordsAND[I].ToLower());
		}

		for (int32 I = 0; I < AssetCount; ++I)
		{
			const FString AssetStringName = OutAssetData[I].AssetName.ToString().ToLower();
			bool Pass = true;

			for (int32 I = 0; I < KeywordCount; ++I)
			{
				Pass &= ECsStringCompare::Compare(AssetStringName, KeywordsORLower[J], CompareType);

				if (!Pass)
					break;
			}

			if (Pass)
			{
				OutAssets.Add(Cast<T>(OutAssetData[I].GetAsset()));
			}
		}
	}

	template<typename T>
	static void GetAssets(const FString &Name, TArray<T*> &OutAssets, TArray<FString> &OutPackagePaths, const TCsStringCompare& CompareType)
	{
		OutAssets.Reset();
		OutPackagePaths.Reset();

		IAssetRegistry& AssetRegistry = GetAssetRegistry();

		TArray<FAssetData> OutAssetData;

		AssetRegistry.GetAssetsByClass(T::StaticClass()->GetFName(), OutAssetData);

		const FString NameLower = Name.ToLower();
		const int32 AssetCount  = OutAssetData.Num();

		for (int32 I = 0; I < AssetCount; ++I)
		{
			const FString AssetStringName = OutAssetData[I].AssetName.ToString().ToLower();

			if (ECsStringCompare::Compare(AssetStringName, NameLower, CompareType))
			{
				OutAssets.Add(Cast<T>(OutAssetData[I].GetAsset()));
				OutPackagePaths.Add(OutAssetData[I].PackagePath.ToString());
			}
		}
	}

	template<typename T>
	static void GetAssets(const FName &Name, TArray<T*> &OutAssets, TArray<FName> &OutPackagePaths, const TCsStringCompare& CompareType)
	{
		OutAssets.Reset();
		OutPackagePaths.Reset();

		IAssetRegistry& AssetRegistry = GetAssetRegistry();

		TArray<FAssetData> OutAssetData;

		AssetRegistry.GetAssetsByClass(T::StaticClass()->GetFName(), OutAssetData);

		const FString NameLower = Name.ToString().ToLower();
		const int32 AssetCount  = OutAssetData.Num();

		for (int32 I = 0; I < AssetCount; ++I)
		{
			const FString AssetStringName = OutAssetData[I].AssetName.ToString().ToLower();

			if (ECsStringCompare::Compare(AssetStringName, NameLower, CompareType))
			{
				OutAssets.Add(Cast<T>(OutAssetData[I].GetAsset()));
				OutPackagePaths.Add(OutAssetData[I].PackagePath);
			}
		}
	}

	template<typename T>
	static T* GetBlueprintDefaultObject(const FString &Name, const TCsStringCompare& CompareType)
	{
		UBlueprint* Bp = GetAsset<UBlueprint>(Name, CompareType);

		return Bp ? Cast<UBlueprintCore>(Bp)->GeneratedClass->GetDefaultObject<T>() : NULL;
	}

	template<typename T>
	static T* GetBlueprintDefaultObject(const FName &Name, const TCsStringCompare& CompareType)
	{
		return GetBlueprintDefaultObject<T>(Name.ToString(), CompareType);
	}

	template<typename T>
	static void GetBlueprintDefaultObjects(const TArray<FString>& KeywordsAND, TArray<T*> &OutDefaultObjects, const TCsStringCompare& CompareType)
	{
		TArray<UBlueprint*> OutAssets;
		GetAssets<UBlueprint>(KeywordsAND, OutAssets, CompareType);

		OutDefaultObjects.Reset();

		const uint32 Count = OutAssets.Num();

		for (uint32 I = 0; I < Count; ++I)
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