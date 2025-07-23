// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Characters/CharacterStates.h"
#include "ShinbiAnimInstance.generated.h"

class UCharacterMovementComponent;
class AShinbi;

/**
 * 
 */
UCLASS()
class PROJECTNIGHT_API UShinbiAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	
	UPROPERTY(BlueprintReadOnly)
	AShinbi* ShinbiCharacter;

	UPROPERTY(BlueprintReadOnly, Category = Movement)
	UCharacterMovementComponent* CharacterMovement;
	
	UPROPERTY(BlueprintReadOnly, Category = Movement)
	float GroundSpeed;

	UPROPERTY(BlueprintReadOnly, Category = Movement)
	bool IsFalling;

	UPROPERTY(BlueprintReadOnly, Category = "Movement | Character State")
	EMovementState MovementState;
};
