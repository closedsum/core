// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Params/CsSpawnerParamsImpl.h"

// Library
#include "Library/CsLibrary_Valid.h"
// Containers
#include "Containers/CsInterfaceMap.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsSpawnerParamsImpl)

#define ParamsType NCsSpawner::NParams::FImpl

ParamsType* FCsSpawnerParamsImpl::ConstructParamsImpl() const
{
	ParamsType* Params = new ParamsType();

	CopyToParamsAsValue(Params);
	return Params;
}

void FCsSpawnerParamsImpl::CopyToParamsAsValue(ParamsType* Params) const
{
	CountParams.CopyToParamsAsValue(Params->GetCountParamsPtr());
	FrequencyParams.CopyToParamsAsValue(Params->GetFrequencyParamsPtr());
	Params->TotalTime = TotalTime;
}

#undef ParamsType

bool FCsSpawnerParamsImpl::IsValidChecked(const FString& Context) const
{
	CS_IS_VALID_CHECKED(CountParams);
	CS_IS_VALID_CHECKED(FrequencyParams);
	return true;
}

bool FCsSpawnerParamsImpl::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsSpawner::FLog::Warning*/) const
{
	CS_IS_VALID(CountParams)
	CS_IS_VALID(FrequencyParams)
	return true;
}

const FName NCsSpawner::NParams::FImpl::Name = FName("NCsSpawner::NParams::FImpl");;

namespace NCsSpawner
{
	namespace NParams
	{
		FImpl::FImpl() :
			// ICsGetInterfaceMap
			InterfaceMap(nullptr),
			// ParamsType (NCsSpawner::NParams::IParams)
			CountParams(),
			FrequencyParams(),
			TotalTime(0.0f)
		{
			InterfaceMap = new FCsInterfaceMap();

			InterfaceMap->SetRoot<FImpl>(this);

			typedef NCsSpawner::NParams::IParams ParamsType;

			InterfaceMap->Add<ParamsType>(static_cast<ParamsType*>(this));
		}

		FImpl::~FImpl()
		{
			delete InterfaceMap;
		}

		bool FImpl::IsValidChecked(const FString& Context) const
		{
			CS_IS_VALID_CHECKED(CountParams);
			CS_IS_VALID_CHECKED(FrequencyParams);
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

		bool FImpl::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsSpawner::FLog::Warning*/) const
		{
			CS_IS_VALID(CountParams)
			CS_IS_VALID(FrequencyParams)
			return true;
		}
	}
}