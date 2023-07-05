// Generic 하게 사용할 수 있는 Util Class 모음


#pragma once


// Id Generator, 고유 Id 값을 만들어내는 클래스
template<typename T>
struct TIdGenerator
{
	T CurId;
	T StartId;
	T EndId;

	TIdGenerator() : CurId(1), StartId(1), EndId(10000) {}
	TIdGenerator(T InStartId, T InEndId) : CurId(InStartId), StartId(InStartId), EndId(InEndId) {}

	FORCEINLINE operator T() const { return CurId; }

	FORCEINLINE TIdGenerator& operator++()
	{
		_Inc();
		return *this;
	}

	FORCEINLINE TIdGenerator operator++(int32)
	{
		TIdGenerator copy(*this);
		_Inc();
		return copy;
	}

	FORCEINLINE void Reset() { CurId = StartId; }

	FORCEINLINE T GetId() const { return CurId; }

private:
	FORCEINLINE void _Inc()
	{
		if (EndId < StartId)
			CurId = StartId;

		++CurId;
	}
};
typedef TIdGenerator<int32> FIdGeneratorInt;


// 별도로 Tick 주기를 체크할 수 있는 클래스
struct FIntervalTimer
{
	//static const int8 Loop = -1; // 인터벌 타이머 무한 반복 값
	//static const int8 Stop = 0; // 인터벌 타이머 중지 값

	float IntervalAcc;  // 누적 값
	float Interval;		// 체크할 시간
	int8  Repeat;		// 반복 여부
	int8  RepeatOrigin; // 설정한 반복 횟수

	FIntervalTimer() : IntervalAcc( 0.f ), Interval( 0.f ), Repeat( 0 ) {}
	FIntervalTimer( float InInterval, int8 InRepeat = -1 ) : IntervalAcc( 0.f ), Interval( InInterval ), Repeat( InRepeat ), RepeatOrigin( InRepeat ) {}

	FORCEINLINE bool Tick(float InDeltaSeconds)
	{
		if (Repeat == 0)
			return false;

		IntervalAcc += InDeltaSeconds;

		if (IntervalAcc < Interval)
			return false;

		if (Repeat > 0)
		{
			IntervalAcc = 0.f;
			Repeat--;
			return true;
		}
		else if (Repeat == -1)
		{
			IntervalAcc = 0.f;
			return true;
		}

		return false;
	}

	// 시간 초기화
	FORCEINLINE void Reset() { IntervalAcc = 0.f; Repeat = RepeatOrigin; }

	// 시간 초기화
	FORCEINLINE void Reset( float InInterval, int8 InRepeat = -1 ) { IntervalAcc = 0.f; Interval = InInterval; Repeat = InRepeat; RepeatOrigin = InRepeat; }

	// 시간 정지
	FORCEINLINE void Stop() { Repeat = 0; }

	// 바로 완료 처리, 다음 틱에서 바로 true 반환
	FORCEINLINE void Complete() { IntervalAcc = Interval + 1.f; }
};

template<typename T>
FORCEINLINE T* LoadSoftObject(TSoftObjectPtr<T> InSoftObj)
{
	FSoftObjectPath path = InSoftObj.ToSoftObjectPath();
	if(!path.IsValid())
		return nullptr;
	
	return LoadObject<T>(nullptr, *path.ToString());
}