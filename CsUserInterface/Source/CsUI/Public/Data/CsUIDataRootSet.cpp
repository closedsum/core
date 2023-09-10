// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#include "Data/CsUIDataRootSet.h"
#include "CsUI.h"

// Types
#include "Types/CsTypes_Macro.h"
// Library
#include "Data/CsLibrary_DataRootSet.h"

// Cached
#pragma region

namespace NCsUIDataRootSet
{
	namespace NCached
	{
		namespace Str
		{
			CS_DEFINE_CACHED_STRING(GetCsUIDataRootSet, "GetCsUIDataRootSet()");

			CS_DEFINE_CACHED_STRING(WidgetActorClasses, "WidgetActorClasses");
			CS_DEFINE_CACHED_STRING(WidgetActors, "WidgetActors");
			CS_DEFINE_CACHED_STRING(UserWidgetPooledClasses, "UserWidgetPooledClasses");
			CS_DEFINE_CACHED_STRING(UserWidgetPooled, "UserWidgetPooled");
			CS_DEFINE_CACHED_STRING(UserWidgetClasses, "UserWidgetClasses");
			CS_DEFINE_CACHED_STRING(UserWidgets, "UserWidgets");
		}

		namespace Name
		{
			CS_DEFINE_CACHED_NAME(WidgetActorClasses, "WidgetActorClasses");
			CS_DEFINE_CACHED_NAME(WidgetActors, "WidgetActors");
			CS_DEFINE_CACHED_NAME(UserWidgetPooledClasses, "UserWidgetPooledClasses");
			CS_DEFINE_CACHED_NAME(UserWidgetPooled, "UserWidgetPooled");
			CS_DEFINE_CACHED_NAME(UserWidgetClasses, "UserWidgetClasses");
			CS_DEFINE_CACHED_NAME(UserWidgets, "UserWidgets");
		}
	}
}

#pragma endregion Cached

#define MemberType FCsUIDataRootSet::EMember
MemberType FCsUIDataRootSet::GetMember(const FName& MemberName)
{
	using namespace NCsUIDataRootSet::NCached;

	if (MemberName == Name::WidgetActorClasses)
		return MemberType::WidgetActorClasses;
	if (MemberName == Name::WidgetActors)
		return MemberType::WidgetActors;
	if (MemberName == Name::UserWidgetPooledClasses)
		return MemberType::UserWidgetPooledClasses;
	if (MemberName == Name::UserWidgetPooled)
		return MemberType::UserWidgetPooled;
	if (MemberName == Name::UserWidgetClasses)
		return MemberType::UserWidgetClasses;
	if (MemberName == Name::UserWidgets)
		return MemberType::UserWidgets;
	return MemberType::WidgetActorClasses;
}
#undef MemberType

bool FCsUIDataRootSet::IsValidChecked(const FString& Context, UObject* Object, const EMember& MemberType) const
{
	using namespace NCsUIDataRootSet::NCached;

	#define CS_TEMP_CHECK(Member) if (MemberType == EMember::Member) \
	{ \
		checkf(Member.ToSoftObjectPath().IsValid(), TEXT("%s: %s.%s.%s is NOT Valid."), *Context, *(Object->GetName()), *Str::GetCsUIDataRootSet, *Str::Member); \
	}

	// WidgetActorClasses
	CS_TEMP_CHECK(WidgetActorClasses)
	// WidgetActors
	CS_TEMP_CHECK(WidgetActors)
	// UserWidgetPooledClasses
	CS_TEMP_CHECK(UserWidgetPooledClasses)
	// UserWidgetPooled
	CS_TEMP_CHECK(UserWidgetPooled)
	// UserWidgetClasses
	CS_TEMP_CHECK(UserWidgetClasses)
	// UserWidgets
	CS_TEMP_CHECK(UserWidgets)

	#undef CS_TEMP_CHECK

	return true;
}

const TSoftObjectPtr<UDataTable>& FCsUIDataRootSet::GetDataTableSoftObjectChecked(const FString& Context, const EMember& MemberType) const
{
	#define CS_TEMP_GET_DATA_TABLE_SOFT_OBJECT_CHECKED(Member) if (MemberType == EMember::Member) \
		return Member;

	// WidgetActorClasses
	CS_TEMP_GET_DATA_TABLE_SOFT_OBJECT_CHECKED(WidgetActorClasses)
	// WidgetActors
	CS_TEMP_GET_DATA_TABLE_SOFT_OBJECT_CHECKED(WidgetActors)
	// UserWidgetPooledClasses
	CS_TEMP_GET_DATA_TABLE_SOFT_OBJECT_CHECKED(UserWidgetPooledClasses)
	// UserWidgetPooled
	CS_TEMP_GET_DATA_TABLE_SOFT_OBJECT_CHECKED(UserWidgetPooled)
	// UserWidgetClasses
	CS_TEMP_GET_DATA_TABLE_SOFT_OBJECT_CHECKED(UserWidgetClasses)
	// UserWidgets
	CS_TEMP_GET_DATA_TABLE_SOFT_OBJECT_CHECKED(UserWidgets)

	#undef CS_TEMP_GET_DATA_TABLE_SOFT_OBJECT_CHECKED

	checkf(0, TEXT("%s: Failed to get DataTable SoftObject for MemberType."), *Context);
	return WidgetActorClasses;
}

bool FCsUIDataRootSet::GetSafeDataTableSoftObject(const FString& Context, const EMember& MemberType, TSoftObjectPtr<UDataTable>& OutSoftObject, void(*Log)(const FString&) /*=&NCsUI::FLog::Warning*/) const
{
	#define CS_TEMP_GET_DATA_TABLE_SOFT_OBJECT_CHECKED(Member) if (MemberType == EMember::Member) \
		{ \
			OutSoftObject = Member; \
			return true; \
		}

	// WidgetActorClasses
	CS_TEMP_GET_DATA_TABLE_SOFT_OBJECT_CHECKED(WidgetActorClasses)
	// WidgetActors
	CS_TEMP_GET_DATA_TABLE_SOFT_OBJECT_CHECKED(WidgetActors)
	// UserWidgetPooledClasses
	CS_TEMP_GET_DATA_TABLE_SOFT_OBJECT_CHECKED(UserWidgetPooledClasses)
	// UserWidgetPooled
	CS_TEMP_GET_DATA_TABLE_SOFT_OBJECT_CHECKED(UserWidgetPooled)
	// UserWidgetClasses
	CS_TEMP_GET_DATA_TABLE_SOFT_OBJECT_CHECKED(UserWidgetClasses)
	// UserWidgets
	CS_TEMP_GET_DATA_TABLE_SOFT_OBJECT_CHECKED(UserWidgets)

	#undef CS_TEMP_GET_DATA_TABLE_SOFT_OBJECT_CHECKED

	CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to get DataTable SoftObject for MemberType."), *Context));
	return false;
}

UDataTable* FCsUIDataRootSet::GetSafeDataTable(const FString& Context, const UObject* WorldContext, const EMember& MemberType) const
{
	using namespace NCsUIDataRootSet::NCached;

	typedef NCsDataRootSet::FLibrary DataRootSetLibrary;

	#define CS_TEMP_GET_SAFE_DATA_TABLE(Member) if (MemberType == EMember::Member) \
		return DataRootSetLibrary::GetSafeDataTable(Context, WorldContext, Str::GetCsUIDataRootSet, Member, Str::Member);

	// WidgetActorClasses
	CS_TEMP_GET_SAFE_DATA_TABLE(WidgetActorClasses)
	// WidgetActors
	CS_TEMP_GET_SAFE_DATA_TABLE(WidgetActors)
	// UserWidgetPooledClasses
	CS_TEMP_GET_SAFE_DATA_TABLE(UserWidgetPooledClasses)
	// UserWidgetPooled
	CS_TEMP_GET_SAFE_DATA_TABLE(UserWidgetPooled)
	// UserWidgetClasses
	CS_TEMP_GET_SAFE_DATA_TABLE(UserWidgetClasses)
	// UserWidgets
	CS_TEMP_GET_SAFE_DATA_TABLE(UserWidgets)

	#undef CS_TEMP_GET_SAFE_DATA_TABLE

	UE_LOG(LogCsUI, Warning, TEXT("%s: Failed to get DataTable for MemberType."));
	return nullptr;
}

UDataTable* FCsUIDataRootSet::GetDataTableChecked(const FString& Context, const UObject* WorldContext, const EMember& MemberType) const
{
	using namespace NCsUIDataRootSet::NCached;

	typedef NCsDataRootSet::FLibrary DataRootSetLibrary;

	return DataRootSetLibrary::GetDataTableChecked(Context, WorldContext, GetDataTableSoftObjectChecked(Context, MemberType));
}

uint8* FCsUIDataRootSet::GetDataTableRowChecked(const FString& Context, const UObject* WorldContext, const EMember& MemberType, const FName& RowName) const
{
	using namespace NCsUIDataRootSet::NCached;

	typedef NCsDataRootSet::FLibrary DataRootSetLibrary;

	return DataRootSetLibrary::GetDataTableRowChecked(Context, WorldContext, GetDataTableSoftObjectChecked(Context, MemberType), RowName);
}

uint8* FCsUIDataRootSet::GetDataTableRowChecked(const FString& Context, const UObject* WorldContext, const EMember& MemberType, const UScriptStruct* RowStruct, const FName& RowName) const
{
	using namespace NCsUIDataRootSet::NCached;

	typedef NCsDataRootSet::FLibrary DataRootSetLibrary;

	return DataRootSetLibrary::GetDataTableRowChecked(Context, WorldContext, GetDataTableSoftObjectChecked(Context, MemberType), RowStruct, RowName);
}