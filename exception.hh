/*
**
**
*/

#ifndef EXCEPTION_HH
#define EXCEPTION_HH

#include <QException>

class InvalidTypeException : public QException
{
public:
  InvalidTypeException();
};

#endif // EXCEPTION_HH
