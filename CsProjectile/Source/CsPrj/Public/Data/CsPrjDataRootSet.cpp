// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Data/CsPrjDataRootSet.h"
#include "CsPrj.h"

// Types
#include "Types/CsTypes_Macro.h"
// Library
#include "Data/CsLibrary_DataRootSet.h"

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
	}
}

#pragma endregion Cached


bool FCsPrjDataRootSet::IsValidChecked(const FString& Context, const UObject* WorldContext, const EMember& MemberType) const
{
	using namespace NCsPrjDataRootSet::NCached;

	#define CS_TEMP_CHECK(Member) if (MemberType == EMember::Member) \
	{ \
		checkf(Member.ToSoftObjectPath().IsValid(), TEXT("%s: %s.%s.%s is NOT Valid."), *Context, *(WorldContext->GetName(), *Str::GetCsPrjDataRootSet, *Str::Member)); \
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
	using namespace NCsPrjDataRootSet::NCached;

	typedef NCsDataRootSet::FLibrary DataRootSetLibrary;

	return DataRootSetLibrary::GetDataTableChecked(Context, WorldContext, GetDataTableSoftObjectChecked(Context, MemberType));
}

uint8* FCsPrjDataRootSet::GetDataTableRowChecked(const FString& Context, const UObject* WorldContext, const EMember& MemberType, const FName& RowName) const
{
	using namespace NCsPrjDataRootSet::NCached;

	typedef NCsDataRootSet::FLibrary DataRootSetLibrary;

	return DataRootSetLibrary::GetDataTableRowChecked(Context, WorldContext, GetDataTableSoftObjectChecked(Context, MemberType), RowName);
}

uint8* FCsPrjDataRootSet::GetDataTableRowChecked(const FString& Context, const UObject* WorldContext, const EMember& MemberType, const UScriptStruct* RowStruct, const FName& RowName) const
{
	using namespace NCsPrjDataRootSet::NCached;

	typedef NCsDataRootSet::FLibrary DataRootSetLibrary;

	return DataRootSetLibrary::GetDataTableRowChecked(Context, WorldContext, GetDataTableSoftObjectChecked(Context, MemberType), RowStruct, RowName);
}