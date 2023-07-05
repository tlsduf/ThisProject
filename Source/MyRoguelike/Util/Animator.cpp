// Fill out your copyright notice in the Description page of Project Settings.


#include "Animator.h"
#include "AnimatorFunctionImpl.h"


// =============================================================
// 애니메이터 파람 생성자
// =============================================================
AnimatorParam::AnimatorParam()
	: Handle( InvalidHandleId )
	, AnimType( EAnimType::Linear )
	, StartValue( 0.f )
	, EndValue( 1.f )
	, DurationTime( 1.f )
	, DurationFunc( nullptr )
	, CompleteFunc( nullptr )
{

}

// =============================================================
// 생성자
// =============================================================
Animator::Animator()
	: Param( AnimatorParam() )
	, Function( nullptr )
	, StartValue( 0.f )
	, CurValue( 0.f )
	, EndValue( 0.f )
	, AccTime( 0.f )
	, EndTime( 0.f )
{

}

// =============================================================
// 생성자
// =============================================================
Animator::Animator( const AnimatorParam& InParam )
	: Param( AnimatorParam() )
	, Function( nullptr )
	, StartValue( 0.f )
	, CurValue( 0.f )
	, EndValue( 0.f )
	, AccTime( 0.f )
	, EndTime( 0.f )
{
	Start( InParam );
}

// =============================================================
// 소멸자
// =============================================================
Animator::~Animator()
{

}

// =============================================================
// 애니메이터 정보를 설정한 후 시작
// =============================================================
bool Animator::Start( const AnimatorParam& InParam )
{
	// 애니메이션 타입이 아직 구현안된거면 중지
	if ( InParam.AnimType == EAnimType::Max )
	{
		return false;
	}

	Function = Animator::TypeToFunction( InParam.AnimType );

	Param = InParam;
	Param.Handle = ++HandleId;

	StartValue = InParam.StartValue;
	CurValue = InParam.StartValue;
	EndValue = InParam.EndValue;

	AccTime = 0.f;
	EndTime = InParam.DurationTime;

	return true;
}

// =============================================================
// 애니메이터 업데이트
// =============================================================
void Animator::Update( float InDeltaTime )
{
	if ( !IsRunning() )
		return;

	AccTime += InDeltaTime;

	if ( AccTime >= EndTime )
	{
		Stop( true );
		return;
	}

	float elapsedTime = EndTime < AccTime ? EndTime : AccTime;

	if ( Function )
		CurValue = Function( elapsedTime * 1000.f, StartValue, EndValue - StartValue, EndTime * 1000.f );

	if ( Param.DurationFunc )
		Param.DurationFunc( CurValue );
}

// =============================================================
// 현재 애니메이터가 동작하는중인지?
// =============================================================
bool Animator::IsRunning()
{
	return Param.Handle != InvalidHandleId;
}

// =============================================================
// 애니메이터 중지
// =============================================================
void Animator::Stop( bool InCompleteEvent )
{
	if ( InCompleteEvent )
	{
		if ( Param.CompleteFunc )
			Param.CompleteFunc( EndValue );
	}

	Param = AnimatorParam();
	StartValue = 0.f;
	CurValue = 0.f;
	EndValue = 0.f;

	AccTime = 0.f;
	EndTime = 0.f;
}

// =============================================================
// 타입을 통해 보간 함수를 연결한다.
// =============================================================
AnimatorFunction Animator::TypeToFunction( EAnimType InType )
{
	switch ( InType )
	{
	case EAnimType::Linear:					return AnimatorFunctionImpl::Linear::Interpolate;
	case EAnimType::Pulse:					return AnimatorFunctionImpl::Pulse::Interpolate;
	case EAnimType::QuadraticEaseIn:		return AnimatorFunctionImpl::Quadratic::EaseIn;
	case EAnimType::QuadraticEaseOut:		return AnimatorFunctionImpl::Quadratic::EaseOut;
	case EAnimType::QuadraticEaseInOut:		return AnimatorFunctionImpl::Quadratic::EaseInOut;
	case EAnimType::QuadraticEaseOutIn:		return AnimatorFunctionImpl::Quadratic::EaseOutIn;
	case EAnimType::CubicEaseIn:			return AnimatorFunctionImpl::Cubic::EaseIn;
	case EAnimType::CubicEaseOut:			return AnimatorFunctionImpl::Cubic::EaseOut;
	case EAnimType::CubicEaseInOut:			return AnimatorFunctionImpl::Cubic::EaseInOut;
	case EAnimType::CubicEaseOutIn:			return AnimatorFunctionImpl::Cubic::EaseOutIn;
	}

	return nullptr;
}