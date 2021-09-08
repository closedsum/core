// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#include "Spawner/Point/CsSpawnerPoint_ShapeCircleImpl.h"
#include "CsCore.h"

// Library
#include "Spawner/Params/CsLibrary_SpawnerParams.h"
// Containers
#include "Containers/CsInterfaceMap.h"
// Spawner
#include "Spawner/CsSpawner.h"
#include "Spawner/Params/CsSpawnerParams.h"
#include "Spawner/Params/Shape/CsSpawnerParams_Shape.h"
#include "Spawner/Params/Shape/CsSpawnerParams_ShapeCircle.h"
// Actor
#include "GameFramework/Actor.h"

namespace NCsSpawner
{
	namespace NPoint
	{
		namespace NShape
		{
			namespace NCircle
			{
				namespace NCached
				{
					namespace Str
					{
						CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsSpawner::NPoint::NShape::NCircle::FImpl, SetParams);
						CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsSpawner::NPoint::NShape::NCircle::FImpl, GetCenterLocation);
					}
				}

				// NCsSpawner::NPoint::IImpl
				#pragma region

				void FImpl::SetSpawner(ICsSpawner* InSpawner)
				{
					Spawner		   = InSpawner;
					SpawnerAsActor = Cast<AActor>(InSpawner->_getUObject());
				}

				#define ParamsType NCsSpawner::NParams::IParams
				void FImpl::SetParams(ParamsType* InParams)
				{
					using namespace NCsSpawner::NPoint::NShape::NCircle::NCached;

					const FString& Context = Str::SetParams;

					// Perform Checks
					typedef NCsSpawner::NParams::FLibrary ParamsLibrary;

					check(ParamsLibrary::IsValidChecked(Context, InParams));

					Params = InParams;

					// Cache Param slices
					typedef NCsSpawner::NParams::NShape::IShape ShapeParamsType;
					typedef NCsSpawner::NParams::NShape::ICircle CircleParamsType;

					FCsInterfaceMap* InterfaceMap = Params->GetInterfaceMap();

					ShapeParams = InterfaceMap->Get<ShapeParamsType>();
					CircleParams = InterfaceMap->Get<CircleParamsType>();

					typedef NCsSpawner::NParams::FCount CountParamsType;
					typedef NCsSpawner::NParams::FFrequency FrequencyParamsType;
					typedef NCsSpawner::NPoint::ECount PointCountType;
					typedef NCsSpawner::EFrequency FrequencyType;
					
					const CountParamsType& CountParams		   = Params->GetCountParams();
					const FrequencyParamsType& FrequencyParams = Params->GetFrequencyParams();

					// None
					if (CountType == PointCountType::None)
					{
						checkf(FrequencyParams.GetType() == FrequencyType::Infinite, TEXT("%s: If CountType == None (PointCountType::None), then Params->GetFrequencyParams().GetType() MUST be Infinite (FrequencyType::Infinite)."), *Context);
					}
					// TotalCount
					else
					if (CountType == PointCountType::TotalCount)
					{
						const FrequencyType& Frequency = FrequencyParams.GetType();

						checkf(Frequency != FrequencyType::Infinite, TEXT("%s: If CountType == TotalCount (PointCountType::TotalCount), then Params->GetFrequencyParams().GetType() must NOT be Infinite (FrequencyType::Infinite)."), *Context);

						// Once
						if (Frequency == FrequencyType::Once)
						{
							Transforms.Reset(CountParams.GetCountPerSpawn());
							Transforms.AddDefaulted(CountParams.GetCountPerSpawn());
						}
						// Count
						else
						if (Frequency == FrequencyType::Count)
						{
							checkf(FrequencyParams.GetCount() > 0, TEXT("%s: If CountType == TotalCount (PointCountType::TotalCount), then Params->GetFrequencyParams().GetCount() MUST be > 0."), *Context);

							Transforms.Reset(CountParams.GetCountPerSpawn() * FrequencyParams.GetCount());
							Transforms.AddDefaulted(CountParams.GetCountPerSpawn() * FrequencyParams.GetCount());
						}
						// TimeCount | TimeInterval
						else
						if (Frequency == FrequencyType::TimeCount ||
							Frequency == FrequencyType::TimeInterval)
						{
							checkf(FrequencyParams.GetCount() > 0, TEXT("%s: If CountType == TotalCount (PointCountType::TotalCount), then Params->GetFrequencyParams().GetCount() MUST be > 0."), *Context);

							Transforms.Reset(FrequencyParams.GetCount());
							Transforms.AddDefaulted(FrequencyParams.GetCount());
						}
					}
					// CountPerSpawn
					else
					if (CountType == PointCountType::CountPerSpawn)
					{
						checkf(FrequencyParams.GetType() != FrequencyType::Infinite, TEXT("%s: If CountType == CountPerSpawn (PointCountType::CountPerSpawn), then Params->GetFrequencyParams().GetType() must NOT be Infinite (FrequencyType::Infinite)."), *Context);

						Transforms.Reset(CountParams.GetCountPerSpawn());
					}

					// Check Center
					typedef NCsSpawner::NShape::ECenter CenterType;

					const CenterType& Center = ShapeParams->GetCenterType();
						// Check if SpawnAsActor exists
					if (Center == CenterType::Self)
					{
						checkf(SpawnerAsActor, TEXT("%s: InParams->GetCenterType() == Self (CenterType::Self) but Spawner is NOT an Actor."), *Context);
					}
					else
					if (Center == CenterType::Actor)
					{
						checkf(CenterAsActor, TEXT("%s: InParams->GetCenterType() == Actor (CenterType::Actor) but NO Actor has been set for the Center."), *Context)
					}
				}
				#undef ParamsType

				void FImpl::Prepare()
				{
					typedef NCsSpawner::NPoint::ECount PointCountType;

					if (CountType == PointCountType::None)
						return;

					for (FTransform& Transform : Transforms)
					{
						Transform.SetTranslation(GenerateRandomLocation());
					}
				}

				void FImpl::Advance(const int32& Count, const int32& Group, const int32& CountPerGroup)
				{
					int32 Last_Group = CurrentGroup;
					CurrentGroup     = Group;

					typedef NCsSpawner::NPoint::ECount PointCountType;
					// None
					if (CountType == PointCountType::None)
						return;
					// TotalCount
					if (CountType == PointCountType::TotalCount)
					{
						++Index;
					}
					// CountPerSpawn
					else
					if (CountType == PointCountType::CountPerSpawn)
					{
						Index = (Index + 1) % Params->GetCountParams().GetCountPerSpawn();

						if (CurrentGroup != Last_Group)
							Prepare();
					}
				}

				FTransform FImpl::GetTransform(const int32& Count, const int32& Group, const int32& CountPerGroup) const
				{
					typedef NCsSpawner::NPoint::ECount PointCountType;

					FVector Location = FVector::ZeroVector;
					// None
					if (CountType == PointCountType::None)
					{
						Location = GenerateRandomLocation();
					}
					// TotalCount
					else
					if (CountType == PointCountType::TotalCount)
					{
						Location = Transforms[Count].GetTranslation();
					}
					// CountPerSpawn
					else
					if (CountType == PointCountType::CountPerSpawn)
					{
						Location = Transforms[CountPerGroup].GetTranslation();
					}

					FTransform Transform = FTransform::Identity;

					Transform.SetTranslation(Location + GetCenterLocation());

					return Transform;
				}

				FTransform FImpl::GetCurrentTransform() const
				{
					typedef NCsSpawner::NPoint::ECount PointCountType;

					FVector Location = FVector::ZeroVector;
					// None
					if (CountType == PointCountType::None)
					{
						Location = GenerateRandomLocation();
					}
					// TotalCount
					else
					if (CountType == PointCountType::TotalCount)
					{
						Location = Transforms[Index].GetTranslation();
					}
					// CountPerSpawn
					else
					if (CountType == PointCountType::CountPerSpawn)
					{
						Location = Transforms[Index].GetTranslation();
					}

					FTransform Transform = FTransform::Identity;

					Transform.SetTranslation(Location + GetCenterLocation());

					return Transform;
				}

				#pragma endregion NCsSpawner::NPoint::IImpl

				FVector FImpl::GenerateRandomLocation() const
				{
					FVector Location = FVector::ZeroVector;

					const float& MinRadius = CircleParams->GetMinRadius();
					const float& MaxRadius = CircleParams->GetMaxRadius();

					const float MaxRadiusSq = MaxRadius * MaxRadius;
					const float MinRadiusSq = MinRadius * MinRadius;

					const float Radius = FMath::Sqrt((FMath::RandRange(0.0f, 1.0f) * (MaxRadiusSq - MinRadiusSq)) + MinRadiusSq);
					const float Theta  = FMath::RandRange(0.0f, 1.0f) * 2.0f * PI;
					const float X	   = Radius * FMath::Cos(Theta);
					const float Y	   = Radius * FMath::Sin(Theta);

					Location.X = X;
					Location.Y = Y;

					return Location;
				}

				FVector FImpl::GetCenterLocation() const
				{
					using namespace NCsSpawner::NPoint::NShape::NCircle::NCached;

					const FString& Context = Str::GetCenterLocation;

					typedef NCsSpawner::NShape::ECenter CenterType;

					const CenterType& Center = ShapeParams->GetCenterType();
					// Self (Spawner)
					if (Center == CenterType::Self)
					{
						return SpawnerAsActor->GetActorLocation();
					}
					// Transform
					else
					if (Center == CenterType::Transform)
					{
						return CenterAsTransform.GetTranslation();
					}
					// Actor
					else
					if (Center == CenterType::Actor)
					{
						return CenterAsActor->GetActorLocation();
					}

					typedef NCsSpawner::NShape::EMCenter CenterMapType;

					checkf(0, TEXT("%s: Center: %s is NOT supported."), *Context, CenterMapType::Get().ToChar(Center));
					return FVector::ZeroVector;
				}
			}
		}
	}
}