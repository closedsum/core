// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#include "Library/CsLibrary_Viewport.h"
#include "CsCore.h"

// Types
#include "Managers/Trace/CsTraceRequest.h"
// Library
#include "Library/CsLibrary_Player.h"
#include "Library/CsLibrary_Math.h"
#include "Managers/Trace/CsLibrary_Manager_Trace.h"
#include "Library/CsLibrary_Valid.h"
// Player
#include "GameFramework/PlayerController.h"
#include "Engine/LocalPlayer.h"
// World
#include "Engine/World.h"
// View
#include "Engine/GameViewportClient.h"
#include "Slate/SceneViewport.h"

namespace NCsViewport
{
	namespace NLocal
	{
		namespace NPlayer
		{
			namespace NLibrary
			{
				namespace NCached
				{
					namespace Str
					{
						CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsViewport::NLocal::NPlayer::FLibrary, CanSafeProjectWorldToScreen);
						CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsViewport::NLocal::NPlayer::FLibrary, CanSafeDeprojectScreenToWorld);
						CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsViewport::NLocal::NPlayer::FLibrary, SafeDeprojectScreenToWorld);
						CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsViewport::NLocal::NPlayer::FLibrary, GetSafeViewport);
						CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsViewport::NLocal::NPlayer::FLibrary, GetSafeSize);
						CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsViewport::NLocal::NPlayer::FLibrary, GetSafeScreenWorldIntersection);
						CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsViewport::NLocal::NPlayer::FLibrary, SafeTrace);
					}
				}
			}

			bool FLibrary::CanProjectWorldToScreenChecked(const FString& Context, const UObject* WorldContext)
			{
				typedef NCsPlayer::FLibrary PlayerLibrary;

				ULocalPlayer* LocalPlayer = PlayerLibrary::GetFirstLocalChecked(Context, WorldContext);

				checkf(LocalPlayer->ViewportClient, TEXT("%s: ViewportClient is NUll for LocalPlayer: %s."), *(LocalPlayer->GetName()));

				return true;
			}

			bool FLibrary::CanSafeProjectWorldToScreen(const FString& Context, const UObject* WorldContext, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
			{
				typedef NCsPlayer::FLibrary PlayerLibrary;

				ULocalPlayer* LocalPlayer = PlayerLibrary::GetSafeFirstLocal(Context, WorldContext, Log);

				if (!LocalPlayer)
					return false;

				if (!LocalPlayer->ViewportClient)
				{
					CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: ViewportClient is NUll for LocalPlayer: %s."), *(LocalPlayer->GetName())));
					return false;
				}
				return true;
			}

			bool FLibrary::CanSafeProjectWorldToScreen(const UObject* WorldContext)
			{
				using namespace NCsViewport::NLocal::NPlayer::NLibrary::NCached;

				const FString& Context = Str::CanSafeProjectWorldToScreen;

				return CanSafeProjectWorldToScreen(Context, WorldContext, nullptr);
			}

			bool FLibrary::CanDeprojectScreenToWorldChecked(const FString& Context, const UObject* WorldContext)
			{
				typedef NCsPlayer::FLibrary PlayerLibrary;

				ULocalPlayer* LocalPlayer = PlayerLibrary::GetFirstLocalChecked(Context, WorldContext);

				checkf(LocalPlayer->ViewportClient, TEXT("%s: ViewportClient is NUll for LocalPlayer: %s."), *(LocalPlayer->GetName()));

				return true;
			}

			bool FLibrary::CanSafeDeprojectScreenToWorld(const FString& Context, const UObject* WorldContext, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
			{
				typedef NCsPlayer::FLibrary PlayerLibrary;

				ULocalPlayer* LocalPlayer = PlayerLibrary::GetSafeFirstLocal(Context, WorldContext, Log);

				if (!LocalPlayer)
					return false;

				if (!LocalPlayer->ViewportClient)
				{
					CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: ViewportClient is NUll for LocalPlayer: %s."), *(LocalPlayer->GetName())));
					return false;
				}
				return true;
			}

			bool FLibrary::CanSafeDeprojectScreenToWorld(const UObject* WorldContext)
			{
				using namespace NCsViewport::NLocal::NPlayer::NLibrary::NCached;

				const FString& Context = Str::CanSafeDeprojectScreenToWorld;

				return CanSafeDeprojectScreenToWorld(Context, WorldContext, nullptr);
			}

			bool FLibrary::DeprojectScreenToWorldChecked(const FString& Context, const UObject* WorldContext, const FVector2D& ScreenPosition, FVector& WorldPosition, FVector& WorldDirection)
			{
				check(CanDeprojectScreenToWorldChecked(Context, WorldContext));

				typedef NCsPlayer::FLibrary PlayerLibrary;

				ULocalPlayer* LocalPlayer = PlayerLibrary::GetFirstLocalChecked(Context, WorldContext);

				UGameViewportClient* GVC = LocalPlayer->ViewportClient;

				checkf(GVC, TEXT("%s: ViewportClient is NUll for LocalPlayer: %s."), *(LocalPlayer->GetName()));

				FViewport* Viewport = GVC->Viewport;

				checkf(Viewport, TEXT("%s: Failed to get Viewport from ViewportClient: %s for LocalPlayer: %s."), *Context, *(GVC->GetName()), *(LocalPlayer->GetName()));

				// Get the projection data
				FSceneViewProjectionData ProjectionData;
				if (LocalPlayer->GetProjectionData(Viewport, eSSP_FULL, /*out*/ ProjectionData))
				{
					FMatrix const InvViewProjMatrix = ProjectionData.ComputeViewProjectionMatrix().InverseFast();
					FSceneView::DeprojectScreenToWorld(ScreenPosition, ProjectionData.GetConstrainedViewRect(), InvViewProjMatrix, /*out*/ WorldPosition, /*out*/ WorldDirection);
					return true;
				}

				// Something went wrong, zero things and return false
				WorldPosition  = FVector::ZeroVector;
				WorldDirection = FVector::ZeroVector;
				return false;
			}

			bool FLibrary::SafeDeprojectScreenToWorld(const FString& Context, const UObject* WorldContext, const FVector2D& ScreenPosition, FVector& WorldPosition, FVector& WorldDirection, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
			{
				WorldPosition = FVector::ZeroVector;
				WorldDirection = FVector::ZeroVector;

				if (!CanSafeDeprojectScreenToWorld(Context, WorldContext, Log))
					return false;

				typedef NCsPlayer::FLibrary PlayerLibrary;

				ULocalPlayer* LocalPlayer = PlayerLibrary::GetSafeFirstLocal(Context, WorldContext, Log);

				if (!LocalPlayer)
					return false;

				UGameViewportClient* GVC = LocalPlayer->ViewportClient;

				if (!GVC)
				{
					CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: ViewportClient is NUll for LocalPlayer: %s."), *(LocalPlayer->GetName())));
					return false;
				}

				FViewport* Viewport = GVC->Viewport;

				if (!Viewport)
				{
					CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to get Viewport from ViewportClient: %s for LocalPlayer: %s."), *Context, *(GVC->GetName()), *(LocalPlayer->GetName())));
					return false;
				}

				// Get the projection data
				FSceneViewProjectionData ProjectionData;
				if (LocalPlayer->GetProjectionData(Viewport, eSSP_FULL, /*out*/ ProjectionData))
				{
					FMatrix const InvViewProjMatrix = ProjectionData.ComputeViewProjectionMatrix().InverseFast();
					FSceneView::DeprojectScreenToWorld(ScreenPosition, ProjectionData.GetConstrainedViewRect(), InvViewProjMatrix, /*out*/ WorldPosition, /*out*/ WorldDirection);
					return true;
				}

				// Something went wrong, zero things and return false
				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Unexpected error."), *Context));
				return false;
			}

			bool FLibrary::SafeDeprojectScreenToWorld(const UObject* WorldContext, const FVector2D& ScreenPosition, FVector& WorldPosition, FVector& WorldDirection)
			{
				using namespace NCsViewport::NLocal::NPlayer::NLibrary::NCached;

				const FString& Context = Str::CanSafeDeprojectScreenToWorld;

				return SafeDeprojectScreenToWorld(Context, WorldContext, ScreenPosition, WorldPosition, WorldDirection);
			}

			FSceneViewport* FLibrary::GetViewportChecked(const FString& Context, const UObject* WorldContext)
			{
				typedef NCsPlayer::FLibrary PlayerLibrary;

				ULocalPlayer* LocalPlayer = PlayerLibrary::GetFirstLocalChecked(Context, WorldContext);
				UGameViewportClient* GVC  = LocalPlayer->ViewportClient;

				checkf(GVC, TEXT("%s: ViewportClient is NUll for LocalPlayer: %s."), *(LocalPlayer->GetName()));

				FSceneViewport* SV = GVC->GetGameViewport();

				checkf(SV, TEXT("%s: Failed get Viewport from LocalPlayer: %s with ViewportClient: %s."), *Context, *(LocalPlayer->GetName()), *(GVC->GetName()));
		
				return SV;
			}

			FSceneViewport* FLibrary::GetSafeViewport(const FString& Context, const UObject* WorldContext, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
			{
				typedef NCsPlayer::FLibrary PlayerLibrary;

				ULocalPlayer* LocalPlayer = PlayerLibrary::GetSafeFirstLocal(Context, WorldContext, Log);

				if (!LocalPlayer)
					return nullptr;

				UGameViewportClient* GVC = LocalPlayer->ViewportClient;

				if (!GVC)
				{
					CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: ViewportClient is NUll for LocalPlayer: %s."), *(LocalPlayer->GetName())));
					return nullptr;
				}

				FSceneViewport* SV = GVC->GetGameViewport();

				if (!SV)
				{
					CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed get Viewport from LocalPlayer: %s with ViewportClient: %s."), *Context, *(LocalPlayer->GetName()), *(GVC->GetName())));
				}
				return SV;
			}

			FSceneViewport* FLibrary::GetSafeViewport(const UObject* WorldContext)
			{
				using namespace NCsViewport::NLocal::NPlayer::NLibrary::NCached;

				const FString& Context = Str::GetSafeViewport;

				return GetSafeViewport(Context, WorldContext, nullptr);
			}

			FIntPoint FLibrary::GetSizeChecked(const FString& Context, const UObject* WorldContext)
			{
				FSceneViewport* SV = GetViewportChecked(Context, WorldContext);

				return SV->GetSizeXY();
			}

			FIntPoint FLibrary::GetSafeSize(const FString& Context, const UObject* WorldContext, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
			{
				FSceneViewport* SV = GetSafeViewport(Context, WorldContext, Log);

				if (!SV)
					return FIntPoint::NoneValue;

				return SV->GetSizeXY();
			}

			FIntPoint FLibrary::GetSafeSize(const UObject* WorldContext)
			{
				using namespace NCsViewport::NLocal::NPlayer::NLibrary::NCached;

				const FString& Context = Str::GetSafeSize;

				return GetSafeSize(Context, WorldContext, nullptr);
			}

			bool FLibrary::GetScreenWorldIntersectionChecked(const FString& Context, const UObject* WorldContext, const FVector2D& ScreenPosition, const FPlane& Plane, FVector& OutIntersection)
			{
				FVector WorldPosition;
				FVector WorldDirection;
				bool Success = DeprojectScreenToWorldChecked(Context, WorldContext, ScreenPosition, WorldPosition, WorldDirection);

				checkf(Success, TEXT("%s: Failed to deproject ScreenPosition: %s."), *Context, *(ScreenPosition.ToString()));

				typedef NCsMath::FLibrary MathLibrary;

				FCsRay Ray(WorldPosition, WorldDirection, true);
				float T;

				return MathLibrary::RayPlaneIntersectionChecked(Context, Ray, Plane, T, OutIntersection);
			}

			bool FLibrary::GetSafeScreenWorldIntersection(const FString& Context, const UObject* WorldContext, const FVector2D& ScreenPosition, const FPlane& Plane, FVector& OutIntersection, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
			{
				FVector WorldPosition = FVector::ZeroVector;
				FVector WorldDirection = FVector::ZeroVector;
				bool Success = SafeDeprojectScreenToWorld(Context, WorldContext, ScreenPosition, WorldPosition, WorldDirection, Log);

				if (!Success)
				{
					CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to deproject ScreenPosition: %s."), *Context, *(ScreenPosition.ToString())));
					return false;
				}

				typedef NCsMath::FLibrary MathLibrary;

				FCsRay Ray(WorldPosition, WorldDirection, true);
				float T;

				return MathLibrary::SafeRayPlaneIntersection(Context, Ray, Plane, T, OutIntersection, Log);
			}

			bool FLibrary::GetSafeScreenWorldIntersection(const UObject* WorldContext, const FVector2D& ScreenPosition, const FPlane& Plane, FVector& OutIntersection)
			{
				using namespace NCsViewport::NLocal::NPlayer::NLibrary::NCached;

				const FString& Context = Str::GetSafeScreenWorldIntersection;

				return GetSafeScreenWorldIntersection(Context, WorldContext, ScreenPosition, Plane, OutIntersection, nullptr);
			}

		// Trace
		#pragma region

		#define ResponseType NCsTrace::NResponse::FResponse
		#define RequestType NCsTrace::NRequest::FRequest

		ResponseType* FLibrary::TraceChecked(const FString& Context, const UObject* WorldContext, const FVector2D& ScreenPosition, RequestType* Request, const float& Distance /*=1000000.0f*/)
		{
			CS_IS_FLOAT_GREATER_THAN_OR_EQUAL_CHECKED(ScreenPosition.X, 0.0f)

			CS_IS_FLOAT_GREATER_THAN_OR_EQUAL_CHECKED(ScreenPosition.Y, 0.0f)

			FVector WorldPosition;
			FVector WorldDirection;

			bool Success = DeprojectScreenToWorldChecked(Context, WorldContext, ScreenPosition, WorldPosition, WorldDirection);

			check(Success);
			
			CS_IS_FLOAT_GREATER_THAN_CHECKED(Distance, 0.0f)

			Request->Start = WorldPosition;
			Request->End   = WorldPosition + Distance * WorldDirection;

			typedef NCsTrace::NManager::FLibrary TraceManagerLibrary;

			return TraceManagerLibrary::TraceChecked(Context, WorldContext, Request);
		}

		ResponseType* FLibrary::SafeTrace(const FString& Context, const UObject* WorldContext, const FVector2D& ScreenPosition, RequestType* Request, const float& Distance /*=1000000.0f*/, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			CS_IS_FLOAT_GREATER_THAN_OR_EQUAL_CHECKED(ScreenPosition.X, 0.0f)

			CS_IS_FLOAT_GREATER_THAN_OR_EQUAL_CHECKED(ScreenPosition.Y, 0.0f)

			FVector WorldPosition;
			FVector WorldDirection;

			if (!SafeDeprojectScreenToWorld(Context, WorldContext, ScreenPosition, WorldPosition, WorldDirection, Log))
				return nullptr;

			CS_IS_FLOAT_GREATER_THAN_RET_NULL(Distance, 0.0f)

			Request->Start = WorldPosition;
			Request->End   = WorldPosition + Distance * WorldDirection;

			typedef NCsTrace::NManager::FLibrary TraceManagerLibrary;

			return TraceManagerLibrary::SafeTrace(Context, WorldContext, Request, Log);
		}

		ResponseType* FLibrary::SafeTrace(const UObject* WorldContext, const FVector2D& ScreenPosition, RequestType* Request, const float& Distance /*=1000000.0f*/)
		{
			using namespace NCsViewport::NLocal::NPlayer::NLibrary::NCached;

			const FString& Context = Str::SafeTrace;

			return SafeTrace(Context, WorldContext, ScreenPosition, Request, Distance, nullptr);
		}

		#undef ResponseType
		#undef RequestType

		#pragma endregion Trace
		}
	}
}