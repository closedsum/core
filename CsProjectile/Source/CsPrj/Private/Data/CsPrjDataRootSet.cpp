// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Data/CsPrjDataRootSet.h"
#include "CsPrj.h"

// Types
#include "CsMacro_Misc.h"
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

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsPrjDataRootSet)

// Cached
#pragma region

namespace NCsPrjDataRootSet
{
	namespace NCached
	{
		namespace Str
		{
			CS_DEFINE_CACHED_STRING(GetCsPrjDataRootSet, "GetCsPrjDataRootSet()");

			CS_DEFINE_CACHED_STRING(Projectiles, "Projectiles");
			CS_DEFINE_CACHED_STRING(ProjectileClasses, "ProjectileClasses");
		}

		namespace Name
		{
			CS_DEFINE_CACHED_NAME(Projectiles, "Projectiles");
			CS_DEFINE_CACHED_NAME(ProjectileClasses, "ProjectileClasses");
		}
	}
}

#pragma endregion Cached

#define MemberType FCsPrjDataRootSet::EMember
MemberType FCsPrjDataRootSet::GetMember(const FName& MemberName)
{
	using namespace NCsPrjDataRootSet::NCached;

	if (MemberName == Name::Projectiles)
		return MemberType::Projectiles;
	if (MemberName == Name::ProjectileClasses)
		return MemberType::ProjectileClasses;
	check(0);
	return MemberType::Projectiles;
}
#undef MemberType

bool FCsPrjDataRootSet::IsValidChecked(const FString& Context, const UObject* WorldContext, const EMember& MemberType) const
{
	using namespace NCsPrjDataRootSet::NCached;

	#define CS_TEMP_CHECK(Member) if (MemberType == EMember::Member) \
	{ \
		checkf(Member.ToSoftObjectPath().IsValid(), TEXT("%s: %s.%s.%s is NOT Valid."), *Context, *(WorldContext->GetName()), *Str::GetCsPrjDataRootSet, *Str::Member); \
	}

	// Projectiles
	CS_TEMP_CHECK(Projectiles)
	// ProjectileClasses
	CS_TEMP_CHECK(ProjectileClasses)

	#undef CS_TEMP_CHECK

	return true;
}

const TSoftObjectPtr<UDataTable>& FCsPrjDataRootSet::GetDataTableSoftObjectChecked(const FString& Context, const EMember& MemberType) const
{
	#define CS_TEMP_GET_DATA_TABLE_SOFT_OBJECT_CHECKED(Member) if (MemberType == EMember::Member) \
		return Member;

	// Projectiles
	CS_TEMP_GET_DATA_TABLE_SOFT_OBJECT_CHECKED(Projectiles)
	// ProjectileClasses
	CS_TEMP_GET_DATA_TABLE_SOFT_OBJECT_CHECKED(ProjectileClasses)

	#undef CS_TEMP_GET_DATA_TABLE_SOFT_OBJECT_CHECKED

	checkf(0, TEXT("%s: Failed to get DataTable SoftObject for MemberType."), *Context);
	return ProjectileClasses;
}

bool FCsPrjDataRootSet::GetSafeDataTableSoftObject(const FString& Context, const EMember& MemberType, TSoftObjectPtr<UDataTable>& OutSoftObject, void(*Log)(const FString&) /*=&NCsProjectile::FLog::Warning*/) const
{
	#define CS_TEMP_GET_DATA_TABLE_SOFT_OBJECT_CHECKED(Member) if (MemberType == EMember::Member) \
		{ \
			OutSoftObject = Member; \
			return true; \
		}

	// Projectiles
	CS_TEMP_GET_DATA_TABLE_SOFT_OBJECT_CHECKED(Projectiles)
	// ProjectileClasses
	CS_TEMP_GET_DATA_TABLE_SOFT_OBJECT_CHECKED(ProjectileClasses)

	#undef CS_TEMP_GET_DATA_TABLE_SOFT_OBJECT_CHECKED

	CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to get DataTable SoftObject for MemberType."), *Context));
	return false;
}

UDataTable* FCsPrjDataRootSet::GetSafeDataTable(const FString& Context, const UObject* WorldContext, const EMember& MemberType) const
{
	using namespace NCsPrjDataRootSet::NCached;

	typedef NCsDataRootSet::FLibrary DataRootSetLibrary;

	#define CS_TEMP_GET_SAFE_DATA_TABLE(Member) if (MemberType == EMember::Member) \
		return DataRootSetLibrary::GetSafeDataTable(Context, WorldContext, Str::GetCsPrjDataRootSet, Member, Str::Member);

	// Projectiles
	CS_TEMP_GET_SAFE_DATA_TABLE(Projectiles)
	// ProjectileClasses
	CS_TEMP_GET_SAFE_DATA_TABLE(ProjectileClasses)

	#undef CS_TEMP_GET_SAFE_DATA_TABLE

	UE_LOG(LogCsPrj, Warning, TEXT("%s: Failed to get DataTable for MemberType."), *Context);
	return nullptr;
}

UDataTable* FCsPrjDataRootSet::GetDataTableChecked(const FString& Context, const UObject* WorldContext, const EMember& MemberType) const
{
#if WITH_EDITOR
	if (CsWorldLibrary::IsPlayInEditorOrEditorPreview(WorldContext))
	{
		return GetDataTableChecked(Context, MemberType);
	}
#endif // #if WITH_EDITOR

	typedef NCsDataRootSet::FLibrary DataRootSetLibrary;

	return DataRootSetLibrary::GetDataTableChecked(Context, WorldContext, GetDataTableSoftObjectChecked(Context, MemberType));
}

UDataTable* FCsPrjDataRootSet::GetDataTableChecked(const FString& Context, const EMember& MemberType) const
{
	const TSoftObjectPtr<UDataTable>& SoftObject = GetDataTableSoftObjectChecked(Context, MemberType);
	UDataTable* DT								 = SoftObject.LoadSynchronous();

	checkf(DT, TEXT("%s: Failed to Load DataTalbe at %s."), *Context, *(SoftObject.ToString()));

#if WITH_EDITOR
	CsLoadLibrary::LoadDataTable(DT, NCsLoadFlags::All, NCsLoadCodes::All);
#endif // #if WITH_EDITOR

	return DT;
}

uint8* FCsPrjDataRootSet::GetDataTableRowChecked(const FString& Context, const UObject* WorldContext, const EMember& MemberType, const FName& RowName) const
{
#if WITH_EDITOR
	if (CsWorldLibrary::IsPlayInEditorOrEditorPreview(WorldContext))
	{
		return GetDataTableRowChecked(Context, MemberType, RowName);
	}
#endif // #if WITH_EDITOR

	typedef NCsDataRootSet::FLibrary DataRootSetLibrary;

	return DataRootSetLibrary::GetDataTableRowChecked(Context, WorldContext, GetDataTableSoftObjectChecked(Context, MemberType), RowName);
}

uint8* FCsPrjDataRootSet::GetDataTableRowChecked(const FString& Context, const UObject* WorldContext, const EMember& MemberType, const UScriptStruct* RowStruct, const FName& RowName) const
{
#if WITH_EDITOR
	if (CsWorldLibrary::IsPlayInEditorOrEditorPreview(WorldContext))
	{
		return GetDataTableRowChecked(Context, MemberType, RowStruct, RowName);
	}
#endif // #if WITH_EDITOR

	typedef NCsDataRootSet::FLibrary DataRootSetLibrary;

	return DataRootSetLibrary::GetDataTableRowChecked(Context, WorldContext, GetDataTableSoftObjectChecked(Context, MemberType), RowStruct, RowName);
}

uint8* FCsPrjDataRootSet::GetDataTableRowChecked(const FString& Context, const EMember& MemberType, const FName& RowName) const
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

uint8* FCsPrjDataRootSet::GetDataTableRowChecked(const FString& Context, const EMember& MemberType, const UScriptStruct* RowStruct, const FName& RowName) const
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