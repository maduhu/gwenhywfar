/***************************************************************************
 $RCSfile$
                             -------------------
    cvs         : $Id$
    begin       : Mon Mar 01 2004
    copyright   : (C) 2004 by Martin Preuss
    email       : martin@libchipcard.de

 ***************************************************************************
 *          Please see toplevel file COPYING for license details           *
 ***************************************************************************/

#ifdef HAVE_CONFIG_H
# include <config.h>
#endif



#include "args.h"
#include "typemaker_p.h"
#include <gwenhywfar/debug.h>
#include <gwenhywfar/logger.h>
#include <gwenhywfar/xml.h>
#include <gwenhywfar/bufferedio.h>

#include <stdlib.h>
#include <assert.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <ctype.h>




int write_hl_file_c(ARGUMENTS *args, GWEN_XMLNODE *node) {
  int rv;
  const char *f;
  GWEN_BUFFER *fname;
  GWEN_BUFFER *hbuf;
  const char *s;
  int fd;
  const char *nacc;
  GWEN_BUFFEREDIO *bio;
  GWEN_ERRORCODE err;
  GWEN_XMLNODE *n;
  const char *id;
  const char *prefix;

  id=get_struct_property(node, "id", 0);
  if (!id) {
    DBG_ERROR(0, "No id for struct");
    return -1;
  }

  prefix=get_struct_property(node, "prefix", 0);
  if (!prefix) {
    DBG_ERROR(0, "No prefix for struct");
    return -1;
  }

  f=get_struct_property(node, "filename", 0);
  if (!f) {
    DBG_ERROR(0, "No filename given");
    return -1;
  }

  nacc=get_struct_property(node, "access", "public");

  fname=GWEN_Buffer_new(0, 256, 0, 1);
  GWEN_Buffer_AppendString(fname, f);
  GWEN_Buffer_AppendString(fname, "_l.h");
  fd=open(GWEN_Buffer_GetStart(fname),
	  O_RDWR|O_CREAT|O_TRUNC,
	  S_IRUSR|S_IWUSR);
  if (fd==-1) {
    DBG_ERROR(0, "open(%s): %s",
	      GWEN_Buffer_GetStart(fname),
	      strerror(errno));
    GWEN_Buffer_free(fname);
    return -1;
  }
  GWEN_Buffer_free(fname);

  bio=GWEN_BufferedIO_File_new(fd);
  GWEN_BufferedIO_SetWriteBuffer(bio, 0, 1024);

  GWEN_BufferedIO_WriteLine(bio, "/* This is a generated file. Please do not edit. */");

  hbuf=GWEN_Buffer_new(0, 256, 0, 1);
  s=f;
  while(*s) {
    GWEN_Buffer_AppendByte(hbuf, toupper(*s));
    s++;
  }
  GWEN_Buffer_AppendString(hbuf, "_L_H");

  GWEN_BufferedIO_Write(bio, "#ifndef ");
  GWEN_BufferedIO_WriteLine(bio, GWEN_Buffer_GetStart(hbuf));
  GWEN_BufferedIO_Write(bio, "#define ");
  GWEN_BufferedIO_WriteLine(bio, GWEN_Buffer_GetStart(hbuf));
  GWEN_BufferedIO_WriteLine(bio, "");


  rv=write_apidoc_c(args, node, bio, "lib");
  if (rv)
    return rv;

  if (strcasecmp(get_struct_property(node, "inherit", ""),
                 "lib")==0) {
    GWEN_BufferedIO_WriteLine(bio, "#include <gwenhywfar/inherit.h>");
  }

  if (strcasecmp(get_struct_property(node, "list", ""),
                 "lib")==0) {
    GWEN_BufferedIO_WriteLine(bio, "#include <gwenhywfar/misc.h>");
  }

  if (strcasecmp(get_struct_property(node, "list2", ""),
                 "lib")==0) {
    GWEN_BufferedIO_WriteLine(bio, "#include <gwenhywfar/list2.h>");
  }


  if (strcasecmp(nacc, "public")==0) {
    fname=GWEN_Buffer_new(0, 256, 0, 1);
    GWEN_Buffer_AppendString(fname, f);
    GWEN_Buffer_AppendString(fname, ".h");
    GWEN_BufferedIO_Write(bio, "#include \"");
    GWEN_BufferedIO_Write(bio, GWEN_Buffer_GetStart(fname));
    GWEN_BufferedIO_WriteLine(bio, "\"");
    GWEN_Buffer_free(fname);
  }

  if (strcasecmp(get_struct_property(node, "list", ""),
                 "lib")==0) {
    GWEN_BufferedIO_WriteLine(bio, "#include <gwenhywfar/misc.h>");
  }


  if (strcasecmp(nacc, "lib")==0) {
    GWEN_BufferedIO_WriteLine(bio, "#include <gwenhywfar/db.h>");

    n=GWEN_XMLNode_FindFirstTag(node, "headers", 0, 0);
    if (n) {
      GWEN_XMLNODE *nn;
  
      nn=GWEN_XMLNode_GetFirstTag(n);
      while(nn) {
        rv=write_hp_group_c(args, nn, bio);
        if (rv) {
          GWEN_Buffer_free(hbuf);
          return -1;
        }
        nn=GWEN_XMLNode_GetNextTag(nn);
      } /* while */
    }
  }
  GWEN_BufferedIO_WriteLine(bio, "");
  GWEN_BufferedIO_WriteLine(bio, "#ifdef __cplusplus");
  GWEN_BufferedIO_WriteLine(bio, "extern \"C\" {");
  GWEN_BufferedIO_WriteLine(bio, "#endif");
  GWEN_BufferedIO_WriteLine(bio, "");

  if (strcasecmp(nacc, "lib")==0) {
    GWEN_BufferedIO_Write(bio, "typedef struct ");
    GWEN_BufferedIO_Write(bio, id);
    GWEN_BufferedIO_Write(bio, " ");
    GWEN_BufferedIO_Write(bio, id);
    GWEN_BufferedIO_WriteLine(bio, ";");
    GWEN_BufferedIO_WriteLine(bio, "");
  }

  if (strcasecmp(get_struct_property(node, "inherit", ""),
                 "lib")==0) {
    GWEN_BufferedIO_Write(bio, "GWEN_INHERIT_FUNCTION_DEFS(");
    GWEN_BufferedIO_Write(bio, id);
    GWEN_BufferedIO_WriteLine(bio, ")");
  }

  if (strcasecmp(get_struct_property(node, "list", ""),
                 "lib")==0) {
    GWEN_BufferedIO_Write(bio, "GWEN_LIST_FUNCTION_DEFS(");
    GWEN_BufferedIO_Write(bio, id);
    GWEN_BufferedIO_Write(bio, ", ");
    GWEN_BufferedIO_Write(bio, prefix);
    GWEN_BufferedIO_WriteLine(bio, ")");
  }

  if (strcasecmp(get_struct_property(node, "list2", ""),
                 "lib")==0) {
    GWEN_BufferedIO_Write(bio, "GWEN_LIST2_FUNCTION_DEFS(");
    GWEN_BufferedIO_Write(bio, id);
    GWEN_BufferedIO_Write(bio, ", ");
    GWEN_BufferedIO_Write(bio, prefix);
    GWEN_BufferedIO_WriteLine(bio, ")");

    GWEN_BufferedIO_WriteLine(bio, "");

    GWEN_BufferedIO_Write(bio, "void ");
    GWEN_BufferedIO_Write(bio, prefix);
    GWEN_BufferedIO_Write(bio, "_List2_freeAll(");
    GWEN_BufferedIO_Write(bio, id);
    GWEN_BufferedIO_WriteLine(bio, "_LIST2 *stl);");
  }

  if (strcasecmp(nacc, "lib")==0) {
    GWEN_BufferedIO_Write(bio, id);
    GWEN_BufferedIO_Write(bio, " *");
    GWEN_BufferedIO_Write(bio, prefix);
    GWEN_BufferedIO_WriteLine(bio, "_new();");

    GWEN_BufferedIO_Write(bio, "void ");
    GWEN_BufferedIO_Write(bio, prefix);
    GWEN_BufferedIO_Write(bio, "_free(");
    GWEN_BufferedIO_Write(bio, id);
    GWEN_BufferedIO_WriteLine(bio, " *st);");

    GWEN_BufferedIO_Write(bio, "void ");
    GWEN_BufferedIO_Write(bio, prefix);
    GWEN_BufferedIO_Write(bio, "_Attach(");
    GWEN_BufferedIO_Write(bio, id);
    GWEN_BufferedIO_WriteLine(bio, " *st);");

    /* dup */
    GWEN_BufferedIO_Write(bio, id);
    GWEN_BufferedIO_Write(bio, " *");
    GWEN_BufferedIO_Write(bio, prefix);
    GWEN_BufferedIO_Write(bio, "_dup(const ");
    GWEN_BufferedIO_Write(bio, id);
    GWEN_BufferedIO_Write(bio, "*st);");

    /* FromDb */
    GWEN_BufferedIO_Write(bio, id);
    GWEN_BufferedIO_Write(bio, " *");
    GWEN_BufferedIO_Write(bio, prefix);
    GWEN_BufferedIO_Write(bio, "_fromDb(GWEN_DB_NODE *db);");

    /* ToDb */
    GWEN_BufferedIO_Write(bio, "int ");
    GWEN_BufferedIO_Write(bio, prefix);
    GWEN_BufferedIO_Write(bio, "_toDb(const ");
    GWEN_BufferedIO_Write(bio, id);
    GWEN_BufferedIO_Write(bio, "*st, GWEN_DB_NODE *db);");

    GWEN_BufferedIO_Write(bio, "int ");
    GWEN_BufferedIO_Write(bio, prefix);
    GWEN_BufferedIO_Write(bio, "_IsModified(const ");
    GWEN_BufferedIO_Write(bio, id);
    GWEN_BufferedIO_WriteLine(bio, " *st);");

    GWEN_BufferedIO_Write(bio, "void ");
    GWEN_BufferedIO_Write(bio, prefix);
    GWEN_BufferedIO_Write(bio, "_SetModified(");
    GWEN_BufferedIO_Write(bio, id);
    GWEN_BufferedIO_WriteLine(bio, " *st, int i);");
  }

  rv=write_h_setget_c(args, node, bio, "lib");
  if (rv) {
    GWEN_Buffer_free(hbuf);
    GWEN_BufferedIO_Abandon(bio);
    GWEN_BufferedIO_free(bio);
    return rv;
  }

  GWEN_BufferedIO_WriteLine(bio, "");
  GWEN_BufferedIO_WriteLine(bio, "#ifdef __cplusplus");
  GWEN_BufferedIO_WriteLine(bio, "} /* __cplusplus */");
  GWEN_BufferedIO_WriteLine(bio, "#endif");
  GWEN_BufferedIO_WriteLine(bio, "");

  /* write trailing endif */
  GWEN_BufferedIO_WriteLine(bio, "");

  GWEN_BufferedIO_Write(bio, "#endif /* ");
  GWEN_BufferedIO_Write(bio, GWEN_Buffer_GetStart(hbuf));
  GWEN_BufferedIO_WriteLine(bio, " */");

  err=GWEN_BufferedIO_Close(bio);
  if (!GWEN_Error_IsOk(err)) {
    DBG_ERROR_ERR(0, err);
    GWEN_BufferedIO_free(bio);
    GWEN_Buffer_free(hbuf);
    return -1;
  }

  GWEN_Buffer_free(hbuf);
  return 0;
}



int write_hl_files_c(ARGUMENTS *args, GWEN_XMLNODE *node) {
  GWEN_XMLNODE *n;
  int rv;

  n=GWEN_XMLNode_FindFirstTag(node, "type", 0, 0);
  while (n) {
    rv=write_hl_file_c(args, n);
    if (rv)
      return rv;
    n=GWEN_XMLNode_FindNextTag(n, "type", 0, 0);
  }
  return 0;
}








