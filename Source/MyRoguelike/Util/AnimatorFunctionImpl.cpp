#include "AnimatorFunctionImpl.h"


float AnimatorFunctionImpl::Linear::Interpolate(float InAccTime, float InStartValue, float InDiffValue, float InEndTime)
{
	return InDiffValue * InAccTime / InEndTime + InStartValue;
}

float AnimatorFunctionImpl::Pulse::Interpolate(float InAccTime, float InStartValue, float InDiffValue, float InEndTime)
{
	if (InAccTime < InEndTime / 2.f)
		return InStartValue;
	else
		return InDiffValue + InStartValue;
}

float AnimatorFunctionImpl::Quadratic::EaseIn(float InAccTime, float InStartValue, float InDiffValue, float InEndTime)
{
	InAccTime /= InEndTime;

	return InDiffValue * InAccTime * InAccTime + InStartValue;
}

float AnimatorFunctionImpl::Quadratic::EaseOut(float InAccTime, float InStartValue, float InDiffValue, float InEndTime)
{
	InAccTime /= InEndTime;

	return -InDiffValue * InAccTime * (InAccTime - 2.f) + InStartValue;
}

float AnimatorFunctionImpl::Quadratic::EaseInOut(float InAccTime, float InStartValue, float InDiffValue, float InEndTime)
{
	InAccTime /= InEndTime / 2.f;

	if (InAccTime < 1.f)
	{
		return InDiffValue / 2.f * InAccTime * InAccTime + InStartValue;
	}
	else
	{
		InAccTime--;

		return -InDiffValue / 2.f * (InAccTime * (InAccTime - 2.f) - 1.f) + InStartValue;
	}
}

float AnimatorFunctionImpl::Quadratic::EaseOutIn(float InAccTime, float InStartValue, float InDiffValue, float InEndTime)
{
	if (InAccTime < InEndTime / 2)
		return EaseOut(InAccTime * 2.f, InStartValue, InDiffValue / 2.f, InEndTime);
	else
		return EaseIn((InAccTime * 2.f) - InEndTime, InStartValue + InDiffValue / 2.f, InDiffValue / 2.f, InEndTime);
}

float AnimatorFunctionImpl::Cubic::EaseIn(float InAccTime, float InStartValue, float InDiffValue, float InEndTime)
{
	InAccTime /= InEndTime;

	return InDiffValue * InAccTime * InAccTime * InAccTime + InStartValue;
}

float AnimatorFunctionImpl::Cubic::EaseOut(float InAccTime, float InStartValue, float InDiffValue, float InEndTime)
{
	InAccTime = InAccTime / InEndTime - 1.f;

	return InDiffValue * (InAccTime * InAccTime * InAccTime + 1.f) + InStartValue;
}

float AnimatorFunctionImpl::Cubic::EaseInOut(float InAccTime, float InStartValue, float InDiffValue, float InEndTime)
{
	InAccTime /= InEndTime / 2.f;

	if (InAccTime < 1.f)
	{
		return InDiffValue / 2.f * InAccTime * InAccTime * InAccTime + InStartValue;
	}
	else
	{
		InAccTime -= 2.f;

		return InDiffValue / 2.f * (InAccTime * InAccTime * InAccTime + 2.f) + InStartValue;
	}
}

float AnimatorFunctionImpl::Cubic::EaseOutIn(float InAccTime, float InStartValue, float InDiffValue, float InEndTime)
{
	if (InAccTime < InEndTime / 2.f)
		return EaseOut(InAccTime * 2.f, InStartValue, InDiffValue / 2.f, InEndTime);
	else
		return EaseIn((InAccTime * 2.f) - InEndTime, InStartValue + InDiffValue / 2.f, InDiffValue / 2.f, InEndTime);
}