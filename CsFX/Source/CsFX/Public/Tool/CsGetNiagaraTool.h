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
			struct CSFX_API FImpl
			{
			public:

				void(*ApplyCompileAndSaveImpl)(UNiagaraSystem*);
			};
		}
	}
}

UINTERFACE(Blueprintable)
class CSFX_API UCsGetNiagaraTool : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class CSFX_API ICsGetNiagaraTool
{
	GENERATED_IINTERFACE_BODY()

private:

	// Allow clearer names without name collisions
	struct _
	{
		using NiagaraToolType = NCsFX::NNiagara::NTool::FImpl;
	};

public:

	virtual _::NiagaraToolType* GetNiagaraTool() = 0;
};