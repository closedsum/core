// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "CoreUObject/Public/UObject/Object.h"
#include "Types/CsTypes_Primitive.h"

#if WITH_EDITOR
#include "AssetRegistryModule.h"
#include "Developer/AssetTools/Public/AssetToolsModule.h"
#include "Editor/ContentBrowser/Public/ContentBrowserModule.h"

#include "Classes/Factories/BlueprintFactory.h"
#endif WITH_EDITOR

#include "CsLibrary_Asset.generated.h"

class UCsEnumStructUserDefinedEnumMap;

UCLASS()
class CSCORE_API UCsLibrary_Asset : public UObject
{
	GENERATED_UCLASS_BODY()

// Asset Registry
#pragma region
public:

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
	static T* GetAsset(const FString& Name, const ECsStringCompare& CompareType)
	{
		IAssetRegistry& AssetRegistry = GetAssetRegistry();

		TArray<FAssetData> OutAssetData;

		AssetRegistry.GetAssetsByClass(T::StaticClass()->GetFName(), OutAssetData);

		const FString NameLower = Name.ToLower();
		const int32 AssetCount  = OutAssetData.Num();

		for (int32 I = 0; I < AssetCount; ++I)
		{
			const FString AssetStringName = OutAssetData[I].AssetName.ToString().ToLower();

			if (NCsStringCompare::Compare(AssetStringName, NameLower, CompareType))
				return Cast<T>(OutAssetData[I].GetAsset());
		}
		return nullptr;
	}

	template<typename T>
	static T* GetAsset(const TArray<FString>& KeywordsOR, const ECsStringCompare& CompareType)
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
				Pass |= NCsStringCompare::Compare(AssetStringName, KeywordsORLower[J], CompareType);

				if (Pass)
					break;
			}

			if (Pass)
				return Cast<T>(OutAssetData[I].GetAsset());
		}
		return nullptr;
	}

	template<typename T>
	static void GetAssets(const FString& Name, const ECsStringCompare& CompareType, TArray<T*>& OutAssets)
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
			
			if (NCsStringCompare::Compare(AssetStringName, NameLower, CompareType))
				OutAssets.Add(Cast<T>(OutAssetData[I].GetAsset()));
		}
	}

	template<typename T>
	static void GetAssets(const FName& Name, const ECsStringCompare& CompareType, TArray<T*>& OutAssets)
	{
		GetAssets<T>(Name.ToString(), CompareType, OutAssets);
	}

	template<typename T>
	static void GetAssets(const TArray<FString>& KeywordsAND, const ECsStringCompare& CompareType, TArray<T*>& OutAssets)
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

			for (int32 J = 0; J < KeywordCount; ++J)
			{
				Pass &= NCsStringCompare::Compare(AssetStringName, KeywordsORLower[J], CompareType);

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
	static void GetAssets(const FString& Name, const ECsStringCompare& CompareType, TArray<T*>& OutAssets, TArray<FString>& OutPackagePaths)
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

			if (NCsStringCompare::Compare(AssetStringName, NameLower, CompareType))
			{
				OutAssets.Add(Cast<T>(OutAssetData[I].GetAsset()));
				OutPackagePaths.Add(OutAssetData[I].PackagePath.ToString());
			}
		}
	}

	template<typename T>
	static void GetAssets(const FName& Name, const ECsStringCompare& CompareType, TArray<T*>& OutAssets, TArray<FName>& OutPackagePaths)
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

			if (NCsStringCompare::Compare(AssetStringName, NameLower, CompareType))
			{
				OutAssets.Add(Cast<T>(OutAssetData[I].GetAsset()));
				OutPackagePaths.Add(OutAssetData[I].PackagePath);
			}
		}
	}

	template<typename T>
	static T* GetDefaultObject(UBlueprint* Bp, UClass* InParentClass)
	{
		UClass* ParentClass = InParentClass ? InParentClass : T::StaticClass();
		UBlueprintCore* BpC = Cast<UBlueprintCore>(Bp);

		if (!BpC)
			return nullptr;
		if (!BpC->GeneratedClass)
			return nullptr;

		UClass* Class = Bp->ParentClass.Get();

		if (!Class)
			return nullptr;
		if (!Class->IsChildOf(ParentClass))
			return nullptr;

		return BpC->GeneratedClass->GetDefaultObject<T>();
	}

	template<typename T>
	static T* GetBlueprintDefaultObject(const FString& Name, const ECsStringCompare& CompareType, UClass* InParentClass)
	{
		UBlueprint* Bp = GetAsset<UBlueprint>(Name, CompareType);

		return GetDefaultObject<T>(Bp, InParentClass);
	}

	template<typename T>
	static T* GetBlueprintDefaultObject(const FName& Name, const ECsStringCompare& CompareType, UClass* InParentClass)
	{
		return GetBlueprintDefaultObject<T>(Name.ToString(), CompareType, InParentClass);
	}

	template<typename T>
	static void GetBlueprintDefaultObjects(const FString& Name, const ECsStringCompare& CompareType, UClass* InParentClass, TArray<T*>& OutDefaultObjects)
	{
		TArray<UBlueprint*> OutAssets;
		GetAssets<UBlueprint>(Name, CompareType, OutAssets);

		OutDefaultObjects.Reset();

		UClass* ParentClass = InParentClass ? InParentClass : T::StaticClass();

		const int32 Count = OutAssets.Num();

		for (int32 I = 0; I < Count; ++I)
		{
			UBlueprint* Bp = Cast<UBlueprint>(OutAssets[I]);

			if (T* DOb = GetDefaultObject<T>(Bp, InParentClass))
				OutDefaultObjects.Add(DOb);
		}
	}

	template<typename T>
	static void GetBlueprintDefaultObjects(const FString& Name, const ECsStringCompare& CompareType, UClass* InParentClass, TArray<T*>& OutDefaultObjects, TArray<FString>& OutPackagePaths)
	{
		TArray<UBlueprint*> OutAssets;
		GetAssets<UBlueprint>(Name, CompareType, OutAssets, OutPackagePaths);

		OutDefaultObjects.Reset();

		UClass* ParentClass = InParentClass ? InParentClass : T::StaticClass();

		const int32 Count = OutAssets.Num();

		for (int32 I = 0; I < Count; ++I)
		{
			UBlueprint* Bp = Cast<UBlueprint>(OutAssets[I]);

			if (T* DOb = GetDefaultObject<T>(Bp, InParentClass))
				OutDefaultObjects.Add(DOb);
		}
	}

	template<typename T>
	static void GetBlueprintDefaultObjects(const TArray<FString>& KeywordsAND, const ECsStringCompare& CompareType, UClass* InParentClass, TArray<T*>& OutDefaultObjects)
	{
		TArray<UBlueprint*> OutAssets;
		GetAssets<UBlueprint>(KeywordsAND, OutAssets, CompareType);

		OutDefaultObjects.Reset();

		const int32 Count = OutAssets.Num();

		for (int32 I = 0; I < Count; ++I)
		{
			UBlueprint* Bp = Cast<UBlueprint>(OutAssets[I]);

			if (T* DOb = GetDefaultObject<T>(Bp, InParentClass))
				OutDefaultObjects.Add(DOb);
		}
	}

	static class ACsDataMapping* GetDataMapping();

	template<typename T>
	static T* GetDataMapping()
	{
		return Cast<T>(GetDataMapping());
	}

	static UCsEnumStructUserDefinedEnumMap* GetEnumStructUserDefinedEnumMap();

	template<typename T>
	static T* GetEnumStructUserDefinedEnumMap()
	{
		return Cast<T>(GetEnumStructUserDefinedEnumMap());
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