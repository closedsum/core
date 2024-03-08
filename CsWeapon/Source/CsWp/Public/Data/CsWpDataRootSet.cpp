// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#include "Data/CsWpDataRootSet.h"
#include "CsWp.h"

// Types
#include "Types/CsTypes_Macro.h"
// Library
#include "Data/CsLibrary_DataRootSet.h"
	// Common
#include "Library/CsLibrary_Valid.h"

#if WITH_EDITOR
// Library
	// Common
#include "Library/CsLibrary_World.h"
#include "Library/Load/CsLibrary_Load.h"
#endif // #if WITH_EDITOR

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
			CS_DEFINE_CACHED_STRING(WeaponSkins, "WeaponSkins");
		}

		namespace Name
		{
			CS_DEFINE_CACHED_NAME(WeaponClasses, "WeaponClasses");
			CS_DEFINE_CACHED_NAME(Weapons, "Weapons");
			CS_DEFINE_CACHED_NAME(WeaponSkins, "WeaponSkins");
		}
	}
}

#pragma endregion Cached

#define MemberType FCsWpDataRootSet::EMember
MemberType FCsWpDataRootSet::GetMember(const FName& MemberName)
{
	using namespace NCsWpDataRootSet::NCached;

	if (MemberName == Name::WeaponClasses)
		return MemberType::WeaponClasses;
	if (MemberName == Name::Weapons)
		return MemberType::Weapons;
	if (MemberName == Name::WeaponSkins)
		return MemberType::WeaponSkins;
	check(0);
	return MemberType::WeaponClasses;
}
#undef MemberType

bool FCsWpDataRootSet::IsValidChecked(const FString& Context, const UObject* WorldContext, const EMember& MemberType) const
{
	using namespace NCsWpDataRootSet::NCached;

	#define CS_TEMP_CHECK(Member) if (MemberType == EMember::Member) \
	{ \
		checkf(Member.ToSoftObjectPath().IsValid(), TEXT("%s: %s.%s.%s is NOT Valid."), *Context, *(WorldContext->GetName()), *Str::GetCsWpDataRootSet, *Str::Member); \
	}

	// WeaponClasses
	CS_TEMP_CHECK(WeaponClasses)
	// Weapons
	CS_TEMP_CHECK(Weapons)
	// WeaponSkins
	CS_TEMP_CHECK(WeaponSkins)

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
	// WeaponSkins
	CS_TEMP_GET_DATA_TABLE_SOFT_OBJECT_CHECKED(WeaponSkins)

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
	// WeaponSkins
	CS_TEMP_GET_DATA_TABLE_SOFT_OBJECT_CHECKED(WeaponSkins)

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
	// WeaponSkins
	CS_TEMP_GET_SAFE_DATA_TABLE(WeaponSkins)

	#undef CS_TEMP_GET_SAFE_DATA_TABLE

	UE_LOG(LogCsWp, Warning, TEXT("%s: Failed to get DataTable for MemberType."), *Context);
	return nullptr;
}

UDataTable* FCsWpDataRootSet::GetDataTableChecked(const FString& Context, const UObject* WorldContext, const EMember& MemberType) const
{
#if WITH_EDITOR
	typedef NCsWorld::FLibrary WorldLibrary;

	if (WorldLibrary::IsPlayInEditorOrEditorPreview(WorldContext))
	{
		return GetDataTableChecked(Context, MemberType);
	}
#endif // #if WITH_EDITOR

	typedef NCsDataRootSet::FLibrary DataRootSetLibrary;

	return DataRootSetLibrary::GetDataTableChecked(Context, WorldContext, GetDataTableSoftObjectChecked(Context, MemberType));
}

UDataTable* FCsWpDataRootSet::GetDataTableChecked(const FString& Context, const EMember& MemberType) const
{
	const TSoftObjectPtr<UDataTable>& SoftObject = GetDataTableSoftObjectChecked(Context, MemberType);
	UDataTable* DT = SoftObject.LoadSynchronous();

	checkf(DT, TEXT("%s: Failed to Load DataTalbe at %s."), *Context, *(SoftObject.ToString()));

#if WITH_EDITOR
	UCsLibrary_Load::LoadDataTable(DT, NCsLoadFlags::All, NCsLoadCodes::All);
#endif // #if WITH_EDITOR

	return DT;
}

uint8* FCsWpDataRootSet::GetDataTableRowChecked(const FString& Context, const UObject* WorldContext, const EMember& MemberType, const FName& RowName) const
{
#if WITH_EDITOR
	typedef NCsWorld::FLibrary WorldLibrary;

	if (WorldLibrary::IsPlayInEditorOrEditorPreview(WorldContext))
	{
		return GetDataTableRowChecked(Context, MemberType, RowName);
	}
#endif // #if WITH_EDITOR

	typedef NCsDataRootSet::FLibrary DataRootSetLibrary;

	return DataRootSetLibrary::GetDataTableRowChecked(Context, WorldContext, GetDataTableSoftObjectChecked(Context, MemberType), RowName);
}

uint8* FCsWpDataRootSet::GetDataTableRowChecked(const FString& Context, const UObject* WorldContext, const EMember& MemberType, const UScriptStruct* RowStruct, const FName& RowName) const
{
#if WITH_EDITOR
	typedef NCsWorld::FLibrary WorldLibrary;

	if (WorldLibrary::IsPlayInEditorOrEditorPreview(WorldContext))
	{
		return GetDataTableRowChecked(Context, MemberType, RowStruct, RowName);
	}
#endif // #if WITH_EDITOR

	typedef NCsDataRootSet::FLibrary DataRootSetLibrary;

	return DataRootSetLibrary::GetDataTableRowChecked(Context, WorldContext, GetDataTableSoftObjectChecked(Context, MemberType), RowStruct, RowName);
}

uint8* FCsWpDataRootSet::GetDataTableRowChecked(const FString& Context, const EMember& MemberType, const FName& RowName) const
{
	UDataTable* DT = GetDataTableChecked(Context, MemberType);

	const TMap<FName, uint8*>& RowMap = DT->GetRowMap();

	for (const TPair<FName, uint8*>& Pair : RowMap)
	{
		const FName& Name = Pair.Key;
		uint8* RowPtr	  = Pair.Value;

		if (Name == RowName)
			return RowPtr;
	}
	checkf(0, TEXT("Failed to find Row with Name: %s from DataTable: %s."), *Context, *(RowName.ToString()), *(DT->GetName()));
	return nullptr;
}

uint8* FCsWpDataRootSet::GetDataTableRowChecked(const FString& Context, const EMember& MemberType, const UScriptStruct* RowStruct, const FName& RowName) const
{
	UDataTable* DT = GetDataTableChecked(Context, MemberType);

	CS_IS_PTR_NULL_CHECKED(RowStruct)

	checkf(DT->GetRowStruct() == RowStruct, TEXT("%s: DataTable: %s RowStruct: %s != %s."), *Context, *(DT->GetName()), *(DT->GetRowStruct()->GetName()), *(RowStruct->GetName()));

	const TMap<FName, uint8*>& RowMap = DT->GetRowMap();

	for (const TPair<FName, uint8*>& Pair : RowMap)
	{
		const FName& Name = Pair.Key;
		uint8* RowPtr = Pair.Value;

		if (Name == RowName)
			return RowPtr;
	}
	checkf(0, TEXT("Failed to find Row with Name: %s from DataTable: %s."), *Context, *(RowName.ToString()), *(DT->GetName()));
	return nullptr;
}