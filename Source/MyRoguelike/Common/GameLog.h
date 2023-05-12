// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include <Logging/LogVerbosity.h>
#include <Logging/LogMacros.h>


// =============================================================
// __pragma message 커스텀 메시지 정의
// 
// 현재 [ TODO ] 형태의 추후 작업 예정 로그만 구현
// =============================================================
#define __chSTR(x) #x
#define chSTR(x)  __chSTR(x)

// 리마인드, 추후 수정 용도로 사용 주석 끝 문장에는 ( 작업자 ) 를 반드시 써줄것
// ex) TODO( "테스트 중, 추후 수정 예정", ( 크로 ) )
#define __TODO(msg, name) message(__FILE__ "(" chSTR(__LINE__) "): [ TODO ] " #msg " " #name)
#define TODO(msg, name) __pragma(__TODO(msg, name)) 

// 코딩 규약에 맞지 않거나 더 나은 코드 작성 방법이 있는 경우 남기려는 목적으로 사용하고자 합니다
// 담당자분은 해당 코멘트 확인하셨으면 수정 후 지워주시면 됩니다
#define __COMMENT(msg, name) message(__FILE__ "(" chSTR(__LINE__) "): [ COMMENT ] " #msg " " #name)
#define COMMENT(msg, name) __pragma(__COMMENT(msg, name)) 

// 코드 작성 관련해서 더 나은 방법이 있는 경우 남기려는 목적으로 사용하고자 합니다
// 담당자분은 해당 코멘트 확인하셨으면 지워주시면 됩니다
// ( 굳이 Tip 대로 수정하실 필요는 없습니다! 개인 취향! )
#define __TIP(msg, name) message(__FILE__ "(" chSTR(__LINE__) "): [ TIP ] " #msg " " #name)
#define TIP(msg, name) __pragma(__TIP(msg, name)) 



#define FUNCTION_NAME __FUNCTION__ TEXT("()")

// =============================================================
// Log Category 정의
// 로그 카테고리 추가 시 GameLog.cpp 에도 같이 추가해야 함.
// =============================================================
DECLARE_LOG_CATEGORY_EXTERN(GameLog, Log, All);


// 실제 배포시에는 로그가 제거됩니다.
#if UE_BUILD_SHIPPING
#define __LOG( Category, LogVerbosity, Prefix, Format, ...) {}
#define LOG_SCREEN( Format, ... ) {}
#define LOG_SCREEN_COLOR( Color, Format, ... ) {}
#else
#define __LOG( Category, LogVerbosity, Prefix, Format, ... )					 \
	{																				 \
		FString msg = FString::Printf( TEXT( "%s : " ), FUNCTION_NAME );			 \
		msg += FString::Printf( Format, ##__VA_ARGS__ );							 \
		UE_LOG( Category, LogVerbosity, TEXT( "%s %s" ), Prefix, *msg );			 \
	}
// =============================================================
// 스크린 출력 로그에 사용되는 Define 모음
// Order 값이 -1 인 점 주의해주세요
// #else ~ #endif 사이에 추가되는 추가 #define 은 UE_BUILD_SHIPPING 에도 같이 정의해주시면 됩니다.
// =============================================================
#define LOG_SCREEN( Format, ... )												 \
	{																				 \
		FString msg = FString::Printf( TEXT( "%s : " ), FUNCTION_NAME );			 \
		msg += FString::Printf( Format, ##__VA_ARGS__ );							 \
		UE_LOG( GameLog, Log, TEXT( "%s" ), *msg );									 \
		GEngine->AddOnScreenDebugMessage( -1, 3.0f, FColor::White, msg );			 \
	}
#define LOG_SCREEN_COLOR( Color, Format, ... )									 \
	{																				 \
		FString msg = FString::Printf( TEXT( "%s : " ), FUNCTION_NAME );			 \
		msg += FString::Printf( Format, ##__VA_ARGS__ );							 \
		UE_LOG( GameLog, Log, TEXT( "%s" ), *msg );									 \
		GEngine->AddOnScreenDebugMessage( -1, 3.0f, Color, msg );					 \
	}
#endif

// =============================================================
// 출력 로그에 사용되는 Define 모음
// =============================================================
// GameLog        : 필터링 할 수 있는 카테고리
// LogVerbosity : Log, Warning, Error 등 로그 중요도
// Prefix       : 접두사 - Format 메시지 외에 추가적인 접두사를 사용할 수있습니다
// Format       : 뒤에 붙는 ... 가변 인수에 따라서 문자열 포맷팅을 수행합니다
// ex) LOG( TEXT( "CurrValue : %d" ), Value );
#define CUSTOM_LOG( LogVerbosity, Prefix, Format, ... )     { __LOG( GameLog,       LogVerbosity, Prefix,             Format, ##__VA_ARGS__ ); }
#define LOG( Format, ... )                                  { __LOG( GameLog,       Log,          TEXT( "" ),         Format, ##__VA_ARGS__ ); }
#define WARN_LOG( Format, ... )                             { __LOG( GameLog,       Warning,      TEXT( "!!" ),       Format, ##__VA_ARGS__ ); }
#define ERROR_LOG( Format, ... )                            { __LOG( GameLog,       Error,        TEXT( "**" ),       Format, ##__VA_ARGS__ ); }

// 하단의 주석처리 된 #define 은 추후 로그 타입 추가시 참고할 수 있는 예시입니다
// Catetgory 를 별도의 필터링이 가능하도록 추가하거나 특정 LogVerbosity, 혹은 특정 접두사 로그가 필요하다면 추가해주세요
// Log Category 정의 추가 필요
/*
#define LOG_SKILL   ( Format, ...                     )		{ __LOG( GameLogSkill , Warning,      TEXT( "!!" ),       Format, ##__VA_ARGS__ ); }
#define CONTENT_LOG1( Format, ...                     )		{ __LOG( GameLog컨텐츠, Log,          TEXT( "접두사" ),   Format, ##__VA_ARGS__ ); }
#define CONTENT_LOG2( Format, ...                     )		{ __LOG( GameLog컨텐츠, Warning,      TEXT( "접두사" ),   Format, ##__VA_ARGS__ ); }
#define CONTENT_LOG3( Format, ...                     )		{ __LOG( GameLog컨텐츠, Error,        TEXT( "접두사" ),   Format, ##__VA_ARGS__ ); }
*/