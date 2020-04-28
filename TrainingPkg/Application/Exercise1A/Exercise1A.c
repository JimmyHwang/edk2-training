#include <Uefi.h>
#include <Library/UefiLib.h>
#include <Library/UefiApplicationEntryPoint.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/BasicMathLib.h>
#include <Protocol/TextDrawProtocol.h>

/**
  The user Entry Point for Application. The user code starts with this function
  as the real entry point for the application.

  @param[in] ImageHandle    The firmware allocated handle for the EFI image.
  @param[in] SystemTable    A pointer to the EFI System Table.

  @retval EFI_SUCCESS       The entry point is executed successfully.
  @retval other             Some error occurs when executing this entry point.

**/
EFI_STATUS
EFIAPI
UefiMain (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
  EFI_STATUS Status;
  TEXT_DRAW_PROTOCOL *TextDraw;
  
  Print (L"Ths is Exercise 1-A\n");
  
  Status = gBS->LocateProtocol (&gTextDrawProtocolGuid, NULL, (VOID **)&TextDraw);
  if (!EFI_ERROR (Status)) {
    TextDraw->DrawRectangle (10, 10, L"*");    
  } else {
    Print (L"Error: TextDraw Protocol locate failed\n");
  }
  
  return EFI_SUCCESS;
}
