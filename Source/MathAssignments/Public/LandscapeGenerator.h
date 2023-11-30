// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProceduralMeshComponent.h"
#include "LandscapeGenerator.generated.h"

UCLASS()
class MATHASSIGNMENTS_API ALandscapeGenerator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALandscapeGenerator();

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Landscape")
	float Scale;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Landscape")
	int32 GridSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Landscape")
	float NoiseScale;


	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	TArray<FVector> Vertices;
	TArray<int32> Triangles;
	TArray<FVector> Normals;
	TArray<FVector2D> UVs;
	TArray<FProcMeshTangent> Tangents;
	
	void GenerateMesh();

	virtual bool ShouldTickIfViewportsOnly() const override;
	
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UProceduralMeshComponent* ProceduralMesh;
};
