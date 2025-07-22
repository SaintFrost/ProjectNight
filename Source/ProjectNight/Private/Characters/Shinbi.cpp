// Developed by SaintFrost


#include "Characters/Shinbi.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

// Sets default values
AShinbi::AShinbi()
{
	PrimaryActorTick.bCanEverTick = true;

	// Camera Boom - TopDown Game: ArmLenght needs to be long and Camera needs to be at the top
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("Camera Boom"));
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));

	// Camera - Attaching Camera to the Camera Boom
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(CameraBoom);
}

void AShinbi::BeginPlay()
{
	Super::BeginPlay();

	// Assigning the DefaultContext to the Subsystem of the character
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultContext, 0);
		}
	}
}

void AShinbi::Move(const FInputActionValue& Value)
{
	if (Controller)
	{
		const FVector2d MovementVector = Value.Get<FVector2d>();
		
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AShinbi::Look(const FInputActionValue& Value)
{
}

void AShinbi::Jump()
{
	Super::Jump();
}

void AShinbi::Attack()
{
}

void AShinbi::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AShinbi::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AShinbi::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AShinbi::Look);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &AShinbi::Jump);
		EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Triggered, this, &AShinbi::Attack);
	}
}

