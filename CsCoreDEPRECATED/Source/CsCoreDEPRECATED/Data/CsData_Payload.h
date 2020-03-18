#pragma once
#include "Data/CsData_Impl.h"
#include "Types/CsTypes_Load.h"
#include "CsData_Payload.generated.h"

// Structs
#pragma region

USTRUCT(BlueprintType)
struct CSCOREDEPRECATED_API FCsPayloadFindEntry
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(Transient, EditAnywhere, BlueprintReadWrite, Category = "Helper")
	bool Find;

	UPROPERTY(Transient, EditAnywhere, BlueprintReadWrite, Category = "Helper")
	FName ShortCode;

	UPROPERTY(Transient, VisibleDefaultsOnly, Category = "Helper")
	FString Message;

	UPROPERTY(Transient, VisibleDefaultsOnly, Category = "Helper")
	FString Output;
};

USTRUCT(BlueprintType)
struct CSCOREDEPRECATED_API FCsPayloadAddEntry
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(Transient, EditAnywhere, BlueprintReadWrite, Category = "Helper")
	bool Add;

	UPROPERTY(Transient, EditAnywhere, BlueprintReadWrite, Category = "Helper")
	FECsDataCollectionType DataCollectionType;

	UPROPERTY(Transient, EditAnywhere, BlueprintReadWrite, Category = "Helper")
	FName ShortCode;

	UPROPERTY(Transient, EditAnywhere, BlueprintReadWrite, Category = "Helper")
	ECsLoadFlags_Editor LoadFlags;

	UPROPERTY(Transient, VisibleDefaultsOnly, Category = "Helper")
	FString Message;

	UPROPERTY(Transient, VisibleDefaultsOnly, Category = "Helper")
	FString Output;
};

USTRUCT(BlueprintType)
struct CSCOREDEPRECATED_API FCsPayloadRemoveEntry
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(Transient, EditAnywhere, BlueprintReadWrite, Category = "Helper")
	bool Remove;

	UPROPERTY(Transient, EditAnywhere, BlueprintReadWrite, Category = "Helper")
	FECsDataCollectionType DataCollectionType;

	UPROPERTY(Transient, EditAnywhere, BlueprintReadWrite, Category = "Helper")
	FName ShortCode;

	UPROPERTY(Transient, VisibleDefaultsOnly, Category = "Helper")
	FString Message;

	UPROPERTY(Transient, VisibleDefaultsOnly, Category = "Helper")
	FString Output;
};

USTRUCT(BlueprintType)
struct CSCOREDEPRECATED_API FCsPayloadValidate
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(Transient, EditAnywhere, BlueprintReadWrite, Category = "Helper")
	bool Validate;

	UPROPERTY(Transient, VisibleDefaultsOnly, Category = "Helper")
	FString Message;

	UPROPERTY(Transient, VisibleDefaultsOnly, Category = "Helper")
	FString Output;
};

#pragma endregion Structs

class UCsDataMapping;

UCLASS(Abstract)
class CSCOREDEPRECATED_API UCsData_Payload : public UCsData_Impl
{
	GENERATED_UCLASS_BODY()

// 98 Editor
#pragma region

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "-98 Editor")
	FCsPayloadFindEntry FindEntry;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "-98 Editor")
	FCsPayloadAddEntry AddEntry;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "-98 Editor")
	FCsPayloadRemoveEntry RemoveEntry;

#if WITH_EDITOR

	bool PerformFindEntry(const FName& InShortCode, TArray<FCsPayloadOld*>& OutPayloads, TArray<FECsDataCollectionType>& OutDataCollectionTypes, TArray<int32>& OutIndices);
	bool PerformAddEntry(const FName& InShortCode, const FECsDataCollectionType& DataCollectionType, const ECsLoadFlags_Editor& LoadFlags, FString& OutMessage, FString& OutOutput);

	virtual bool Editor_IsValid(UCsDataMapping* DataMapping);

	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& e) override;

#endif // #if WITH_EDITOR

#pragma endregion 98 Editor
};