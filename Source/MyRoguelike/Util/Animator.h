// Fill out your copyright notice in the Description page of Project Settings.


#pragma once
#include <functional>


// =========================================
// 사용법
/*

*		매 틱에서 MyAnimator.Update(InDeltaTime) 호출

		// 사용 전 동작중이라면 중지
*		if(MyAnimator.IsRunning())
			MyAnimator.Stop();

		// param 값 세팅 ( Handle 은 세팅 안해도 됨 )
*		AnimatorParam param;
		param.AnimType = EAnimType::Linear;
		param.StartValue = 0.f;
		param.EndValue = 200.f;
		param.DurationTime = 3.f;

		// ** 주의 : Animator 의 Update 를 this 가 아닌 외부에서 호출하는 경우 댕글링 포인터가 될 수 있어 
		//			 TWeakObjectPtr<클래스> thisPtr = this 로 지역 변수를 선언하여 WeakPtr 로 캡처하여 사용 부탁드립니다

		//param.DurationFunc = [](float InCurValue) {};
		param.DurationFunc = [this](float InCurValue)
		{
			Position = Vector2D(InCurValue, InCurValue);
		};
		param.CompleteFunc = [this](float InCurValue)
		{
			Position = Vector2D(InCurValue, InCurValue);
		};

		// 애니메이터의 Start 함수를 호출해서 param 등록
*		MyAnimator.Start(param);

*/
// 이외에 버그 발생시 편하게 문의 부탁드립니다
// =========================================


// Invalid 값이라는거는 작동하지 않는 무의미한 상태를 나타내는 아이디
const	int InvalidHandleId = 0;
static	int HandleId		= 0;


// 애니메이션이 어떻게 변화하는지
enum class EAnimType {
	Linear,					// 선형 함수를 이용한 보간
	Pulse,					// 펄스 함수를 이용한 보간
	QuadraticEaseIn,		// 2차 함수를 이용한 서서히 빨라지는 보간
	QuadraticEaseOut,		// 2차 함수를 이용한 서서히 느려지는 보간
	QuadraticEaseInOut,		// 2차 함수를 이용한 빨라지다가 느려지는 보간
	QuadraticEaseOutIn,		// 2차 함수를 이용한 느려지다가 빨라지는 보간
	CubicEaseIn,			// 3차 함수를 이용한 서서히 빨라지는 보간
	CubicEaseOut,			// 3차 함수를 이용한 서서히 느려지는 보간
	CubicEaseInOut,			// 3차 함수를 이용한 빨라지다가 느려지는 보간
	CubicEaseOutIn,			// 3차 함수를 이용한 느려지다가 빨라지는 보간
	Max,
};


// 매 틱 혹은 애니메이션이 끝났을때 호출하는 함수 타입
typedef std::function<void( float )> CallbackType;
// 애니메이션 타입에 따라 호출할 함수 포인터
typedef std::function<float( float, float, float, float )> AnimatorFunction;


// 애니메이션을 어떻게 동작시킬것인지 파라미터 정보
class AnimatorParam 
{
public:
	// 해당 애니메이터를 특정지을수 있는 핸들값 (일단은 사용할 일은 없어 보입니다)
	int Handle;
	EAnimType AnimType;

	float StartValue;
	float EndValue;

	// 애니메이터의 지속 시간 (= 종료 시간)
	float DurationTime;

	// 매 틱마다 호출할 함수
	CallbackType DurationFunc;
	// 애니메이터 종료시 호출할 함수
	CallbackType CompleteFunc;

public:
	AnimatorParam();
};



// 특정 시간동안 시작값과 최종값 사이의 보간 애니메이션을 위한 애니메이터
class Animator
{
private:
	AnimatorParam Param;

	AnimatorFunction Function;

	float StartValue;
	float CurValue;
	float EndValue;

	// 애니메이션의 현재 소요 시간
	float AccTime;

	// 애니메이터의 종료 시간
	float EndTime;

public:
	// 생성자
	Animator();

	// 생성자
	Animator( const AnimatorParam& InParam );

	// 소멸자
	~Animator();

	// 애니메이션을 초기화하고 시작한다.
	bool Start( const AnimatorParam& InParam );

	// 애니메이션을 수동으로 업데이트한다.
	void Update( float InDeltaTime );

	// 애니메이션이 현재 동작중인지?
	bool IsRunning();

	// 현재 동작중인 애니메이션을 중지한다.
	void Stop( bool InCompleteEvent = false );

	// 애님 타입을 토대로 현재 값을 계산할 함수를 반환한다.
	static AnimatorFunction TypeToFunction( EAnimType InType );
};