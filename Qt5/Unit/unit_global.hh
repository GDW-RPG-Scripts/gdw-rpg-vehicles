#ifndef UNIT_GLOBAL_HH
#define UNIT_GLOBAL_HH

#include <QtCore/qglobal.h>

#if defined(UNIT_LIBRARY)
#  define UNITSHARED_EXPORT Q_DECL_EXPORT
#else
#  define UNITSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // UNIT_GLOBAL_HH
