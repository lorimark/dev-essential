
#ifndef __ATTACHMENT_H___
#define __ATTACHMENT_H___

namespace Wtx {
  namespace Eml {

class Attachment
{
public:
  std::string fileName;

  std::string contentDescription;

  std::string spoolFileName;

  Attachment( const std::string & aFileName, const std::string & aContentDescription, const std::string & aSpoolFileName )
  : fileName(aFileName),
    contentDescription(aContentDescription),
    spoolFileName(aSpoolFileName)
  {
  }
};


  } // endnamespace Eml {
} // endnamespace Wtx {

#endif // ATTACHMENT_H_


