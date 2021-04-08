// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/FX/CsLibrary_FX.h"
#include "CsCore.h"

// FX
#include "Managers/FX/Params/CsParams_FX.h"
#include "Managers/FX/Params/CsLibrary_Params_FX.h"
#include "NiagaraSystem.h"
#include "NiagaraComponent.h"

namespace NCsFX
{
	bool FLibrary::HasVariableNameChecked(const FString& Context, UNiagaraSystem* System, const FName& Name)
	{
		checkf(System, TEXT("%s: System is NULL."), *Context);

		checkf(Name != NAME_None, TEXT("%s: Name: None is NOT Valid."), *Context);

		static TArray<FNiagaraVariable> Parameters;

		Parameters.Reset(Parameters.Max());

		System->GetExposedParameters().GetParameters(Parameters);

		bool Found = false;

		for (FNiagaraVariable& Var : Parameters)
		{
			if (Name == Var.GetName())
				Found = true;
		}

		checkf(Found, TEXT("%s: Failed to find Parameter with Name: %s on System: %s."), *Context, *(Name.ToString()), *(System->GetName()));
		return true;
	}

	#define ParameterType NCsFX::NParameter::IParameter
	bool FLibrary::HasParameterChecked(const FString& Context, UNiagaraSystem* System, const ParameterType* Parameter)
	{
	#undef ParameterType

		checkf(System, TEXT("%s: System is NULL."), *Context);

		typedef NCsFX::NParameter::FLibrary ParameterLibrary;

		check(ParameterLibrary::IsValidChecked(Context, Parameter));

		const FName& Name = Parameter->GetName();

		static TArray<FNiagaraVariable> Parameters;

		Parameters.Reset(Parameters.Max());

		System->GetExposedParameters().GetParameters(Parameters);

		bool Found = false;

		for (FNiagaraVariable& Var : Parameters)
		{
			if (Name == Var.GetName())
				Found = true;
		}

		checkf(Found, TEXT("%s: Failed to find Parameter with Name: %s on System: %s."), *Context, *(Name.ToString()), *(System->GetName()));
		return true;
	}

	#define ParameterType NCsFX::NParameter::IParameter
	void FLibrary::SetParameterChecked(const FString& Context, UNiagaraComponent* Component, const ParameterType* Parameter)
	{
	#undef ParameterType

		checkf(Component, TEXT("%s: Component is NULL."), *Context);

		UNiagaraSystem* System = Component->GetAsset();

		checkf(System, TEXT("%s: Asset on Component: %s is NULL."), *Context, *(Component->GetName()));

		check(HasParameterChecked(Context, System, Parameter));

		typedef NCsFX::NParameter::EValue ParameterValueType;
		typedef NCsFX::NParameter::EMValue ParameterValueMapType;
		typedef NCsFX::NParameter::FLibrary ParameterLibrary;

		const ParameterValueType& ValueType = Parameter->GetValueType();

		// Int
		if (ValueType == ParameterValueType::Int)
			Component->SetVariableInt(Parameter->GetName(), ParameterLibrary::GetIntChecked(Context, Parameter));
		// Float
		if (ValueType == ParameterValueType::Float)
			Component->SetVariableFloat(Parameter->GetName(), ParameterLibrary::GetFloatChecked(Context, Parameter));
		// Vector
		else
		if (ValueType == ParameterValueType::Vector)
			Component->SetVariableVec3(Parameter->GetName(), ParameterLibrary::GetVectorChecked(Context, Parameter));
	}
}