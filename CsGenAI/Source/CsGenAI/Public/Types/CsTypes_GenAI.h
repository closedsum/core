#pragma once
// Types
#include "Types/Enum/CsEnumMap.h"

#include "CsTypes_GenAI.generated.h"

// GenAIService
#pragma region

/**
* Describes any service used for any Generative AI (Text, Speech, Image, ... etc).
*/
UENUM(BlueprintType)
enum class ECsGenAIService : uint8
{
	OPENAI				UMETA(DisplayName = "Open AI"),
	ECsGenAIService_MAX	UMETA(Hidden),
};

struct CSGENAI_API EMCsGenAIService : public TCsEnumMap<ECsGenAIService>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsGenAIService, ECsGenAIService)
};

namespace NCsGenAIService
{
	using Type = ECsGenAIService;

	namespace Ref
	{
		extern CSGENAI_API const Type OPENAI;
		extern CSGENAI_API const Type ECsGenAIService_MAX;
	}
}

#pragma endregion GenAIService

// TextModel
#pragma region

/**
* Describes any model used for any Generating Text via a LLM Service.
*/
UENUM(BlueprintType)
enum class ECsTextModel : uint8
{
	GPT_4_1				UMETA(DisplayName = "gpt-4.1"),
	GPT_4O				UMETA(DisplayName = "gpt-4o"),
	GPT_4_1_MINI		UMETA(DisplayName = "gpt-4.1-mini"),
	GPT_4O_MINI			UMETA(DisplayName = "gpt-4o-mini"),
	GPT_4_1_NANO		UMETA(DisplayName = "gpt-4.1-nano"),
	ECsTextModel_MAX	UMETA(Hidden),
};

struct CSGENAI_API EMCsTextModel : public TCsEnumMap<ECsTextModel>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsTextModel, ECsTextModel)
};

namespace NCsTextModel
{
	using Type = ECsTextModel;

	namespace Ref
	{
		extern CSGENAI_API const Type GPT_4_1;
		extern CSGENAI_API const Type GPT_4O;
		extern CSGENAI_API const Type GPT_4_1_MINI;
		extern CSGENAI_API const Type GPT_4O_MINI;
		extern CSGENAI_API const Type GPT_4_1_NANO;
		extern CSGENAI_API const Type ECsTextModel_MAX;
	}
}

#pragma endregion TextModel

// TextToSpeechModel
#pragma region

/**
* Describes any model used for any Generating Speech via a Text to Speech (TTS) Service.
*/
UENUM(BlueprintType)
enum class ECsTextToSpeechModel : uint8
{
	GPT_4O_MINI_TTS				UMETA(DisplayName = "gpt-4o-mini-tts"),
	ECsTextToSpeechModel_MAX	UMETA(Hidden),
};

struct CSGENAI_API EMCsTextToSpeechModel : public TCsEnumMap<ECsTextToSpeechModel>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsTextToSpeechModel, ECsTextToSpeechModel)
};

namespace NCsTextToSpeechModel
{
	using Type = ECsTextToSpeechModel;

	namespace Ref
	{
		extern CSGENAI_API const Type GPT_4O_MINI_TTS;
		extern CSGENAI_API const Type ECsTextToSpeechModel_MAX;
	}
}

#pragma endregion TextToSpeechModel

// SpeechToTextModel
#pragma region

/**
* Describes any model used for any Generating Text via a Speech to Text Service.
*/
UENUM(BlueprintType)
enum class ECsSpeechToTextModel : uint8
{
	WHISPER_1					UMETA(DisplayName = "whisper-1"),
	ECsSpeechToTextModel_MAX	UMETA(Hidden),
};

struct CSGENAI_API EMCsSpeechToTextModel : public TCsEnumMap<ECsSpeechToTextModel>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsSpeechToTextModel, ECsSpeechToTextModel)
};

namespace NCsSpeechToTextModel
{
	using Type = ECsSpeechToTextModel;

	namespace Ref
	{
		extern CSGENAI_API const Type WHISPER_1;
		extern CSGENAI_API const Type ECsSpeechToTextModel_MAX;
	}
}

#pragma endregion SpeechToTextModel