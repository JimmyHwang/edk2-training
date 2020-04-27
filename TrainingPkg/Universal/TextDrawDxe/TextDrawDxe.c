#include <PiDxe.h>

#include <Library/PrintLib.h>
#include <Library/DebugLib.h>
#include <Library/UefiLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiDriverEntryPoint.h>

#include <Protocol/TextDrawProtocol.h>

STATIC EFI_HANDLE  mTextDrawHandle = NULL;

/**
  Draw a text rectangle on screen 

  @param  X           Position-X
  @param  Y           Position-Y
  @param  Width       Width of rectangle
  @param  Height      Height of rectangle
  @param  Character   Special character to draw

  @retval EFI_SUCCESS   Run successful

**/
EFI_STATUS
EFIAPI
TextDrawRectangle (
  IN  UINTN X,            // Unsupported yet
  IN  UINTN Y,            // Unsupported yet
  IN  UINTN Width,
  IN  UINTN Height,
  IN  CHAR16 *Character
  )
{
  EFI_STATUS Status;
  UINTN H;
  UINTN W;
  
  Status = EFI_SUCCESS;
  
  for (H=0; H<Height; H++) {
    for (W=0; W<Width; W++) {
      Print(Character);
    }
    Print(L"\n");
  }
  
  return Status;
}

CONST TEXT_DRAW_PROTOCOL mTextDrawProtocol = {
  TextDrawRectangle
};

/**
  The user Entry Point for Text Draw module.

  @param[in] ImageHandle    The firmware allocated handle for the EFI image.
  @param[in] SystemTable    A pointer to the EFI System Table.

  @retval EFI_SUCCESS       The entry point is executed successfully.
  @retval Others            Some error occurs when executing this entry point.

**/
EFI_STATUS
EFIAPI
TextDrawEntryPoint (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  )
{
  EFI_STATUS  Status;

  Status = gBS->InstallMultipleProtocolInterfaces (
                  &mTextDrawHandle,
                  &gTextDrawProtocolGuid, &mTextDrawProtocol,
                  NULL
                  );
  ASSERT_EFI_ERROR (Status);

  return Status;
}
