#include <Uefi.h>

#include <Library/BasicMathLib.h>

/**
  Simple Interger Add function
  
  @param  X                   Input X
  @param  Y                   Input Y

  @retval                     Return the add result
**/
UINTN 
BasicMathAddI (
  IN UINTN X,
  IN UINTN Y
  )
{
  return X+Y;
}