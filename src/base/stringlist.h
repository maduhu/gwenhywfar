/***************************************************************************
 $RCSfile$
 -------------------
 cvs         : $Id$
 begin       : Thu Apr 03 2003
 copyright   : (C) 2003 by Martin Preuss
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

#ifndef GWENHYWFAR_STRINGLIST_H
#define GWENHYWFAR_STRINGLIST_H

#include <gwenhywfar/gwenhywfarapi.h>


#ifdef __cplusplus
extern "C" {
#endif


GWENHYWFAR_API typedef struct GWEN_STRINGLISTENTRYSTRUCT GWEN_STRINGLISTENTRY;


GWENHYWFAR_API typedef struct GWEN_STRINGLISTSTRUCT GWEN_STRINGLIST;


GWENHYWFAR_API GWEN_STRINGLIST *GWEN_StringList_new();
GWENHYWFAR_API void GWEN_StringList_free(GWEN_STRINGLIST *sl);
GWENHYWFAR_API void GWEN_StringList_Clear(GWEN_STRINGLIST *sl);

GWENHYWFAR_API
  unsigned int GWEN_StringList_Count(GWEN_STRINGLIST *sl);

GWENHYWFAR_API GWEN_STRINGLISTENTRY *GWEN_StringListEntry_new(const char *s,
                                                              int take);
GWENHYWFAR_API void GWEN_StringListEntry_ReplaceString(GWEN_STRINGLISTENTRY *e,
                                                       const char *s,
                                                       int take);
GWENHYWFAR_API void GWEN_StringListEntry_free(GWEN_STRINGLISTENTRY *sl);
GWENHYWFAR_API void GWEN_StringList_AppendEntry(GWEN_STRINGLIST *sl,
                                                GWEN_STRINGLISTENTRY *se);
GWENHYWFAR_API void GWEN_StringList_RemoveEntry(GWEN_STRINGLIST *sl,
                                                GWEN_STRINGLISTENTRY *se);
GWENHYWFAR_API
  GWEN_STRINGLISTENTRY *GWEN_StringList_FirstEntry(GWEN_STRINGLIST *sl);
GWENHYWFAR_API
  GWEN_STRINGLISTENTRY *GWEN_StringListEntry_Next(GWEN_STRINGLISTENTRY *se);

GWENHYWFAR_API
  const char *GWEN_StringListEntry_Data(GWEN_STRINGLISTENTRY *se);

/**
 * Appends a string.
 * @return 0 if not appended, !=0 if appended
 * @param take if true then the StringList takes over ownership of the string
 * @param checkDouble if true the the string will only be appended if it
 * does not already exist
 */
GWENHYWFAR_API int GWEN_StringList_AppendString(GWEN_STRINGLIST *sl,
                                                const char *s,
                                                int take,
                                                int checkDouble);

/**
 * Inserts a string.
 * @return 0 if not inserted, !=0 if inserted
 * @param take if true then the StringList takes over ownership of the string
 * @param checkDouble if true the the string will only be appended if it
 * does not already exist
 */
GWENHYWFAR_API int GWEN_StringList_InsertString(GWEN_STRINGLIST *sl,
                                                const char *s,
                                                int take,
                                                int checkDouble);

/**
 * Removes a given string from the stringlist.
 * @return 0 if not found, !=0 if found and removed
 */
GWENHYWFAR_API int GWEN_StringList_RemoveString(GWEN_STRINGLIST *sl,
                                                const char *s);



#ifdef __cplusplus
}
#endif

#endif


