// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include <Logging/LogVerbosity.h>
#include <Logging/LogMacros.h>


// =============================================================
// __pragma message Ŀ���� �޽��� ����
// 
// ���� [ TODO ] ������ ���� �۾� ���� �α׸� ����
// =============================================================
#define __chSTR(x) #x
#define chSTR(x)  __chSTR(x)

// �����ε�, ���� ���� �뵵�� ��� �ּ� �� ���忡�� ( �۾��� ) �� �ݵ�� ���ٰ�
// ex) TODO( "�׽�Ʈ ��, ���� ���� ����", ( ũ�� ) )
#define __TODO(msg, name) message(__FILE__ "(" chSTR(__LINE__) "): [ TODO ] " #msg " " #name)
#define TODO(msg, name) __pragma(__TODO(msg, name)) 

// �ڵ� �Ծ࿡ ���� �ʰų� �� ���� �ڵ� �ۼ� ����� �ִ� ��� ������� �������� ����ϰ��� �մϴ�
// ����ں��� �ش� �ڸ�Ʈ Ȯ���ϼ����� ���� �� �����ֽø� �˴ϴ�
#define __COMMENT(msg, name) message(__FILE__ "(" chSTR(__LINE__) "): [ COMMENT ] " #msg " " #name)
#define COMMENT(msg, name) __pragma(__COMMENT(msg, name)) 

// �ڵ� �ۼ� �����ؼ� �� ���� ����� �ִ� ��� ������� �������� ����ϰ��� �մϴ�
// ����ں��� �ش� �ڸ�Ʈ Ȯ���ϼ����� �����ֽø� �˴ϴ�
// ( ���� Tip ��� �����Ͻ� �ʿ�� �����ϴ�! ���� ����! )
#define __TIP(msg, name) message(__FILE__ "(" chSTR(__LINE__) "): [ TIP ] " #msg " " #name)
#define TIP(msg, name) __pragma(__TIP(msg, name)) 



#define FUNCTION_NAME __FUNCTION__ TEXT("()")

// =============================================================
// Log Category ����
// �α� ī�װ� �߰� �� GameLog.cpp ���� ���� �߰��ؾ� ��.
// =============================================================
DECLARE_LOG_CATEGORY_EXTERN(GameLog, Log, All);


// ���� �����ÿ��� �αװ� ���ŵ˴ϴ�.
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
// ��ũ�� ��� �α׿� ���Ǵ� Define ����
// Order ���� -1 �� �� �������ּ���
// #else ~ #endif ���̿� �߰��Ǵ� �߰� #define �� UE_BUILD_SHIPPING ���� ���� �������ֽø� �˴ϴ�.
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
// ��� �α׿� ���Ǵ� Define ����
// =============================================================
// GameLog        : ���͸� �� �� �ִ� ī�װ�
// LogVerbosity : Log, Warning, Error �� �α� �߿䵵
// Prefix       : ���λ� - Format �޽��� �ܿ� �߰����� ���λ縦 ����� ���ֽ��ϴ�
// Format       : �ڿ� �ٴ� ... ���� �μ��� ���� ���ڿ� �������� �����մϴ�
// ex) LOG( TEXT( "CurrValue : %d" ), Value );
#define CUSTOM_LOG( LogVerbosity, Prefix, Format, ... )     { __LOG( GameLog,       LogVerbosity, Prefix,             Format, ##__VA_ARGS__ ); }
#define LOG( Format, ... )                                  { __LOG( GameLog,       Log,          TEXT( "" ),         Format, ##__VA_ARGS__ ); }
#define WARN_LOG( Format, ... )                             { __LOG( GameLog,       Warning,      TEXT( "!!" ),       Format, ##__VA_ARGS__ ); }
#define ERROR_LOG( Format, ... )                            { __LOG( GameLog,       Error,        TEXT( "**" ),       Format, ##__VA_ARGS__ ); }

// �ϴ��� �ּ�ó�� �� #define �� ���� �α� Ÿ�� �߰��� ������ �� �ִ� �����Դϴ�
// Catetgory �� ������ ���͸��� �����ϵ��� �߰��ϰų� Ư�� LogVerbosity, Ȥ�� Ư�� ���λ� �αװ� �ʿ��ϴٸ� �߰����ּ���
// Log Category ���� �߰� �ʿ�
/*
#define LOG_SKILL   ( Format, ...                     )		{ __LOG( GameLogSkill , Warning,      TEXT( "!!" ),       Format, ##__VA_ARGS__ ); }
#define CONTENT_LOG1( Format, ...                     )		{ __LOG( GameLog������, Log,          TEXT( "���λ�" ),   Format, ##__VA_ARGS__ ); }
#define CONTENT_LOG2( Format, ...                     )		{ __LOG( GameLog������, Warning,      TEXT( "���λ�" ),   Format, ##__VA_ARGS__ ); }
#define CONTENT_LOG3( Format, ...                     )		{ __LOG( GameLog������, Error,        TEXT( "���λ�" ),   Format, ##__VA_ARGS__ ); }
*/