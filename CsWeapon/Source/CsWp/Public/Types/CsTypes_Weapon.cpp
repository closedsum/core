// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/CsTypes_Weapon.h"
#include "CsWp.h"

// Library
	// Settings
#include "Settings/CsLibrary_WeaponSettings.h"
	// Common
#include "Level/CsLibrary_Level.h"
#include "Library/CsLibrary_Valid.h"
// Utility
#include "Utility/CsWpPopulateEnumMapFromSettings.h"
// Interface
#include "Types/CsGetWeaponTypes.h"
// Level
#include "Engine/LevelScriptActor.h"

// Weapon
#pragma region

namespace NCsWeapon
{
	namespace NCached
	{
		namespace Str
		{
			const FString Weapon = TEXT("Weapon");
		}

		namespace Name
		{
			const FName Weapons = FName("Weapons");
		}
	}

	void FromEnumSettings(const FString& Context)
	{
		using namespace NCsWeapon::NCached;

		typedef NCsWeapon::NSettings::FLibrary SettingsLibrary;
		typedef NCsEnum::NSettings::FLibrary EnumSettingsLibrary;
		typedef NCsEnum::NSettings::FLibrary::FPopulate::FPayload PayloadType;

		PayloadType Payload;
		Payload.Enums					 = SettingsLibrary::GetSettingsEnum_Weapon();
		Payload.EnumSettingsPath		 = SettingsLibrary::GetSettingsEnumPath_Weapon();
		Payload.EnumName				 = Str::Weapon;
		Payload.Create					 = &Create;
		Payload.CreateCustom			 = &CreateCustom;
		Payload.IsValidEnum				 = &IsValidEnum;
		Payload.IsValidEnumByDisplayName = &IsValidEnumByDisplayName;
		Payload.Log						 = &NCsWeapon::FLog::Warning;

		EnumSettingsLibrary::Populate(Context, Payload);
	}

	void FromDataTable(const FString& Context, UObject* ContextRoot)
	{
		using namespace NCsWeapon::NCached;

		typedef FCsWpPopulateEnumMapFromSettings::FFromDataTable::FPayload PayloadType;

		PayloadType Payload;
		Payload.ContextRoot				 = ContextRoot;
		Payload.DataTableName			 = Name::Weapons;
		Payload.EnumName				 = Str::Weapon;
		Payload.Create					 = &Create;
		Payload.CreateCustom			 = &CreateCustom;
		Payload.IsValidEnum				 = &IsValidEnum;
		Payload.IsValidEnumByDisplayName = &IsValidEnumByDisplayName;
		Payload.Log						 = &NCsWeapon::FLog::Warning;

		FCsWpPopulateEnumMapFromSettings::FromDataTable(Context, Payload);
	}

	void PopulateEnumMapFromSettings(const FString& Context, UObject* ContextRoot)
	{
		typedef NCsWeapon::NSettings::FLibrary SettingsLibrary;

		EMCsWeapon::Get().ClearUserDefinedEnums();

		// Enum Settings
		if (SettingsLibrary::Get_ECsWeapon_PopulateEnumMapMethod() == ECsPopulateEnumMapMethod::EnumSettings)
		{
			FromEnumSettings(Context);
		}

		// DataTable
		if (SettingsLibrary::Get_ECsWeapon_PopulateEnumMapMethod() == ECsPopulateEnumMapMethod::DataTable)
		{
			FromDataTable(Context, ContextRoot);
		}
	}

	void GetSafeFromLevel(const FString& Context, const UObject* WorldContext, TSet<FECsWeapon>& OutWeaponTypes, void(*Log)(const FString&) /*=&NCsWeapon::FLog::Warning*/)
	{
		typedef NCsLevel::NPersistent::FLibrary LevelLibrary;

		ICsGetWeaponTypes* GetWeaponTypes = LevelLibrary::GetSafeSetupData<ICsGetWeaponTypes>(Context, WorldContext, Log);

		if (!GetWeaponTypes)
			return;

		OutWeaponTypes = GetWeaponTypes->GetWeaponTypes();

		CS_IS_ENUM_STRUCT_SET_UNIQUE_CHECKED(EMCsWeapon, FECsWeapon, OutWeaponTypes)
	}
}

#pragma endregion Weapon

// WeaponClass
#pragma region

namespace NCsWeaponClass
{
	namespace NCached
	{
		namespace Str
		{
			const FString WeaponClass = TEXT("WeaponClass");
		}

		namespace Name
		{
			const FName WeaponClasses = FName("WeaponClasses");
		}
	}

	void FromEnumSettings(const FString& Context)
	{
		using namespace NCsWeaponClass::NCached;

		typedef NCsWeapon::NSettings::FLibrary SettingsLibrary;
		typedef NCsEnum::NSettings::FLibrary EnumSettingsLibrary;
		typedef NCsEnum::NSettings::FLibrary::FPopulate::FPayload PayloadType;

		PayloadType Payload;
		Payload.Enums					 = SettingsLibrary::GetSettingsEnum_WeaponClass();
		Payload.EnumSettingsPath		 = SettingsLibrary::GetSettingsEnumPath_WeaponClass();
		Payload.EnumName				 = Str::WeaponClass;
		Payload.Create					 = &Create;
		Payload.CreateCustom			 = &CreateCustom;
		Payload.IsValidEnum				 = &IsValidEnum;
		Payload.IsValidEnumByDisplayName = &IsValidEnumByDisplayName;
		Payload.Log						 = &NCsWeapon::FLog::Warning;

		EnumSettingsLibrary::Populate(Context, Payload);
	}

	void FromDataTable(const FString& Context, UObject* ContextRoot)
	{
		using namespace NCsWeaponClass::NCached;

		typedef FCsWpPopulateEnumMapFromSettings::FFromDataTable::FPayload PayloadType;

		PayloadType Payload;
		Payload.ContextRoot				 = ContextRoot;
		Payload.DataTableName			 = Name::WeaponClasses;
		Payload.EnumName				 = Str::WeaponClass;
		Payload.Create					 = &Create;
		Payload.CreateCustom			 = &CreateCustom;
		Payload.IsValidEnum				 = &IsValidEnum;
		Payload.IsValidEnumByDisplayName = &IsValidEnumByDisplayName;
		Payload.Log						 = &NCsWeapon::FLog::Warning;

		FCsWpPopulateEnumMapFromSettings::FromDataTable(Context, Payload);
	}

	void PopulateEnumMapFromSettings(const FString& Context, UObject* ContextRoot)
	{
		typedef NCsWeapon::NSettings::FLibrary SettingsLibrary;

		EMCsWeaponClass::Get().ClearUserDefinedEnums();

		// Enum Settings
		if (SettingsLibrary::Get_ECsWeaponClass_PopulateEnumMapMethod() == ECsPopulateEnumMapMethod::EnumSettings)
		{
			FromEnumSettings(Context);
		}

		// DataTable
		if (SettingsLibrary::Get_ECsWeaponClass_PopulateEnumMapMethod() == ECsPopulateEnumMapMethod::DataTable)
		{
			FromDataTable(Context, ContextRoot);
		}
	}
}

#pragma endregion WeaponClass

// WeaponState
#pragma region

namespace NCsWeaponState
{
	namespace NCached
	{
		namespace Str
		{
			const FString WeaponState = TEXT("WeaponState");
		}
	}

	void FromEnumSettings(const FString& Context)
	{
		using namespace NCsWeaponState::NCached;

		typedef NCsWeapon::NSettings::FLibrary SettingsLibrary;
		typedef NCsEnum::NSettings::FLibrary EnumSettingsLibrary;
		typedef NCsEnum::NSettings::FLibrary::FPopulate::FPayload PayloadType;

		PayloadType Payload;
		Payload.Enums					 = SettingsLibrary::GetSettingsEnum_WeaponState();
		Payload.EnumSettingsPath		 = SettingsLibrary::GetSettingsEnumPath_WeaponState();
		Payload.EnumName				 = Str::WeaponState;
		Payload.Create					 = &Create;
		Payload.CreateCustom			 = &CreateCustom;
		Payload.IsValidEnum				 = &IsValidEnum;
		Payload.IsValidEnumByDisplayName = &IsValidEnumByDisplayName;
		Payload.Log						 = &NCsWeapon::FLog::Warning;

		EnumSettingsLibrary::Populate(Context, Payload);
	}

	void PopulateEnumMapFromSettings(const FString& Context, UObject* ContextRoot)
	{
		EMCsWeaponState::Get().ClearUserDefinedEnums();

		FromEnumSettings(Context);
	}
}

#pragma endregion WeaponState

// WeaponData
#pragma region

namespace NCsWeaponData
{
	CSWP_API CS_CREATE_ENUM_STRUCT_CUSTOM(Weapon, "ICsData_Weapon");
	CSWP_API CS_CREATE_ENUM_STRUCT_CUSTOM(ProjectileWeapon, "ICsData_ProjectileWeapon");
	CSWP_API CS_CREATE_ENUM_STRUCT_CUSTOM(ProjectileWeaponSound, "ICsData_ProjectileWeapon_SoundFire");
}

#pragma endregion WeaponData

// FCsData_WeaponPtr
#pragma region

UObject* FCsData_WeaponPtr::SafeLoad(const FString& Context, void(*Log)(const FString&) /*=&NCsWeapon::FLog::Warning*/)
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
		return nullptr;
	}

	UClass* Class = Cast<UClass>(O);

	if (!Class)
	{
		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Data: %s with Class: %s is NOT of type UClass."), *Context, *(Data->GetName()), *(Data->GetClass()->GetName())))
		return nullptr;
	}

	UObject* DOb = Class->GetDefaultObject();

	if (!DOb)
	{
		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to get Default Object for Class: %s."), *Context, *(Class->GetName())))
	}
	return DOb;
}

UObject* FCsData_WeaponPtr::SafeLoadSoftClass(const FString& Context, void(*Log)(const FString&) /*=&NCsWeapon::FLog::Warning*/)
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

#pragma endregion FCsData_WeaponPtr