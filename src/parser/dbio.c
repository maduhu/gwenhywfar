/***************************************************************************
 $RCSfile$
 -------------------
 cvs         : $Id$
 begin       : Wed Mar 31 2004
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


#ifdef HAVE_CONFIG_H
# include <config.h>
#endif

#define DISABLE_DEBUGLOG

#include "dbio_p.h"
#include <gwenhywfar/misc.h>
#include <gwenhywfar/debug.h>
#include <gwenhywfar/path.h>
#include <gwenhywfar/bufferedio.h>
#include <gwenhywfar/text.h>
#include <gwenhywfar/directory.h>

/* TODO: #include <gwenhywfar/plugin.h> */

#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>

#ifdef OS_WIN32
# include <windows.h>
#endif



GWEN_LIST_FUNCTIONS(GWEN_DBIO, GWEN_DBIO);
GWEN_INHERIT_FUNCTIONS(GWEN_DBIO);



static GWEN_DBIO_LIST *gwen_dbio__list=0;


GWEN_ERRORCODE GWEN_DBIO_ModuleInit(){
  /* TODO: GWEN_PLUGIN_MANAGER *pm; */

  gwen_dbio__list=GWEN_DBIO_List_new();
  /* TODO:
  pm=GWEN_PluginManager_new("dbio");
  if (GWEN_PluginManager_Register(pm)) {
    DBG_ERROR(GWEN_LOGDOMAIN, "Could not register DBIO plugin manager");
    return GWEN_Error_new(0,
                          GWEN_ERROR_SEVERITY_ERR,
                          GWEN_ERROR_TYPE_ERROR,
                          GWEN_ERROR_UNSPECIFIED);
  }
  */
  return 0;
}



GWEN_ERRORCODE GWEN_DBIO_ModuleFini(){
  GWEN_DBIO_List_free(gwen_dbio__list);
  return 0;
}






GWEN_DBIO *GWEN_DBIO_new(const char *name, const char *descr){
  GWEN_DBIO *dbio;

  assert(name);
  GWEN_NEW_OBJECT(GWEN_DBIO, dbio);
  GWEN_LIST_INIT(GWEN_DBIO, dbio);
  GWEN_INHERIT_INIT(GWEN_DBIO, dbio);
  dbio->name=strdup(name);
  if (descr)
    dbio->descr=strdup(descr);

  dbio->usage=1;
  return dbio;
}



void GWEN_DBIO_free(GWEN_DBIO *dbio){
  if (dbio) {
    assert(dbio->usage);
    if (--(dbio->usage)==0) {
      GWEN_INHERIT_FINI(GWEN_DBIO, dbio);
      GWEN_LIST_FINI(GWEN_DBIO, dbio);

      if (dbio->libLoader) {
        GWEN_LibLoader_CloseLibrary(dbio->libLoader);
        GWEN_LibLoader_free(dbio->libLoader);
      }
      free(dbio->name);
      free(dbio->descr);

      GWEN_FREE_OBJECT(dbio);
    }
  }
}



void GWEN_DBIO_Attach(GWEN_DBIO *dbio){
  assert(dbio);
  dbio->usage++;
}



int GWEN_DBIO_Import(GWEN_DBIO *dbio,
                     GWEN_BUFFEREDIO *bio,
                     GWEN_TYPE_UINT32 flags,
                     GWEN_DB_NODE *db,
                     GWEN_DB_NODE *params) {
  assert(dbio);
  assert(bio);
  assert(db);

  if (dbio->importFn)
    return dbio->importFn(dbio, bio, flags, db, params);
  else {
    DBG_INFO(GWEN_LOGDOMAIN, "No import function set");
    return -1;
  }
}



int GWEN_DBIO_Export(GWEN_DBIO *dbio,
                     GWEN_BUFFEREDIO *bio,
                     GWEN_TYPE_UINT32 flags,
                     GWEN_DB_NODE *db,
                     GWEN_DB_NODE *params) {
  assert(dbio);
  assert(bio);
  assert(db);

  if (dbio->exportFn)
    return dbio->exportFn(dbio, bio, flags, db, params);
  else {
    DBG_INFO(GWEN_LOGDOMAIN, "No export function set");
    return -1;
  }
}



GWEN_DBIO_CHECKFILE_RESULT GWEN_DBIO_CheckFile(GWEN_DBIO *dbio,
                                               const char *fname) {
  assert(dbio);
  assert(fname);

  if (dbio->checkFileFn)
    return dbio->checkFileFn(dbio, fname);
  else {
    DBG_INFO(GWEN_LOGDOMAIN, "No checkFile function set");
    return GWEN_DBIO_CheckFileResultUnknown;
  }
}



const char *GWEN_DBIO_GetName(const GWEN_DBIO *dbio){
  assert(dbio);
  return dbio->name;
}



const char *GWEN_DBIO_GetDescription(const GWEN_DBIO *dbio){
  assert(dbio);
  return dbio->descr;
}



GWEN_LIBLOADER *GWEN_DBIO_GetLibLoader(const GWEN_DBIO *dbio){
  assert(dbio);
  return dbio->libLoader;
}



void GWEN_DBIO_SetLibLoader(GWEN_DBIO *dbio, GWEN_LIBLOADER *ll){
  assert(dbio);
  assert(dbio->libLoader==0);
  dbio->libLoader=ll;
}




int GWEN_DBIO_Register(GWEN_DBIO *dbio) {
  assert(gwen_dbio__list);
  assert(dbio);

  GWEN_DBIO_List_Insert(dbio, gwen_dbio__list);

  return 0;
}



GWEN_DBIO *GWEN_DBIO_Find(const char *name) {
  GWEN_DBIO *dbio;

  assert(gwen_dbio__list);
  assert(name);

  dbio=GWEN_DBIO_List_First(gwen_dbio__list);
  while(dbio) {
    if (strcasecmp(GWEN_DBIO_GetName(dbio), name)==0)
      return dbio;
    dbio=GWEN_DBIO_List_Next(dbio);
  } /* while */

  return 0;
}



void GWEN_DBIO_SetImportFn(GWEN_DBIO *dbio, GWEN_DBIO_IMPORTFN f){
  assert(dbio);
  dbio->importFn=f;
}



void GWEN_DBIO_SetExportFn(GWEN_DBIO *dbio, GWEN_DBIO_EXPORTFN f){
  assert(dbio);
  dbio->exportFn=f;
}


void GWEN_DBIO_SetCheckFileFn(GWEN_DBIO *dbio, GWEN_DBIO_CHECKFILEFN f){
  assert(dbio);
  dbio->checkFileFn=f;
}



GWEN_DBIO *GWEN_DBIO_LoadPluginFile(const char *modname, const char *fname){
  GWEN_LIBLOADER *ll;
  GWEN_DBIO *dbio;
  GWEN_DBIO_FACTORYFN fn;
  void *p;
  GWEN_BUFFER *nbuf;
  const char *s;
  GWEN_ERRORCODE err;

  ll=GWEN_LibLoader_new();
  if (GWEN_LibLoader_OpenLibrary(ll, fname)) {
    DBG_ERROR(GWEN_LOGDOMAIN, "Could not load DBIO plugin \"%s\" (%s)", modname, fname);
    GWEN_LibLoader_free(ll);
    return 0;
  }

  /* create name of init function */
  nbuf=GWEN_Buffer_new(0, 128, 0, 1);
  s=modname;
  while(*s) GWEN_Buffer_AppendByte(nbuf, tolower(*(s++)));
  GWEN_Buffer_AppendString(nbuf, "_factory");

  /* resolve name of factory function */
  err=GWEN_LibLoader_Resolve(ll, GWEN_Buffer_GetStart(nbuf), &p);
  if (!GWEN_Error_IsOk(err)) {
    DBG_ERROR_ERR(GWEN_LOGDOMAIN, err);
    GWEN_Buffer_free(nbuf);
    GWEN_LibLoader_CloseLibrary(ll);
    GWEN_LibLoader_free(ll);
    return 0;
  }
  GWEN_Buffer_free(nbuf);

  fn=(GWEN_DBIO_FACTORYFN)p;
  assert(fn);
  dbio=fn();
  if (!dbio) {
    DBG_ERROR(GWEN_LOGDOMAIN, "Error in plugin: No DBIO created");
    GWEN_LibLoader_CloseLibrary(ll);
    GWEN_LibLoader_free(ll);
    return 0;
  }

  /* store libloader */
  GWEN_DBIO_SetLibLoader(dbio, ll);

  return dbio;
}



int GWEN_DBIO_GetPluginPath(GWEN_BUFFER *pbuf) {
#ifdef OS_WIN32
  HKEY hkey;
  TCHAR nbuffer[MAX_PATH];
  BYTE vbuffer[MAX_PATH];
  DWORD nsize;
  DWORD vsize;
  DWORD typ;
  int i;

  snprintf(nbuffer, sizeof(nbuffer), "Software\\Gwenhywfar\\Paths");

  /* open the key */
  if (RegOpenKey(HKEY_CURRENT_USER, nbuffer, &hkey)){
    DBG_ERROR(GWEN_LOGDOMAIN,
              "RegOpenKey failed, returning compile-time value");
    GWEN_Directory_OsifyPath(GWENHYWFAR_PLUGINS
                             "/"
                             GWEN_DBIO_FOLDER,
                             pbuf,
                             1);
    return 1;
  }

  /* find the key for dbio-plugins */
  for (i=0;; i++) {
    nsize=sizeof(nbuffer);
    vsize=sizeof(vbuffer);
    if (ERROR_SUCCESS!=RegEnumValue(hkey,
                                    i,    /* index */
                                    nbuffer,
                                    &nsize,
                                    0,       /* reserved */
                                    &typ,
                                    vbuffer,
                                    &vsize))
      break;
    if (strcasecmp(nbuffer, "dbio-plugins")==0 &&
        typ==REG_SZ) {
      /* variable found */
      RegCloseKey(hkey);
      GWEN_Buffer_AppendBytes(pbuf, (char*)vbuffer, vsize-1);
      return 0;
    }
  } /* for */

  RegCloseKey(hkey);
  DBG_INFO(GWEN_LOGDOMAIN,
           "RegKey does not exist, returning compile-time value");
  GWEN_Directory_OsifyPath(GWENHYWFAR_PLUGINS
                           "/"
                           GWEN_DBIO_FOLDER,
                           pbuf,
                           1);
  return 1;
#else
  GWEN_Directory_OsifyPath(GWENHYWFAR_PLUGINS
                           "/"
                           GWEN_DBIO_FOLDER,
                           pbuf,
                           0);
  return 0;
#endif
}



GWEN_DBIO *GWEN_DBIO_LoadPlugin(const char *modname){
  GWEN_LIBLOADER *ll;
  GWEN_DBIO *dbio;
  GWEN_DBIO_FACTORYFN fn;
  void *p;
  GWEN_BUFFER *nbuf;
  const char *s;
  GWEN_ERRORCODE err;
  GWEN_BUFFER *pbuf;

  ll=GWEN_LibLoader_new();
  pbuf=GWEN_Buffer_new(0, 256, 0, 1);
  GWEN_DBIO_GetPluginPath(pbuf);
  if (GWEN_LibLoader_OpenLibraryWithPath(ll,
                                         GWEN_Buffer_GetStart(pbuf),
                                         modname)) {
    DBG_ERROR(GWEN_LOGDOMAIN, "Could not load DBIO plugin \"%s\"", modname);
    GWEN_Buffer_free(pbuf);
    GWEN_LibLoader_free(ll);
    return 0;
  }
  GWEN_Buffer_free(pbuf);

  /* create name of init function */
  nbuf=GWEN_Buffer_new(0, 128, 0, 1);
  s=modname;
  while(*s) GWEN_Buffer_AppendByte(nbuf, tolower(*(s++)));
  GWEN_Buffer_AppendString(nbuf, "_factory");

  /* resolve name of factory function */
  err=GWEN_LibLoader_Resolve(ll, GWEN_Buffer_GetStart(nbuf), &p);
  if (!GWEN_Error_IsOk(err)) {
    DBG_ERROR_ERR(GWEN_LOGDOMAIN, err);
    GWEN_Buffer_free(nbuf);
    GWEN_LibLoader_CloseLibrary(ll);
    GWEN_LibLoader_free(ll);
    return 0;
  }
  GWEN_Buffer_free(nbuf);

  fn=(GWEN_DBIO_FACTORYFN)p;
  assert(fn);
  dbio=fn();
  if (!dbio) {
    DBG_ERROR(GWEN_LOGDOMAIN, "Error in plugin: No DBIO created");
    GWEN_LibLoader_CloseLibrary(ll);
    GWEN_LibLoader_free(ll);
    return 0;
  }

  /* store libloader */
  GWEN_DBIO_SetLibLoader(dbio, ll);

  return dbio;
}



GWEN_DBIO *GWEN_DBIO_GetPlugin(const char *modname){
  GWEN_DBIO *dbio;

  dbio=GWEN_DBIO_Find(modname);
  if (dbio) {
    GWEN_DBIO_Attach(dbio);
    return dbio;
  }
  dbio=GWEN_DBIO_LoadPlugin(modname);
  if (!dbio)
    return 0;

  if (strcasecmp(GWEN_DBIO_GetName(dbio), modname)!=0) {
    DBG_ERROR(GWEN_LOGDOMAIN, "Plugin \"%s\" does not support the expected DBIO \"%s\"",
              GWEN_DBIO_GetName(dbio), modname);
    GWEN_DBIO_free(dbio);
    return 0;
  }
  GWEN_DBIO_Register(dbio);
  GWEN_DBIO_Attach(dbio);
  return dbio;
}

















