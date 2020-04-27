#ifndef __TEXT_DRAW_H__
#define __TEXT_DRAW_H__

//
// Forward reference for pure ANSI compatability
//
typedef struct _TEXT_DRAW_PROTOCOL  TEXT_DRAW_PROTOCOL;

/**
  Draw a text rectangle on screen 

  @param  X           Position-X
  @param  Y           Position-Y
  @param  Width       Width of rectangle
  @param  Height      Height of rectangle
  @param  Character   Special character to draw

  @retval EFI_SUCCESS   Run successful

**/
typedef
EFI_STATUS
(EFIAPI *TEXT_DRAW_RECTANGLE)(
  IN  UINTN X,
  IN  UINTN Y,
  IN  UINTN Width,
  IN  UINTN Height,
  IN  CHAR16 *Character
  );

struct _TEXT_DRAW_PROTOCOL {
  TEXT_DRAW_RECTANGLE                  DrawRectangle;
};

extern EFI_GUID gTextDrawProtocolGuid;

#endif
