// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#include "Data/CsDmgDataRootSet.h"
#include "CsDmg.h"

// Library
#include "Data/CsLibrary_DataRootSet.h"
#include "Data/CsDmgLibrary_DataRootSet.h"
#include "Level/CsLibrary_Level.h"
#include "Library/CsLibrary_Valid.h"

// Cached
#pragma region

namespace NCsDmgDataRootSet
{
	namespace NCached
	{
		namespace Str
		{
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(FCsDmgDataRootSet, AddDataTable);

			CS_DEFINE_CACHED_STRING(GetCsDmgDataRootSet, "GetCsDmgDataRootSet()");

			CS_DEFINE_CACHED_STRING(Damages, "Damages");
		}
	}
}

#pragma endregion Cached

bool FCsDmgDataRootSet::IsValidChecked(const FString& Context, const UObject* WorldContext, const EMember& MemberType) const
{
	using namespace NCsDmgDataRootSet::NCached;

	#define CS_TEMP_CHECK(Member) if (MemberType == EMember::Member) \
	{ \
		checkf(Member.ToSoftObjectPath().IsValid(), TEXT("%s: %s.%s.%s is NOT Valid."), *Context, *(WorldContext->GetName(), *Str::GetCsDmgDataRootSet, *Str::Member)); \
	}

	// Damages
	CS_TEMP_CHECK(Damages)

	#undef CS_TEMP_CHECK

	return true;
}

const TSoftObjectPtr<UDataTable>& FCsDmgDataRootSet::GetDataTableSoftObjectChecked(const FString& Context, const EMember& MemberType) const
{
	#define CS_TEMP_GET_DATA_TABLE_SOFT_OBJECT_CHECKED(Member) if (MemberType == EMember::Member) \
		return Member;

	// Damages
	CS_TEMP_GET_DATA_TABLE_SOFT_OBJECT_CHECKED(Damages)

	#undef CS_TEMP_GET_DATA_TABLE_SOFT_OBJECT_CHECKED

	checkf(0, TEXT("%s: Failed to get DataTable SoftObject for MemberType."), *Context);
	return Damages;
}

UDataTable* FCsDmgDataRootSet::GetSafeDataTable(const FString& Context, const UObject* WorldContext, const EMember& MemberType) const
{
	using namespace NCsDmgDataRootSet::NCached;

	typedef NCsDamage::NDataRootSet::FLibrary DataRootSetLibrary;

	#define CS_TEMP_GET_SAFE_DATA_TABLE(Member) if (MemberType == EMember::Member) \
		return DataRootSetLibrary::GetSafeDataTable(Context, WorldContext, EMember::Member);

	// Damages
	CS_TEMP_GET_SAFE_DATA_TABLE(Damages)

	#undef CS_TEMP_GET_SAFE_DATA_TABLE

	UE_LOG(LogCsDmg, Warning, TEXT("%s: Failed to get DataTable for MemberType."), *Context);
	return nullptr;
}

UDataTable* FCsDmgDataRootSet::GetDataTableChecked(const FString& Context, const UObject* WorldContext, const EMember& MemberType) const
{
	using namespace NCsDmgDataRootSet::NCached;

	typedef NCsDataRootSet::FLibrary DataRootSetLibrary;

	return DataRootSetLibrary::GetDataTableChecked(Context, WorldContext, GetDataTableSoftObjectChecked(Context, MemberType));
}

uint8* FCsDmgDataRootSet::GetDataTableRowChecked(const FString& Context, const UObject* WorldContext, const EMember& MemberType, const FName& RowName) const
{
	using namespace NCsDmgDataRootSet::NCached;

	typedef NCsDataRootSet::FLibrary DataRootSetLibrary;

	return DataRootSetLibrary::GetDataTableRowChecked(Context, WorldContext, GetDataTableSoftObjectChecked(Context, MemberType), RowName);
}

uint8* FCsDmgDataRootSet::GetDataTableRowChecked(const FString& Context, const UObject* WorldContext, const EMember& MemberType, const UScriptStruct* RowStruct, const FName& RowName) const
{
	using namespace NCsDmgDataRootSet::NCached;

	typedef NCsDataRootSet::FLibrary DataRootSetLibrary;

	return DataRootSetLibrary::GetDataTableRowChecked(Context, WorldContext, GetDataTableSoftObjectChecked(Context, MemberType), RowStruct, RowName);
}