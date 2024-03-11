// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Material/CsTypes_Material.h"

// Library
#include "Material/CsLibrary_Material.h"
#include "Library/CsLibrary_Valid.h"
// Material
#include "Materials/MaterialInterface.h"

// FCsMaterialInterface
#pragma region

 UMaterialInterface* FCsMaterialInterface::LoadChecked(const FString& Context)
{
	CS_IS_SOFT_OBJECT_PTR_VALID_CHECKED(Material, UMaterialInterface)

	Material_Internal = Material.LoadSynchronous();

	checkf(Material_Internal, TEXT("%s: Material has NOT been loaded from Path @ %s."), *Context, *(Material.ToSoftObjectPath().ToString()));
	return Material_Internal;
}

UMaterialInterface* FCsMaterialInterface::SafeLoad(const FString& Context, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
{
	CS_IS_SOFT_OBJECT_PTR_VALID_RET_NULL(Material, UMaterialInterface)

	Material_Internal = Material.LoadSynchronous();

	if (!Material_Internal)
	{
		if (Log)
			Log(FString::Printf(TEXT("%s: Material has NOT been loaded from Path @ %s."), *Context, *(Material.ToSoftObjectPath().ToString())));
	}
	return Material_Internal;
}

#pragma endregion FCsMaterialInterface

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

#define ParamsType NCsMaterial::NParameter::NFloat::FValue

void FCsMaterialParameterFloat::CopyToParams(ParamsType* Params)
{
	Params->SetName(&Name);
	Params->SetValue(&Value);
}

void FCsMaterialParameterFloat::CopyToParamsAsValue(ParamsType* Params) const
{
	Params->SetName(Name);
	Params->SetValue(Value);
}

#undef ParamsType

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

bool FCsMaterialParameterFloat::IsValidChecked(const FString& Context, UMaterialInterface* Material) const
{
	check(IsValidChecked(Context));

	typedef NCsMaterial::FLibrary MaterialLibrary;

	return MaterialLibrary::IsScalarParameterValidChecked(Context, Material, Name);
}

bool FCsMaterialParameterFloat::IsValid(const FString& Context, UMaterialInterface* Material, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
{
	if (!IsValid(Context, Log))
		return false;

	typedef NCsMaterial::FLibrary MaterialLibrary;

	return MaterialLibrary::IsScalarParameterValid(Context, Material, Name, Log);
}

void FCsMaterialParameterFloat::SetChecked(const FString& Context, UMaterialInstanceDynamic* MID) const
{
	check(IsValidChecked(Context));

	typedef NCsMaterial::NMID::FLibrary MIDLibrary;

	MIDLibrary::SetScalarParameterValueChecked(Context, MID, Name, Value);
}

bool FCsMaterialParameterFloat::SetSafe(const FString& Context, UMaterialInstanceDynamic* MID, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
{
	if (!IsValid(Context, Log))
		return false;

	typedef NCsMaterial::NMID::FLibrary MIDLibrary;

	return MIDLibrary::SetSafeScalarParameterValue(Context, MID, Name, Value, Log);
}

namespace NCsMaterial
{
	namespace NParameter
	{
		namespace NFloat
		{
			bool FValue::IsValidChecked(const FString& Context) const
			{
				CS_IS_NAME_NONE_CHECKED(GetName())
				return true;
			}

			bool FValue::IsValid(const FString& Context, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
			{
				CS_IS_NAME_NONE(GetName())
				return true;
			}

			bool FValue::IsValidChecked(const FString& Context, UMaterialInterface* Material) const
			{
				check(IsValidChecked(Context));

				typedef NCsMaterial::FLibrary MaterialLibrary;

				return MaterialLibrary::IsScalarParameterValidChecked(Context, Material, GetName());
			}

			bool FValue::IsValid(const FString& Context, UMaterialInterface* Material, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
			{
				if (!IsValid(Context, Log))
					return false;

				typedef NCsMaterial::FLibrary MaterialLibrary;

				return MaterialLibrary::IsScalarParameterValid(Context, Material, GetName(), Log);
			}

			void FValue::SetChecked(const FString& Context, UMaterialInstanceDynamic* MID) const
			{
				check(IsValidChecked(Context));

				typedef NCsMaterial::NMID::FLibrary MIDLibrary;

				MIDLibrary::SetScalarParameterValueChecked(Context, MID, GetName(), GetValue());
			}

			bool FValue::SetSafe(const FString& Context, UMaterialInstanceDynamic* MID, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
			{
				if (!IsValid(Context, Log))
					return false;

				typedef NCsMaterial::NMID::FLibrary MIDLibrary;

				return MIDLibrary::SetSafeScalarParameterValue(Context, MID, GetName(), GetValue(), Log);
			}
		}
	}
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

bool FCsMaterialParameterFloatRange::IsValidChecked(const FString& Context, UMaterialInterface* Material) const
{
	check(IsValidChecked(Context));

	typedef NCsMaterial::FLibrary MaterialLibrary;

	return MaterialLibrary::IsScalarParameterValidChecked(Context, Material, Name);
}

bool FCsMaterialParameterFloatRange::IsValid(const FString& Context, UMaterialInterface* Material, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
{
	if (!IsValid(Context, Log))
		return false;

	typedef NCsMaterial::FLibrary MaterialLibrary;

	return MaterialLibrary::IsScalarParameterValid(Context, Material, Name, Log);
}

void FCsMaterialParameterFloatRange::SetChecked(const FString& Context, UMaterialInstanceDynamic* MID) const
{
	check(IsValidChecked(Context));

	typedef NCsMaterial::NMID::FLibrary MIDLibrary;

	MIDLibrary::SetScalarParameterValueChecked(Context, MID, Name, CalculateValue());
}

bool FCsMaterialParameterFloatRange::SetSafe(const FString& Context, UMaterialInstanceDynamic* MID, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
{
	if (!IsValid(Context, Log))
		return false;

	typedef NCsMaterial::NMID::FLibrary MIDLibrary;

	return MIDLibrary::SetSafeScalarParameterValue(Context, MID, Name, CalculateValue(), Log);
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

			bool FRange::IsValidChecked(const FString& Context, UMaterialInterface* Material) const
			{
				check(IsValidChecked(Context));

				typedef NCsMaterial::FLibrary MaterialLibrary;

				return MaterialLibrary::IsScalarParameterValidChecked(Context, Material, GetName());
			}

			bool FRange::IsValid(const FString& Context, UMaterialInterface* Material, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
			{
				if (!IsValid(Context, Log))
					return false;

				typedef NCsMaterial::FLibrary MaterialLibrary;

				return MaterialLibrary::IsScalarParameterValid(Context, Material, GetName(), Log);
			}

			void FRange::SetChecked(const FString& Context, UMaterialInstanceDynamic* MID) const
			{
				check(IsValidChecked(Context));

				typedef NCsMaterial::NMID::FLibrary MIDLibrary;

				MIDLibrary::SetScalarParameterValueChecked(Context, MID, GetName(), CalculateValue());
			}

			bool FRange::SetSafe(const FString& Context, UMaterialInstanceDynamic* MID, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
			{
				if (!IsValid(Context, Log))
					return false;

				typedef NCsMaterial::NMID::FLibrary MIDLibrary;

				return MIDLibrary::SetSafeScalarParameterValue(Context, MID, GetName(), CalculateValue(), Log);
			}
		}
	}
}

#pragma endregion FCsMaterialParameterFloatRange

// FCsMaterialParameterColor
#pragma region

#define ParamsType NCsMaterial::NParameter::NColor::FValue

void FCsMaterialParameterColor::CopyToParams(ParamsType* Params)
{
	Params->SetName(&Name);
	Params->SetValue(&Value);
}

void FCsMaterialParameterColor::CopyToParamsAsValue(ParamsType* Params) const
{
	Params->SetName(Name);
	Params->SetValue(Value);
}

#undef ParamsType

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

bool FCsMaterialParameterColor::IsValidChecked(const FString& Context, UMaterialInterface* Material) const
{
	check(IsValidChecked(Context));

	typedef NCsMaterial::FLibrary MaterialLibrary;

	return MaterialLibrary::IsVectorParameterValidChecked(Context, Material, Name);
}

bool FCsMaterialParameterColor::IsValid(const FString& Context, UMaterialInterface* Material, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
{
	if (!IsValid(Context, Log))
		return false;

	typedef NCsMaterial::FLibrary MaterialLibrary;

	return MaterialLibrary::IsVectorParameterValid(Context, Material, Name, Log);
}

void FCsMaterialParameterColor::SetChecked(const FString& Context, UMaterialInstanceDynamic* MID) const
{
	check(IsValidChecked(Context));

	typedef NCsMaterial::NMID::FLibrary MIDLibrary;

	MIDLibrary::SetVectorParameterValueChecked(Context, MID, Name, Value);
}

bool FCsMaterialParameterColor::SetSafe(const FString& Context, UMaterialInstanceDynamic* MID, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
{
	if (!IsValid(Context, Log))
		return false;

	typedef NCsMaterial::NMID::FLibrary MIDLibrary;

	return MIDLibrary::SetSafeVectorParameterValue(Context, MID, Name, Value, Log);
}

namespace NCsMaterial
{
	namespace NParameter
	{
		namespace NColor
		{
			bool FValue::IsValidChecked(const FString& Context) const
			{
				CS_IS_NAME_NONE_CHECKED(GetName())
				return true;
			}

			bool FValue::IsValid(const FString& Context, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
			{
				CS_IS_NAME_NONE(GetName())
				return true;
			}

			bool FValue::IsValidChecked(const FString& Context, UMaterialInterface* Material) const
			{
				check(IsValidChecked(Context));

				typedef NCsMaterial::FLibrary MaterialLibrary;

				return MaterialLibrary::IsVectorParameterValidChecked(Context, Material, GetName());
			}

			bool FValue::IsValid(const FString& Context, UMaterialInterface* Material, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
			{
				if (!IsValid(Context, Log))
					return false;

				typedef NCsMaterial::FLibrary MaterialLibrary;

				return MaterialLibrary::IsVectorParameterValid(Context, Material, GetName(), Log);
			}

			void FValue::SetChecked(const FString& Context, UMaterialInstanceDynamic* MID) const
			{
				check(IsValidChecked(Context));

				typedef NCsMaterial::NMID::FLibrary MIDLibrary;

				MIDLibrary::SetVectorParameterValueChecked(Context, MID, GetName(), GetValue());
			}

			bool FValue::SetSafe(const FString& Context, UMaterialInstanceDynamic* MID, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
			{
				if (!IsValid(Context, Log))
					return false;

				typedef NCsMaterial::NMID::FLibrary MIDLibrary;

				return MIDLibrary::SetSafeVectorParameterValue(Context, MID, GetName(), GetValue(), Log);
			}
		}
	}
}

#pragma endregion FCsMaterialParameterColor

// FCsMaterialParameterColorRange
#pragma region

#define ParamsType NCsMaterial::NParameter::NColor::FRange

void FCsMaterialParameterColorRange::CopyToParams(ParamsType* Params)
{
	Params->SetName(&Name);
	Params->SetFrom(&From);
	Params->SetTo(&To);
}

void FCsMaterialParameterColorRange::CopyToParamsAsValue(ParamsType* Params) const
{
	Params->SetName(Name);
	Params->SetFrom(From);
	Params->SetTo(To);
}

#undef ParamsType

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

bool FCsMaterialParameterColorRange::IsValidChecked(const FString& Context, UMaterialInterface* Material) const
{
	check(IsValidChecked(Context));

	typedef NCsMaterial::FLibrary MaterialLibrary;

	return MaterialLibrary::IsVectorParameterValidChecked(Context, Material, Name);
}

bool FCsMaterialParameterColorRange::IsValid(const FString& Context, UMaterialInterface* Material, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
{
	if (!IsValid(Context, Log))
		return false;

	typedef NCsMaterial::FLibrary MaterialLibrary;

	return MaterialLibrary::IsVectorParameterValid(Context, Material, Name, Log);
}

void FCsMaterialParameterColorRange::SetChecked(const FString& Context, UMaterialInstanceDynamic* MID) const
{
	check(IsValidChecked(Context));

	typedef NCsMaterial::NMID::FLibrary MIDLibrary;

	MIDLibrary::SetVectorParameterValueChecked(Context, MID, Name, CalculateValue());
}

bool FCsMaterialParameterColorRange::SetSafe(const FString& Context, UMaterialInstanceDynamic* MID, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
{
	if (!IsValid(Context, Log))
		return false;

	typedef NCsMaterial::NMID::FLibrary MIDLibrary;

	return MIDLibrary::SetSafeVectorParameterValue(Context, MID, Name, CalculateValue(), Log);
}

namespace NCsMaterial
{
	namespace NParameter
	{
		namespace NColor
		{
			bool FRange::IsValidChecked(const FString& Context) const
			{
				CS_IS_NAME_NONE_CHECKED(GetName())
				return true;
			}

			bool FRange::IsValid(const FString& Context, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
			{
				CS_IS_NAME_NONE(GetName())
				return true;
			}

			bool FRange::IsValidChecked(const FString& Context, UMaterialInterface* Material) const
			{
				check(IsValidChecked(Context));

				typedef NCsMaterial::FLibrary MaterialLibrary;

				return MaterialLibrary::IsVectorParameterValidChecked(Context, Material, GetName());
			}

			bool FRange::IsValid(const FString& Context, UMaterialInterface* Material, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
			{
				if (!IsValid(Context, Log))
					return false;

				typedef NCsMaterial::FLibrary MaterialLibrary;

				return MaterialLibrary::IsVectorParameterValid(Context, Material, GetName(), Log);
			}

			void FRange::SetChecked(const FString& Context, UMaterialInstanceDynamic* MID) const
			{
				check(IsValidChecked(Context));

				typedef NCsMaterial::NMID::FLibrary MIDLibrary;

				MIDLibrary::SetVectorParameterValueChecked(Context, MID, GetName(), CalculateValue());
			}

			bool FRange::SetSafe(const FString& Context, UMaterialInstanceDynamic* MID, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
			{
				if (!IsValid(Context, Log))
					return false;

				typedef NCsMaterial::NMID::FLibrary MIDLibrary;

				return MIDLibrary::SetSafeVectorParameterValue(Context, MID, GetName(), CalculateValue(), Log);
			}
		}
	}
}

#pragma endregion FCsMaterialParameterColorRange

// FCsMaterialInterface_WithParameters
#pragma region

#define MaterialType NCsMaterial::NInterface::FWithParameters

void FCsMaterialInterface_WithParameters::CopyToMaterial(MaterialType* Mat)
{
	Mat->SetMaterial(Material.GetPtr());

	// Float
	{
		typedef NCsMaterial::NParameter::NFloat::FValue ParamType;

		TArray<ParamType>* Params = Mat->GetFloatParametersPtr();

		const int32 Count = FloatParameters.Num();

		Params->Reset(Count);

		for (FCsMaterialParameterFloat& P : FloatParameters)
		{
			ParamType& Param = Params->AddDefaulted_GetRef();
			P.CopyToParams(&Param);
		}
	}
	// Color
	{
		typedef NCsMaterial::NParameter::NColor::FValue ParamType;

		TArray<ParamType>* Params = Mat->GetColorParametersPtr();

		const int32 Count = ColorParameters.Num();

		Params->Reset(Count);

		for (FCsMaterialParameterColor& P : ColorParameters)
		{
			ParamType& Param = Params->AddDefaulted_GetRef();
			P.CopyToParams(&Param);
		}
	}
}

void FCsMaterialInterface_WithParameters::CopyToMaterialAsValue(MaterialType* Mat) const
{
	Mat->SetMaterial(Material.Get());

	// Float
	{
		typedef NCsMaterial::NParameter::NFloat::FValue ParamType;

		TArray<ParamType>* Params = Mat->GetFloatParametersPtr();

		const int32 Count = FloatParameters.Num();

		Params->Reset(Count);

		for (const FCsMaterialParameterFloat& P : FloatParameters)
		{
			ParamType& Param = Params->AddDefaulted_GetRef();
			P.CopyToParamsAsValue(&Param);
		}
	}
	// Color
	{
		typedef NCsMaterial::NParameter::NColor::FValue ParamType;

		TArray<ParamType>* Params = Mat->GetColorParametersPtr();

		const int32 Count = ColorParameters.Num();

		Params->Reset(Count);

		for (const FCsMaterialParameterColor& P : ColorParameters)
		{
			ParamType& Param = Params->AddDefaulted_GetRef();
			P.CopyToParamsAsValue(&Param);
		}
	}
}

#undef MaterialType

bool FCsMaterialInterface_WithParameters::IsValidChecked(const FString& Context) const
{
	CS_IS_VALID_CHECKED(Material);
	// Float
	for (const FCsMaterialParameterFloat& Param : FloatParameters)
	{
		check(Param.IsValidChecked(Context, Material.Get()));
	}
	// Color
	for (const FCsMaterialParameterColor& Param : ColorParameters)
	{
		check(Param.IsValidChecked(Context, Material.Get()));
	}
	return true;
}

bool FCsMaterialInterface_WithParameters::IsValid(const FString& Context, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
{
	CS_IS_VALID(Material)
	// Float
	for (const FCsMaterialParameterFloat& Param : FloatParameters)
	{
		if (!Param.IsValid(Context, Material.Get(), Log))
			return false;
	}
	// Color
	for (const FCsMaterialParameterColor& Param : ColorParameters)
	{
		if (!Param.IsValid(Context, Material.Get(), Log))
			return false;
	}
	return true;
}

bool FCsMaterialInterface_WithParameters::IsTopValidChecked(const FString& Context) const
{
	CS_IS_TOP_VALID_CHECKED(Material);
	// Float
	for (const FCsMaterialParameterFloat& Param : FloatParameters)
	{
		check(Param.IsValidChecked(Context, Material.Get()));
	}
	// Color
	for (const FCsMaterialParameterColor& Param : ColorParameters)
	{
		check(Param.IsValidChecked(Context, Material.Get()));
	}
	return true;
}

bool FCsMaterialInterface_WithParameters::IsTopValid(const FString& Context, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
{
	CS_IS_TOP_VALID(Material)
	// Float
	for (const FCsMaterialParameterFloat& Param : FloatParameters)
	{
		if (!Param.IsValid(Context, Material.Get(), Log))
			return false;
	}
	// Color
	for (const FCsMaterialParameterColor& Param : ColorParameters)
	{
		if (!Param.IsValid(Context, Material.Get(), Log))
			return false;
	}
	return true;
}

void FCsMaterialInterface_WithParameters::SetChecked(const FString& Context, UPrimitiveComponent* Component, const int32& Index, UMaterialInstanceDynamic*& OutMID) const
{
	check(IsValidChecked(Context));

	typedef NCsMaterial::NMID::FLibrary MIDLibrary;

	MIDLibrary::SetChecked(Context, Component, Material.GetChecked(Context), Index, OutMID);
	// Float
	for (const FCsMaterialParameterFloat& Param : FloatParameters)
	{
		Param.SetChecked(Context, OutMID);
	}
	// Color
	for (const FCsMaterialParameterColor& Param : ColorParameters)
	{
		Param.SetChecked(Context, OutMID);
	}
}

bool FCsMaterialInterface_WithParameters::SetSafe(const FString& Context, UPrimitiveComponent* Component, const int32& Index, UMaterialInstanceDynamic*& OutMID, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
{
	if (!IsValid(Context, Log))
		return false;

	typedef NCsMaterial::NMID::FLibrary MIDLibrary;

	MIDLibrary::SetChecked(Context, Component, Material.GetChecked(Context), Index, OutMID);
	// Float
	for (const FCsMaterialParameterFloat& Param : FloatParameters)
	{
		if (!Param.SetSafe(Context, OutMID, Log))
			return false;
	}
	// Color
	for (const FCsMaterialParameterColor& Param : ColorParameters)
	{
		if (!Param.SetSafe(Context, OutMID, Log))
			return false;
	}
	return true;
}

namespace NCsMaterial
{
	namespace NInterface
	{
		bool FWithParameters::IsValidChecked(const FString& Context) const
		{
			CS_IS_PTR_NULL_CHECKED(GetMaterial());
			// Float
			typedef NCsMaterial::NParameter::NFloat::FValue FloatParameterType;

			for (const FloatParameterType& Param : GetFloatParameters())
			{
				check(Param.IsValidChecked(Context, GetMaterial()));
			}
			// Color
			typedef NCsMaterial::NParameter::NColor::FValue ColorParameterType;

			for (const ColorParameterType& Param : GetColorParameters())
			{
				check(Param.IsValidChecked(Context, GetMaterial()));
			}
			return true;
		}

		bool FWithParameters::IsValid(const FString& Context, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
		{
			CS_IS_PTR_NULL(GetMaterial());
			// Float
			typedef NCsMaterial::NParameter::NFloat::FValue FloatParameterType;

			for (const FloatParameterType& Param : GetFloatParameters())
			{
				if (!Param.IsValid(Context, GetMaterial(), Log))
					return false;
			}
			// Color
			typedef NCsMaterial::NParameter::NColor::FValue ColorParameterType;

			for (const ColorParameterType& Param : GetColorParameters())
			{
				if (!Param.IsValid(Context, GetMaterial(), Log))
					return false;
			}
			return true;
		}

		void FWithParameters::SetChecked(const FString& Context, UPrimitiveComponent* Component, const int32& Index, UMaterialInstanceDynamic*& OutMID) const
		{
			check(IsValidChecked(Context));

			typedef NCsMaterial::NMID::FLibrary MIDLibrary;

			MIDLibrary::SetChecked(Context, Component, GetMaterial(), Index, OutMID);
			// Float
			typedef NCsMaterial::NParameter::NFloat::FValue FloatParameterType;
			
			for (const FloatParameterType& Param : GetFloatParameters())
			{
				Param.SetChecked(Context, OutMID);
			}
			// Color
			typedef NCsMaterial::NParameter::NColor::FValue ColorParameterType;

			for (const ColorParameterType& Param : GetColorParameters())
			{
				Param.SetChecked(Context, OutMID);
			}
		}

		bool FWithParameters::SetSafe(const FString& Context, UPrimitiveComponent* Component, const int32& Index, UMaterialInstanceDynamic*& OutMID, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
		{
			if (!IsValid(Context, Log))
				return false;

			typedef NCsMaterial::NMID::FLibrary MIDLibrary;

			if (!MIDLibrary::SetSafe(Context, Component, GetMaterial(), Index, OutMID, Log))
				return false;

			// Float
			typedef NCsMaterial::NParameter::NFloat::FValue FloatParameterType;

			for (const FloatParameterType& Param : GetFloatParameters())
			{
				if (!Param.SetSafe(Context, OutMID, Log))
					return false;
			}
			// Color
			typedef NCsMaterial::NParameter::NColor::FValue ColorParameterType;

			for (const ColorParameterType& Param : GetColorParameters())
			{
				if (!Param.SetSafe(Context, OutMID, Log))
					return false;
			}
			return true;
		}

		void FWithParameters::SetChecked(const FString& Context, UPrimitiveComponent* Component, const int32& Index) const
		{
			check(IsValidChecked(Context));

			typedef NCsMaterial::FLibrary MaterialLibrary;

			MaterialLibrary::SetChecked(Context, Component, GetMaterial(), Index);
		}

		bool FWithParameters::SetSafe(const FString& Context, UPrimitiveComponent* Component, const int32& Index, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
		{
			if (!IsValid(Context, Log))
				return false;

			typedef NCsMaterial::FLibrary MaterialLibrary;

			return MaterialLibrary::SetSafe(Context, Component, GetMaterial(), Index, Log);
		}
	}
}

#pragma endregion FCsMaterialInterface_WithParameters

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
	// Color
	{
		typedef NCsMaterial::NParameter::NColor::FRange ParamType;

		TArray<ParamType>* Params = Mat->GetColorParametersPtr();

		const int32 Count = ColorParameters.Num();

		Params->Reset(Count);

		for (FCsMaterialParameterColorRange& P : ColorParameters)
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
	// Color
	{
		typedef NCsMaterial::NParameter::NColor::FRange ParamType;

		TArray<ParamType>* Params = Mat->GetColorParametersPtr();

		const int32 Count = ColorParameters.Num();

		Params->Reset(Count);

		for (const FCsMaterialParameterColorRange& P : ColorParameters)
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
	// Float
	for (const FCsMaterialParameterFloatRange& Param : FloatParameters)
	{
		check(Param.IsValidChecked(Context, Material.Get()));
	}
	// Color
	for (const FCsMaterialParameterColorRange& Param : ColorParameters)
	{
		check(Param.IsValidChecked(Context, Material.Get()));
	}
	return true;
}

bool FCsMaterialInterface_WithRangeParameters::IsValid(const FString& Context, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
{
	CS_IS_VALID(Material)
	// Float
	for (const FCsMaterialParameterFloatRange& Param : FloatParameters)
	{
		if (!Param.IsValid(Context, Material.Get(), Log))
			return false;
	}
	// Color
	for (const FCsMaterialParameterColorRange& Param : ColorParameters)
	{
		if (!Param.IsValid(Context, Material.Get(), Log))
			return false;
	}
	return true;
}

bool FCsMaterialInterface_WithRangeParameters::IsTopValidChecked(const FString& Context) const
{
	CS_IS_TOP_VALID_CHECKED(Material);
	// Float
	for (const FCsMaterialParameterFloatRange& Param : FloatParameters)
	{
		check(Param.IsValidChecked(Context, Material.Get()));
	}
	// Color
	for (const FCsMaterialParameterColorRange& Param : ColorParameters)
	{
		check(Param.IsValidChecked(Context, Material.Get()));
	}
	return true;
}

bool FCsMaterialInterface_WithRangeParameters::IsTopValid(const FString& Context, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
{
	CS_IS_TOP_VALID(Material)
	// Float
	for (const FCsMaterialParameterFloatRange& Param : FloatParameters)
	{
		if (!Param.IsValid(Context, Material.Get(), Log))
			return false;
	}
	// Color
	for (const FCsMaterialParameterColorRange& Param : ColorParameters)
	{
		if (!Param.IsValid(Context, Material.Get(), Log))
			return false;
	}
	return true;
}

void FCsMaterialInterface_WithRangeParameters::SetChecked(const FString& Context, UPrimitiveComponent* Component, const int32& Index, UMaterialInstanceDynamic*& OutMID) const
{
	check(IsValidChecked(Context));

	typedef NCsMaterial::NMID::FLibrary MIDLibrary;

	MIDLibrary::SetChecked(Context, Component, Material.GetChecked(Context), Index, OutMID);
	// Float
	for (const FCsMaterialParameterFloatRange& Param : FloatParameters)
	{
		Param.SetChecked(Context, OutMID);
	}
	// Color
	for (const FCsMaterialParameterColorRange& Param : ColorParameters)
	{
		Param.SetChecked(Context, OutMID);
	}
}

bool FCsMaterialInterface_WithRangeParameters::SetSafe(const FString& Context, UPrimitiveComponent* Component, const int32& Index, UMaterialInstanceDynamic*& OutMID, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
{
	if (!IsValid(Context, Log))
		return false;

	typedef NCsMaterial::NMID::FLibrary MIDLibrary;

	MIDLibrary::SetChecked(Context, Component, Material.GetChecked(Context), Index, OutMID);
	// Float
	for (const FCsMaterialParameterFloatRange& Param : FloatParameters)
	{
		if (!Param.SetSafe(Context, OutMID, Log))
			return false;
	}
	// Color
	for (const FCsMaterialParameterColorRange& Param : ColorParameters)
	{
		if (!Param.SetSafe(Context, OutMID, Log))
			return false;
	}
	return true;
}

namespace NCsMaterial
{
	namespace NInterface
	{
		bool FWithRangeParameters::IsValidChecked(const FString& Context) const
		{
			CS_IS_PTR_NULL_CHECKED(GetMaterial());
			// Float
			typedef NCsMaterial::NParameter::NFloat::FRange FloatParameterType;

			for (const FloatParameterType& Param : GetFloatParameters())
			{
				check(Param.IsValidChecked(Context, GetMaterial()));
			}
			// Color
			typedef NCsMaterial::NParameter::NColor::FRange ColorParameterType;

			for (const ColorParameterType& Param : GetColorParameters())
			{
				check(Param.IsValidChecked(Context, GetMaterial()));
			}
			return true;
		}

		bool FWithRangeParameters::IsValid(const FString& Context, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
		{
			CS_IS_PTR_NULL(GetMaterial());
			// Float
			typedef NCsMaterial::NParameter::NFloat::FRange FloatParameterType;

			for (const FloatParameterType& Param : GetFloatParameters())
			{
				if (!Param.IsValid(Context, GetMaterial(), Log))
					return false;
			}
			// Color
			typedef NCsMaterial::NParameter::NColor::FRange ColorParameterType;

			for (const ColorParameterType& Param : GetColorParameters())
			{
				if (!Param.IsValid(Context, GetMaterial(), Log))
					return false;
			}
			return true;
		}

		void FWithRangeParameters::SetChecked(const FString& Context, UPrimitiveComponent* Component, const int32& Index, UMaterialInstanceDynamic*& OutMID) const
		{
			check(IsValidChecked(Context));

			typedef NCsMaterial::NMID::FLibrary MIDLibrary;

			MIDLibrary::SetChecked(Context, Component, GetMaterial(), Index, OutMID);
			// Float
			typedef NCsMaterial::NParameter::NFloat::FRange FloatParameterType;
			
			for (const FloatParameterType& Param : GetFloatParameters())
			{
				Param.SetChecked(Context, OutMID);
			}
			// Color
			typedef NCsMaterial::NParameter::NColor::FRange ColorParameterType;

			for (const ColorParameterType& Param : GetColorParameters())
			{
				Param.SetChecked(Context, OutMID);
			}
		}

		bool FWithRangeParameters::SetSafe(const FString& Context, UPrimitiveComponent* Component, const int32& Index, UMaterialInstanceDynamic*& OutMID, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
		{
			if (!IsValid(Context, Log))
				return false;

			typedef NCsMaterial::NMID::FLibrary MIDLibrary;

			if (!MIDLibrary::SetSafe(Context, Component, GetMaterial(), Index, OutMID, Log))
				return false;

			// Float
			typedef NCsMaterial::NParameter::NFloat::FRange FloatParameterType;

			for (const FloatParameterType& Param : GetFloatParameters())
			{
				if (!Param.SetSafe(Context, OutMID, Log))
					return false;
			}
			// Color
			typedef NCsMaterial::NParameter::NColor::FRange ColorParameterType;

			for (const ColorParameterType& Param : GetColorParameters())
			{
				if (!Param.SetSafe(Context, OutMID, Log))
					return false;
			}
			return true;
		}

		void FWithRangeParameters::SetChecked(const FString& Context, UPrimitiveComponent* Component, const int32& Index) const
		{
			check(IsValidChecked(Context));

			typedef NCsMaterial::FLibrary MaterialLibrary;

			MaterialLibrary::SetChecked(Context, Component, GetMaterial(), Index);
		}

		bool FWithRangeParameters::SetSafe(const FString& Context, UPrimitiveComponent* Component, const int32& Index, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
		{
			if (!IsValid(Context, Log))
				return false;

			typedef NCsMaterial::FLibrary MaterialLibrary;

			return MaterialLibrary::SetSafe(Context, Component, GetMaterial(), Index, Log);
		}
	}
}

#pragma endregion FCsMaterialInterface_WithRangeParameters