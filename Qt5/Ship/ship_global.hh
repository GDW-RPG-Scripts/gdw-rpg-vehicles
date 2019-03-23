#ifndef SHIP_GLOBAL_HH
#define SHIP_GLOBAL_HH

#include <QtCore/qglobal.h>

#if defined(SHIP_LIBRARY)
#  define SHIPSHARED_EXPORT Q_DECL_EXPORT
#else
#  define SHIPSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // SHIP_GLOBAL_HH
