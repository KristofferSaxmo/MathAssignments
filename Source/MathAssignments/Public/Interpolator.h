#pragma once

#include "InterpType.h"
#include "InterpObject.h"
#include "CurveDuration.h"
#include "LerpDuration.h"
#include "Interpolator.generated.h"

USTRUCT(Blueprintable)
struct FInterpolator
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Duration = 0.f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TEnumAsByte<EInterpType> Type = {};

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (EditCondition = "Type == EInterpType::Curve", EditConditionHides))
	UCurveFloat* CurveFloat = nullptr;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (EditCondition = "Type == EInterpType::Lerp", EditConditionHides))
	float From = 0.f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (EditCondition = "Type == EInterpType::Lerp", EditConditionHides))
	float To = 0.f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bLooping = false;
	
	void Initialize()
	{
		switch(Type)
		{
		case EInterpType::Curve:
			Instance = new FCurveDuration(Duration, bLooping, CurveFloat);
			break;
		default: case EInterpType::Lerp:
			Instance = new FLerpDuration(Duration, bLooping, From, To);
			break;
		}
	}

	void Update(const float DeltaTime) const
	{
		Instance->Update(DeltaTime);
	}

	float GetValue() const
	{
		return Instance->GetValue();
	}

	void Reset() const
	{
		Instance->Reset();
	}

private:
	FInterpObject* Instance = nullptr;
};