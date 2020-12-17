// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Data/CsUIDataRootSet.h"
#include "CsUI.h"

// Types
#include "Types/CsTypes_Macro.h"
// Library
#include "Data/CsLibrary_DataRootSet.h"
// DataTable
#include "Engine/DataTable.h"

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
	}
}

/*
* 		_WidgetActorClasses,
		_WidgetActors,
		_UserWidgetPooledClasses,
		_UserWidgetPooled,
		_UserWidgetClasses,
		_UserWidgets
*/
#pragma endregion Cached

bool FCsUIDataRootSet::IsValidChecked(const FString& Context, UObject* Object, const EMember& MemberType) const
{
	using namespace NCsUIDataRootSet::NCached;

	#define CS_TEMP_CHECK(Member) if (MemberType == EMember::_##Member) \
	{ \
		checkf(Member.ToSoftObjectPath().IsValid(), TEXT("%s: %s.%s.%s is NOT Valid."), *Context, *(Object->GetName(), *Str::GetCsUIDataRootSet, *Str::Member)); \
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

UDataTable* FCsUIDataRootSet::GetSafeDataTable(const FString& Context, UObject* Object, const EMember& MemberType) const
{
	using namespace NCsUIDataRootSet::NCached;

	typedef NCsDataRootSet::FLibrary DataRootSetLibrary;

	#define CS_TEMP_GET_SAFE_DATA_TABLE(Member) if (MemberType == EMember::_##Member) \
		return DataRootSetLibrary::GetSafeDataTable(Context, Object, Str::GetCsUIDataRootSet, Member, Str::Member);

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