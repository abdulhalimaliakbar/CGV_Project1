/* Copyright (C) Dante Treglia II and Mark A. DeLoura, 2000. 
 * All rights reserved worldwide.
 *
 * This software is provided "as is" without express or implied
 * warranties. You may freely copy and compile this source into
 * applications you distribute provided that the copyright text
 * below is included in the resulting source code, for example:
 * "Portions Copyright (C) Dante Treglia II and Mark A. DeLoura, 2000"
 */
//==========================================================
// C++ Matrix Library
// Version: 2.5
// Date: April 22, 2000
// Authors: Dante Treglia II and Mark A. DeLoura
// Thanks to: Miguel Gomez, Stan Melax, Pete Isensee, 
//   Gabor Nagy, Scott Bilas, James Boer, Eric Lengyel
//==========================================================
#include "mtxlib.h"
#include <cmath>
#include <cassert>

using namespace std;

////////////////////////////////////////////////////////////
// vector2 class
//

// Constructor with initializing float values
vector2::vector2(float inX, float inY) 
{
  x = inX;
  y = inY;
}

// Constructor with initializing vector2
vector2::vector2(const vector2 &v) 
{
  x = v.x;
  y = v.y;
}

// Array indexing
float &vector2::operator [] (unsigned int i) 
{
  assert (i<2);
  
  return *(&x+i);
}

// Array indexing
const float &vector2::operator [] (unsigned int i) const 
{
  assert (i<2);

  return *(&x+i);
}

// Assign 
vector2 &vector2::operator = (const vector2 &v) 
{
  x = v.x;
  y = v.y;

  return *this;
}

vector2 &vector2::operator = (const vector3 &v)
{
  x = v.x;
  y = v.y;

  return *this;
}

// Add a vector2 to this one
vector2 &vector2::operator += (const vector2 &v) 
{
  x += v.x;
  y += v.y;

  return *this;
}

// Subtract a vector2 from this one
vector2 &vector2::operator -= (const vector2 &v) 
{
  x -= v.x;
  y -= v.y;

  return *this;
}

// Multiply the vector2 by a float
vector2 &vector2::operator *= (float f) 
{
  x *= f;
  y *= f;

  return *this;
}

// Divide the vector2 by a float
vector2 &vector2::operator /= (float f) 
{
  x /= f;
  y /= f;

  return *this;
}

// Are these two vector2's equal?
bool operator == (const vector2 &a, const vector2 &b) 
{
  return ((a.x == b.x) && (a.y == b.y));
}

// Are these two vector2's not equal?
bool operator != (const vector2 &a, const vector2 &b) 
{
  return ((a.x != b.x) || (a.y != b.y));
}

// Add two vector2's
vector2 operator + (const vector2 &a, const vector2 &b) 
{
  vector2 ret(a);

  ret += b;

  return ret;
}

// Subtract one vector2 from another
vector2 operator - (const vector2 &a, const vector2 &b) 
{
  vector2 ret(a);

  ret -= b;

  return ret;
}

// Multiply vector2 by a float
vector2 operator * (const vector2 &v, float f) 
{
  return vector2(f * v.x, f * v.y);
}

// Multiply vector2 by a float
vector2 operator * (float f, const vector2 &v) 
{
  return vector2(f * v.x, f * v.y);
}

// Divide vector2 by a float
vector2 operator / (const vector2 &v, float f) 
{
  return vector2(v.x / f, v.y / f);
}

// Negate a vector2
vector2 operator - (const vector2 &a) 
{
  return vector2(-a.x, -a.y);
}

// Set Values
void vector2::set(float xIn, float yIn)
{
  x = xIn;
  y = yIn;
}

// Get length of a vector2
float vector2::length() const 
{
  return (float) sqrt(x*x + y*y);
}

// Get squared length of a vector2
float vector2::lengthSqr() const 
{
  return (x*x + y*y);
}

// Does vector2 equal (0, 0)?
bool vector2::isZero() const 
{
  return ((x == 0.0F) && (y == 0.0F));
}

// Normalize a vector2
vector2 &vector2::normalize() 
{
  float m = length();

  if (m > 0.0F) 
    m = 1.0F / m;
  else 
    m = 0.0F;
  x *= m;
  y *= m;

  return *this;
}


////////////////////////////////////////////////////////////
// vector3 class
//

// Constructor with initializing float values
vector3::vector3(float inX, float inY, float inZ) 
{
  x = inX;
  y = inY;
  z = inZ;
}

// Constructor with initializing vector3
vector3::vector3(const vector3 &v) 
{
  x = v.x;
  y = v.y;
  z = v.z;
}

// Constructor with initializing vector2
vector3::vector3(const vector2 &v) 
{
  x = v.x;
  y = v.y;
  z = 0.0F;
}

// Constructor with initializing vector4
vector3::vector3(const vector4 &v) 
{
  x = v.x;
  y = v.y;
  z = v.z;
}

// Array indexing
float &vector3::operator [] (unsigned int i) 
{
  assert (i<3);
        
  return *(&x+i);
}

// Array indexing
const float &vector3::operator [] (unsigned int i) const 
{
  assert (i<3);

  return *(&x+i);
}

// Assign
vector3 &vector3::operator = (const vector3 &v) 
{
  x = v.x;
  y = v.y;
  z = v.z;

  return *this;
}

// Assign from a vector2
vector3 &vector3::operator = (const vector2 &v) 
{
  x = v.x;
  y = v.y;
  z = 0.0F;

  return *this;
}

// Add a vector3 to this one
vector3 &vector3::operator += (const vector3 &v) 
{
  x += v.x;
  y += v.y;
  z += v.z;

  return *this;
}

// Subtract a vector3 from this one
vector3 &vector3::operator -= (const vector3 &v) 
{
  x -= v.x;
  y -= v.y;
  z -= v.z;

  return *this;
}

// Multiply the vector3 by a float
vector3 &vector3::operator *= (float f) 
{
  x *= f;
  y *= f;
  z *= f;

  return *this;
}

// Divide the vector3 by a float
vector3 &vector3::operator /= (float f) 
{
  x /= f;
  y /= f;
  z /= f;

  return *this;
}

// Are these two vector3's equal?
bool operator == (const vector3 &a, const vector3 &b) 
{
  return ((a.x == b.x) && (a.y == b.y) && (a.z == b.z));
}

// Are these two vector3's not equal?
bool operator != (const vector3 &a, const vector3 &b) 
{
  return ((a.x != b.x) || (a.y != b.y) || (a.z != b.z));
}

// Add two vector3's
vector3 operator + (const vector3 &a, const vector3 &b) 
{
  vector3 ret(a);

  ret += b;

  return ret;
}

// Subtract one vector3 from another
vector3 operator - (const vector3 &a, const vector3 &b) 
{
  vector3 ret(a);

  ret -= b;

  return ret;
}

// Multiply vector3 by a float
vector3 operator * (const vector3 &v, float f) 
{
  return vector3(f * v.x, f * v.y, f * v.z);
}

// Multiply vector3 by a float
vector3 operator * (float f, const vector3 &v) 
{
  return vector3(f * v.x, f * v.y, f * v.z);
}

// Divide vector3 by a float
vector3 operator / (const vector3 &v, float f) 
{
  return vector3(v.x / f, v.y / f, v.z / f);
}

// Negate a vector3
vector3 operator - (const vector3 &a) 
{
  return vector3(-a.x, -a.y, -a.z);
}

// Set Values
void vector3::set(float xIn, float yIn, float zIn)
{
  x = xIn;
  y = yIn;
  z = zIn;
}

// Get length of a vector3
float vector3::length() const 
{
  return (float) sqrt(x*x + y*y + z*z);
}

// Get squared length of a vector3
float vector3::lengthSqr() const 
{
  return (x*x + y*y + z*z);
}

// Does vector3 equal (0, 0, 0)?
bool vector3::isZero() const 
{
  return ((x == 0.0F) && (y == 0.0F) && (z == 0.0F));
}

// Normalize a vector3
vector3 &vector3::normalize() 
{
  float m = length();

  if (m > 0.0F) 
    m = 1.0F / m;
  else 
    m = 0.0F;
  x *= m;
  y *= m;
  z *= m;

  return *this;
}


////////////////////////////////////////////////////////////
// vector4 class
//

// Constructor with initializing float values
vector4::vector4(float inX, float inY, float inZ, float inW) 
{
  x = inX;
  y = inY;
  z = inZ;
  w = inW;
}

// Constructor with initializing vector4
vector4::vector4(const vector4 &v) 
{
  x = v.x;
  y = v.y;
  z = v.z;
  w = v.w;
}

// Constructor with initializing vector3
vector4::vector4(const vector3 &v) 
{
  x = v.x;
  y = v.y;
  z = v.z;
  w = 0.0F;
}

// Constructor with initializing vector2
vector4::vector4(const vector2 &v) 
{
  x = v.x;
  y = v.y;
  z = 0.0F;
  w = 0.0F;
}

// Array indexing
float &vector4::operator [] (unsigned int i) 
{
  assert (i<4);
  
  return *(&x+i);
}

// Array indexing
const float &vector4::operator [] (unsigned int i) const 
{
  assert (i<4);
  
  return *(&x+i);
}

// Assign
vector4 &vector4::operator = (const vector4 &v) 
{
  x = v.x;
  y = v.y;
  z = v.z;
  w = v.w;

  return *this;
}

// Assign from a vector3
vector4 &vector4::operator = (const vector3 &v) 
{
  x = v.x;
  y = v.y;
  z = v.z;
  w = 0.0F;

  return *this;
}

// Assign from a vector2
vector4 &vector4::operator = (const vector2 &v) 
{
  x = v.x;
  y = v.y;
  z = 0.0F;
  w = 0.0F;

  return *this;
}

// Add a vector4 to this one
vector4 &vector4::operator += (const vector4 &v) 
{
  x += v.x;
  y += v.y;
  z += v.z;
  w += v.w;

  return *this;
}

// Subtract a vector4 from this one
vector4 &vector4::operator -= (const vector4 &v) 
{
  x -= v.x;
  y -= v.y;
  z -= v.z;
  w -= v.w;

  return *this;
}

// Multiply the vector4 by a float
vector4 &vector4::operator *= (float f) 
{
  x *= f;
  y *= f;
  z *= f;
  w *= f;

  return *this;
}

// Divide the vector4 by a float
vector4 &vector4::operator /= (float f) 
{
  x /= f;
  y /= f;
  z /= f;
  w /= f;

  return *this;
}

// Are these two vector4's equal?
bool operator == (const vector4 &a, const vector4 &b) 
{
  return ((a.x == b.x) && (a.y == b.y) &&
          (a.z == b.z) && (a.w == b.w));
}

// Are these two vector4's not equal?
bool operator != (const vector4 &a, const vector4 &b) 
{
  return ((a.x != b.x) || (a.y != b.y) ||
          (a.z != b.z) || (a.w != b.w));
}

// Add two vector4's
vector4 operator + (const vector4 &a, const vector4 &b) 
{
  vector4 ret(a);

  ret += b;

  return ret;
}

// Subtract one vector4 from another
vector4 operator - (const vector4 &a, const vector4 &b) 
{
  vector4 ret(a);

  ret -= b;

  return ret;
}

// Multiply vector4 by a float
vector4 operator * (const vector4 &v, float f) 
{
  return vector4(f * v.x, f * v.y, f * v.z, f * v.w);
}

// Multiply vector4 by a float
vector4 operator * (float f, const vector4 &v) 
{
  return vector4(f * v.x, f * v.y, f * v.z, f * v.w);
}

// Divide vector4 by a float
vector4 operator / (const vector4 &v, float f) 
{
  return vector4(v.x / f, v.y / f, v.z / f, v.w / f);
}

// Negate a vector4
vector4 operator - (const vector4 &a) 
{
  return vector4(-a.x, -a.y, -a.z, -a.w);
}

// Set Values
void vector4::set(float xIn, float yIn, float zIn, float wIn)
{
  x = xIn;
  y = yIn;
  z = zIn;
  w = wIn;
}

// Get length of a vector4
float vector4::length() const 
{
  return (float) sqrt(x*x + y*y + z*z + w*w);
}

// Get squared length of a vector4
float vector4::lengthSqr() const 
{
  return (x*x + y*y + z*z + w*w);
}

// Does vector4 equal (0, 0, 0, 0)?
bool vector4::isZero() const 
{
  return ((x == 0.0F) && (y == 0.0F) && (z == 0.0F) && (w == 0.0F));
}

// Normalize a vector4
vector4 &vector4::normalize() 
{
  float m = length();

  if (m > 0.0F) 
    m = 1.0F / m;
  else 
    m = 0.0F;
  x *= m;
  y *= m;
  z *= m;
  w *= m;

  return *this;
}


////////////////////////////////////////////////////////////
// Miscellaneous vector functions
//

// Return Normal of vector2's
vector2 Normalized(const vector2 &a)
{
  vector2 ret(a);
  return ret.normalize();
}
// Return Normal of vector3's
vector3 Normalized(const vector3 &a)
{
  vector3 ret(a);
  return ret.normalize();
}
// Return Normal of vector4's
vector4 Normalized(const vector4 &a)
{
  vector4 ret(a);
  return ret.normalize();
}

// Dot product of two vector2's
float DotProduct(const vector2 &a, const vector2 &b) 
{
  return a.x*b.x + a.y*b.y;
}

// Dot product of two vector3's
float DotProduct(const vector3 &a, const vector3 &b) 
{
  return a.x*b.x + a.y*b.y + a.z*b.z;
}

// Dot product of two vector4's
float DotProduct(const vector4 &a, const vector4 &b) 
{
  return a.x*b.x + a.y*b.y + a.z*b.z + a.w*b.w;
}

// Swap two vector2's
void SwapVec(vector2 &a, vector2 &b) 
{
  vector2 tmp(a);

  a = b;
  b = tmp;
}

// Swap two vector3's
void SwapVec(vector3 &a, vector3 &b) 
{
  vector3 tmp(a);

  a = b;
  b = tmp;
}

// Swap two vector4's
void SwapVec(vector4 &a, vector4 &b) 
{
  vector4 tmp(a);

  a = b;
  b = tmp;
}

// Cross product of two vector3's
vector3 CrossProduct(const vector3 &a, const vector3 &b) 
{
  return vector3(a.y*b.z - a.z*b.y,
                 a.z*b.x - a.x*b.z,
                 a.x*b.y - a.y*b.x);
}

// Are these two vector2's nearly equal?
bool NearlyEquals( const vector2& a, const vector2& b, float r ) 
{
  vector2 diff = a - b; // difference

  return (DotProduct(diff, diff) < r*r); // radius
}

// Are these two vector3's nearly equal?
bool NearlyEquals( const vector3& a, const vector3& b, float r ) 
{
  vector3 diff = a - b; // difference

  return (DotProduct(diff, diff) < r*r); // radius
}

// Are these two vector4's nearly equal?
bool NearlyEquals( const vector4& a, const vector4& b, float r ) 
{
  vector4 diff = a - b; // difference

  return (DotProduct(diff, diff) < r*r); // radius
}

// -----------------------------------------------------------------------------------------------

////////////////////////////////////////////////////////////
// matrix22 class
//

// Constructor with initializing value
matrix22::matrix22(float v) 
{
  col[0].set(v, v);
  col[1].set(v, v);
}

// Constructor with initializing matrix22
matrix22::matrix22(const matrix22 &m) 
{
  col[0] = m[0];
  col[1] = m[1];
}

// Constructor with initializing vector2's
matrix22::matrix22(const vector2 &v0, const vector2 &v1) 
{
  col[0] = v0;
  col[1] = v1;
}

// Array indexing
vector2 &matrix22::operator [] (unsigned int i) 
{
  assert (i<2);
        
  return (vector2&)col[i];
}

// Array indexing
const vector2 &matrix22::operator [] (unsigned int i) const 
{
  assert (i<2);

  return (vector2&)col[i];
}

// Assign
matrix22 &matrix22::operator = (const matrix22 &m) 
{
  col[0] = m[0];
  col[1] = m[1];

  return *this;
}

// Assign
matrix22 &matrix22::operator = (const matrix33 &m) 
{
	col[0] = m[0];
	col[1] = m[1];

	return *this;
}

// Add a matrix22 to this one
matrix22 &matrix22::operator += (const matrix22 &m) 
{
  col[0] += m[0];
  col[1] += m[1];

  return *this;
}

// Subtract a matrix22 from this one
matrix22 &matrix22::operator -= (const matrix22 &m) 
{
  col[0] -= m[0];
  col[1] -= m[1];

  return *this;
}

// Multiply the matrix22 by another matrix22
matrix22 &matrix22::operator *= (const matrix22 &m) 
{
  matrix22 t;
  
  for (unsigned int r = 0; r < 2; r++) 
  {
    for (unsigned int c = 0; c < 2; c++) 
    {
      float f = 0;
          
      f += col[0][r] * m[c][0];
      f += col[1][r] * m[c][1];
          
      t[c][r] = f;
    }
  }
  
  *this = t;
  
  return *this;
}

// Multiply the matrix22 by a float
matrix22 &matrix22::operator *= (float f) 
{
  col[0] *= f;
  col[1] *= f;

  return *this;
}

// Divid the matrix22 by a float
matrix22 &matrix22::operator /= (float f)
{
  col[0] /= f;
  col[1] /= f;

  return *this;
}

// Are these two matrix22's equal?
bool operator == (const matrix22 &a, const matrix22 &b) 
{
  return ((a[0] == b[0]) && (a[1] == b[1]));
}

// Are these two matrix22's not equal?
bool operator != (const matrix22 &a, const matrix22 &b) 
{
  return ((a[0] != b[0]) || (a[1] != b[1]));
}

// Add two matrix22's
matrix22 operator + (const matrix22 &a, const matrix22 &b) 
{
  matrix22 ret(a);

  ret += b;

  return ret;
}

// Subtract one matrix22 from another
matrix22 operator - (const matrix22 &a, const matrix22 &b) 
{
  matrix22 ret(a);

  ret -= b;

  return ret;
}

// Multiply matrix22 by another matrix22
matrix22 operator * (const matrix22 &a, const matrix22 &b) 
{
  matrix22 ret(a);

  ret *= b;

  return ret;
}

// Multiply a vector2 by this matrix22
vector2 operator * (const matrix22 &m, const vector2 &v) 
{
  vector2 ret;

  ret.x = v.x * m[0][0] + v.y * m[1][0];
  ret.y = v.x * m[0][1] + v.y * m[1][1];

  return ret;
}

// Multiply a vector2 by this matrix22
vector2 operator * (const vector2 &v, const matrix22 &m) 
{
  vector2 ret;

  ret.x = DotProduct(m[0], v);
  ret.y = DotProduct(m[1], v);

  return ret;

}

// Multiply matrix22 by a float
matrix22 operator * (float f, const matrix22 &m) 
{
  matrix22 ret(m);

  ret *= f;

  return ret;
}

// Multiply matrix22 by a float
matrix22 operator * (const matrix22 &m, float f) 
{
  matrix22 ret(m);

  ret *= f;

  return ret;
}

// Divid matrix22 by a float
matrix22 operator / (float f, const matrix22 &m)
{
  matrix22 ret(m);

  ret /= f;

  return ret;
}

// Divid matrix22 by a float
matrix22 operator / (const matrix22 &m, float f)
{
  matrix22 ret(m);

  ret /= f;

  return ret;
}

// Set matrix22 to the identity matrix
matrix22 &matrix22::identity() 
{
  for (unsigned int c = 0; c < 2; c++) 
  {
    for (unsigned int r = 0; r < 2; r++) 
    {
      if (c == r) 
        col[c][r] = 1.0F;
      else 
        col[c][r] = 0.0F;
    } 
  }
  
  return *this;
}

// Transpose the matrix22
matrix22 &matrix22::transpose() 
{
  float t;
  
  for (unsigned int c = 0; c < 2; c++) 
  {
    for (unsigned int r = c + 1; r < 2; r++) 
    {
      t = col[c][r];
      col[c][r] = col[r][c];
      col[r][c] = t;
    } 
  }
  
  return *this;
}

// Invert the matrix22
matrix22 &matrix22::invert() 
{
    matrix22 a(*this) , b;
    float det = fabs(a[0][0] * a[1][1] - a[0][1] * a[1][0]);

	b[0][0] = a[1][1] / det;
	b[1][1] = a[0][0] / det;
	b[1][0] = -a[1][0] / det;
	b[0][1] = -a[0][1] / det;
    
    *this = b;
    return *this;
}

// Return a matrix22 set to the identity matrix
matrix22 IdentityMatrix22() 
{
  matrix22 ret;

  return ret.identity();
}

// Return the transpose of the matrix22
matrix22 TransposeMatrix22(const matrix22 &m) 
{
  matrix22 ret(m);

  return ret.transpose();
}

// Return the inverted matrix22
matrix22 InvertMatrix22(const matrix22 &m) 
{
  matrix22 ret(m);

  return ret.invert();
}

// Return a 2D rotation matrix22
matrix22 RotateRadMatrix22(float rad) 
{
  matrix22 ret;
  float sinA, cosA;

  sinA = (float)sin(rad);
  cosA = (float)cos(rad);

  ret[0][0] = cosA; ret[1][0] = -sinA;
  ret[0][1] = sinA; ret[1][1] =  cosA;

  return ret;
}

// Return a 2D translation matrix22
matrix22 TranslateMatrix22(float x, float y) 
{
  matrix22 ret;

  ret.identity();
  ret[2][0] = x;
  ret[2][1] = y;

  return ret;
}

// Return a 2D scale matrix22
matrix22 ScaleMatrix22(float x, float y, float z) 
{
  matrix22 ret;

  ret.identity();
  ret[0][0] = x;
  ret[1][1] = y;
  ret[2][2] = z;

  return ret;
}

////////////////////////////////////////////////////////////
// matrix33 class
//

// Constructor with initializing value
matrix33::matrix33(float v) 
{
	col[0].set(v, v, v);
	col[1].set(v, v, v);
	col[2].set(v, v, v);
}

// Constructor with initializing matrix33
matrix33::matrix33(const matrix33 &m) 
{
	col[0] = m[0];
	col[1] = m[1];
	col[2] = m[2];
}

// Constructor with initializing vector3's
matrix33::matrix33(const vector3 &v0, const vector3 &v1, const vector3 &v2) 
{
	col[0] = v0;
	col[1] = v1;
	col[2] = v2;
}

// Array indexing
vector3 &matrix33::operator [] (unsigned int i) 
{
	assert (i<3);

	return (vector3&)col[i];
}

// Array indexing
const vector3 &matrix33::operator [] (unsigned int i) const 
{
	assert (i<3);

	return (vector3&)col[i];
}

// Assign
matrix33 &matrix33::operator = (const matrix33 &m) 
{
	col[0] = m[0];
	col[1] = m[1];
	col[2] = m[2];

	return *this;
}

// Add a matrix33 to this one
matrix33 &matrix33::operator += (const matrix33 &m) 
{
	col[0] += m[0];
	col[1] += m[1];
	col[2] += m[2];

	return *this;
}

// Subtract a matrix33 from this one
matrix33 &matrix33::operator -= (const matrix33 &m) 
{
	col[0] -= m[0];
	col[1] -= m[1];
	col[2] -= m[2];

	return *this;
}

// Multiply the matrix33 by another matrix33
matrix33 &matrix33::operator *= (const matrix33 &m) 
{
	matrix33 t;

	for (unsigned int r = 0; r < 3; r++) 
	{
		for (unsigned int c = 0; c < 3; c++) 
		{
			float f = 0;

			f += col[0][r] * m[c][0];
			f += col[1][r] * m[c][1];
			f += col[2][r] * m[c][2];

			t[c][r] = f;
		}
	}

	*this = t;

	return *this;
}

// Multiply the matrix33 by a float
matrix33 &matrix33::operator *= (float f) 
{
	col[0] *= f;
	col[1] *= f;
	col[2] *= f;

	return *this;
}

// Divid the matrix33 by a float
matrix33 &matrix33::operator /= (float f)
{
	col[0] /= f;
	col[1] /= f;
	col[2] /= f;

	return *this;
}

// Are these two matrix33's equal?
bool operator == (const matrix33 &a, const matrix33 &b) 
{
	return ((a[0] == b[0]) && (a[1] == b[1]) && (a[2] == b[2]));
}

// Are these two matrix33's not equal?
bool operator != (const matrix33 &a, const matrix33 &b) 
{
	return ((a[0] != b[0]) || (a[1] != b[1]) || (a[2] != b[2]));
}

// Add two matrix33's
matrix33 operator + (const matrix33 &a, const matrix33 &b) 
{
	matrix33 ret(a);

	ret += b;

	return ret;
}

// Subtract one matrix33 from another
matrix33 operator - (const matrix33 &a, const matrix33 &b) 
{
	matrix33 ret(a);

	ret -= b;

	return ret;
}

// Multiply matrix33 by another matrix33
matrix33 operator * (const matrix33 &a, const matrix33 &b) 
{
	matrix33 ret(a);

	ret *= b;

	return ret;
}

// Multiply a vector3 by this matrix33
vector3 operator * (const matrix33 &m, const vector3 &v) 
{
	vector3 ret;

	ret.x = v.x * m[0][0] + v.y * m[1][0] + v.z * m[2][0];
	ret.y = v.x * m[0][1] + v.y * m[1][1] + v.z * m[2][1];
	ret.z = v.x * m[0][2] + v.y * m[1][2] + v.z * m[2][2];

	return ret;
}

// Multiply a vector3 by this matrix33
vector3 operator * (const vector3 &v, const matrix33 &m) 
{
	vector3 ret;

	ret.x = DotProduct(m[0], v);
	ret.y = DotProduct(m[1], v);
	ret.z = DotProduct(m[2], v);

	return ret;

}

// Multiply matrix33 by a float
matrix33 operator * (float f, const matrix33 &m) 
{
	matrix33 ret(m);

	ret *= f;

	return ret;
}

// Multiply matrix33 by a float
matrix33 operator * (const matrix33 &m, float f) 
{
	matrix33 ret(m);

	ret *= f;

	return ret;
}

// Divid matrix33 by a float
matrix33 operator / (float f, const matrix33 &m)
{
	matrix33 ret(m);

	ret /= f;

	return ret;
}

// Divid matrix33 by a float
matrix33 operator / (const matrix33 &m, float f)
{
	matrix33 ret(m);

	ret /= f;

	return ret;
}

// Get determinant of matrix33
float &matrix33::determinant()
{
	matrix33 a(*this);

	float det = a[0][0] * a[1][1] * a[2][2] +
				a[0][1] * a[1][2] * a[2][0] +
				a[0][2] * a[1][0] * a[2][1] -
				a[2][0] * a[1][1] * a[0][2] -
				a[2][1] * a[1][2] * a[0][0] -
				a[2][2] * a[1][0] * a[0][1] ;

	return det;
}

// Set matrix33 to the identity matrix
matrix33 &matrix33::identity() 
{
	for (unsigned int c = 0; c < 3; c++) 
	{
		for (unsigned int r = 0; r < 3; r++) 
		{
			if (c == r) 
				col[c][r] = 1.0F;
			else 
				col[c][r] = 0.0F;
		} 
	}

	return *this;
}

// Transpose the matrix33
matrix33 &matrix33::transpose() 
{
	float t;

	for (unsigned int c = 0; c < 3; c++) 
	{
		for (unsigned int r = c + 1; r < 3; r++) 
		{
			t = col[c][r];
			col[c][r] = col[r][c];
			col[r][c] = t;
		} 
	}

	return *this;
}

// Invert the matrix33
matrix33 &matrix33::invert() 
{
	matrix33 a(*this) , b;

	float determine =   a[0][0] * a[1][1] * a[2][2] +
						a[0][1] * a[1][2] * a[2][0] +
						a[0][2] * a[1][0] * a[2][1] -
						a[2][0] * a[1][1] * a[0][2] -
						a[2][1] * a[1][2] * a[0][0] -
						a[2][2] * a[1][0] * a[0][1] ;

	determine = fabs(determine);

	b[0][0] = a[1][1] * a[2][2] - a[2][1] * a[1][2];
	b[0][1] = a[2][0] * a[1][2] - a[1][0] * a[2][2];
	b[0][2] = a[1][0] * a[2][1] - a[2][0] * a[1][1];
	b[1][0] = a[2][1] * a[0][2] - a[0][1] * a[2][2];
	b[1][1] = a[0][0] * a[2][2] - a[2][0] * a[0][2];
	b[1][2] = a[2][0] * a[0][1] - a[0][0] * a[2][1];
	b[2][0] = a[0][1] * a[1][2] - a[1][1] * a[0][2];
	b[2][1] = a[1][0] * a[0][2] - a[0][0] * a[1][2];
	b[2][2] = a[0][0] * a[1][1] - a[1][0] * a[0][1];

	for (int i = 0 ; i < 3 ; i++)
		for (int j = 0 ; j < 3 ; j++)
			b[i][j] /= determine;

	b.transpose();

	*this = b;
	return *this;

	/*
	matrix33 a(*this);
	matrix33 b(IdentityMatrix33());

	unsigned int c, r;
	unsigned int cc;
	unsigned int rowMax; // Points to max abs value row in this column
	unsigned int row;
	float tmp;

	// Go through columns
	for (c=0; c<3; c++) 
	{
	// Find the row with max value in this column
	rowMax = c;
	for (r=c+1; r<3; r++) 
	{
	if (fabs(a[c][r]) > fabs(a[c][rowMax])) 
	{
	rowMax = r;
	}
	}

	// If the max value here is 0, we can't invert.  Return identity.
	if (a[rowMax][c] == 0.0F) 
	return (identity());

	// Swap row "rowMax" with row "c"
	for (cc=0; cc<3; cc++) 
	{
	tmp = a[cc][c];
	a[cc][c] = a[cc][rowMax];
	a[cc][rowMax] = tmp;
	tmp = b[cc][c];
	b[cc][c] = b[cc][rowMax];
	b[cc][rowMax] = tmp;
	}

	// Now everything we do is on row "c".
	// Set the max cell to 1 by dividing the entire row by that value
	tmp = a[c][c];
	for (cc=0; cc<3; cc++) 
	{
	a[cc][c] /= tmp;
	b[cc][c] /= tmp;
	}

	// Now do the other rows, so that this column only has a 1 and 0's
	for (row = 0; row < 3; row++) 
	{
	if (row != c) 
	{
	tmp = a[c][row];
	for (cc=0; cc<3; cc++) 
	{
	a[cc][row] -= a[cc][c] * tmp;
	b[cc][row] -= b[cc][c] * tmp;
	}
	}
	}

	}

	*this = b;

	return *this;
	*/
}

// Return a matrix33 set to the identity matrix
matrix33 IdentityMatrix33() 
{
	matrix33 ret;

	return ret.identity();
}

// Return the transpose of the matrix33
matrix33 TransposeMatrix33(const matrix33 &m) 
{
	matrix33 ret(m);

	return ret.transpose();
}

// Return the inverted matrix33
matrix33 InvertMatrix33(const matrix33 &m) 
{
	matrix33 ret(m);

	return ret.invert();
}

// Return a 2D rotation matrix33
matrix33 RotateRadMatrix33(float rad) 
{
	matrix33 ret;
	float sinA, cosA;

	sinA = (float)sin(rad);
	cosA = (float)cos(rad);

	ret[0][0] = cosA; ret[1][0] = -sinA; ret[2][0] = 0.0F;
	ret[0][1] = sinA; ret[1][1] =  cosA; ret[2][1] = 0.0F;
	ret[0][2] = 0.0F; ret[1][2] =  0.0F; ret[2][2] = 1.0F;

	return ret;
}

// Return a 2D translation matrix33
matrix33 TranslateMatrix33(float x, float y) 
{
	matrix33 ret;

	ret.identity();
	ret[2][0] = x;
	ret[2][1] = y;

	return ret;
}

// Return a 2D/3D scale matrix33
matrix33 ScaleMatrix33(float x, float y, float z) 
{
	matrix33 ret;

	ret.identity();
	ret[0][0] = x;
	ret[1][1] = y;
	ret[2][2] = z;

	return ret;
}

////////////////////////////////////////////////////////////
// matrix44 class
//

// Constructor with initializing value
matrix44::matrix44(float v) 
{
  col[0].set(v, v, v, v);
  col[1].set(v, v, v, v);
  col[2].set(v, v, v, v);
  col[3].set(v, v, v, v);
}

// Constructor with initializing matrix44
matrix44::matrix44(const matrix44 &m) 
{
  col[0] = m[0];
  col[1] = m[1];
  col[2] = m[2];
  col[3] = m[3];
}

// Constructor with initializing matrix33
matrix44::matrix44(const matrix33 &m) 
{
  col[0] = m[0];
  col[1] = m[1];
  col[2] = m[2];
  col[3] = vector4(0.0, 0.0, 0.0, 1.0);
}

// Constructor with initializing vector4's
matrix44::matrix44(const vector4 &v0, const vector4 &v1, 
                   const vector4 &v2, const vector4 &v3) 
{
  col[0] = v0;
  col[1] = v1;
  col[2] = v2;
  col[3] = v3;
}

// Array indexing
vector4 &matrix44::operator [] (unsigned int i) 
{
  assert (i<4);

  return (vector4&) col[i];
}

// Array indexing
const vector4 &matrix44::operator [] (unsigned int i) const 
{
  assert (i<4);
  
  return (vector4&) col[i];
}

// Assign
matrix44 &matrix44::operator = (const matrix44 &m) 
{
  col[0] = m[0];
  col[1] = m[1];
  col[2] = m[2];
  col[3] = m[3];

  return *this;
}

// Assign a matrix33 to the matrix44
matrix44 &matrix44::operator = (const matrix33 &m) 
{
  col[0] = m[0];
  col[1] = m[1];
  col[2] = m[2];
  col[3] = vector4(0.0, 0.0, 0.0, 1.0);

  return *this;
}

// Add a matrix44 to this one
matrix44 &matrix44::operator += (const matrix44 &m) 
{
  col[0] += m[0];
  col[1] += m[1];
  col[2] += m[2];
  col[3] += m[3];

  return *this;
}

// Subtract a matrix44 from this one
matrix44 &matrix44::operator -= (const matrix44 &m) 
{
  col[0] -= m[0];
  col[1] -= m[1];
  col[2] -= m[2];
  col[3] -= m[3];

  return *this;
}

// Multiply the matrix44 by another matrix44
matrix44 &matrix44::operator *= (const matrix44 &m) 
{
  matrix44 t;
  
  for (unsigned int r = 0; r < 4; r++) 
  {
    for (unsigned int c = 0; c < 4; c++) 
    {
      float f = 0;
          
      f += col[0][r] * m[c][0];
      f += col[1][r] * m[c][1];
      f += col[2][r] * m[c][2];
      f += col[3][r] * m[c][3];
          
      t[c][r] = f;
    }
  }
  
  *this = t;

  return *this;
}

// Multiply the matrix44 by a float
matrix44 &matrix44::operator *= (float f) 
{
  col[0] *= f;
  col[1] *= f;
  col[2] *= f;
  col[3] *= f;

  return *this;
}

// Are these two matrix44's equal?
bool operator == (const matrix44 &a, const matrix44 &b) 
{
  return ((a[0] == b[0]) && (a[1] == b[1]) &&
          (a[2] == b[2]) && (a[3] == b[3]));
}

// Are these two matrix44's not equal?
bool operator != (const matrix44 &a, const matrix44 &b) 
{
  return ((a[0] != b[0]) || (a[1] != b[1]) ||
          (a[2] != b[2]) || (a[3] != b[3]));
}

// Add two matrix44's
matrix44 operator + (const matrix44 &a, const matrix44 &b) 
{
  matrix44 ret(a);

  ret += b;

  return ret;
}

// Subtract one matrix44 from another
matrix44 operator - (const matrix44 &a, const matrix44 &b) 
{
  matrix44 ret(a);

  ret -= b;

  return ret;
}

// Multiply matrix44 by another matrix44
matrix44 operator * (const matrix44 &a, const matrix44 &b) 
{
  matrix44 ret(a);

  ret *= b;

  return ret;
}

// Multiply a vector3 by this matrix44
vector3 operator * (const matrix44 &m, const vector3 &v) 
{
  vector4 ret(v);

  ret = m * ret;

  return vector3(ret.x, ret.y, ret.z);
}

// Multiply a vector3 by this matrix44
vector3 operator * (const vector3 &v, const matrix44 &m) 
{
  vector4 ret(v);

  ret = ret * m;

  return vector3(ret.x, ret.y, ret.z);
}

// Multiply a vector4 by this matrix44
vector4 operator * (const matrix44 &m, const vector4 &v) 
{
  vector4 ret;

  ret.x = v.x * m[0][0] + v.y * m[1][0] + v.z * m[2][0] + v.w * m[3][0];
  ret.y = v.x * m[0][1] + v.y * m[1][1] + v.z * m[2][1] + v.w * m[3][1];
  ret.z = v.x * m[0][2] + v.y * m[1][2] + v.z * m[2][2] + v.w * m[3][2];
  ret.w = v.x * m[0][3] + v.y * m[1][3] + v.z * m[2][3] + v.w * m[3][3];

  return ret;
}

// Multiply a vector4 by this matrix44
vector4 operator * (const vector4 &v, const matrix44 &m) 
{
  vector4 ret;

  ret.x = DotProduct(m[0], v);
  ret.y = DotProduct(m[1], v);
  ret.z = DotProduct(m[2], v);
  ret.w = DotProduct(m[3], v);

  return ret;
}

// Multiply matrix44 by a float
matrix44 operator * (float f, const matrix44 &m) 
{
  matrix44 ret(m);

  ret *= f;

  return ret;
}

// Set matrix44 to the identity matrix
matrix44 &matrix44::identity() 
{
  for (unsigned int c = 0; c < 4; c++) 
  {
    for (unsigned int r = 0; r < 4; r++) 
    {
      if (c == r) 
        col[c][r] = 1.0F;
      else 
        col[c][r] = 0.0F;
    } 
  } 
  
  return *this;
}

// Transpose the matrix44
matrix44 &matrix44::transpose() 
{
  float t;
  
  for (unsigned int c = 0; c < 4; c++) 
  {
    for (unsigned int r = c + 1; r < 4; r++) 
    {
      t = col[c][r];
      col[c][r] = col[r][c];
      col[r][c] = t;
    } 
  } 
  
  return *this;
}

// Invert the matrix44
matrix44 &matrix44::invert() 
{
  matrix44 a(*this);
  matrix44 b(IdentityMatrix44());

  unsigned int r, c;
  unsigned int cc;
  unsigned int rowMax; // Points to max abs value row in this column
  unsigned int row;
  float tmp;

  // Go through columns
  for (c=0; c<4; c++) 
  {
      
    // Find the row with max value in this column
    rowMax = c;
    for (r=c+1; r<4; r++) 
    {
      if (fabs(a[c][r]) > fabs(a[c][rowMax])) 
      {
        rowMax = r;
      }
    }
      
    // If the max value here is 0, we can't invert.  Return identity.
    if (a[rowMax][c] == 0.0F) 
      return (identity());
      
    // Swap row "rowMax" with row "c"
    for (cc=0; cc<4; cc++) 
    {
      tmp = a[cc][c];
      a[cc][c] = a[cc][rowMax];
      a[cc][rowMax] = tmp;
      tmp = b[cc][c];
      b[cc][c] = b[cc][rowMax];
      b[cc][rowMax] = tmp;
    }
      
    // Now everything we do is on row "c".
    // Set the max cell to 1 by dividing the entire row by that value
    tmp = a[c][c];
    for (cc=0; cc<4; cc++) 
    {
      a[cc][c] /= tmp;
      b[cc][c] /= tmp;
    }
      
    // Now do the other rows, so that this column only has a 1 and 0's
    for (row = 0; row < 4; row++) 
    {
      if (row != c) 
      {
        tmp = a[c][row];
        for (cc=0; cc<4; cc++) 
        {
          a[cc][row] -= a[cc][c] * tmp;
          b[cc][row] -= b[cc][c] * tmp;
        }
      }
    }
      
  }

  *this = b;

  return *this;
}

// Return a matrix44 set to the identity matrix
matrix44 IdentityMatrix44() 
{
  matrix44 ret;

  return ret.identity();
}

// Return the transpose of the matrix44
matrix44 TransposeMatrix44(const matrix44 &m) 
{
  matrix44 ret(m);

  return ret.transpose();
}

// Return the inverted matrix44
matrix44 InvertMatrix44(const matrix44 &m) 
{
  matrix44 ret(m);

  return ret.invert();
}

// Return a 3D axis-rotation matrix44
// Pass in 'x', 'y', or 'z' for the axis.
matrix44 RotateRadMatrix44(char axis, float rad) 
{
  matrix44 ret;
  float sinA, cosA;

  sinA = (float)sin(rad);
  cosA = (float)cos(rad);

  switch(axis) 
  {
  case 'x':
  case 'X':
    ret[0][0] =  1.0F; ret[1][0] =  0.0F; ret[2][0] =  0.0F;
    ret[0][1] =  0.0F; ret[1][1] =  cosA; ret[2][1] = -sinA;
    ret[0][2] =  0.0F; ret[1][2] =  sinA; ret[2][2] =  cosA;
    break;
    
  case 'y':
  case 'Y':
    ret[0][0] =  cosA; ret[1][0] =  0.0F; ret[2][0] =  sinA;
    ret[0][1] =  0.0F; ret[1][1] =  1.0F; ret[2][1] =  0.0F;
    ret[0][2] = -sinA; ret[1][2] =  0.0F; ret[2][2] =  cosA;
    break;
    
  case 'z':
  case 'Z':
    ret[0][0] =  cosA; ret[1][0] = -sinA; ret[2][0] =  0.0F;
    ret[0][1] =  sinA; ret[1][1] =  cosA; ret[2][1] =  0.0F;
    ret[0][2] =  0.0F; ret[1][2] =  0.0F; ret[2][2] =  1.0F;
    break;
  }
  
  ret[0][3] = 0.0F; ret[1][3] = 0.0F; ret[2][3] = 0.0F;
  ret[3][0] = 0.0F;
  ret[3][1] = 0.0F;
  ret[3][2] = 0.0F;
  ret[3][3] = 1.0F;
  
  return ret;
}

// Return a 3D axis-rotation matrix44
// Pass in an arbitrary vector3 axis.
matrix44 RotateRadMatrix44(const vector3 &axis, float rad) 
{
  matrix44 ret;
  float sinA, cosA;
  float invCosA;
  vector3 nrm = axis;
  float x, y, z;
  float xSq, ySq, zSq;

  nrm.normalize();
  sinA = (float)sin(rad);
  cosA = (float)cos(rad);
  invCosA = 1.0F - cosA;

  x = nrm.x;
  y = nrm.y;
  z = nrm.z;

  xSq = x * x;
  ySq = y * y;
  zSq = z * z;

  ret[0][0] = (invCosA * xSq) + (cosA);
  ret[1][0] = (invCosA * x * y) - (sinA * z );
  ret[2][0] = (invCosA * x * z) + (sinA * y );
  ret[3][0] = 0.0F;
  
  ret[0][1] = (invCosA * x * y) + (sinA * z);
  ret[1][1] = (invCosA * ySq) + (cosA);
  ret[2][1] = (invCosA * y * z) - (sinA * x);
  ret[3][1] = 0.0F;

  ret[0][2] = (invCosA * x * z) - (sinA * y);
  ret[1][2] = (invCosA * y * z) + (sinA * x);
  ret[2][2] = (invCosA * zSq) + (cosA);
  ret[3][2] = 0.0F;

  ret[0][3] = 0.0F;
  ret[1][3] = 0.0F;
  ret[2][3] = 0.0F;
  ret[3][3] = 1.0F;

  return ret;
}

// Return a 3D translation matrix44
matrix44 TranslateMatrix44(float x, float y, float z) 
{
  matrix44 ret;

  ret.identity();
  ret[3][0] = x;
  ret[3][1] = y;
  ret[3][2] = z;

  return ret;
}

// Return a 3D/4D scale matrix44
matrix44 ScaleMatrix44(float x, float y, float z, float w) 
{
  matrix44 ret;

  ret.identity();
  ret[0][0] = x;
  ret[1][1] = y;
  ret[2][2] = z;
  ret[3][3] = w;

  return ret;
}

// Return a "lookat" matrix44 given the current camera position (vector3),
//   camera-up vector3, and camera-target vector3.
matrix44 LookAtMatrix44(const vector3 &camPos, const vector3 &camUp, 
                        const vector3 &target ) 
{
  matrix44 rot;
  matrix44 tran;

  vector3 look = (camPos - target);
  look.normalize();

  vector3 right = CrossProduct(camUp, look);
  right.normalize();

  vector3 up = CrossProduct(look, right);
  up.normalize();

  rot[0][0] = right.x;
  rot[1][0] = right.y;
  rot[2][0] = right.z;
  rot[3][0] = 0.0;

  rot[0][1] = up.x;
  rot[1][1] = up.y;
  rot[2][1] = up.z;
  rot[3][1] = 0.0;

  rot[0][2] = look.x;
  rot[1][2] = look.y;
  rot[2][2] = look.z;
  rot[3][2] = 0.0;

  rot[0][3] = 0.0F;
  rot[1][3] = 0.0F;
  rot[2][3] = 0.0F;
  rot[3][3] = 1.0F;

  tran = TranslateMatrix44(-camPos.x, -camPos.y, -camPos.z);

  return (rot * tran);
}

// Return a frustum matrix44 given the left, right, bottom, top,
//   near, and far values for the frustum boundaries.
matrix44 FrustumMatrix44(float l, float r, 
                         float b, float t, float n, float f) 
{
  matrix44 ret;
  float width = r-l;
  float height = t-b;
  float depth = f-n;

  ret[0][0] = (2*n) / width;
  ret[0][1] = 0.0F;
  ret[0][2] = 0.0F;
  ret[0][3] = 0.0F;

  ret[1][0] = 0.0F;
  ret[1][1] = (2*n) / height;
  ret[1][2] = 0.0F;
  ret[1][3] = 0.0F;

  ret[2][0] = (r + l) / width;
  ret[2][1] = (t + b) / height;
  ret[2][2] = -(f + n) / depth;
  ret[2][3] = -1.0F;

  ret[3][0] = 0.0F;
  ret[3][1] = 0.0F;
  ret[3][2] = -(2*f*n) / depth;
  ret[3][3] = 0.0F;

  return ret;
}

// Return a perspective matrix44 given the field-of-view in the Y
//   direction in degrees, the aspect ratio of Y/X, and near and
//   far plane distances.
matrix44 PerspectiveMatrix44(float fovY, float aspect, float n, float f) 
{
  matrix44 ret;
  float angle;
  float cot;

  angle = fovY / 2.0F;
  angle = DegToRad( angle );

  cot = (float) cos(angle) / (float) sin(angle);

  ret[0][0] = cot / aspect;
  ret[0][1] = 0.0F;
  ret[0][2] = 0.0F;
  ret[0][3] = 0.0F;

  ret[1][0] = 0.0F;
  ret[1][1] = cot;
  ret[1][2] = 0.0F;
  ret[1][3] = 0.0F;

  ret[2][0] = 0.0F;
  ret[2][1] = 0.0F;
  ret[2][2] = -(f + n) / (f - n);
  ret[2][3] = -1.0F;


  ret[3][0] = 0.0F;
  ret[3][1] = 0.0F;
  ret[3][2] = -(2*f*n) / (f - n);
  ret[3][3] = 0.0F;

  return ret;
}

// Return an orthographic matrix44 given the left, right, bottom, top,
//   near, and far values for the frustum boundaries.
matrix44 OrthoMatrix44(float l, float r, 
                       float b, float t, float n, float f) 
{
  matrix44 ret;
  float width = r-l;
  float height = t-b;
  float depth = f-n;
  
  ret[0][0] = 2.0F / width;
  ret[0][1] = 0.0F;
  ret[0][2] = 0.0F;
  ret[0][3] = 0.0F;

  ret[1][0] = 0.0F;
  ret[1][1] = 2.0F / height;
  ret[1][2] = 0.0F;
  ret[1][3] = 0.0F;

  ret[2][0] = 0.0F;
  ret[2][1] = 0.0F;
  ret[2][2] = -(2.0F) / depth;
  ret[2][3] = 0.0F;

  ret[3][0] = -(r + l) / width;
  ret[1][3] = -(t + b) / height;
  ret[3][2] = -(f + n) / depth;
  ret[3][3] = 1.0F;
  
  return ret;
}

// Return an orientation matrix using 3 basis normalized vectors
matrix44	OrthoNormalMatrix44(const vector3 &xdir, 
				const vector3 &ydir, const vector3 &zdir)
{
  matrix44 ret;
  
  ret[0] = (vector4)xdir;
  ret[1] = (vector4)ydir;
  ret[2] = (vector4)zdir;
  ret[3][3] = 1.0F;
  
  return ret;
}


////////////////////////////////////////////////////////////
// Debug functions
//

// Print a vector2 to a file
void vector2::fprint(FILE* file, char* str) const 
{
  fprintf(file, "%svector2: <%f, %f>\n", str, x, y);
}

// Print a vector3 to a file
void vector3::fprint(FILE* file, char* str) const 
{
  fprintf(file, "%svector3: <%f, %f, %f>\n", str, x, y, z);
}

// Print a vector4 to a file
void vector4::fprint(FILE* file, char* str) const 
{
  fprintf(file, "%svector4: <%f, %f, %f, %f>\n", str, x, y, z, w);
}

// Print a matrix33 to a file
void matrix33::fprint(FILE* file, char * str) const 
{
  fprintf(file, "%smatrix33:\n", str);
  vector3 row0(col[0][0], col[1][0], col[2][0]);
  row0.fprint(file, "\t");
  vector3 row1(col[0][1], col[1][1], col[2][1]);
  row1.fprint(file, "\t");
  vector3 row2(col[0][2], col[1][2], col[2][2]);
  row2.fprint(file, "\t");
}

// Print a matrix44 to a file
void matrix44::fprint(FILE* file, char* str) const 
{
  fprintf(file, "%smatrix44:\n", str);
  vector4 row0(col[0][0], col[1][0], col[2][0], col[3][0]);
  row0.fprint(file, "\t");
  vector4 row1(col[0][1], col[1][1], col[2][1], col[3][1]);
  row1.fprint(file, "\t");
  vector4 row2(col[0][2], col[1][2], col[2][2], col[3][2]);
  row2.fprint(file, "\t");
  vector4 row3(col[0][3], col[1][3], col[2][3], col[3][3]);
  row3.fprint(file, "\t");
}
