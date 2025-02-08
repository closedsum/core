// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Kismet/KismetSystemLibrary.h"
// Types
#include "CollisionQueryParams.h"
#include "Engine/HitResult.h"

class UWorld;
class AActor;

namespace NCsDebug
{
	namespace NDraw
	{
		struct CSCORELIBRARY_API FLibrary
		{
			static const float DEBUG_IMPACTPOINT_SIZE;

			/** 
			* Draw a debug line
			*/
			static void DrawDebugLine(const UWorld* InWorld, FVector3f const& LineStart, FVector3f const& LineEnd, FColor const& Color, bool bPersistentLines = false, float LifeTime = -1.f, uint8 DepthPriority = 0, float Thickness = 0.f);
			static void DrawDebugLine(const UWorld* InWorld, FVector const& LineStart, FVector const& LineEnd, FColor const& Color, bool bPersistentLines = false, float LifeTime = -1.f, uint8 DepthPriority = 0, float Thickness = 0.f);

			/** 
			* Draw a debug point
			*/
			static void DrawDebugPoint(const UWorld* InWorld, FVector3f const& Position, float Size, FColor const& PointColor, bool bPersistentLines = false, float LifeTime = -1.f, uint8 DepthPriority = 0);
			static void DrawDebugPoint(const UWorld* InWorld, FVector const& Position, float Size, FColor const& PointColor, bool bPersistentLines = false, float LifeTime = -1.f, uint8 DepthPriority = 0);

			/** 
			* Draw directional arrow 
			*/
			static void DrawDebugDirectionalArrow(const UWorld* InWorld, FVector3f const& LineStart, FVector3f const& LineEnd, float ArrowSize, FColor const& Color, bool bPersistentLines = false, float LifeTime = -1.f, uint8 DepthPriority = 0, float Thickness = 0.f);
			static void DrawDebugDirectionalArrow(const UWorld* InWorld, FVector const& LineStart, FVector const& LineEnd, float ArrowSize, FColor const& Color, bool bPersistentLines = false, float LifeTime = -1.f, uint8 DepthPriority = 0, float Thickness = 0.f);

			/** 
			* Draw a debug box
			*/
			static void DrawDebugBox(const UWorld* InWorld, FVector3f const& Center, FVector3f const& Extent, FColor const& Color, bool bPersistentLines = false, float LifeTime = -1.f, uint8 DepthPriority = 0, float Thickness = 0.f);
			static void DrawDebugBox(const UWorld* InWorld, FVector const& Center, FVector const& Extent, FColor const& Color, bool bPersistentLines = false, float LifeTime = -1.f, uint8 DepthPriority = 0, float Thickness = 0.f);

			/** 
			* Draw a debug box with rotation
			*/
			static void DrawDebugBox(const UWorld* InWorld, FVector3f const& Center, FVector3f const& Extent, const FQuat4f& Rotation, FColor const& Color, bool bPersistentLines = false, float LifeTime = -1.f, uint8 DepthPriority = 0, float Thickness = 0.f);
			static void DrawDebugBox(const UWorld* InWorld, FVector const& Center, FVector const& Extent, const FQuat& Rotation, FColor const& Color, bool bPersistentLines = false, float LifeTime = -1.f, uint8 DepthPriority = 0, float Thickness = 0.f);

			/** 
			* Draw Debug Circle
			*/
			static void DrawDebugCircle(const UWorld* InWorld, const FMatrix44f& TransformMatrix, float Radius, int32 Segments, const FColor& Color, bool bPersistentLines = false, float LifeTime = -1.f, uint8 DepthPriority = 0, float Thickness = 0.f, bool bDrawAxis = true);
			static void DrawDebugCircle(const UWorld* InWorld, const FMatrix& TransformMatrix, float Radius, int32 Segments, const FColor& Color, bool bPersistentLines = false, float LifeTime = -1.f, uint8 DepthPriority = 0, float Thickness = 0.f, bool bDrawAxis = true);

			/** 
			* Draw Debug Circle
			*/
			static void DrawDebugCircle(const UWorld* InWorld, FVector3f Center, float Radius, int32 Segments, const FColor& Color, bool bPersistentLines = false, float LifeTime = -1.f, uint8 DepthPriority = 0, float Thickness = 0.f, FVector3f YAxis = FVector3f(0.f, 1.f, 0.f), FVector3f ZAxis = FVector3f(0.f, 0.f, 1.f), bool bDrawAxis = true);
			static void DrawDebugCircle(const UWorld* InWorld, FVector Center, float Radius, int32 Segments, const FColor& Color, bool bPersistentLines = false, float LifeTime = -1.f, uint8 DepthPriority = 0, float Thickness = 0.f, FVector YAxis = FVector(0.f, 1.f, 0.f), FVector ZAxis = FVector(0.f, 0.f, 1.f), bool bDrawAxis = true);

			/** 
			* Draw a capsule using the LineBatcher 
			*/
			static void DrawDebugCapsule(const UWorld* InWorld, FVector3f const& Center, float HalfHeight, float Radius, const FQuat4f& Rotation, FColor const& Color, bool bPersistentLines = false, float LifeTime = -1.f, uint8 DepthPriority = 0, float Thickness = 0);
			static void DrawDebugCapsule(const UWorld* InWorld, FVector const& Center, float HalfHeight, float Radius, const FQuat& Rotation, FColor const& Color, bool bPersistentLines = false, float LifeTime = -1.f, uint8 DepthPriority = 0, float Thickness = 0);

			/** 
			* Draw Debug 2D donut 
			*/
			static void DrawDebug2DDonut(const UWorld* InWorld, const FMatrix44f& TransformMatrix, float InnerRadius, float OuterRadius, int32 Segments, const FColor& Color, bool bPersistentLines = false, float LifeTime = -1.f, uint8 DepthPriority = 0, float Thickness = 0.f);
			static void DrawDebug2DDonut(const UWorld* InWorld, const FMatrix& TransformMatrix, float InnerRadius, float OuterRadius, int32 Segments, const FColor& Color, bool bPersistentLines = false, float LifeTime = -1.f, uint8 DepthPriority = 0, float Thickness = 0.f);

			/** 
			* Draw a debug sphere
			*/
			static void DrawDebugSphere(const UWorld* InWorld, FVector3f const& Center, float Radius, int32 Segments, FColor const& Color, bool bPersistentLines = false, float LifeTime = -1.f, uint8 DepthPriority = 0, float Thickness = 0.f);
			static void DrawDebugSphere(const UWorld* InWorld, FVector const& Center, float Radius, int32 Segments, FColor const& Color, bool bPersistentLines = false, float LifeTime = -1.f, uint8 DepthPriority = 0, float Thickness = 0.f);

			/** 
			* Draw a debug cone. AngleWidth and AngleHeight are given in radians 
			*/
			static void DrawDebugCone(const UWorld* InWorld, FVector3f const& Origin, FVector3f const& Direction, float Length, float AngleWidth, float AngleHeight, int32 NumSides, FColor const& Color, bool bPersistentLines = false, float LifeTime = -1.f, uint8 DepthPriority = 0, float Thickness = 0.f);
			static void DrawDebugCone(const UWorld* InWorld, FVector const& Origin, FVector const& Direction, float Length, float AngleWidth, float AngleHeight, int32 NumSides, FColor const& Color, bool bPersistentLines = false, float LifeTime = -1.f, uint8 DepthPriority = 0, float Thickness = 0.f);

			static void DrawDebugString(const UWorld* InWorld, FVector3f const& TextLocation, const FString& Text, class AActor* TestBaseActor = NULL, FColor const& TextColor = FColor::White, float Duration = -1.000000, bool bDrawShadow = false, float FontScale = 1.f);
			static void DrawDebugString(const UWorld* InWorld, FVector const& TextLocation, const FString& Text, class AActor* TestBaseActor = NULL, FColor const& TextColor = FColor::White, float Duration = -1.000000, bool bDrawShadow = false, float FontScale = 1.f);

			/** Draw a solid box.  Various API's provided for convenience, including ones that use FBox as well as ones that prefer (Center, Extent). **/

			/** 
			* Draw a Debug box with optional transform.
			*/
			static void DrawDebugSolidBox(const UWorld* InWorld, FBox3f const& Box, FColor const& Color, const FTransform3f& Transform = FTransform3f::Identity, bool bPersistent = false, float LifeTime = -1.f, uint8 DepthPriority = 0);
			static void DrawDebugSolidBox(const UWorld* InWorld, FBox const& Box, FColor const& Color, const FTransform& Transform = FTransform::Identity, bool bPersistent = false, float LifeTime = -1.f, uint8 DepthPriority = 0);

			/** 
			* Draw a Debug box from (Center, Extent) with no rotation (axis-aligned) 
			*/
			static void DrawDebugSolidBox(const UWorld* InWorld, FVector3f const& Center, FVector3f const& Extent, FColor const& Color, bool bPersistent = false, float LifeTime = -1.f, uint8 DepthPriority = 0);
			static void DrawDebugSolidBox(const UWorld* InWorld, FVector const& Center, FVector const& Extent, FColor const& Color, bool bPersistent = false, float LifeTime = -1.f, uint8 DepthPriority = 0);

			/** 
			* Draw a Debug box from (Center, Extent) with specified Rotation 
			*/
			static void DrawDebugSolidBox(const UWorld* InWorld, FVector3f const& Center, FVector3f const& Extent, FQuat4f const& Rotation, FColor const& Color, bool bPersistent = false, float LifeTime = -1.f, uint8 DepthPriority = 0);
			static void DrawDebugSolidBox(const UWorld* InWorld, FVector const& Center, FVector const& Extent, FQuat const& Rotation, FColor const& Color, bool bPersistent = false, float LifeTime = -1.f, uint8 DepthPriority = 0);

			static FCollisionQueryParams ConfigureCollisionParams(FName TraceTag, bool bTraceComplex, const TArray<AActor*>& ActorsToIgnore, bool bIgnoreSelf, UObject* WorldContextObject);

			static FCollisionObjectQueryParams ConfigureCollisionObjectParams(const TArray<TEnumAsByte<EObjectTypeQuery> >& ObjectTypes);

			static void SweptSphere(const UWorld* InWorld, FVector3f const& Start, FVector3f const& End, float Radius, FColor const& Color, bool bPersistentLines = false, float LifeTime = -1.f, uint8 DepthPriority = 0);
			static void SweptSphere(const UWorld* InWorld, FVector const& Start, FVector const& End, float Radius, FColor const& Color, bool bPersistentLines = false, float LifeTime = -1.f, uint8 DepthPriority = 0);
			static void SweptBox(const UWorld* InWorld, FVector3f const& Start, FVector3f const& End, FRotator3f const& Orientation, FVector3f const& HalfSize, FColor const& Color, bool bPersistentLines = false, float LifeTime = -1.f, uint8 DepthPriority = 0);
			static void SweptBox(const UWorld* InWorld, FVector const& Start, FVector const& End, FRotator const& Orientation, FVector const& HalfSize, FColor const& Color, bool bPersistentLines = false, float LifeTime = -1.f, uint8 DepthPriority = 0);

			static void LineTraceSingle(const UWorld* World, const FVector3f& Start, const FVector3f& End, EDrawDebugTrace::Type DrawDebugType, bool bHit, const FHitResult& OutHit, FLinearColor TraceColor, FLinearColor TraceHitColor, float DrawTime);
			static void LineTraceSingle(const UWorld* World, const FVector& Start, const FVector& End, EDrawDebugTrace::Type DrawDebugType, bool bHit, const FHitResult& OutHit, FLinearColor TraceColor, FLinearColor TraceHitColor, float DrawTime);
			static void LineTraceMulti(const UWorld* World, const FVector3f& Start, const FVector3f& End, EDrawDebugTrace::Type DrawDebugType, bool bHit, const TArray<FHitResult>& OutHits, FLinearColor TraceColor, FLinearColor TraceHitColor, float DrawTime);
			static void LineTraceMulti(const UWorld* World, const FVector& Start, const FVector& End, EDrawDebugTrace::Type DrawDebugType, bool bHit, const TArray<FHitResult>& OutHits, FLinearColor TraceColor, FLinearColor TraceHitColor, float DrawTime);

			static void BoxTraceSingle(const UWorld* World, const FVector3f& Start, const FVector3f& End, const FVector3f HalfSize, const FRotator3f Orientation, EDrawDebugTrace::Type DrawDebugType, bool bHit, const FHitResult& OutHit, FLinearColor TraceColor, FLinearColor TraceHitColor, float DrawTime);
			static void BoxTraceSingle(const UWorld* World, const FVector& Start, const FVector& End, const FVector HalfSize, const FRotator Orientation, EDrawDebugTrace::Type DrawDebugType, bool bHit, const FHitResult& OutHit, FLinearColor TraceColor, FLinearColor TraceHitColor, float DrawTime);
			static void BoxTraceMulti(const UWorld* World, const FVector3f& Start, const FVector3f& End, const FVector3f HalfSize, const FRotator3f Orientation, EDrawDebugTrace::Type DrawDebugType, bool bHit, const TArray<FHitResult>& OutHits, FLinearColor TraceColor, FLinearColor TraceHitColor, float DrawTime);
			static void BoxTraceMulti(const UWorld* World, const FVector& Start, const FVector& End, const FVector HalfSize, const FRotator Orientation, EDrawDebugTrace::Type DrawDebugType, bool bHit, const TArray<FHitResult>& OutHits, FLinearColor TraceColor, FLinearColor TraceHitColor, float DrawTime);

			static void SphereTraceSingle(const UWorld* World, const FVector3f& Start, const FVector3f& End, float Radius, EDrawDebugTrace::Type DrawDebugType, bool bHit, const FHitResult& OutHit, FLinearColor TraceColor, FLinearColor TraceHitColor, float DrawTime);
			static void SphereTraceSingle(const UWorld* World, const FVector& Start, const FVector& End, float Radius, EDrawDebugTrace::Type DrawDebugType, bool bHit, const FHitResult& OutHit, FLinearColor TraceColor, FLinearColor TraceHitColor, float DrawTime);
			static void SphereTraceMulti(const UWorld* World, const FVector3f& Start, const FVector3f& End, float Radius, EDrawDebugTrace::Type DrawDebugType, bool bHit, const TArray<FHitResult>& OutHits, FLinearColor TraceColor, FLinearColor TraceHitColor, float DrawTime);
			static void SphereTraceMulti(const UWorld* World, const FVector& Start, const FVector& End, float Radius, EDrawDebugTrace::Type DrawDebugType, bool bHit, const TArray<FHitResult>& OutHits, FLinearColor TraceColor, FLinearColor TraceHitColor, float DrawTime);

			static void CapsuleTraceSingle(const UWorld* World, const FVector3f& Start, const FVector3f& End, float Radius, float HalfHeight, EDrawDebugTrace::Type DrawDebugType, bool bHit, const FHitResult& OutHit, FLinearColor TraceColor, FLinearColor TraceHitColor, float DrawTime);
			static void CapsuleTraceSingle(const UWorld* World, const FVector& Start, const FVector& End, float Radius, float HalfHeight, EDrawDebugTrace::Type DrawDebugType, bool bHit, const FHitResult& OutHit, FLinearColor TraceColor, FLinearColor TraceHitColor, float DrawTime);
			static void CapsuleTraceMulti(const UWorld* World, const FVector3f& Start, const FVector3f& End, float Radius, float HalfHeight, EDrawDebugTrace::Type DrawDebugType, bool bHit, const TArray<FHitResult>& OutHits, FLinearColor TraceColor, FLinearColor TraceHitColor, float DrawTime);
			static void CapsuleTraceMulti(const UWorld* World, const FVector& Start, const FVector& End, float Radius, float HalfHeight, EDrawDebugTrace::Type DrawDebugType, bool bHit, const TArray<FHitResult>& OutHits, FLinearColor TraceColor, FLinearColor TraceHitColor, float DrawTime);

			static void String(const UWorld* InWorld, FVector3f const& TextLocation, const FString& Text, AActor* TestBaseActor = NULL, FColor const& TextColor = FColor::White, float Duration = -1.000000, bool bDrawShadow = false, float FontScale = 1.f);
			static void String(const UWorld* InWorld, FVector const& TextLocation, const FString& Text, AActor* TestBaseActor = NULL, FColor const& TextColor = FColor::White, float Duration = -1.000000, bool bDrawShadow = false, float FontScale = 1.f);
		};
	}
}

using CsDebugDrawLibrary = NCsDebug::NDraw::FLibrary;