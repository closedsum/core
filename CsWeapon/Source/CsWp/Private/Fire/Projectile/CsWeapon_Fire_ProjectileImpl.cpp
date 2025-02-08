// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Fire/Projectile/CsWeapon_Fire_ProjectileImpl.h"
#include "CsWp.h"

// CVar
#include "Script/CsCVars_Script.h"
#include "Projectile/CsCVars_ProjectileWeapon.h"
// Types
#include "CsMacro_Misc.h"
#include "Types/CsTypes_Math_Library.h"
// Library
#include "Managers/Trace/CsLibrary_Manager_Trace.h"
#include "Managers/Projectile/CsLibrary_Manager_Projectile.h"
	// Data
#include "Data/CsLibrary_Data_Projectile.h"
	// Weapon
#include "Projectile/Params/Launch/CsLibrary_Params_ProjectileWeapon_Launch.h"
	// Common
#include "Camera/CsLibrary_Camera.h"
#include "Library/CsLibrary_Math.h"
#include "Library/CsLibrary_Valid.h"
// Data
	// Projectile
#include "Data/Collision/CsData_Projectile_Collision.h"
// Trace
#include "Managers/Trace/CsTraceRequest.h"
// Weapon
#include "CsWeapon.h"
#include "Projectile/CsProjectileWeapon.h"
	// Projectile
#include "Projectile/Params/Launch/Trace/CsParams_ProjectileWeapon_LaunchTrace.h"
// Projectile
#include "Types/CsGetProjectileType.h"
// Interface
#include "Object/Orientation/CsObject_Orientation.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsWeapon_Fire_ProjectileImpl)

UCsWeapon_Fire_Projectile::UCsWeapon_Fire_Projectile(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

// UCsWeapon_Fire_ProjectileImpl
//	Cached
#pragma region

CS_START_CACHED_FUNCTION_NAME(CsWeapon_Fire_ProjectileImpl)
	// ICsWeapon_Component
	CS_DEFINE_CACHED_FUNCTION_NAME(UCsWeapon_Fire_ProjectileImpl, SetWeapon)
	// Weapon_Fire_Projectile
	CS_DEFINE_CACHED_FUNCTION_NAME(UCsWeapon_Fire_ProjectileImpl, GetLaunchLocation)
	CS_DEFINE_CACHED_FUNCTION_NAME(UCsWeapon_Fire_ProjectileImpl, GetLaunchDirection)
CS_END_CACHED_FUNCTION_NAME

#pragma endregion Cached

UCsWeapon_Fire_ProjectileImpl::UCsWeapon_Fire_ProjectileImpl(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

using ParamsLibrary = NCsWeapon::NProjectile::NParams::NLaunch::NLibrary::FLibrary;
using ParamsType = NCsWeapon::NProjectile::NParams::NLaunch::ILaunch;
using LocationType = NCsWeapon::NProjectile::NParams::NLaunch::ELocation;
using LocationOffsetSpaceType = NCsWeapon::NProjectile::NParams::NLaunch::NLocation::EOffsetSpace;
using DirectionMapType = NCsWeapon::NProjectile::NParams::NLaunch::EMDirection;
using DirectionType = NCsWeapon::NProjectile::NParams::NLaunch::EDirection;


// ICsWeapon_Component
#pragma region

void UCsWeapon_Fire_ProjectileImpl::SetWeapon(ICsWeapon* InWeapon) 
{
	CS_SET_CONTEXT_AS_FUNCTION_NAME(SetWeapon);

	Weapon		   = InWeapon;
	WeaponAsObject = Weapon->_getUObject();
	ProjectileWeapon = CS_INTERFACE_CAST_CHECKED(WeaponAsObject, UObject, ICsProjectileWeapon);
}

#pragma endregion ICsWeapon_Component

// ICsWeapon_Fire_Projectile
#pragma region

FVector UCsWeapon_Fire_ProjectileImpl::GetLaunchLocation(const PayloadType& Payload)
{
	/*using namespace NCsProjectileWeaponActorPooled::NCached::NProjectileImpl;

	const FString& ScopeName		   = Str::GetLaunchLocation;
	const FECsScopedGroup& ScopedGroup = NCsScopedGroup::WeaponProjectile;
	const FECsCVarLog& ScopeLog		   = NCsCVarLog::LogWeaponProjectileScopedTimerGetLaunchLocation;

	CS_SCOPED_TIMER_ONE_SHOT(&ScopeName, ScopedGroup, ScopeLog);*/

	CS_SET_CONTEXT_AS_FUNCTION_NAME(GetLaunchLocation);
	
	if (Payload.Shot.UseCachedLocation())
		return GetLaunchSpreadLocation(Payload.Shot.CachedLocation, Payload);

	// Get Launch Params
	const ParamsType* Params = ParamsLibrary::GetChecked(Context, Weapon->GetData());

	const LocationType& LocType			   = Params->GetLocationType();
	const LocationOffsetSpaceType& LocationOffsetSpace = Params->GetLocationOffsetSpace();
	const int32& LocationOffsetSpaceRules		   = Params->GetLocationOffsetSpaceRules();
	const int32 InvLocationOffsetSpaceRules		   = ~LocationOffsetSpaceRules & ((int32)NCsRotationRules::All);
	const FRotator& LocationOffsetSpaceOffset	   = Params->GetLocationOffsetSpaceOffset();
	const FVector& LocationOffset				   = Params->GetLocationOffset();

	// Determine Offset
	FVector Offset = LocationOffset * NCsRotationRules::GetDirection(FVector::OneVector, InvLocationOffsetSpaceRules);
	{
		// None
		if (LocationOffsetSpace == LocationOffsetSpaceType::None)
		{
			Offset = LocationOffset;
		}
		// Owner
		else
		if (LocationOffsetSpace == LocationOffsetSpaceType::Owner)
		{
			UObject* TheOwner = Weapon->GetWeaponOwner();

			checkf(IsValid(TheOwner), TEXT("%s: No Owner found for %s."), *Context, *PrintWeaponNameAndClass());

			bool IsValidOwner = false;

			FRotator Rotation = FRotator::ZeroRotator;

			// CsObject_Orientation
			if (ICsObject_Orientation* Object_Movement = Cast<ICsObject_Orientation>(TheOwner))
			{
				Rotation	 = NCsRotationRules::GetRotation(Object_Movement->Orientation_GetRotation3d(), LocationOffsetSpaceRules);
				IsValidOwner = true;
			}
			// AActor
			else
			if (AActor* Actor = Cast<AActor>(TheOwner))
			{
				Rotation	 = NCsRotationRules::GetRotation(Actor, LocationOffsetSpaceRules);
				IsValidOwner = true;
			}
			// USceneComponent
			else
			if (USceneComponent* Component = Cast<USceneComponent>(TheOwner))
			{
				Rotation	  = NCsRotationRules::GetRotation(Component, LocationOffsetSpaceRules);
				IsValidOwner  = true;
			}

			if (IsValidOwner)
			{
				FVector Dir	= Rotation.Vector();

				const FRotator RotationOffset = NCsRotationRules::GetRotation(LocationOffsetSpaceOffset, LocationOffsetSpaceRules);

				Dir = Dir.RotateAngleAxis(RotationOffset.Pitch, CsMathLibrary::GetRightFromNormal(Dir));
				Dir = Dir.RotateAngleAxis(RotationOffset.Yaw, FVector::UpVector);
				
				FVector Right, Up;
				CsMathLibrary::GetRightAndUpFromNormal(Dir, Right, Up);

				Offset += LocationOffset.X * Dir + LocationOffset.Y * Right + LocationOffset.Z * Up;
			}
			else
			{
				checkf(0, TEXT("%s: Failed to get Location from %s."), *Context, *PrintWeaponNameClassAndOwner());
			}
		}
		// Bone
		else
		if (LocationOffsetSpace == LocationOffsetSpaceType::Owner)
		{
			checkf(0, TEXT("NOT IMPLEMENTED"));
		}
		// Component
		else
		if (LocationOffsetSpace == LocationOffsetSpaceType::Component)
		{
			CS_IS_PTR_NULL_CHECKED(ComponentDirection)

			const FRotator Rotation = NCsRotationRules::GetRotation(ComponentDirection, LocationOffsetSpaceRules);
			FVector Dir				= Rotation.Vector();

			const FRotator RotationOffset = NCsRotationRules::GetRotation(LocationOffsetSpaceOffset, LocationOffsetSpaceRules);

			Dir = Dir.RotateAngleAxis(RotationOffset.Pitch, CsMathLibrary::GetRightFromNormal(Dir));
			Dir = Dir.RotateAngleAxis(RotationOffset.Yaw, FVector::UpVector);

			FVector Right, Up;
			CsMathLibrary::GetRightAndUpFromNormal(Dir, Right, Up);

			Offset += LocationOffset.X * Dir + LocationOffset.Y * Right + LocationOffset.Z * Up;
		}
		// Camera
		else
		if (LocationOffsetSpace == LocationOffsetSpaceType::Camera)
		{
			// Try to get camera through the owner
			if (IsValid(WeaponAsObject))
			{
				FVector Dir	= CsCameraLibrary::GetDirectionChecked(Context, WeaponAsObject, LocationOffsetSpaceRules);

				const FRotator3f RotationOffset = NCsRotationRules::GetRotation3f(LocationOffsetSpaceOffset, LocationOffsetSpaceRules);

				Dir = Dir.RotateAngleAxis(RotationOffset.Pitch, CsMathLibrary::GetRightFromNormal(Dir));
				Dir = Dir.RotateAngleAxis(RotationOffset.Yaw, FVector::UpVector);

				FVector Right, Up;
				CsMathLibrary::GetRightAndUpFromNormal(Dir, Right, Up);

				Offset += LocationOffset.X * Dir + LocationOffset.Y * Right + LocationOffset.Z * Up;
			}
			else
			{
				checkf(0, TEXT("%s: Failed to find Camera / Camera Component from %s."), *Context, *PrintWeaponNameAndClass());
			}
		}
		// Custom
		else
		if (LocationOffsetSpace == LocationOffsetSpaceType::Custom)
		{
			checkf(0, TEXT("NOT IMPLEMENTED"));
		}
	}

	// TODO: Have "Apply Spread" for other Location Types
	
	// Owner
	if (LocType == LocationType::Owner)
	{
		UObject* TheOwner = Weapon->GetWeaponOwner();

		checkf(TheOwner, TEXT("%s: No Owner found for %s."), *Context, *PrintWeaponNameAndClass());

		FVector Location = FVector::ZeroVector;

		// Actor
		if (AActor* Actor = Cast<AActor>(TheOwner))
		{
			Location = Actor->GetActorLocation() + Offset;
		}
		// Component
		else
		if (USceneComponent* Component = Cast<USceneComponent>(TheOwner))
		{
			Location = Component->GetComponentLocation() + Offset;
		}
		else
		{
			checkf(0, TEXT("%s: Failed to get Location from %s."), *Context, *PrintWeaponNameClassAndOwner());
		}
		return GetLaunchSpreadLocation(Location, Payload);
	}
	// Bone
	if (LocType == LocationType::Bone)
	{
		checkf(0, TEXT("NOT IMPLEMENTED"));
	}
	// Component
	if (LocType == LocationType::Component)
	{
		CS_IS_PTR_NULL_CHECKED(ComponentLocation)

		FVector Location = ComponentLocation->GetComponentLocation() + Offset;

		return GetLaunchSpreadLocation(Location, Payload);
	}
	// Custom
	if (LocType == LocationType::Custom)
	{
		FVector Location = CustomLocation + Offset;

		// TODO: Get the Launch Direction properly
		
		// TEMP: Just assume DirectionType is Custom

		return GetLaunchSpreadLocation(Location, Payload);
	}
	checkf(0, TEXT("%s: Failed to get Location from %s."), *Context, *PrintWeaponNameClassAndOwner());
	return FVector::ZeroVector;
}

FVector UCsWeapon_Fire_ProjectileImpl::GetLaunchDirection(const PayloadType& Payload)
{
/*
	using namespace NCsProjectileWeaponActorPooled::NCached::NProjectileImpl;

	const FString& ScopeName		   = Str::GetLaunchDirection;
	const FECsScopedGroup& ScopedGroup = NCsScopedGroup::WeaponProjectile;
	const FECsCVarLog& ScopeLog		   = NCsCVarLog::LogWeaponProjectileScopedTimerGetLaunchDirection;

	CS_SCOPED_TIMER_ONE_SHOT(&ScopeName, ScopedGroup, ScopeLog);
*/
	CS_SET_CONTEXT_AS_FUNCTION_NAME(GetLaunchDirection);

#if WITH_EDITOR
	if (bOverride_GetLaunchDirection)
	{
		if (CS_CVAR_LOG_IS_SHOWING(LogOverrideFunctions))
		{
			UE_LOG(LogCsWp, Warning, TEXT("%s OVERRIDDEN for %s."), *Context, *(GetName()));
		}
		return Override_GetLaunchDirection();
	}
#endif // #if WITH_EDITOR

	// Get Launch Params
	const ParamsType* Params = ParamsLibrary::GetChecked(Context, Weapon->GetData());

	const LocationType& LocType		= Params->GetLocationType();
	const DirectionType& DirType	= Params->GetDirectionType();
	const FRotator& DirectionOffset = Params->GetDirectionOffset();
	int32 DirectionScalar			= Params->InvertDirection() ? -1.0f : 1.0f;
	const int32& DirectionRules		= Params->GetDirectionRules();

	if (Payload.Shot.UseCachedDirection())
	{
		const FVector Dir = NCsRotationRules::GetDirection(Payload.Shot.CachedDirection, DirectionRules);

		return GetLaunchSpreadDirection(Dir, Payload);
	}

	// Owner
	if (DirType == DirectionType::Owner)
	{
		if (UObject* TheOwner = Weapon->GetWeaponOwner())
		{
			// AActor
			if (AActor* Actor = Cast<AActor>(TheOwner))
			{
				const FRotator Rotation = NCsRotationRules::GetRotation(Actor, DirectionRules);
				FVector Dir				= Rotation.Vector();

				const FRotator RotationOffset = NCsRotationRules::GetRotation(DirectionOffset, DirectionRules);

				Dir = Dir.RotateAngleAxis(RotationOffset.Pitch, CsMathLibrary::GetRightFromNormal(Dir));
				Dir = Dir.RotateAngleAxis(RotationOffset.Yaw, FVector::UpVector);
				Dir = DirectionScalar * GetLaunchSpreadDirection(Dir, Payload);
				CS_NON_SHIPPING_EXPR(Log_GetLaunchDirection(Params, Dir));
				return Dir;
			}
			// USceneComponent
			if (USceneComponent* Component = Cast<USceneComponent>(TheOwner))
			{
				const FRotator Rotation = NCsRotationRules::GetRotation(Component, DirectionRules);
				FVector Dir				= Rotation.Vector();

				const FRotator RotationOffset = NCsRotationRules::GetRotation(DirectionOffset, DirectionRules);

				Dir = Dir.RotateAngleAxis(RotationOffset.Pitch, CsMathLibrary::GetRightFromNormal(Dir));
				Dir = Dir.RotateAngleAxis(RotationOffset.Yaw, FVector::UpVector);
				Dir = DirectionScalar * GetLaunchSpreadDirection(Dir, Payload);
				CS_NON_SHIPPING_EXPR(Log_GetLaunchDirection(Params, Dir));
				return Dir;
			}
			checkf(0, TEXT("%s: Failed to get Direction from %s."), *Context, *PrintWeaponNameClassAndOwner());
		}
	}
	// Bone
	if (DirType == DirectionType::Bone)
	{
		checkf(0, TEXT("NOT IMPLEMENTED"));
	}
	// Component
	if (DirType == DirectionType::Component)
	{
		const FRotator Rotation = NCsRotationRules::GetRotation(ComponentDirection, DirectionRules);
		FVector Dir			    = Rotation.Vector();

		const FRotator3f RotationOffset = NCsRotationRules::GetRotation(CsMathLibrary::Convert(DirectionOffset), DirectionRules);

		Dir = Dir.RotateAngleAxis(RotationOffset.Pitch, CsMathLibrary::GetRightFromNormal(Dir));
		Dir = Dir.RotateAngleAxis(RotationOffset.Yaw, FVector::UpVector);
		Dir = DirectionScalar * GetLaunchSpreadDirection(Dir, Payload);
		CS_NON_SHIPPING_EXPR(Log_GetLaunchDirection(Params, Dir));
		return Dir;
	}
	// Camera
	if (DirType == DirectionType::Camera)
	{
		// Try to get camera through the owner
		if (UObject* TheOwner = Weapon->GetWeaponOwner())
		{
			FVector Dir	= CsCameraLibrary::GetDirectionChecked(Context, WeaponAsObject, DirectionRules);

			const FRotator RotationOffset = NCsRotationRules::GetRotation(DirectionOffset, DirectionRules);

			Dir = Dir.RotateAngleAxis(RotationOffset.Pitch, CsMathLibrary::GetRightFromNormal(Dir));
			Dir = Dir.RotateAngleAxis(RotationOffset.Yaw, FVector::UpVector);
			Dir = DirectionScalar * GetLaunchSpreadDirection(Dir, Payload);
			CS_NON_SHIPPING_EXPR(Log_GetLaunchDirection(Params, Dir));
			return Dir;
		}
		checkf(0, TEXT("%s: Failed to find Camera / Camera Component from %s."), *Context, *PrintWeaponNameAndClass());
	}
	// ITrace | Get Launch Trace Params
	if (DirType == DirectionType::Trace)
	{
		using TraceParamsType = NCsWeapon::NProjectile::NParams::NLaunch::NTrace::ITrace;
		using TraceStartType = NCsWeapon::NProjectile::NParams::NLaunch::NTrace::EStart;

		const TraceParamsType* TraceParams = ParamsLibrary::GetInterfaceChecked<TraceParamsType>(Context, Params);
		
		// Start
		const TraceStartType& TraceStart = TraceParams->GetTraceStartType();

		FVector Start = FVector::ZeroVector;

		// LaunchLocation
		if (TraceStart == TraceStartType::LaunchLocation)
		{
			Start = GetLaunchLocation(Payload);
		}
		// Owner
		else
		if (TraceStart == TraceStartType::Owner)
		{
			checkf(0, TEXT("NOT IMPLEMENTED"));
		}
		// Bone
		else
		if (TraceStart == TraceStartType::Bone)
		{
			checkf(0, TEXT("NOT IMPLEMENTED"));
		}
		// Component
		else
		if (TraceStart == TraceStartType::Component)
		{
			CS_IS_PENDING_KILL_CHECKED(ComponentLocation)

			Start = ComponentLocation->GetComponentLocation();
		}
		// Camera
		else
		if (TraceStart == TraceStartType::Camera)
		{
			// Try to get camera through the owner
			if (UObject* TheOwner = Weapon->GetWeaponOwner())
			{
				Start = CsCameraLibrary::GetLocationChecked(Context, TheOwner);
			}
			// TODO: For now assert
			else
			{
				checkf(0, TEXT("%s: Failed to find Camera / Camera Component from %s."), *Context, *PrintWeaponNameAndClass());
			}
		}

		// Direction
		using TraceDirectionType = NCsWeapon::NProjectile::NParams::NLaunch::NTrace::EDirection;

		const TraceDirectionType& TraceDirection  = TraceParams->GetTraceDirectionType();

		FVector Dir = FVector::ZeroVector;

		// Owner
		if (TraceDirection == TraceDirectionType::Owner)
		{
			checkf(0, TEXT("NOT IMPLEMENTED"));
		}
		// Bone
		else
		if (TraceDirection == TraceDirectionType::Bone)
		{
			checkf(0, TEXT("NOT IMPLEMENTED"));
		}
		// Component
		else
		if (TraceDirection == TraceDirectionType::Component)
		{
			CS_IS_PENDING_KILL_CHECKED(ComponentDirection)

			const FRotator Rotation = NCsRotationRules::GetRotation(ComponentDirection->GetComponentRotation(), DirectionRules);

			Dir = Rotation.Vector();
		}
		else
		// Camera
		if (TraceDirection == TraceDirectionType::Camera)
		{
			// Try to get camera through the owner
			if (UObject* TheOwner = Weapon->GetWeaponOwner())
			{
				const FRotator Rotation = CsCameraLibrary::GetRotationChecked(Context, TheOwner, DirectionRules);

				Dir = Rotation.Vector();
			}
			// TODO: For now assert
			else
			{
				checkf(0, TEXT("%s: Failed to find Camera / Camera Component from %s."), *Context, *PrintWeaponNameAndClass());
			}
		}

		const float& Distance = TraceParams->GetTraceDistance();

		const FVector End = Start + Distance * Dir;

		// Perform Trace
		CsTraceRequestType* Request = CsTraceManagerLibrary::AllocateRequestChecked(Context, this);
		Request->Start		 = Start;
		Request->End		 = End;

		// Get collision information related to the projectile to be used in the trace.
		ICsGetProjectileType* GetProjectileType  = CS_INTERFACE_CAST_CHECKED(WeaponAsObject, UObject, ICsGetProjectileType);
		CsProjectileDataType* PrjData		     = CsPrjManagerLibrary::GetDataChecked(Context, this, GetProjectileType->GetProjectileType());	
		CsPrjCollisionDataType* PrjCollisionData = CsProjectileDataLibrary::GetInterfaceChecked<CsPrjCollisionDataType>(Context, PrjData);

		const FCsCollisionPreset& CollisionPreset		 = PrjCollisionData->GetCollisionPreset();
		const TEnumAsByte<ECollisionChannel>& ObjectType = CollisionPreset.ObjectType;

		Request->ObjectParams.AddObjectTypesToQuery(ObjectType);

		Request->Type = TraceParams->GetTraceType();

		if (Request->Type == ECsTraceType::Sweep)
		{
			//Request->Shape = 
		}
		
		CsTraceResponseType* Response = CsTraceManagerLibrary::TraceChecked(Context, this, Request);

		FVector LookAtLocation = FVector::ZeroVector;

		if (Response &&
			Response->bResult)
		{
			LookAtLocation = Start + Response->OutHits[CS_FIRST].Distance * Dir;
		}
		else
		{
			LookAtLocation = Start + Distance * Dir;
		}

		const FVector LaunchLocation = GetLaunchLocation(Payload);
		FVector LaunchDirection		 = (LookAtLocation - LaunchLocation).GetSafeNormal();

		const FRotator RotationOffset = NCsRotationRules::GetRotation(DirectionOffset, DirectionRules);

		LaunchDirection = LaunchDirection.RotateAngleAxis(RotationOffset.Pitch, CsMathLibrary::GetRightFromNormal(LaunchDirection));
		LaunchDirection = LaunchDirection.RotateAngleAxis(RotationOffset.Yaw, FVector::UpVector);

		// Check the direction is in FRONT of the Start. The trace could produce a result BEHIND the start

		if (Start == LaunchDirection ||
			FVector::DotProduct(Dir, LaunchDirection) > 0)
		{
			CS_NON_SHIPPING_EXPR(Log_GetLaunchDirection(Params, DirectionScalar * LaunchDirection));
			return LaunchDirection;
		}
		CS_NON_SHIPPING_EXPR(Log_GetLaunchDirection(Params, DirectionScalar * Dir));
		return Dir;
	}
	// Custom
	if (DirType == DirectionType::Custom)
	{		
		const FRotator RotationOffset = NCsRotationRules::GetRotation(DirectionOffset, DirectionRules);
		FVector Direction			  = NCsRotationRules::GetDirection(CustomDirection, DirectionRules);

		Direction = Direction.RotateAngleAxis(RotationOffset.Pitch, CsMathLibrary::GetRightFromNormal(Direction));
		Direction = Direction.RotateAngleAxis(RotationOffset.Yaw, FVector::UpVector);

		Direction = DirectionScalar * GetLaunchSpreadDirection(Direction, Payload);

		CS_NON_SHIPPING_EXPR(Log_GetLaunchDirection(Params, Direction));
		return Direction;
	}
	CS_NON_SHIPPING_EXPR(Log_GetLaunchDirection(Params, FVector::ZeroVector));
	return FVector::ZeroVector;
}

void UCsWeapon_Fire_ProjectileImpl::Launch(const PayloadType& LaunchPayload) 
{
}

#pragma endregion ICsWeapon_Fire_Projectile

// Weapon_Fire_Projectile
#pragma region

void UCsWeapon_Fire_ProjectileImpl::Log_GetLaunchDirection(const ParamsType* LaunchParams, const FVector& Direction)
{
	if (CS_CVAR_LOG_IS_SHOWING(LogWeaponProjectileLaunchDirection))
	{
		UE_LOG(LogCsWp, Warning, TEXT("UCsWeapon_Fire_ProjectileImpl::GetLaunchDirection"));
		UE_LOG(LogCsWp, Warning, TEXT(" Weapon: %s"), *(WeaponAsObject->GetName()));
		UE_LOG(LogCsWp, Warning, TEXT(" Class: %s"), *(WeaponAsObject->GetClass()->GetName()));
		UE_LOG(LogCsWp, Warning, TEXT(" Owner: %s"), Weapon->GetWeaponOwner() ? *(Weapon->GetWeaponOwner()->GetName()) : TEXT("None"));

		const DirectionType& DirType = LaunchParams->GetDirectionType();

		UE_LOG(LogCsWp, Warning, TEXT(" DirectionType: %s"), DirectionMapType::Get().ToChar(DirType));
		UE_LOG(LogCsWp, Warning, TEXT(" Direction: %s"), *(Direction.ToString()));
	}
}

#pragma endregion Weapon_Fire_Projectile

FVector UCsWeapon_Fire_ProjectileImpl::GetLaunchSpreadLocation(const FVector& InLocation, const PayloadType& Payload)
{
	FVector Location = InLocation;

	// If NOT Spread, return Location
	if (!Payload.HasSpread())
		return Location;
	// If NO Offset, return Location
	if (!Payload.Spread.HasOffset())
		return Location;

	static const int32 AXIS_UP				 = 0;
	static const int32 AXIS_LAUNCH_DIRECTION = 1;

	// Up
	if (Payload.Spread.Axis == AXIS_UP)
	{
		Location.X += Payload.Spread.Offset.X;
		Location.Y += Payload.Spread.Offset.Y;
	}
	else
	if (Payload.Spread.Axis == AXIS_LAUNCH_DIRECTION)
	{
		const FVector Direction = GetLaunchDirection();

		Location += Payload.Spread.Offset.X * CsMathLibrary::GetRightFromNormal(Direction);
		//Location += Payload.Spread.Offset.Y * CsMathLibrary::GetUpFromNormal(Direction);
	}	
	return Location;
}

FVector UCsWeapon_Fire_ProjectileImpl::GetLaunchSpreadDirection(const FVector& Direction, const PayloadType& Payload)
{
	return FVector::ZeroVector;
}

// Print
#pragma region

FString UCsWeapon_Fire_ProjectileImpl::PrintWeaponNameAndClass()
{
	return FString::Printf(TEXT("Weapon: %s with Class: %s"), *(WeaponAsObject->GetName()), *(WeaponAsObject->GetClass()->GetName()));
}

FString UCsWeapon_Fire_ProjectileImpl::PrintWeaponNameClassAndOwner()
{
	return FString::Printf(TEXT("Weapon: %s with Class: %s with MyOwner: %s"), *(WeaponAsObject->GetName()), *(WeaponAsObject->GetClass()->GetName()), *(Weapon->GetWeaponOwner()->GetName()));
}

#pragma endregion Print