// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Enhanced/Data/CsLibrary_EnhancedInput_WithGameplayTag_DataRootSet.h"

// Library
#include "Data/CsLibrary_DataRootSet.h"
// Utility
#include "Utility/CsInputWithGameplayTagLog.h"
// Data
#include "Enhanced/Data/CsGetEnhancedInputWithGameplayTagDataRootSet.h"
#include "Enhanced/Data/CsEnhancedInputWithGameplayTagDataRootSet.h"

namespace NCsInput
{
	namespace NEnhanced
	{
		namespace NWithGameplayTag
		{
			namespace NDataRootSet
			{
				#define DataRootSetType FCsEnhancedInputWithGameplayTagDataRootSet
				#define GetDataRootSetType ICsGetEnhancedInputWithGameplayTagDataRootSet
				#define GetDataRootSetFn GetCsEnhancedInputWithGameplayTagDataRootSet

				const DataRootSetType* FLibrary::GetSafe(const FString& Context, const UObject* WorldContext)
				{
					return NCsDataRootSet::FLibrary::GetSafe<DataRootSetType, GetDataRootSetType, &GetDataRootSetType::GetDataRootSetFn>(Context, WorldContext, &NCsInput::NWithGameplayTag::FLog::Warning);
				}

				const DataRootSetType& FLibrary::GetChecked(const FString& Context, const UGameInstance* GameInstance)
				{
					return NCsDataRootSet::FLibrary::GetChecked<DataRootSetType, GetDataRootSetType, &GetDataRootSetType::GetDataRootSetFn>(Context, GameInstance);
				}

				const DataRootSetType& FLibrary::GetChecked(const FString& Context, const UObject* WorldContext)
				{
					return NCsDataRootSet::FLibrary::GetChecked<DataRootSetType, GetDataRootSetType, &GetDataRootSetType::GetDataRootSetFn>(Context, WorldContext);
				}

				UCsData_EnhancedInput_WithGameplayTag* FLibrary::GetDataChecked(const FString& Context, const UObject* WorldContext)
				{
					return GetChecked(Context, WorldContext).GetDataChecked(Context);
				}

				#undef DataRootSetType
				#undef GetDataRootSetType
				#undef GetDataRootSetFn
			}
		}
	}
}