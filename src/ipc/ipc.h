/***************************************************************************
 $RCSfile$
                             -------------------
    cvs         : $Id$
    begin       : Tue Sep 16 2003
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


#ifndef GWENHYWFAR_IPC_H
#define GWENHYWFAR_IPC_H

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup MOD_IPC
 *
 */
/*@{*/

/** @name Error Codes
 *
 */
/*@{*/
#define GWEN_IPC_ERROR_TYPE "IPC"
#define GWEN_IPC_ERROR_INQUEUE_FULL          1
#define GWEN_IPC_ERROR_OUTQUEUE_FULL         2
#define GWEN_IPC_ERROR_BAD_STATE             3
#define GWEN_IPC_ERROR_NO_CONNECTIONS        4
#define GWEN_IPC_ERROR_CONNECTION_NOT_FOUND  5
#define GWEN_IPC_ERROR_XMLFILE               6
#define GWEN_IPC_ERROR_SEG_NOT_FOUND         7
#define GWEN_IPC_ERROR_BAD_MSG               8
#define GWEN_IPC_ERROR_HANDSHAKING           9
#define GWEN_IPC_ERROR_BAD_DATA              10
#define GWEN_IPC_ERROR_INTERNAL              11
#define GWEN_IPC_ERROR_UNKNOWN_MSG           12
#define GWEN_IPC_ERROR_INVALID               13
#define GWEN_IPC_ERROR_GENERIC               14
#define GWEN_IPC_ERROR_INQUEUE_EMPTY         15
#define GWEN_IPC_ERROR_SOME_FAILED           16
#define GWEN_IPC_ERROR_REQUEST_NOT_FOUND     17
#define GWEN_IPC_ERROR_NO_DATA               18
/*@}*/ /* name */

  /** @defgroup MOD_IPC_LOWLEVEL Low Level IPC Functions
   */
  /*@{*/
  /** @defgroup MOD_IPC_TRANSPORTLAYER IPC Transport Layer */
  /** @defgroup MOD_IPC_MSGLAYER IPC Message Layer */
  /** @defgroup MOD_IPC_CONNLAYER IPC Connection Layer */
  /** @defgroup MOD_IPC_SERVICELAYER IPC Service Layer */
  /*@}*/ /* addtogroup */

  /** @defgroup MOD_IPC_MIDLEVEL Middle Level IPC Functions */
  /** @defgroup MOD_IPC_HIGHLEVEL High Level IPC Functions */
  /** @defgroup MOD_IPC_SECURITY Security Functions For IPC */


/*@}*/ /* addtogroup */

#ifdef __cplusplus
}
#endif


#endif /* GWENHYWFAR_IPC_H */



