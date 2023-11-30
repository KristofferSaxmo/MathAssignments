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
	for (int32 A = 0; A < Demonstrators.Num(); ++A)
	{
		for (int32 B = A + 1; B < Demonstrators.Num(); ++B)
		{
			if (Demonstrators[A] == Demonstrators[B]) continue;
			
			if (Demonstrators[A]->IntersectionType == Sphere &&
				Demonstrators[B]->IntersectionType == Sphere)
			{
				if (UIntersection::SphereIntersect(
					Demonstrators[A]->GetActorLocation(),
					Demonstrators[A]->Radius,
					Demonstrators[B]->GetActorLocation(),
					Demonstrators[B]->Radius))
				{
					Demonstrators[A]->Color = FColor::Red;
					Demonstrators[B]->Color = FColor::Red;
				}

				continue;
			}

			if (Demonstrators[A]->IntersectionType == AABB &&
				Demonstrators[B]->IntersectionType == AABB)
			{
				FVector ContactPoint;
				float Depth;

				if (UIntersection::AABBIntersect(
					Demonstrators[A]->GetActorLocation() - Demonstrators[A]->Size / 2,
					Demonstrators[A]->GetActorLocation() + Demonstrators[A]->Size / 2,
					Demonstrators[B]->GetActorLocation() - Demonstrators[B]->Size / 2,
					Demonstrators[B]->GetActorLocation() + Demonstrators[B]->Size / 2,
					ContactPoint,
					Depth))
				{
					Demonstrators[A]->Color = FColor::Red;
					Demonstrators[B]->Color = FColor::Red;

					if (!(Demonstrators[A]->bCollision && Demonstrators[B]->bCollision)) continue;

					FVector CollisionResult = (ContactPoint - Demonstrators[B]->GetActorLocation()) / (Demonstrators[B]->Size / 2);

					for (int32 i = 0; i < 3; i++)
					{
						if (!FMath::IsNearlyEqual(FMath::Abs(CollisionResult[i]), 1.0f))
							CollisionResult[i] = 0;
					}

					FVector PostCollisionLocation = Demonstrators[A]->GetActorLocation() + CollisionResult * Depth;

					Demonstrators[A]->SetActorLocation(PostCollisionLocation);
				}
				continue;
			}

			if (Demonstrators[A]->IntersectionType == Sphere && Demonstrators[B]->IntersectionType == AABB)
			{
				if (UIntersection::SphereAABBIntersect(
					Demonstrators[A]->GetActorLocation(),	
					Demonstrators[A]->Radius,
					Demonstrators[B]->GetActorLocation() - Demonstrators[B]->Size/2,
					Demonstrators[B]->GetActorLocation() + Demonstrators[B]->Size/2))
				{
					Demonstrators[A]->Color = FColor::Red;
					Demonstrators[B]->Color = FColor::Red;
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
