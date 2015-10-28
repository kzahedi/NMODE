#ifndef MACROS
#define MACROS

#include <string>
#include <algorithm> 
#include <functional> 
#include <cctype>
#include <locale>
#include <math.h>

#define FORC(t, i, c)       for(t::iterator i = c.begin(); i != c.end(); i++)
#define FORCC(t, i, c)      for(t::const_iterator i = c.begin(); i != c.end(); i++)
#define FORP(t, i, c)       for(t::iterator i = c->begin(); i != c->end(); i++)
#define FORF(t, i, c, b, e) for(t::iterator i = (c)->b; i != (c)->e; i++)
#define FORI(s, e, i)       for(int i = s; i < (int)e; i++)

#define SIGN(a)             ((a<0.0)?-1.0:1.0)

#define DIST(a, b)          sqrt((a.x - b.x) * (a.x - b.x) + \
                                 (a.y - b.y) * (a.y - b.y) + \
                                 (a.z - b.z) * (a.z - b.z))

#define RAD_TO_DEG(x)       (( (double)(x) / (M_PI))  * 180.0)
#define DEG_TO_RAD(x)       (( (double)(x) / (180.0)) * M_PI)

#define MIN(a,b)            ((a<b)?a:b)
#define MAX(a,b)            ((a>b)?a:b)

// trim from start
static inline std::string &ltrim(std::string &s) {
        s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
        return s;
}

// trim from end
static inline std::string &rtrim(std::string &s) {
        s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
        return s;
}

// trim from both ends
static inline std::string &trim(std::string &s) {
        return ltrim(rtrim(s));
}

#endif // MACROS
