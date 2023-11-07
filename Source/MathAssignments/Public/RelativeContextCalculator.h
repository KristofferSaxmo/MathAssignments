// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "RelativeContextCalculator.generated.h"

UENUM(Meta = (Bitflags))
enum class ERelativeContext
{
	None		= 0,
	InFront		= 1 << 0,
	Behind		= 1 << 1,
	Above		= 1 << 2,
	Below		= 1 << 3,
	ToTheRight	= 1 << 4,
	ToTheLeft	= 1 << 5,
	Close		= 1 << 6,
	Far			= 1 << 7,
};

UCLASS()
class MATHASSIGNMENTS_API URelativeContextCalculator : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()


public:
	UFUNCTION(BlueprintCallable, Category="Context")
	static int32 CalculateContextFlags(AActor* Target, AActor* Other)
	{
		int32 ContextFlags = 0;

		const auto TargetLocation = Target->GetActorLocation();
		const auto OtherLocation = Other->GetActorLocation();
		const auto Direction = OtherLocation - TargetLocation;

		// Get relative location of Other to Target
		const auto LocalSpaceLocation = Target->GetActorTransform().InverseTransformPosition(OtherLocation);

		// In front
		if(LocalSpaceLocation.X > 0)
			ContextFlags |= static_cast<int32>(ERelativeContext::InFront);

		// Behind
		else if(LocalSpaceLocation.X < 0)
			ContextFlags |= static_cast<int32>(ERelativeContext::Behind);

		// Right
		if(LocalSpaceLocation.Y > 0)
			ContextFlags |= static_cast<int32>(ERelativeContext::ToTheRight);

		// Left
		else if(LocalSpaceLocation.Y < 0)
			ContextFlags |= static_cast<int32>(ERelativeContext::ToTheLeft);

		// Above
		if(LocalSpaceLocation.Z > 0)
			ContextFlags |= static_cast<int32>(ERelativeContext::Above);

		// Below
		else if(LocalSpaceLocation.Z < 0)
			ContextFlags |= static_cast<int32>(ERelativeContext::Below);

		// Close
		if(Direction.Size() < 500)
			ContextFlags |= static_cast<int32>(ERelativeContext::Close);

		// Far
		else if(Direction.Size() > 500)
			ContextFlags |= static_cast<int32>(ERelativeContext::Far);

		return ContextFlags;
	}
};
