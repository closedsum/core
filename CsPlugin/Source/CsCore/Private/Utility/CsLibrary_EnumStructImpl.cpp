// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Utility/CsLibrary_EnumStructImpl.h"

// Types
#include "CsMacro_Misc.h"
// Library
#include "Settings/CsLibrary_DeveloperSettings.h"

#if WITH_EDITOR
// Library
#include "Library/CsLibrary_Valid.h"
// Engine
#include "Engine/Engine.h"
// Enum
#include "Types/Enum/Tool/CsGetEnumStructTool.h"
#endif // #if WITH_EDITOR

namespace NCsEnum
{
	namespace NStruct
	{
		namespace NLayout
		{
			namespace NImpl
			{
				namespace NLibrary
				{
					namespace NCached
					{
						namespace Str
						{
							CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsEnum::NStruct::NLayout::NImpl::FLibrary, AddPropertyChange);
						}
					}
				}

				#define USING_NS_CACHED using namespace NCsEnum::NStruct::NLayout::NImpl::NLibrary::NCached;
				#define SET_CONTEXT(__FunctionName) using namespace NCsEnum::NStruct::NLayout::NImpl::NLibrary::NCached; \
					const FString& Context = Str::__FunctionName

				void FLibrary::ConditionalAddLayout(const FName& EnumName, const TArray<FName>& Names, UDataTable* DataTable)
				{
					typedef NCsCore::NSettings::FLibrary SettingsLibrary;

					TMap<FName, FCsEnumStructLayoutHistory>& EnumStructlayoutHistoryMap = SettingsLibrary::GetEnumStructlayoutHistoryMap();

					if (!EnumStructlayoutHistoryMap.Find(EnumName))
					{
						FCsEnumStructLayoutHistory& History = EnumStructlayoutHistoryMap.Add(EnumName);

						int32 Count = 0;

						for (const FName& Name : Names)
						{
							FCsEnumStructLayoutHistory_NameAndValue& NameAndValue = History.NameAndValues.AddDefaulted_GetRef();
							NameAndValue.Name  = Name;
							NameAndValue.Value = Count;

							++Count;
						}

						History.DataTable = DataTable;

						SettingsLibrary::TryUpdateDefaultConfigFile();
					}
				}

				void FLibrary::AddPropertyChange(const FName& EnumName, UStruct* EnumStruct)
				{
					SET_CONTEXT(AddPropertyChange);

				#if WITH_EDITOR
					typedef NCsEnum::NStruct::NTool::FImpl EnumStructToolType;

					ICsGetEnumStructTool* GetEnumStructTool = CS_INTERFACE_CAST_CHECKED(GEngine, UEngine, ICsGetEnumStructTool);
					EnumStructToolType& EnumStructTool		= GetEnumStructTool->GetEnumStructTool();

					EnumStructTool.AddPropertyChange(EnumName, EnumStruct);
				#endif // #if WITH_EDITOR
				}

				#undef USING_NS_CACHED
				#undef SET_CONTEXT
			}
		}
	}
}