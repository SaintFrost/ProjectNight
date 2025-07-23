// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/ShinbiAnimInstance.h"
#include "Characters/Shinbi.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

void UShinbiAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	// Getting the Character Movement Component from the Owner
	ShinbiCharacter = Cast<AShinbi>(TryGetPawnOwner());
	if (ShinbiCharacter)
	{
		CharacterMovement = ShinbiCharacter->GetCharacterMovement();	
	}
}

void UShinbiAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	// Accessing the GroundSpeed and IsFalling variables from the Character Movement Component of the Character
	// in this case, it's Shinbi
	if (CharacterMovement)
	{
		GroundSpeed = UKismetMathLibrary::VSizeXY(CharacterMovement->Velocity);
		IsFalling = CharacterMovement->IsFalling();
		MovementState = ShinbiCharacter->GetMovementState();
	}
}
