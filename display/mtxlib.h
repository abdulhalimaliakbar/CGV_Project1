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

#ifndef MtxlibH
#define MtxlibH

#include "stdio.h"

static inline float DegToRad(float a) { return a*0.01745329252f; };
static inline float RadToDeg(float a) { return a*57.29577951f; };

class vector2;
class vector3;
class vector4;
class matrix22;
class matrix33;
class matrix44;

////////////////////////////////////////////////////////////
// vector2 class
//

class vector2 
{
 public:
  // Members
  float x, y;
  
 public:
  // Constructors
  // vector2(): x(0), y(0) {};
  vector2() {};
  vector2(float inX, float inY);
  vector2(const vector2 &v);
  
 public:
  // Operators
  float                 &operator [] (unsigned int index);
  const float           &operator [] (unsigned int index) const;
  vector2				&operator =  (const vector3 &v);
  vector2               &operator =  (const vector2 &v);
  vector2               &operator += (const vector2 &v);
  vector2               &operator -= (const vector2 &v);
  vector2               &operator *= (float f);
  vector2               &operator /= (float f);
  friend bool           operator == (const vector2 &a, const vector2 &b);
  friend bool           operator != (const vector2 &a, const vector2 &b);
  friend vector2        operator - (const vector2 &a);
  friend vector2        operator + (const vector2 &a, const vector2 &b);
  friend vector2        operator - (const vector2 &a, const vector2 &b);
  friend vector2        operator * (const vector2 &v, float f);
  friend vector2        operator * (float f, const vector2 &v);
  friend vector2        operator / (const vector2 &v, float f);
  
  //operator float*() {return &x;};

 public:
  // Methods
  void                  set(float xIn, float yIn);
  float                 length() const;
  float                 lengthSqr() const;
  bool                  isZero() const;
  vector2               &normalize();
  
  // Debug
  void                  fprint(FILE* file, char* str) const;
};


////////////////////////////////////////////////////////////
// vector3 class
//

class vector3 
{
 public:
  // Members
  float x, y, z;

 public:
  // Constructors
  // vector3(): x(0), y(0), z(0) {};
  vector3() {};
  vector3(float inX, float inY, float inZ);
  vector3(const vector3 &v);
  explicit vector3(const vector2 &v);
  explicit vector3(const vector4 &v);
  
 public:
  // Operators
  float                 &operator [] (unsigned int index);
  const float           &operator [] (unsigned int index) const;
  vector3               &operator =  (const vector3 &v);
  vector3               &operator =  (const vector2 &v);
  vector3               &operator += (const vector3 &v);
  vector3               &operator -= (const vector3 &v);
  vector3               &operator *= (float f);
  vector3               &operator /= (float f);
  friend bool           operator == (const vector3 &a, const vector3 &b);
  friend bool           operator != (const vector3 &a, const vector3 &b);
  friend vector3        operator - (const vector3 &a);
  friend vector3        operator + (const vector3 &a, const vector3 &b);
  friend vector3        operator - (const vector3 &a, const vector3 &b);
  friend vector3        operator * (const vector3 &v, float f);
  friend vector3        operator * (float f, const vector3 &v);
  friend vector3        operator / (const vector3 &v, float f);

  //operator float*() {return &x;};

 public:
  // Methods
  void                  set(float xIn, float yIn, float zIn);
  float                 length() const;
  float                 lengthSqr() const;
  bool                  isZero() const;
  vector3               &normalize();
  
  // Debug
  void                  fprint(FILE* file, char* str) const;
};


////////////////////////////////////////////////////////////
// vector4 class
//

class vector4 
{
 public:
  // Members
  float x, y, z, w;
  
 public:
  // Constructors
  // vector4(): x(0), y(0), z(0), w(0) {};
  vector4() {};
  vector4(float inX, float inY, float inZ, float inW);
  vector4(const vector4 &v);
  explicit vector4(const vector3 &v);
  explicit vector4(const vector2 &v);
  
 public:
  // Operators
  float                 &operator [] (unsigned int index);
  const float           &operator [] (unsigned int index) const;
  vector4               &operator =  (const vector4 &v);
  vector4               &operator =  (const vector3 &v);
  vector4               &operator =  (const vector2 &v);
  vector4               &operator += (const vector4 &v);
  vector4               &operator -= (const vector4 &v);
  vector4               &operator *= (float f);
  vector4               &operator /= (float f);
  friend bool           operator == (const vector4 &a, const vector4 &b);
  friend bool           operator != (const vector4 &a, const vector4 &b);
  friend vector4        operator - (const vector4 &a);
  friend vector4        operator + (const vector4 &a, const vector4 &b);
  friend vector4        operator - (const vector4 &a, const vector4 &b);
  friend vector4        operator * (const vector4 &v, float f);
  friend vector4        operator * (float f, const vector4 &v);
  friend vector4        operator / (const vector4 &v, float f);

  //operator float*() {return &x;};

 public:
  // Methods
  void                  set(float xIn, float yIn, float zIn, float wIn);
  float                 length() const;
  float                 lengthSqr() const;
  bool                  isZero() const;
  vector4               &normalize();
  
  // Debug
  void                  fprint(FILE* file, char* str) const;
};


////////////////////////////////////////////////////////////
// Miscellaneous vector functions
//

vector2 Normalized(const vector2 &a);
vector3 Normalized(const vector3 &a);
vector4 Normalized(const vector4 &a);
float DotProduct(const vector2 &a, const vector2 &b);
float DotProduct(const vector3 &a, const vector3 &b);
float DotProduct(const vector4 &a, const vector4 &b);
void SwapVec(vector2 &a, vector2 &b);
void SwapVec(vector3 &a, vector3 &b);
void SwapVec(vector4 &a, vector4 &b);
vector3 CrossProduct(const vector3 &a, const vector3 &b);
bool NearlyEquals(const vector2 &a, const vector2 &b, float r);
bool NearlyEquals(const vector3 &a, const vector3 &b, float r);
bool NearlyEquals(const vector4 &a, const vector4 &b, float r);


////////////////////////////////////////////////////////////
// matrix22 class
//

class matrix22
{
 public:
  // Members
  vector2       col[2];
  
 public:
  // Constructors
  matrix22() {};
  matrix22(float v);
  matrix22(const matrix22 &m);
  matrix22(const vector2 &v0, const vector2 &v1);
  
 public:
  // Operators
  vector2			&operator [] (unsigned int i);
  const vector2		&operator [] (unsigned int i) const;
  matrix22		&operator =	 (const matrix33 &m);
  matrix22		&operator =  (const matrix22 &m);
  matrix22		&operator += (const matrix22 &m);
  matrix22		&operator -= (const matrix22 &m);
  matrix22		&operator *= (const matrix22 &m);
  matrix22		&operator *= (float f);
  matrix22		&operator /= (float f);
  friend bool		operator == (const matrix22 &a, const matrix22 &b);
  friend bool		operator != (const matrix22 &a, const matrix22 &b);
  friend matrix22	operator + (const matrix22 &a, const matrix22 &b);
  friend matrix22	operator - (const matrix22 &a, const matrix22 &b);
  friend matrix22	operator * (const matrix22 &a, const matrix22 &b);
  friend vector2 	operator * (const matrix22 &m, const vector2 &v);
  friend vector2 	operator * (const vector2 &v, const matrix22 &m);
  friend matrix22	operator * (const matrix22 &m, float f);
  friend matrix22	operator * (float f, const matrix22 &m);
  friend matrix22	operator / (const matrix22 &m, float f);
  
  //operator float*() {return (float*)col[0]; };

 public:
  // Methods
  matrix22		&identity();
  matrix22		&transpose();
  matrix22		&invert();

  // Debug
  void			fprint(FILE* file, char* str) const;
};

matrix22	IdentityMatrix22();
matrix22	TransposeMatrix22(const matrix22 &m);
matrix22	InvertMatrix22(const matrix22 &m);
matrix22	RotateRadMatrix22(float rad);
matrix22	TranslateMatrix22(float x, float y);
matrix22	ScaleMatrix22(float x, float y, float z = 1.0);

////////////////////////////////////////////////////////////
// matrix33 class
//

class matrix33 
{
 public:
  // Members
  vector3       col[3];
  
 public:
  // Constructors
  matrix33() {};
  matrix33(float v);
  matrix33(const matrix33 &m);
  matrix33(const vector3 &v0, const vector3 &v1, const vector3 &v2);
  
 public:
  // Operators
  vector3		&operator [] (unsigned int i);
  const vector3		&operator [] (unsigned int i) const;
  matrix33		&operator =  (const matrix33 &m);
  matrix33		&operator += (const matrix33 &m);
  matrix33		&operator -= (const matrix33 &m);
  matrix33		&operator *= (const matrix33 &m);
  matrix33		&operator *= (float f);
  matrix33		&operator /= (float f);
  friend bool		operator == (const matrix33 &a, const matrix33 &b);
  friend bool		operator != (const matrix33 &a, const matrix33 &b);
  friend matrix33	operator + (const matrix33 &a, const matrix33 &b);
  friend matrix33	operator - (const matrix33 &a, const matrix33 &b);
  friend matrix33	operator * (const matrix33 &a, const matrix33 &b);
  friend vector3 	operator * (const matrix33 &m, const vector3 &v);
  friend vector3 	operator * (const vector3 &v, const matrix33 &m);
  friend matrix33	operator * (const matrix33 &m, float f);
  friend matrix33	operator * (float f, const matrix33 &m);
  friend matrix33	operator / (const matrix33 &m, float f);
  
  //operator float*() {return (float*)col[0]; };

 public:
  // Methods
  float			&determinant();
  matrix33		&identity();
  matrix33		&transpose();
  matrix33		&invert();

  // Debug
  void			fprint(FILE* file, char* str) const;
};

matrix33	IdentityMatrix33();
matrix33	TransposeMatrix33(const matrix33 &m);
matrix33	InvertMatrix33(const matrix33 &m);
matrix33	RotateRadMatrix33(float rad);
matrix33	TranslateMatrix33(float x, float y);
matrix33	ScaleMatrix33(float x, float y, float z = 1.0);


////////////////////////////////////////////////////////////
// matrix44 class
//

class matrix44 
{
 public:
  // Members
  vector4	col[4];

 public:
  // Constructors
  matrix44() {};
  matrix44(float v);
  matrix44(const matrix44 &m);
  matrix44(const vector4 &v0, const vector4 &v1, 
	   const vector4 &v2, const vector4 &v3);
  explicit matrix44(const matrix33 &m);

 public:
  // Operators
  vector4		&operator [] (unsigned int i);
  const vector4		&operator [] (unsigned int i) const;
  matrix44		&operator =  (const matrix44 &m);
  matrix44		&operator =  (const matrix33 &m);
  matrix44		&operator += (const matrix44 &m);
  matrix44		&operator -= (const matrix44 &m);
  matrix44		&operator *= (const matrix44 &m);
  matrix44		&operator *= (float f);
  matrix44		&operator /= (float f);
  friend bool		operator == (const matrix44 &a, const matrix44 &b);
  friend bool		operator != (const matrix44 &a, const matrix44 &b);
  friend matrix44	operator + (const matrix44 &a, const matrix44 &b);
  friend matrix44	operator - (const matrix44 &a, const matrix44 &b);
  friend matrix44	operator * (const matrix44 &a, const matrix44 &b);
  friend vector3 	operator * (const matrix44 &m, const vector3 &v);
  friend vector3 	operator * (const vector3 &v, const matrix44 &m);
  friend vector4 	operator * (const matrix44 &m, const vector4 &v);
  friend vector4 	operator * (const vector4 &v, const matrix44 &m);
  friend matrix44	operator * (const matrix44 &m, float f);
  friend matrix44	operator * (float f, const matrix44 &m);
  friend matrix44	operator / (const matrix44 &m, float f);

  //operator float*() {return (float*)col[0]; };

 public:
  // Methods
  matrix44		&identity();
  matrix44		&transpose();
  matrix44		&invert();

  // Debug
  void			fprint(FILE* file, char* str) const;
};

matrix44	IdentityMatrix44();
matrix44	TransposeMatrix44(const matrix44 &m);
matrix44	InvertMatrix44(const matrix44 &m);
matrix44	RotateRadMatrix44(char axis, float rad);
matrix44	RotateRadMatrix44(const vector3 &axis, float rad);
matrix44	TranslateMatrix44(float x, float y, float z);
matrix44	ScaleMatrix44(float x, float y, float z, float w = 1.0);
matrix44	LookAtMatrix44(const vector3 &camPos, const vector3 &camUp, 
			    const vector3 &target );
matrix44	FrustumMatrix44(float l, float r, float b, float t, 
				float n, float f);
matrix44	PerspectiveMatrix44(float fovY, float aspect, 
				float n, float f);
matrix44	OrthoMatrix44(float l, float r, float b, float t, 
			    float n, float f);
matrix44	OrthoNormalMatrix44(const vector3 &xdir, 
				const vector3 &ydir, const vector3 &zdir);

#endif
