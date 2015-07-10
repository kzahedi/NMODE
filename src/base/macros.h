#ifndef MACROS
#define MACROS

#define FORC(t, i, c)       for(t::iterator i = c.begin(); i != c.end(); i++)
#define FORP(t, i, c)       for(t::iterator i = c->begin(); i != c->end(); i++)
#define FORF(t, i, c, b, e) for(t::iterator i = (c)b; i != (c)e; i++)

#endif // MACROS
