// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Types/Enum/Tool/CsEnumStructLayoutTool.h"
#include "CsEditor.h"

// Types
#include "Data/CsTypes_DataEntry.h"
// Library
	// Settings
#include "Settings/CsLibrary_DeveloperSettings.h"
	// Common
#include "Library/CsLibrary_Blueprint.h"
#include "Library/CsLibrary_Property.h"
// Package
#include "Misc/PackageName.h"
// Editor
#include "Toolkits/AssetEditorToolkit.h"
#include "LevelEditorSubsystem.h"
#include "Subsystems/EditorActorSubsystem.h"
#include "LevelEditor.h"
// Engine
#include "Engine/Engine.h"

#include "Framework/Docking/TabManager.h"

namespace NCsEnum
{
	namespace NStruct
	{
		namespace NLayout
		{
			namespace NTool
			{
				namespace NCached
				{
					namespace Str
					{
						CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsEnum::NStruct::NLayout::FTool, DetermineChanges);
						CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsEnum::NStruct::NLayout::FTool, ResolveChanges);

						const FString DirectorBP = TEXT("(Director BP)");
					}
				}
			}

			#define USING_NS_CACHED using namespace NCsEnum::NStruct::NLayout::NTool::NCached;
			#define SET_CONTEXT(__FunctionName) using namespace NCsEnum::NStruct::NLayout::NTool::NCached; \
				const FString& Context = Str::__FunctionName

			#define SettingsLibrary NCsCore::NSettings::FLibrary
			#define BlueprintLibrary NCsBlueprint::FLibrary
			#define PropertyLibrary NCsProperty::FLibrary
			
			/*static*/ void FTool::DetermineChanges(TMap<FName, UStruct*>& OutStructMap)
			{
				SET_CONTEXT(DetermineChanges);

				TMap<FName, FCsEnumStructLayoutHistory>& EnumStructlayoutHistoryMap = SettingsLibrary::GetEnumStructlayoutHistoryMap();

				FName EnumName = NAME_None;
				TArray<FName> Names;
				UStruct* Struct = nullptr;

				#define ADD_ENUM_STRUCT(__Enum_Namespace) __Enum_Namespace::ConditionalAddLayout(); \
					__Enum_Namespace::GetNames(EnumName, Names); \
					Struct = __Enum_Namespace::GetStruct(); \
					EnumStructlayoutHistoryMap[EnumName].DetermineChange(Names); \
					OutStructMap.Add(EnumName, Struct)

				// FECsDataEntryData
				ADD_ENUM_STRUCT(NCsDataEntryData);

				#undef ADD_ENUM_STRUCT
			}

			/*static*/ void FTool::ResolveChanges(const TMap<FName, UStruct*>& StructMap, bool bForce /*=false*/)
			{
				SET_CONTEXT(ResolveChanges);

				// TODO: Properly handle this
				if (StructMap.Num() == CS_EMPTY)
					return;

				UAssetEditorSubsystem* AssetEditorSubsystem = GEditor->GetEditorSubsystem<UAssetEditorSubsystem>();

				TMap<FName, FCsEnumStructLayoutHistory>& EnumStructlayoutHistoryMap = SettingsLibrary::GetEnumStructlayoutHistoryMap();

				for (TPair<FName, FCsEnumStructLayoutHistory>& Pair : EnumStructlayoutHistoryMap)
				{
					const FName& EnumName				= Pair.Key;
					FCsEnumStructLayoutHistory& History = Pair.Value;

					UStruct* const* StructPtr = StructMap.Find(EnumName);

					if (!StructPtr)
						continue;

					const UStruct* Struct = *StructPtr;

					if (bForce || History.HasChanged())
					{
						TSet<FSoftObjectPath>& References = History.References;

						TSet<FSoftObjectPath> ToRemove;
						ToRemove.Reserve(References.Num());

						for (const FSoftObjectPath& Path : References)
						{
							// Check Path is Valid for the Enum Struct

							// If NOT Valid, remove
							if (!Path.IsValid())
							{
								UE_LOG(LogCsEditor, Warning, TEXT("%s: Reference Path is NOT Valid."), *Context);
								ToRemove.Add(Path);
								continue;
							}
							else
							if (Path.IsSubobject())
							{
								// Director BP
								if (Path.GetSubPathString().Contains(Str::DirectorBP))
								{
									UObject* Object = Path.TryLoad();

									if (Object)
									{
										// Blueprint
										if (BlueprintLibrary::Is(Object))
										{
											if (UObject* CDOb = BlueprintLibrary::GetSafeClassDefaultObject(Context, Object, nullptr))
											{	
												if (PropertyLibrary::HasStructProperty(Context, CDOb->GetClass(), Struct, nullptr))
												{
													if (AssetEditorSubsystem->OpenEditorForAsset(Object))
													{		
														AssetEditorSubsystem->CloseAllEditorsForAsset(Object);
													}
													else
													{
														UE_LOG(LogCsEditor, Warning, TEXT("%s: Failed to Open Asset at Path: %s."), *Context, *(Path.ToString()));
														ToRemove.Add(Path);
														continue;
													}
												}
												else
												{
													UE_LOG(LogCsEditor, Warning, TEXT("%s: Object at Path: %s no longer as reference to a struct of type: %s."), *Context, *(Path.ToString()), *(Struct->GetName()));
													ToRemove.Add(Path);
													continue;
												}
											}
										}
										else
										{
											UE_LOG(LogCsEditor, Warning, TEXT("%s: Object at Path: %s is no longer a blueprint."), *Context, *(Path.ToString()));
											ToRemove.Add(Path);
											continue;
										}
									}
									else
									{
										UE_LOG(LogCsEditor, Warning, TEXT("%s: Failed to Load Object at Path: %s."), *Context, *(Path.ToString()));
										ToRemove.Add(Path);
										continue;
									}
								}
								// Level
								// For now, assume a Reference with a SubPath is an object in a Level
								else
								{
									FLevelEditorModule& LevelEditorModule = FModuleManager::GetModuleChecked<FLevelEditorModule>("LevelEditor");

									FGlobalTabmanager::Get()->DrawAttentionToTabManager(LevelEditorModule.GetLevelEditorTabManager().ToSharedRef());

									ULevelEditorSubsystem* LevelEditorSubsystem = GEditor->GetEditorSubsystem<ULevelEditorSubsystem>();

									// Cache Current Level
									ULevel* CurrentLevel = LevelEditorSubsystem->GetCurrentLevel();

									FSoftObjectPath CurrentLevelPath(CurrentLevel);
								
									// Check if Current Level == Level to Load
									const FString CurrentLevelAssetPath = CurrentLevelPath.GetLongPackageName();
									const FString AssetPath				= Path.GetLongPackageName();

									bool bLoadLevel = CurrentLevelAssetPath != AssetPath;

									if (bLoadLevel)
									{
										LevelEditorSubsystem->LoadLevel(AssetPath);
									}

									// Select Actor in Level
									FString SubPath = Path.GetSubPathString();

									UEditorActorSubsystem* EditorActorSubsystem = GEditor->GetEditorSubsystem<UEditorActorSubsystem>();

									AActor* Actor = EditorActorSubsystem->GetActorReference(SubPath);

									if (!Actor)
									{
										UE_LOG(LogCsEditor, Warning, TEXT("%s: Failed to find Actor at SubPath: %s for Level @ %s."), *Context, *SubPath, *AssetPath);
										ToRemove.Add(Path);
										continue;
									}

									TArray<AActor*> ActorsToSelect;
									ActorsToSelect.Add(Actor);

									EditorActorSubsystem->SetSelectedLevelActors(ActorsToSelect);
									EditorActorSubsystem->ClearActorSelectionSet();

									// Go back to Current Level
									if (bLoadLevel)
									{
										LevelEditorSubsystem->LoadLevel(CurrentLevelAssetPath);
									}
								}
							}
							else
							{
								UObject* Object = Path.TryLoad();

								// If the Load fails, remove
								if (!Object)
								{
									UE_LOG(LogCsEditor, Warning, TEXT("%s: Failed to load Object at Path: %s."), *Context, *(Path.ToString()));

									ToRemove.Add(Path);
									continue;
								}
								else
								{
									// Blueprint
									if (BlueprintLibrary::Is(Object))
									{
										if (UObject* DOb = BlueprintLibrary::GetSafeDefaultObject(Context, Object, nullptr))
										{	
											if (PropertyLibrary::HasStructProperty(Context, DOb->GetClass(), Struct, nullptr))
											{
												if (AssetEditorSubsystem->OpenEditorForAsset(Object))
												{		
													AssetEditorSubsystem->CloseAllEditorsForAsset(Object);
												}
												else
												{
													UE_LOG(LogCsEditor, Warning, TEXT("%s: Failed to Open Object at Path: %s."), *Context, *(Path.ToString()));
													ToRemove.Add(Path);
													continue;
												}
											}
											else
											{
												UE_LOG(LogCsEditor, Warning, TEXT("%s: Object at Path: %s no longer as reference to a struct of type: %s."), *Context, *(Path.ToString()), *(Struct->GetName()));
												ToRemove.Add(Path);
												continue;
											}
										}
										else
										if (UObject* CDOb = BlueprintLibrary::GetSafeClassDefaultObject(Context, Object, nullptr))
										{	
											if (PropertyLibrary::HasStructProperty(Context, CDOb->GetClass(), Struct, nullptr))
											{
												if (AssetEditorSubsystem->OpenEditorForAsset(Object))
												{		
													AssetEditorSubsystem->CloseAllEditorsForAsset(Object);
												}
												else
												{
													UE_LOG(LogCsEditor, Warning, TEXT("%s: Failed to Open Object at Path: %s."), *Context, *(Path.ToString()));
													ToRemove.Add(Path);
													continue;
												}
											}
											else
											{
												UE_LOG(LogCsEditor, Warning, TEXT("%s: Object at Path: %s no longer as reference to a struct of type: %s."), *Context, *(Path.ToString()), *(Struct->GetName()));
												ToRemove.Add(Path);
												continue;
											}
										}
										else
										{
											UE_LOG(LogCsEditor, Warning, TEXT("%s: Failed to get Default Object for Blueprint at Path: %s."), *Context, *(Path.ToString()));

											ToRemove.Add(Path);
											continue;
										}
									}
									else
									{
										if (PropertyLibrary::HasStructProperty(Context, Object->GetClass(), Struct, nullptr))
										{
											if (AssetEditorSubsystem->OpenEditorForAsset(Object))
											{		
												AssetEditorSubsystem->CloseAllEditorsForAsset(Object);
											}
											else
											{
												UE_LOG(LogCsEditor, Warning, TEXT("%s: Failed to Open Object at Path: %s."), *Context, *(Path.ToString()));
												ToRemove.Add(Path);
												continue;
											}
										}
										else
										{
											UE_LOG(LogCsEditor, Warning, TEXT("%s: Object at Path: %s no longer as reference to a struct of type: %s."), *Context, *(Path.ToString()), *(Struct->GetName()));
											ToRemove.Add(Path);
											continue;
										}
									}
								}
							}
						}

						for (const FSoftObjectPath& Path : ToRemove)
						{
							References.Remove(Path);
						}

						if (ToRemove.Num() > CS_EMPTY)
						{
							SettingsLibrary::TryUpdateDefaultConfigFile();
						}
					}
				}
			}

			#undef SettingsLibrary
			#undef BlueprintLibrary
			#undef PropertyLibrary

			#undef USING_NS_CACHED
			#undef SET_CONTEXT
		}
	}
}