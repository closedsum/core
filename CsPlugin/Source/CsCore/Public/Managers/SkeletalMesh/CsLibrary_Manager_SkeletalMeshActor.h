// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.


#pragma once

class UObject;

namespace NCsSkeletalMeshActor
{
	namespace NManager
	{
		struct CSCORE_API FLibrary final
		{
		public:

			/**
			* Get the Context (Root) for UCsManager_SkeletalMeshActor from a WorldContext.
			*
			* @oaram WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* return				Context for UCsManager_SkeletalMeshActor
			*/
			static UObject* GetContextRoot(UObject* WorldContext);

			/**
			* Get the Context (Root) for UCsManager_SkeletalMeshActor from a WorldContext.
			*
			* @param Context		The calling context.
			* @oaram WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* return				Context for UCsManager_SkeletalMeshActor
			*/
			static UObject* GetContextRootChecked(const FString& Context, UObject* WorldContext);
		};
	}
}