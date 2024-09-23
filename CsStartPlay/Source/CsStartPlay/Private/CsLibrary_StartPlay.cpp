// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "CsLibrary_StartPlay.h"

// Types
#include "CsMacro_Misc.h"
// Library
#include "Object/CsLibrary_Object.h"
#include "Library/CsLibrary_Valid.h"
// Start
#include "CsScriptStartPlay.h"

namespace NCsStartPlay
{
	#define LogLevel void(*Log)(const FString&) /*=&NCsStartPlay::FLog::Warning*/

	bool FLibrary::ImplementsChecked(const FString& Context, const UObject* Object)
	{
		CS_IS_PENDING_KILL_CHECKED(Object)

		if (Cast<ICsStartPlay>(Object) ||
			Object->GetClass()->ImplementsInterface(UCsScriptStartPlay::StaticClass()))
			return true;

		checkf(0, TEXT("%s %s does NOT implement the interface: ICsStartPlay."), *Context, *CsObjectLibrary::PrintObjectAndClass(Object));
		return true;
	}

	bool FLibrary::ImplementsChecked(const FString& Context, const UObject* Object, bool& OutIsScript)
	{
		CS_IS_PENDING_KILL_CHECKED(Object)

		if (Cast<ICsStartPlay>(Object))
		{
			OutIsScript = false;
			return true;
		}
			
		if (Object->GetClass()->ImplementsInterface(UCsScriptStartPlay::StaticClass()))
		{
			OutIsScript = true;
			return true;
		}
		checkf(0, TEXT("%s %s does NOT implement the interface: ICsStartPlay."), *Context, *CsObjectLibrary::PrintObjectAndClass(Object));
		return true;
	}

	bool FLibrary::SafeImplements(const FString& Context, const UObject* Object, LogLevel)
	{
		CS_IS_PENDING_KILL(Object)

		if (Cast<ICsStartPlay>(Object) ||
			Object->GetClass()->ImplementsInterface(UCsScriptStartPlay::StaticClass()))
			return true;

		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s %s does NOT implement the interface: ICsStartPlay."), *Context, *CsObjectLibrary::PrintObjectAndClass(Object)));
		return true;
	}

	bool FLibrary::SafeImplements(const FString& Context, const UObject* Object, bool& OutIsScript, LogLevel)
	{
		CS_IS_PENDING_KILL(Object)

		if (Cast<ICsStartPlay>(Object))
		{
			OutIsScript = false;
			return true;
		}
			
		if (Object->GetClass()->ImplementsInterface(UCsScriptStartPlay::StaticClass()))
		{
			OutIsScript = true;
			return true;
		}

		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s %s does NOT implement the interface: ICsStartPlay."), *Context, *CsObjectLibrary::PrintObjectAndClass(Object)));
		return true;
	}

	bool FLibrary::HasStartedPlayChecked(const FString& Context, const UObject* Object)
	{
		CS_IS_PENDING_KILL_CHECKED(Object)

		if (const ICsStartPlay* Interface = Cast<ICsStartPlay>(Object))
		{
			return Interface->HasStartedPlay();
		}

		if (Object->GetClass()->ImplementsInterface(UCsStartPlay::StaticClass()))
		{
			return ICsScriptStartPlay::Execute_Script_HasStartedPlay(Object);
		}

		checkf(0, TEXT("%s %s does NOT implement the interface: ICsStartPlay."), *Context, *CsObjectLibrary::PrintObjectAndClass(Object));
		return false;
	}

	bool FLibrary::SafeHasStartedPlay(const FString& Context, const UObject* Object, LogLevel)
	{
		CS_IS_PENDING_KILL(Object)

		if (const ICsStartPlay* Interface = Cast<ICsStartPlay>(Object))
		{
			return Interface->HasStartedPlay();
		}

		if (Object->GetClass()->ImplementsInterface(UCsStartPlay::StaticClass()))
		{
			return ICsScriptStartPlay::Execute_Script_HasStartedPlay(Object);
		}

		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s %s does NOT implement the interface: ICsStartPlay."), *Context, *CsObjectLibrary::PrintObjectAndClass(Object)));
		return false;
	}

	void FLibrary::StartPlayChecked(const FString& Context, UObject* Object)
	{
		CS_IS_PENDING_KILL_CHECKED(Object)

		if (ICsStartPlay* Interface = Cast<ICsStartPlay>(Object))
		{
			Interface->StartPlay();
			return;
		}

		if (Object->GetClass()->ImplementsInterface(UCsStartPlay::StaticClass()))
		{
			ICsScriptStartPlay::Execute_Script_StartPlay(Object);
		}
		checkf(0, TEXT("%s %s does NOT implement the interface: ICsStartPlay."), *Context, *CsObjectLibrary::PrintObjectAndClass(Object));
	}

	void FLibrary::SafeStartPlay(const FString& Context, UObject* Object, LogLevel)
	{
		CS_IS_PENDING_KILL_EXIT(Object)

		if (ICsStartPlay* Interface = Cast<ICsStartPlay>(Object))
		{
			Interface->StartPlay();
			return;
		}

		if (Object->GetClass()->ImplementsInterface(UCsStartPlay::StaticClass()))
		{
			ICsScriptStartPlay::Execute_Script_StartPlay(Object);
		}
		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s %s does NOT implement the interface: ICsStartPlay."), *Context, *CsObjectLibrary::PrintObjectAndClass(Object)));
	}

	#undef LogLevel
}