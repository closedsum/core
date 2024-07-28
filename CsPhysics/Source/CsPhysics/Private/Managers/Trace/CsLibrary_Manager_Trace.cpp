// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/Trace/CsLibrary_Manager_Trace.h"

// Library
#include "Library/CsLibrary_SkeletalMesh.h"
#include "Kismet/GameplayStatics.h"
#include "Library/CsLibrary_Viewport.h"
#include "Game/CsLibrary_GameState.h"
#include "Player/CsLibrary_Player.h"
#include "Library/CsLibrary_Math.h"
#include "Library/CsLibrary_Valid.h"
// Managers
#include "Managers/Trace/CsManager_Trace.h"
// Components
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"

#if WITH_EDITOR
// Library
	// Common
#include "Library/CsLibrary_World.h"
// Managers
#include "Singleton/CsGetManagerSingleton.h"
#endif // #if WITH_EDITOR

namespace NCsTrace
{
	namespace NManager
	{
		namespace NLibrary
		{
			namespace NCached
			{
				namespace Str
				{
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsTrace::NManager::FLibrary, GetSafeContextRoot);
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsTrace::NManager::FLibrary, GetSafe);
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsTrace::NManager::FLibrary, SafeAllocateRequest);
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsTrace::NManager::FLibrary, SafeTrace);
				}

				namespace Name
				{
					const FName TraceScreenToWorldChecked = FName("TraceScreenToWorldChecked");
				}
			}
		}

		#define USING_NS_CACHED using namespace NCsTrace::NManager::NLibrary::NCached;
		#define SET_CONTEXT(__FunctionName) using namespace NCsTrace::NManager::NLibrary::NCached; \
			const FString& Context = Str::__FunctionName
		#define LogLevel void(*Log)(const FString&) /*=&NCsPhysics::FLog::Warning*/

		// ContextRoot
		#pragma region

		#if WITH_EDITOR

		UObject* FLibrary::GetContextRootChecked(const FString& Context, const UObject* WorldContext)
		{
			if (CsWorldLibrary::IsPlayInEditorOrEditorPreview(WorldContext))
			{
				const ICsGetManagerSingleton* GetManagerSingleton = CS_CONST_INTERFACE_CAST_CHECKED(WorldContext, UObject, ICsGetManagerSingleton);

				return GetManagerSingleton->_getUObject();
			}
			return CsGameStateLibrary::GetAsObjectChecked(Context, WorldContext);
		}

		UObject* FLibrary::GetSafeContextRoot(const FString& Context, const UObject* WorldContext, LogLevel)
		{
			if (CsWorldLibrary::IsPlayInEditorOrEditorPreview(WorldContext))
			{
				const ICsGetManagerSingleton* GetManagerSingleton = CS_CONST_INTERFACE_CAST_CHECKED(WorldContext, UObject, ICsGetManagerSingleton);

				return GetManagerSingleton->_getUObject();
			}
			return CsGameStateLibrary::GetSafeAsObject(Context, WorldContext, Log);
		}

		UObject* FLibrary::GetSafeContextRoot(const UObject* WorldContext)
		{
			SET_CONTEXT(GetSafeContextRoot);

			return GetSafeContextRoot(Context, WorldContext, nullptr);
		}

		#endif // #if WITH_EDITOR

		#pragma endregion ContextRoot

		// Get
		#pragma region

		UCsManager_Trace* FLibrary::GetChecked(const FString& Context, const UObject* WorldContext)
		{
			UObject* ContextRoot			 = GetContextRootChecked(Context, WorldContext);
			UCsManager_Trace* Manager_Trace  = UCsManager_Trace::Get(ContextRoot);

			CS_IS_PTR_NULL_CHECKED(Manager_Trace)
			return Manager_Trace;
		}

		UCsManager_Trace* FLibrary::GetSafe(const FString& Context, const UObject* WorldContext, LogLevel)
		{
			UObject* ContextRoot = GetSafeContextRoot(Context, WorldContext, Log);

		#if WITH_EDITOR
			if (!ContextRoot)
				return nullptr;
		#endif // #if WITH_EDITOR

			UCsManager_Trace* Manager_Trace = UCsManager_Trace::GetSafe(Context, ContextRoot, Log);

			if (!Manager_Trace)
			{
				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to get Manager_Trace."), *Context));
			}
			return Manager_Trace;
		}

		UCsManager_Trace* FLibrary::GetSafe(UObject* ContextObject)
		{
			SET_CONTEXT(GetSafe);

			return GetSafe(Context, ContextObject, nullptr);
		}

		#pragma endregion Get

		// Request
		#pragma region

		#define RequestType NCsTrace::NRequest::FRequest

		RequestType* FLibrary::AllocateRequestChecked(const FString& Context, const UObject* WorldContext)
		{
			return GetChecked(Context, WorldContext)->AllocateRequest();
		}

		RequestType* FLibrary::SafeAllocateRequest(const FString& Context, const UObject* WorldContext, LogLevel)
		{
			UCsManager_Trace* Manager_Trace = GetSafe(Context, WorldContext, Log);

			if (!Manager_Trace)
				return nullptr;
			return Manager_Trace->AllocateRequest();
		}

		RequestType* FLibrary::SafeAllocateRequest(const UObject* WorldContext)
		{
			SET_CONTEXT(SafeAllocateRequest);

			return SafeAllocateRequest(Context, WorldContext, nullptr);
		}

		bool FLibrary::SafeDeallocateRequest(const FString& Context, const UObject* WorldContext, RequestType* Request, LogLevel)
		{
			UCsManager_Trace* Manager_Trace = GetSafe(Context, WorldContext, Log);

			if (!Manager_Trace)
				return false;

			return Manager_Trace->SafeDeallocateRequest(Context, Request, Log);
		}

		#undef RequestType

		#pragma endregion Request

		#define ResponseType NCsTrace::NResponse::FResponse
		#define RequestType NCsTrace::NRequest::FRequest

		ResponseType* FLibrary::TraceChecked(const FString& Context, const UObject* WorldContext, RequestType* Request)
		{
			CS_IS_PTR_NULL_CHECKED(Request);

			check(Request->IsValidChecked(Context));

			return GetChecked(Context, WorldContext)->Trace(Request);
		}

		ResponseType* FLibrary::SafeTrace(const FString& Context, const UObject* WorldContext, RequestType* Request, LogLevel)
		{
			CS_IS_PTR_NULL_RET_NULL(Request)

			if (!Request->IsValid(Context, Log))
				return nullptr;

			UCsManager_Trace* Manager_Trace = GetSafe(Context, WorldContext, Log);

			if (!Manager_Trace)
				return nullptr;
			return Manager_Trace->Trace(Request);
		}

		ResponseType* FLibrary::SafeTrace(const UObject* WorldContext, RequestType* Request)
		{
			SET_CONTEXT(SafeTrace);

			return SafeTrace(Context, WorldContext, Request, nullptr);
		}

			// Sphere
		#pragma region

		#define ParamsType NCsTrace::NManager::FLibrary::FSphereTrace::FParams
		#define BoneSpaceType NCsTrace::NBone::ESpace

		bool FLibrary::SafeSphereTrace(const FString& Context, const ParamsType& Params, FHitResult& OutHit, LogLevel)
		{
			if (RequestType* Request = SafeAllocateRequest(Context, Params.GetWorldContext(), Log))
			{
				// Fill out Request
				bool OutSuccess = false;
				FVector Start	= CsSkeletalMeshLibrary::GetSafeBoneOrSocketLocation(Context, Params.Component, Params.BoneOrSocket, OutSuccess, Log);

				if (!OutSuccess)
				{
					SafeDeallocateRequest(Context, Params.GetWorldContext(), Request, Log);
					return false;
				}

				// Bone
				if (Params.Space == BoneSpaceType::Bone)
				{
					const FRotator Rotation = CsSkeletalMeshLibrary::GetSafeBoneOrSocketRotation(Context, Params.Component, Params.BoneOrSocket, OutSuccess, Log);
					Start					= CsMathLibrary::Add(Start, Rotation, Params.Location);
				}
				// Component
				else
				if (Params.Space == BoneSpaceType::Component)
				{
					const FRotator Rotation = Params.Component->GetComponentRotation();
					Start					= CsMathLibrary::Add(Start, Rotation, Params.Location);
				}

				if (!OutSuccess)
				{
					SafeDeallocateRequest(Context, Params.GetWorldContext(), Request, Log);
					return false;
				}

				Request->Type				  = ECsTraceType::Sweep;
				Request->Method				  = ECsTraceMethod::Single;
				Request->Query				  = ECsTraceQuery::Channel;
				Request->Start				  = CsMathLibrary::Convert(Start);
				Request->End				  = CsMathLibrary::Convert(Start);
				Request->Channel			  = Params.Channel;
				Request->Params.bTraceComplex = Params.bTraceComplex;
				Request->Shape.SetSphere(Params.Radius);

				if (Params.bIgnoreSelf)
				{
					if (AActor* Actor = Cast<AActor>(Params.GetWorldContext()))
						Request->Params.AddIgnoredActor(Actor);
				}

				Request->Params.AddIgnoredActors(Params.ActorsToIgnore);

				// Check Response
				if (ResponseType* Response = SafeTrace(Context, Params.GetWorldContext(), Request, Log))
				{
					if (Response->bResult)
					{
						OutHit = Response->OutHits[CS_FIRST];
					}
					return Response->bResult;
				}
				return false;
			}
			return false;
		}

		bool FLibrary::SafeSphereTrace(const FString& Context, UObject* WorldContext, const USkeletalMeshComponent* Component, const FName& BoneOrSocket, const float& Radius, const TEnumAsByte<ECollisionChannel>& Channel, const bool& bTraceComplex, const bool& bIgnoreSelf, const TArray<AActor*>& ActorsToIgnore, FHitResult& OutHit, LogLevel)
		{
			static ParamsType Params;
			Params.WorldContext = WorldContext;
			Params.Component	= const_cast<USkeletalMeshComponent*>(Component);
			Params.BoneOrSocket = BoneOrSocket;
			Params.Space		= BoneSpaceType::Bone;
			Params.Location		= FVector::ZeroVector;
			Params.Radius		= Radius;
			Params.Channel		= Channel;
			Params.bTraceComplex = bTraceComplex;
			Params.bIgnoreSelf	= bIgnoreSelf;
			Params.SetActorsToIngore(ActorsToIgnore);
			
			return SafeSphereTrace(Context, Params, OutHit, Log);
		}

		bool FLibrary::SphereTraceChecked(const FString& Context, const ParamsType& Params, FHitResult& OutHit)
		{
			RequestType* Request = AllocateRequestChecked(Context, Params.GetWorldContext());
			// Fill out Request
			FVector Start	= CsSkeletalMeshLibrary::GetBoneOrSocketLocationChecked(Context, Params.Component, Params.BoneOrSocket);

			// Bone
			if (Params.Space == BoneSpaceType::Bone)
			{
				const FRotator Rotation = CsSkeletalMeshLibrary::GetBoneOrSocketRotationChecked(Context, Params.Component, Params.BoneOrSocket);
				Start					= CsMathLibrary::Add(Start, Rotation, Params.Location);
			}
			// Component
			else
			if (Params.Space == BoneSpaceType::Component)
			{
				const FRotator Rotation = Params.Component->GetComponentRotation();
				Start					= CsMathLibrary::Add(Start, Rotation, Params.Location);
			}

			Request->Type				  = ECsTraceType::Sweep;
			Request->Method				  = ECsTraceMethod::Single;
			Request->Query				  = ECsTraceQuery::Channel;
			Request->Start				  = CsMathLibrary::Convert(Start);
			Request->End				  = CsMathLibrary::Convert(Start);
			Request->Channel			  = Params.Channel;
			Request->Params.bTraceComplex = Params.bTraceComplex;
			Request->Shape.SetSphere(Params.Radius);

			if (Params.bIgnoreSelf)
			{
				if (AActor* Actor = Cast<AActor>(Params.GetWorldContext()))
					Request->Params.AddIgnoredActor(Actor);
			}

			Request->Params.AddIgnoredActors(Params.ActorsToIgnore);

			// Check Response
			if (ResponseType* Response = TraceChecked(Context, Params.GetWorldContext(), Request))
			{
				if (Response->bResult)
				{
					OutHit = Response->OutHits[CS_FIRST];
				}
				return Response->bResult;
			}
			return false;
		}

		#undef ParamsType
		#undef BoneSpaceType

		#pragma endregion Sphere

			// Sweep
		#pragma region

		ResponseType* FLibrary::SafeSweep(const FString& Context, const UObject* WorldContext, UCapsuleComponent* Component, const FCollisionQueryParams& Params, LogLevel)
		{
			CS_IS_PENDING_KILL_RET_NULL(Component)
			CS_IS_FLOAT_GREATER_THAN_RET_NULL(Component->GetScaledCapsuleRadius(), 0.0f)
			CS_IS_FLOAT_GREATER_THAN_RET_NULL(Component->GetScaledCapsuleHalfHeight(), 0.0f)

			const ECollisionChannel Channel = Component->GetCollisionObjectType();

			if (Channel == ECollisionChannel::ECC_MAX ||
				Channel == ECollisionChannel::ECC_OverlapAll_Deprecated)
			{
				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Component->GetCollisionObjectType() == (ECollisionChannel::ECC_MAX || ECollisionChannel::ECC_OverlapAll_Deprecated) is NOT Valid."), *Context))
				return nullptr;
			}

			const FCollisionResponseContainer& Container = Component->GetCollisionResponseToChannels();

			if (!NCsCollisionResponseContainer::IsValid(Context, Container, Log))
				return nullptr;
				
			UCsManager_Trace* Manager_Trace = GetSafe(Context, WorldContext, Log);

			if (!Manager_Trace)
				return nullptr;

			RequestType* Request = Manager_Trace->AllocateRequest();

			Request->Type	  = ECsTraceType::Sweep;
			Request->Method   = ECsTraceMethod::Multi;
			Request->Query	  = ECsTraceQuery::Channel;
			Request->Start	  = CsMathLibrary::Convert(Component->GetComponentLocation());
			Request->End	  = CsMathLibrary::Convert(Component->GetComponentLocation());
			Request->Rotation = CsMathLibrary::Convert(Component->GetComponentRotation());
			Request->SetShape(Component);
			Request->Channel						  = Channel;
			Request->Params							  = Params;
			Request->ResponseParams.CollisionResponse = Container;

			return Manager_Trace->Trace(Request);
		}

		ResponseType* FLibrary::SafeSweepAgainstObject(const FString& Context, const UObject* WorldContext, UCapsuleComponent* Component, const FCollisionQueryParams& Params, UObject* Object, LogLevel)
		{
			CS_IS_PENDING_KILL_RET_NULL(Component)
			CS_IS_FLOAT_GREATER_THAN_RET_NULL(Component->GetScaledCapsuleRadius(), 0.0f)
			CS_IS_FLOAT_GREATER_THAN_RET_NULL(Component->GetScaledCapsuleHalfHeight(), 0.0f)

			const ECollisionChannel Channel = Component->GetCollisionObjectType();

			if (Channel == ECollisionChannel::ECC_MAX ||
				Channel == ECollisionChannel::ECC_OverlapAll_Deprecated)
			{
				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Component->GetCollisionObjectType() == (ECollisionChannel::ECC_MAX || ECollisionChannel::ECC_OverlapAll_Deprecated) is NOT Valid."), *Context))
				return nullptr;
			}

			const FCollisionResponseContainer& Container = Component->GetCollisionResponseToChannels();

			if (!NCsCollisionResponseContainer::IsValid(Context, Container, Log))
				return nullptr;

			CS_IS_PTR_NULL_RET_NULL(Object)

			UCsManager_Trace* Manager_Trace = GetSafe(Context, WorldContext, Log);

			if (!Manager_Trace)
				return nullptr;

			RequestType* Request = Manager_Trace->AllocateRequest();

			Request->Type	  = ECsTraceType::Sweep;
			Request->Method	  = ECsTraceMethod::Multi;
			Request->Query	  = ECsTraceQuery::Channel;
			Request->Start	  = CsMathLibrary::Convert(Component->GetComponentLocation());
			Request->End	  = CsMathLibrary::Convert(Component->GetComponentLocation());
			Request->Rotation = CsMathLibrary::Convert(Component->GetComponentRotation());
			Request->SetShape(Component);
			Request->Channel						  = Channel;
			Request->Params							  = Params;
			Request->ResponseParams.CollisionResponse = Container;

			ResponseType* Response = Manager_Trace->Trace(Request);

			bool ObjectFound = false;

			for (const FHitResult& Hit : Response->OutHits)
			{
				if (Object == Hit.GetActor())
				{
					ObjectFound = true;
					continue;
				}

				if (Object == Hit.GetComponent())
				{
					ObjectFound = true;
					continue;
				}
			}

			if (!ObjectFound)
				return nullptr;
			return Response;
		}

		ResponseType* FLibrary::SafeSweepAgainstObjectOnly(const FString& Context, const UObject* WorldContext, UCapsuleComponent* Component, const FCollisionQueryParams& Params, UObject* Object, LogLevel)
		{
			CS_IS_PENDING_KILL_RET_NULL(Component)
			CS_IS_FLOAT_GREATER_THAN_RET_NULL(Component->GetScaledCapsuleRadius(), 0.0f)
			CS_IS_FLOAT_GREATER_THAN_RET_NULL(Component->GetScaledCapsuleHalfHeight(), 0.0f)

			const ECollisionChannel Channel = Component->GetCollisionObjectType();

			if (Channel == ECollisionChannel::ECC_MAX ||
				Channel == ECollisionChannel::ECC_OverlapAll_Deprecated)
			{
				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Component->GetCollisionObjectType() == (ECollisionChannel::ECC_MAX || ECollisionChannel::ECC_OverlapAll_Deprecated) is NOT Valid."), *Context))
				return nullptr;
			}

			const FCollisionResponseContainer& Container = Component->GetCollisionResponseToChannels();

			if (!NCsCollisionResponseContainer::IsValid(Context, Container, Log))
				return nullptr;

			CS_IS_PTR_NULL_RET_NULL(Object)

			UCsManager_Trace* Manager_Trace = GetSafe(Context, WorldContext, Log);

			if (!Manager_Trace)
				return nullptr;

			RequestType* Request = Manager_Trace->AllocateRequest();

			Request->Type	  = ECsTraceType::Sweep;
			Request->Method   = ECsTraceMethod::Multi;
			Request->Query	  = ECsTraceQuery::Channel;
			Request->Start	  = CsMathLibrary::Convert(Component->GetComponentLocation());
			Request->End	  = CsMathLibrary::Convert(Component->GetComponentLocation());
			Request->Rotation = CsMathLibrary::Convert(Component->GetComponentRotation());
			Request->SetShape(Component);
			Request->Channel = Channel;
			Request->Params  = Params;
			Request->ResponseParams.CollisionResponse = Container;

			ResponseType* Response = Manager_Trace->Trace(Request);

			const int32 Count = Response->OutHits.Num();

			for (int32 I = Count - 1; I >= 0; --I)
			{
				const FHitResult& Hit = Response->OutHits[I];

				if (Object == Hit.GetActor())
					continue;

				if (Object == Hit.GetComponent())
					continue;

				Response->OutHits.RemoveAt(I, 1, false);
			}

			if (Response->OutHits.Num() == CS_EMPTY)
				return nullptr;
			return Response;
		}

		#pragma endregion Sweep

			// Screen
		#pragma region

		ResponseType* FLibrary::TraceScreenToWorldChecked(const FString& Context, const UObject* WorldContext, const FVector2f& ScreenPosition, const float& Distance, const ECollisionChannel& Channel)
		{
			USING_NS_CACHED

			CS_IS_FLOAT_GREATER_THAN_OR_EQUAL_CHECKED(Distance, 0.0f)

			checkf(Channel != ECollisionChannel::ECC_MAX, TEXT("%s: Channel: ECC_MAX is NOT Valid."), *Context);

			typedef NCsViewport::NLocal::NPlayer::FLibrary ViewportLibrary;

			FVector3f WorldOrigin;
			FVector3f WorldDirection;

			if (ViewportLibrary::DeprojectScreenToWorldChecked(Context, WorldContext, ScreenPosition, WorldOrigin, WorldDirection))
			{
				UCsManager_Trace* Manager_Trace = GetChecked(Context, WorldContext);

				RequestType* Request    = Manager_Trace->AllocateRequest();
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

		#pragma endregion Screen

		#undef ResponseType
		#undef RequestType

		#undef USING_NS_CACHED
		#undef SET_CONTEXT
		#undef LogLevel
	}
}