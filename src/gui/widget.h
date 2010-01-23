/***************************************************************************
    begin       : Wed Jan 20 2010
    copyright   : (C) 2010 by Martin Preuss
    email       : martin@libchipcard.de

 ***************************************************************************
 *                                                                         *
 *   This library is free software; you can redistribute it and/or         *
 *   modify it under the terms of the GNU Lesser General Public            *
 *   License as published by the Free Software Foundation; either          *
 *   version 2.1 of the License, or (at your option) any later version.    *
 *                                                                         *
 *   This library is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU     *
 *   Lesser General Public License for more details.                       *
 *                                                                         *
 *   You should have received a copy of the GNU Lesser General Public      *
 *   License along with this library; if not, write to the Free Software   *
 *   Foundation, Inc., 59 Temple Place, Suite 330, Boston,                 *
 *   MA  02111-1307  USA                                                   *
 *                                                                         *
 ***************************************************************************/


#ifndef GWENHYWFAR_GUI_WIDGET_H
#define GWENHYWFAR_GUI_WIDGET_H


#include <gwenhywfar/tree.h>


typedef struct GWEN_WIDGET GWEN_WIDGET;

#ifdef __cplusplus
extern "C" {
#endif


GWEN_TREE_FUNCTION_LIB_DEFS(GWEN_WIDGET, GWEN_Widget, GWENHYWFAR_API)


#define GWEN_WIDGET_FLAGS_NONE  0x00000000L
#define GWEN_WIDGET_FLAGS_FILLX 0x80000000L
#define GWEN_WIDGET_FLAGS_FILLY 0x40000000L



typedef enum {
    GWEN_Widget_TypeUnknown=-1,
    GWEN_Widget_TypeNone=0,
    GWEN_Widget_TypeLabel=1,
    GWEN_Widget_TypePushButton,
    GWEN_Widget_TypeLineEdit,
    GWEN_Widget_TypeTextEdit,
    GWEN_Widget_TypeComboBox,
    GWEN_Widget_TypeRadioButton,
    GWEN_Widget_TypeProgressBar,
    GWEN_Widget_TypeRadioGroup,
    GWEN_Widget_TypeGroupBox,
    GWEN_Widget_TypeHSpacer,
    GWEN_Widget_TypeVSpacer,
    GWEN_Widget_TypeHLayout,
    GWEN_Widget_TypeVLayout,
    GWEN_Widget_TypeGridLayout,
    GWEN_Widget_TypeImage,
    GWEN_Widget_TypeListBox
} GWEN_WIDGET_TYPE;




#ifdef __cplusplus
}
#endif



/* other gwen headers */
#include <gwenhywfar/dialog.h>



#ifdef __cplusplus
extern "C" {
#endif


void GWEN_Widget_free(GWEN_WIDGET *w);


GWEN_DIALOG *GWEN_Widget_GetDialog(const GWEN_WIDGET *w);

const char *GWEN_Widget_GetName(const GWEN_WIDGET *w);
void GWEN_Widget_SetName(GWEN_WIDGET *w, const char *s);

uint32_t GWEN_Widget_GetFlags(const GWEN_WIDGET *w);
void GWEN_Widget_SetFlags(GWEN_WIDGET *w, uint32_t fl);
void GWEN_Widget_AddFlags(GWEN_WIDGET *w, uint32_t fl);
void GWEN_Widget_SubFlags(GWEN_WIDGET *w, uint32_t fl);

GWEN_WIDGET_TYPE GWEN_Widget_GetType(const GWEN_WIDGET *w);
void GWEN_Widget_SetType(GWEN_WIDGET *w, GWEN_WIDGET_TYPE t);

int GWEN_Widget_GetColumns(const GWEN_WIDGET *w);
void GWEN_Widget_SetColumns(GWEN_WIDGET *w, int i);

int GWEN_Widget_GetRows(const GWEN_WIDGET *w);
void GWEN_Widget_SetRows(GWEN_WIDGET *w, int i);

const char *GWEN_Widget_GetText(const GWEN_WIDGET *w);
void GWEN_Widget_SetText(GWEN_WIDGET *w, const char *s);


GWEN_WIDGET_TYPE GWEN_Widget_Type_fromString(const char *s);
const char *GWEN_Widget_Type_toString(GWEN_WIDGET_TYPE t);

uint32_t GWEN_Widget_Flags_fromString(const char *s);



#ifdef __cplusplus
}
#endif


#endif
