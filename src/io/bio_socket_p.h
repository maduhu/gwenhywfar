/***************************************************************************
 $RCSfile$
 -------------------
 cvs         : $Id$
 begin       : Fri Feb 07 2003
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


#ifndef GWENHYWFAR_BIO_SOCKET_P_H
#define GWENHYWFAR_BIO_SOCKET_P_H

#include <gwenhywfar/bio_socket.h>

#define GWEN_BUFFEREDIO_SOCKET_TIMEOUT 20000
#define GWEN_BUFFEREDIO_SOCKET_TRIES   3


struct GWEN_BUFFEREDIO_SOCKET {
  GWEN_SOCKET *sock;
};
typedef struct GWEN_BUFFEREDIO_SOCKET GWEN_BUFFEREDIO_SOCKET;




#endif /* GWENHYWFAR_BIO_SOCKET_P_H */




