// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Data/CsDmgDataRootSet.h"
#include "CsDmg.h"

// Library
#include "Data/CsLibrary_DataRootSet.h"
#include "Data/CsDmgLibrary_DataRootSet.h"
#include "Level/CsLibrary_Level.h"
#include "Library/CsLibrary_Valid.h"

#if WITH_EDITOR
// Library
	// Common
#include "Library/CsLibrary_World.h"
#include "Library/Load/CsLibrary_Load.h"
#endif // #if WITH_EDITOR

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

		namespace Name
		{
			CS_DEFINE_CACHED_NAME(Damages, "Damages");
		}
	}
}

#pragma endregion Cached

#define MemberType FCsDmgDataRootSet::EMember
MemberType FCsDmgDataRootSet::GetMember(const FName& MemberName)
{
	using namespace NCsDmgDataRootSet::NCached;

	if (MemberName == Name::Damages)
		return MemberType::Damages;
	return MemberType::Damages;
}
#undef MemberType

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

bool FCsDmgDataRootSet::GetSafeDataTableSoftObject(const FString& Context, const EMember& MemberType, TSoftObjectPtr<UDataTable>& OutSoftObject, void(*Log)(const FString&) /*=&NCsDamage::FLog::Warning*/) const
{
	#define CS_TEMP_GET_DATA_TABLE_SOFT_OBJECT_CHECKED(Member) if (MemberType == EMember::Member) \
		{ \
			OutSoftObject = Member; \
			return true; \
		}

	// Damages
	CS_TEMP_GET_DATA_TABLE_SOFT_OBJECT_CHECKED(Damages)

	#undef CS_TEMP_GET_DATA_TABLE_SOFT_OBJECT_CHECKED

	CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to get DataTable SoftObject for MemberType."), *Context));
	return false;
}

UDataTable* FCsDmgDataRootSet::GetSafeDataTable(const FString& Context, const UObject* WorldContext, const EMember& MemberType) const
{
	using namespace NCsDmgDataRootSet::NCached;

	typedef NCsDataRootSet::FLibrary DataRootSetLibrary;

	#define CS_TEMP_GET_SAFE_DATA_TABLE(Member) if (MemberType == EMember::Member) \
		return DataRootSetLibrary::GetSafeDataTable(Context, WorldContext, Str::GetCsDmgDataRootSet, Member, Str::Member);

	// Damages
	CS_TEMP_GET_SAFE_DATA_TABLE(Damages)

	#undef CS_TEMP_GET_SAFE_DATA_TABLE

	UE_LOG(LogCsDmg, Warning, TEXT("%s: Failed to get DataTable for MemberType."), *Context);
	return nullptr;
}

UDataTable* FCsDmgDataRootSet::GetDataTableChecked(const FString& Context, const UObject* WorldContext, const EMember& MemberType) const
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

UDataTable* FCsDmgDataRootSet::GetDataTableChecked(const FString& Context, const EMember& MemberType) const
{
	const TSoftObjectPtr<UDataTable>& SoftObject = GetDataTableSoftObjectChecked(Context, MemberType);
	UDataTable* DT								 = SoftObject.LoadSynchronous();

	checkf(DT, TEXT("%s: Failed to Load DataTalbe at %s."), *Context, *(SoftObject.ToString()));

#if WITH_EDITOR
	UCsLibrary_Load::LoadDataTable(DT, NCsLoadFlags::All, NCsLoadCodes::All);
#endif // #if WITH_EDITOR

	return DT;
}

uint8* FCsDmgDataRootSet::GetDataTableRowChecked(const FString& Context, const UObject* WorldContext, const EMember& MemberType, const FName& RowName) const
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

uint8* FCsDmgDataRootSet::GetDataTableRowChecked(const FString& Context, const UObject* WorldContext, const EMember& MemberType, const UScriptStruct* RowStruct, const FName& RowName) const
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

uint8* FCsDmgDataRootSet::GetDataTableRowChecked(const FString& Context, const EMember& MemberType, const FName& RowName) const
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

uint8* FCsDmgDataRootSet::GetDataTableRowChecked(const FString& Context, const EMember& MemberType, const UScriptStruct* RowStruct, const FName& RowName) const
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