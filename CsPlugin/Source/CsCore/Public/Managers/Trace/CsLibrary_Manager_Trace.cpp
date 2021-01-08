// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Trace/CsLibrary_Manager_Trace.h"

// Library
#include "Kismet/GameplayStatics.h"
#include "Library/CsLibrary_Viewport.h"
#include "Library/CsLibrary_Player.h"
// Managers
#include "Managers/Trace/CsManager_Trace.h"
// Game
#include "GameFramework/GameStateBase.h"
// World
#include "Engine/World.h"

namespace NCsTrace
{
	namespace NManager
	{
		namespace NCached
		{
			namespace Name
			{
				const FName TraceScreenToWorldChecked = FName("TraceScreenToWorldChecked");
			}
		}

		UObject* FLibrary::GetContextRootChecked(const FString& Context, UObject* WorldContext)
		{
			checkf(WorldContext, TEXT("%s: WorldContext is NULL."), *Context);

			UWorld* World = WorldContext->GetWorld();

			checkf(World, TEXT("%s: Failed to get World from WorldcContext: %s."), *Context, *(WorldContext->GetName()));

			return World->GetGameState();
		}

		FCsTraceResponse* FLibrary::TraceScreenToWorldChecked(const FString& Context, UObject* WorldContext, const FVector2D& ScreenPosition, const float& Distance, const TEnumAsByte<ECollisionChannel>& Channel)
		{
			using namespace NCached;

			typedef NCsViewport::NLocal::NPlayer::FLibrary ViewportLibrary;

			checkf(Distance > 0.0f, TEXT("%s: Distance: %f is NOT > 0.0f."), *Context, Distance);

			checkf(Channel != ECollisionChannel::ECC_MAX, TEXT("%s: Channel: ECC_MAX is NOT Valid."), *Context);

			APlayerController* PC = FCsLibrary_Player::GetFirstLocalPlayerControllerChecked(Context, WorldContext);

			FVector WorldOrigin;
			FVector WorldDirection;

			if (ViewportLibrary::DeprojectScreenToWorldChecked(Context, WorldContext, ScreenPosition, WorldOrigin, WorldDirection))
			{
				UObject* ContextRoot = GetContextRootChecked(Context, WorldContext);

				UCsManager_Trace* Manager_Trace = UCsManager_Trace::Get(ContextRoot);

				FCsTraceRequest* Request = Manager_Trace->AllocateRequest();
				Request->ProfileName	= Name::TraceScreenToWorldChecked;
				Request->Type			= ECsTraceType::Line;
				Request->Method			= ECsTraceMethod::Multi;
				Request->Query			= ECsTraceQuery::Channel;
				Request->Start			= WorldOrigin;
				Request->End			= WorldOrigin + WorldDirection * Distance;
				Request->Channel		= Channel;

				return Manager_Trace->Trace(Request);
			}
			return nullptr;
		}
	}
}