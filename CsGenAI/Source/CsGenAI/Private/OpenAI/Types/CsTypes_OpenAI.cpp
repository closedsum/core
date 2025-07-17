#include "OpenAI/Types/CsTypes_OpenAI.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsTypes_OpenAI)

// OpenAI: TextModel
#pragma region

namespace NCsOpenAI_TextModel
{
	using EnumMapType = EMCsOpenAI_TextModel;

	namespace Ref
	{
		CSGENAI_API CS_ADD_TO_ENUM_MAP_CUSTOM(GPT_4_1, "gpt-4.1");
		CSGENAI_API CS_ADD_TO_ENUM_MAP_CUSTOM(GPT_4O, "gpt-4o");
		CSGENAI_API CS_ADD_TO_ENUM_MAP_CUSTOM(GPT_4_1_MINI, "gpt-4.1-mini");
		CSGENAI_API CS_ADD_TO_ENUM_MAP_CUSTOM(GPT_4O_MINI, "gpt-4o-mini");
		CSGENAI_API CS_ADD_TO_ENUM_MAP_CUSTOM(GPT_4_1_NANO, "gpt-4.1-nano");
		CSGENAI_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsOpenAI_TextModel_MAX, "MAX");
	}
}

#pragma endregion OpenAI: TextModel

// OpenAI: TextToSpeechModel
#pragma region

namespace NCsOpenAI_TextToSpeechModel
{
	using EnumMapType = EMCsOpenAI_TextToSpeechModel;

	namespace Ref
	{
		CSGENAI_API CS_ADD_TO_ENUM_MAP_CUSTOM(GPT_4O_MINI_TTS, "gpt-4o-mini-tts");
		CSGENAI_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsOpenAI_TextToSpeechModel_MAX, "MAX");
	}
}

#pragma endregion TextToSpeechModel

// OpenAI: SpeechToTextModel
#pragma region

namespace NCsOpenAI_SpeechToTextModel
{
	using EnumMapType = EMCsOpenAI_SpeechToTextModel;

	namespace Ref
	{
		CSGENAI_API CS_ADD_TO_ENUM_MAP_CUSTOM(WHISPER_1, "whisper-1");
		CSGENAI_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsOpenAI_SpeechToTextModel_MAX, "MAX");
	}
}

#pragma endregion SpeechToTextModel