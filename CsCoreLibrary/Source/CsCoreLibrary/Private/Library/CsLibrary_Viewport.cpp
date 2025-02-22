// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Library/CsLibrary_Viewport.h"

// Library
#include "Game/CsLibrary_GameInstance.h"
#include "Player/CsLibrary_Player.h"
#include "Library/CsLibrary_Math.h"
#include "Library/CsLibrary_Valid.h"
// Player
#include "GameFramework/PlayerController.h"
#include "Engine/LocalPlayer.h"
// Game
#include "Engine/GameInstance.h"
// World
#include "Engine/World.h"
// View
#include "Engine/GameViewportClient.h"
#include "Slate/SceneViewport.h"
#include "SceneView.h"

CS_START_CACHED_FUNCTION_NAME_NESTED_3(NCsViewport, NLocal, NPlayer, Library)
	CS_DEFINE_CACHED_FUNCTION_NAME(NCsViewport::NLocal::NPlayer::FLibrary, CanSafeProjectWorldToScreen)
	CS_DEFINE_CACHED_FUNCTION_NAME(NCsViewport::NLocal::NPlayer::FLibrary, CanSafeDeprojectScreenToWorld)
	CS_DEFINE_CACHED_FUNCTION_NAME(NCsViewport::NLocal::NPlayer::FLibrary, SafeDeprojectScreenToWorld)
	CS_DEFINE_CACHED_FUNCTION_NAME(NCsViewport::NLocal::NPlayer::FLibrary, GetSafeViewport)
	CS_DEFINE_CACHED_FUNCTION_NAME(NCsViewport::NLocal::NPlayer::FLibrary, GetSafeSize)
	CS_DEFINE_CACHED_FUNCTION_NAME(NCsViewport::NLocal::NPlayer::FLibrary, GetSafeScreenWorldIntersection)
	CS_DEFINE_CACHED_FUNCTION_NAME(NCsViewport::NLocal::NPlayer::FLibrary, SafeTrace)
CS_END_CACHED_FUNCTION_NAME_NESTED_3

namespace NCsViewport
{
	namespace NLocal
	{
		namespace NPlayer
		{
			using LogClassType = NCsCore::NLibrary::FLog;

			CS_DEFINE_STATIC_LOG_LEVEL(FLibrary, LogClassType::Warning);
			
			bool FLibrary::CanProjectWorldToScreenChecked(const FString& Context, const UObject* WorldContext)
			{
				ULocalPlayer* LocalPlayer = CsPlayerLibrary::GetFirstLocalChecked(Context, WorldContext);

				checkf(LocalPlayer->ViewportClient, TEXT("%s: ViewportClient is NUll for LocalPlayer: %s."), *Context, *(LocalPlayer->GetName()));
				return true;
			}

			bool FLibrary::CanSafeProjectWorldToScreen(const FString& Context, const UObject* WorldContext, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT)
			{
				ULocalPlayer* LocalPlayer = CsPlayerLibrary::GetSafeFirstLocal(Context, WorldContext, Log);

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
				CS_SET_CONTEXT_AS_FUNCTION_NAME(CanSafeProjectWorldToScreen);

				return CanSafeProjectWorldToScreen(Context, WorldContext, nullptr);
			}

			bool FLibrary::ProjectWorldToScreenChecked(const FString& Context, const UObject* WorldContext, const FVector& WorldPosition, FVector2D& OutScreenPosition, bool bPlayerViewportRelative /*=false*/)
			{
				check(CanProjectWorldToScreenChecked(Context, WorldContext));

				ULocalPlayer* LocalPlayer = CsPlayerLibrary::GetFirstLocalChecked(Context, WorldContext);
				UGameViewportClient* GVC  = LocalPlayer->ViewportClient;

				checkf(GVC, TEXT("%s: ViewportClient is NUll for LocalPlayer: %s."), *Context, *(LocalPlayer->GetName()));

				FViewport* Viewport = GVC->Viewport;

				checkf(Viewport, TEXT("%s: Failed to get Viewport from ViewportClient: %s for LocalPlayer: %s."), *Context, *(GVC->GetName()), *(LocalPlayer->GetName()));

				// Get the projection data
				FSceneViewProjectionData ProjectionData;
				if (LocalPlayer->GetProjectionData(Viewport, /*out*/ ProjectionData))
				{
					FMatrix const ViewProjectionMatrix = ProjectionData.ComputeViewProjectionMatrix();
					FVector2D Position;
					bool bResult					   = FSceneView::ProjectWorldToScreen(WorldPosition, ProjectionData.GetConstrainedViewRect(), ViewProjectionMatrix, Position);

					OutScreenPosition = Position;

					if (bPlayerViewportRelative)
					{
						OutScreenPosition -= FVector2D(ProjectionData.GetConstrainedViewRect().Min);
					}

					//bResult = bResult && PlayerController->PostProcessWorldToScreen(WorldPosition, ScreenPosition, bPlayerViewportRelative);
					return bResult;
				}
				OutScreenPosition = FVector2D::ZeroVector;
				return false;
			}

			bool FLibrary::ProjectWorldToScreenChecked(const FString& Context, const UObject* WorldContext, const FVector3f& WorldPosition, FVector2f& OutScreenPosition, bool bPlayerViewportRelative /*=false*/)
			{
				check(CanProjectWorldToScreenChecked(Context, WorldContext));

				ULocalPlayer* LocalPlayer = CsPlayerLibrary::GetFirstLocalChecked(Context, WorldContext);
				UGameViewportClient* GVC  = LocalPlayer->ViewportClient;

				checkf(GVC, TEXT("%s: ViewportClient is NUll for LocalPlayer: %s."), *Context, *(LocalPlayer->GetName()));

				FViewport* Viewport = GVC->Viewport;

				checkf(Viewport, TEXT("%s: Failed to get Viewport from ViewportClient: %s for LocalPlayer: %s."), *Context, *(GVC->GetName()), *(LocalPlayer->GetName()));

				// Get the projection data
				FSceneViewProjectionData ProjectionData;
				if (LocalPlayer->GetProjectionData(Viewport, /*out*/ ProjectionData))
				{
					FMatrix const ViewProjectionMatrix = ProjectionData.ComputeViewProjectionMatrix();
					FVector2D Position;
					bool bResult					   = FSceneView::ProjectWorldToScreen(CsMathLibrary::Convert(WorldPosition), ProjectionData.GetConstrainedViewRect(), ViewProjectionMatrix, Position);

					OutScreenPosition = CsMathLibrary::Convert(Position);

					if (bPlayerViewportRelative)
					{
						OutScreenPosition -= FVector2f(ProjectionData.GetConstrainedViewRect().Min);
					}

					//bResult = bResult && PlayerController->PostProcessWorldToScreen(WorldPosition, ScreenPosition, bPlayerViewportRelative);
					return bResult;
				}
				OutScreenPosition = FVector2f::ZeroVector;
				return false;
			}

			bool FLibrary::ProjectWorldToScreenChecked(const FString& Context, const UObject* WorldContext, const TArray<FVector>& WorldPositions, TArray<FVector2D>& OutScreenPositions)
			{
				check(CanProjectWorldToScreenChecked(Context, WorldContext));

				ULocalPlayer* LocalPlayer = CsPlayerLibrary::GetFirstLocalChecked(Context, WorldContext);
				UGameViewportClient* GVC  = LocalPlayer->ViewportClient;

				checkf(GVC, TEXT("%s: ViewportClient is NUll for LocalPlayer: %s."), *Context, *(LocalPlayer->GetName()));

				FViewport* Viewport = GVC->Viewport;

				checkf(Viewport, TEXT("%s: Failed to get Viewport from ViewportClient: %s for LocalPlayer: %s."), *Context, *(GVC->GetName()), *(LocalPlayer->GetName()));

				if (OutScreenPositions.Num() != WorldPositions.Num())
				{
					OutScreenPositions.Reset(FMath::Max(WorldPositions.Num(), OutScreenPositions.Num()));
					OutScreenPositions.AddDefaulted(WorldPositions.Num());
				}

				bool Result = false;

				// Get the projection data
				FSceneViewProjectionData ProjectionData;
				if (LocalPlayer->GetProjectionData(Viewport, /*out*/ ProjectionData))
				{
					FMatrix const ViewProjectionMatrix = ProjectionData.ComputeViewProjectionMatrix();

					const int32 Count = WorldPositions.Num();

					for (int32 I = 0; I < Count; ++I)
					{
						const FVector& WorldPosition = WorldPositions[I];
						FVector2D& ScreenPosition	 = OutScreenPositions[I];
						FVector2D Position;
						Result &= FSceneView::ProjectWorldToScreen(WorldPosition, ProjectionData.GetConstrainedViewRect(), ViewProjectionMatrix, Position);

						ScreenPosition = Position;
					}
				}
				return Result;
			}

			bool FLibrary::ProjectWorldToScreenChecked(const FString& Context, const UObject* WorldContext, const TArray<FVector3f>& WorldPositions, TArray<FVector2f>& OutScreenPositions)
			{
				check(CanProjectWorldToScreenChecked(Context, WorldContext));

				ULocalPlayer* LocalPlayer = CsPlayerLibrary::GetFirstLocalChecked(Context, WorldContext);
				UGameViewportClient* GVC  = LocalPlayer->ViewportClient;

				checkf(GVC, TEXT("%s: ViewportClient is NUll for LocalPlayer: %s."), *Context, *(LocalPlayer->GetName()));

				FViewport* Viewport = GVC->Viewport;

				checkf(Viewport, TEXT("%s: Failed to get Viewport from ViewportClient: %s for LocalPlayer: %s."), *Context, *(GVC->GetName()), *(LocalPlayer->GetName()));

				if (OutScreenPositions.Num() != WorldPositions.Num())
				{
					OutScreenPositions.Reset(FMath::Max(WorldPositions.Num(), OutScreenPositions.Num()));
					OutScreenPositions.AddDefaulted(WorldPositions.Num());
				}

				bool Result = false;

				// Get the projection data
				FSceneViewProjectionData ProjectionData;
				if (LocalPlayer->GetProjectionData(Viewport, /*out*/ ProjectionData))
				{
					FMatrix const ViewProjectionMatrix = ProjectionData.ComputeViewProjectionMatrix();

					const int32 Count = WorldPositions.Num();

					for (int32 I = 0; I < Count; ++I)
					{
						const FVector3f& WorldPosition = WorldPositions[I];
						FVector2f& ScreenPosition	 = OutScreenPositions[I];
						FVector2d Position;
						Result &= FSceneView::ProjectWorldToScreen(CsMathLibrary::Convert(WorldPosition), ProjectionData.GetConstrainedViewRect(), ViewProjectionMatrix, Position);

						ScreenPosition = CsMathLibrary::Convert(Position);
					}
				}
				return Result;
			}

			bool FLibrary::ProjectWorldToScreenChecked(const FString& Context, const UObject* WorldContext, const TArray<FVector>& WorldPositions, const TArray<int32>& Indices, const int32& Count, TArray<FVector2D>& OutScreenPositions)
			{
				check(CanProjectWorldToScreenChecked(Context, WorldContext));

				ULocalPlayer* LocalPlayer = CsPlayerLibrary::GetFirstLocalChecked(Context, WorldContext);
				UGameViewportClient* GVC  = LocalPlayer->ViewportClient;

				checkf(GVC, TEXT("%s: ViewportClient is NUll for LocalPlayer: %s."), *Context, *(LocalPlayer->GetName()));

				FViewport* Viewport = GVC->Viewport;

				checkf(Viewport, TEXT("%s: Failed to get Viewport from ViewportClient: %s for LocalPlayer: %s."), *Context, *(GVC->GetName()), *(LocalPlayer->GetName()));
				checkf(WorldPositions.Num() == Indices.Num(), TEXT("%s: Mismatch between the WorldPositions.Num() != Indices.Num() (%d != %d)."), *Context, WorldPositions.Num(), Indices.Num());
				checkf(WorldPositions.Num() == OutScreenPositions.Num(), TEXT("%s: Mismatch between the WorldPositions.Num() != OutScreenPositions.Num() (%d != %d)."), *Context, WorldPositions.Num(), OutScreenPositions.Num());
				checkf(Indices.Num() >= Count, TEXT("%s: Count > Indices.Num() (%d > %d)."), *Context, Count, Indices.Num());

				bool Result = false;

				// Get the projection data
				FSceneViewProjectionData ProjectionData;
				if (LocalPlayer->GetProjectionData(Viewport, /*out*/ ProjectionData))
				{
					FMatrix const ViewProjectionMatrix = ProjectionData.ComputeViewProjectionMatrix();

					for (int32 I = 0; I < Count; ++I)
					{
						const int32& Index = Indices[I];

						const FVector& WorldPosition = WorldPositions[Index];
						FVector2D& ScreenPosition	 = OutScreenPositions[Index];
						FVector2D Position;

						Result &= FSceneView::ProjectWorldToScreen(WorldPosition, ProjectionData.GetConstrainedViewRect(), ViewProjectionMatrix, Position);

						ScreenPosition = Position;
					}
				}
				return Result;
			}

			bool FLibrary::ProjectWorldToScreenChecked(const FString& Context, const UObject* WorldContext, const TArray<FVector3f>& WorldPositions, const TArray<int32>& Indices, const int32& Count, TArray<FVector2f>& OutScreenPositions)
			{
				check(CanProjectWorldToScreenChecked(Context, WorldContext));

				ULocalPlayer* LocalPlayer = CsPlayerLibrary::GetFirstLocalChecked(Context, WorldContext);
				UGameViewportClient* GVC  = LocalPlayer->ViewportClient;

				checkf(GVC, TEXT("%s: ViewportClient is NUll for LocalPlayer: %s."), *Context, *(LocalPlayer->GetName()));

				FViewport* Viewport = GVC->Viewport;

				checkf(Viewport, TEXT("%s: Failed to get Viewport from ViewportClient: %s for LocalPlayer: %s."), *Context, *(GVC->GetName()), *(LocalPlayer->GetName()));
				checkf(WorldPositions.Num() == Indices.Num(), TEXT("%s: Mismatch between the WorldPositions.Num() != Indices.Num() (%d != %d)."), *Context, WorldPositions.Num(), Indices.Num());
				checkf(WorldPositions.Num() == OutScreenPositions.Num(), TEXT("%s: Mismatch between the WorldPositions.Num() != OutScreenPositions.Num() (%d != %d)."), *Context, WorldPositions.Num(), OutScreenPositions.Num());
				checkf(Indices.Num() >= Count, TEXT("%s: Count > Indices.Num() (%d > %d)."), *Context, Count, Indices.Num());

				bool Result = false;

				// Get the projection data
				FSceneViewProjectionData ProjectionData;
				if (LocalPlayer->GetProjectionData(Viewport, /*out*/ ProjectionData))
				{
					FMatrix44d const ViewProjectionMatrix = ProjectionData.ComputeViewProjectionMatrix();

					for (int32 I = 0; I < Count; ++I)
					{
						const int32& Index = Indices[I];

						const FVector3f& WorldPosition = WorldPositions[Index];
						FVector2f& ScreenPosition	 = OutScreenPositions[Index];
						FVector2d Position;

						Result &= FSceneView::ProjectWorldToScreen(CsMathLibrary::Convert(WorldPosition), ProjectionData.GetConstrainedViewRect(), ViewProjectionMatrix, Position);

						ScreenPosition = CsMathLibrary::Convert(Position);
					}
				}
				return Result;
			}

			bool FLibrary::CanDeprojectScreenToWorldChecked(const FString& Context, const UObject* WorldContext)
			{
				ULocalPlayer* LocalPlayer = CsPlayerLibrary::GetFirstLocalChecked(Context, WorldContext);

				checkf(LocalPlayer->ViewportClient, TEXT("%s: ViewportClient is NUll for LocalPlayer: %s."), *Context, *(LocalPlayer->GetName()));
				return true;
			}

			bool FLibrary::CanSafeDeprojectScreenToWorld(const FString& Context, const UObject* WorldContext, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT)
			{
				ULocalPlayer* LocalPlayer = CsPlayerLibrary::GetSafeFirstLocal(Context, WorldContext, Log);

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
				CS_SET_CONTEXT_AS_FUNCTION_NAME(CanSafeDeprojectScreenToWorld);

				return CanSafeDeprojectScreenToWorld(Context, WorldContext, nullptr);
			}

			bool FLibrary::DeprojectScreenToWorldChecked(const FString& Context, const UObject* WorldContext, const FVector2D& ScreenPosition, FVector& OutWorldPosition, FVector& OutWorldDirection)
			{
				check(CanDeprojectScreenToWorldChecked(Context, WorldContext));

				ULocalPlayer* LocalPlayer = CsPlayerLibrary::GetFirstLocalChecked(Context, WorldContext);
				UGameViewportClient* GVC  = LocalPlayer->ViewportClient;

				checkf(GVC, TEXT("%s: ViewportClient is NUll for LocalPlayer: %s."), *Context, *(LocalPlayer->GetName()));

				FViewport* Viewport = GVC->Viewport;

				checkf(Viewport, TEXT("%s: Failed to get Viewport from ViewportClient: %s for LocalPlayer: %s."), *Context, *(GVC->GetName()), *(LocalPlayer->GetName()));

				// Get the projection data
				FSceneViewProjectionData ProjectionData;
				if (LocalPlayer->GetProjectionData(Viewport, /*out*/ ProjectionData))
				{
					FMatrix const InvViewProjMatrix = ProjectionData.ComputeViewProjectionMatrix().InverseFast();
					FVector Position;
					FVector Direction;
					FSceneView::DeprojectScreenToWorld(ScreenPosition, ProjectionData.GetConstrainedViewRect(), InvViewProjMatrix, /*out*/ Position, /*out*/ Direction);

					OutWorldPosition  = Position;
					OutWorldDirection = Direction;
					return true;
				}

				// Something went wrong, zero things and return false
				OutWorldPosition  = FVector::ZeroVector;
				OutWorldDirection = FVector::ZeroVector;
				return false;
			}

			bool FLibrary::DeprojectScreenToWorldChecked(const FString& Context, const UObject* WorldContext, const FVector2f& ScreenPosition, FVector3f& OutWorldPosition, FVector3f& OutWorldDirection)
			{
				check(CanDeprojectScreenToWorldChecked(Context, WorldContext));

				ULocalPlayer* LocalPlayer = CsPlayerLibrary::GetFirstLocalChecked(Context, WorldContext);
				UGameViewportClient* GVC  = LocalPlayer->ViewportClient;

				checkf(GVC, TEXT("%s: ViewportClient is NUll for LocalPlayer: %s."), *Context, *(LocalPlayer->GetName()));

				FViewport* Viewport = GVC->Viewport;

				checkf(Viewport, TEXT("%s: Failed to get Viewport from ViewportClient: %s for LocalPlayer: %s."), *Context, *(GVC->GetName()), *(LocalPlayer->GetName()));

				// Get the projection data
				FSceneViewProjectionData ProjectionData;
				if (LocalPlayer->GetProjectionData(Viewport, /*out*/ ProjectionData))
				{
					FMatrix const InvViewProjMatrix = ProjectionData.ComputeViewProjectionMatrix().InverseFast();
					FVector3d Position;
					FVector3d Direction;
					FSceneView::DeprojectScreenToWorld(CsMathLibrary::Convert(ScreenPosition), ProjectionData.GetConstrainedViewRect(), InvViewProjMatrix, /*out*/ Position, /*out*/ Direction);

					OutWorldPosition = CsMathLibrary::Convert(Position);
					OutWorldDirection = CsMathLibrary::Convert(Direction);
					return true;
				}

				// Something went wrong, zero things and return false
				OutWorldPosition = FVector3f::ZeroVector;
				OutWorldDirection = FVector3f::ZeroVector;
				return false;
			}

			bool FLibrary::SafeDeprojectScreenToWorld(const FString& Context, const UObject* WorldContext, const FVector2D& ScreenPosition, FVector& OutWorldPosition, FVector& OutWorldDirection, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT)
			{
				OutWorldPosition  = FVector::ZeroVector;
				OutWorldDirection = FVector::ZeroVector;

				if (!CanSafeDeprojectScreenToWorld(Context, WorldContext, Log))
					return false;

				ULocalPlayer* LocalPlayer = CsPlayerLibrary::GetSafeFirstLocal(Context, WorldContext, Log);

				if (!LocalPlayer)
					return false;

				UGameViewportClient* GVC = LocalPlayer->ViewportClient;

				if (!GVC)
				{
					CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: ViewportClient is NUll for LocalPlayer: %s."), *Context, *(LocalPlayer->GetName())));
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
				if (LocalPlayer->GetProjectionData(Viewport, /*out*/ ProjectionData))
				{
					FMatrix const InvViewProjMatrix = ProjectionData.ComputeViewProjectionMatrix().InverseFast();
					FVector Position;
					FVector Direction;
					FSceneView::DeprojectScreenToWorld(ScreenPosition, ProjectionData.GetConstrainedViewRect(), InvViewProjMatrix, /*out*/ Position, /*out*/ Direction);

					OutWorldPosition  = Position;
					OutWorldDirection = Direction;
					return true;
				}

				// Something went wrong, zero things and return false
				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Unexpected error."), *Context));
				return false;
			}

			bool FLibrary::SafeDeprojectScreenToWorld(const FString& Context, const UObject* WorldContext, const FVector2f& ScreenPosition, FVector3f& OutWorldPosition, FVector3f& OutWorldDirection, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT)
			{
				OutWorldPosition = FVector3f::ZeroVector;
				OutWorldDirection = FVector3f::ZeroVector;

				if (!CanSafeDeprojectScreenToWorld(Context, WorldContext, Log))
					return false;

				ULocalPlayer* LocalPlayer = CsPlayerLibrary::GetSafeFirstLocal(Context, WorldContext, Log);

				if (!LocalPlayer)
					return false;

				UGameViewportClient* GVC = LocalPlayer->ViewportClient;

				if (!GVC)
				{
					CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: ViewportClient is NUll for LocalPlayer: %s."), *Context, *(LocalPlayer->GetName())));
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
				if (LocalPlayer->GetProjectionData(Viewport, /*out*/ ProjectionData))
				{
					FMatrix const InvViewProjMatrix = ProjectionData.ComputeViewProjectionMatrix().InverseFast();
					FVector3d Position;
					FVector3d Direction;
					FSceneView::DeprojectScreenToWorld(CsMathLibrary::Convert(ScreenPosition), ProjectionData.GetConstrainedViewRect(), InvViewProjMatrix, /*out*/ Position, /*out*/ Direction);

					OutWorldPosition = CsMathLibrary::Convert(Position);
					OutWorldDirection = CsMathLibrary::Convert(Direction);
					return true;
				}

				// Something went wrong, zero things and return false
				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Unexpected error."), *Context));
				return false;
			}

			bool FLibrary::SafeDeprojectScreenToWorld(const UObject* WorldContext, const FVector2D& ScreenPosition, FVector& OutWorldPosition, FVector& OutWorldDirection)
			{
				CS_SET_CONTEXT_AS_FUNCTION_NAME(SafeDeprojectScreenToWorld);

				return SafeDeprojectScreenToWorld(Context, WorldContext, ScreenPosition, OutWorldPosition, OutWorldDirection, nullptr);
			}

			bool FLibrary::SafeDeprojectScreenToWorld(const UObject* WorldContext, const FVector2f& ScreenPosition, FVector3f& OutWorldPosition, FVector3f& OutWorldDirection)
			{
				CS_SET_CONTEXT_AS_FUNCTION_NAME(SafeDeprojectScreenToWorld);

				return SafeDeprojectScreenToWorld(Context, WorldContext, ScreenPosition, OutWorldPosition, OutWorldDirection);
			}

			FSceneViewport* FLibrary::GetViewportChecked(const FString& Context, const UObject* WorldContext)
			{
				ULocalPlayer* LocalPlayer = CsPlayerLibrary::GetFirstLocalChecked(Context, WorldContext);
				UGameViewportClient* GVC  = LocalPlayer->ViewportClient;

				checkf(GVC, TEXT("%s: ViewportClient is NUll for LocalPlayer: %s."), *Context, *(LocalPlayer->GetName()));

				FSceneViewport* SV = GVC->GetGameViewport();

				checkf(SV, TEXT("%s: Failed get Viewport from LocalPlayer: %s with ViewportClient: %s."), *Context, *(LocalPlayer->GetName()), *(GVC->GetName()));	
				return SV;
			}

			FSceneViewport* FLibrary::GetSafeViewport(const FString& Context, const UObject* WorldContext, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT)
			{
				ULocalPlayer* LocalPlayer = CsPlayerLibrary::GetSafeFirstLocal(Context, WorldContext, Log);

				if (!LocalPlayer)
					return nullptr;

				UGameViewportClient* GVC = LocalPlayer->ViewportClient;

				if (!GVC)
				{
					CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: ViewportClient is NUll for LocalPlayer: %s."), *Context, *(LocalPlayer->GetName())));
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
				CS_SET_CONTEXT_AS_FUNCTION_NAME(GetSafeViewport);

				return GetSafeViewport(Context, WorldContext, nullptr);
			}

			FIntPoint FLibrary::GetSizeChecked(const FString& Context, const UObject* WorldContext)
			{
				return GetViewportChecked(Context, WorldContext)->GetSizeXY();
			}

			FIntPoint FLibrary::GetSafeSize(const FString& Context, const UObject* WorldContext, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT)
			{
				FSceneViewport* SV = GetSafeViewport(Context, WorldContext, Log);

				if (!SV)
					return FIntPoint::NoneValue;
				return SV->GetSizeXY();
			}

			FIntPoint FLibrary::GetSafeSize(const UObject* WorldContext)
			{
				CS_SET_CONTEXT_AS_FUNCTION_NAME(GetSafeSize);

				return GetSafeSize(Context, WorldContext, nullptr);
			}

			bool FLibrary::GetScreenWorldIntersectionChecked(const FString& Context, const UObject* WorldContext, const FVector2f& ScreenPosition, const FPlane4f& Plane, FVector3f& OutIntersection)
			{
				FVector3f WorldPosition;
				FVector3f WorldDirection;
				bool Success = DeprojectScreenToWorldChecked(Context, WorldContext, ScreenPosition, WorldPosition, WorldDirection);

				checkf(Success, TEXT("%s: Failed to deproject ScreenPosition: %s."), *Context, *(ScreenPosition.ToString()));

				FCsRay3f Ray(WorldPosition, WorldDirection, true);
				float T;

				return CsMathLibrary::RayPlaneIntersectionChecked(Context, Ray, Plane, T, OutIntersection);
			}

			bool FLibrary::GetScreenWorldIntersectionChecked(const FString& Context, const UObject* WorldContext, const FVector2D& ScreenPosition, const FPlane& Plane, FVector& OutIntersection)
			{
				FVector WorldPosition;
				FVector WorldDirection;
				bool Success = DeprojectScreenToWorldChecked(Context, WorldContext, ScreenPosition, WorldPosition, WorldDirection);

				checkf(Success, TEXT("%s: Failed to deproject ScreenPosition: %s."), *Context, *(ScreenPosition.ToString()));

				FCsRay Ray(WorldPosition, WorldDirection, true);
				double T;

				return CsMathLibrary::RayPlaneIntersectionChecked(Context, Ray, Plane, T, OutIntersection);
			}

			bool FLibrary::GetSafeScreenWorldIntersection(const FString& Context, const UObject* WorldContext, const FVector2D& ScreenPosition, const FPlane& Plane, FVector& OutIntersection, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT)
			{
				FVector WorldPosition = FVector::ZeroVector;
				FVector WorldDirection = FVector::ZeroVector;
				bool Success = SafeDeprojectScreenToWorld(Context, WorldContext, ScreenPosition, WorldPosition, WorldDirection, Log);

				if (!Success)
				{
					CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to deproject ScreenPosition: %s."), *Context, *(ScreenPosition.ToString())));
					return false;
				}

				FCsRay Ray(WorldPosition, WorldDirection, true);
				double T;

				return CsMathLibrary::SafeRayPlaneIntersection(Context, Ray, Plane, T, OutIntersection, Log);
			}

			bool FLibrary::GetSafeScreenWorldIntersection(const FString& Context, const UObject* WorldContext, const FVector2f& ScreenPosition, const FPlane4f& Plane, FVector3f& OutIntersection, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT)
			{
				FVector3f WorldPosition = FVector3f::ZeroVector;
				FVector3f WorldDirection = FVector3f::ZeroVector;
				bool Success = SafeDeprojectScreenToWorld(Context, WorldContext, ScreenPosition, WorldPosition, WorldDirection, Log);

				if (!Success)
				{
					CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to deproject ScreenPosition: %s."), *Context, *(ScreenPosition.ToString())));
					return false;
				}

				FCsRay3f Ray(WorldPosition, WorldDirection, true);
				float T;

				return CsMathLibrary::SafeRayPlaneIntersection(Context, Ray, Plane, T, OutIntersection, Log);
			}

			bool FLibrary::GetSafeScreenWorldIntersection(const UObject* WorldContext, const FVector2D& ScreenPosition, const FPlane& Plane, FVector& OutIntersection)
			{
				CS_SET_CONTEXT_AS_FUNCTION_NAME(GetSafeScreenWorldIntersection);

				return GetSafeScreenWorldIntersection(Context, WorldContext, ScreenPosition, Plane, OutIntersection, nullptr);
			}

			bool FLibrary::GetSafeScreenWorldIntersection(const UObject* WorldContext, const FVector2f& ScreenPosition, const FPlane4f& Plane, FVector3f& OutIntersection)
			{
				CS_SET_CONTEXT_AS_FUNCTION_NAME(GetSafeScreenWorldIntersection);

				return GetSafeScreenWorldIntersection(Context, WorldContext, ScreenPosition, Plane, OutIntersection, nullptr);
			}
		}
	}
}

namespace NCsViewport
{
	namespace NGame
	{
		UGameViewportClient* FLibrary::GetClientChecked(const FString& Context, const UObject* WorldContext)
		{
			UGameInstance* GameInstance = CsGameInstanceLibrary::GetChecked(Context, WorldContext);
			UGameViewportClient* GVC	= GameInstance->GetGameViewportClient();

			checkf(GVC, TEXT("%s: Failed to get GameViewportClient from GameInstance."), *Context);
			return GVC;
		}
	}
}