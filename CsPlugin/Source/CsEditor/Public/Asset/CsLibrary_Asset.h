// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Types/CsTypes_String.h"

#include "AssetRegistry/AssetRegistryModule.h"
#include "Developer/AssetTools/Public/AssetToolsModule.h"
#include "Editor/ContentBrowser/Public/ContentBrowserModule.h"
#include "Editor/ContentBrowser/Public/IContentBrowserSingleton.h"

#include "Factories/BlueprintFactory.h"

// Enums
#pragma region

enum class ECsFindObjectByClassRule : uint8
{
	/** No logging. */
	None,
	/** Find first that matches the input with logging. */
	First,
	/** Find an exact match from the input with logging. */
	Exact,
	ECsFindObjectByClassRule_MAX
};

#pragma endregion Enums

class UCsEnumStructUserDefinedEnumMap;
class UCsDataMapping;

class UAnimSequence;
class USkeletalMesh;
class USkeletalMeshComponent;
class UPoseableMeshComponent;

class UClass;

namespace NCsAsset
{
	struct CSEDITOR_API FLibrary
	{
	// Asset Registry
	#pragma region
	public:

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
			// TODO: FIX
			check(0);
			//AssetRegistry.GetAssetsByClass(T::StaticClass()->GetFName(), OutAssetData);

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

			// TODO: FIX
			check(0);
			//AssetRegistry.GetAssetsByClass(T::StaticClass()->GetFName(), OutAssetDatas);

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
					return Cast<T>(OutAssetDatas[I].GetAsset());
			}
			return nullptr;
		}

		template<typename T>
		static void GetAssets(const FString& Name, const ECsStringCompare& CompareType, TArray<T*>& OutAssets)
		{
			OutAssets.Reset();

			IAssetRegistry& AssetRegistry = GetAssetRegistry();

			TArray<FAssetData> OutAssetData;

			// TODO: FIX
			check(0);
			//AssetRegistry.GetAssetsByClass(T::StaticClass()->GetFName(), OutAssetData);

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

			// TODO: FIX
			check(0);
			//AssetRegistry.GetAssetsByClass(T::StaticClass()->GetFName(), OutAssetData);

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
					Pass &= NCsStringCompare::Compare(AssetStringName, KeywordsANDLower[J], CompareType);

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

			// TODO: FIX
			check(0);
			//AssetRegistry.GetAssetsByClass(T::StaticClass()->GetFName(), OutAssetData);

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

			// TODO: FIX
			check(0);
			//AssetRegistry.GetAssetsByClass(T::StaticClass()->GetFName(), OutAssetData);

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
			GetAssets<UBlueprint>(KeywordsAND, CompareType, OutAssets);

			OutDefaultObjects.Reset();

			const int32 Count = OutAssets.Num();

			for (int32 I = 0; I < Count; ++I)
			{
				UBlueprint* Bp = Cast<UBlueprint>(OutAssets[I]);

				if (T* DOb = GetDefaultObject<T>(Bp, InParentClass))
					OutDefaultObjects.Add(DOb);
			}
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

		static class UAnimSequence* CreateAnimSequence(USkeletalMesh* Mesh, const FString &Name, const FString &PackagePath);
		static void InitAnimSequence(UAnimSequence* Anim, USkeletalMeshComponent* Mesh);
		static void InitAnimSequence(UAnimSequence* Anim, UPoseableMeshComponent* Mesh);

	#pragma endregion Asset Registry

	// Find
	#pragma region
	public:

		static void FindObjectsByClass(const FName& ClassName, const FName& ObjectName, TArray<UObject*>& OutObjects);

		static UObject* FindObjectByClass(const FName& ClassName, const FName& ObjectName, const ECsFindObjectByClassRule& Rule = ECsFindObjectByClassRule::None);

		template<typename T>
		static T* FindObjectByClass(const FName& ClassName, const FName& ObjectName, const ECsFindObjectByClassRule& Rule = ECsFindObjectByClassRule::None)
		{
			return Cast<T>(FindObjectByClass(ClassName, ObjectName, Rule));
		}

	#pragma endregion Find
	};
}

namespace NCsAsset
{
	namespace NDependency
	{
		namespace NSoftPath
		{
			struct CSEDITOR_API FLibrary
			{
			public:

				static bool IsValidPath(const FSoftObjectPath& Path);
				FORCEINLINE static bool IsValidPath(const FName& Path)
				{
					return IsValidPath(FSoftObjectPath(Path.ToString()));
				}

				static UClass* GetClass(const FSoftObjectPath& Path);

				static void GetObjectAndClass(const FSoftObjectPath& Path, UObject*& O, UClass*& Class);

				struct FGet
				{
				public:

					struct FResult
					{
					public:

						TArray<FSoftObjectPath> Paths;
						TSet<FSoftObjectPath> PathSet;
						// [Group][Paths as Array]
						TArray<TArray<FSoftObjectPath>> PathsByGroup;
						// [Group][Paths as Set]
						TArray<TSet<FSoftObjectPath>> PathSetsByGroup;

						FResult();

						void AddPath(const FName& Path) 
						{ 
							PathSet.Add(FSoftObjectPath(Path.ToString()));
						}

						void AddPaths(const TArray<FName>& Dependecies)
						{
							for (const FName& Path : Dependecies)
							{
								PathSet.Add(FSoftObjectPath(Path.ToString()));
							}
						}

						bool AddPathToGroup(const FSoftObjectPath& Path);

						void Resolve();
					};
				};

			using ResultType = NCsAsset::NDependency::NSoftPath::FLibrary::FGet::FResult;

			private:

				static void Get_Internal(const void* StructValue, UStruct* const& Struct, ResultType& OutResult);

			public:

				static void Get(const void* StructValue, UStruct* const& Struct, const int32& Depth, ResultType& OutResult);
				
				static void DataTable_CheckAndAdd(const FSoftObjectPath& Path, TArray<FName>& Dependecies);
			};
		}
	}
}