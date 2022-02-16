// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Data/CsWpDataRootSet.h"
#include "CsWp.h"

// Types
#include "Types/CsTypes_Macro.h"
// Library
#include "Data/CsLibrary_DataRootSet.h"

// Cached
#pragma region

namespace NCsWpDataRootSet
{
	namespace NCached
	{
		namespace Str
		{
			CS_DEFINE_CACHED_STRING(GetCsWpDataRootSet, "GetCsWpDataRootSet()");

			CS_DEFINE_CACHED_STRING(WeaponClasses, "WeaponClasses");
			CS_DEFINE_CACHED_STRING(Weapons, "Weapons");
		}
	}
}

#pragma endregion Cached


bool FCsWpDataRootSet::IsValidChecked(const FString& Context, const UObject* WorldContext, const EMember& MemberType) const
{
	using namespace NCsWpDataRootSet::NCached;

	#define CS_TEMP_CHECK(Member) if (MemberType == EMember::Member) \
	{ \
		checkf(Member.ToSoftObjectPath().IsValid(), TEXT("%s: %s.%s.%s is NOT Valid."), *Context, *(WorldContext->GetName(), *Str::GetCsWpDataRootSet, *Str::Member)); \
	}

	// WeaponClasses
	CS_TEMP_CHECK(WeaponClasses)
	// Weapons
	CS_TEMP_CHECK(Weapons)

	#undef CS_TEMP_CHECK

	return true;
}

const TSoftObjectPtr<UDataTable>& FCsWpDataRootSet::GetDataTableSoftObjectChecked(const FString& Context, const EMember& MemberType) const
{
	#define CS_TEMP_GET_DATA_TABLE_SOFT_OBJECT_CHECKED(Member) if (MemberType == EMember::Member) \
		return Member;

	// WeaponClasses
	CS_TEMP_GET_DATA_TABLE_SOFT_OBJECT_CHECKED(WeaponClasses)
	// Weapons
	CS_TEMP_GET_DATA_TABLE_SOFT_OBJECT_CHECKED(Weapons)

	#undef CS_TEMP_GET_DATA_TABLE_SOFT_OBJECT_CHECKED

	checkf(0, TEXT("%s: Failed to get DataTable SoftObject for MemberType."), *Context);
	return WeaponClasses;
}

bool FCsWpDataRootSet::GetSafeDataTableSoftObject(const FString& Context, const EMember& MemberType, TSoftObjectPtr<UDataTable>& OutSoftObject, void(*Log)(const FString&) /*=&NCsProjectile::FLog::Warning*/) const
{
	#define CS_TEMP_GET_DATA_TABLE_SOFT_OBJECT_CHECKED(Member) if (MemberType == EMember::Member) \
		{ \
			OutSoftObject = Member; \
			return true; \
		}

	// WeaponClasses
	CS_TEMP_GET_DATA_TABLE_SOFT_OBJECT_CHECKED(WeaponClasses)
	// Weapons
	CS_TEMP_GET_DATA_TABLE_SOFT_OBJECT_CHECKED(Weapons)

	#undef CS_TEMP_GET_DATA_TABLE_SOFT_OBJECT_CHECKED

	CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to get DataTable SoftObject for MemberType."), *Context));
	return false;
}

UDataTable* FCsWpDataRootSet::GetSafeDataTable(const FString& Context, const UObject* WorldContext, const EMember& MemberType) const
{
	using namespace NCsWpDataRootSet::NCached;

	typedef NCsDataRootSet::FLibrary DataRootSetLibrary;

	#define CS_TEMP_GET_SAFE_DATA_TABLE(Member) if (MemberType == EMember::Member) \
		return DataRootSetLibrary::GetSafeDataTable(Context, WorldContext, Str::GetCsWpDataRootSet, Member, Str::Member);

	// WeaponClasses
	CS_TEMP_GET_SAFE_DATA_TABLE(WeaponClasses)
	// Weapons
	CS_TEMP_GET_SAFE_DATA_TABLE(Weapons)

	#undef CS_TEMP_GET_SAFE_DATA_TABLE

	UE_LOG(LogCsWp, Warning, TEXT("%s: Failed to get DataTable for MemberType."), *Context);
	return nullptr;
}

UDataTable* FCsWpDataRootSet::GetDataTableChecked(const FString& Context, const UObject* WorldContext, const EMember& MemberType) const
{
	using namespace NCsWpDataRootSet::NCached;

	typedef NCsDataRootSet::FLibrary DataRootSetLibrary;

	return DataRootSetLibrary::GetDataTableChecked(Context, WorldContext, GetDataTableSoftObjectChecked(Context, MemberType));
}

uint8* FCsWpDataRootSet::GetDataTableRowChecked(const FString& Context, const UObject* WorldContext, const EMember& MemberType, const FName& RowName) const
{
	using namespace NCsWpDataRootSet::NCached;

	typedef NCsDataRootSet::FLibrary DataRootSetLibrary;

	return DataRootSetLibrary::GetDataTableRowChecked(Context, WorldContext, GetDataTableSoftObjectChecked(Context, MemberType), RowName);
}

uint8* FCsWpDataRootSet::GetDataTableRowChecked(const FString& Context, const UObject* WorldContext, const EMember& MemberType, const UScriptStruct* RowStruct, const FName& RowName) const
{
	using namespace NCsWpDataRootSet::NCached;

	typedef NCsDataRootSet::FLibrary DataRootSetLibrary;

	return DataRootSetLibrary::GetDataTableRowChecked(Context, WorldContext, GetDataTableSoftObjectChecked(Context, MemberType), RowStruct, RowName);
}