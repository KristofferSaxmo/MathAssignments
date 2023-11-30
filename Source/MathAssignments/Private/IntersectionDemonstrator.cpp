// Fill out your copyright notice in the Description page of Project Settings.


#include "..\Public\IntersectionDemonstrator.h"
#include "IntersectionSubsystem.h"

// Sets default values
AIntersectionDemonstrator::AIntersectionDemonstrator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AIntersectionDemonstrator::BeginPlay()
{
	Super::BeginPlay();

	const auto SubSystem = GetWorld()->GetSubsystem<UIntersectionSubsystem>();
	SubSystem->RegisterDemonstrator(this);
}

// Called every frame
void AIntersectionDemonstrator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	DrawShape();
	Color = FColor::Green;
}

void AIntersectionDemonstrator::DrawShape() const
{
	switch (IntersectionType.GetValue())
	{
	case Sphere:
		DrawDebugSphere(GetWorld(), GetActorLocation(), Radius, 16, Color, false, -1, 0, 1);
		break;

	case AABB:
		DrawDebugBox(GetWorld(), GetActorLocation(), Size * 0.5f, Color, false, -1, 0, 1);
		break;
	}
}

bool AIntersectionDemonstrator::ShouldTickIfViewportsOnly() const
{
	return true;
}

void AIntersectionDemonstrator::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	const FName Property = PropertyChangedEvent.Property->GetFName();

	if (Property == GET_MEMBER_NAME_CHECKED(AIntersectionDemonstrator, IntersectionType))
	{
		switch (IntersectionType.GetValue())
		{
		case Sphere:
			Size = FVector::ZeroVector;
			bCollision = false;
			break;
		case AABB:
			Radius = 0.f;
			break;
		}
	}
}

