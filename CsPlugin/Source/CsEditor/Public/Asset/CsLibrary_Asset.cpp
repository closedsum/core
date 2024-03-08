// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Asset/CsLibrary_Asset.h"
#include "CsEditor.h"

// Types
#include "Load/CsObjectPathDependencyGroup.h"
#include "Types/Enum/CsEnumStructUserDefinedEnumMap.h"
// Library
	// Settings
#include "Settings/CsLibrary_DeveloperSettings.h"
// Data
#include "Engine/DataTable.h"
// Class
#include "UObject/Class.h"
// Asset
#include "AssetRegistry/AssetRegistryModule.h"
// Blueprint
#include "Engine/BlueprintGeneratedClass.h"
#include "Engine/BlueprintCore.h"
// Animation
#include "Animation/AnimCompositeBase.h"
#include "Animation/BlendSpace.h"
#include "Animation/AnimData/AnimDataModel.h"
// Font
#include "Engine/Font.h"
#include "Engine/FontFace.h"
// Material
#include "Materials/MaterialParameterCollection.h"
#include "Materials/MaterialFunction.h"
#include "Materials/MaterialInstance.h"
// FX
#include "NiagaraSystem.h"
#include "NiagaraEmitter.h"
#include "NiagaraScript.h"
#include "NiagaraParameterDefinitions.h"
// Sound
#include "Sound/SoundBase.h"
// Components
#include "Components/SkeletalMeshComponent.h"
#include "Components/PoseableMeshComponent.h"
// Engine
#include "Engine/UserDefinedEnum.h"
#include "Engine/UserDefinedStruct.h"
#include "Engine.h"
// Level Sequence
// Physics
#include "PhysicsEngine/PhysicsAsset.h"

#include "../Classes/Factories/AnimSequenceFactory.h"

#include "Developer/AssetTools/Public/IAssetTools.h"
#include "Editor/ContentBrowser/Public/IContentBrowserSingleton.h"

// TODO: Cleanup Headers

namespace NCsAsset
{
	namespace NLibrary
	{
		namespace NCached
		{
			namespace Str
			{
				const FString AssetPath_SlateCore = TEXT("/Script/SlateCore");
				const FString AssetPath_UMG = TEXT("/Script/UMG");
				const FString AssetPath_UMGEditor = TEXT("/Script/UMGEditor");
				const FString AssetPath_AudioEditor = TEXT("/Script/AudioEditor");
				const FString AssetPath_MovieSceneTracks= TEXT("/Script/MovieSceneTracks");
				const FString AssetPath_MovieSceneTools = TEXT("/Script/MovieSceneTools");
				const FString AssetPath_Niagara = TEXT("/Script/Niagara");
				const FString AssetPath_NiagaraEditor = TEXT("/Script/NiagaraEditor");
				const FString AssetPath_NavigationSystem = TEXT("/Script/NavigationSystem");
				const FString AssetPath_AnimGraph = TEXT("/Script/AnimGraph");
				const FString AssetPath_AnimGraphRuntime = TEXT("/Script/AnimGraphRuntime");
			}
		}
	}

	// Asset Registry
	#pragma region

	IAssetRegistry& FLibrary::GetAssetRegistry()
	{
		FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>(FName("AssetRegistry"));
		return AssetRegistryModule.Get();
	}

	UCsEnumStructUserDefinedEnumMap* FLibrary::GetEnumStructUserDefinedEnumMap()
	{
		// TODO: Make Name a Config variable for UCsEdEngine
		const FString Name					= TEXT("EnumStructUserDefinedEnumMap");
		const ECsStringCompare& CompareType = ECsStringCompare::Contains;
		TArray<UCsEnumStructUserDefinedEnumMap*> OutDefaultObjects;
		TArray<FString> OutPackagePaths;

		GetBlueprintDefaultObjects<UCsEnumStructUserDefinedEnumMap>(Name, CompareType, UCsEnumStructUserDefinedEnumMap::StaticClass(), OutDefaultObjects, OutPackagePaths);
	
		if (OutDefaultObjects.Num() == CS_EMPTY)
		{
			UE_LOG(LogCsEditor, Warning, TEXT("NCsAsset::FLibrary::GetEnumStructUserDefinedEnumMap: No class found of type: UCsEnumStructUserDefinedEnumMap."));
			return nullptr;
		}

		if (OutDefaultObjects.Num() > CS_SINGLETON)
		{
			UE_LOG(LogCsEditor, Warning, TEXT("NCsAsset::FLibrary::GetEnumStructUserDefinedEnumMap: More than ONE class found of type: UCsEnumStructUserDefinedEnumMap. Choosing the FICST one. There should only be ONE."));

			for (const FString& Path : OutPackagePaths)
			{
				UE_LOG(LogCsEditor, Warning, TEXT("NCsAsset::FLibrary::GetEnumStructUserDefinedEnumMap: Asset of type: UCsEnumStructUserDefinedEnumMap found at: %s."), *Path);
			}
		}
		return OutDefaultObjects[CS_EMPTY];
	}

	void FLibrary::SyncBrowserToAsset(UObject* InObject)
	{
		TArray<UObject*> ObjectsToSync;
		ObjectsToSync.Add(InObject);

		FContentBrowserModule& ContentBrowserModule = FModuleManager::LoadModuleChecked<FContentBrowserModule>("ContentBrowser");
		ContentBrowserModule.Get().SyncBrowserToAssets(ObjectsToSync);
	}

	void FLibrary::SyncBrowserToAssets(TArray<UObject*> Objects)
	{
		FContentBrowserModule& ContentBrowserModule = FModuleManager::LoadModuleChecked<FContentBrowserModule>("ContentBrowser");
		ContentBrowserModule.Get().SyncBrowserToAssets(Objects);
	}

	UFactory* FLibrary::GetFactory(UClass* ClassToSpawn)
	{
		for (TObjectIterator<UClass> It; It; ++It)
		{
			UClass* CurrentClass = *It;

			if (CurrentClass->IsChildOf(UFactory::StaticClass()) && !(CurrentClass->HasAnyClassFlags(CLASS_Abstract)))
			{
				UFactory* Factory = Cast<UFactory>(CurrentClass->GetDefaultObject());

				if (Factory->CanCreateNew() && Factory->ImportPriority >= 0 && Factory->SupportedClass == ClassToSpawn)
				{
					return Factory;
				}
			}
		}
		return nullptr;
	}

	UObject* FLibrary::CreateAsset(UClass* ClassToSpawn, const FString& Name, const FString &PackagePath)
	{
		FAssetToolsModule& AssetToolsModule = FModuleManager::GetModuleChecked<FAssetToolsModule>("AssetTools");
		UFactory* Factory					= GetFactory(ClassToSpawn);
		UObject* NewAsset					= AssetToolsModule.Get().CreateAsset(Name, PackagePath, ClassToSpawn, Factory);

		TArray<UObject*> ObjectsToSync;
		ObjectsToSync.Add(NewAsset);

		FContentBrowserModule& ContentBrowserModule = FModuleManager::LoadModuleChecked<FContentBrowserModule>("ContentBrowser");
		ContentBrowserModule.Get().SyncBrowserToAssets(ObjectsToSync);

		return NewAsset;
	}

	UAnimSequence* FLibrary::CreateAnimSequence(USkeletalMesh* Mesh, const FString &Name, const FString &PackagePath)
	{
		FAssetToolsModule& AssetToolsModule = FModuleManager::GetModuleChecked<FAssetToolsModule>("AssetTools");
		UAnimSequenceFactory* Factory		= NewObject<UAnimSequenceFactory>();

		Factory->TargetSkeleton		 = Mesh->GetSkeleton();
		Factory->PreviewSkeletalMesh = Mesh;

		UAnimSequence* NewAsset = Cast<UAnimSequence>(AssetToolsModule.Get().CreateAsset(Name, PackagePath, UAnimSequence::StaticClass(), Factory));;

		TArray<UObject*> ObjectsToSync;
		ObjectsToSync.Add(NewAsset);

		FContentBrowserModule& ContentBrowserModule = FModuleManager::LoadModuleChecked<FContentBrowserModule>("ContentBrowser");
		ContentBrowserModule.Get().SyncBrowserToAssets(ObjectsToSync);
	
		return NewAsset;
	}

	void FLibrary::InitAnimSequence(UAnimSequence* Anim, USkeletalMeshComponent* Mesh)
	{
		check(0);
		//Anim->RecycleAnimSequence();

		USkeleton* AnimSkeleton     = Anim->GetSkeleton();
		USkeletalMesh* SkeletalMesh = Mesh->GetSkeletalMeshAsset();

		const int32 BoneCount = Mesh->GetComponentSpaceTransforms().Num();

		for (int32 BoneIndex = 0; BoneIndex < BoneCount; ++BoneIndex)
		{
			// verify if this bone exists in skeleton
			const int32 BoneTreeIndex = AnimSkeleton->GetSkeletonBoneIndexFromMeshBoneIndex(SkeletalMesh, BoneIndex);
			if (BoneTreeIndex != INDEX_NONE)
			{
				// add tracks for the bone existing
				FName BoneTreeName = AnimSkeleton->GetReferenceSkeleton().GetBoneName(BoneTreeIndex);
				check(0);
				//Anim->AddNewRawTrack(BoneTreeName);
			}
		}

		// Setup notifies
		Anim->InitializeNotifyTrack();
	}

	void FLibrary::InitAnimSequence(UAnimSequence* Anim, UPoseableMeshComponent* Mesh)
	{
		check(0);
		//Anim->RecycleAnimSequence();

		USkeleton* AnimSkeleton     = Anim->GetSkeleton();
		USkeletalMesh* SkeletalMesh = Cast<USkeletalMesh>(Mesh->GetSkinnedAsset());

		const int32 BoneCount = Mesh->BoneSpaceTransforms.Num();

		for (int32 BoneIndex = 0; BoneIndex < BoneCount; ++BoneIndex)
		{
			// verify if this bone exists in skeleton
			const int32 BoneTreeIndex = AnimSkeleton->GetSkeletonBoneIndexFromMeshBoneIndex(SkeletalMesh, BoneIndex);
			if (BoneTreeIndex != INDEX_NONE)
			{
				// add tracks for the bone existing
				FName BoneTreeName = AnimSkeleton->GetReferenceSkeleton().GetBoneName(BoneTreeIndex);
				check(0);
				//Anim->AddNewRawTrack(BoneTreeName);
			}
		}

		// Setup notifies
		Anim->InitializeNotifyTrack();
	}

	#pragma endregion Asset Registry

	// Find
	#pragma region

	void FLibrary::FindObjectsByClass(const FName& ClassName, const FName& ObjectName, TArray<UObject*>& OutObjects)
	{
		FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>(FName("AssetRegistry"));
		IAssetRegistry& AssetRegistry			  = AssetRegistryModule.Get();
		TArray<FAssetData> AssetDatas;

		// TODO: FIX
		check(0);
		//AssetRegistry.GetAssetsByClass(ClassName, AssetDatas);

		for (FAssetData& Data : AssetDatas)
		{
			if (Data.AssetName == ObjectName)
			{
				OutObjects.Add(Data.GetAsset());
			}
		}
	}

	UObject* FLibrary::FindObjectByClass(const FName& ClassName, const FName& ObjectName, const ECsFindObjectByClassRule& Rule /*= ECsFindObjectByClassRule::None*/)
	{
		// None | First
		if (Rule == ECsFindObjectByClassRule::None ||
			Rule == ECsFindObjectByClassRule::First)
		{
			FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>(FName("AssetRegistry"));
			IAssetRegistry& AssetRegistry			  = AssetRegistryModule.Get();
			TArray<FAssetData> AssetDatas;

			// TODO: FIX
			check(0);
			//AssetRegistry.GetAssetsByClass(ClassName, AssetDatas);

			UObject* Object = nullptr;

			for (FAssetData& Data : AssetDatas)
			{
				if (Data.AssetName == ObjectName)
				{
					Object = Data.GetAsset();
				}
			}

			if (Rule == ECsFindObjectByClassRule::First)
			{
				if (!Object)
				{
					UE_LOG(LogCsEditor, Warning, TEXT("NCsAsset::FLibrary::FindObjectByClass: Failed to find %s with name: %s."), *(ClassName.ToString()), *(ObjectName.ToString()));
				}
			}
			return Object;
		}
		// Exact
		if (Rule == ECsFindObjectByClassRule::Exact)
		{
			TArray<UObject*> Objects;
			FindObjectsByClass(ClassName, ObjectName, Objects);

			// Check if NO Objects were found
			if (Objects.Num() == CS_EMPTY)
			{
				UE_LOG(LogCsEditor, Warning, TEXT("NCsAsset::FLibrary::FindObjectByClass: Failed to find %s with name: %s."), *(ClassName.ToString()), *(ObjectName.ToString()));
				return nullptr;
			}
			// Check if only ONE Object was found
			if (Objects.Num() != CS_SINGLETON)
			{
				UE_LOG(LogCsEditor, Warning, TEXT("NCsAsset::FLibrary::FindObjectByClass: Found more than one %s with name: %s."), *(ClassName.ToString()), *(ObjectName.ToString()));
				return nullptr;
			}
			return Objects[CS_FIRST];
		}
		return nullptr;
	}

	#pragma endregion Find

	namespace NDependency
	{
		namespace NSoftPath
		{	
			bool FLibrary::IsValidPath(const FSoftObjectPath& Path)
			{
				using namespace NCsAsset::NLibrary::NCached;
				
				if (!Path.IsValid())
					return false;

				const FString& AssetPath = Path.ToString();

				if (AssetPath == Str::AssetPath_SlateCore)
					return false;
				if (AssetPath == Str::AssetPath_UMG)
					return false;
				if (AssetPath == Str::AssetPath_UMGEditor)
					return false;
				if (AssetPath == Str::AssetPath_AudioEditor)
					return false;
				if (AssetPath == Str::AssetPath_MovieSceneTracks)
					return false;
				if (AssetPath == Str::AssetPath_MovieSceneTools)
					return false;
				if (AssetPath == Str::AssetPath_Niagara)
					return false;
				if (AssetPath == Str::AssetPath_NiagaraEditor)
					return false;
				if (AssetPath == Str::AssetPath_NavigationSystem)
					return false;
				if (AssetPath == Str::AssetPath_AnimGraph)
					return false;
				if (AssetPath == Str::AssetPath_AnimGraphRuntime)
					return false;

				typedef NCsCore::NSettings::FLibrary SettingsLibrary;

				const TArray<FString>& IgnoreAssetPaths = SettingsLibrary::GetIgnoreAssetPaths();

				for (const FString& IgnoreAssetPath : IgnoreAssetPaths)
				{
					if (AssetPath == IgnoreAssetPath)
						return false;
				}
				return true;
			}

			UClass* FLibrary::GetClass(const FSoftObjectPath& Path)
			{
				if (IsValidPath(Path))
				{
					UObject* O = Path.TryLoad();

					if (!O)
						return nullptr;

					return O->GetClass();
				}
				return nullptr;
			}

			void FLibrary::GetObjectAndClass(const FSoftObjectPath& Path, UObject*& O, UClass*& Class)
			{
				O	  = nullptr;
				Class = nullptr;

				if (IsValidPath(Path))
				{
					O = Path.TryLoad();

					if (!O)
						return;

					Class = O->GetClass();
				}
			}

			FLibrary::FGet::FResult::FResult() :
				Paths(),
				PathSet(),
				PathsByGroup(),
				PathSetsByGroup()
			{
				typedef EMCsObjectPathDependencyGroup GroupMapType;
				typedef ECsObjectPathDependencyGroup GroupType;

				const int32& Count = GroupMapType::Get().Num();

				PathsByGroup.Reset(Count);
				PathSetsByGroup.Reset(Count);

				for (const GroupType& Group : GroupMapType::Get())
				{
					PathsByGroup.AddDefaulted();
					PathSetsByGroup.AddDefaulted();
				}
			}

			bool FLibrary::FGet::FResult::AddPathToGroup(const FSoftObjectPath& Path)
			{
				using namespace NCsAsset::NLibrary::NCached;

				UObject* O = nullptr;
				UClass* Class = nullptr;
				
				GetObjectAndClass(Path, O, Class);

				if (!Class)
					return false;

				typedef ECsObjectPathDependencyGroup GroupType;

				// DataTable
				if (Class->IsChildOf<UDataTable>())
				{
					PathSetsByGroup[(uint8)GroupType::DataTable].Add(Path);
				}
				// Sequencer
				/*
				else
				if (Class->IsChildOf<UMovieSceneSequencePlayer>() ||
					Class->ImplementsInterface(UMovieScenePlaybackClient::StaticClass()) ||
					Class->ImplementsInterface(UMovieSceneBindingOwnerInterface::StaticClass()) ||
					Class->IsChildOf<UMovieSceneSignedObject>())
				{
					DependencySetList[(uint8)ECsObjectPathDependencyGroup::Sequencer].Add(SoftPath);
				}
				*/
				// Blueprint
				else
				if (Class->HasAnyCastFlag(EClassCastFlags::CASTCLASS_UBlueprint))
				{
					PathSetsByGroup[(uint8)GroupType::Blueprint].Add(Path);
				}
				else
				if (Class->HasAnyClassFlags(EClassFlags::CLASS_CompiledFromBlueprint) ||
					Class->IsChildOf<UBlueprintGeneratedClass>())
				{
					// Check for SkeletonGeneratedClasses. Skip adding the path.
					if (UBlueprintGeneratedClass* BpGC = Cast<UBlueprintGeneratedClass>(O))
					{
					#if WITH_EDITOR
						if (UBlueprintCore* BpC = Cast<UBlueprintCore>(BpGC->ClassGeneratedBy))
						{
							if (O == BpC->SkeletonGeneratedClass)
							{
								return false;
							}
						}
					#endif // #if WITH_EDITOR
					}

					if (UBlueprintGeneratedClass* BpGC = Cast<UBlueprintGeneratedClass>(Class))
					{
					#if WITH_EDITOR
						if (UBlueprintCore* BpC = Cast<UBlueprintCore>(BpGC->ClassGeneratedBy))
						{
							if (Class == BpC->SkeletonGeneratedClass)
							{
								return false;
							}
						}
					#endif // #if WITH_EDITOR
					}

					PathSetsByGroup[(uint8)GroupType::Blueprint].Add(Path);
				}
				// AnimComposite
				else
				if (Class->IsChildOf<UAnimCompositeBase>())
				{
					PathSetsByGroup[(uint8)GroupType::AnimComposite].Add(Path);
				}
				// BlendSpace
				else
				if (Class->IsChildOf<UBlendSpace>())
				{
					PathSetsByGroup[(uint8)GroupType::BlendSpace].Add(Path);
				}
				// AnimationAsset
				else
				if (Class->IsChildOf<UAnimSequence>())
				{
					PathSetsByGroup[(uint8)GroupType::AnimationAsset].Add(Path);
				}
				// AnimData - SKIP
				else
				if (Class->IsChildOf<UAnimDataModel>())
				{
					return false;
				}
				// FX
				else
				if (Class->IsChildOf<UNiagaraSystem>())
				{
					PathSetsByGroup[(uint8)GroupType::FX].Add(Path);
				}
				// FX - SKIP - IGNORE. 
				//	NOTE: 4.26. Niagara Emitter no longer get cooked
				else
				if (Class->IsChildOf<UNiagaraEmitter>() ||
					Class->IsChildOf<UNiagaraScript>() ||
					Class->IsChildOf<UNiagaraParameterDefinitions>())
				{
					return false;
				}
				// Sound
				else
				if (Class->IsChildOf<USoundBase>())
				{
					PathSetsByGroup[(uint8)GroupType::Sound].Add(Path);
				}
				// Skeletal
				else
				if (Class->IsChildOf<USkeletalMesh>() ||
					Class->IsChildOf<UPhysicsAsset>() ||
					Class->IsChildOf<USkeleton>())
				{
					PathSetsByGroup[(uint8)GroupType::Skeletal].Add(Path);
				}
				// StaticMesh
				else
				if (Class->IsChildOf<UStaticMesh>())
				{
					PathSetsByGroup[(uint8)GroupType::StaticMesh].Add(Path);
				}
				// Material Parameter Collection
				else
				if (Class->IsChildOf<UMaterialParameterCollection>())
				{
					PathSetsByGroup[(uint8)GroupType::MaterialParameterCollection].Add(Path);
				}
				// Material Function
				else
				if (Class->IsChildOf<UMaterialFunction>())
				{
					PathSetsByGroup[(uint8)GroupType::MaterialFunction].Add(Path);
					//return false;
				}
				// Material
				else
				if (Class->IsChildOf<UMaterial>())
				{
					PathSetsByGroup[(uint8)GroupType::Material].Add(Path);
				}
				// Material Instance
				else
				if (Class->IsChildOf<UMaterialInstance>())
				{
					PathSetsByGroup[(uint8)GroupType::MaterialInstance].Add(Path);
				}
				// Font | Font Face
				else
				if (Class->IsChildOf<UFont>() ||
					Class->IsChildOf<UFontFace>())
				{
					PathSetsByGroup[(uint8)GroupType::Font].Add(Path);
				}
				// Texture
				else
				if (Class->IsChildOf<UTexture>())
				{
					PathSetsByGroup[(uint8)GroupType::Texture].Add(Path);
				}
				// Enum
				else
				if (Class->IsChildOf<UUserDefinedEnum>())
				{
					PathSetsByGroup[(uint8)GroupType::Enum].Add(Path);
				}
				// Other
				else
				{
					PathSetsByGroup[(uint8)GroupType::Other].Add(Path);
				}
				return true;
			}

			void FLibrary::FGet::FResult::Resolve()
			{
				Paths.Reset(PathSet.Num());

				for (const FSoftObjectPath& Path : PathSet)
				{
					const bool Success = AddPathToGroup(Path);

					if (Success)
						Paths.Add(Path);
				}

				PathSet.Reset();

				for (const FSoftObjectPath& Path : Paths)
				{
					PathSet.Add(Path);
				}

				const int32 Count = PathSetsByGroup.Num();

				for (int32 I = 0; I < Count; ++I)
				{
					const TSet<FSoftObjectPath>& Set = PathSetsByGroup[I];
					TArray<FSoftObjectPath>& Arr	 = PathsByGroup[I];

					Arr.Reset(Set.Num());

					for (const FSoftObjectPath& Path : Set)
					{
						Arr.Add(Path);
					}
				}
			}

			#define ResultType NCsAsset::NDependency::NSoftPath::FLibrary::FGet::FResult

			void FLibrary::Get_Internal(const void* StructValue, UStruct* const& Struct, ResultType& OutResult)
			{
				for (TFieldIterator<FProperty> It(Struct); It; ++It)
				{
					FProperty* Property = CastField<FProperty>(*It);

					const FString PropertyName = Property->GetName();
		
					// Object
					if (FObjectProperty* ObjectProperty = CastField<FObjectProperty>(Property))
					{
						// DataTable
						if (ObjectProperty->PropertyClass == UDataTable::StaticClass())
						{
							UDataTable* const* DataTablePtr = ObjectProperty->ContainerPtrToValuePtr<UDataTable*>(StructValue);
				
							if (UDataTable* DataTable = *DataTablePtr)
							{
								const FSoftObjectPath ObjectPath = FSoftObjectPath(DataTable);

								OutResult.AddPath(FName(ObjectPath.ToString()));

								// Check each row for any Object Paths
								const UScriptStruct* ScriptStruct = DataTable->GetRowStruct();
								UScriptStruct* Temp				  = const_cast<UScriptStruct*>(ScriptStruct);
								UStruct* const RowStruct		  = Temp;

								TArray<FName> RowNames = DataTable->GetRowNames();

								for (const FName& RowName : RowNames)
								{
									uint8* RowPtr = DataTable->FindRowUnchecked(RowName);

									Get_Internal(RowPtr, RowStruct, OutResult);
								}
							}
						}
						continue;
					}
					// SoftClass
					if (FSoftClassProperty* SoftClassProperty = CastField<FSoftClassProperty>(Property))
					{
						if (const FSoftObjectPtr* Ptr = SoftClassProperty->GetPropertyValuePtr_InContainer(StructValue))
						{
							const FSoftObjectPath ObjectPath = Ptr->ToSoftObjectPath();

							if (ObjectPath.IsValid())
							{
								OutResult.AddPath(FName(ObjectPath.ToString()));

								FAssetRegistryModule& AssetRegistryModule = FModuleManager::GetModuleChecked<FAssetRegistryModule>("AssetRegistry");
								TArray<FName> Dependencies;

								AssetRegistryModule.Get().GetDependencies(ObjectPath.GetLongPackageFName(), Dependencies);
								OutResult.AddPaths(Dependencies);
							}
						}
						continue;
					}
					// SoftObject
					if (FSoftObjectProperty* SoftObjectProperty = CastField<FSoftObjectProperty>(Property))
					{
						if (const FSoftObjectPtr* Ptr = SoftObjectProperty->GetPropertyValuePtr_InContainer(StructValue))
						{
							const FSoftObjectPath ObjectPath = Ptr->ToSoftObjectPath();

							if (ObjectPath.IsValid())
							{
								if (UObject* O = Ptr->LoadSynchronous())
								{
									OutResult.AddPath(FName(ObjectPath.ToString()));

									if (UDataTable* DataTable = Cast<UDataTable>(O))
									{
										// Check each row for any Object Paths
										const UScriptStruct* ScriptStruct = DataTable->GetRowStruct();
										UScriptStruct* Temp				  = const_cast<UScriptStruct*>(ScriptStruct);
										UStruct* const RowStruct		  = Temp;

										TArray<FName> RowNames = DataTable->GetRowNames();

										for (const FName& RowName : RowNames)
										{
											uint8* RowPtr = DataTable->FindRowUnchecked(RowName);

											Get_Internal(RowPtr, RowStruct, OutResult);
										}
									}
									else
									{
										FAssetRegistryModule& AssetRegistryModule = FModuleManager::GetModuleChecked<FAssetRegistryModule>("AssetRegistry");
										TArray<FName> Dependencies;

										AssetRegistryModule.Get().GetDependencies(ObjectPath.GetLongPackageFName(), Dependencies);
										OutResult.AddPaths(Dependencies);
									}
								}
							}
						}
						continue;
					}
					// Struct
					if (FStructProperty* StructProperty = CastField<FStructProperty>(Property))
					{
						for (int32 I = 0; I < StructProperty->ArrayDim; ++I)
						{
							if (const uint8* Ptr = StructProperty->ContainerPtrToValuePtr<uint8>(StructValue, I))
							{
								Get_Internal(Ptr, StructProperty->Struct, OutResult);
							}
						}
						continue;
					}
		
					// Array
					if (FArrayProperty* ArrayProperty = CastField<FArrayProperty>(Property))
					{
						FScriptArrayHelper_InContainer Helper(ArrayProperty, StructValue);

						const int32 Count = Helper.Num();

						for (int32 I = 0; I < Count; ++I)
						{
							uint8* Ptr = Helper.GetRawPtr(I);

							// SoftClass
							if (FSoftClassProperty* InnerSoftClassProperty = CastField<FSoftClassProperty>(ArrayProperty->Inner))
							{
								TSoftClassPtr<UObject>* ObjectPtr = reinterpret_cast<TSoftClassPtr<UObject>*>(Helper.GetRawPtr(I));
								const FSoftObjectPath ObjectPath  = ObjectPtr->ToSoftObjectPath();

								if (ObjectPath.IsValid())
								{
									OutResult.AddPath(FName(ObjectPath.ToString()));

									FAssetRegistryModule& AssetRegistryModule = FModuleManager::GetModuleChecked<FAssetRegistryModule>("AssetRegistry");
									TArray<FName> Dependencies;

									AssetRegistryModule.Get().GetDependencies(ObjectPath.GetLongPackageFName(), Dependencies);
									OutResult.AddPaths(Dependencies);
								}
								continue;
							}
							// SoftObject
							if (FSoftObjectProperty* InnerSoftObjectProperty = CastField<FSoftObjectProperty>(ArrayProperty->Inner))
							{
								TSoftObjectPtr<UObject>* ObjectPtr = reinterpret_cast<TSoftObjectPtr<UObject>*>(Helper.GetRawPtr(I));
								const FSoftObjectPath ObjectPath   = ObjectPtr->ToSoftObjectPath();

								if (ObjectPath.IsValid())
								{
									if (UObject* O = ObjectPtr->LoadSynchronous())
									{
										OutResult.AddPath(FName(ObjectPath.ToString()));
										
										if (UDataTable* DataTable = Cast<UDataTable>(O))
										{
											// Check each row for any Object Paths
											const UScriptStruct* ScriptStruct = DataTable->GetRowStruct();
											UScriptStruct* Temp				  = const_cast<UScriptStruct*>(ScriptStruct);
											UStruct* const RowStruct		  = Temp;

											TArray<FName> RowNames = DataTable->GetRowNames();

											for (const FName& RowName : RowNames)
											{
												uint8* RowPtr = DataTable->FindRowUnchecked(RowName);

												Get_Internal(RowPtr, RowStruct, OutResult);
											}
										}
										else
										{
											FAssetRegistryModule& AssetRegistryModule = FModuleManager::GetModuleChecked<FAssetRegistryModule>("AssetRegistry");
											TArray<FName> Dependencies;

											AssetRegistryModule.Get().GetDependencies(ObjectPath.GetLongPackageFName(), Dependencies);
											OutResult.AddPaths(Dependencies);
										}
									}
								}
								continue;
							}
							// Struct
							if (FStructProperty* InnerStructProperty = CastField<FStructProperty>(ArrayProperty->Inner))
							{
								Get_Internal(Ptr, InnerStructProperty->Struct, OutResult);
								continue;
							}
						}
						continue;
					}
				}
			}

			void FLibrary::Get(const void* StructValue, UStruct* const& Struct, const int32& Depth, ResultType& OutResult)
			{
				Get_Internal(StructValue, Struct, OutResult);

				FAssetRegistryModule& AssetRegistryModule = FModuleManager::GetModuleChecked<FAssetRegistryModule>("AssetRegistry");

				TArray<FName> Dependencies_Total;

				for (const FSoftObjectPath& Path : OutResult.PathSet)
				{
					TArray<FName> Dependencies;
					AssetRegistryModule.Get().GetDependencies(Path.GetLongPackageFName(), Dependencies);
					Dependencies_Total.Append(Dependencies);
				}

				int32 Count = 2;
				TArray<FName> Dependencies_Depth_Current = Dependencies_Total;

				while (Count < Depth)
				{
					TArray<FName> Dependencies_Depth_Added;

					for (const FName& Path : Dependencies_Depth_Current)
					{
						TArray<FName> Dependencies;
						AssetRegistryModule.Get().GetDependencies(Path, Dependencies);
						Dependencies_Depth_Added.Append(Dependencies);
						Dependencies_Total.Append(Dependencies);
					}
					
					Dependencies_Depth_Current = Dependencies_Depth_Added;
					++Count;
				}

				for (const FName& Path : Dependencies_Total)
				{
					OutResult.PathSet.Add(FSoftObjectPath(Path.ToString()));
				}

				OutResult.Resolve();
			}

			#undef ResultType

			void FLibrary::DataTable_CheckAndAdd(const FSoftObjectPath& Path, TArray<FName>& Dependecies)
			{
				if (UClass* Class = GetClass(Path))
				{
					if (Class->IsChildOf<UDataTable>())
					{
						FAssetRegistryModule& AssetRegistryModule = FModuleManager::GetModuleChecked<FAssetRegistryModule>("AssetRegistry");

						TArray<FName> AdditionalDependencies;
						AssetRegistryModule.Get().GetDependencies(Path.GetLongPackageFName(), AdditionalDependencies);
						Dependecies.Append(AdditionalDependencies);
					}
				}
			}
		}
	}
}