// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "Types/CsTypes_Primitive.h"
#include "CsBTTask_LookAt.generated.h"

// Enums
#pragma region

UENUM()
namespace ECsBTTask_LookAtType
{
	enum Type
	{
		UntilAligned				UMETA(DisplayName = "Until Aligned"),
		Timed						UMETA(DisplayName = "Timed"),
		Forever						UMETA(DisplayName = "Forever"),
		ECsBTTask_LookAtType_MAX	UMETA(Hidden),
	};
}

typedef ECsBTTask_LookAtType::Type TCsBTTask_LookAtType;

struct CSCORE_API EMCsBTTask_LookAtType : public TCsEnumMap<ECsBTTask_LookAtType::Type>
{
protected:
	EMCsBTTask_LookAtType() {}
	EMCsBTTask_LookAtType(const EMCsBTTask_LookAtType &) = delete;
	EMCsBTTask_LookAtType(EMCsBTTask_LookAtType &&) = delete;
public:
	~EMCsBTTask_LookAtType() {}
private:
	static EMCsBTTask_LookAtType* Instance;

public:
	static EMCsBTTask_LookAtType& Get();
};

namespace ECsBTTask_LookAtType
{
	namespace Ref
	{
		extern CSCORE_API const Type UntilAligned;
		extern CSCORE_API const Type Timed;
		extern CSCORE_API const Type Forever;
		extern CSCORE_API const Type ECsBTTask_LookAtType_MAX;
	}
}

#pragma endregion Enums

// Structs
#pragma region

struct FCsBTTask_LookAtMemory
{
	float ElapsedTime;

	void Reset()
	{
		ElapsedTime = 0.0f;
	}
};

USTRUCT(BlueprintType)
struct FCsBTTask_LookAt_ResetOnAbort
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
class CSCORE_API UCsBTTask_LookAt : public UBTTask_BlackboardBase
{
	GENERATED_UCLASS_BODY()

protected:

	UPROPERTY(EditAnywhere, Category = Node, meta = (InlineEditConditionToggle))
	bool bResetOnAbort;
	UPROPERTY(EditAnywhere, Category = Node, meta = (editcondition = "bResetOnAbort"))
	FCsBTTask_LookAt_ResetOnAbort ResetOnAbort;

	UPROPERTY(EditAnywhere, Category = Node)
	TEnumAsByte<ECsBTTask_LookAtType::Type> Type;

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
