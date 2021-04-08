// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Types
#include "Managers/FX/CsTypes_FX.h"

class UObject;

// NCsFX::NPayload::FImpl
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsFX, NPayload, FImpl)

namespace NCsFX
{
	namespace NManager
	{
		/**
		*/
		struct CSCORE_API FLibrary final
		{
		public:

		#if WITH_EDITOR
			/**
			* Get the Context (Root) for UCsManager_FX from a WorldContext.
			* 
			* @parma Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* return				Context for UCsManager_FX.
			*/
			static UObject* GetContextRootChecked(const FString& Context, UObject* WorldContext);
		#else
			FORCEINLINE static UObject* GetContextRootChecked(const FString& Context, UObject* WorldContext)
			{
				return nullptr;
			}
		#endif // #if WITH_EDITOR

		#if WITH_EDITOR
			/**
			* Safely get the Context (Root) for UCsManager_FX from a WorldContext.
			*
			* @parma Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* return				Context for UCsManager_FX.
			*/
			static UObject* GetSafeContextRoot(const FString& Context, UObject* WorldContext);
		#else
			FORCEINLINE static UObject* GetSafeContextRoot(const FString& Context, UObject* WorldContext)
			{
				return nullptr;
			}
		#endif // #if WITH_EDITOR

		#define PayloadImplType NCsFX::NPayload::FImpl

			/**
			* 
			* 
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Type
			* @param FX
			* return				Payload.
			*/
			static PayloadImplType* AllocatePayloadChecked(const FString& Context, UObject* WorldContext, const FECsFX& Type, const FCsFX& FX);

		#undef PayloadImplType
		};
	}
}