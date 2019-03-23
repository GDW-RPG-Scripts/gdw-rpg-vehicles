#ifndef WEAPON_GLOBAL_HH
#define WEAPON_GLOBAL_HH

#include <QtCore/qglobal.h>

#if defined(WEAPON_LIBRARY)
#  define WEAPONSHARED_EXPORT Q_DECL_EXPORT
#else
#  define WEAPONSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // WEAPON_GLOBAL_HH
