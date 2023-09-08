// Copyright 2017-2021 Closed Sum Games, Inc. All rights reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "ConsoleCommand/CsTypes_ConsoleCommand.h"

class UWorld;

namespace NCsConsoleCommand
{
	namespace NManager
	{
		/**
		*/
		class CSCORE_API IManager
		{
		#define InfoType NCsConsoleCommand::FInfo

		public:

			virtual ~IManager(){}

			virtual const TArray<InfoType>& GetCommandInfos() const = 0;

			virtual const FString& GetCategoryName() const = 0;

			virtual bool Exec(UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Out = *GLog) = 0;

		#undef InfoType
		};
	}
}