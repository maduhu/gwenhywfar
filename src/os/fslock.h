/***************************************************************************
 $RCSfile$
                             -------------------
    cvs         : $Id$
    begin       : Wed Mar 24 2004
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


#ifndef GWEN_FSLOCK_H
#define GWEN_FSLOCK_H

/** @defgroup MOD_FSLOCK Simple File/Folder Lock Management
 * @ingroup MOD_OS
 *
 * @brief This group contains the definition of a GWEN_FSLOCK.
 *
 * The files in this group provide a very simple lock mechanism.
 * When a file is to be locked a lockfile is created exclusively. If this
 * lockfile can not be created exclusively (because it already exists) the
 * file is assumed to be locked.
 * This group can lock files and folders. For folders the lockfile name
 * consists of the foldername plus "/.dir.lck", for files it is the filename
 * plus ".lck". This only works if you have write-access to the folder or,
 * if locking a file, to the folder containing the file to be locked.
 */
/*@{*/

#ifdef __cplusplus
extern "C" {
#endif


#define GWEN_FSLOCK_CBID_IO "GWEN_FSLOCK_CBID_IO"

#define GWEN_FSLOCK_TIMEOUT_NONE    (0)
#define GWEN_FSLOCK_TIMEOUT_FOREVER (-1)


typedef struct GWEN_FSLOCK GWEN_FSLOCK;

typedef enum {
  GWEN_FSLock_TypeUnknown=0,
  GWEN_FSLock_TypeFile,
  GWEN_FSLock_TypeDir,
} GWEN_FSLOCK_TYPE;


typedef enum {
  GWEN_FSLock_ResultOk=0,
  GWEN_FSLock_ResultError,
  GWEN_FSLock_ResultTimeout,
  GWEN_FSLock_ResultBusy,
  GWEN_FSLock_ResultNoLock,
  GWEN_FSLock_ResultUserAbort
} GWEN_FSLOCK_RESULT;


#include <gwenhywfar/gwenhywfarapi.h>
#include <gwenhywfar/types.h>
#include <gwenhywfar/db.h>


GWENHYWFAR_API
GWEN_FSLOCK *GWEN_FSLock_new(const char *fname, GWEN_FSLOCK_TYPE t);
GWENHYWFAR_API
void GWEN_FSLock_free(GWEN_FSLOCK *fl);

/**
 * This function tries to acquire a lock for the given file/folder.
 * It waits if necessary (using @ref GWEN_WaitCallback) while waiting.
 * This function enters and leaves the waitcallback
 *   @ref GWEN_FSLOCK_CBID_IO.
 * @param fl fslock object
 * @param timeout timeout in milliseconds (special values are
 *   @ref GWEN_FSLOCK_TIMEOUT_NONE (which does not wait at all) and
 *   @ref GWEN_FSLOCK_TIMEOUT_FOREVER (which waits forever).
 */
GWENHYWFAR_API
GWEN_FSLOCK_RESULT GWEN_FSLock_Lock(GWEN_FSLOCK *fl, int timeout);

/**
 * This function removes a lock.
 * @param fl fslock object
 */
GWENHYWFAR_API
GWEN_FSLOCK_RESULT GWEN_FSLock_Unlock(GWEN_FSLOCK *fl);


#ifdef __cplusplus
}
#endif

/*@}*/ /* defgroup */

#endif






