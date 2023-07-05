// Copyright GuardiansW. All Rights Reserved.
//
// Enum 관련 편의 함수 모음


#pragma once


#include <Misc\EnumRange.h>


#define ENUM_TO_STRING( Type, Value )             UtilEnum::EnumToString<Type>( Value )
#define STRING_TO_ENUM( Type, String )            UtilEnum::StringToEnum<Type>( String )
#define STRING_TO_ENUM_VAL( Type, String, Value ) UtilEnum::StringToEnum<Type>( String, Value )

// Enum 으로 Ranged base for loop 를 사용할 수 있게 하는 함수
// ENUM_RANGE_BY_COUNT( Type, Type::Max ) 가 선언되어있어야 함 ( 2번째 인자는 최대 갯수로 판별할 기준 )
#define ENUM_RANGE( Type ) TEnumRange<Type>()


namespace UtilEnum
{
	// UENUM To String 함수
	template<typename T>
	FString EnumToString( T InValue )
	{
		UEnum* enumClass = StaticEnum<T>();
		if ( !ensure( enumClass ) ) return FString();

		return enumClass->GetNameStringByValue( ( int64 )InValue );
	}

	template<typename T>
	T StringToEnum( const FString& InString, T InDefault = T::Max )
	{
		UEnum* enumClass = StaticEnum<T>();
		if ( !enumClass )
			return InDefault;

		int32 index = enumClass->GetValueByName( FName( InString ) );
		return ( index != INDEX_NONE ) ? ( T )index : InDefault;
	}
}