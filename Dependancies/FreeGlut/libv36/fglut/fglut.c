
/* Copyright (c) Mark J. Kilgard, 1994. */

/* This program is freely distributable without licensing fees
   and is provided without guarantee or warrantee expressed or
   implied. This program is -not- in the public domain. */

#ifndef WRAPPERS_ONLY

#include <glutint.h>

extern int __Argc;
extern char **__Argv;

static GLUTmenuStateFCB fortranMenuStateFunc;

void
glutnull_(void)
{
}

void
glutinit_(void)
{
  glutInit(&__Argc, __Argv);
}

static void
fortranMenuStateWrapper(int value)
{
  fortranMenuStateFunc(&value);
}

static void
fortranReshapeWrapper(int w, int h)
{
  (*__glutCurrentWindow->freshape) (&w, &h);
}

static void
fortranKeyboardWrapper(unsigned char ch, int x, int y)
{
  int chi = ch;

  (*__glutCurrentWindow->fkeyboard) (&chi, &x, &y);
}

static void
fortranMouseWrapper(int btn, int state, int x, int y)
{
  (*__glutCurrentWindow->fmouse) (&btn, &state, &x, &y);
}

static void
fortranMotionWrapper(int x, int y)
{
  (*__glutCurrentWindow->fmotion) (&x, &y);
}

static void
fortranPassiveMotionWrapper(int x, int y)
{
  (*__glutCurrentWindow->fpassive) (&x, &y);
}

static void
fortranEntryWrapper(int state)
{
  (*__glutCurrentWindow->fentry) (&state);
}

static void
fortranVisibilityWrapper(int state)
{
  (*__glutCurrentWindow->fvisibility) (&state);
}

static void
fortranTimerWrapper(int value)
{
  /* relies on special knowledge that __glutTimerList points to 
     the GLUTtimer* currently being processed! */
  (*__glutTimerList->ffunc) (&value);
}

static void
fortranSelectWrapper(int value)
{
  (*__glutItemSelected->menu->fselect) (&value);
}

static void
fortranSpecialWrapper(int key, int x, int y)
{
  (*__glutCurrentWindow->fspecial) (&key, &x, &y);
}

static void
fortranSpaceballMotionWrapper(int x, int y, int z)
{
  (*__glutCurrentWindow->fspaceMotion) (&x, &y, &z);
}

static void
fortranSpaceballRotateWrapper(int x, int y, int z)
{
  (*__glutCurrentWindow->fspaceRotate) (&x, &y, &z);
}

static void
fortranSpaceballButtonWrapper(int button, int state)
{
  (*__glutCurrentWindow->fspaceButton) (&button, &state);
}

static void
fortranTabletMotionWrapper(int x, int y)
{
  (*__glutCurrentWindow->ftabletMotion) (&x, &y);
}

static void
fortranTabletButtonWrapper(int button, int state, int x, int y)
{
  (*__glutCurrentWindow->ftabletButton) (&button, &state, &x, &y);
}

static void
fortranDialsWrapper(int dial, int value)
{
  (*__glutCurrentWindow->fdials) (&dial, &value);
}

static void
fortranButtonBoxWrapper(int button, int state)
{
  (*__glutCurrentWindow->fbuttonBox) (&button, &state);
}

#endif /* WRAPPERS_ONLY */

#define glutfunc(Name,name) \
void \
glut##name##func(GLUT##name##FCB name) \
{ \
    if(name == (GLUT##name ## FCB) glutnull_) { \
	glut##Name ## Func(NULL); \
    } else { \
	glut ## Name ## Func(fortran ## Name ## Wrapper); \
	__glutCurrentWindow->f ## name = name; \
    } \
}

glutfunc(Reshape, reshape)
glutfunc(Keyboard, keyboard)
glutfunc(Mouse, mouse)
glutfunc(Motion, motion)
glutfunc(Entry, entry)
glutfunc(Visibility, visibility)
glutfunc(Special, special)
glutfunc(Dials, dials)

/* special callback cases */

/* The display has no parameters passed so no need for wrapper. */
void
glutdisplayfunc(GLUTdisplayFCB display)
{
  glutDisplayFunc((GLUTdisplayCB) display);
}

void
glutpassivemotionfunc(GLUTpassiveFCB passive)
{
  if (passive == (GLUTpassiveFCB) glutnull_) {
    glutPassiveMotionFunc(NULL);
  } else {
    glutPassiveMotionFunc(fortranPassiveMotionWrapper);
    __glutCurrentWindow->fpassive = passive;
  }
}

void
glutspacemotionfunc(GLUTspaceMotionFCB spaceMotion)
{
  if (spaceMotion == (GLUTspaceMotionFCB) glutnull_) {
    glutSpaceballMotionFunc(NULL);
  } else {
    glutSpaceballMotionFunc(fortranSpaceballMotionWrapper);
    __glutCurrentWindow->fspaceMotion = spaceMotion;
  }
}

void
glutspacerotatefunc(GLUTspaceRotateFCB spaceRotate)
{
  if (spaceRotate == (GLUTspaceRotateFCB) glutnull_) {
    glutSpaceballRotateFunc(NULL);
  } else {
    glutSpaceballRotateFunc(fortranSpaceballRotateWrapper);
    __glutCurrentWindow->fspaceRotate = spaceRotate;
  }
}

void
glutspacebuttonfunc(GLUTspaceButtonFCB spaceButton)
{
  if (spaceButton == (GLUTspaceButtonFCB) glutnull_) {
    glutSpaceballButtonFunc(NULL);
  } else {
    glutSpaceballButtonFunc(fortranSpaceballButtonWrapper);
    __glutCurrentWindow->fspaceButton = spaceButton;
  }
}

void
glutbuttonboxfunc(GLUTbuttonBoxFCB buttonBox)
{
  if (buttonBox == (GLUTbuttonBoxFCB) glutnull_) {
    glutButtonBoxFunc(NULL);
  } else {
    glutButtonBoxFunc(fortranButtonBoxWrapper);
    __glutCurrentWindow->fbuttonBox = buttonBox;
  }
}

void
gluttabletmotionfunc(GLUTtabletMotionFCB tabletMotion)
{
  if (tabletMotion == (GLUTtabletMotionFCB) glutnull_) {
    glutTabletMotionFunc(NULL);
  } else {
    glutTabletMotionFunc(fortranTabletMotionWrapper);
    __glutCurrentWindow->ftabletMotion = tabletMotion;
  }
}

void
gluttabletbuttonfunc(GLUTtabletButtonFCB tabletButton)
{
  if (tabletButton == (GLUTtabletButtonFCB) glutnull_) {
    glutTabletButtonFunc(NULL);
  } else {
    glutTabletButtonFunc(fortranTabletButtonWrapper);
    __glutCurrentWindow->ftabletButton = tabletButton;
  }
}

int
glutcreatemenu(GLUTselectFCB selectFunc)
{
  int menu;

  menu = glutCreateMenu(fortranSelectWrapper);
  __glutCurrentMenu->fselect = selectFunc;
  return menu;
}

void
gluttimerfunc(unsigned long interval, GLUTtimerFCB timerFunc, int value)
{
  glutTimerFunc((unsigned int) interval, fortranTimerWrapper, value);
  /* relies on special __glutNewTimer variable side effect to
     establish Fortran timer func! */
  __glutNewTimer->ffunc = timerFunc;
}

void
glutidlefunc(GLUTidleFCB idleFunc)
{
  if (idleFunc == (GLUTidleFCB) glutnull_) {
    glutIdleFunc(NULL);
  } else {
    glutIdleFunc(idleFunc);
  }
}

void
glutmenustatefunc(GLUTmenuStateFCB menuStateFunc)
{
  if (menuStateFunc == (GLUTmenuStateFCB) glutnull_) {
    glutMenuStateFunc(NULL);
  } else {
    glutMenuStateFunc(fortranMenuStateWrapper);
    fortranMenuStateFunc = menuStateFunc;
  }
}

void
glutbitmapcharacter(int *font, int ch)
{
  /* 
   * mkf2c gets confused by double pointers and void* pointers.
   * So mkf2c does not complain, we consider the font handle to
   * be an int*.  But we really get an int** since Fortran
   * passes by reference.  So to "pedantically decode" the 
   * pointer, cast it first to int**, then dereference it,
   * then cast the result to a void*.
   */
  void *trueFont = (void *) *((int **) font);

  glutBitmapCharacter(trueFont, ch);
}

void
glutstrokecharacter(int *font, int ch)
{
  /* 
   * mkf2c gets confused by double pointers and void* pointers.
   * So mkf2c does not complain, we consider the font handle to
   * be an int*.  But we really get an int** since Fortran
   * passes by reference.  So to "pedantically decode" the 
   * pointer, cast it first to int**, then dereference it,
   * then cast the result to a void*.
   */
  void *trueFont = (void *) *((int **) font);

  glutStrokeCharacter(trueFont, ch);
}
