// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Interface.h"

#include "CsGetPIEInfo.generated.h"

UINTERFACE(BlueprintType, meta = (CannotImplementInterfaceInBlueprint))
class CSCORE_API UCsGetPIEInfo : public UInterface
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

namespace NCsPIE
{
	struct CSCORE_API FInfo
	{
	public:

	#define StateType NCsPIE::EState

		StateType State;

		FInfo() :
			State(StateType::None)
		{
		}

		FORCEINLINE const StateType& GetState() const { return State; }
		FORCEINLINE void SetNone() { State = StateType::None; }
		FORCEINLINE bool IsNone() const { return State == StateType::None; }
		FORCEINLINE void SetBeginning() { State = StateType::Beginning; }
		FORCEINLINE bool IsBeginning() const { return State == StateType::Beginning; }
		FORCEINLINE void SetActive() { State = StateType::Active; }
		FORCEINLINE bool IsActive() const { return State == StateType::Active; }
		FORCEINLINE bool IsBeginningOrActive() const { return IsBeginning() | IsActive(); };
		FORCEINLINE void SetEnding() { State = StateType::Ending; }

	#undef StateType
	};
}

/**
*/
class CSCORE_API ICsGetPIEInfo
{
	GENERATED_IINTERFACE_BODY()

public:

#define InfoType NCsPIE::FInfo

	virtual const InfoType& GetPIEInfo() const = 0;

#undef InfoType
};