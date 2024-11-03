// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once

#define CS_DECLARE_STATIC_LOG_LEVEL static void(*LogLevel)(const FString&);
#define CS_DEFINE_STATIC_LOG_LEVEL(__ClassType, __LogFn) void(*__ClassType::LogLevel)(const FString&) = &__LogFn
#define CS_DECLARE_STATIC_LOG_WARNING static void(*LogWarning)(const FString&);
#define CS_DEFINE_STATIC_LOG_WARNING(__ClassType, __LogFn) void(*__ClassType::LogWarning)(const FString&) = &__LogFn
#define CS_DECLARE_STATIC_LOG_ERROR static void(*LogError)(const FString&);
#define CS_DEFINE_STATIC_LOG_ERROR(__ClassType, __LogFn) void(*__ClassType::LogError)(const FString&) = &__LogFn


// Assume the "default" value = LogLevel
#define CS_FN_PARAM_DEFAULT_LOG_LEVEL void(*Log)(const FString&) = LogLevel
#define CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT void(*Log)(const FString&) /*=LogLevel*/
// Assume the "default" value = LogWarning
#define CS_FN_PARAM_DEFAULT_LOG_WARNING void(*Log)(const FString&) = LogWarning
#define CS_FN_PARAM_DEFAULT_LOG_WARNING_COMMENT void(*Log)(const FString&) /*=LogWarning*/
// Assume the "default" value = LogError
#define CS_FN_PARAM_DEFAULT_LOG_ERROR void(*Log)(const FString&) = LogError
#define CS_FN_PARAM_DEFAULT_LOG_ERROR_COMMENT void(*Log)(const FString&) /*=LogError*/