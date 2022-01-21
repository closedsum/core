// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Spawner/Params/CsSpawnerParamsImpl.h"

#include "Containers/CsInterfaceMap.h"

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
	check(CountParams.IsValidChecked(Context));

	check(FrequencyParams.IsValidChecked(Context));

	return true;
}

bool FCsSpawnerParamsImpl::IsValid(const FString& Context, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
{
	if (!CountParams.IsValid(Context, Log))
		return false;

	if (!FrequencyParams.IsValid(Context, Log))
		return false;

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
			check(CountParams.IsValidChecked(Context));

			check(FrequencyParams.IsValidChecked(Context));

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
			if (!CountParams.IsValid(Context, Log))
				return false;

			if (!FrequencyParams.IsValid(Context, Log))
				return false;

			return true;
		}
	}
}