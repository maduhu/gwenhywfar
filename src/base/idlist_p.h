/***************************************************************************
 $RCSfile$
                             -------------------
    cvs         : $Id$
    begin       : Mon Mar 01 2004
    copyright   : (C) 2004 by Martin Preuss
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



#ifndef GWENHYWFAR_IDLIST_P_H
#define GWENHYWFAR_IDLIST_P_H

#include <gwenhywfar/types.h>
#include <gwenhywfar/misc.h>
#include <gwenhywfar/idlist.h>


#define GWEN_IDTABLE_MAXENTRIES 16


typedef struct GWEN_IDTABLE GWEN_IDTABLE;
GWEN_LIST_FUNCTION_DEFS(GWEN_IDTABLE, GWEN_IdTable);
struct GWEN_IDTABLE {
  GWEN_LIST_ELEMENT(GWEN_IDTABLE);
  GWEN_TYPE_UINT32 freeEntries;
  GWEN_TYPE_UINT32 entries[GWEN_IDTABLE_MAXENTRIES];
  GWEN_TYPE_UINT32 current;
};

GWEN_IDTABLE *GWEN_IdTable_new();
void GWEN_IdTable_free(GWEN_IDTABLE *idt);

int GWEN_IdTable_AddId(GWEN_IDTABLE *idt, GWEN_TYPE_UINT32 id);
int GWEN_IdTable_HasId(const GWEN_IDTABLE *idt, GWEN_TYPE_UINT32 id);
int GWEN_IdTable_DelId(GWEN_IDTABLE *idt, GWEN_TYPE_UINT32 id);
int GWEN_IdTable_IsEmpty(const GWEN_IDTABLE *idt);
int GWEN_IdTable_IsFull(const GWEN_IDTABLE *idt);
GWEN_TYPE_UINT32 GWEN_IdTable_GetFirstId(GWEN_IDTABLE *idt);
GWEN_TYPE_UINT32 GWEN_IdTable_GetNextId(GWEN_IDTABLE *idt);
unsigned int GWEN_IdTable_GetCount(const GWEN_IDTABLE *idt);

struct GWEN_IDLIST {
  GWEN_IDTABLE_LIST *idTables;
  GWEN_TYPE_UINT32 entryCount;
  GWEN_IDTABLE *current;
};




#endif /* GWENHYWFAR_IDLIST_P_H */
