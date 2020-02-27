/** @file
  This sample application bases on HelloWorld PCD setting
  to print "UEFI Hello World!" to the UEFI Console.

  Copyright (c) 2006 - 2018, Intel Corporation. All rights reserved.<BR>
  SPDX-License-Identifier: BSD-2-Clause-Patent

**/

#include <Uefi.h>
#include <Library/UefiLib.h>
#include <Library/UefiApplicationEntryPoint.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/DebugLib.h>
#include <Library/HiiLib.h>
#include <Library/ShellLib.h>
#include <Library/ShellCommandLib.h>

#define GET_STRING_TOKEN(a) GetToken (STRING_TOKEN (a), gGuiAdkHiiHandle)

#define SHELL_EXERCISE_HII_1_APP_GUID \
{ \
  0x97b258de, 0x9647, 0x4997, {0xa5, 0x4f, 0xe9, 0x69, 0x37, 0xfa, 0x13, 0x3d} \
}
EFI_GUID             gShellExerciseHii1Guid = SHELL_EXERCISE_HII_1_APP_GUID;
EFI_HANDLE           gShellExerciseHii1HiiHandle = NULL;
extern UINT8         ExerciseHii1Strings[];

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
  
  Print (L"Ths is Exercise Hii-1\n");

  //
  // initialize the shell lib
  //
  Status = ShellInitialize();
  ASSERT_EFI_ERROR(Status);

  gShellExerciseHii1HiiHandle = HiiAddPackages (&gShellExerciseHii1Guid, gImageHandle, ExerciseHii1Strings, NULL);
  if (gShellExerciseHii1HiiHandle == NULL) {
    Status  = EFI_DEVICE_ERROR;
    return Status;
  }

  ShellPrintHiiEx(-1, -1, NULL, STRING_TOKEN (STR_HELLO_UNICODE_STRING), gShellExerciseHii1HiiHandle);

  return EFI_SUCCESS;
}
