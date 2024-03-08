// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Interface.h"

#include "CsGetNiagaraTool.generated.h"

class UNiagaraSystem;

namespace NCsFX
{
	namespace NNiagara
	{
		namespace NTool
		{
			struct CSCORE_API FImpl
			{
			public:

				void(*ApplyCompileAndSaveImpl)(UNiagaraSystem*);
			};
		}
	}
}

UINTERFACE(Blueprintable)
class CSCORE_API UCsGetNiagaraTool : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class CSCORE_API ICsGetNiagaraTool
{
	GENERATED_IINTERFACE_BODY()

public:

#define NiagaraToolType NCsFX::NNiagara::NTool::FImpl

	virtual NiagaraToolType* GetNiagaraTool() = 0;

#undef NiagaraToolType
};