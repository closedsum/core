// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Material/CsTypes_Material.h"

// Library
#include "Material/CsLibrary_Material.h"
#include "Library/CsLibrary_Valid.h"

// FCsTArrayMaterialInterface
#pragma region

void FCsTArrayMaterialInterface::SetChecked(const FString& Context, UPrimitiveComponent* Component) const
{
	check(IsValidChecked(Context))

	CS_IS_PTR_NULL_CHECKED(Component)

	typedef NCsMaterial::FLibrary MaterialLibrary;

	MaterialLibrary::SetChecked(Context, Component, Materials_Internal);
}

bool FCsTArrayMaterialInterface::SetSafe(const FString& Context, UPrimitiveComponent* Component, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
{
	if (!IsValid(Context))
		return false;

	CS_IS_PTR_NULL(Component)

	typedef NCsMaterial::FLibrary MaterialLibrary;

	return MaterialLibrary::SetSafe(Context, Component, Materials_Internal, Log);
}

#pragma endregion FCsTArrayMaterialInterface

// FCsMaterialParameterFloat
#pragma region

bool FCsMaterialParameterFloat::IsValidChecked(const FString& Context) const
{
	CS_IS_NAME_NONE_CHECKED(Name)
	return true;
}
bool FCsMaterialParameterFloat::IsValid(const FString& Context, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const 
{
	CS_IS_NAME_NONE(Name)
	return true;
}

#pragma endregion FCsMaterialParameterFloat

// FCsMaterialParameterFloatRange
#pragma region

#define ParamsType NCsMaterial::NParameter::NFloat::FRange

void FCsMaterialParameterFloatRange::CopyToParams(ParamsType* Params)
{
	Params->SetName(&Name);
	Params->SetMin(&Min);
	Params->SetMax(&Max);
}

void FCsMaterialParameterFloatRange::CopyToParamsAsValue(ParamsType* Params) const
{
	Params->SetName(Name);
	Params->SetMin(Min);
	Params->SetMax(Max);
}

#undef ParamsType

bool FCsMaterialParameterFloatRange::IsValidChecked(const FString& Context) const
{
	CS_IS_NAME_NONE_CHECKED(Name)
	CS_IS_FLOAT_GREATER_THAN_OR_EQUAL_CHECKED(Max, Min)
	return true;
}
bool FCsMaterialParameterFloatRange::IsValid(const FString& Context, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
{
	CS_IS_NAME_NONE(Name)
	CS_IS_FLOAT_GREATER_THAN_OR_EQUAL(Max, Min)
	return true;
}

void FCsMaterialParameterFloatRange::SetChecked(const FString& Context, UMaterialInstanceDynamic* MID) const
{
	check(IsValidChecked(Context));

	typedef NCsMaterial::NMID::FLibrary MIDLibrary;

	MIDLibrary::SetScalarParameterValueChecked(Context, MID, Name, CalculateValue());
}

namespace NCsMaterial
{
	namespace NParameter
	{
		namespace NFloat
		{
			bool FRange::IsValidChecked(const FString& Context) const
			{
				CS_IS_NAME_NONE_CHECKED(GetName())
				CS_IS_FLOAT_GREATER_THAN_OR_EQUAL_CHECKED(GetMax(), GetMin())
				return true;
			}
			bool FRange::IsValid(const FString& Context, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
			{
				CS_IS_NAME_NONE(GetName())
				CS_IS_FLOAT_GREATER_THAN_OR_EQUAL(GetMax(), GetMin())
				return true;
			}

			void FRange::SetChecked(const FString& Context, UMaterialInstanceDynamic* MID) const
			{
				check(IsValidChecked(Context));

				typedef NCsMaterial::NMID::FLibrary MIDLibrary;

				MIDLibrary::SetScalarParameterValueChecked(Context, MID, GetName(), CalculateValue());
			}
		}
	}
}

#pragma endregion FCsMaterialParameterFloatRange

// FCsMaterialParameterColor
#pragma region

bool FCsMaterialParameterColor::IsValidChecked(const FString& Context) const
{
	CS_IS_NAME_NONE_CHECKED(Name)
	return true;
}
bool FCsMaterialParameterColor::IsValid(const FString& Context, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
{
	CS_IS_NAME_NONE(Name)
	return true;
}

#pragma endregion FCsMaterialParameterColor

// FCsMaterialParameterColorRange
#pragma region

bool FCsMaterialParameterColorRange::IsValidChecked(const FString& Context) const
{
	CS_IS_NAME_NONE_CHECKED(Name)
	return true;
}
bool FCsMaterialParameterColorRange::IsValid(const FString& Context, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
{
	CS_IS_NAME_NONE(Name)
	return true;
}

#pragma endregion FCsMaterialParameterColorRange

// FCsMaterialInterface_WithRangeParameters
#pragma region

#define MaterialType NCsMaterial::NInterface::FWithRangeParameters

void FCsMaterialInterface_WithRangeParameters::CopyToMaterial(MaterialType* Mat)
{
	Mat->SetMaterial(Material.GetPtr());

	// Float
	{
		typedef NCsMaterial::NParameter::NFloat::FRange ParamType;

		TArray<ParamType>* Params = Mat->GetFloatParametersPtr();

		const int32 Count = FloatParameters.Num();

		Params->Reset(Count);

		for (FCsMaterialParameterFloatRange& P : FloatParameters)
		{
			ParamType& Param = Params->AddDefaulted_GetRef();
			P.CopyToParams(&Param);
		}
	}
}

void FCsMaterialInterface_WithRangeParameters::CopyToMaterialAsValue(MaterialType* Mat) const
{
	Mat->SetMaterial(Material.Get());

	// Float
	{
		typedef NCsMaterial::NParameter::NFloat::FRange ParamType;

		TArray<ParamType>* Params = Mat->GetFloatParametersPtr();

		const int32 Count = FloatParameters.Num();

		Params->Reset(Count);

		for (const FCsMaterialParameterFloatRange& P : FloatParameters)
		{
			ParamType& Param = Params->AddDefaulted_GetRef();
			P.CopyToParamsAsValue(&Param);
		}
	}
}

#undef MaterialType

bool FCsMaterialInterface_WithRangeParameters::IsValidChecked(const FString& Context) const
{
	CS_IS_VALID_CHECKED(Material);

	for (const FCsMaterialParameterFloatRange& Param : FloatParameters)
	{
		CS_IS_VALID_CHECKED(Param);
	}
	return true;
}

bool FCsMaterialInterface_WithRangeParameters::IsValid(const FString& Context, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
{
	CS_IS_VALID(Material)

	for (const FCsMaterialParameterFloatRange& Param : FloatParameters)
	{
		CS_IS_VALID(Param)
	}
	return true;
}

void FCsMaterialInterface_WithRangeParameters::SetChecked(const FString& Context, UPrimitiveComponent* Component, const int32& Index, UMaterialInstanceDynamic*& OutMID) const
{
	check(IsValidChecked(Context));

	typedef NCsMaterial::NMID::FLibrary MIDLibrary;

	MIDLibrary::SetChecked(Context, Component, Material.GetChecked(Context), Index, OutMID);

	for (const FCsMaterialParameterFloatRange& Param : FloatParameters)
	{
		Param.SetChecked(Context, OutMID);
	}
}

namespace NCsMaterial
{
	namespace NInterface
	{
		bool FWithRangeParameters::IsValidChecked(const FString& Context) const
		{
			CS_IS_PTR_NULL_CHECKED(GetMaterial());

			typedef NCsMaterial::NParameter::NFloat::FRange FloatParameterType;

			for (const FloatParameterType& Param : GetFloatParameters())
			{
				CS_IS_VALID_CHECKED(Param);
			}
			return true;
		}

		bool FWithRangeParameters::IsValid(const FString& Context, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
		{
			CS_IS_PTR_NULL(GetMaterial());

			typedef NCsMaterial::NParameter::NFloat::FRange FloatParameterType;

			for (const FloatParameterType& Param : GetFloatParameters())
			{
				CS_IS_VALID(Param);
			}
			return true;
		}

		void FWithRangeParameters::SetChecked(const FString& Context, UPrimitiveComponent* Component, const int32& Index, UMaterialInstanceDynamic*& OutMID) const
		{
			check(IsValidChecked(Context));

			typedef NCsMaterial::NMID::FLibrary MIDLibrary;

			MIDLibrary::SetChecked(Context, Component, GetMaterial(), Index, OutMID);

			typedef NCsMaterial::NParameter::NFloat::FRange FloatParameterType;

			for (const FloatParameterType& Param : GetFloatParameters())
			{
				Param.SetChecked(Context, OutMID);
			}
		}
	}
}

#pragma endregion FCsMaterialInterface_WithRangeParameters