#include <nmode/Com.h>

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

#if !defined(_MSC_VER) && !defined(_WIN32)
#  include <sys/time.h>
#endif // _MSC_VER

#include <sstream>
#include <iostream>

// Just required to put the bytes together again.
// It is not a real buffer size
#define __BUFFER_SIZE    8192

#define __DOUBLE_VALUE   'd'
#define __INTEGER_VALUE  'i'
#define __STRING_VALUE   's'

#define __DOUBLE_VECTOR  'D'
#define __INTEGER_VECTOR 'I'

# ifndef MSG_WAITALL
#  define MSG_WAITALL 0x0008
# endif

# define MIN(a,b) ((a<b)?a:b)


using namespace std;

inline void __printBytes(char c)
{
  for(int i = 0; i < 8; i++)
  {
    if(0x01 & (c >> i))
    {
      std::cout << "1";
    }
    else
    {
      std::cout << "0";
    }
  }
  std::cout << std::endl;
}

Com::Com()
{
  _sock           = -1;
  _mysock         = -1;
  _throwException = false;
}

Com::~Com()
{
  close();
}

/** \brief Function for the client
 *
 *  Closes sockets, if they are still open.
 **/
void Com::connect(const std::string host, const int port)
{
  struct hostent *h;
  struct in_addr **addr_list;
  int flag = 1;

  if ((_sock = socket(AF_INET, SOCK_STREAM, 0)) < 0 )
  {
    cerr << "Com::connect: ECHOCLNT: Error creating listening socket." << endl;
    exit(-1);
  }

  if ((h = gethostbyname(host.c_str())) == NULL)  // get the host info
  {
    cerr << "Com::connect: gethostbyname, cannot resolve hostname" << endl;
    exit(-1);
  }

  addr_list = (struct in_addr **)h->h_addr_list;

#ifdef __APPLE__
  if (inet_aton(inet_ntoa(*addr_list[0]), &_peer.sin_addr) <= 0)
  {
    cerr << "Com::connect: invalid address given." << endl;
    exit(-1);
  }
#else
  // to do
#endif // __APPLE__

  memset(&_peer, 0, sizeof(_peer));
  _peer.sin_family      = AF_INET;
  _peer.sin_port        = htons(port);

  if ((_sock = socket(AF_INET, SOCK_STREAM, 0)) < 0 )
  {
    cerr << "Com::connect: Error creating listening socket." << endl;
    exit(-1);
  }

  if ( ::connect(_sock, (struct sockaddr *) &_peer, sizeof(_peer) ) < 0 )
  {
    cerr << "Com::connect: Error calling connect()" << endl;
    exit(-1);
  }

  if(setsockopt(_sock, IPPROTO_TCP, TCP_NODELAY, (char *) &flag, sizeof(int)) < 0)
  {
    cerr << "Com::connect: Error setting setsockopt." << endl;
    exit(-1);
  }
}


int Com::accept(const int port)
{
  int flag = 1;
  int p    = port - 1;
  memset(&_peer, 0, sizeof(_peer));
  _peer.sin_family      = AF_INET;
  _peer.sin_addr.s_addr = htonl(INADDR_ANY);

  if ((_mysock = socket(AF_INET, SOCK_STREAM, 0)) < 0 )
  {
    cerr << "Com::accept ECHOSERV: Error creating listening socket." << endl;
    exit(-1);
  }

#if defined(_MSC_VER) || defined(_WIN32)
  cout << "Com not yet implemented in Windows version" << endl;
  exit(-1);
#else
  do { _peer.sin_port = htons(++p); }
  while(bind(_mysock, (struct sockaddr *) &_peer, sizeof(_peer)) < 0 );
#endif

  cout << "  --> port " << p << " opened" << endl;

  if ( listen(_mysock, 1) < 0 ) // only one connection on this port
  {
    cerr << "Com::accept ECHOSERV: Error calling listen()" << endl;
    exit(-1);
  }

  if ( (_sock = ::accept(_mysock, NULL, NULL) ) < 0 ) // ::accept != Com::accept
  {
    cerr << "Com::accept ECHOSERV: Error calling accept()" << endl;
    exit(-1);
  }

  if (setsockopt(_sock, IPPROTO_TCP, TCP_NODELAY, (char *) &flag, sizeof(int)) < 0)
  {
    cerr << "Com::connect: Error setting setsockopt on my socket." << endl;
    exit(-1);
  }

  if(setsockopt(_mysock, IPPROTO_TCP, TCP_NODELAY, (char *) &flag, sizeof(int)) < 0)
  {
    cerr << "Com::connect: Error setting setsockopt on client socket." << endl;
    exit(-1);
  }
  return p;
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
// BUFFER
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// BUFFER - SEND
////////////////////////////////////////////////////////////////////////////////

const Com& Com::operator<<(const ComBuffer &b) const
{
  char *buf = new char[b.size() + 1];
  buf[0] = b.label;

  for(unsigned int i = 0; i < b.size(); i++)
  {
    buf[1 + i] = b[i];
  }

  send(_sock, buf, b.size() + 1, 0);

  delete[] buf;

  return *this;
}

////////////////////////////////////////////////////////////////////////////////
// BUFFER - RECEIVE
////////////////////////////////////////////////////////////////////////////////

const Com& Com::operator>>(ComBuffer &b) const
{
  b.resize(0);
  char *buf       = new char[__BUFFER_SIZE];
  char *type      = new char[1];
  char *sizeBytes = new char[4];
  int r           = 0;
  int size        = -1;
  int read        = 0;
  int toread      = 0;

  recv(_sock, type, 1, MSG_WAITALL);
  ((Com*)this)->__check(b.label, type[0]);

  switch(type[0])
  {
    case __STRING_VALUE:
      recv(_sock, sizeBytes, 4, MSG_WAITALL);
      for(int i = 0; i < 4; i++) b.push_back(sizeBytes[i]);
      ((Com*)this)->__coneverToInt(sizeBytes, &size);
      break;
    case __INTEGER_VECTOR:
      recv(_sock, sizeBytes, 4, MSG_WAITALL);
      for(int i = 0; i < 4; i++) b.push_back(sizeBytes[i]);
      ((Com*)this)->__coneverToInt(sizeBytes, &size);
      size *= sizeof(int);
      break;
    case __DOUBLE_VECTOR:
      recv(_sock, sizeBytes, 4, MSG_WAITALL);
      for(int i = 0; i < 4; i++) b.push_back(sizeBytes[i]);
      ((Com*)this)->__coneverToInt(sizeBytes, &size);
      size *= sizeof(double);
      break;
    case __INTEGER_VALUE:
      size = sizeof(int);
      break;
    case __DOUBLE_VALUE:
      size = sizeof(double);
      break;
  }

  read = 0;
  while(read < size)
  {
    toread = MIN(size - read, __BUFFER_SIZE);
    r = recv(_sock, buf, toread, MSG_WAITALL);
    read += r;
    for(int i = 0; i < r; i++)
    {
      b.push_back(buf[i]);
    }
  }

  delete[] buf;
  delete[] type;
  delete[] sizeBytes;

  return *this;
}



////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
// DOUBLE
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// DOUBLE - SEND
////////////////////////////////////////////////////////////////////////////////

const Com& Com::operator<<(const double &d) const
{
  ComBuffer b;
  b.resize(0);
  b.label = __DOUBLE_VALUE;
  ((Com*)this)->__writeDouble(&b, d);
  *this << b;
  return *this;
}

////////////////////////////////////////////////////////////////////////////////
// DOUBLE - RECEIVE
////////////////////////////////////////////////////////////////////////////////

const Com& Com::operator>>(double& d) const
{
  d = 0;
  int size = sizeof(double);
  ComBuffer b;
  b.resize(size);
  b.label = __DOUBLE_VALUE;
  *this >> b;
  ((Com*)this)->__readDouble(&d, b, 0);
  return *this;
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
// INTEGER
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// INTEGER - SEND
////////////////////////////////////////////////////////////////////////////////

const Com& Com::operator<<(const int &i) const
{
  ComBuffer b;
  b.label = __INTEGER_VALUE;
  b.resize(0);
  ((Com*)this)->__writeInteger(&b, i);
  *this << b;
  return *this;
}

////////////////////////////////////////////////////////////////////////////////
// INTEGER - RECEIVE
////////////////////////////////////////////////////////////////////////////////

const Com& Com::operator>>(int& i) const
{
  i = 0;
  int size = sizeof(int);
  ComBuffer b;
  b.label = __INTEGER_VALUE;
  b.resize(size);
  *this >> b;
  ((Com*)this)->__readInteger(&i, b, 0);
  return *this;
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
// STRING
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// STRING - SEND
////////////////////////////////////////////////////////////////////////////////

const Com& Com::operator<<(const std::string& s) const
{
  ComBuffer b;
  b.resize(0);
  b.label = __STRING_VALUE;
  ((Com*)this)->__writeInteger(&b, (int)s.length());
  for(unsigned int i = 0; i < s.length(); i++)
  {
    b.push_back(s[i]);
  }
  *this << b;
  return *this;
}

////////////////////////////////////////////////////////////////////////////////
// STRING - RECEIVE
////////////////////////////////////////////////////////////////////////////////

const Com& Com::operator>>(std::string& s) const
{
  s = "";
  ComBuffer b;
  b.resize(0);
  b.label = __STRING_VALUE;
  *this >> b;

  stringstream oss;
  int size = 0;
  ((Com*)this)->__readInteger(&size, b, 0);
  for(unsigned int i = sizeof(int); i < b.size(); i++)
  {
    oss << b[i];
  }
  s = oss.str();
  return *this;
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
// VECTOR OF INTEGERS
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// VECTOR OF INTEGERS - SEND
////////////////////////////////////////////////////////////////////////////////

const Com& Com::operator<<(const std::vector<int>& v) const
{
  ComBuffer b;
  b.label = __INTEGER_VECTOR;
  b.resize(0);
  int s = (int)v.size();
  ((Com*)this)->__writeInteger(&b, s);

  for(std::vector<int>::const_iterator i = v.begin(); i != v.end(); i++)
  {
    int value = *i;
    ((Com*)this)->__writeInteger(&b, value);
  }
  *this << b;
  return *this;
}

////////////////////////////////////////////////////////////////////////////////
// VECTOR OF INTEGERS - RECEIVE
////////////////////////////////////////////////////////////////////////////////

const Com& Com::operator>>(std::vector<int>& v) const
{
  v.clear();
  ComBuffer b;
  b.label = __INTEGER_VECTOR;
  b.resize(0);
  int vectorSize = 0;

  *this >> b;

  ((Com*)this)->__readInteger(&vectorSize, b, 0);

  for(int i = 0; i < vectorSize; i++)
  {
    int value = 0;
    ((Com*)this)->__readInteger(&value, b, (i+1) * sizeof(int));
    v.push_back(value);
  }
  return *this;
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
// VECTOR OF DOUBLES
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// VECTOR OF DOUBLES - SEND
////////////////////////////////////////////////////////////////////////////////
const Com& Com::operator<<(const std::vector<double>& v) const
{
  ComBuffer b;
  b.label = __DOUBLE_VECTOR;
  b.resize(0);
  int s = (int)v.size();

  ((Com*)this)->__writeInteger(&b, s);

  for(std::vector<double>::const_iterator i = v.begin(); i != v.end(); i++)
  {
    double value = *i;
    ((Com*)this)->__writeDouble(&b, value);
  }
  *this << b;
  return *this;
}


////////////////////////////////////////////////////////////////////////////////
// VECTOR OF DOUBLES - RECEIVE
////////////////////////////////////////////////////////////////////////////////

const Com& Com::operator>>(std::vector<double>& v) const
{
  v.clear();
  ComBuffer b;
  b.label = __DOUBLE_VECTOR;
  b.resize(0);

  *this >> b;

  int vectorSize = 0;

  ((Com*)this)->__readInteger(&vectorSize, b, 0);

  for(int i = 0; i < vectorSize; i++)
  {
    double value = 0;
    ((Com*)this)->__readDouble(&value, b, i * sizeof(double) + sizeof(int));
    v.push_back(value);
  }
  return *this;
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
// ComBuffer access functions
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

void Com::__writeDouble(ComBuffer *b, double d)
{
  char *x_ptr=reinterpret_cast<char*>(&d);
  for(unsigned int count = 0;count < sizeof(double); count++)
  {
    b->push_back(*(x_ptr+count));
  }
}

void Com::__readDouble(double *d, ComBuffer b, int startIndex)
{
  *d = 0;
  char *x_ptr=reinterpret_cast<char *>(d);
  for(int count = sizeof(double)-1; count >= 0; count--)
  {
    *(x_ptr+count)|=b[startIndex + count];
  }
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

void Com::__writeInteger(ComBuffer *b, int i)
{
  char *x_ptr=reinterpret_cast<char*>(&i);
  for(unsigned int count = 0; count < sizeof(int); count++)
  {
    b->push_back(*(x_ptr+count));
  }
}

void Com::__readInteger(int *i, ComBuffer b, int startIndex)
{
  *i = 0;
  char *x_ptr=reinterpret_cast<char *>(i);
  for(int count = sizeof(int)-1; count >= 0; count--)
  {
    *(x_ptr+count)|=b[startIndex + count];
  }
}

void Com::__coneverToInt(char *c, int *i)
{
  *i = 0;
  char *x_ptr=reinterpret_cast<char *>(i);
  for(int count = sizeof(int)-1; count >= 0; count--)
  {
    *(x_ptr+count)|=c[count];
  }
}

void Com::__check(const char a, const char b)
{
  if(a == b) return; // everything ok
  stringstream oss;
  oss << "Com communication error. Awaited ";
  switch(a)
  {
    case __DOUBLE_VALUE:
      oss << "<double value> '"    << __DOUBLE_VALUE   << "'";
      break;
    case __INTEGER_VALUE:
      oss << "<integer value> '"  << __INTEGER_VALUE  << "'";
      break;
    case __STRING_VALUE:
      oss << "<string value> '"   << __STRING_VALUE   << "'";
      break;
    case __DOUBLE_VECTOR:
      oss << "<double vector> '"   << __DOUBLE_VECTOR  << "'";
      break;
    case __INTEGER_VECTOR:
      oss << "<integer vector> '" << __INTEGER_VECTOR << "'";
      break;
    default:
      oss << "<unknown \"" << (int)b << "\">";
      break;
  }
  oss << " but received ";
  switch(b)
  {
    case __DOUBLE_VALUE:
      oss << "<double value> '"    << __DOUBLE_VALUE   << "'";
      break;
    case __INTEGER_VALUE:
      oss << "<integer value> '"  << __INTEGER_VALUE  << "'";
      break;
    case __STRING_VALUE:
      oss << "<string value> '"   << __STRING_VALUE   << "'";
      break;
    case __DOUBLE_VECTOR:
      oss << "<double vector> '"   << __DOUBLE_VALUE   << "'";
      break;
    case __INTEGER_VECTOR:
      oss << "<integer vector> '" << __INTEGER_VECTOR << "'";
      break;
    default:
      oss << "<unknown \"" << b << "\">";
      break;
  }
  cerr << oss.str() << endl;
  close();
}

void Com::close()
{
  if(_sock != -1)
  {
#ifdef __APPLE__
     ::shutdown(_sock, SHUT_RDWR);
#else
#if defined(_MSC_VER) || defined(_WIN32)
     closesocket(_sock);
#  else
     ::close(_sock);
#  endif
#endif // __APPLE__
  }

  if(_mysock != -1)
  {
#ifdef __APPLE__
     ::shutdown(_sock, SHUT_RDWR);
#else
#if defined(_MSC_VER) || defined(_WIN32)
     closesocket(_sock);
#  else
     ::close(_sock);
#  endif
#endif // __APPLE__
  }

  _sock   = -1;
  _mysock = -1;
}

void Com::throwException(bool te)
{
  _throwException = te;
}
