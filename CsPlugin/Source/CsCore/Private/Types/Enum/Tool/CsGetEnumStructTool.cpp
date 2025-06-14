// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Types/Enum/Tool/CsGetEnumStructTool.h"

// Types
#include "CsMacro_Misc.h"
// Library
	// Settings
#include "Settings/CsLibrary_DeveloperSettings.h"
	// Common
#include "Library/CsLibrary_Blueprint.h"
#include "Library/CsLibrary_Property.h"
#include "Library/CsLibrary_Valid.h"
// Interface
#include "Asset/Tool/CsGetAssetTool.h"
#include "Level/Editor/Event/CsLevelEditor_Event.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsGetEnumStructTool)

namespace NCsEnum
{
	namespace NStruct
	{
		namespace NTool
		{
			namespace NImpl
			{
				namespace NCached
				{
					namespace Str
					{
						CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsEnum::NStruct::NTool::FImpl, Init);
						CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsEnum::NStruct::NTool::FImpl, AddPropertyChange);
						CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsEnum::NStruct::NTool::FImpl, OnActorSelectionChanged);
					}
				}
			}

			#define USING_NS_CACHED using namespace NCsEnum::NStruct::NTool::NImpl::NCached;
			#define SET_CONTEXT(__FunctionName) using namespace NCsEnum::NStruct::NTool::NImpl::NCached; \
				const FString& Context = Str::__FunctionName

			void FImpl::Init(UObject* InOuter)
			{
				SET_CONTEXT(Init);

				Outer = InOuter;

				ICsLevelEditor_Event* LevelEditor_Event = CS_INTERFACE_CAST_CHECKED(Outer, UObject, ICsLevelEditor_Event);

				LevelEditor_Event->GetOnActorSelectionChanged_Event().AddRaw(this, &FImpl::OnActorSelectionChanged);
			}

			#define SettingsLibrary NCsCore::NSettings::FLibrary
			
			void FImpl::AddPropertyChange(const FName& Name, UStruct* Struct)
			{
				SET_CONTEXT(AddPropertyChange);

				if (!Outer)
					return;

				FPropertyChange& Change = PropertyChanges.AddDefaulted_GetRef();
				Change.Name   = Name;
				Change.Struct = Struct;

				// Check Opened Assets
				{
					TMap<FName, FCsEnumStructLayoutHistory>& EnumStructlayoutHistoryMap = SettingsLibrary::GetEnumStructlayoutHistoryMap();
					FCsEnumStructLayoutHistory& History									= EnumStructlayoutHistoryMap[Name];

					ICsGetAssetTool* GetAssetTool = CS_INTERFACE_CAST_CHECKED(Outer, UObject, ICsGetAssetTool);

					const TArray<TWeakObjectPtr<UObject>>& OpenedAssets = GetAssetTool->GetAssetTool()->GetOpenedAssetsImpl();

					bool Found = false;

					for (const TWeakObjectPtr<UObject>& O : OpenedAssets)
					{
						UObject* Asset = O.IsValid() ? O.Get() : nullptr;

						if (!IsValid(Asset))
							continue;

						TSoftObjectPtr<UObject> SoftObjectPtr(Asset);

						const FSoftObjectPath& Path = SoftObjectPtr.ToSoftObjectPath();

						if (History.References.Contains(Path))
							continue;

						// Blueprint
						if (CsBlueprintLibrary::Is(Asset))
						{
							if (UObject* DOb = CsBlueprintLibrary::GetSafeDefaultObject(Context, Asset, nullptr))
							{	
								if (CsPropertyLibrary::HasStructProperty(Context, DOb->GetClass(), Struct, nullptr))
								{
									History.References.Add(Path);

									Found = true;
								}
							}
							else
							if (UObject* CDOb = CsBlueprintLibrary::GetSafeClassDefaultObject(Context, Asset, nullptr))
							{	
								if (CsPropertyLibrary::HasStructProperty(Context, CDOb->GetClass(), Struct, nullptr))
								{
									History.References.Add(Path);

									Found = true;
								}
							}
						}
					}

					if (Found)
					{
						PropertyChanges.RemoveAt(PropertyChanges.Num() - 1, 1, EAllowShrinking::No);

						SettingsLibrary::TryUpdateDefaultConfigFile();
					}
				}
			}

			void FImpl::OnActorSelectionChanged(const TArray<UObject*>& NewSelection, bool bForceRefresh)
			{
				SET_CONTEXT(OnActorSelectionChanged);

				TMap<FName, FCsEnumStructLayoutHistory>& EnumStructlayoutHistoryMap = SettingsLibrary::GetEnumStructlayoutHistoryMap();

				bool Found = false;

				for (UObject* Object : NewSelection)
				{
					// Check Changes
					for (FPropertyChange& Change : PropertyChanges)
					{
						const FName& Name = Change.Name;

						FCsEnumStructLayoutHistory& History	= EnumStructlayoutHistoryMap[Name];

						TSoftObjectPtr<UObject> SoftObjectPtr(Object);

						const FSoftObjectPath& Path = SoftObjectPtr.ToSoftObjectPath();

						if (History.References.Contains(Path))
							continue;

						// Blueprint
						if (CsBlueprintLibrary::Is(Object))
						{
							if (UObject* DOb = CsBlueprintLibrary::GetSafeDefaultObject(Context, Object, nullptr))
							{	
								if (CsPropertyLibrary::HasStructProperty(Context, DOb->GetClass(), Change.Struct, nullptr))
								{
									History.References.Add(Path);

									Found = true;
								}
							}
							else
							if (UObject* CDOb = CsBlueprintLibrary::GetSafeClassDefaultObject(Context, Object, nullptr))
							{	
								if (CsPropertyLibrary::HasStructProperty(Context, CDOb->GetClass(), Change.Struct, nullptr))
								{
									History.References.Add(Path);

									Found = true;
								}
							}
						}
						else
						{
							if (CsPropertyLibrary::HasStructProperty(Context, Object->GetClass(), Change.Struct, nullptr))
							{
								History.References.Add(Path);

								Found = true;
							}
						}
					}
				}

				PropertyChanges.Reset(PropertyChanges.Max());

				if (Found)
				{
					SettingsLibrary::TryUpdateDefaultConfigFile();
				}
			}

			#undef SettingsLibrary

			#undef USING_NS_CACHED
			#undef SET_CONTEXT
		}
	}
}

UCsGetEnumStructTool::UCsGetEnumStructTool(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}