// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/CsTypes_Macro.h"
#pragma once

class UNiagaraSystem;
class UNiagaraComponent;

// NCsFX::NParamter::IParamter
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsFX, NParameter, IParameter)

namespace NCsFX
{
	/**
	* Library of function related to FX
	*/
	class CSCORE_API FLibrary
	{
	#define ParameterType NCsFX::NParameter::IParameter

	public:

		static bool HasVariableNameChecked(const FString& Context, UNiagaraSystem* System, const FName& Name);


		/**
		*/
		static bool HasParameterChecked(const FString& Context, UNiagaraSystem* System, const ParameterType* Parameter);

		/**
		*/
		static void SetParameterChecked(const FString& Context, UNiagaraComponent* Component, const ParameterType* Parameter);

	#undef ParameterType
	};
}