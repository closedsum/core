// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Spawner
#include "Spawner/Point/CsSpawnerPointImpl.h"

class ICsSpawner;
class AActor;

// NCsSpawner::NParams::IParams
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsSpawner, NParams, IParams)
// NCsSpawner::NParams::NShape::IShape
CS_FWD_DECLARE_STRUCT_NAMESPACE_3(NCsSpawner, NParams, NShape, IShape)
// NCsSpawner::NParams::NShape::ICircle
CS_FWD_DECLARE_STRUCT_NAMESPACE_3(NCsSpawner, NParams, NShape, ICircle)

namespace NCsSpawner
{
	namespace NPoint
	{
		namespace NShape
		{
			namespace NCircle
			{
			#define ImplType NCsSpawner::NPoint::IImpl

				/**
				* Basic implementation of the interface ImplType (NCsSpawner::NPoint::IImpl)
				* that describes any spawn "points", a place where an object is spawned, for a
				* Spawner (object that implements the interface: ICsSpawner).
				* The spawn "points" are distributed in a circle around a "center".
				*/
				struct CSCORE_API FImpl : public ImplType
				{
				public:

				#define PointCountType NCsSpawner::NPoint::ECount
				#define OrderType NCsSpawner::NPoint::EOrder
				#define ParamsType NCsSpawner::NParams::IParams
				#define ShapeParamsType NCsSpawner::NParams::NShape::IShape
				#define CircleParamsType NCsSpawner::NParams::NShape::ICircle

					/** Reference to the object that will handle spawning objects. */
					ICsSpawner* Spawner;
					/** Reference to Spawner as an AActor. */
					AActor* SpawnerAsActor;

					/** Describes how spawning of objects is tracked (counted). */
					PointCountType CountType;
					/** Describes the order in which spawn points are chosen. */
					OrderType Order;

					ParamsType* Params;
					ShapeParamsType* ShapeParams;
					CircleParamsType* CircleParams;

					/** The acting "center", this orientation is played to transform in GetTransform and
						GetCurrentTransform, as an Actor. */
					AActor* CenterAsActor;

					/** The acting "center", this orientation is played to transform in GetTransform and
						GetCurrentTransform, as an Transform. */
					FTransform CenterAsTransform;

					int32 Index;

					TArray<FTransform> Transforms;

					int32 CurrentGroup;

					FImpl() :
						Spawner(nullptr),
						SpawnerAsActor(nullptr),
						CountType(PointCountType::TotalCount),
						Order(OrderType::Random),
						Params(nullptr),
						ShapeParams(nullptr),
						CircleParams(nullptr),
						CenterAsActor(nullptr),
						CenterAsTransform(FTransform::Identity),
						Index(0),
						Transforms(),
						CurrentGroup(INDEX_NONE)
					{
					}

					~FImpl(){}

				// ImplType (NCsSpawner::NPoint::IImpl)
				#pragma region
				public:

					void SetSpawner(ICsSpawner* InSpawner);

					void SetCountType(const PointCountType& InCountType) { CountType = InCountType; }

					void SetOrderType(const OrderType& InOrder) { Order = InOrder; }

					void SetParams(ParamsType* InParams);

					void SetCenter(AActor* Center);

					void SetCenter(const FTransform& Center);

					void Prepare();

					void Advance(const int32& Count, const int32& Group, const int32& CountPerGroup);

					FTransform GetTransform(const int32& Count, const int32& Group, const int32& CountPerGroup) const;

					FTransform GetCurrentTransform() const;

				#pragma endregion ImplType (NCsSpawner::NPoint::IImpl)

				public:

					FVector GenerateRandomLocation() const;

					FVector GetCenterLocation() const;

					static void Deconstruct(void* Ptr)
					{
						delete static_cast<NCsSpawner::NPoint::NShape::NCircle::FImpl*>(Ptr);
					}

				#undef PointCountType
				#undef OrderType
				#undef ParamsType
				#undef ShapeParamsType
				#undef CircleParamsType
				};

			#undef ImplType
			}
		}
	}
}