// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Spawner/Params/Shape/CsSpawnerParams_ShapeCircleImpl.h"

// Library
#include "Library/CsLibrary_Valid.h"
// Container
#include "Containers/CsInterfaceMap.h"

#define ParamsType NCsSpawner::NParams::NShape::NCircle::FImpl

ParamsType* FCsSpawnerParams_ShapeCircleImpl::ConstructParamsImpl() const
{
	ParamsType* Params = new ParamsType();

	CopyToParamsAsValue(Params);
	return Params;
}

void FCsSpawnerParams_ShapeCircleImpl::CopyToParamsAsValue(ParamsType* Params) const
{
	CountParams.CopyToParamsAsValue(Params->GetCountParamsPtr());
	FrequencyParams.CopyToParamsAsValue(Params->GetFrequencyParamsPtr());
	Params->TotalTime = TotalTime;
	Params->Shape = (NCsSpawner::EShape)Shape;
	Params->Center = (NCsSpawner::NShape::ECenter)Center;
	Params->Distribution = (NCsSpawner::EDistribution)Distribution;
	Params->MinRadius = MinRadius;
	Params->MaxRadius = MaxRadius;
}

#undef ParamsType

bool FCsSpawnerParams_ShapeCircleImpl::IsValidChecked(const FString& Context) const
{
	CS_IS_VALID_CHECKED(CountParams);

	CS_IS_VALID_CHECKED(FrequencyParams);

	checkf(Shape == ECsSpawnerShape::Circle, TEXT("%s: Shape: %s is NOT Circle (ECsSpawnerShape::Circle)."), *Context, EMCsSpawnerShape::Get().ToChar(Shape));

	CS_IS_ENUM_STRUCT_VALID_CHECKED(EMCsSpawnerShapeCenter, Center)

	CS_IS_ENUM_STRUCT_VALID_CHECKED(EMCsSpawnerDistribution, Distribution)

	CS_IS_FLOAT_GREATER_THAN_OR_EQUAL_CHECKED(MinRadius, 0.0f)

	CS_IS_FLOAT_GREATER_THAN_CHECKED(MaxRadius, 0.0f)

	return true;
}

bool FCsSpawnerParams_ShapeCircleImpl::IsValid(const FString& Context, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
{
	CS_IS_VALID(CountParams)

	CS_IS_VALID(FrequencyParams)

	if (Shape != ECsSpawnerShape::Circle)
	{
		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Shape: %s is NOT Circle (ECsSpawnerShape::Circle)."), *Context, EMCsSpawnerShape::Get().ToChar(Shape)));
		return false;
	}

	CS_IS_ENUM_VALID(EMCsSpawnerShapeCenter, ECsSpawnerShapeCenter, Center)

	CS_IS_ENUM_VALID(EMCsSpawnerDistribution, ECsSpawnerDistribution, Distribution)

	CS_IS_FLOAT_GREATER_THAN_OR_EQUAL(MinRadius, 0.0f)

	CS_IS_FLOAT_GREATER_THAN(MaxRadius, 0.0f)

	return true;
}

const FName NCsSpawner::NParams::NShape::NCircle::FImpl::Name = FName("NCsSpawner::NParams::NShape::NCircle::FImpl");;

namespace NCsSpawner
{
	namespace NParams
	{
		namespace NShape
		{
			namespace NCircle
			{
			#define ShapeType NCsSpawner::EShape
			#define CenterType NCsSpawner::NShape::ECenter
			#define DistributionType NCsSpawner::EDistribution

				FImpl::FImpl() :
					// ICsGetInterfaceMap
					InterfaceMap(nullptr),
					// ParamsType (NCsSpawner::NParams::IParams)
					CountParams(),
					FrequencyParams(),
					TotalTime(0.0f),
					// ShapeParamsType (NCsSpawner::NParams::NShape::IShape)
					Shape(ShapeType::Circle),
					Center(CenterType::Self),
					Distribution(DistributionType::Uniform),
					// CircleParamsType (NCsSpawner::NParams::NShape::ICircle)
					MinRadius(0.0f),
					MaxRadius(0.0f)
				{
					InterfaceMap = new FCsInterfaceMap();

					InterfaceMap->SetRoot<FImpl>(this);

					typedef NCsSpawner::NParams::IParams ParamsType;
					typedef NCsSpawner::NParams::NShape::IShape ShapeParamsType;
					typedef NCsSpawner::NParams::NShape::ICircle CircleParamsType;

					InterfaceMap->Add<ParamsType>(static_cast<ParamsType*>(this));
					InterfaceMap->Add<ShapeParamsType>(static_cast<ShapeParamsType*>(this));
					InterfaceMap->Add<CircleParamsType>(static_cast<CircleParamsType*>(this));
				}

				FImpl::~FImpl()
				{
					delete InterfaceMap;
				}

				bool FImpl::IsValidChecked(const FString& Context) const
				{
					CS_IS_VALID_CHECKED(CountParams);

					CS_IS_VALID_CHECKED(FrequencyParams);

					typedef NCsSpawner::EMShape ShapeMapType;

					checkf(Shape == ShapeType::Circle, TEXT("%s: Shape: %s is NOT Circle (ShapeType::Circle)."), *Context, ShapeMapType::Get().ToChar(Shape));

					typedef NCsSpawner::NShape::EMCenter CenterMapType;
					typedef NCsSpawner::EMDistribution DistributionMapType;

					CS_IS_ENUM_STRUCT_VALID_CHECKED(CenterMapType, Center)

					CS_IS_ENUM_STRUCT_VALID_CHECKED(DistributionMapType, Distribution)

					CS_IS_FLOAT_GREATER_THAN_OR_EQUAL_CHECKED(MinRadius, 0.0f)

					CS_IS_FLOAT_GREATER_THAN_CHECKED(MaxRadius, 0.0f)
					return true;
				}

				#define ParamsType NCsSpawner::NParams::IParams
				/*static*/ bool FImpl::IsValidChecked(const FString& Context, ParamsType* Params)
				{
					FCsInterfaceMap* Map = Params->GetInterfaceMap();
					FImpl* P			 = Map->PureStaticCastChecked<FImpl, ParamsType>(Context, Params);
					check(P->IsValidChecked(Context));
					return true;
				}
				#undef ParamsType

				bool FImpl::IsValid(const FString& Context, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
				{
					CS_IS_VALID(CountParams)

					CS_IS_VALID(FrequencyParams)

					if (Shape != ShapeType::Circle)
					{
						typedef NCsSpawner::EMShape ShapeMapType;

						CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Shape: %s is NOT Circle (ShapeType::Circle)."), *Context, ShapeMapType::Get().ToChar(Shape)));
						return false;
					}

					typedef NCsSpawner::NShape::EMCenter CenterMapType;
					typedef NCsSpawner::EMDistribution DistributionMapType;

					CS_IS_ENUM_VALID(CenterMapType, CenterType, Center)

					CS_IS_ENUM_VALID(DistributionMapType, DistributionType, Distribution)

					CS_IS_FLOAT_GREATER_THAN_OR_EQUAL(MinRadius, 0.0f)

					CS_IS_FLOAT_GREATER_THAN(MaxRadius, 0.0f)
					return true;
				}

			#undef ShapeType
			#undef CenterType
			#undef DistributionType
			}
		}
	}
}