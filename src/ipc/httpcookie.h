/* This file is auto-generated from "httpcookie.xml" by the typemaker
   tool of Gwenhywfar. 
   Do not edit this file -- all changes will be lost! */
#ifndef HTTPCOOKIE_H
#define HTTPCOOKIE_H

/** @page P_GWEN_HTTP_COOKIE_PUBLIC GWEN_HttpCookie (public)
This page describes the properties of GWEN_HTTP_COOKIE
@anchor GWEN_HTTP_COOKIE_Name
<h3>Name</h3>
<p>
</p>
<p>
Set this property with @ref GWEN_HttpCookie_SetName, 
get it with @ref GWEN_HttpCookie_GetName
</p>

@anchor GWEN_HTTP_COOKIE_Value
<h3>Value</h3>
<p>
</p>
<p>
Set this property with @ref GWEN_HttpCookie_SetValue, 
get it with @ref GWEN_HttpCookie_GetValue
</p>

@anchor GWEN_HTTP_COOKIE_Expires
<h3>Expires</h3>
<p>
</p>
<p>
Set this property with @ref GWEN_HttpCookie_SetExpires, 
get it with @ref GWEN_HttpCookie_GetExpires
</p>

@anchor GWEN_HTTP_COOKIE_Path
<h3>Path</h3>
<p>
</p>
<p>
Set this property with @ref GWEN_HttpCookie_SetPath, 
get it with @ref GWEN_HttpCookie_GetPath
</p>

@anchor GWEN_HTTP_COOKIE_Domain
<h3>Domain</h3>
<p>
</p>
<p>
Set this property with @ref GWEN_HttpCookie_SetDomain, 
get it with @ref GWEN_HttpCookie_GetDomain
</p>

@anchor GWEN_HTTP_COOKIE_Secure
<h3>Secure</h3>
<p>
</p>
<p>
Set this property with @ref GWEN_HttpCookie_SetSecure, 
get it with @ref GWEN_HttpCookie_GetSecure
</p>

*/
#ifdef __cplusplus
extern "C" {
#endif

typedef struct GWEN_HTTP_COOKIE GWEN_HTTP_COOKIE;

#ifdef __cplusplus
} /* __cplusplus */
#endif

#include <gwenhywfar/db.h>
#include <gwenhywfar/misc.h>
#include <gwenhywfar/list2.h>
#include <gwenhywfar/types.h>
#include <gwenhywfar/gwentime.h>

#ifdef __cplusplus
extern "C" {
#endif

GWEN_LIST_FUNCTION_LIB_DEFS(GWEN_HTTP_COOKIE, GWEN_HttpCookie, GWENHYWFAR_API)
GWEN_HTTP_COOKIE_LIST *GWEN_HttpCookie_List_dup(const GWEN_HTTP_COOKIE_LIST *stl);

GWEN_LIST2_FUNCTION_LIB_DEFS(GWEN_HTTP_COOKIE, GWEN_HttpCookie, GWENHYWFAR_API)

/** Destroys all objects stored in the given LIST2 and the list itself
*/
GWENHYWFAR_API void GWEN_HttpCookie_List2_freeAll(GWEN_HTTP_COOKIE_LIST2 *stl);
/** Creates a deep copy of the given LIST2.
*/
GWENHYWFAR_API GWEN_HTTP_COOKIE_LIST2 *GWEN_HttpCookie_List2_dup(const GWEN_HTTP_COOKIE_LIST2 *stl);

/** Creates a new object.
*/
GWENHYWFAR_API GWEN_HTTP_COOKIE *GWEN_HttpCookie_new();
/** Destroys the given object.
*/
GWENHYWFAR_API void GWEN_HttpCookie_free(GWEN_HTTP_COOKIE *st);
/** Increments the usage counter of the given object, so an additional free() is needed to destroy the object.
*/
GWENHYWFAR_API void GWEN_HttpCookie_Attach(GWEN_HTTP_COOKIE *st);
/** Creates and returns a deep copy of thegiven object.
*/
GWENHYWFAR_API GWEN_HTTP_COOKIE *GWEN_HttpCookie_dup(const GWEN_HTTP_COOKIE*st);
/** Creates an object from the data in the given GWEN_DB_NODE
*/
GWENHYWFAR_API GWEN_HTTP_COOKIE *GWEN_HttpCookie_fromDb(GWEN_DB_NODE *db);
/** Stores an object in the given GWEN_DB_NODE
*/
GWENHYWFAR_API int GWEN_HttpCookie_toDb(const GWEN_HTTP_COOKIE*st, GWEN_DB_NODE *db);
/** Returns 0 if this object has not been modified, !=0 otherwise
*/
GWENHYWFAR_API int GWEN_HttpCookie_IsModified(const GWEN_HTTP_COOKIE *st);
/** Sets the modified state of the given object
*/
GWENHYWFAR_API void GWEN_HttpCookie_SetModified(GWEN_HTTP_COOKIE *st, int i);

/**
* Returns the property @ref GWEN_HTTP_COOKIE_Name
*/
GWENHYWFAR_API const char *GWEN_HttpCookie_GetName(const GWEN_HTTP_COOKIE *el);
/**
* Set the property @ref GWEN_HTTP_COOKIE_Name
*/
GWENHYWFAR_API void GWEN_HttpCookie_SetName(GWEN_HTTP_COOKIE *el, const char *d);

/**
* Returns the property @ref GWEN_HTTP_COOKIE_Value
*/
GWENHYWFAR_API const char *GWEN_HttpCookie_GetValue(const GWEN_HTTP_COOKIE *el);
/**
* Set the property @ref GWEN_HTTP_COOKIE_Value
*/
GWENHYWFAR_API void GWEN_HttpCookie_SetValue(GWEN_HTTP_COOKIE *el, const char *d);

/**
* Returns the property @ref GWEN_HTTP_COOKIE_Expires
*/
GWENHYWFAR_API const GWEN_TIME *GWEN_HttpCookie_GetExpires(const GWEN_HTTP_COOKIE *el);
/**
* Set the property @ref GWEN_HTTP_COOKIE_Expires
*/
GWENHYWFAR_API void GWEN_HttpCookie_SetExpires(GWEN_HTTP_COOKIE *el, const GWEN_TIME *d);

/**
* Returns the property @ref GWEN_HTTP_COOKIE_Path
*/
GWENHYWFAR_API const char *GWEN_HttpCookie_GetPath(const GWEN_HTTP_COOKIE *el);
/**
* Set the property @ref GWEN_HTTP_COOKIE_Path
*/
GWENHYWFAR_API void GWEN_HttpCookie_SetPath(GWEN_HTTP_COOKIE *el, const char *d);

/**
* Returns the property @ref GWEN_HTTP_COOKIE_Domain
*/
GWENHYWFAR_API const char *GWEN_HttpCookie_GetDomain(const GWEN_HTTP_COOKIE *el);
/**
* Set the property @ref GWEN_HTTP_COOKIE_Domain
*/
GWENHYWFAR_API void GWEN_HttpCookie_SetDomain(GWEN_HTTP_COOKIE *el, const char *d);

/**
* Returns the property @ref GWEN_HTTP_COOKIE_Secure
*/
GWENHYWFAR_API int GWEN_HttpCookie_GetSecure(const GWEN_HTTP_COOKIE *el);
/**
* Set the property @ref GWEN_HTTP_COOKIE_Secure
*/
GWENHYWFAR_API void GWEN_HttpCookie_SetSecure(GWEN_HTTP_COOKIE *el, int d);


#ifdef __cplusplus
} /* __cplusplus */
#endif


#endif /* HTTPCOOKIE_H */