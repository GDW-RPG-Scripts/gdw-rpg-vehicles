#ifndef VEHICLE_GLOBAL_HH
#define VEHICLE_GLOBAL_HH

#include <QtCore/qglobal.h>

#if defined(VEHICLE_LIBRARY)
#  define VEHICLESHARED_EXPORT Q_DECL_EXPORT
#else
#  define VEHICLESHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // VEHICLE_GLOBAL_HH
