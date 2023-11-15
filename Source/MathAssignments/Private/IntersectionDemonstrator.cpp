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

bool AIntersectionDemonstrator::ShouldTickIfViewportsOnly() const
{
	return true;
}

void AIntersectionDemonstrator::DrawShape() const
{
	switch (IntersectionType.GetValue())
	{
	case Sphere:
		DrawDebugSphere(GetWorld(), GetActorLocation(), Radius, 16, Color, false, -1, 0, 1);
		break;

	case AABB:
		DrawDebugBox(GetWorld(), GetActorLocation(), FVector(0.5f * (Max.X - Min.X), 0.5f * (Max.Y - Min.Y), 0.5f * (Max.Z - Min.Z)), Color, false, -1, 0, 1);
		break;
	}
}

