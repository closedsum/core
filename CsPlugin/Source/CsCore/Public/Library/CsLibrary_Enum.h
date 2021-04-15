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
		FORCEINLINE static EnumStruct GetSafe(const FString& Context, const FString& EnumStructName, const FString& Name, void(*Log)(const FString&) = &FCsLog::Warning)
		{
			if (EnumStructMap::Get().IsValidEnum(Name))
				return EnumStructMap::Get()[Name];

			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Enum of type %s and Name: %s does NOT exist."), *Context, *EnumStructName, *Name));

			return EnumStruct(0, NCsCached::Str::INVALID);
		}

		template<typename EnumStructMap, typename EnumStruct>
		FORCEINLINE static EnumStruct GetSafeByIndex(const FString& Context, const FString& EnumStructName, const int32& Index, void(*Log)(const FString&) = &FCsLog::Warning)
		{
			const int32& Count = EnumStructMap::Get().Num();

			if (Index < Count)
				return EnumStructMap::Get().GetEnumAt(Index);

			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Enum of type %s and Index: %d (%d >= %d) does NOT exist."), *Context, *EnumStructName, Index, Index, Count));

			return EnumStruct(0, NCsCached::Str::INVALID);
		}

		template<typename EnumStructMap, typename EnumStruct>
		FORCEINLINE static void GetAll(TArray<EnumStruct>& OutTypes)
		{
			const int32& Count = EnumStructMap::Get().Num();

			OutTypes.Reset(FMath::Max(OutTypes.Max(), Count));

			for (int32 I = 0; I < Count; ++I)
			{
				OutTypes.Add(EnumStructMap::Get().GetEnumAt(I));
			}
		}
	};
}