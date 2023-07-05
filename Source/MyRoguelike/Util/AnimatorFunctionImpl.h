#pragma once

// 각 함수의 정보는 아래 링크 참조
// http://easings.net


// 각 함수별 동작은 Animator.h 의 EAnimType 주석 참고 부탁드립니다
namespace AnimatorFunctionImpl
{
	namespace Linear
	{
		float Interpolate(float InAccTime, float InStartValue, float InDiffValue, float InEndTime);
	}

	namespace Pulse
	{
		float Interpolate(float InAccTime, float InStartValue, float InDiffValue, float InEndTime);
	}

	namespace Quadratic
	{
		float EaseIn(float InAccTime, float InStartValue, float InDiffValue, float InEndTime);
		float EaseOut(float InAccTime, float InStartValue, float InDiffValue, float InEndTime);
		float EaseInOut(float InAccTime, float InStartValue, float InDiffValue, float InEndTime);
		float EaseOutIn(float InAccTime, float InStartValue, float InDiffValue, float InEndTime);
	}

	namespace Cubic
	{
		float EaseIn(float InAccTime, float InStartValue, float InDiffValue, float InEndTime);
		float EaseOut(float InAccTime, float InStartValue, float InDiffValue, float InEndTime);
		float EaseInOut(float InAccTime, float InStartValue, float InDiffValue, float InEndTime);
		float EaseOutIn(float InAccTime, float InStartValue, float InDiffValue, float InEndTime);
	}
}