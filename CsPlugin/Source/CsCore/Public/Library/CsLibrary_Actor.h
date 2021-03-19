// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

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
	};
}