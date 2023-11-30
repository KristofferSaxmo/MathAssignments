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
	static bool AABBIntersect(const FVector MinA, const FVector MaxA, const FVector MinB, const FVector MaxB, FVector& ContactPoint, float& Depth)
	{
		if(MinA.X > MaxB.X || MinB.X > MaxA.X)
			return false;

		if(MinA.Y > MaxB.Y || MinB.Y > MaxA.Y)
			return false;

		if(MinA.Z > MaxB.Z || MinB.Z > MaxA.Z)
			return false;


		const auto CenterA = (MinA + MaxA ) / 2;
		const auto CenterB = (MinB + MaxB ) / 2;

		// Revert direction if A center is inside B bounds
		auto Direction = CenterB - CenterA;
		if(CenterA.X >= MinB.X && CenterA.X <= MaxB.X &&
			CenterA.Y >= MinB.Y && CenterA.Y <= MaxB.Y &&
			CenterA.Z >= MinB.Z && CenterA.Z <= MaxB.Z)
				Direction = -Direction;

		RayAABB(CenterA, Direction.GetSafeNormal(), MinB, MaxB, ContactPoint);

		const FVector Overlap = FVector(
			FMath::Min(MaxA.X, MaxB.X) - FMath::Max(MinA.X, MinB.X),
			FMath::Min(MaxA.Y, MaxB.Y) - FMath::Max(MinA.Y, MinB.Y),
			FMath::Min(MaxA.Z, MaxB.Z) - FMath::Max(MinA.Z, MinB.Z));
		
		Depth = FMath::Min3(Overlap.X, Overlap.Y, Overlap.Z);
		
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

	UFUNCTION(BlueprintCallable, Category = "Intersection")
	static bool RayAABB(
		const FVector Origin,
		const FVector Direction,
		const FVector Min,
		const FVector Max,
		FVector& ContactPoint)
	{
		const auto T1 = (Min.X - Origin.X) / Direction.X;
		const auto T2 = (Max.X - Origin.X) / Direction.X;
		const auto T3 = (Min.Y - Origin.Y) / Direction.Y;
		const auto T4 = (Max.Y - Origin.Y) / Direction.Y;
		const auto T5 = (Min.Z - Origin.Z) / Direction.Z;
		const auto T6 = (Max.Z - Origin.Z) / Direction.Z;

		// Find the largest minimum value
		const auto TMin = FMath::Max(
			FMath::Max(
				FMath::Min(T1,T2),
				FMath::Min(T3,T4)
				),
			FMath::Min(T5,T6)
			);

		// Find the smallest maximum value
		const auto TMax = FMath::Min(
			FMath::Min(
				FMath::Max(T1,T2),
				FMath::Max(T3,T4)
				),
			FMath::Max(T5,T6)
			);

		if(TMax < 0 || TMin > TMax)
			return false;

		const auto T = TMin < 0.f ? TMax : TMin;

		ContactPoint = Origin + (Direction * T);

		return true;
	}
};
