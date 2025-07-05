#include "Types/CsTypes_GenAI.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsTypes_GenAI)

namespace NCsGenAIService
{
	using EnumMapType = EMCsGenAIService;

	namespace Ref
	{
		CSGENAI_API CS_ADD_TO_ENUM_MAP_CUSTOM(OPENAI, "Open AI");
		CSGENAI_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsGenAIService_MAX, "MAX");
	}
}

namespace NCsTextModel
{
	using EnumMapType = EMCsTextModel;

	namespace Ref
	{
		CSGENAI_API CS_ADD_TO_ENUM_MAP_CUSTOM(GPT_4_1, "gpt-4.1");
		CSGENAI_API CS_ADD_TO_ENUM_MAP_CUSTOM(GPT_4O, "gpt-4o");
		CSGENAI_API CS_ADD_TO_ENUM_MAP_CUSTOM(GPT_4_1_MINI, "gpt-4.1-mini");
		CSGENAI_API CS_ADD_TO_ENUM_MAP_CUSTOM(GPT_4O_MINI, "gpt-4o-mini");
		CSGENAI_API CS_ADD_TO_ENUM_MAP_CUSTOM(GPT_4_1_NANO, "gpt-4.1-nano");
		CSGENAI_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsTextModel_MAX, "MAX");
	}
}

namespace NCsTextToSpeechModel
{
	using EnumMapType = EMCsTextToSpeechModel;

	namespace Ref
	{
		CSGENAI_API CS_ADD_TO_ENUM_MAP_CUSTOM(GPT_4O_MINI_TTS, "gpt-4o-mini-tts");
		CSGENAI_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsTextToSpeechModel_MAX, "MAX");
	}
}

namespace NCsSpeechToTextModel
{
	using EnumMapType = EMCsSpeechToTextModel;

	namespace Ref
	{
		CSGENAI_API CS_ADD_TO_ENUM_MAP_CUSTOM(WHISPER_1, "whisper-1");
		CSGENAI_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsSpeechToTextModel_MAX, "MAX");
	}
}