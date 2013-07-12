#ifndef WATER_VEC2
#define WATER_VEC2
#include <cmath>

template< class T > class vec2 {
    public :
        //  This constructor is the default constructor and it forbids the use of vec2 on a 
        //  variable other than numeric or that doesn't have a conversion constructor with a numeric parameter
        inline vec2<T>() : x(T(0)), y(T(0)){}
        
        inline vec2<T>( T pX, T pY ) : x(pX), y(pY) {}
        template< class U > inline vec2<T>( const vec2<U>& u ) : x(static_cast< T >(u.x)), y(static_cast< T >(u.y)) {}
        inline ~vec2() {}

        inline void operator=( const vec2<T>& b ) {
            x = b.x;
            y = b.y;
        }

        inline bool operator==( const vec2<T>& b ) {
            return x == b.x && y == b.y;
        }

        inline vec2<T> add( const vec2<T>& b )   const {
            return vec2<T>( x + b.x, y + b.y );
        }
        inline vec2<T> sub( const vec2& b )   const {
            return vec2<T>( x - b.x, y - b.y );
        }
        inline vec2<T> mul( const vec2& b )   const {
            return vec2<T>( x * b.x, y * b.y );
        }
        inline vec2<T> scale( T scale )   const {
            return vec2<T>( x * scale, y * scale );
        }

        inline vec2<T> operator+( const vec2<T>& b ) const {
			return add( b );
        }
        inline vec2<T> operator-( const vec2<T>& b ) const {
            return sub( b );
        }
        inline vec2<T> operator/( const vec2<T>& b ) const {
            return vec2<T>( x / b.x, y / b.y );
        }
        inline vec2<T> operator/( T f )   const {
            return *this / vec2<T>( f, f );
        }
        inline vec2<T> operator*( const vec2<T>& b ) const {
            return mul( b );
        }
        inline vec2<T> operator*( T f ) const {
            return scale( f );
        }

        inline void operator+=( const vec2<T>& b ) {
            x += b.x;
            y += b.y;
        }
        inline void operator-=( const vec2<T>& b ) {
            x -= b.x;
            y -= b.y;
        }
        inline void operator/=( const vec2<T>& b ) {
            x /= b.x;
            y /= b.y;
        }
        inline void operator*=( const vec2<T>& b ) {
            x *= b.x;
            y *= b.y;
        }

        inline void operator*=( T f ) {
            x *= f;
            y *= f;
        }

        inline void operator/=( T f ) {
            x /= f;
            y /= f;
        }

        inline static T len( const vec2<T>& v ) {
            return sqrt( v.x*v.x + v.y*v.y );
        }

        inline static T dot( const vec2<T>& a, const vec2& b ) {
            return a.x * b.x + a.y * b.y;
        }

        inline vec2<T> projection( const vec2<T>& b )    const {
            T dot = vec2<T>::dot( *this, b );
            vec2<T> ret;
            ret.x = ( dot / ( b.x*b.x + b.y*b.y ) ) * b.x;
            ret.y = ( dot / ( b.x*b.x + b.y*b.y ) ) * b.y;
            return ret;
        }

        inline vec2<T> normalRight() {
            return vec2<T>( y, -x );
        }

        inline vec2<T> normalLeft() {
            return vec2<T>( -y, x );
        }

        inline vec2<T> normalized() {
            vec2<T> ret;
            T len = vec2<T>::len( *this );
            ret.x = x / len;
            ret.y = y / len;
            return ret;
        }

        T x,
          y;
};

typedef vec2<float> vec2f;
typedef vec2<int> vec2i;
typedef vec2<unsigned int> vec2ui;
typedef vec2<double> vec2d;


#endif // WATER_VEC2
