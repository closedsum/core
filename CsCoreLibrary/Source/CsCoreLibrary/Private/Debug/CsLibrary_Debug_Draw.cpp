// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Debug/CsLibrary_Debug_Draw.h"

// Library
#include "Library/CsLibrary_Math.h"
// Player
#include "GameFramework/PlayerController.h"
// Settings
#include "PhysicsEngine/PhysicsSettings.h"
// UI
#include "GameFramework/HUD.h"
// Debug
#include "DrawDebugHelpers.h"

const float NCsDebug::NDraw::FLibrary::DEBUG_IMPACTPOINT_SIZE = 16.f;

namespace NCsDebug
{
	namespace NDraw
	{
		void FLibrary::DrawDebugLine(const UWorld* InWorld, FVector3f const& LineStart, FVector3f const& LineEnd, FColor const& Color, bool bPersistentLines /*=false*/, float LifeTime /*=-1.f*/, uint8 DepthPriority /*=0*/, float Thickness /*=0.f*/)
		{
			::DrawDebugLine(InWorld, CsMathLibrary::Convert(LineStart), CsMathLibrary::Convert(LineEnd), Color, bPersistentLines, LifeTime, DepthPriority, Thickness);
		}

		void FLibrary::DrawDebugLine(const UWorld* InWorld, FVector const& LineStart, FVector const& LineEnd, FColor const& Color, bool bPersistentLines /*=false*/, float LifeTime /*=-1.f*/, uint8 DepthPriority /*=0*/, float Thickness /*=0.f*/)
		{
			::DrawDebugLine(InWorld, LineStart, LineEnd, Color, bPersistentLines, LifeTime, DepthPriority, Thickness);
		}

		void FLibrary::DrawDebugPoint(const UWorld* InWorld, FVector3f const& Position, float Size, FColor const& PointColor, bool bPersistentLines /*=false*/, float LifeTime /*=-1.f*/, uint8 DepthPriority /*=0*/)
		{
			::DrawDebugPoint(InWorld, CsMathLibrary::Convert(Position), Size, PointColor, bPersistentLines, LifeTime, DepthPriority);
		}

		void FLibrary::DrawDebugPoint(const UWorld* InWorld, FVector const& Position, float Size, FColor const& PointColor, bool bPersistentLines /*=false*/, float LifeTime /*=-1.f*/, uint8 DepthPriority /*=0*/)
		{
			::DrawDebugPoint(InWorld, Position, Size, PointColor, bPersistentLines, LifeTime, DepthPriority);
		}

		void FLibrary::DrawDebugDirectionalArrow(const UWorld* InWorld, FVector3f const& LineStart, FVector3f const& LineEnd, float ArrowSize, FColor const& Color, bool bPersistentLines /*=false*/, float LifeTime /*=-1.f*/, uint8 DepthPriority /*=0*/, float Thickness /*=0.f*/)
		{
			::DrawDebugDirectionalArrow(InWorld, CsMathLibrary::Convert(LineStart), CsMathLibrary::Convert(LineEnd), ArrowSize, Color, bPersistentLines, LifeTime,DepthPriority, Thickness);
		}

		void FLibrary::DrawDebugDirectionalArrow(const UWorld* InWorld, FVector const& LineStart, FVector const& LineEnd, float ArrowSize, FColor const& Color, bool bPersistentLines /*=false*/, float LifeTime /*=-1.f*/, uint8 DepthPriority /*=0*/, float Thickness /*=0.f*/)
		{
			::DrawDebugDirectionalArrow(InWorld, LineStart, LineEnd, ArrowSize, Color, bPersistentLines, LifeTime,DepthPriority, Thickness);
		}

		void FLibrary::DrawDebugBox(const UWorld* InWorld, FVector3f const& Center, FVector3f const& Extent, FColor const& Color, bool bPersistentLines /*=false*/, float LifeTime /*=-1.f*/, uint8 DepthPriority /*=0*/, float Thickness /*=0.f*/)
		{
			::DrawDebugBox(InWorld, CsMathLibrary::Convert(Center), CsMathLibrary::Convert(Extent), Color, bPersistentLines, LifeTime, DepthPriority, Thickness);
		}

		void FLibrary::DrawDebugBox(const UWorld* InWorld, FVector const& Center, FVector const& Extent, FColor const& Color, bool bPersistentLines /*=false*/, float LifeTime /*=-1.f*/, uint8 DepthPriority /*=0*/, float Thickness /*=0.f*/)
		{
			::DrawDebugBox(InWorld, Center, Extent, Color, bPersistentLines, LifeTime, DepthPriority, Thickness);
		}

		void FLibrary::DrawDebugBox(const UWorld* InWorld, FVector3f const& Center, FVector3f const& Extent, const FQuat4f& Rotation, FColor const& Color, bool bPersistentLines /*=false*/, float LifeTime /*=-1.f*/, uint8 DepthPriority /*=0*/, float Thickness /*=0.f*/)
		{
			::DrawDebugBox(InWorld, CsMathLibrary::Convert(Center), CsMathLibrary::Convert(Extent), CsMathLibrary::Convert(Rotation), Color, bPersistentLines, LifeTime, DepthPriority, Thickness);
		}

		void FLibrary::DrawDebugBox(const UWorld* InWorld, FVector const& Center, FVector const& Extent, const FQuat& Rotation, FColor const& Color, bool bPersistentLines /*=false*/, float LifeTime /*=-1.f*/, uint8 DepthPriority /*=0*/, float Thickness /*=0.f*/)
		{
			::DrawDebugBox(InWorld, Center, Extent, Rotation, Color, bPersistentLines, LifeTime, DepthPriority, Thickness);
		}

		void FLibrary::DrawDebugCircle(const UWorld* InWorld, const FMatrix44f& TransformMatrix, float Radius, int32 Segments, const FColor& Color, bool bPersistentLines /*=false*/, float LifeTime /*=-1.f*/, uint8 DepthPriority /*=0*/, float Thickness /*=0.f*/, bool bDrawAxis /*=true*/)
		{
			::DrawDebugCircle(InWorld, CsMathLibrary::Convert(TransformMatrix), Radius, Segments, Color, bPersistentLines, LifeTime, DepthPriority, Thickness, bDrawAxis);
		}

		void FLibrary::DrawDebugCircle(const UWorld* InWorld, const FMatrix& TransformMatrix, float Radius, int32 Segments, const FColor& Color, bool bPersistentLines /*=false*/, float LifeTime /*=-1.f*/, uint8 DepthPriority /*=0*/, float Thickness /*=0.f*/, bool bDrawAxis /*=true*/)
		{
			::DrawDebugCircle(InWorld, TransformMatrix, Radius, Segments, Color, bPersistentLines, LifeTime, DepthPriority, Thickness, bDrawAxis);
		}

		void FLibrary::DrawDebugCircle(const UWorld* InWorld, FVector3f Center, float Radius, int32 Segments, const FColor& Color, bool bPersistentLines /*=false*/, float LifeTime /*=-1.f*/, uint8 DepthPriority /*=0*/, float Thickness /*=0.f*/, FVector3f YAxis /*=FVector3f(0.f, 1.f, 0.f)*/, FVector3f ZAxis /*=FVector3f(0.f, 0.f, 1.f)*/, bool bDrawAxis /*=true*/)
		{
			::DrawDebugCircle(InWorld, CsMathLibrary::Convert(Center), Radius, Segments, Color, bPersistentLines, LifeTime, DepthPriority, Thickness, CsMathLibrary::Convert(YAxis), CsMathLibrary::Convert(ZAxis), bDrawAxis);
		}

		void FLibrary::DrawDebugCircle(const UWorld* InWorld, FVector Center, float Radius, int32 Segments, const FColor& Color, bool bPersistentLines /*=false*/, float LifeTime /*=-1.f*/, uint8 DepthPriority /*=0*/, float Thickness /*=0.f*/, FVector YAxis /*=FVector(0.f, 1.f, 0.f)*/, FVector ZAxis /*=FVector(0.f, 0.f, 1.f)*/, bool bDrawAxis /*=true*/)
		{
			::DrawDebugCircle(InWorld, Center, Radius, Segments, Color, bPersistentLines, LifeTime, DepthPriority, Thickness, YAxis, ZAxis, bDrawAxis);
		}

		void FLibrary::DrawDebugCapsule(const UWorld* InWorld, FVector3f const& Center, float HalfHeight, float Radius, const FQuat4f& Rotation, FColor const& Color, bool bPersistentLines /*=false*/, float LifeTime /*=-1.f*/, uint8 DepthPriority /*=0*/, float Thickness /*=0*/)
		{
			::DrawDebugCapsule(InWorld, CsMathLibrary::Convert(Center), HalfHeight, Radius, CsMathLibrary::Convert(Rotation), Color, bPersistentLines, LifeTime, DepthPriority, Thickness);
		}

		void FLibrary::DrawDebugCapsule(const UWorld* InWorld, FVector const& Center, float HalfHeight, float Radius, const FQuat& Rotation, FColor const& Color, bool bPersistentLines /*=false*/, float LifeTime /*=-1.f*/, uint8 DepthPriority /*=0*/, float Thickness /*=0*/)
		{
			::DrawDebugCapsule(InWorld, Center, HalfHeight, Radius, Rotation, Color, bPersistentLines, LifeTime, DepthPriority, Thickness);
		}

		void FLibrary::DrawDebug2DDonut(const UWorld* InWorld, const FMatrix44f& TransformMatrix, float InnerRadius, float OuterRadius, int32 Segments, const FColor& Color, bool bPersistentLines /*=false*/, float LifeTime /*=-1.f*/, uint8 DepthPriority /*=0*/, float Thickness /*=0.f*/)
		{
			::DrawDebug2DDonut(InWorld, CsMathLibrary::Convert(TransformMatrix), InnerRadius, OuterRadius, Segments, Color, bPersistentLines, LifeTime, DepthPriority, Thickness);
		}

		void FLibrary::DrawDebug2DDonut(const UWorld* InWorld, const FMatrix& TransformMatrix, float InnerRadius, float OuterRadius, int32 Segments, const FColor& Color, bool bPersistentLines /*=false*/, float LifeTime /*=-1.f*/, uint8 DepthPriority /*=0*/, float Thickness /*=0.f*/)
		{
			::DrawDebug2DDonut(InWorld, TransformMatrix, InnerRadius, OuterRadius, Segments, Color, bPersistentLines, LifeTime, DepthPriority, Thickness);
		}

		void FLibrary::DrawDebugSphere(const UWorld* InWorld, FVector3f const& Center, float Radius, int32 Segments, FColor const& Color, bool bPersistentLines /*=false*/, float LifeTime /*=-1.f*/, uint8 DepthPriority /*=0*/, float Thickness /*=0.f*/)
		{
			::DrawDebugSphere(InWorld, CsMathLibrary::Convert(Center), Radius, Segments, Color, bPersistentLines, LifeTime, DepthPriority, Thickness);
		}

		void FLibrary::DrawDebugSphere(const UWorld* InWorld, FVector const& Center, float Radius, int32 Segments, FColor const& Color, bool bPersistentLines /*=false*/, float LifeTime /*=-1.f*/, uint8 DepthPriority /*=0*/, float Thickness /*=0.f*/)
		{
			::DrawDebugSphere(InWorld, Center, Radius, Segments, Color, bPersistentLines, LifeTime, DepthPriority, Thickness);
		}

		void FLibrary::DrawDebugCone(const UWorld* InWorld, FVector3f const& Origin, FVector3f const& Direction, float Length, float AngleWidth, float AngleHeight, int32 NumSides, FColor const& Color, bool bPersistentLines /*=false*/, float LifeTime /*=-1.f*/, uint8 DepthPriority /*=0*/, float Thickness /*=0.f*/)
		{
			::DrawDebugCone(InWorld, CsMathLibrary::Convert(Origin), CsMathLibrary::Convert(Direction), Length, AngleWidth, AngleHeight, NumSides, Color, bPersistentLines, LifeTime, DepthPriority, Thickness);
		}

		void FLibrary::DrawDebugCone(const UWorld* InWorld, FVector const& Origin, FVector const& Direction, float Length, float AngleWidth, float AngleHeight, int32 NumSides, FColor const& Color, bool bPersistentLines /*=false*/, float LifeTime /*=-1.f*/, uint8 DepthPriority /*=0*/, float Thickness /*=0.f*/)
		{
			::DrawDebugCone(InWorld, Origin, Direction, Length, AngleWidth, AngleHeight, NumSides, Color, bPersistentLines, LifeTime, DepthPriority, Thickness);
		}

		void FLibrary::DrawDebugString(const UWorld* InWorld, FVector3f const& TextLocation, const FString& Text, class AActor* TestBaseActor /*=NULL*/, FColor const& TextColor /*=FColor::White*/, float Duration /*=-1.000000*/, bool bDrawShadow /*=false*/, float FontScale /*=1.f*/)
		{
			::DrawDebugString(InWorld, CsMathLibrary::Convert(TextLocation), Text, TestBaseActor, TextColor, Duration, bDrawShadow, FontScale);
		}

		void FLibrary::DrawDebugString(const UWorld* InWorld, FVector const& TextLocation, const FString& Text, class AActor* TestBaseActor /*=NULL*/, FColor const& TextColor /*=FColor::White*/, float Duration /*=-1.000000*/, bool bDrawShadow /*=false*/, float FontScale /*=1.f*/)
		{
			::DrawDebugString(InWorld, TextLocation, Text, TestBaseActor, TextColor, Duration, bDrawShadow, FontScale);
		}

		void FLibrary::DrawDebugSolidBox(const UWorld* InWorld, FBox3f const& Box, FColor const& Color, const FTransform3f& Transform /*=FTransform3f::Identity*/, bool bPersistent /*=false*/, float LifeTime /*=-1.f*/, uint8 DepthPriority /*=0*/)
		{
			::DrawDebugSolidBox(InWorld, CsMathLibrary::Convert(Box), Color, CsMathLibrary::Convert(Transform), bPersistent, LifeTime, DepthPriority);
		}

		void FLibrary::DrawDebugSolidBox(const UWorld* InWorld, FBox const& Box, FColor const& Color, const FTransform& Transform /*=FTransform::Identity*/, bool bPersistent /*=false*/, float LifeTime /*=-1.f*/, uint8 DepthPriority /*=0*/)
		{
			::DrawDebugSolidBox(InWorld, Box, Color, Transform, bPersistent, LifeTime, DepthPriority);
		}

		void FLibrary::DrawDebugSolidBox(const UWorld* InWorld, FVector3f const& Center, FVector3f const& Extent, FColor const& Color, bool bPersistent /*=false*/, float LifeTime /*=-1.f*/, uint8 DepthPriority /*=0*/)
		{
			::DrawDebugSolidBox(InWorld, CsMathLibrary::Convert(Center), CsMathLibrary::Convert(Extent), Color, bPersistent, LifeTime, DepthPriority);
		}
		
		void FLibrary::DrawDebugSolidBox(const UWorld* InWorld, FVector const& Center, FVector const& Extent, FColor const& Color, bool bPersistent /*=false*/, float LifeTime /*=-1.f*/, uint8 DepthPriority /*=0*/)
		{
			::DrawDebugSolidBox(InWorld, Center, Extent, Color, bPersistent, LifeTime, DepthPriority);
		}

		void FLibrary::DrawDebugSolidBox(const UWorld* InWorld, FVector3f const& Center, FVector3f const& Extent, FQuat4f const& Rotation, FColor const& Color, bool bPersistent /*=false*/, float LifeTime /*=-1.f*/, uint8 DepthPriority /*=0*/)
		{
			::DrawDebugSolidBox(InWorld, CsMathLibrary::Convert(Center), CsMathLibrary::Convert(Extent), CsMathLibrary::Convert(Rotation), Color, bPersistent, LifeTime, DepthPriority);
		}

		void FLibrary::DrawDebugSolidBox(const UWorld* InWorld, FVector const& Center, FVector const& Extent, FQuat const& Rotation, FColor const& Color, bool bPersistent /*=false*/, float LifeTime /*=-1.f*/, uint8 DepthPriority /*=0*/)
		{
			::DrawDebugSolidBox(InWorld, Center, Extent, Rotation, Color, bPersistent, LifeTime, DepthPriority);
		}

		FCollisionQueryParams FLibrary::ConfigureCollisionParams(FName TraceTag, bool bTraceComplex, const TArray<AActor*>& ActorsToIgnore, bool bIgnoreSelf, UObject* WorldContextObject)
		{
			FCollisionQueryParams Params(TraceTag, SCENE_QUERY_STAT_ONLY(KismetTraceUtils), bTraceComplex);
			Params.bReturnPhysicalMaterial = true;
			Params.bReturnFaceIndex = !UPhysicsSettings::Get()->bSuppressFaceRemapTable; // Ask for face index, as long as we didn't disable globally
			Params.AddIgnoredActors(ActorsToIgnore);
			if (bIgnoreSelf)
			{
				AActor* IgnoreActor = Cast<AActor>(WorldContextObject);
				if (IgnoreActor)
				{
					Params.AddIgnoredActor(IgnoreActor);
				}
				else
				{
					// find owner
					UObject* CurrentObject = WorldContextObject;
					while (CurrentObject)
					{
						CurrentObject = CurrentObject->GetOuter();
						IgnoreActor = Cast<AActor>(CurrentObject);
						if (IgnoreActor)
						{
							Params.AddIgnoredActor(IgnoreActor);
							break;
						}
					}
				}
			}

			return Params;
		}

		FCollisionObjectQueryParams FLibrary::ConfigureCollisionObjectParams(const TArray<TEnumAsByte<EObjectTypeQuery> > & ObjectTypes)
		{
			TArray<TEnumAsByte<ECollisionChannel>> CollisionObjectTraces;
			CollisionObjectTraces.AddUninitialized(ObjectTypes.Num());

			for (auto Iter = ObjectTypes.CreateConstIterator(); Iter; ++Iter)
			{
				CollisionObjectTraces[Iter.GetIndex()] = UEngineTypes::ConvertToCollisionChannel(*Iter);
			}

			FCollisionObjectQueryParams ObjectParams;
			for (auto Iter = CollisionObjectTraces.CreateConstIterator(); Iter; ++Iter)
			{
				const ECollisionChannel & Channel = (*Iter);
				if (FCollisionObjectQueryParams::IsValidObjectQuery(Channel))
				{
					ObjectParams.AddObjectTypesToQuery(Channel);
				}
				else
				{
					UE_LOG(LogBlueprintUserMessages, Warning, TEXT("%d isn't valid object type"), (int32)Channel);
				}
			}

			return ObjectParams;
		}

		void FLibrary::SweptSphere(const UWorld* InWorld, FVector3f const& Start, FVector3f const& End, float Radius, FColor const& Color, bool bPersistentLines, float LifeTime, uint8 DepthPriority)
		{
			FVector3f const TraceVec = End - Start;
			float const Dist		 = TraceVec.Size();

			FVector3f const Center = Start + TraceVec * 0.5f;
			float const HalfHeight = (Dist * 0.5f) + Radius;

			FQuat4f const CapsuleRot = FRotationMatrix44f::MakeFromZ(TraceVec).ToQuat();
			DrawDebugCapsule(InWorld, Center, HalfHeight, Radius, CapsuleRot, Color, bPersistentLines, LifeTime, DepthPriority);
		}

		void FLibrary::SweptSphere(const UWorld* InWorld, FVector const& Start, FVector const& End, float Radius, FColor const& Color, bool bPersistentLines, float LifeTime, uint8 DepthPriority)
		{
			FVector const TraceVec = End - Start;
			float const Dist	   = TraceVec.Size();

			FVector const Center   = Start + TraceVec * 0.5f;
			float const HalfHeight = (Dist * 0.5f) + Radius;

			FQuat const CapsuleRot = FRotationMatrix::MakeFromZ(TraceVec).ToQuat();
			DrawDebugCapsule(InWorld, Center, HalfHeight, Radius, CapsuleRot, Color, bPersistentLines, LifeTime, DepthPriority);
		}

		void FLibrary::SweptBox(const UWorld* InWorld, FVector3f const& Start, FVector3f const& End, FRotator3f const & Orientation, FVector3f const & HalfSize, FColor const& Color, bool bPersistentLines, float LifeTime, uint8 DepthPriority)
		{
			FVector3f const TraceVec = End - Start;
			float const Dist		 = TraceVec.Size();

			FVector3f const Center = Start + TraceVec * 0.5f;

			FQuat4f const CapsuleRot = Orientation.Quaternion();
			DrawDebugBox(InWorld, Start, HalfSize, CapsuleRot, Color, bPersistentLines, LifeTime, DepthPriority);

			//now draw lines from vertices
			FVector3f Vertices[8];
			Vertices[0] = Start + CapsuleRot.RotateVector(FVector3f(-HalfSize.X, -HalfSize.Y, -HalfSize.Z));	//flt
			Vertices[1] = Start + CapsuleRot.RotateVector(FVector3f(-HalfSize.X, HalfSize.Y, -HalfSize.Z));	//frt
			Vertices[2] = Start + CapsuleRot.RotateVector(FVector3f(-HalfSize.X, -HalfSize.Y, HalfSize.Z));	//flb
			Vertices[3] = Start + CapsuleRot.RotateVector(FVector3f(-HalfSize.X, HalfSize.Y, HalfSize.Z));	//frb
			Vertices[4] = Start + CapsuleRot.RotateVector(FVector3f(HalfSize.X, -HalfSize.Y, -HalfSize.Z));	//blt
			Vertices[5] = Start + CapsuleRot.RotateVector(FVector3f(HalfSize.X, HalfSize.Y, -HalfSize.Z));	//brt
			Vertices[6] = Start + CapsuleRot.RotateVector(FVector3f(HalfSize.X, -HalfSize.Y, HalfSize.Z));	//blb
			Vertices[7] = Start + CapsuleRot.RotateVector(FVector3f(HalfSize.X, HalfSize.Y, HalfSize.Z));		//brb
			for (int32 VertexIdx = 0; VertexIdx < 8; ++VertexIdx)
			{
				DrawDebugLine(InWorld, Vertices[VertexIdx], Vertices[VertexIdx] + TraceVec, Color, bPersistentLines, LifeTime, DepthPriority);
			}

			DrawDebugBox(InWorld, End, HalfSize, CapsuleRot, Color, bPersistentLines, LifeTime, DepthPriority);
		}

		void FLibrary::SweptBox(const UWorld* InWorld, FVector const& Start, FVector const& End, FRotator const & Orientation, FVector const & HalfSize, FColor const& Color, bool bPersistentLines, float LifeTime, uint8 DepthPriority)
		{
			FVector const TraceVec = End - Start;
			float const Dist	   = TraceVec.Size();

			FVector const Center = Start + TraceVec * 0.5f;

			FQuat const CapsuleRot = Orientation.Quaternion();
			DrawDebugBox(InWorld, Start, HalfSize, CapsuleRot, Color, bPersistentLines, LifeTime, DepthPriority);

			//now draw lines from vertices
			FVector Vertices[8];
			Vertices[0] = Start + CapsuleRot.RotateVector(FVector(-HalfSize.X, -HalfSize.Y, -HalfSize.Z));	//flt
			Vertices[1] = Start + CapsuleRot.RotateVector(FVector(-HalfSize.X, HalfSize.Y, -HalfSize.Z));	//frt
			Vertices[2] = Start + CapsuleRot.RotateVector(FVector(-HalfSize.X, -HalfSize.Y, HalfSize.Z));	//flb
			Vertices[3] = Start + CapsuleRot.RotateVector(FVector(-HalfSize.X, HalfSize.Y, HalfSize.Z));	//frb
			Vertices[4] = Start + CapsuleRot.RotateVector(FVector(HalfSize.X, -HalfSize.Y, -HalfSize.Z));	//blt
			Vertices[5] = Start + CapsuleRot.RotateVector(FVector(HalfSize.X, HalfSize.Y, -HalfSize.Z));	//brt
			Vertices[6] = Start + CapsuleRot.RotateVector(FVector(HalfSize.X, -HalfSize.Y, HalfSize.Z));	//blb
			Vertices[7] = Start + CapsuleRot.RotateVector(FVector(HalfSize.X, HalfSize.Y, HalfSize.Z));		//brb
			for (int32 VertexIdx = 0; VertexIdx < 8; ++VertexIdx)
			{
				DrawDebugLine(InWorld, Vertices[VertexIdx], Vertices[VertexIdx] + TraceVec, Color, bPersistentLines, LifeTime, DepthPriority);
			}

			DrawDebugBox(InWorld, End, HalfSize, CapsuleRot, Color, bPersistentLines, LifeTime, DepthPriority);
		}

		/** Util for drawing result of single line trace  */
		void FLibrary::LineTraceSingle(const UWorld* World, const FVector3f& Start, const FVector3f& End, EDrawDebugTrace::Type DrawDebugType, bool bHit, const FHitResult& OutHit, FLinearColor TraceColor, FLinearColor TraceHitColor, float DrawTime)
		{
			if (DrawDebugType != EDrawDebugTrace::None)
			{
				bool bPersistent = DrawDebugType == EDrawDebugTrace::Persistent;
				float LifeTime   = (DrawDebugType == EDrawDebugTrace::ForDuration) ? DrawTime : 0.f;

				// @fixme, draw line with thickness = 2.f?
				if (bHit && OutHit.bBlockingHit)
				{
					// Red up to the blocking hit, green thereafter
					DrawDebugLine(World, Start, CsMathLibrary::Convert(OutHit.ImpactPoint), TraceColor.ToFColor(true), bPersistent, LifeTime);
					DrawDebugLine(World, CsMathLibrary::Convert(OutHit.ImpactPoint), End, TraceHitColor.ToFColor(true), bPersistent, LifeTime);
					DrawDebugPoint(World, CsMathLibrary::Convert(OutHit.ImpactPoint), DEBUG_IMPACTPOINT_SIZE, TraceColor.ToFColor(true), bPersistent, LifeTime);
				}
				else
				{
					// no hit means all red
					DrawDebugLine(World, Start, End, TraceColor.ToFColor(true), bPersistent, LifeTime);
				}
			}
		}

		void FLibrary::LineTraceSingle(const UWorld* World, const FVector& Start, const FVector& End, EDrawDebugTrace::Type DrawDebugType, bool bHit, const FHitResult& OutHit, FLinearColor TraceColor, FLinearColor TraceHitColor, float DrawTime)
		{
			if (DrawDebugType != EDrawDebugTrace::None)
			{
				bool bPersistent = DrawDebugType == EDrawDebugTrace::Persistent;
				float LifeTime   = (DrawDebugType == EDrawDebugTrace::ForDuration) ? DrawTime : 0.f;

				// @fixme, draw line with thickness = 2.f?
				if (bHit && OutHit.bBlockingHit)
				{
					// Red up to the blocking hit, green thereafter
					DrawDebugLine(World, Start, OutHit.ImpactPoint, TraceColor.ToFColor(true), bPersistent, LifeTime);
					DrawDebugLine(World, OutHit.ImpactPoint, End, TraceHitColor.ToFColor(true), bPersistent, LifeTime);
					DrawDebugPoint(World, OutHit.ImpactPoint, DEBUG_IMPACTPOINT_SIZE, TraceColor.ToFColor(true), bPersistent, LifeTime);
				}
				else
				{
					// no hit means all red
					DrawDebugLine(World, Start, End, TraceColor.ToFColor(true), bPersistent, LifeTime);
				}
			}
		}

		/** Util for drawing result of multi line trace  */
		void FLibrary::LineTraceMulti(const UWorld* World, const FVector3f& Start, const FVector3f& End, EDrawDebugTrace::Type DrawDebugType, bool bHit, const TArray<FHitResult>& OutHits, FLinearColor TraceColor, FLinearColor TraceHitColor, float DrawTime)
		{
			if (DrawDebugType != EDrawDebugTrace::None)
			{
				bool bPersistent = DrawDebugType == EDrawDebugTrace::Persistent;
				float LifeTime   = (DrawDebugType == EDrawDebugTrace::ForDuration) ? DrawTime : 0.f;

				// @fixme, draw line with thickness = 2.f?
				if (bHit && OutHits.Last().bBlockingHit)
				{
					// Red up to the blocking hit, green thereafter
					FVector3f const BlockingHitPoint = CsMathLibrary::Convert(OutHits.Last().ImpactPoint);
					DrawDebugLine(World, Start, BlockingHitPoint, TraceColor.ToFColor(true), bPersistent, LifeTime);
					DrawDebugLine(World, BlockingHitPoint, End, TraceHitColor.ToFColor(true), bPersistent, LifeTime);
				}
				else
				{
					// no hit means all red
					DrawDebugLine(World, Start, End, TraceColor.ToFColor(true), bPersistent, LifeTime);
				}

				// draw hits
				for (int32 HitIdx = 0; HitIdx < OutHits.Num(); ++HitIdx)
				{
					FHitResult const& Hit = OutHits[HitIdx];
					DrawDebugPoint(World, CsMathLibrary::Convert(Hit.ImpactPoint), DEBUG_IMPACTPOINT_SIZE, (Hit.bBlockingHit ? TraceColor.ToFColor(true) : TraceHitColor.ToFColor(true)), bPersistent, LifeTime);
				}
			}
		}

		void FLibrary::LineTraceMulti(const UWorld* World, const FVector& Start, const FVector& End, EDrawDebugTrace::Type DrawDebugType, bool bHit, const TArray<FHitResult>& OutHits, FLinearColor TraceColor, FLinearColor TraceHitColor, float DrawTime)
		{
			if (DrawDebugType != EDrawDebugTrace::None)
			{
				bool bPersistent = DrawDebugType == EDrawDebugTrace::Persistent;
				float LifeTime   = (DrawDebugType == EDrawDebugTrace::ForDuration) ? DrawTime : 0.f;

				// @fixme, draw line with thickness = 2.f?
				if (bHit && OutHits.Last().bBlockingHit)
				{
					// Red up to the blocking hit, green thereafter
					FVector const BlockingHitPoint = OutHits.Last().ImpactPoint;
					DrawDebugLine(World, Start, BlockingHitPoint, TraceColor.ToFColor(true), bPersistent, LifeTime);
					DrawDebugLine(World, BlockingHitPoint, End, TraceHitColor.ToFColor(true), bPersistent, LifeTime);
				}
				else
				{
					// no hit means all red
					DrawDebugLine(World, Start, End, TraceColor.ToFColor(true), bPersistent, LifeTime);
				}

				// draw hits
				for (int32 HitIdx = 0; HitIdx < OutHits.Num(); ++HitIdx)
				{
					FHitResult const& Hit = OutHits[HitIdx];
					DrawDebugPoint(World, Hit.ImpactPoint, DEBUG_IMPACTPOINT_SIZE, (Hit.bBlockingHit ? TraceColor.ToFColor(true) : TraceHitColor.ToFColor(true)), bPersistent, LifeTime);
				}
			}
		}

		void FLibrary::BoxTraceSingle(const UWorld* World, const FVector3f& Start, const FVector3f& End, const FVector3f HalfSize, const FRotator3f Orientation, EDrawDebugTrace::Type DrawDebugType, bool bHit, const FHitResult& OutHit, FLinearColor TraceColor, FLinearColor TraceHitColor, float DrawTime)
		{
			if (DrawDebugType != EDrawDebugTrace::None && (World != nullptr))
			{
				bool bPersistent = DrawDebugType == EDrawDebugTrace::Persistent;
				float LifeTime = (DrawDebugType == EDrawDebugTrace::ForDuration) ? DrawTime : 0.f;

				if (bHit && OutHit.bBlockingHit)
				{
					// Red up to the blocking hit, green thereafter
					SweptBox(World, Start, CsMathLibrary::Convert(OutHit.Location), Orientation, HalfSize, TraceColor.ToFColor(true), bPersistent, LifeTime);
					SweptBox(World, CsMathLibrary::Convert(OutHit.Location), End, Orientation, HalfSize, TraceHitColor.ToFColor(true), bPersistent, LifeTime);
					DrawDebugPoint(World, CsMathLibrary::Convert(OutHit.ImpactPoint), DEBUG_IMPACTPOINT_SIZE, TraceColor.ToFColor(true), bPersistent, LifeTime);
				}
				else
				{
					// no hit means all red
					SweptBox(World, Start, End, Orientation, HalfSize, TraceColor.ToFColor(true), bPersistent, LifeTime);
				}
			}
		}

		void FLibrary::BoxTraceSingle(const UWorld* World, const FVector& Start, const FVector& End, const FVector HalfSize, const FRotator Orientation, EDrawDebugTrace::Type DrawDebugType, bool bHit, const FHitResult& OutHit, FLinearColor TraceColor, FLinearColor TraceHitColor, float DrawTime)
		{
			if (DrawDebugType != EDrawDebugTrace::None && (World != nullptr))
			{
				bool bPersistent = DrawDebugType == EDrawDebugTrace::Persistent;
				float LifeTime = (DrawDebugType == EDrawDebugTrace::ForDuration) ? DrawTime : 0.f;

				if (bHit && OutHit.bBlockingHit)
				{
					// Red up to the blocking hit, green thereafter
					SweptBox(World, Start, OutHit.Location, Orientation, HalfSize, TraceColor.ToFColor(true), bPersistent, LifeTime);
					SweptBox(World, OutHit.Location, End, Orientation, HalfSize, TraceHitColor.ToFColor(true), bPersistent, LifeTime);
					DrawDebugPoint(World, OutHit.ImpactPoint, DEBUG_IMPACTPOINT_SIZE, TraceColor.ToFColor(true), bPersistent, LifeTime);
				}
				else
				{
					// no hit means all red
					SweptBox(World, Start, End, Orientation, HalfSize, TraceColor.ToFColor(true), bPersistent, LifeTime);
				}
			}
		}

		void FLibrary::BoxTraceMulti(const UWorld* World, const FVector3f& Start, const FVector3f& End, const FVector3f HalfSize, const FRotator3f Orientation, EDrawDebugTrace::Type DrawDebugType, bool bHit, const TArray<FHitResult>& OutHits, FLinearColor TraceColor, FLinearColor TraceHitColor, float DrawTime)
		{
			if (DrawDebugType != EDrawDebugTrace::None && (World != nullptr))
			{
				bool bPersistent = DrawDebugType == EDrawDebugTrace::Persistent;
				float LifeTime = (DrawDebugType == EDrawDebugTrace::ForDuration) ? DrawTime : 0.f;

				if (bHit && OutHits.Last().bBlockingHit)
				{
					// Red up to the blocking hit, green thereafter
					FVector3f const BlockingHitPoint = CsMathLibrary::Convert(OutHits.Last().Location);
					SweptBox(World, Start, BlockingHitPoint, Orientation, HalfSize, TraceColor.ToFColor(true), bPersistent, LifeTime);
					SweptBox(World, BlockingHitPoint, End, Orientation, HalfSize, TraceHitColor.ToFColor(true), bPersistent, LifeTime);
				}
				else
				{
					// no hit means all red
					SweptBox(World, Start, End, Orientation, HalfSize, TraceColor.ToFColor(true), bPersistent, LifeTime);
				}

				// draw hits
				for (int32 HitIdx = 0; HitIdx < OutHits.Num(); ++HitIdx)
				{
					FHitResult const& Hit = OutHits[HitIdx];
					DrawDebugPoint(World, CsMathLibrary::Convert(Hit.ImpactPoint), DEBUG_IMPACTPOINT_SIZE, (Hit.bBlockingHit ? TraceColor.ToFColor(true) : TraceHitColor.ToFColor(true)), bPersistent, LifeTime);
				}
			}
		}

		void FLibrary::BoxTraceMulti(const UWorld* World, const FVector& Start, const FVector& End, const FVector HalfSize, const FRotator Orientation, EDrawDebugTrace::Type DrawDebugType, bool bHit, const TArray<FHitResult>& OutHits, FLinearColor TraceColor, FLinearColor TraceHitColor, float DrawTime)
		{
			if (DrawDebugType != EDrawDebugTrace::None && (World != nullptr))
			{
				bool bPersistent = DrawDebugType == EDrawDebugTrace::Persistent;
				float LifeTime = (DrawDebugType == EDrawDebugTrace::ForDuration) ? DrawTime : 0.f;

				if (bHit && OutHits.Last().bBlockingHit)
				{
					// Red up to the blocking hit, green thereafter
					FVector const BlockingHitPoint = OutHits.Last().Location;
					SweptBox(World, Start, BlockingHitPoint, Orientation, HalfSize, TraceColor.ToFColor(true), bPersistent, LifeTime);
					SweptBox(World, BlockingHitPoint, End, Orientation, HalfSize, TraceHitColor.ToFColor(true), bPersistent, LifeTime);
				}
				else
				{
					// no hit means all red
					SweptBox(World, Start, End, Orientation, HalfSize, TraceColor.ToFColor(true), bPersistent, LifeTime);
				}

				// draw hits
				for (int32 HitIdx = 0; HitIdx < OutHits.Num(); ++HitIdx)
				{
					FHitResult const& Hit = OutHits[HitIdx];
					DrawDebugPoint(World, Hit.ImpactPoint, DEBUG_IMPACTPOINT_SIZE, (Hit.bBlockingHit ? TraceColor.ToFColor(true) : TraceHitColor.ToFColor(true)), bPersistent, LifeTime);
				}
			}
		}

		void FLibrary::SphereTraceSingle(const UWorld* World, const FVector3f& Start, const FVector3f& End, float Radius, EDrawDebugTrace::Type DrawDebugType, bool bHit, const FHitResult& OutHit, FLinearColor TraceColor, FLinearColor TraceHitColor, float DrawTime)
		{
			if (DrawDebugType != EDrawDebugTrace::None)
			{
				bool bPersistent = DrawDebugType == EDrawDebugTrace::Persistent;
				float LifeTime = (DrawDebugType == EDrawDebugTrace::ForDuration) ? DrawTime : 0.f;

				if (bHit && OutHit.bBlockingHit)
				{
					// Red up to the blocking hit, green thereafter
					SweptSphere(World, Start, CsMathLibrary::Convert(OutHit.Location), Radius, TraceColor.ToFColor(true), bPersistent, LifeTime);
					SweptSphere(World, CsMathLibrary::Convert(OutHit.Location), End, Radius, TraceHitColor.ToFColor(true), bPersistent, LifeTime);
					DrawDebugPoint(World, CsMathLibrary::Convert(OutHit.ImpactPoint), DEBUG_IMPACTPOINT_SIZE, TraceColor.ToFColor(true), bPersistent, LifeTime);
				}
				else
				{
					// no hit means all red
					SweptSphere(World, Start, End, Radius, TraceColor.ToFColor(true), bPersistent, LifeTime);
				}
			}
		}

		void FLibrary::SphereTraceSingle(const UWorld* World, const FVector& Start, const FVector& End, float Radius, EDrawDebugTrace::Type DrawDebugType, bool bHit, const FHitResult& OutHit, FLinearColor TraceColor, FLinearColor TraceHitColor, float DrawTime)
		{
			if (DrawDebugType != EDrawDebugTrace::None)
			{
				bool bPersistent = DrawDebugType == EDrawDebugTrace::Persistent;
				float LifeTime = (DrawDebugType == EDrawDebugTrace::ForDuration) ? DrawTime : 0.f;

				if (bHit && OutHit.bBlockingHit)
				{
					// Red up to the blocking hit, green thereafter
					SweptSphere(World, Start, OutHit.Location, Radius, TraceColor.ToFColor(true), bPersistent, LifeTime);
					SweptSphere(World, OutHit.Location, End, Radius, TraceHitColor.ToFColor(true), bPersistent, LifeTime);
					DrawDebugPoint(World, OutHit.ImpactPoint, DEBUG_IMPACTPOINT_SIZE, TraceColor.ToFColor(true), bPersistent, LifeTime);
				}
				else
				{
					// no hit means all red
					SweptSphere(World, Start, End, Radius, TraceColor.ToFColor(true), bPersistent, LifeTime);
				}
			}
		}

		void FLibrary::SphereTraceMulti(const UWorld* World, const FVector3f& Start, const FVector3f& End, float Radius, EDrawDebugTrace::Type DrawDebugType, bool bHit, const TArray<FHitResult>& OutHits, FLinearColor TraceColor, FLinearColor TraceHitColor, float DrawTime)
		{
			if (DrawDebugType != EDrawDebugTrace::None)
			{
				bool bPersistent = DrawDebugType == EDrawDebugTrace::Persistent;
				float LifeTime = (DrawDebugType == EDrawDebugTrace::ForDuration) ? DrawTime : 0.f;

				if (bHit && OutHits.Last().bBlockingHit)
				{
					// Red up to the blocking hit, green thereafter
					FVector3f const BlockingHitPoint = CsMathLibrary::Convert(OutHits.Last().Location);
					SweptSphere(World, Start, BlockingHitPoint, Radius, TraceColor.ToFColor(true), bPersistent, LifeTime);
					SweptSphere(World, BlockingHitPoint, End, Radius, TraceHitColor.ToFColor(true), bPersistent, LifeTime);
				}
				else
				{
					// no hit means all red
					SweptSphere(World, Start, End, Radius, TraceColor.ToFColor(true), bPersistent, LifeTime);
				}

				// draw hits
				for (int32 HitIdx = 0; HitIdx < OutHits.Num(); ++HitIdx)
				{
					FHitResult const& Hit = OutHits[HitIdx];
					DrawDebugPoint(World, CsMathLibrary::Convert(Hit.ImpactPoint), DEBUG_IMPACTPOINT_SIZE, (Hit.bBlockingHit ? TraceColor.ToFColor(true) : TraceHitColor.ToFColor(true)), bPersistent, LifeTime);
				}
			}
		}

		void FLibrary::SphereTraceMulti(const UWorld* World, const FVector& Start, const FVector& End, float Radius, EDrawDebugTrace::Type DrawDebugType, bool bHit, const TArray<FHitResult>& OutHits, FLinearColor TraceColor, FLinearColor TraceHitColor, float DrawTime)
		{
			if (DrawDebugType != EDrawDebugTrace::None)
			{
				bool bPersistent = DrawDebugType == EDrawDebugTrace::Persistent;
				float LifeTime = (DrawDebugType == EDrawDebugTrace::ForDuration) ? DrawTime : 0.f;

				if (bHit && OutHits.Last().bBlockingHit)
				{
					// Red up to the blocking hit, green thereafter
					FVector const BlockingHitPoint = OutHits.Last().Location;
					SweptSphere(World, Start, BlockingHitPoint, Radius, TraceColor.ToFColor(true), bPersistent, LifeTime);
					SweptSphere(World, BlockingHitPoint, End, Radius, TraceHitColor.ToFColor(true), bPersistent, LifeTime);
				}
				else
				{
					// no hit means all red
					SweptSphere(World, Start, End, Radius, TraceColor.ToFColor(true), bPersistent, LifeTime);
				}

				// draw hits
				for (int32 HitIdx = 0; HitIdx < OutHits.Num(); ++HitIdx)
				{
					FHitResult const& Hit = OutHits[HitIdx];
					DrawDebugPoint(World, Hit.ImpactPoint, DEBUG_IMPACTPOINT_SIZE, (Hit.bBlockingHit ? TraceColor.ToFColor(true) : TraceHitColor.ToFColor(true)), bPersistent, LifeTime);
				}
			}
		}

		void FLibrary::CapsuleTraceSingle(const UWorld* World, const FVector3f& Start, const FVector3f& End, float Radius, float HalfHeight, EDrawDebugTrace::Type DrawDebugType, bool bHit, const FHitResult& OutHit, FLinearColor TraceColor, FLinearColor TraceHitColor, float DrawTime)
		{
			if (DrawDebugType != EDrawDebugTrace::None)
			{
				bool bPersistent = DrawDebugType == EDrawDebugTrace::Persistent;
				float LifeTime = (DrawDebugType == EDrawDebugTrace::ForDuration) ? DrawTime : 0.f;

				if (bHit && OutHit.bBlockingHit)
				{
					// Red up to the blocking hit, green thereafter
					DrawDebugCapsule(World, Start, HalfHeight, Radius, FQuat4f::Identity, TraceColor.ToFColor(true), bPersistent, LifeTime);
					DrawDebugCapsule(World, CsMathLibrary::Convert(OutHit.Location), HalfHeight, Radius, FQuat4f::Identity, TraceColor.ToFColor(true), bPersistent, LifeTime);
					DrawDebugLine(World, Start, CsMathLibrary::Convert(OutHit.Location), TraceColor.ToFColor(true), bPersistent, LifeTime);
					DrawDebugPoint(World, CsMathLibrary::Convert(OutHit.ImpactPoint), DEBUG_IMPACTPOINT_SIZE, TraceColor.ToFColor(true), bPersistent, LifeTime);

					DrawDebugCapsule(World, End, HalfHeight, Radius, FQuat4f::Identity, TraceHitColor.ToFColor(true), bPersistent, LifeTime);
					DrawDebugLine(World, CsMathLibrary::Convert(OutHit.Location), End, TraceHitColor.ToFColor(true), bPersistent, LifeTime);
				}
				else
				{
					// no hit means all red
					DrawDebugCapsule(World, Start, HalfHeight, Radius, FQuat4f::Identity, TraceColor.ToFColor(true), bPersistent, LifeTime);
					DrawDebugCapsule(World, End, HalfHeight, Radius, FQuat4f::Identity, TraceColor.ToFColor(true), bPersistent, LifeTime);
					DrawDebugLine(World, Start, End, TraceColor.ToFColor(true), bPersistent, LifeTime);
				}
			}
		}

		void FLibrary::CapsuleTraceSingle(const UWorld* World, const FVector& Start, const FVector& End, float Radius, float HalfHeight, EDrawDebugTrace::Type DrawDebugType, bool bHit, const FHitResult& OutHit, FLinearColor TraceColor, FLinearColor TraceHitColor, float DrawTime)
		{
			if (DrawDebugType != EDrawDebugTrace::None)
			{
				bool bPersistent = DrawDebugType == EDrawDebugTrace::Persistent;
				float LifeTime = (DrawDebugType == EDrawDebugTrace::ForDuration) ? DrawTime : 0.f;

				if (bHit && OutHit.bBlockingHit)
				{
					// Red up to the blocking hit, green thereafter
					DrawDebugCapsule(World, Start, HalfHeight, Radius, FQuat::Identity, TraceColor.ToFColor(true), bPersistent, LifeTime);
					DrawDebugCapsule(World, OutHit.Location, HalfHeight, Radius, FQuat::Identity, TraceColor.ToFColor(true), bPersistent, LifeTime);
					DrawDebugLine(World, Start, OutHit.Location, TraceColor.ToFColor(true), bPersistent, LifeTime);
					DrawDebugPoint(World, OutHit.ImpactPoint, DEBUG_IMPACTPOINT_SIZE, TraceColor.ToFColor(true), bPersistent, LifeTime);

					DrawDebugCapsule(World, End, HalfHeight, Radius, FQuat::Identity, TraceHitColor.ToFColor(true), bPersistent, LifeTime);
					DrawDebugLine(World, OutHit.Location, End, TraceHitColor.ToFColor(true), bPersistent, LifeTime);
				}
				else
				{
					// no hit means all red
					DrawDebugCapsule(World, Start, HalfHeight, Radius, FQuat::Identity, TraceColor.ToFColor(true), bPersistent, LifeTime);
					DrawDebugCapsule(World, End, HalfHeight, Radius, FQuat::Identity, TraceColor.ToFColor(true), bPersistent, LifeTime);
					DrawDebugLine(World, Start, End, TraceColor.ToFColor(true), bPersistent, LifeTime);
				}
			}
		}

		void FLibrary::CapsuleTraceMulti(const UWorld* World, const FVector3f& Start, const FVector3f& End, float Radius, float HalfHeight, EDrawDebugTrace::Type DrawDebugType, bool bHit, const TArray<FHitResult>& OutHits, FLinearColor TraceColor, FLinearColor TraceHitColor, float DrawTime)
		{
			if (DrawDebugType != EDrawDebugTrace::None)
			{
				bool bPersistent = DrawDebugType == EDrawDebugTrace::Persistent;
				float LifeTime = (DrawDebugType == EDrawDebugTrace::ForDuration) ? DrawTime : 0.f;

				if (bHit && OutHits.Last().bBlockingHit)
				{
					// Red up to the blocking hit, green thereafter
					FVector3f const BlockingHitPoint = CsMathLibrary::Convert(OutHits.Last().Location);
					DrawDebugCapsule(World, Start, HalfHeight, Radius, FQuat4f::Identity, TraceColor.ToFColor(true), bPersistent, LifeTime);
					DrawDebugCapsule(World, BlockingHitPoint, HalfHeight, Radius, FQuat4f::Identity, TraceColor.ToFColor(true), bPersistent, LifeTime);
					DrawDebugLine(World, Start, BlockingHitPoint, TraceColor.ToFColor(true), bPersistent, LifeTime);

					DrawDebugCapsule(World, End, HalfHeight, Radius, FQuat4f::Identity, TraceHitColor.ToFColor(true), bPersistent, LifeTime);
					DrawDebugLine(World, BlockingHitPoint, End, TraceHitColor.ToFColor(true), bPersistent, LifeTime);
				}
				else
				{
					// no hit means all red
					DrawDebugCapsule(World, Start, HalfHeight, Radius, FQuat4f::Identity, TraceColor.ToFColor(true), bPersistent, LifeTime);
					DrawDebugCapsule(World, End, HalfHeight, Radius, FQuat4f::Identity, TraceColor.ToFColor(true), bPersistent, LifeTime);
					DrawDebugLine(World, Start, End, TraceColor.ToFColor(true), bPersistent, LifeTime);
				}

				// draw hits
				for (int32 HitIdx = 0; HitIdx < OutHits.Num(); ++HitIdx)
				{
					FHitResult const& Hit = OutHits[HitIdx];
					DrawDebugPoint(World, CsMathLibrary::Convert(Hit.ImpactPoint), DEBUG_IMPACTPOINT_SIZE, (Hit.bBlockingHit ? TraceColor.ToFColor(true) : TraceHitColor.ToFColor(true)), bPersistent, LifeTime);
				}
			}
		}

		void FLibrary::CapsuleTraceMulti(const UWorld* World, const FVector& Start, const FVector& End, float Radius, float HalfHeight, EDrawDebugTrace::Type DrawDebugType, bool bHit, const TArray<FHitResult>& OutHits, FLinearColor TraceColor, FLinearColor TraceHitColor, float DrawTime)
		{
			if (DrawDebugType != EDrawDebugTrace::None)
			{
				bool bPersistent = DrawDebugType == EDrawDebugTrace::Persistent;
				float LifeTime = (DrawDebugType == EDrawDebugTrace::ForDuration) ? DrawTime : 0.f;

				if (bHit && OutHits.Last().bBlockingHit)
				{
					// Red up to the blocking hit, green thereafter
					FVector const BlockingHitPoint = OutHits.Last().Location;
					DrawDebugCapsule(World, Start, HalfHeight, Radius, FQuat::Identity, TraceColor.ToFColor(true), bPersistent, LifeTime);
					DrawDebugCapsule(World, BlockingHitPoint, HalfHeight, Radius, FQuat::Identity, TraceColor.ToFColor(true), bPersistent, LifeTime);
					DrawDebugLine(World, Start, BlockingHitPoint, TraceColor.ToFColor(true), bPersistent, LifeTime);

					DrawDebugCapsule(World, End, HalfHeight, Radius, FQuat::Identity, TraceHitColor.ToFColor(true), bPersistent, LifeTime);
					DrawDebugLine(World, BlockingHitPoint, End, TraceHitColor.ToFColor(true), bPersistent, LifeTime);
				}
				else
				{
					// no hit means all red
					DrawDebugCapsule(World, Start, HalfHeight, Radius, FQuat::Identity, TraceColor.ToFColor(true), bPersistent, LifeTime);
					DrawDebugCapsule(World, End, HalfHeight, Radius, FQuat::Identity, TraceColor.ToFColor(true), bPersistent, LifeTime);
					DrawDebugLine(World, Start, End, TraceColor.ToFColor(true), bPersistent, LifeTime);
				}

				// draw hits
				for (int32 HitIdx = 0; HitIdx < OutHits.Num(); ++HitIdx)
				{
					FHitResult const& Hit = OutHits[HitIdx];
					DrawDebugPoint(World, Hit.ImpactPoint, DEBUG_IMPACTPOINT_SIZE, (Hit.bBlockingHit ? TraceColor.ToFColor(true) : TraceHitColor.ToFColor(true)), bPersistent, LifeTime);
				}
			}
		}

		void FLibrary::String(const UWorld* InWorld, FVector3f const& TextLocation, const FString& Text, AActor* TestBaseActor /*=NULL*/, FColor const& TextColor /*=FColor::White*/, float Duration /*= -1.000000*/, bool bDrawShadow /*=false*/, float FontScale /*=1.f*/)
		{
		#if WITH_EDITOR
			// no debug line drawing on dedicated server
			if (GEngine->GetNetMode(InWorld) != NM_DedicatedServer)
			{
				check(TestBaseActor == NULL || TestBaseActor->GetWorld() == InWorld);
				AActor* BaseAct = (TestBaseActor != NULL) ? TestBaseActor : InWorld->GetWorldSettings();

				// iterate through the player controller list
				for (FConstPlayerControllerIterator Iterator = InWorld->GetPlayerControllerIterator(); Iterator; ++Iterator)
				{
					APlayerController* PlayerController = Iterator->Get();
					if (PlayerController && PlayerController->MyHUD && PlayerController->Player)
					{
						PlayerController->MyHUD->AddDebugText(Text, BaseAct, Duration, CsMathLibrary::Convert(TextLocation), CsMathLibrary::Convert(TextLocation), TextColor, true, (TestBaseActor == NULL), false, nullptr, FontScale, bDrawShadow);
					}
				}
			}
		#endif // #if WITH_EDITOR
		}

		void FLibrary::String(const UWorld* InWorld, FVector const& TextLocation, const FString& Text, AActor* TestBaseActor /*=NULL*/, FColor const& TextColor /*=FColor::White*/, float Duration /*= -1.000000*/, bool bDrawShadow /*=false*/, float FontScale /*=1.f*/)
		{
		#if WITH_EDITOR
			// no debug line drawing on dedicated server
			if (GEngine->GetNetMode(InWorld) != NM_DedicatedServer)
			{
				check(TestBaseActor == NULL || TestBaseActor->GetWorld() == InWorld);
				AActor* BaseAct = (TestBaseActor != NULL) ? TestBaseActor : InWorld->GetWorldSettings();

				// iterate through the player controller list
				for (FConstPlayerControllerIterator Iterator = InWorld->GetPlayerControllerIterator(); Iterator; ++Iterator)
				{
					APlayerController* PlayerController = Iterator->Get();
					if (PlayerController && PlayerController->MyHUD && PlayerController->Player)
					{
						PlayerController->MyHUD->AddDebugText(Text, BaseAct, Duration, TextLocation, TextLocation, TextColor, true, (TestBaseActor == NULL), false, nullptr, FontScale, bDrawShadow);
					}
				}
			}
		#endif // #if WITH_EDITOR
		}
	}
}