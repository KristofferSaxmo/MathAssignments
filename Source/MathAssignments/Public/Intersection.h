// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Intersection.generated.h"

/**
 * 
 */
UCLASS()
class MATHASSIGNMENTS_API UIntersection : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	
	UFUNCTION(BlueprintCallable, Category="Intersection")
	static bool SphereIntersect(FVector LocationA, float RadiusA, FVector LocationB, float RadiusB)
	{
		const auto DistanceSquared = FVector::DistSquared(LocationA, LocationB);
		const auto SumOfRadiiSquared = FMath::Square(RadiusA + RadiusB);
		return DistanceSquared <= SumOfRadiiSquared;
	}

	UFUNCTION(BlueprintCallable, Category="Intersection")
	static bool AABBIntersect(const FVector MinA, const FVector MaxA, const FVector MinB, const FVector MaxB)
	{
		if(MinA.X > MaxB.X || MinB.X > MaxA.X)
			return false;

		if(MinA.Y > MaxB.Y || MinB.Y > MaxA.Y)
			return false;

		if(MinA.Z > MaxB.Z || MinB.Z > MaxA.Z)
			return false;

		return true;
	}	

	UFUNCTION(BlueprintCallable, Category="Intersection")
	static bool SphereAABBIntersect(const FVector Location, const float Radius, const FVector Min, const FVector Max)
	{
		const auto ClosestPoint = FVector(
			FMath::Clamp(Location.X, Min.X, Max.X),
			FMath::Clamp(Location.Y, Min.Y, Max.Y),
			FMath::Clamp(Location.Z, Min.Z, Max.Z)
		);

		const auto Distance = FVector::Dist(Location, ClosestPoint);
		return Distance <= Radius;
	}
};
