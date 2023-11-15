// Fill out your copyright notice in the Description page of Project Settings.


#include "IntersectionSubsystem.h"
#include "Intersection.h"

void UIntersectionSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UIntersectionSubsystem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	for (const auto DemonstratorA : Demonstrators)
	{
		for (const auto DemonstratorB : Demonstrators)
		{
			if (DemonstratorA == DemonstratorB) continue;

			if (DemonstratorA->IntersectionType == Sphere &&
				DemonstratorB->IntersectionType == Sphere)
			{
				if (UIntersection::SphereIntersect(
					DemonstratorA->GetActorLocation(),
					DemonstratorA->Radius,
					DemonstratorB->GetActorLocation(),
					DemonstratorB->Radius))
				{
					DemonstratorA->Color = FColor::Red;
					DemonstratorB->Color = FColor::Red;
				}

				continue;
			}

			if (DemonstratorA->IntersectionType == AABB &
				DemonstratorB->IntersectionType == AABB)
			{
				if (UIntersection::AABBIntersect(
					DemonstratorA->GetActorLocation() + DemonstratorA->Min,
					DemonstratorA->GetActorLocation() + DemonstratorA->Max,
					DemonstratorB->GetActorLocation() + DemonstratorB->Min,
					DemonstratorB->GetActorLocation() + DemonstratorB->Max))
				{
					DemonstratorA->Color = FColor::Red;
					DemonstratorB->Color = FColor::Red;
				}

				continue;
			}

			if (DemonstratorA->IntersectionType == Sphere &
				DemonstratorB->IntersectionType == AABB)
			{
				if (UIntersection::SphereAABBIntersect(
					DemonstratorA->GetActorLocation(),
					DemonstratorA->Radius,
					DemonstratorB->GetActorLocation() + DemonstratorA->Min,
					DemonstratorB->GetActorLocation() + DemonstratorA->Max))
				{
					DemonstratorA->Color = FColor::Red;
					DemonstratorB->Color = FColor::Red;
				}
			}
		}
	}
}

void UIntersectionSubsystem::RegisterDemonstrator(AIntersectionDemonstrator* Demonstrator)
{
	if (Demonstrators.Contains(Demonstrator)) return;
	Demonstrators.Add(Demonstrator);
}

void UIntersectionSubsystem::UnregisterDemonstrator(AIntersectionDemonstrator* Demonstrator)
{
	if (!Demonstrators.Contains(Demonstrator)) return;
	Demonstrators.Remove(Demonstrator);
}

TStatId UIntersectionSubsystem::GetStatId() const
{
	return TStatId();
}
