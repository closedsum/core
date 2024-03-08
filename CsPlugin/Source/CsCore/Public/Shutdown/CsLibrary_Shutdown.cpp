// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Shutdown/CsLibrary_Shutdown.h"
#include "CsCore.h"

// Types
#include "Types/CsTypes_Macro.h"
// Library
	// Common
#include "Object/CsLibrary_Object.h"
#include "Library/CsLibrary_Valid.h"
// Interface
#include "Shutdown/CsShutdown.h"

namespace NCsShutdown
{
	namespace NLibrary
	{
		namespace NCached
		{
			namespace Str
			{
				// Implements
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsData::FLibrary, SafeImplements);
				// Shutdown
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsData::FLibrary, SafeHasShutdown);
			}
		}
	}

	#define USING_NS_CACHED using namespace NCsShutdown::NLibrary::NCached;
	#define SET_CONTEXT(__FunctionName) using namespace NCsShutdown::NLibrary::NCached; \
		const FString& Context = Str::__FunctionName

	// Implement
	#pragma region

	#define ObjectLibrary NCsObject::FLibrary

	bool FLibrary::ImplementsChecked(const FString& Context, const UObject* Object)
	{
		CS_IS_PENDING_KILL_CHECKED(Object)

		UClass* Class = Object->GetClass();

		checkf(Class, TEXT("%s: Failed to get class from Object: %s."), *Context, *(Object->GetName()));
		checkf(Class->ImplementsInterface(UCsShutdown::StaticClass()), TEXT("%s: %s does NOT implement the interface: ICsShutdown."), *Context, *ObjectLibrary::PrintObjectAndClass(Object));
		return true;
	}

	bool FLibrary::SafeImplements(const FString& Context, const UObject* Object, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
	{
		CS_IS_PENDING_KILL(Object)

		UClass* Class = Object->GetClass();

		if (!Class)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to get class from Object: %s."), *Context, *(Object->GetName())));
			return false;
		}

		const bool Success = Class->ImplementsInterface(UCsShutdown::StaticClass());

		if (!Success)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: %s does NOT implement the interface: ICsShutdown."), *Context, *ObjectLibrary::PrintObjectAndClass(Object)));
		}
		return Success;
	}

	bool FLibrary::SafeImplements(const UObject* Object)
	{
		SET_CONTEXT(SafeImplements);

		return SafeImplements(Context, Object, nullptr);
	}

	#undef ObjectLibrary

	#pragma endregion Implment

	// Shutdown
	#pragma region
	
	bool FLibrary::SafeHasShutdown(const FString& Context, const UObject* Object, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
	{
		CS_IS_PENDING_KILL_RET_VALUE(Object, true)

		if (!SafeImplements(Context, Object, Log))
			return false;

		const ICsShutdown* Shutdown = CS_CONST_INTERFACE_CAST(Object, UObject, ICsShutdown);

		if (Shutdown)
			return Shutdown->HasShutdown();
		return false;
	}

	bool FLibrary::SafeHasShutdown(const UObject* Object)
	{
		SET_CONTEXT(SafeHasShutdown);

		return SafeHasShutdown(Context, Object, nullptr);
	}

	#pragma endregion Shutdown

	#undef USING_NS_CACHED
	#undef SET_CONTEXT
}