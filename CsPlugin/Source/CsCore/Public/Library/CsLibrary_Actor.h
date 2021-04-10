// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Log
#include "Utility/CsLog.h"

class AActor;
class UObject;

namespace NCsActor
{
	struct CSCORE_API FLibrary final
	{
	public:

		/**
		* Get an Actor with the given Tag (checks AActor->Tags)
		* 
		* @param Context		The calling context.
		* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
		* @param Tag
		* return
		*/
		static AActor* GetActorWithTagChecked(const FString& Context, UObject* WorldContext, const FName& Tag);

		/**
		* Get an Actor (casted to type T) with the given Tag (checks AActor->Tags)
		*
		* @param Context		The calling context.
		* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
		* @param Tag
		* return
		*/
		template<typename T>
		FORCEINLINE static T* GetActorWithTagChecked(const FString& Context, UObject* WorldContext, const FName& Tag)
		{
			T* A = Cast<T>(GetActorWithTagChecked(Context, WorldContext, Tag));

			checkf(A, TEXT("%s: Failed to cast Actor to type: %s."), *Context, *(T::StaticClass()->GetName()));

			return A;
		}

		/**
		* Get an Actor with the given Name.
		* 
		* @param Context		The calling context.
		* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
		* @param Name
		* @param Log
		* return
		*/
		static AActor* GetSafeActorByName(const FString& Context, UObject* WorldContext, const FName& Name, void(*Log)(const FString&) = &FCsLog::Warning);

		/**
		* Get an Actor with the given Name.
		*
		* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
		* @param Name
		* return
		*/
		static AActor* GetSafeActorByName(UObject* WorldContext, const FName& Name);

		/**
		* Get an Actor with the given Label.
		* NOTE: - More than 1 Actor can have the SAME Label in Editor. In this case, the FIRST
		*		  Actor found in the search will be returned.
		*		- Only valid in Editor.
		*
		* @param Context		The calling context.
		* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
		* @param Name
		* @param Log
		* return
		*/
		static AActor* GetSafeActorByLabel(const FString& Context, UObject* WorldContext, const FString& Label, void(*Log)(const FString&) = &FCsLog::Warning);

		/**
		* Get an Actor with the given Label.
		* NOTE: - More than 1 Actor can have the SAME Label in Editor. In this case, the FIRST
		*		  Actor found in the search will be returned.
		*		- Only valid in Editor.
		*
		* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
		* @param Name
		* return
		*/
		static AActor* GetSafeActorByLabel(UObject* WorldContext, const FString& Label);
	};
}