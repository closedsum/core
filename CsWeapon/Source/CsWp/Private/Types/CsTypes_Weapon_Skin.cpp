// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/CsTypes_Weapon_Skin.h"
#include "CsWp.h"

// Types
#include "CsMacro_Misc.h"
// Library
#include "Data/CsLibrary_Data.h"
#include "Library/CsLibrary_Valid.h"
// Data
#include "Data/Skin/CsData_Weapon_Skin.h"
// Utility
#include "Utility/CsWpPopulateEnumMapFromSettings.h"

// WeaponSkin
#pragma region

namespace NCsWeaponSkin
{
	namespace NCached
	{
		namespace Str
		{
			const FString WeaponSkin = TEXT("WeaponSkin");
		}

		namespace Name
		{
			const FName WeaponSkins = FName("WeaponSkins");
		}
	}

	void FromDataTable(const FString& Context, UObject* ContextRoot)
	{
		using namespace NCsWeaponSkin::NCached;

		typedef FCsWpPopulateEnumMapFromSettings::FFromDataTable::FPayload PayloadType;

		PayloadType Payload;
		Payload.ContextRoot				 = ContextRoot;
		Payload.DataTableName			 = Name::WeaponSkins;
		Payload.EnumName				 = Str::WeaponSkin;
		Payload.Create					 = &Create;
		Payload.CreateCustom			 = &CreateCustom;
		Payload.IsValidEnum				 = &IsValidEnum;
		Payload.IsValidEnumByDisplayName = &IsValidEnumByDisplayName;
		Payload.Log						 = &NCsWeapon::FLog::Warning;

		FCsWpPopulateEnumMapFromSettings::FromDataTable(Context, Payload);
	}

	void PopulateEnumMapFromSettings(const FString& Context, UObject* ContextRoot)
	{
		EMCsWeaponSkin::Get().ClearUserDefinedEnums();

		FromDataTable(Context, ContextRoot);
	}
}

#pragma endregion Character

// FCsData_Weapon_SkinPtr
#pragma region

namespace NCsDataWeaponSkinPtr
{
	namespace NCached
	{
		namespace Str
		{
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(FCsData_Weapon_SkinPtr, SafeLoad);
		}
	}
}

#define DataType NCsWeapon::NData::NSkin::ISkin

DataType* FCsData_Weapon_SkinPtr::GetChecked(const FString& Context) const
{
	const FSoftObjectPath& Path = Data.ToSoftObjectPath();

	checkf(Path.IsValid(), TEXT("%s: Data is NULL. No Path set."), *Context);

	checkf(Data_Internal, TEXT("%s: Data has NOT been loaded @ %s."), *Context, *(Path.ToString()));

	typedef NCsData::FLibrary DataLibrary;

	return DataLibrary::GetChecked<DataType>(Context, Data_Internal);
}

DataType* FCsData_Weapon_SkinPtr::GetSafe(const FString& Context) const
{
	const FSoftObjectPath& Path = Data.ToSoftObjectPath();

	if (!Path.IsValid())
	{
		UE_LOG(LogCsWp, Warning, TEXT("%s: Data is NULL. No Path set."), *Context);
		return nullptr;
	}

	if (!Data_Internal)
	{
		UE_LOG(LogCsWp, Warning, TEXT("%s: Data has NOT been loaded @ %s."), *Context, *(Path.ToString()));
		return nullptr;
	}

	typedef NCsData::FLibrary DataLibrary;

	return DataLibrary::GetSafe<DataType>(Context, Data_Internal);
}

DataType* FCsData_Weapon_SkinPtr::SafeLoad(const FString& Context, void(*Log)(const FString&) /*=&FCLog::Warning*/)
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

DataType* FCsData_Weapon_SkinPtr::SafeLoad()
{
	using namespace NCsDataWeaponSkinPtr::NCached;

	const FString& Context = Str::SafeLoad;

	return SafeLoad(Context, nullptr);
}

#undef DataType

UObject* FCsData_Weapon_SkinPtr::SafeLoadSoftClass(const FString& Context, void(*Log)(const FString&) /*=&FCLog::Warning*/)
{
	const FSoftObjectPath& Path = Data.ToSoftObjectPath();

	if (!Path.IsValid())
	{
		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Data is NOT Valid."), *Context))
		return nullptr;
	}

	UObject* O = Data.LoadSynchronous();

	if (!O)
	{
		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to load Data at Path: %s."), *Context, *(Path.ToString())))
	}
	return O;
}

#pragma endregion FCsData_Weapon_SkinPtr