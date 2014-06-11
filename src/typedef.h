// <3
#pragma once



#include <math.h>

#define FLOAT_EPSILON 0.0001f

class Vec3
{
private:
    bool IsNearZeroFloat( const float param )
    {
            return (fabs(param) < FLOAT_EPSILON);
    }
 
public:
    float fX, fY, fZ;
   
    Vec3 ()
    {
        this->fX = 0;
        this->fY = 0;
        this->fZ = 0;
    };
   
    Vec3 ( float fX, float fY, float fZ)
    {
        this->fX = fX;
        this->fY = fY;
        this->fZ = fZ;
    }

    float Normalize ( void )
    {
        double t = sqrt(fX*fX + fY*fY + fZ*fZ);
        if ( t > FLOAT_EPSILON )
        {
            double fX2 = fX / t;
            double fY2 = fY / t;
            double fZ2 = fZ / t;
            fX = (float)fX2;
            fY = (float)fY2;
            fZ = (float)fZ2;
        }
        else
            t = 0;
        return static_cast < float > ( t );
    }
 
    float Length ( void ) const
    {
       	return sqrt ( (fX*fX) + (fY*fY) + (fZ*fZ) );
    }

    float DistanceTo( const Vec3 * param ) const
    {
	    return sqrt( pow( param->fX - fX, 2 ) + pow( param->fY - fY, 2 ) + pow( param->fZ - fZ, 2 ) );
	}

    float DotProduct ( const Vec3 * param ) const
    {
        return fX*param->fX + fY*param->fY + fZ*param->fZ;
    }
 
    void CrossProduct ( const Vec3 * param )
    {
        float _fX = fX, _fY = fY, _fZ = fZ;
        fX = _fY * param->fZ - param->fY * _fZ;
        fY = _fZ * param->fX - param->fZ * _fX;
        fZ = _fX * param->fY - param->fX * _fY;
    }

    bool IsNearZero ( void )
    {
        //if(!isfinite(fX) || !isfinite(fY) || !isfinite(fZ))
        //      return 1;
        return (IsNearZeroFloat(fX) && IsNearZeroFloat(fY) && IsNearZeroFloat(fZ));
    }

    void Zero ( void )
    {
        fX = 0.0f;
        fY = 0.0f;
        fZ = 0.0f;
    }

    void ZeroNearZero ( void )
    {
        if ( IsNearZeroFloat(fX) )
                fX = 0.0f;
        if ( IsNearZeroFloat(fY) )
                fY = 0.0f;
        if ( IsNearZeroFloat(fZ) )
                fZ = 0.0f;
    }

    float GetAngleRadians ( void )
    {
        return -atan2(fY, -fX);
    }

    float GetAngleDegrees ( void )
    {
        static float radtodeg = 57.324840764331210191082802547771; // 180/pi
        float ret = (atan2(fY, -fX) * radtodeg) + 270.0f;
        if (ret >= 360.0f) ret -= 360.0f;
        return ret;
    }

    Vec3 operator + ( const Vec3& vecRight ) const
    {
        return Vec3 ( fX + vecRight.fX, fY + vecRight.fY, fZ + vecRight.fZ );
    }
 
    Vec3 operator - ( const Vec3& vecRight ) const
    {
        return Vec3 ( fX - vecRight.fX, fY - vecRight.fY, fZ - vecRight.fZ );
    }
 
    Vec3 operator * ( const Vec3& vecRight ) const
    {
        return Vec3 ( fX * vecRight.fX, fY * vecRight.fY, fZ * vecRight.fZ );
    }
 
    Vec3 operator * ( float fRight ) const
    {
        return Vec3 ( fX * fRight, fY * fRight, fZ * fRight );
    }
 
    Vec3 operator / ( const Vec3& vecRight ) const
    {
        return Vec3 ( fX / vecRight.fX, fY / vecRight.fY, fZ / vecRight.fZ );
    }
 
        Vec3 operator / ( float fRight ) const
        {
                return Vec3 ( fX / fRight, fY / fRight, fZ / fRight );
        }
 
    Vec3 operator - () const
    {
        return Vec3 ( -fX, -fY, -fZ );
    }
 
    void operator += ( float fRight )
    {
        fX += fRight;
        fY += fRight;
        fZ += fRight;
    }
 
    void operator += ( const Vec3& vecRight )
    {
        fX += vecRight.fX;
        fY += vecRight.fY;
        fZ += vecRight.fZ;
    }
 
    void operator -= ( float fRight )
    {
        fX -= fRight;
        fY -= fRight;
        fZ -= fRight;
    }
 
    void operator -= ( const Vec3& vecRight )
    {
        fX -= vecRight.fX;
        fY -= vecRight.fY;
        fZ -= vecRight.fZ;
    }
 
    void operator *= ( float fRight )
    {
        fX *= fRight;
        fY *= fRight;
        fZ *= fRight;
    }
 
    void operator *= ( const Vec3& vecRight )
    {
        fX *= vecRight.fX;
        fY *= vecRight.fY;
        fZ *= vecRight.fZ;
    }
 
    void operator /= ( float fRight )
    {
        fX /= fRight;
        fY /= fRight;
        fZ /= fRight;
    }
 
    void operator /= ( const Vec3& vecRight )
    {
        fX /= vecRight.fX;
        fY /= vecRight.fY;
        fZ /= vecRight.fZ;
    }
 
    bool operator== ( const Vec3& param ) const
    {
        return ( ( fabs ( fX - param.fX ) < FLOAT_EPSILON ) &&
                 ( fabs ( fY - param.fY ) < FLOAT_EPSILON ) &&
                 ( fabs ( fZ - param.fZ ) < FLOAT_EPSILON ) );
    }
 
    bool operator!= ( const Vec3& param ) const
    {
        return ( ( fabs ( fX - param.fX ) >= FLOAT_EPSILON ) ||
                 ( fabs ( fY - param.fY ) >= FLOAT_EPSILON ) ||
                 ( fabs ( fZ - param.fZ ) >= FLOAT_EPSILON ) );
    }
};

typedef unsigned long       DWORD;
typedef int                 BOOL;
typedef unsigned char       BYTE;
typedef unsigned short      WORD;
typedef float               FLOAT;
typedef FLOAT               *PFLOAT;

typedef int PLAYERID;
typedef int VEHICLEID;
typedef int NEWSTATE;
typedef int PICKUPID;