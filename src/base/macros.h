#ifndef MACROS
#define MACROS

#define FORC(t, i, c)       for(t::iterator i = c.begin(); i != c.end(); i++)
#define FORCC(t, i, c)      for(t::const_iterator i = c.begin(); i != c.end(); i++)
#define FORP(t, i, c)       for(t::iterator i = c->begin(); i != c->end(); i++)
#define FORF(t, i, c, b, e) for(t::iterator i = (c)b; i != (c)e; i++)

#define SIGN(a) ((a<0.0)?-1.0:1.0)

#define DIST(a, b) sqrt((a.x - b.x) * (a.x - b.x) +\
                        (a.y - b.y) * (a.y - b.y) +\
                        (a.z - b.z) * (a.z - b.z))

#endif // MACROS
