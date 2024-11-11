// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Settings/CsTypes_Settings_Enum.h"
#include "CsTypes.h"

// Types
#include "CsMacro_Misc.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsTypes_Settings_Enum)

// FCsSettings_Enum
#pragma region

namespace NCsEnum
{
	namespace NSettings
	{
		using PayloadType = NCsEnum::NSettings::FLibrary::FPopulate::FPayload;

		void FLibrary::PopulateArrayFromString(TArray<FCsSettings_Enum>& Enums, const FString& Str, const FString& EnumTypeName)
		{
			if (Str.IsEmpty())
				return;

			TArray<FCsSettings_Enum> Temp;

			const TCHAR* Stream = *Str;

			FString Line;
			FString Name;
			FString DisplayName;

			FParse::Line(&Stream, Line);

			int32 Count = 0;

			while (!Line.IsEmpty())
			{
				if (Line.Split(TEXT(","), &Name, &DisplayName))
				{
					Temp.AddDefaulted();
					FCsSettings_Enum& E = Temp.Last();

					if (Name.IsEmpty())
					{
						UE_LOG(LogCsTypes, Warning, TEXT("%s: Failed to get a Name from Line %d: %s."), *EnumTypeName, Count, *Line);
						return;
					}

					if (DisplayName.IsEmpty())
					{
						UE_LOG(LogCsTypes, Warning, TEXT("%s: Failed to get a DisplayName from Line %d: %s."), *EnumTypeName, Count, *Line);
						return;
					}

					E.Name		  = Name;
					E.DisplayName = DisplayName;
				}
				else
				{
					UE_LOG(LogCsTypes, Warning, TEXT("%s: Failed to split Line %d: %s and get a Name and DisplayName."), *EnumTypeName, Count, *Line);
					return;
				}
				FParse::Line(&Stream, Line);

				++Count;
			}

			Enums.Reset(Temp.Num());

			Enums = Temp;
		}

		void FLibrary::Populate(const FString& Context, PayloadType& Payload)
		{
			const TArray<FCsSettings_Enum>& Enums = Payload.Enums;
			const FString& EnumSettingsPath		  = Payload.EnumSettingsPath;
			const FString& EnumName				  = Payload.EnumName;

			void(*Log)(const FString&) = Payload.Log;

			if (Enums.Num() > CS_EMPTY)
			{
				for (const FCsSettings_Enum& Enum : Enums)
				{
					const FString& Name		   = Enum.Name;
					const FString& DisplayName = Enum.DisplayName;

					if (Name.IsEmpty())
					{
						CS_NON_SHIPPING_EXPR(Log(FString::Printf(TEXT("%s: Empty Enum listed in %s."), *Context, *EnumSettingsPath)));
						return;
					}

					checkf(!Payload.IsValidEnum(Name), TEXT("%s: %s (Name): %s already exists (declared in native)."), *Context, *EnumName, *Name);

					if (!Enum.DisplayName.IsEmpty())
					{
						checkf(!Payload.IsValidEnumByDisplayName(DisplayName), TEXT("%s: %s (DisplayName): %s already exists (declared in native)."), *Context, *EnumName, *DisplayName);

						Payload.CreateCustom(Name, DisplayName, true);
					}
					else
					{
						Payload.Create(Name, true);
					}
				}
			}
			else
			{
				CS_NON_SHIPPING_EXPR(Log(FString::Printf(TEXT("%s: Enum Setting @ %s is empty."), *Context, *EnumSettingsPath)));
			}
		}
	}
}

#pragma endregion FCsSettings_Enum

// PopulateEnumMapMethod
#pragma region

namespace NCsPopulateEnumMapMethod
{
	namespace Ref
	{
		typedef EMCsPopulateEnumMapMethod EnumMapType;

		CSTYPES_API CS_ADD_TO_ENUM_MAP(Native);
		CSTYPES_API CS_ADD_TO_ENUM_MAP_CUSTOM(EnumSettings, "Enum Settings");
		CSTYPES_API CS_ADD_TO_ENUM_MAP(DataTable);
		CSTYPES_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsPopulateEnumMapMethod_MAX, "MAX");
	}

	CSTYPES_API const uint8 MAX = (uint8)ECsPopulateEnumMapMethod::ECsPopulateEnumMapMethod_MAX;
}

#pragma endregion PopulateEnumMapMethod