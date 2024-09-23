// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Params/Shape/CsSpawnerParams_ShapeCircleImpl.h"

// Types
#include "CsMacro_Misc.h"
// Library
#include "Library/CsLibrary_Valid.h"
// Container
#include "Containers/CsInterfaceMap.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsSpawnerParams_ShapeCircleImpl)

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
	Params->SetTotalTime(TotalTime);
	Params->SetShape((NCsSpawner::EShape)Shape);
	Params->SetCenter((NCsSpawner::NShape::ECenter)Center);
	Params->SetDistribution((NCsSpawner::EDistribution)Distribution);
	Params->SetMinRadius(MinRadius);
	Params->SetMaxRadius(MaxRadius);
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
					CS_CTOR_INIT_MEMBER_WITH_PROXY(TotalTime, 0.0f),
					// ShapeParamsType (NCsSpawner::NParams::NShape::IShape)
					CS_CTOR_INIT_MEMBER_WITH_PROXY(Shape, ShapeType::Circle),
					CS_CTOR_INIT_MEMBER_WITH_PROXY(Center, CenterType::Self),
					CS_CTOR_INIT_MEMBER_WITH_PROXY(Distribution, DistributionType::Uniform),
					// CircleParamsType (NCsSpawner::NParams::NShape::ICircle)
					CS_CTOR_INIT_MEMBER_WITH_PROXY(MinRadius, 0.0f),
					CS_CTOR_INIT_MEMBER_WITH_PROXY(MaxRadius, 0.0f)
				{
					InterfaceMap = new FCsInterfaceMap();

					InterfaceMap->SetRoot<FImpl>(this);

					typedef NCsSpawner::NParams::IParams ParamsType;
					typedef NCsSpawner::NParams::NShape::IShape ShapeParamsType;
					typedef NCsSpawner::NParams::NShape::ICircle CircleParamsType;

					InterfaceMap->Add<ParamsType>(static_cast<ParamsType*>(this));
					InterfaceMap->Add<ShapeParamsType>(static_cast<ShapeParamsType*>(this));
					InterfaceMap->Add<CircleParamsType>(static_cast<CircleParamsType*>(this));

					CS_CTOR_SET_MEMBER_PROXY(TotalTime);
					CS_CTOR_SET_MEMBER_PROXY(Shape);
					CS_CTOR_SET_MEMBER_PROXY(Center);
					CS_CTOR_SET_MEMBER_PROXY(Distribution);
					CS_CTOR_SET_MEMBER_PROXY(MinRadius);
					CS_CTOR_SET_MEMBER_PROXY(MaxRadius);
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

					checkf(GetShape() == ShapeType::Circle, TEXT("%s: GetShape(): %s is NOT Circle (ShapeType::Circle)."), *Context, ShapeMapType::Get().ToChar(GetShape()));

					typedef NCsSpawner::NShape::EMCenter CenterMapType;
					typedef NCsSpawner::EMDistribution DistributionMapType;

					CS_IS_ENUM_STRUCT_VALID_CHECKED(CenterMapType, GetCenter())
					CS_IS_ENUM_STRUCT_VALID_CHECKED(DistributionMapType, GetDistribution())
					CS_IS_FLOAT_GREATER_THAN_OR_EQUAL_CHECKED(GetMinRadius(), 0.0f)
					CS_IS_FLOAT_GREATER_THAN_CHECKED(GetMaxRadius(), 0.0f)
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

					if (GetShape() != ShapeType::Circle)
					{
						typedef NCsSpawner::EMShape ShapeMapType;

						CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: GetShape(): %s is NOT Circle (ShapeType::Circle)."), *Context, ShapeMapType::Get().ToChar(GetShape())));
						return false;
					}

					typedef NCsSpawner::NShape::EMCenter CenterMapType;
					typedef NCsSpawner::EMDistribution DistributionMapType;

					CS_IS_ENUM_VALID(CenterMapType, CenterType, GetCenter())
					CS_IS_ENUM_VALID(DistributionMapType, DistributionType, GetDistribution())
					CS_IS_FLOAT_GREATER_THAN_OR_EQUAL(GetMinRadius(), 0.0f)
					CS_IS_FLOAT_GREATER_THAN(GetMaxRadius(), 0.0f)
					return true;
				}

			#undef ShapeType
			#undef CenterType
			#undef DistributionType
			}
		}
	}
}