// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Types
#include "Types/Enum/CsEnum_uint8.h"
#include "Types/Enum/CsEnumMap.h"
#include "Types/Enum/CsEnumStructMap.h"
// Log
#include "Utility/CsSeamlessTransitionLog.h"

#include "CsTypes_GameInstance_Transition.generated.h"

// GameInstanceTransitionState
#pragma region

USTRUCT(BlueprintType)
struct CSSEAMLESSTRANSITION_API FECsGameInstanceTransitionState : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()
	
	CS_ENUM_UINT8_BODY(FECsGameInstanceTransitionState)
};

CS_DEFINE_ENUM_UINT8_GET_TYPE_HASH(FECsGameInstanceTransitionState)

struct CSSEAMLESSTRANSITION_API EMCsGameInstanceTransitionState final : public TCsEnumStructMap<FECsGameInstanceTransitionState, uint8>
{
	CS_ENUM_STRUCT_MAP_BODY(EMCsGameInstanceTransitionState, FECsGameInstanceTransitionState, uint8)
};

namespace NCsGameInstanceTransitionState
{
	typedef FECsGameInstanceTransitionState Type;
	typedef EMCsGameInstanceTransitionState EnumMapType;
}

// FCsGameInstance_TransitionParams
#pragma region 

USTRUCT(BlueprintType)
struct CSSEAMLESSTRANSITION_API FCsGameInstance_TransitionParams
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsSeamlessTransition|Game Instance|Transition")
	bool bGeneric;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsSeamlessTransition|Game Instance|Transition")
	FECsGameInstanceTransitionState From;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsSeamlessTransition|Game Instance|Transition", meta = (AllowedClasses = "/Script/Engine.World"))
	FSoftObjectPath FromMap;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsSeamlessTransition|Game Instance|Transition", meta = (AllowedClasses = "/Script/Engine.World"))
	FSoftObjectPath TransitionMap;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsSeamlessTransition|Game Instance|Transition")
	FECsGameInstanceTransitionState To;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsSeamlessTransition|Game Instance|Transition", meta = (AllowedClasses = "/Script/Engine.World"))
	FSoftObjectPath ToMap;

	FCsGameInstance_TransitionParams() :
		bGeneric(false),
		From(),
		FromMap(),
		TransitionMap(),
		To(),
		ToMap()
	{
	}

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsSeamlessTransition::FLog::Warning) const;
};

namespace NCsGameInstance
{
	namespace NTransition
	{
		struct CSSEAMLESSTRANSITION_API FParams
		{
		private:

			typedef FECsGameInstanceTransitionState StateType;
			typedef EMCsGameInstanceTransitionState StateMapType;

		public:

			bool bActive;

			bool bGeneric;

			StateType From;

			FSoftObjectPath FromMap;

			FSoftObjectPath TransitionMap;

			StateType To;

			FSoftObjectPath ToMap;

			FName GamePlay;

			FParams() :
				bActive(false),
				bGeneric(false),
				From(),
				FromMap(),
				TransitionMap(),
				To(),
				ToMap(),
				GamePlay(NAME_None)
			{
			}

			FParams(const FParams& B)
			{
				Copy(B);
			}

			FParams& operator=(const FParams& B)
			{
				Copy(B);
				return *this;
			}

			static FParams Make(const FCsGameInstance_TransitionParams& B)
			{
				FParams P;
				P.Copy(B);
				return P;
			}

			void Copy(const FParams& B)
			{
				bGeneric	  = B.bGeneric;
				From		  = B.From;
				FromMap		  = B.FromMap;
				TransitionMap = B.TransitionMap;
				To			  = B.To;
				ToMap		  = B.ToMap;
			}

			void Copy(const FCsGameInstance_TransitionParams& B)
			{
				bGeneric	  = B.bGeneric;
				From		  = B.From;
				FromMap		  = B.FromMap;
				TransitionMap = B.TransitionMap;
				To			  = B.To;
				ToMap		  = B.ToMap;
			}
		
			void Reset()
			{
				bActive = false;
				bGeneric = false;
				From = StateMapType::Get().GetMAX();
				FromMap.Reset();
				TransitionMap.Reset();
				To = StateMapType::Get().GetMAX();
				ToMap.Reset();
				GamePlay = NAME_None;
			}

			FORCEINLINE void MarkActive() { bActive = true; }
			FORCEINLINE bool IsActive() const { return bActive; }

			FORCEINLINE bool HasTransition() const { return TransitionMap.IsValid(); }

			// TODO: Get from Settings
			bool HasCustomTransition() const 
			{ 
				return HasTransition();
			}

			bool IsValidChecked(const FString& Context) const;
			bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsSeamlessTransition::FLog::Warning) const;
		};
	}
}

using CsGameInstanceTransitionParamsType = NCsGameInstance::NTransition::FParams;

#pragma endregion FCGameInstance_TransitionParams

// GameInstanceTransitionUnpauseCondition
#pragma region

/**
* Describes the condition to unpause the Transition after the Transition Map has "completed".
*  Transition Map is used in the Seamless Travel between a Origin World and a Destination World.
*   Once the Seamless Travel has started, the Origin World is unloaded and the Transition Map is loaded.
*   The Game State and minimal game logic is "restarted" in a way to keep a seamless transition between
*   the Origin World and the Transition Map. Once this process is done, the Transition Map has entered 
*   a "completed" state.
*/
UENUM(BlueprintType)
enum class ECsGameInstanceTransitionUnpauseCondition : uint8
{
	/** Unpause the Transition immediately after the Transition Map has "completed". */
	None											UMETA(DisplayName = "None"),
	/** Unpause the Transition after some Time after the Transition Map has "completed". */
	Time											UMETA(DisplayName = "Time"),
	/** Unpause the Transition by some Custom logic / method after the Transition Map has "completed". */
	Custom											UMETA(DisplayName = "Custom"),
	ECsGameInstanceTransitionUnpauseCondition_MAX	UMETA(Hidden)
};

struct CSSEAMLESSTRANSITION_API EMCsGameInstanceTransitionUnpauseCondition : public TCsEnumMap<ECsGameInstanceTransitionUnpauseCondition>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsGameInstanceTransitionUnpauseCondition, ECsGameInstanceTransitionUnpauseCondition)
};

namespace NCsGameInstanceTransitionUnpauseCondition
{
	typedef ECsGameInstanceTransitionUnpauseCondition Type;

	namespace Ref
	{
		extern CSSEAMLESSTRANSITION_API const Type None;
		extern CSSEAMLESSTRANSITION_API const Type Time;
		extern CSSEAMLESSTRANSITION_API const Type Custom;
		extern CSSEAMLESSTRANSITION_API const Type ECsGameInstanceTransitionUnpauseCondition_MAX;
	}
}

namespace NCsGameInstance
{
	namespace NTransition
	{
		namespace NUnpause
		{
			enum class ECondition : uint8
			{
				None,
				Time,
				Custom,
				ECondition_MAX
			};

			struct CSSEAMLESSTRANSITION_API EMCondition : public TCsEnumMap<ECondition>
			{
				CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCondition, ECondition)
			};

			namespace NCondition
			{
				typedef ECondition Type;

				namespace Ref
				{
					extern CSSEAMLESSTRANSITION_API const Type None;
					extern CSSEAMLESSTRANSITION_API const Type Time;
					extern CSSEAMLESSTRANSITION_API const Type Custom;
					extern CSSEAMLESSTRANSITION_API const Type ECondition_MAX;
				}
			}
		}
	}
}

#pragma endregion GameInstanceTransitionUnpauseCondition