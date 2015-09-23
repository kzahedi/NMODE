#ifndef MACROS
#define MACROS

#include <string>
#include <algorithm> 
#include <functional> 
#include <cctype>
#include <locale>

#define FORC(t, i, c)       for(t::iterator i = c.begin(); i != c.end(); i++)
#define FORCC(t, i, c)      for(t::const_iterator i = c.begin(); i != c.end(); i++)
#define FORP(t, i, c)       for(t::iterator i = c->begin(); i != c->end(); i++)
#define FORF(t, i, c, b, e) for(t::iterator i = (c)->b; i != (c)->e; i++)

#define SIGN(a) ((a<0.0)?-1.0:1.0)

#define DIST(a, b) sqrt((a.x - b.x) * (a.x - b.x) +\
                        (a.y - b.y) * (a.y - b.y) +\
                        (a.z - b.z) * (a.z - b.z))

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
