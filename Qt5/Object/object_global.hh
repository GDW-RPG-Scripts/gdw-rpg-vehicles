#ifndef OBJECT_GLOBAL_HH
#define OBJECT_GLOBAL_HH

#include <QtCore/qglobal.h>

#if defined(OBJECT_LIBRARY)
#  define OBJECTSHARED_EXPORT Q_DECL_EXPORT
#else
#  define OBJECTSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // OBJECT_GLOBAL_HH
