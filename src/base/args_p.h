/***************************************************************************
 $RCSfile$
                             -------------------
    cvs         : $Id$
    begin       : Sat Apr 24 2004
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

#ifndef GWENHYWFAR_ARGS_P
#define GWENHYWFAR_ARGS_P

#include <gwenhywfar/args.h>


typedef enum {
  GWEN_ArgsElementTypeFreeParam=0,
  GWEN_ArgsElementTypeShort,
  GWEN_ArgsElementTypeLong
} GWEN_ARGS_ELEMENT_TYPE;


int GWEN_Args_UsageTXT(const GWEN_ARGS *args, GWEN_BUFFER *ubuf);
int GWEN_Args_UsageHTML(const GWEN_ARGS *args, GWEN_BUFFER *ubuf);
int GWEN_Args__AppendTXT(GWEN_BUFFER *ubuf, const char *s, unsigned int ins);



#endif /* GWENHYWFAR_ARGS_P */



