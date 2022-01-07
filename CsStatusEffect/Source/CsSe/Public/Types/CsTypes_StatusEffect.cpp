// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/CsTypes_StatusEffect.h"
#include "CsSe.h"

// Library
#include "Data/CsLibrary_Data.h"
// Utility
#include "Utility/CsSeLog.h"
#include "Utility/CsPopulateEnumMapFromSettings.h"
#include "Utility/CsSePopulateEnumMapFromSettings.h"
// Data
#include "Data/CsSeGetDataRootSet.h"
#include "Data/CsData_StatusEffect.h"

// StatusEffect
#pragma region

namespace NCsStatusEffect
{
	namespace Str
	{
		const FString StatusEffect = TEXT("StatusEffect");
	}

	void FromDataTable(const FString& Context, UObject* ContextRoot)
	{
		const FCsSeDataRootSet* DataRootSet = FCsSePopulateEnumMapFromSettings::GetDataRootSet(Context, ContextRoot);

		if (!DataRootSet)
			return;

		FCsPopulateEnumMapFromSettings::FromDataTable<EMCsStatusEffect>(Context, ContextRoot, DataRootSet->StatusEffects, Str::StatusEffect, &NCsStatusEffect::FLog::Warning);
	}

	void PopulateEnumMapFromSettings(const FString& Context, UObject* ContextRoot)
	{
		EMCsStatusEffect::Get().ClearUserDefinedEnums();

		FromDataTable(Context, ContextRoot);
	}
}

#pragma endregion StatusEffect

// StatusEffectEvent
#pragma region

namespace NCsStatusEffectEvent
{
	CSSE_API CS_CREATE_ENUM_STRUCT(Default);
	CSSE_API CS_CREATE_ENUM_STRUCT(Damage);
}

#pragma endregion StatusEffectEvent

// FCData_CharacterPtr
#pragma region

namespace NCDataStatusEffectPtr
{
	namespace NCached
	{
		namespace Str
		{
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(FCsData_StatusEffectPtr, SafeLoad);
		}
	}
}

#define DataType NCsStatusEffect::NData::IData

DataType* FCsData_StatusEffectPtr::GetChecked(const FString& Context) const
{
	const FSoftObjectPath& Path = Data.ToSoftObjectPath();

	checkf(Path.IsValid(), TEXT("%s: Data is NULL. No Path set."), *Context);

	checkf(Data_Internal, TEXT("%s: Data has NOT been loaded @ %s."), *Context, *(Path.ToString()));

	typedef NCsData::FLibrary DataLibrary;

	return DataLibrary::GetChecked<DataType>(Context, Data_Internal);
}

DataType* FCsData_StatusEffectPtr::GetSafe(const FString& Context) const
{
	const FSoftObjectPath& Path = Data.ToSoftObjectPath();

	if (!Path.IsValid())
	{
		UE_LOG(LogCsSe, Warning, TEXT("%s: Data is NULL. No Path set."), *Context);
		return nullptr;
	}

	if (!Data_Internal)
	{
		UE_LOG(LogCsSe, Warning, TEXT("%s: Data has NOT been loaded @ %s."), *Context, *(Path.ToString()));
		return nullptr;
	}

	typedef NCsData::FLibrary DataLibrary;

	return DataLibrary::GetSafe<DataType>(Context, Data_Internal);
}

DataType* FCsData_StatusEffectPtr::SafeLoad(const FString& Context, void(*Log)(const FString&) /*=&NCsStatusEffect::FLog::Warning*/)
{
	const FSoftObjectPath& Path = Data.ToSoftObjectPath();

	if (!Path.IsValid())
	{
		if (Log)
			Log(FString::Printf(TEXT("%s: Data is NULL. No Path set."), *Context));
		return nullptr;
	}

	if (!Data_Internal)
	{
		Data_Class = Data.LoadSynchronous();

		if (Data_Class)
		{
			Data_Internal = Data_Class->GetDefaultObject();

			if (!Data_Internal)
			{
				if (Log)
					Log(FString::Printf(TEXT("%s: Failed to get DefaultObject for Data @ Path: %s with Class: %s."), *Context, *(Path.ToString()), *(Data_Class->GetName())));
				return nullptr;
			}
		}
		else
		{
			if (Log)
				Log(FString::Printf(TEXT("%s: Failed to load Data @ Path: %s."), *Context, *(Path.ToString())));
			return nullptr;
		}
	}

	typedef NCsData::FLibrary DataLibrary;

	return DataLibrary::SafeLoad<DataType>(Context, Data_Internal, Log);
}

DataType* FCsData_StatusEffectPtr::SafeLoad()
{
	using namespace NCDataStatusEffectPtr::NCached;

	const FString& Context = Str::SafeLoad;

	return SafeLoad(Context, nullptr);
}

#undef DataType

#pragma endregion FCData_CharacterPtr