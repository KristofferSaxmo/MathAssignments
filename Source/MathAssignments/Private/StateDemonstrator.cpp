// Fill out your copyright notice in the Description page of Project Settings.
#include "MathAssignments/Public/StateDemonstrator.h"
#include "DrawDebugHelpers.h"
#include "RelativeContextCalculator.h"

// Sets default values
AStateDemonstrator::AStateDemonstrator()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	SetRootComponent(StaticMeshComponent);
}

void AStateDemonstrator::BeginPlay()
{
	Super::BeginPlay();
	ScaleInterpolator.Initialize();
	RotationInterpolator.Initialize();

	Health = 100.f;
}

void AStateDemonstrator::UpdateDemonstrator(float DeltaTime, AActor* const Actor)
{
	const int32 RelativeContext = URelativeContextCalculator::CalculateContextFlags(this, Actor);
		
	const bool IsInFront = (RelativeContext & static_cast<int32>(ERelativeContext::InFront)) != 0;
	const bool IsBehind = (RelativeContext & static_cast<int32>(ERelativeContext::Behind)) != 0;
	const bool IsAbove = (RelativeContext & static_cast<int32>(ERelativeContext::Above)) != 0;
	const bool IsBelow = (RelativeContext & static_cast<int32>(ERelativeContext::Below)) != 0;
	const bool IsToTheRight = (RelativeContext & static_cast<int32>(ERelativeContext::ToTheRight)) != 0;
	const bool IsToTheLeft = (RelativeContext & static_cast<int32>(ERelativeContext::ToTheLeft)) != 0;
	const bool IsClose = (RelativeContext & static_cast<int32>(ERelativeContext::Close)) != 0;
	const bool IsFar = (RelativeContext & static_cast<int32>(ERelativeContext::Far)) != 0;
		
	UStaticMeshComponent* MeshComponent = Actor->FindComponentByClass<UStaticMeshComponent>();
	UMaterialInstanceDynamic* DynMaterial = MeshComponent->CreateDynamicMaterialInstance(0);

	if (IsInFront)
		UE_LOG(LogTemp, Warning, TEXT("Front"));

	if (IsBehind)
		UE_LOG(LogTemp, Warning, TEXT("Behind"));

	if (IsAbove)
		DynMaterial->SetVectorParameterValue("Color", FLinearColor::Red);
			
	if (IsBelow)
		DynMaterial->SetVectorParameterValue("Color", FLinearColor::Blue);

	if (IsToTheRight)
		UE_LOG(LogTemp, Warning, TEXT("Right"));
		
	if (IsToTheLeft)
		UE_LOG(LogTemp, Warning, TEXT("Left"));

	if (IsClose)
	{
		Actor->SetActorScale3D(FVector(1, 1, 1));
		FVector Direction = Actor->GetActorLocation() - GetActorLocation();
		float Distance = Direction.Size();
		Direction.Normalize();
		Actor->SetActorLocation(Actor->GetActorLocation() + Direction * DeltaTime * (1100 - Distance) * 0.5f);
	}

	if (IsFar)
		Actor->SetActorScale3D(FVector(2, 2, 2));


	MeshComponent->SetMaterial(0, DynMaterial);
}

// Called every frame
void AStateDemonstrator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ScaleInterpolator.Update(DeltaTime);
	const float ScaleValue = ScaleInterpolator.GetValue();
	const FVector NewScale = FVector(ScaleValue, ScaleValue, ScaleValue);
	StaticMeshComponent->GetChildComponent(0)->SetRelativeScale3D(NewScale);

	RotationInterpolator.Update(DeltaTime);
	const float RotationValue = RotationInterpolator.GetValue();
	const FRotator NewRotation = FRotator(0, RotationValue, 0);
	StaticMeshComponent->GetChildComponent(0)->SetRelativeRotation(NewRotation);
	
	for (const auto Actor : Demonstrators)
	{
		if (Actor == nullptr)
			continue;
		
		UpdateDemonstrator(DeltaTime, Actor);
	}
}

bool AStateDemonstrator::ShouldTickIfViewportsOnly() const
{
	return false;
}
