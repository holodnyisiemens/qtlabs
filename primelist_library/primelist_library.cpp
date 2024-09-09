#include "primelist_library.h"

#include <stdexcept>

bool isprime(int n)
{
  if(n == 1)
  {
    return false;
  }
  for(int i = 2; i*i <= n; ++i)
  {
    if(n % i == 0)
    {
      return false;
    }
  }
  return true;
}

std::vector<int> primelist(int l, int r)
{
  if(l <= 0)
  {
    throw std::out_of_range("A must be positive");
  }
  if(r <= 0)
  {
    throw std::out_of_range("B must be positive");
  }
  if(r < l)
  {
    throw std::domain_error("A must be equal or less than B");
  }
  std::vector<int> result;
  for(int n = l; n <= r; ++n)
  {
    if(isprime(n))
    {
      result.push_back(n);
    }
  }
  return result;
}
