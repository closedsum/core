// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Interface.h"

#include "CsGetPIEInfo.generated.h"

UINTERFACE(BlueprintType, meta = (CannotImplementInterfaceInBlueprint))
class CSPIE_API UCsGetPIEInfo : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

namespace NCsPIE
{
	enum class EState : uint8
	{
		None, 
		Beginning,
		Active,
		Ending
	};
}

using CsPIEStateType = NCsPIE::EState;

namespace NCsPIE
{
	struct CSPIE_API FInfo
	{
	public:

		CsPIEStateType State;

		FInfo() :
			State(CsPIEStateType::None)
		{
		}

		FORCEINLINE const CsPIEStateType& GetState() const { return State; }
		FORCEINLINE void SetNone() { State = CsPIEStateType::None; }
		FORCEINLINE bool IsNone() const { return State == CsPIEStateType::None; }
		FORCEINLINE void SetBeginning() { State = CsPIEStateType::Beginning; }
		FORCEINLINE bool IsBeginning() const { return State == CsPIEStateType::Beginning; }
		FORCEINLINE void SetActive() { State = CsPIEStateType::Active; }
		FORCEINLINE bool IsActive() const { return State == CsPIEStateType::Active; }
		FORCEINLINE bool IsBeginningOrActive() const { return IsBeginning() | IsActive(); };
		FORCEINLINE void SetEnding() { State = CsPIEStateType::Ending; }
	};
}

using CsPIEInfoType = NCsPIE::FInfo;

/**
*/
class CSPIE_API ICsGetPIEInfo
{
	GENERATED_IINTERFACE_BODY()

public:

	virtual const CsPIEInfoType& GetPIEInfo() const = 0;
};