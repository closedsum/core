// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#include "Data/CsSeDataRootSet.h"
#include "CsSe.h"

// Types
#include "Types/CsTypes_Macro.h"
// Library
#include "Data/CsLibrary_DataRootSet.h"
// DataTable
#include "Engine/DataTable.h"

// Cached
#pragma region

namespace NCsSeDataRootSet
{
	namespace NCached
	{
		namespace Str
		{
			CS_DEFINE_CACHED_STRING(GetCsSeDataRootSet, "GetCsSeDataRootSet()");

			CS_DEFINE_CACHED_STRING(StatusEffects, "StatusEffects");
		}
	}
}

#pragma endregion Cached

bool FCsSeDataRootSet::IsValidChecked(const FString& Context, const UObject* WorldContext, const EMember& MemberType) const
{
	using namespace NCsSeDataRootSet::NCached;

	#define CS_TEMP_CHECK(Member) if (MemberType == EMember::Member) \
	{ \
		checkf(Member.ToSoftObjectPath().IsValid(), TEXT("%s: %s.%s.%s is NOT Valid."), *Context, *(WorldContext->GetName(), *Str::GetCsSeDataRootSet, *Str::Member)); \
	}

	// StatusEffects
	CS_TEMP_CHECK(StatusEffects)

	#undef CS_TEMP_CHECK

	return true;
}

const TSoftObjectPtr<UDataTable>& FCsSeDataRootSet::GetDataTableSoftObjectChecked(const FString& Context, const EMember& MemberType) const
{
	#define CS_TEMP_GET_DATA_TABLE_SOFT_OBJECT_CHECKED(Member) if (MemberType == EMember::Member) \
		return Member;

	// StatusEffects
	CS_TEMP_GET_DATA_TABLE_SOFT_OBJECT_CHECKED(StatusEffects)

	#undef CS_TEMP_GET_DATA_TABLE_SOFT_OBJECT_CHECKED

	checkf(0, TEXT("%s: Failed to get DataTable SoftObject for MemberType."), *Context);
	return StatusEffects;
}

bool FCsSeDataRootSet::GetSafeDataTableSoftObject(const FString& Context, const EMember& MemberType, TSoftObjectPtr<UDataTable>& OutSoftObject, void(*Log)(const FString&) /*=&NCsProjectile::FLog::Warning*/) const
{
	#define CS_TEMP_GET_DATA_TABLE_SOFT_OBJECT_CHECKED(Member) if (MemberType == EMember::Member) \
		{ \
			OutSoftObject = Member; \
			return true; \
		}

	// StatusEffects
	CS_TEMP_GET_DATA_TABLE_SOFT_OBJECT_CHECKED(StatusEffects)

	#undef CS_TEMP_GET_DATA_TABLE_SOFT_OBJECT_CHECKED

	CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to get DataTable SoftObject for MemberType."), *Context));
	return false;
}

UDataTable* FCsSeDataRootSet::GetSafeDataTable(const FString& Context, const UObject* WorldContext, const EMember& MemberType) const
{
	using namespace NCsSeDataRootSet::NCached;

	typedef NCsDataRootSet::FLibrary DataRootSetLibrary;

	#define CS_TEMP_GET_SAFE_DATA_TABLE(Member) if (MemberType == EMember::Member) \
		return DataRootSetLibrary::GetSafeDataTable(Context, WorldContext, Str::GetCsSeDataRootSet, Member, Str::Member);

	// StatusEffects
	CS_TEMP_GET_SAFE_DATA_TABLE(StatusEffects)

	#undef CS_TEMP_GET_SAFE_DATA_TABLE

	UE_LOG(LogCsSe, Warning, TEXT("%s: Failed to get DataTable for MemberType."), *Context);
	return nullptr;
}

UDataTable* FCsSeDataRootSet::GetDataTableChecked(const FString& Context, const UObject* WorldContext, const EMember& MemberType) const
{
	using namespace NCsSeDataRootSet::NCached;

	typedef NCsDataRootSet::FLibrary DataRootSetLibrary;

	return DataRootSetLibrary::GetDataTableChecked(Context, WorldContext, GetDataTableSoftObjectChecked(Context, MemberType));
}

uint8* FCsSeDataRootSet::GetDataTableRowChecked(const FString& Context, const UObject* WorldContext, const EMember& MemberType, const FName& RowName) const
{
	using namespace NCsSeDataRootSet::NCached;

	typedef NCsDataRootSet::FLibrary DataRootSetLibrary;

	return DataRootSetLibrary::GetDataTableRowChecked(Context, WorldContext, GetDataTableSoftObjectChecked(Context, MemberType), RowName);
}

uint8* FCsSeDataRootSet::GetDataTableRowChecked(const FString& Context, const UObject* WorldContext, const EMember& MemberType, const UScriptStruct* RowStruct, const FName& RowName) const
{
	using namespace NCsSeDataRootSet::NCached;

	typedef NCsDataRootSet::FLibrary DataRootSetLibrary;

	return DataRootSetLibrary::GetDataTableRowChecked(Context, WorldContext, GetDataTableSoftObjectChecked(Context, MemberType), RowStruct, RowName);
}