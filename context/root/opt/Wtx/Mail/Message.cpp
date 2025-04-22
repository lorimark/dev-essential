
#include "Message.h"

void Wtx::Mail::Message::addAttachment
(
 const std::string & mimeType,
 const std::string & fileName,
 std::istream *data
)
{
  Wt::Mail::Message::addAttachment( mimeType, fileName, data );

  m_attachments.push_back( { mimeType, fileName, data } );
}

const std::vector< Wtx::Mail::Message::Attachment > & Wtx::Mail::Message::attachments() const
{
  return m_attachments;
}


