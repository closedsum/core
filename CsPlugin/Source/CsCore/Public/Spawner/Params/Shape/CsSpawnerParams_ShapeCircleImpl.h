// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
// Spawner
#include "Spawner/Params/CsSpawnerParams.h"
#include "Spawner/Params/Shape/CsSpawnerParams_Shape.h"
#include "Spawner/Params/Shape/CsSpawnerParams_ShapeCircle.h"

#include "CsSpawnerParams_ShapeCircleImpl.generated.h"
#pragma once

// NCsSpawner::NParams::NShape::NCircle::FImpl
CS_FWD_DECLARE_STRUCT_NAMESPACE_4(NCsSpawner, NParams, NShape, NCircle, FImpl)

/**
* Spawn Parameters for a Spawner to describe how to spawn objects in a Circle
*/
USTRUCT(BlueprintType)
struct CSCORE_API FCsSpawnerParams_ShapeCircleImpl
{
	GENERATED_USTRUCT_BODY()

public:

// ParamsType (NCsSpawner::NParams::IParams)

	/** Parameters describing number (count) of objects "created" when Spawn is called. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Spawner|Params|Shape")
	FCsSpawnerCountParams CountParams;

	/** Parameters describing the frequency at which Spawn is called after calling Start. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Spawner|Params|Shape")
	FCsSpawnerFrequencyParams FrequencyParams;

	/** The total time the objects are being spawned for. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Spawner|Params|Shape")
	float TotalTime;

// ShapeParamsType (NCsSpawner::NParams::NShape::IShape)

	/** The shape / area of the spawner from which objects are spawned. 
		This defaults to Circle (ECsSpawnerShape::Circle). */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CsCore|Spawner|Params|Shape")
	ECsSpawnerShape Shape;

	/** Describe what is designed as the "center" of the spawner's shape. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Spawner|Params|Shape")
	ECsSpawnerShapeCenter Center;

	/** How the spawning is distributed over a shape / area. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Spawner|Params|Shape")
	ECsSpawnerDistribution Distribution;

// CircleParamsType (NCsSpawner::NParams::NShape::ICircle)

	/** Minimum radius of the circle. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Spawner|Params|Shape", meta = (UIMin = "0.0", ClampMin = "0.0", UIMax = "0.0", ClampMax = "0.0"))
	float MinRadius;

	/** Maximum radius of the circle. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Spawner|Params|Shape", meta = (UIMin = "0.0", ClampMin = "0.0", UIMax = "0.0", ClampMax = "0.0"))
	float MaxRadius;

	FCsSpawnerParams_ShapeCircleImpl() :
		// ParamsType (NCsSpawner::NParams::IParams)
		CountParams(),
		FrequencyParams(),
		TotalTime(0.0f),
		// ShapeParamsType (NCsSpawner::NParams::NShape::IShape)
		Shape(ECsSpawnerShape::Circle),
		Center(ECsSpawnerShapeCenter::Self),
		Distribution(ECsSpawnerDistribution::Uniform),
		// CircleParamsType (NCsSpawner::NParams::NShape::ICircle)
		MinRadius(0.0f),
		MaxRadius(0.0f)
	{
	}

	void Update()
	{
		FrequencyParams.Update();
	}

#define ParamsType NCsSpawner::NParams::NShape::NCircle::FImpl
	ParamsType* ConstructParamsImpl() const;
	void CopyToParamsAsValue(ParamsType* Params) const;
#undef ParamsType

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const;
};

struct FCsInterfaceMap;

namespace NCsSpawner
{
	namespace NParams
	{
		namespace NShape
		{
			namespace NCircle
			{
			#define ParamsType NCsSpawner::NParams::IParams
			#define ShapeParamsType NCsSpawner::NParams::NShape::IShape
			#define CircleParamsType NCsSpawner::NParams::NShape::ICircle

				/**
				* Spawn Parameters for a Spawner to describe how to spawn objects in a Circle
				*/
				struct CSCORE_API FImpl final : public ParamsType,
												public ShapeParamsType,
												public CircleParamsType
				{
				public:

					static const FName Name;

				#define CountParamsType NCsSpawner::NParams::FCount
				#define FrequencyParamsType NCsSpawner::NParams::FFrequency
				#define ShapeType NCsSpawner::EShape
				#define CenterType NCsSpawner::NShape::ECenter
				#define DistributionType NCsSpawner::EDistribution

				private:

					FCsInterfaceMap* InterfaceMap;

				public:

				// ParamsType (NCsSpawner::NParams::IParams)

					/** Parameters describing number (count) of objects "created" when Spawn is called. */
					CountParamsType CountParams;

					/** Parameters describing the frequency at which Spawn is called after calling Start. */
					FrequencyParamsType FrequencyParams;

					/** The total time the objects are being spawned for. */
					float TotalTime;

				// ShapeParamsType (NCsSpawner::NParams::NShape::IShape)

					/** The shape / area of the spawner from which objects are spawned. 
						This defaults to Circle (NCsSpawner::EShape::Circle). */
					ShapeType Shape;

					/** Describe what is designed as the "center" of the spawner's shape. */
					CenterType Center;

					/** How the spawning is distributed over a shape / area. */
					DistributionType Distribution;

				// CircleParamsType (NCsSpawner::NParams::NShape::ICircle)

					/** Minimum radius of the circle. */
					float MinRadius;

					/** Maximum radius of the circle. */
					float MaxRadius;

				public:

					FImpl();
					~FImpl();

				// ICsGetInterfaceMap
				#pragma region
				public:

					FORCEINLINE FCsInterfaceMap* GetInterfaceMap() const { return InterfaceMap; }

				#pragma endregion ICsGetInterfaceMap

				public:

					FORCEINLINE CountParamsType* GetCountParamsPtr() { return &CountParams; }
					FORCEINLINE FrequencyParamsType* GetFrequencyParamsPtr() { return &FrequencyParams; }
					FORCEINLINE float* GetTotalTimePtr() { return &TotalTime; }

				// ParamsType (NCsSpawner::NParams::IParams)
				#pragma region
				public:

					FORCEINLINE const CountParamsType& GetCountParams() const { return CountParams; }
					FORCEINLINE const FrequencyParamsType& GetFrequencyParams() const { return FrequencyParams; }
					FORCEINLINE const float& GetTotalTime() const { return TotalTime; }

				#pragma endregion ParamsType (NCsSpawner::NParams::IParams)

				public:

					FORCEINLINE ShapeType* GetShapeTypePtr() { return &Shape; }
					FORCEINLINE CenterType* GetCenterTypePtr() { return &Center; }
					FORCEINLINE DistributionType* GetDistributionTypePtr() { return &Distribution; }

				// ShapeParamsType (NCsSpawner::NParams::NShape::IShape)
				#pragma region
				public:

					FORCEINLINE const ShapeType& GetShapeType() const { return Shape; }
					FORCEINLINE const CenterType& GetCenterType() const { return Center; }
					FORCEINLINE const DistributionType& GetDistributionType() const { return Distribution; }

				#pragma endregion ShapeParamsType (NCsSpawner::NParams::NShape::IShape)

				public:

					FORCEINLINE float* GetMinRadiusPtr() { return &MinRadius; }
					FORCEINLINE float* GetMaxRadiusPtr() { return &MaxRadius; }

				// CircleParamsType (NCsSpawner::NParams::NShape::ICircle)
				#pragma region
				public:

					FORCEINLINE const float& GetMinRadius() const { return MinRadius; }
					FORCEINLINE const float& GetMaxRadius() const { return MaxRadius; }

				#pragma endregion CircleParamsType (NCsSpawner::NParams::NShape::ICircle)
				public:

					static void Deconstruct(void* Ptr)
					{
						delete static_cast<NCsSpawner::NParams::NShape::NCircle::FImpl*>(Ptr);
					}

					bool IsValidChecked(const FString& Context) const;
					static bool IsValidChecked(const FString& Context, ParamsType* Params);
					bool IsValid(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const;

				#undef CountParamsType
				#undef FrequencyParamsType
				#undef ShapeType
				};

			#undef ParamsType
			#undef ShapeParamsType
			#undef CircleParamsType
			}
		}
	}
}