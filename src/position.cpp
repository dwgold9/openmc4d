#include "openmc/position.h"

namespace openmc {

//==============================================================================
// Position implementation
//==============================================================================

Position& Position::operator+=(Position other)
{
  x += other.x;
  y += other.y;
  z += other.z;
  t += other.t;
  return *this;
}

Position& Position::operator+=(double v)
{
  x += v;
  y += v;
  z += v;
  t += v;
  return *this;
}

Position& Position::operator-=(Position other)
{
  x -= other.x;
  y -= other.y;
  z -= other.z;
  t -= other.t;
  return *this;
}

Position& Position::operator-=(double v)
{
  x -= v;
  y -= v;
  z -= v;
  t -= v;
  return *this;
}

Position& Position::operator*=(Position other)
{
  x *= other.x;
  y *= other.y;
  z *= other.z;
  t *= other.t;
  return *this;
}

Position& Position::operator*=(double v)
{
  x *= v;
  y *= v;
  z *= v;
  t *= v;
  return *this;
}

Position& Position::operator/=(Position other)
{
  x /= other.x;
  y /= other.y;
  z /= other.z;
  t /= other.t;
  return *this;
}

Position& Position::operator/=(double v)
{
  x /= v;
  y /= v;
  z /= v;
  t /= v;
  return *this;
}

Position Position::operator-() const
{
  return {-x, -y, -z, -t};
}

std::ostream& operator<<(std::ostream& os, Position r)
{
  os << "(" << r.x << ", " << r.y << ", " << r.z << ", " << r.t << ")";
  return os;
}

} // namespace openmc
