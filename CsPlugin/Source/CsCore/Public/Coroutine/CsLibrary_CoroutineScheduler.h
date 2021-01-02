// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.


#pragma once

class UObject;

namespace NCsCoroutine
{
	namespace NScheduler
	{
		struct CSCORE_API FLibrary final
		{
		public:

			/**
			* Get the Context (Root) for UCsCoroutineScheduler from an Actor.
			*
			* @oaram WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* return				Context for CoroutineScheduler
			*/
			static UObject* GetContextRoot(UObject* WorldContext);
		};
	}
}