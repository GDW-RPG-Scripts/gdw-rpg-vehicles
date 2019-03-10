#ifndef WEAPONS_GLOBAL_HH
#define WEAPONS_GLOBAL_HH

#include <QtCore/qglobal.h>

#if defined(WEAPONS_LIBRARY)
#  define WEAPONSSHARED_EXPORT Q_DECL_EXPORT
#else
#  define WEAPONSSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // WEAPONS_GLOBAL_HH
