// Developed by SaintFrost

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "GameFramework/Character.h"
#include "Characters/CharacterStates.h"
#include "Shinbi.generated.h"

class UCameraComponent;
class USpringArmComponent;

class UInputMappingContext;
class UInputAction;

class UAnimMontage;

UCLASS()
class PROJECTNIGHT_API AShinbi : public ACharacter
{
	GENERATED_BODY()

public:
	AShinbi();

	virtual void Tick(float DeltaTime) override;
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	virtual void BeginPlay() override;

	// Input Mapping Context
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputMappingContext* DefaultContext;

	/**
	 * Input Actions
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* AttackAction;

	/**
	 * Enhanced Input Action Functions
	 */
	void Move(const FInputActionValue& Value);
	virtual void Jump() override;
	void Attack();

	void PlayAttackMontage();
	bool CanAttack();

	UFUNCTION(BlueprintCallable)
	void AttackEnd();
	
private:
	/**
	 * Enum States
	 */
	EMovementState MovementState = EMovementState::EMS_Idle;

	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	EActionState ActionState = EActionState::EAS_Unoccupied;

	/**
	 * Components
	 */
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* Camera;

	/**
	 * Animation Montages
	 */
	UPROPERTY(EditDefaultsOnly, Category = Montages)
	UAnimMontage* AttackMontage1;

public:
	FORCEINLINE EMovementState GetMovementState() const {return MovementState;}
};
