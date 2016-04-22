#include <nmode/XSDString.h>

XSDString::XSDString(const char* const toTranscode)
{
  // Call the private transcoding method
  fUnicodeForm = XMLString::transcode(toTranscode);
}

XSDString::~XSDString()
{
  XMLString::release(&fUnicodeForm);
}

const XMLCh* XSDString::unicodeForm() const
{
  return fUnicodeForm;
}

