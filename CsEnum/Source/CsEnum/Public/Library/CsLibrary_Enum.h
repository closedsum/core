// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "Types/Enum/CsTypes_Enum.h"
// Log
#include "Utility/CsEnumLog.h"

namespace NCsEnum
{
	struct CSENUM_API FLibrary final
	{
	public:

		template<typename EnumStructMap, typename EnumStruct>
		FORCEINLINE static EnumStruct CreateSafe(const FString& Context, const FString& Name, const FString& DisplayName, void(*Log)(const FString&) = &NCsEnum::FLog::Warning)
		{
			if (Name.IsEmpty())
			{
				if (Log)
				{
					Log(FString::Printf(TEXT("%s: Name is EMPTY."), *Context, *Name));
				}
				return EnumStruct(0, NCsEnum::Str::INVALID);
			}

			if (DisplayName.IsEmpty())
			{
				if (Log)
				{
					Log(FString::Printf(TEXT("%s: DisplayName is EMPTY."), *Context, *DisplayName));
				}
				return EnumStruct(0, NCsEnum::Str::INVALID);
			}

			if (EnumStructMap::Get().IsValidEnum(Name))
				return EnumStructMap::Get().GetEnum(Name);
			return EnumStructMap::Get().Create(Name, DisplayName, true);
		}

		template<typename EnumStructMap, typename EnumStruct>
		FORCEINLINE static EnumStruct GetSafe(const FString& Context, const FString& EnumStructName, const FString& Name, void(*Log)(const FString&) = &NCsEnum::FLog::Warning)
		{
			if (EnumStructMap::Get().IsValidEnum(Name))
				return EnumStructMap::Get()[Name];

			if (Log)
			{ 
				Log(FString::Printf(TEXT("%s: Enum of type %s and Name: %s does NOT exist."), *Context, *EnumStructName, *Name));
			}
			return EnumStruct(0, NCsEnum::Str::INVALID);
		}

		template<typename EnumStructMap, typename EnumStruct>
		FORCEINLINE static EnumStruct GetSafeByIndex(const FString& Context, const FString& EnumStructName, const int32& Index, void(*Log)(const FString&) = &NCsEnum::FLog::Warning)
		{
			const int32& Count = EnumStructMap::Get().Num();

			if (Index < Count)
				return EnumStructMap::Get().GetEnumAt(Index);

			if (Log)
			{
				Log(FString::Printf(TEXT("%s: Enum of type %s and Index: %d (%d >= %d) does NOT exist."), *Context, *EnumStructName, Index, Index, Count));
			}

			return EnumStruct(0, NCsEnum::Str::INVALID);
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

using CsEnumLibrary = NCsEnum::FLibrary;