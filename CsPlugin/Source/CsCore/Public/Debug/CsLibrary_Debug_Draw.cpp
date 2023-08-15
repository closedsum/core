// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
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
			typedef NCsMath::FLibrary MathLibrary;

			::DrawDebugLine(InWorld, MathLibrary::Convert(LineStart), MathLibrary::Convert(LineEnd), Color, bPersistentLines, LifeTime, DepthPriority, Thickness);
		}

		void FLibrary::DrawDebugPoint(const UWorld* InWorld, FVector3f const& Position, float Size, FColor const& PointColor, bool bPersistentLines /*=false*/, float LifeTime /*=-1.f*/, uint8 DepthPriority /*=0*/)
		{
			typedef NCsMath::FLibrary MathLibrary;

			::DrawDebugPoint(InWorld, MathLibrary::Convert(Position), Size, PointColor, bPersistentLines, LifeTime, DepthPriority);
		}

		void DrawDebugPoint(const UWorld* InWorld, FVector3f const& Position, float Size, FColor const& PointColor, bool bPersistentLines /*=false*/, float LifeTime /*=-1.f*/, uint8 DepthPriority /*=0*/)
		{
			typedef NCsMath::FLibrary MathLibrary;

			::DrawDebugPoint(InWorld, MathLibrary::Convert(Position), Size, PointColor, bPersistentLines, LifeTime, DepthPriority);
		}

		void FLibrary::DrawDebugDirectionalArrow(const UWorld* InWorld, FVector3f const& LineStart, FVector3f const& LineEnd, float ArrowSize, FColor const& Color, bool bPersistentLines /*=false*/, float LifeTime /*=-1.f*/, uint8 DepthPriority /*=0*/, float Thickness /*=0.f*/)
		{
			typedef NCsMath::FLibrary MathLibrary;

			::DrawDebugDirectionalArrow(InWorld, MathLibrary::Convert(LineStart), MathLibrary::Convert(LineEnd), ArrowSize, Color, bPersistentLines, LifeTime,DepthPriority, Thickness);
		}

		void FLibrary::DrawDebugBox(const UWorld* InWorld, FVector3f const& Center, FVector3f const& Extent, FColor const& Color, bool bPersistentLines /*=false*/, float LifeTime /*=-1.f*/, uint8 DepthPriority /*=0*/, float Thickness /*=0.f*/)
		{
			typedef NCsMath::FLibrary MathLibrary;

			::DrawDebugBox(InWorld, MathLibrary::Convert(Center), MathLibrary::Convert(Extent), Color, bPersistentLines, LifeTime, DepthPriority, Thickness);
		}

		void FLibrary::DrawDebugBox(const UWorld* InWorld, FVector3f const& Center, FVector3f const& Extent, const FQuat4f& Rotation, FColor const& Color, bool bPersistentLines /*=false*/, float LifeTime /*=-1.f*/, uint8 DepthPriority /*=0*/, float Thickness /*=0.f*/)
		{
			typedef NCsMath::FLibrary MathLibrary;

			::DrawDebugBox(InWorld, MathLibrary::Convert(Center), MathLibrary::Convert(Extent), MathLibrary::Convert(Rotation), Color, bPersistentLines, LifeTime, DepthPriority, Thickness);
		}

		void FLibrary::DrawDebugCircle(const UWorld* InWorld, const FMatrix44f& TransformMatrix, float Radius, int32 Segments, const FColor& Color, bool bPersistentLines /*=false*/, float LifeTime /*=-1.f*/, uint8 DepthPriority /*=0*/, float Thickness /*=0.f*/, bool bDrawAxis /*=true*/)
		{
			typedef NCsMath::FLibrary MathLibrary;

			::DrawDebugCircle(InWorld, MathLibrary::Convert(TransformMatrix), Radius, Segments, Color, bPersistentLines, LifeTime, DepthPriority, Thickness, bDrawAxis);
		}

		void FLibrary::DrawDebugCircle(const UWorld* InWorld, FVector3f Center, float Radius, int32 Segments, const FColor& Color, bool bPersistentLines /*=false*/, float LifeTime /*=-1.f*/, uint8 DepthPriority /*=0*/, float Thickness /*=0.f*/, FVector3f YAxis /*=FVector3f(0.f, 1.f, 0.f)*/, FVector3f ZAxis /*=FVector3f(0.f, 0.f, 1.f)*/, bool bDrawAxis /*=true*/)
		{
			typedef NCsMath::FLibrary MathLibrary;

			::DrawDebugCircle(InWorld, MathLibrary::Convert(Center), Radius, Segments, Color, bPersistentLines, LifeTime, DepthPriority, Thickness, MathLibrary::Convert(YAxis), MathLibrary::Convert(ZAxis), bDrawAxis);
		}

		void FLibrary::DrawDebugCapsule(const UWorld* InWorld, FVector3f const& Center, float HalfHeight, float Radius, const FQuat4f& Rotation, FColor const& Color, bool bPersistentLines /*=false*/, float LifeTime /*=-1.f*/, uint8 DepthPriority /*=0*/, float Thickness /*=0*/)
		{
			typedef NCsMath::FLibrary MathLibrary;

			::DrawDebugCapsule(InWorld, MathLibrary::Convert(Center), HalfHeight, Radius, MathLibrary::Convert(Rotation), Color, bPersistentLines, LifeTime, DepthPriority, Thickness);
		}

		void FLibrary::DrawDebug2DDonut(const UWorld* InWorld, const FMatrix44f& TransformMatrix, float InnerRadius, float OuterRadius, int32 Segments, const FColor& Color, bool bPersistentLines /*=false*/, float LifeTime /*=-1.f*/, uint8 DepthPriority /*=0*/, float Thickness /*=0.f*/)
		{
			typedef NCsMath::FLibrary MathLibrary;

			::DrawDebug2DDonut(InWorld, MathLibrary::Convert(TransformMatrix), InnerRadius, OuterRadius, Segments, Color, bPersistentLines, LifeTime, DepthPriority, Thickness);
		}

		void FLibrary::DrawDebugSphere(const UWorld* InWorld, FVector3f const& Center, float Radius, int32 Segments, FColor const& Color, bool bPersistentLines /*=false*/, float LifeTime /*=-1.f*/, uint8 DepthPriority /*=0*/, float Thickness /*=0.f*/)
		{
			typedef NCsMath::FLibrary MathLibrary;

			::DrawDebugSphere(InWorld, MathLibrary::Convert(Center), Radius, Segments, Color, bPersistentLines, LifeTime, DepthPriority, Thickness);
		}

		void FLibrary::DrawDebugCone(const UWorld* InWorld, FVector3f const& Origin, FVector3f const& Direction, float Length, float AngleWidth, float AngleHeight, int32 NumSides, FColor const& Color, bool bPersistentLines /*=false*/, float LifeTime /*=-1.f*/, uint8 DepthPriority /*=0*/, float Thickness /*=0.f*/)
		{
			typedef NCsMath::FLibrary MathLibrary;

			::DrawDebugCone(InWorld, MathLibrary::Convert(Origin), MathLibrary::Convert(Direction), Length, AngleWidth, AngleHeight, NumSides, Color, bPersistentLines, LifeTime, DepthPriority, Thickness);
		}

		void FLibrary::DrawDebugString(const UWorld* InWorld, FVector3f const& TextLocation, const FString& Text, class AActor* TestBaseActor /*=NULL*/, FColor const& TextColor /*=FColor::White*/, float Duration /*=-1.000000*/, bool bDrawShadow /*=false*/, float FontScale /*=1.f*/)
		{
			typedef NCsMath::FLibrary MathLibrary;

			::DrawDebugString(InWorld, MathLibrary::Convert(TextLocation), Text, TestBaseActor, TextColor, Duration, bDrawShadow, FontScale);
		}

		void FLibrary::DrawDebugSolidBox(const UWorld* InWorld, FBox3f const& Box, FColor const& Color, const FTransform3f& Transform /*=FTransform3f::Identity*/, bool bPersistent /*=false*/, float LifeTime /*=-1.f*/, uint8 DepthPriority /*=0*/)
		{
			typedef NCsMath::FLibrary MathLibrary;

			::DrawDebugSolidBox(InWorld, MathLibrary::Convert(Box), Color, MathLibrary::Convert(Transform), bPersistent, LifeTime, DepthPriority);
		}

		void FLibrary::DrawDebugSolidBox(const UWorld* InWorld, FVector3f const& Center, FVector3f const& Extent, FColor const& Color, bool bPersistent /*=false*/, float LifeTime /*=-1.f*/, uint8 DepthPriority /*=0*/)
		{
			typedef NCsMath::FLibrary MathLibrary;

			::DrawDebugSolidBox(InWorld, MathLibrary::Convert(Center), MathLibrary::Convert(Extent), Color, bPersistent, LifeTime, DepthPriority);
		}
		
		void FLibrary::DrawDebugSolidBox(const UWorld* InWorld, FVector3f const& Center, FVector3f const& Extent, FQuat4f const& Rotation, FColor const& Color, bool bPersistent /*=false*/, float LifeTime /*=-1.f*/, uint8 DepthPriority /*=0*/)
		{
			typedef NCsMath::FLibrary MathLibrary;

			::DrawDebugSolidBox(InWorld, MathLibrary::Convert(Center), MathLibrary::Convert(Extent), MathLibrary::Convert(Rotation), Color, bPersistent, LifeTime, DepthPriority);
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

		/** Util for drawing result of single line trace  */
		void FLibrary::LineTraceSingle(const UWorld* World, const FVector3f& Start, const FVector3f& End, EDrawDebugTrace::Type DrawDebugType, bool bHit, const FHitResult& OutHit, FLinearColor TraceColor, FLinearColor TraceHitColor, float DrawTime)
		{
			if (DrawDebugType != EDrawDebugTrace::None)
			{
				typedef NCsMath::FLibrary MathLibrary;

				bool bPersistent = DrawDebugType == EDrawDebugTrace::Persistent;
				float LifeTime   = (DrawDebugType == EDrawDebugTrace::ForDuration) ? DrawTime : 0.f;

				// @fixme, draw line with thickness = 2.f?
				if (bHit && OutHit.bBlockingHit)
				{
					// Red up to the blocking hit, green thereafter
					DrawDebugLine(World, Start, MathLibrary::Convert(OutHit.ImpactPoint), TraceColor.ToFColor(true), bPersistent, LifeTime);
					DrawDebugLine(World, MathLibrary::Convert(OutHit.ImpactPoint), End, TraceHitColor.ToFColor(true), bPersistent, LifeTime);
					DrawDebugPoint(World, MathLibrary::Convert(OutHit.ImpactPoint), DEBUG_IMPACTPOINT_SIZE, TraceColor.ToFColor(true), bPersistent, LifeTime);
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
				typedef NCsMath::FLibrary MathLibrary;

				bool bPersistent = DrawDebugType == EDrawDebugTrace::Persistent;
				float LifeTime   = (DrawDebugType == EDrawDebugTrace::ForDuration) ? DrawTime : 0.f;

				// @fixme, draw line with thickness = 2.f?
				if (bHit && OutHits.Last().bBlockingHit)
				{
					// Red up to the blocking hit, green thereafter
					FVector3f const BlockingHitPoint = MathLibrary::Convert(OutHits.Last().ImpactPoint);
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
					DrawDebugPoint(World, MathLibrary::Convert(Hit.ImpactPoint), DEBUG_IMPACTPOINT_SIZE, (Hit.bBlockingHit ? TraceColor.ToFColor(true) : TraceHitColor.ToFColor(true)), bPersistent, LifeTime);
				}
			}
		}

		void FLibrary::BoxTraceSingle(const UWorld* World, const FVector3f& Start, const FVector3f& End, const FVector3f HalfSize, const FRotator3f Orientation, EDrawDebugTrace::Type DrawDebugType, bool bHit, const FHitResult& OutHit, FLinearColor TraceColor, FLinearColor TraceHitColor, float DrawTime)
		{
			if (DrawDebugType != EDrawDebugTrace::None && (World != nullptr))
			{
				typedef NCsMath::FLibrary MathLibrary;

				bool bPersistent = DrawDebugType == EDrawDebugTrace::Persistent;
				float LifeTime = (DrawDebugType == EDrawDebugTrace::ForDuration) ? DrawTime : 0.f;

				if (bHit && OutHit.bBlockingHit)
				{
					// Red up to the blocking hit, green thereafter
					SweptBox(World, Start, MathLibrary::Convert(OutHit.Location), Orientation, HalfSize, TraceColor.ToFColor(true), bPersistent, LifeTime);
					SweptBox(World, MathLibrary::Convert(OutHit.Location), End, Orientation, HalfSize, TraceHitColor.ToFColor(true), bPersistent, LifeTime);
					DrawDebugPoint(World, MathLibrary::Convert(OutHit.ImpactPoint), DEBUG_IMPACTPOINT_SIZE, TraceColor.ToFColor(true), bPersistent, LifeTime);
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
				typedef NCsMath::FLibrary MathLibrary;

				bool bPersistent = DrawDebugType == EDrawDebugTrace::Persistent;
				float LifeTime = (DrawDebugType == EDrawDebugTrace::ForDuration) ? DrawTime : 0.f;

				if (bHit && OutHits.Last().bBlockingHit)
				{
					// Red up to the blocking hit, green thereafter
					FVector3f const BlockingHitPoint = MathLibrary::Convert(OutHits.Last().Location);
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
					DrawDebugPoint(World, MathLibrary::Convert(Hit.ImpactPoint), DEBUG_IMPACTPOINT_SIZE, (Hit.bBlockingHit ? TraceColor.ToFColor(true) : TraceHitColor.ToFColor(true)), bPersistent, LifeTime);
				}
			}
		}

		void FLibrary::SphereTraceSingle(const UWorld* World, const FVector3f& Start, const FVector3f& End, float Radius, EDrawDebugTrace::Type DrawDebugType, bool bHit, const FHitResult& OutHit, FLinearColor TraceColor, FLinearColor TraceHitColor, float DrawTime)
		{
			if (DrawDebugType != EDrawDebugTrace::None)
			{
				typedef NCsMath::FLibrary MathLibrary;

				bool bPersistent = DrawDebugType == EDrawDebugTrace::Persistent;
				float LifeTime = (DrawDebugType == EDrawDebugTrace::ForDuration) ? DrawTime : 0.f;

				if (bHit && OutHit.bBlockingHit)
				{
					// Red up to the blocking hit, green thereafter
					SweptSphere(World, Start, MathLibrary::Convert(OutHit.Location), Radius, TraceColor.ToFColor(true), bPersistent, LifeTime);
					SweptSphere(World, MathLibrary::Convert(OutHit.Location), End, Radius, TraceHitColor.ToFColor(true), bPersistent, LifeTime);
					DrawDebugPoint(World, MathLibrary::Convert(OutHit.ImpactPoint), DEBUG_IMPACTPOINT_SIZE, TraceColor.ToFColor(true), bPersistent, LifeTime);
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
				typedef NCsMath::FLibrary MathLibrary;

				bool bPersistent = DrawDebugType == EDrawDebugTrace::Persistent;
				float LifeTime = (DrawDebugType == EDrawDebugTrace::ForDuration) ? DrawTime : 0.f;

				if (bHit && OutHits.Last().bBlockingHit)
				{
					// Red up to the blocking hit, green thereafter
					FVector3f const BlockingHitPoint = MathLibrary::Convert(OutHits.Last().Location);
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
					DrawDebugPoint(World, MathLibrary::Convert(Hit.ImpactPoint), DEBUG_IMPACTPOINT_SIZE, (Hit.bBlockingHit ? TraceColor.ToFColor(true) : TraceHitColor.ToFColor(true)), bPersistent, LifeTime);
				}
			}
		}

		void FLibrary::CapsuleTraceSingle(const UWorld* World, const FVector3f& Start, const FVector3f& End, float Radius, float HalfHeight, EDrawDebugTrace::Type DrawDebugType, bool bHit, const FHitResult& OutHit, FLinearColor TraceColor, FLinearColor TraceHitColor, float DrawTime)
		{
			if (DrawDebugType != EDrawDebugTrace::None)
			{
				typedef NCsMath::FLibrary MathLibrary;

				bool bPersistent = DrawDebugType == EDrawDebugTrace::Persistent;
				float LifeTime = (DrawDebugType == EDrawDebugTrace::ForDuration) ? DrawTime : 0.f;

				if (bHit && OutHit.bBlockingHit)
				{
					// Red up to the blocking hit, green thereafter
					DrawDebugCapsule(World, Start, HalfHeight, Radius, FQuat4f::Identity, TraceColor.ToFColor(true), bPersistent, LifeTime);
					DrawDebugCapsule(World, MathLibrary::Convert(OutHit.Location), HalfHeight, Radius, FQuat4f::Identity, TraceColor.ToFColor(true), bPersistent, LifeTime);
					DrawDebugLine(World, Start, MathLibrary::Convert(OutHit.Location), TraceColor.ToFColor(true), bPersistent, LifeTime);
					DrawDebugPoint(World, MathLibrary::Convert(OutHit.ImpactPoint), DEBUG_IMPACTPOINT_SIZE, TraceColor.ToFColor(true), bPersistent, LifeTime);

					DrawDebugCapsule(World, End, HalfHeight, Radius, FQuat4f::Identity, TraceHitColor.ToFColor(true), bPersistent, LifeTime);
					DrawDebugLine(World, MathLibrary::Convert(OutHit.Location), End, TraceHitColor.ToFColor(true), bPersistent, LifeTime);
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

		void FLibrary::CapsuleTraceMulti(const UWorld* World, const FVector3f& Start, const FVector3f& End, float Radius, float HalfHeight, EDrawDebugTrace::Type DrawDebugType, bool bHit, const TArray<FHitResult>& OutHits, FLinearColor TraceColor, FLinearColor TraceHitColor, float DrawTime)
		{
			if (DrawDebugType != EDrawDebugTrace::None)
			{
				typedef NCsMath::FLibrary MathLibrary;

				bool bPersistent = DrawDebugType == EDrawDebugTrace::Persistent;
				float LifeTime = (DrawDebugType == EDrawDebugTrace::ForDuration) ? DrawTime : 0.f;

				if (bHit && OutHits.Last().bBlockingHit)
				{
					// Red up to the blocking hit, green thereafter
					FVector3f const BlockingHitPoint = MathLibrary::Convert(OutHits.Last().Location);
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
					DrawDebugPoint(World, MathLibrary::Convert(Hit.ImpactPoint), DEBUG_IMPACTPOINT_SIZE, (Hit.bBlockingHit ? TraceColor.ToFColor(true) : TraceHitColor.ToFColor(true)), bPersistent, LifeTime);
				}
			}
		}

		void FLibrary::String(const UWorld* InWorld, FVector3f const& TextLocation, const FString& Text, AActor* TestBaseActor /*=NULL*/, FColor const& TextColor /*=FColor::White*/, float Duration /*= -1.000000*/, bool bDrawShadow /*=false*/, float FontScale /*=1.f*/)
		{
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
						typedef NCsMath::FLibrary MathLibrary;

						PlayerController->MyHUD->AddDebugText(Text, BaseAct, Duration, MathLibrary::Convert(TextLocation), MathLibrary::Convert(TextLocation), TextColor, true, (TestBaseActor == NULL), false, nullptr, FontScale, bDrawShadow);
					}
				}
			}
		}
	}
}