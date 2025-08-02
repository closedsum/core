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

#pragma endregion OpenAI: TextToSpeechModel

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

#pragma endregion OpenAI: SpeechToTextModel

// OpenAI: Voice
#pragma region

namespace NCsOpenAI_Voice
{
	using EnumMapType = EMCsOpenAI_Voice;

	namespace Ref
	{
		CSGENAI_API CS_ADD_TO_ENUM_MAP_CUSTOM(ALLOY, "allow");
		CSGENAI_API CS_ADD_TO_ENUM_MAP_CUSTOM(ASH, "ash");
		CSGENAI_API CS_ADD_TO_ENUM_MAP_CUSTOM(BALLAD, "ballad");
		CSGENAI_API CS_ADD_TO_ENUM_MAP_CUSTOM(CORAL, "coral");
		CSGENAI_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECHO, "echo");
		CSGENAI_API CS_ADD_TO_ENUM_MAP_CUSTOM(FABLE, "fable");
		CSGENAI_API CS_ADD_TO_ENUM_MAP_CUSTOM(ONYX, "onyx");
		CSGENAI_API CS_ADD_TO_ENUM_MAP_CUSTOM(NOVA, "nova");
		CSGENAI_API CS_ADD_TO_ENUM_MAP_CUSTOM(SAGE, "sage");
		CSGENAI_API CS_ADD_TO_ENUM_MAP_CUSTOM(SHIMMER, "shimmer");
		CSGENAI_API CS_ADD_TO_ENUM_MAP_CUSTOM(VERSE, "verse");	
		CSGENAI_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsOpenAI_Voice_MAX, "MAX");
	}
}

#pragma endregion OpenAI: Voice