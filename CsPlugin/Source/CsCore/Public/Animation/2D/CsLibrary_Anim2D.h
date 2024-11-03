// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "Animation/2D/CsTypes_Library_Anim2D.h"
#include "Coroutine/CsRoutineHandle.h"

struct FCsRoutine;

namespace NCsAnim
{
	namespace N2D
	{
		namespace NTexture
		{
			struct CSCORE_API FLibrary final
			{
			private:
				FLibrary();

				FLibrary(const FLibrary&) = delete;
				FLibrary(FLibrary&&) = delete;
			public:
				~FLibrary();

				FORCEINLINE static FLibrary& Get()
				{
					static FLibrary Instance;
					return Instance;
				}

			private:

				CS_DECLARE_STATIC_LOG_LEVEL

				using ParamsManagerType = NCsAnim::N2D::NTexture::NPlay::NParams::FManager;
				using ParamsResourceType = NCsAnim::N2D::NTexture::NPlay::NParams::FResource;
				using ParamsType = NCsAnim::N2D::NTexture::NPlay::NParams::FParams;

				ParamsManagerType Manager_PlayParams;

			public:
		
				FORCEINLINE ParamsResourceType* AllocatePlayParams() { return Manager_PlayParams.Allocate(); }
		
				FORCEINLINE void DeallocatePlayParams(ParamsResourceType* Resource) { Manager_PlayParams.Deallocate(Resource); }

				/**
				* Play a Texture 2D animation with the given Params.
				*
				* @param Params
				* return			Handle
				*/
				static const FCsRoutineHandle& Play(const ParamsType& Params);

				/**
				* Safely play a Material 2D animation with the given Params.
				*
				* @param Context	The calling context.
				* @param Params
				* @param Log		(optional)
				* return			Handle
				*/
				static const FCsRoutineHandle& SafePlay(const FString& Context, const ParamsType& Params, CS_FN_PARAM_DEFAULT_LOG_LEVEL);

				/**
				* Play a Texture 2D animation with the given Params.
				* NOTE: This assumes Params was allocated via AllocatePlayParams().
				*		Use Play(const ParamsType& Params) if you do NOT want to allocate
				*		the params upfront.
				*
				* @param Params
				* return			 Handle
				*/
				static const FCsRoutineHandle& Play(ParamsResourceType* Params);

				/**
				* Safely play a Texture 2D animation with the given Params.
				* NOTE: This assumes Params was allocated via AllocatePlayParams().
				*		Use Play(const ParamsType& Params) if you do NOT want to allocate
				*		the params upfront.
				*
				* @param Context	The calling context.
				* @param Params
				* @param Log		(optional)
				* return			Handle
				*/
				static const FCsRoutineHandle& SafePlay(const FString& Context, ParamsResourceType* Params, CS_FN_PARAM_DEFAULT_LOG_LEVEL);

			private:

				static char Play_Internal(FCsRoutine* R);

				static void Play_Internal_OnEnd(FCsRoutine* R);
			};
		}
	}
}

using Cs2DTextureAnimLibrary = NCsAnim::N2D::NTexture::FLibrary;

namespace NCsAnim
{
	namespace N2D
	{
		namespace NMaterial
		{
			struct CSCORE_API FLibrary final
			{
			private:
				FLibrary();

				FLibrary(const FLibrary&) = delete;
				FLibrary(FLibrary&&) = delete;
			public:
				~FLibrary();

				FORCEINLINE static FLibrary& Get()
				{
					static FLibrary Instance;
					return Instance;
				}

			private:

				CS_DECLARE_STATIC_LOG_LEVEL

				using ParamsManagerType = NCsAnim::N2D::NMaterial::NPlay::NParams::FManager;
				using ParamsResourceType = NCsAnim::N2D::NMaterial::NPlay::NParams::FResource;
				using ParamsType = NCsAnim::N2D::NMaterial::NPlay::NParams::FParams;

				ParamsManagerType Manager_PlayParams;

			public:
		
				FORCEINLINE ParamsResourceType* AllocatePlayParams() { return Manager_PlayParams.Allocate(); }
		
				FORCEINLINE void DeallocatePlayParams(ParamsResourceType* Resource) { Manager_PlayParams.Deallocate(Resource); }

				/**
				* Play a Material 2D animation with the given Params.
				*
				* @param Params
				* return			Handle
				*/
				static const FCsRoutineHandle& Play(const ParamsType& Params);

				/**
				* Safely play a Material 2D animation with the given Params.
				*
				* @param Context	The calling context.
				* @param Params
				* @param Log		(optional)
				* return			Handle
				*/
				static const FCsRoutineHandle& SafePlay(const FString& Context, const ParamsType& Params, CS_FN_PARAM_DEFAULT_LOG_LEVEL);

				/**
				* Play a Material 2D animation with the given Params.
				* NOTE: This assumes Params was allocated via AllocatePlayParams().
				*		Use Play(const ParamsType& Params) if you do NOT want to allocate
				*		the params upfront.
				* 
				* @param Params
				* return			 Handle
				*/
				static const FCsRoutineHandle& Play(ParamsResourceType* Params);

				/**
				* Safely play a Material 2D animation with the given Params.
				* NOTE: This assumes Params was allocated via AllocatePlayParams().
				*		Use Play(const ParamsType& Params) if you do NOT want to allocate
				*		the params upfront.
				*
				* @param Context	The calling context.
				* @param Params
				* @param Log		(optional)
				* return			Handle
				*/
				static const FCsRoutineHandle& SafePlay(const FString& Context, ParamsResourceType* Params, CS_FN_PARAM_DEFAULT_LOG_LEVEL);

			private:

				static char Play_Internal(FCsRoutine* R);

				static void Play_Internal_OnEnd(FCsRoutine* R);
			};
		}
	}
}

using Cs2DMaterialAnimLibrary = NCsAnim::N2D::NMaterial::FLibrary;