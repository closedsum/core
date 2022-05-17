// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Animation/Vertex/CsVertexAnimNotify.h"
#include "CsCore.h"

// Library
#include "Library/CsLibrary_Valid.h"
// Settings
#include "Settings/CsDeveloperSettings.h"

namespace NCsVertexAnimNotify
{
	namespace Str
	{
		const FString VertexAnimNotify = TEXT("VertexAnimNotify");
	}

	void PopulateEnumMapFromSettings(const FString& Context, UObject* ContextRoot)
	{
		UCsDeveloperSettings* Settings = GetMutableDefault<UCsDeveloperSettings>();

		EMCsVertexAnimNotify::Get().ClearUserDefinedEnums();

		// Enum Settings
		if (Settings->ECsVertexAnimNotify_PopulateEnumMapMethod == ECsPopulateEnumMapMethod::EnumSettings)
		{
			const TArray<FCsSettings_Enum>& Enums = Settings->GetSettingsEnum<FECsVertexAnimNotify>();
			const FString& EnumSettingsPath		  = Settings->GetSettingsEnumPath<FECsVertexAnimNotify>();

			if (Enums.Num() > CS_EMPTY)
			{
				for (const FCsSettings_Enum& Enum : Enums)
				{
					const FString& Name		   = Enum.Name;
					const FString& DisplayName = Enum.DisplayName;

					if (Name.IsEmpty())
					{
						UE_LOG(LogCs, Warning, TEXT("%s: Empty Enum listed in %s."), *Context, *EnumSettingsPath);
						return;
					}

					checkf(!EMCsVertexAnimNotify::Get().IsValidEnum(Name), TEXT("%s: VertexAnimNotify (Name): %s already exists (declared in native)."), *Context, *Name);

					if (!Enum.DisplayName.IsEmpty())
					{
						checkf(!EMCsVertexAnimNotify::Get().IsValidEnumByDisplayName(DisplayName), TEXT("%s: VertexAnimNotify (DisplayName): %s already exists (declared in native)."), *Context, *DisplayName);

						EMCsVertexAnimNotify::Get().Create(Name, DisplayName, true);
					}
					else
					{
						EMCsVertexAnimNotify::Get().Create(Name, true);
					}
				}
			}
			else
			{
				UE_LOG(LogCs, Warning, TEXT("%s: Enum Setting @ %s is empty."), *Context, *EnumSettingsPath);
			}
		}
	}
}

#define NotifyType NCsAnim::NVertex::FNotify

void FCsVertexAnimNotify::CopyToNotify(NotifyType* Value)
{
	Value->SetNotify(&Notify);
	Value->SetTime(&Time);
}

void FCsVertexAnimNotify::CopyToNotifyAsValue(NotifyType* Value) const
{
	Value->SetNotify(Notify);
	Value->SetTime(Time);
}

#undef NotifyType

bool FCsVertexAnimNotify::IsValidChecked(const FString& Context) const
{
	CS_IS_ENUM_STRUCT_VALID_CHECKED(EMCsVertexAnimNotify, Notify)
	CS_IS_FLOAT_GREATER_THAN_OR_EQUAL_CHECKED(Time, 0.0f)
	return true;
}

bool FCsVertexAnimNotify::IsValid(const FString& Context, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
{
	CS_IS_ENUM_STRUCT_VALID(EMCsVertexAnimNotify, FECsVertexAnimNotify, Notify)
	CS_IS_FLOAT_GREATER_THAN_OR_EQUAL(Time, 0.0f)
	return true;
}

const NCsAnim::NVertex::FNotify NCsAnim::NVertex::FNotify::Invalid = NCsAnim::NVertex::FNotify(EMCsVertexAnimNotify::Get().GetMAX(), -1.0f);

namespace NCsAnim
{
	namespace NVertex
	{
		bool FNotify::IsValidChecked(const FString& Context) const
		{
			CS_IS_ENUM_STRUCT_VALID_CHECKED(EMCsVertexAnimNotify, GetNotify())
			CS_IS_FLOAT_GREATER_THAN_OR_EQUAL_CHECKED(GetTime(), 0.0f)
			return true;
		}

		bool FNotify::IsValid(const FString& Context, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
		{
			CS_IS_ENUM_STRUCT_VALID(EMCsVertexAnimNotify, FECsVertexAnimNotify, GetNotify())
			CS_IS_FLOAT_GREATER_THAN_OR_EQUAL(GetTime(), 0.0f)
			return true;
		}
	}
}