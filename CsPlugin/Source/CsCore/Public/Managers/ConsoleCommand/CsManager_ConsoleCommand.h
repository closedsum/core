// Copyright 2019 Respawn Entertainment, Inc. All rights reserved.
#pragma once

class UWorld;

namespace NCsConsoleCommand
{
	namespace NManager
	{
		/**
		*/
		class CSCORE_API IManager
		{
		public:

			virtual ~IManager(){}

			virtual bool Exec(UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Out = *GLog) = 0;
		};
	}
}