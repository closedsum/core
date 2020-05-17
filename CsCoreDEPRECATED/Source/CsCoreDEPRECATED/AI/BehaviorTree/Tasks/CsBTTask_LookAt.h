// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "Types/Enum/CsEnumMap.h"
#include "CsBTTask_LookAt.generated.h"

// Enums
#pragma region

	// BTTask_LookAtType
#pragma region

UENUM()
enum class ECsBTTask_LookAtType : uint8
{
	UntilAligned				UMETA(DisplayName = "Until Aligned"),
	Timed						UMETA(DisplayName = "Timed"),
	Forever						UMETA(DisplayName = "Forever"),
	ECsBTTask_LookAtType_MAX	UMETA(Hidden),
};

struct CSCOREDEPRECATED_API EMCsBTTask_LookAtType : public TCsEnumMap<ECsBTTask_LookAtType>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsBTTask_LookAtType, ECsBTTask_LookAtType)
};

namespace NCsBTTask_LookAtType
{
	typedef ECsBTTask_LookAtType Type;

	namespace Ref
	{
		extern CSCOREDEPRECATED_API const Type UntilAligned;
		extern CSCOREDEPRECATED_API const Type Timed;
		extern CSCOREDEPRECATED_API const Type Forever;
		extern CSCOREDEPRECATED_API const Type ECsBTTask_LookAtType_MAX;
	}

	extern CSCOREDEPRECATED_API const uint8 MAX;
}

#define ECS_BTTASK_LOOKATTYPE NCsBTTask_LookAtType::MAX

#pragma endregion BTTask_LookAtType

#pragma endregion Enums

// Structs
#pragma region

struct CSCOREDEPRECATED_API FCsBTTask_LookAtMemory
{
	float ElapsedTime;

	void Reset()
	{
		ElapsedTime = 0.0f;
	}
};

USTRUCT(BlueprintType)
struct CSCOREDEPRECATED_API FCsBTTask_LookAt_ResetOnAbort
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, Category = Node, meta = (ClampMin = "0.0", UIMin = "0.0"))
	float BlendOutRate;

	FCsBTTask_LookAt_ResetOnAbort()
	{
		BlendOutRate = 0.0f;
	}
	~FCsBTTask_LookAt_ResetOnAbort() {}
};

#pragma endregion Structs

class AAIController;

UCLASS(config = Game)
class CSCOREDEPRECATED_API UCsBTTask_LookAt : public UBTTask_BlackboardBase
{
	GENERATED_UCLASS_BODY()

protected:

	UPROPERTY(EditAnywhere, Category = Node, meta = (InlineEditConditionToggle))
	bool bResetOnAbort;
	UPROPERTY(EditAnywhere, Category = Node, meta = (editcondition = "bResetOnAbort"))
	FCsBTTask_LookAt_ResetOnAbort ResetOnAbort;

	UPROPERTY(EditAnywhere, Category = Node)
	ECsBTTask_LookAtType Type;

	UPROPERTY(EditAnywhere, Category = Node, meta = (ClampMin = "0.0", UIMin = "0.0"))
	float Rate;

	UPROPERTY(EditAnywhere, Category = Node, meta = (InlineEditConditionToggle))
	bool bTime;

	UPROPERTY(EditAnywhere, Category = Node, meta = (editcondition = "bTime"))
	float Time;

	UPROPERTY(EditAnywhere, Category = Node)
	FName Bone;

	/** Success condition for Type: UntilAligned when the Actor's look direction (pitch and yaw) is within delta */
	UPROPERTY(EditAnywhere, Category = Node, meta = (ClampMin = "0.0", UIMin = "0.0"))
	float AngleDeltaForSuccess;

public:

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	virtual EBTNodeResult::Type AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void DescribeRuntimeValues(const UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTDescriptionVerbosity::Type Verbosity, TArray<FString>& Values) const override;
	virtual FString GetStaticDescription() const override;

	virtual uint16 GetInstanceMemorySize() const override { return sizeof(FCsBTTask_LookAtMemory); }

	void SetTimeByType();

#if WITH_EDITOR

	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& e) override;

#endif // #if WITH_EDITOR
};
