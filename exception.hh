/*
**
**
*/

#ifndef EXCEPTION_HH
#define EXCEPTION_HH

#include <QException>

namespace GDW
{
  namespace RPG
  {
    class InvalidTypeException : public QException
    {
    public:
      InvalidTypeException();
    };
  };
};

#endif // EXCEPTION_HH
