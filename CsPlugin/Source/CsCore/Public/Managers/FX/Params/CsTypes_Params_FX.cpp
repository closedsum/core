// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/FX/Params/CsTypes_Params_FX.h"

#include "Managers/FX/Params/CsParams_FX.h"

// FXParameterValue
#pragma region

namespace NCsFXParameterValue
{
	namespace Ref
	{
		typedef EMCsFXParameterValue EnumMapType;

		CSCORE_API CS_ADD_TO_ENUM_MAP(Float);
		CSCORE_API CS_ADD_TO_ENUM_MAP(Vector);
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsFXParameterValue_MAX, "MAX");
	}

	CSCORE_API const uint8 MAX = (uint8)Type::ECsFXParameterValue_MAX;
}

#pragma endregion FXParameterValue

// FCsFXParameterVector
#pragma region

#define ParameterType NCsFX::NParameter::NVector::FVectorTypeEmu
void FCsFXParameterVector::CopyParams(ParameterType* Params)
{
#undef ParameterType

	Params->SetName(&Name);
	Params->SetValue(&Value);
}

#pragma endregion FCsFXParameterVector