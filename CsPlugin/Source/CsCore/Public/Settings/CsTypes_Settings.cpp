// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Settings/CsTypes_Settings.h"
#include "CsCore.h"

// FCsSettings_Enum
#pragma region

namespace NCsEnum
{
	namespace NSettings
	{
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
						UE_LOG(LogCs, Warning, TEXT("%s: Failed to get a Name from Line %d: %s."), *EnumTypeName, Count, *Line);
						return;
					}

					if (DisplayName.IsEmpty())
					{
						UE_LOG(LogCs, Warning, TEXT("%s: Failed to get a DisplayName from Line %d: %s."), *EnumTypeName, Count, *Line);
						return;
					}

					E.Name		  = Name;
					E.DisplayName = DisplayName;
				}
				else
				{
					UE_LOG(LogCs, Warning, TEXT("%s: Failed to split Line %d: %s and get a Name and DisplayName."), *EnumTypeName, Count, *Line);
					return;
				}
				FParse::Line(&Stream, Line);

				++Count;
			}

			Enums.Reset(Temp.Num());

			Enums = Temp;
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

		CSCORE_API CS_ADD_TO_ENUM_MAP(Native);
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EnumSettings, "Enum Settings");
		CSCORE_API CS_ADD_TO_ENUM_MAP(DataTable);
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsPopulateEnumMapMethod_MAX, "MAX");
	}

	CSCORE_API const uint8 MAX = (uint8)ECsPopulateEnumMapMethod::ECsPopulateEnumMapMethod_MAX;
}

#pragma endregion PopulateEnumMapMethod