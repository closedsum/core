#pragma once
// Types
#include "Types/Enum/CsEnumMap.h"

#include "CsTypes_OpenAI.generated.h"

// OpenAI: TextModel
#pragma region

/**
* Describes any model used for any Generating Text via OpenAI.
*/
UENUM(BlueprintType)
enum class ECsOpenAI_TextModel : uint8
{
	GPT_4_1					UMETA(DisplayName = "gpt-4.1"),
	GPT_4O					UMETA(DisplayName = "gpt-4o"),
	GPT_4_1_MINI			UMETA(DisplayName = "gpt-4.1-mini"),
	GPT_4O_MINI				UMETA(DisplayName = "gpt-4o-mini"),
	GPT_4_1_NANO			UMETA(DisplayName = "gpt-4.1-nano"),
	ECsOpenAI_TextModel_MAX	UMETA(Hidden),
};

struct CSGENAI_API EMCsOpenAI_TextModel : public TCsEnumMap<ECsOpenAI_TextModel>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsOpenAI_TextModel, ECsOpenAI_TextModel)
};

namespace NCsOpenAI_TextModel
{
	using Type = ECsOpenAI_TextModel;

	namespace Ref
	{
		extern CSGENAI_API const Type GPT_4_1;
		extern CSGENAI_API const Type GPT_4O;
		extern CSGENAI_API const Type GPT_4_1_MINI;
		extern CSGENAI_API const Type GPT_4O_MINI;
		extern CSGENAI_API const Type GPT_4_1_NANO;
		extern CSGENAI_API const Type ECsOpenAI_TextModel_MAX;
	}
}

#pragma endregion OpenAI: TextModel

// OpenAI: TextToSpeechModel
#pragma region

/**
* Describes any model used for any Generating Speech via OpenAI's Text to Speech (TTS) Service.
*/
UENUM(BlueprintType)
enum class ECsOpenAI_TextToSpeechModel : uint8
{
	GPT_4O_MINI_TTS					UMETA(DisplayName = "gpt-4o-mini-tts"),
	ECsOpenAI_TextToSpeechModel_MAX	UMETA(Hidden),
};

struct CSGENAI_API EMCsOpenAI_TextToSpeechModel : public TCsEnumMap<ECsOpenAI_TextToSpeechModel>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsOpenAI_TextToSpeechModel, ECsOpenAI_TextToSpeechModel)
};

namespace NCsOpenAI_TextToSpeechModel
{
	using Type = ECsOpenAI_TextToSpeechModel;

	namespace Ref
	{
		extern CSGENAI_API const Type GPT_4O_MINI_TTS;
		extern CSGENAI_API const Type ECsOpenAI_TextToSpeechModel_MAX;
	}
}

#pragma endregion OpenAI: TextToSpeechModel

// OpenAI: SpeechToTextModel
#pragma region

/**
* Describes any model used for any Generating Text via OpenAI's Speech to Text Service.
*/
UENUM(BlueprintType)
enum class ECsOpenAI_SpeechToTextModel : uint8
{
	WHISPER_1						UMETA(DisplayName = "whisper-1"),
	ECsOpenAI_SpeechToTextModel_MAX	UMETA(Hidden),
};

struct CSGENAI_API EMCsOpenAI_SpeechToTextModel : public TCsEnumMap<ECsOpenAI_SpeechToTextModel>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsOpenAI_SpeechToTextModel, ECsOpenAI_SpeechToTextModel)
};

namespace NCsOpenAI_SpeechToTextModel
{
	using Type = ECsOpenAI_SpeechToTextModel;

	namespace Ref
	{
		extern CSGENAI_API const Type WHISPER_1;
		extern CSGENAI_API const Type ECsOpenAI_SpeechToTextModel_MAX;
	}
}

#pragma endregion OpenAI: SpeechToTextModel

// OpenAI: Voice
#pragma region

/**
* Describes the voice use for any Audio generated from OpenAI's Text to Speech Service.
*/
UENUM(BlueprintType)
enum class ECsOpenAI_Voice : uint8
{
	ALLOY				UMETA(DisplayName = "alloy"),
	ASH					UMETA(DisplayName = "ash"),
	BALLAD				UMETA(DisplayName = "ballad"),
	CORAL				UMETA(DisplayName = "coral"),
	ECHO				UMETA(DisplayName = "echo"),
	FABLE				UMETA(DisplayName = "fable"),
	ONYX				UMETA(DisplayName = "onyx"),
	NOVA				UMETA(DisplayName = "nova"),
	SAGE				UMETA(DisplayName = "sage"),
	SHIMMER				UMETA(DisplayName = "shimmer"),
	VERSE				UMETA(DisplayName = "verse"),
	ECsOpenAI_Voice_MAX	UMETA(Hidden),
};

struct CSGENAI_API EMCsOpenAI_Voice : public TCsEnumMap<ECsOpenAI_Voice>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsOpenAI_Voice, ECsOpenAI_Voice)
};

namespace NCsOpenAI_Voice
{
	using Type = ECsOpenAI_Voice;

	namespace Ref
	{
		extern CSGENAI_API const Type ALLOY;
		extern CSGENAI_API const Type ASH;
		extern CSGENAI_API const Type BALLAD;
		extern CSGENAI_API const Type CORAL;
		extern CSGENAI_API const Type ECHO;
		extern CSGENAI_API const Type FABLE;
		extern CSGENAI_API const Type ONYX;
		extern CSGENAI_API const Type NOVA;
		extern CSGENAI_API const Type SAGE;
		extern CSGENAI_API const Type SHIMMER;
		extern CSGENAI_API const Type VERSE;
		extern CSGENAI_API const Type ECsOpenAI_Voice_MAX;
	}
}

#pragma endregion OpenAI: Voice