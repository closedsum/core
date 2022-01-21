// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Runnable/CsTypes_Runnable.h"
#pragma once

class UObject;

namespace NCsRunnable
{
	namespace NTask
	{
		DECLARE_DELEGATE(FOnComplete)

		/**
		*/
		struct CSCORE_API ITask
		{
		public:

			virtual ~ITask(){}

		public:

			/**
			*/
			virtual void Execute() = 0;

			/**
			*/
			virtual bool IsRunning() const = 0;

			/**
			*/
			virtual bool IsComplete() const = 0;

			/**
			*/
			virtual TArray<FOnComplete>& GetOnComplete_Events() = 0;

			/**
			*/
			virtual TArray<FOnComplete>& GetOnComplete_AsyncEvents() = 0;

			virtual void Reset() = 0;
		};
	}
}