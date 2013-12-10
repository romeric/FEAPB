#ifndef PRINT_ARRAY_H
#define PRINT_ARRAY_H

#include "boost/multi_array.hpp"
#include "boost/array.hpp"
#include "boost/cstdlib.hpp"

template <typename Array>
void print(std::ostream& os, const Array& A)
{
  typename Array::const_iterator i;
  os << "[";
  for (i = A.begin(); i != A.end(); ++i) {
    print(os, *i);
    if (boost::next(i) != A.end())
      os << ',';
  }
  os << "]";
}
template<> void print<double>(std::ostream& os, const double& x)
{
  os << x;
}

#endif // PRINT_ARRAY_H
