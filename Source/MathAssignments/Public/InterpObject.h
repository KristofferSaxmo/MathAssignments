#pragma once

class FInterpObject
{
	float Time = 0.f;
	
protected:
	float Duration = 0;
	float CurrentValue = 0;
	float T = 0;
	
public:
	FInterpObject(const float Duration)
	{
		this->Duration = Duration;
		Time = 0.f;
	}
	
	virtual void Update(const float DeltaTime)
	{
		Time += DeltaTime;
		Time = FMath::Clamp(Time, 0, Duration);
		T = Time / Duration;
	}

	float GetValue() const
	{
		return CurrentValue;
	}

	void Reset()
	{
		Time = 0.f;
	}
};