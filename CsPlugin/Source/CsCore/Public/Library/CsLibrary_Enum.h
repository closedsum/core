// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

// Types
#include "Types/CsTypes_Macro.h"
// Log
#include "Utility/CsLog.h"

namespace NCsEnum
{
	struct CSCORE_API FLibrary final
	{
	public:

		template<typename EnumStructMap, typename EnumStruct>
		static EnumStruct Get(const FString& FunctionName, const FString& EnumStructName, const FString& Name)
		{
			if (EnumStructMap::Get().IsValidEnum(Name))
				return EnumStructMap::Get()[Name];

			CS_NON_SHIPPING_EXPR(FCsLog::Warning(FString::Printf(TEXT("NCsEnum::FLibrary::%s: Enum of type %s and Name: %s does NOT exist."), *FunctionName, *EnumStructName, *Name)));

			return EnumStruct(0, NCsCached::Str::INVALID);
		}

		template<typename EnumStructMap, typename EnumStruct>
		static EnumStruct GetByIndex(const FString& FunctionName, const FString& EnumStructName, const int32& Index)
		{
			const int32& Count = EnumStructMap::Get().Num();

			if (Index < Count)
				return EnumStructMap::Get().GetEnumAt(Index);

			CS_NON_SHIPPING_EXPR(FCsLog::Warning(FString::Printf(TEXT("NCsEnum::FLibrary::%s: Enum of type %s and Index: %d (%d >= %d) does NOT exist."), *FunctionName, *EnumStructName, Index, Index, Count)));

			return EnumStruct(0, NCsCached::Str::INVALID);
		}

		template<typename EnumStructMap, typename EnumStruct>
		static void GetAll(TArray<EnumStruct>& OutTypes)
		{
			const int32& Count = EnumStructMap::Get().Num();

			for (int32 I = 0; I < Count; ++I)
			{
				OutTypes.Add(EnumStructMap::Get().GetEnumAt(I));
			}
		}
	};
}