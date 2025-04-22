
#include <Wt/WString.h>
#include <Wt/WObject.h>

#include "ClientFolder.h"
#include "Util.h"

//#define DEBUG_TRACE

std::string Wtx::ClientFolder::s_rootPath  = "approot/clients";
std::string Wtx::ClientFolder::s_idPrefix  = " ~ C";
int         Wtx::ClientFolder::s_idLength  = 6;
char        Wtx::ClientFolder::s_idPadding = '0';
std::string Wtx::ClientFolder::s_idSuffix  = "";

Wtx::ClientFolder::ClientFolder()
: Wt::WObject()
{
#ifdef DEBUG_TRACE
  std::cout << __FILE__ << ":" << __LINE__
    << std::endl;
#endif

  m_isValid = false;
}

Wtx::ClientFolder::ClientFolder
(
 int uid,
 const std::string & key,
 const std::string & name
)
: Wt::WObject(),
  m_uid( Wtx::itos(uid) ),
  m_key( key ),
  m_name( name )
{
#ifdef DEBUG_TRACE
  std::cout << __FILE__ << ":" << __LINE__
    << " uid:" << m_uid
    << " key:" << m_key
    << " name:" << m_name
    << std::endl;
#endif

  m_isValid = true;
}

Wtx::ClientFolder::ClientFolder
(
 const std::string & uid,
 const std::string & key,
 const std::string & name
)
: Wt::WObject(),
  m_uid( uid ),
  m_key( key ),
  m_name( name )
{
#ifdef DEBUG_TRACE
  std::cout << __FILE__ << ":" << __LINE__
    << " uid:" << m_uid
    << " key:" << m_key
    << " name:" << m_name
    << std::endl;
#endif

  m_isValid = true;
}

Wtx::ClientFolder::ClientFolder( const ClientFolder & copy )
: Wt::WObject(),
  m_isValid( copy.m_isValid ),
  m_uid( copy.m_uid ),
  m_key( copy.m_key ),
  m_name( copy.m_name )
{
#ifdef DEBUG_TRACE
  std::cout << __FILE__ << ":" << __LINE__
    << " uid:" << m_uid
    << " key:" << m_key
    << " name:" << m_name
    << std::endl;
#endif

}

void Wtx::ClientFolder::setup
(
  const std::string & rootPath,
  const std::string & idPrefix,
  int idLength,
  char idPadding,
  const std::string & idSuffix
)
{
  s_rootPath  = rootPath;
  s_idPrefix  = idPrefix;
  s_idLength  = idLength;
  s_idPadding = idPadding;
  s_idSuffix  = idSuffix;

#ifdef DEBUG_TRACE
  std::cout << __FILE__ << ":" << __LINE__
    << " rootPath:" << s_rootPath
    << " idPrefix:" << s_idPrefix
    << " idLength:" << s_idLength
    << " idPadding:" << s_idPadding
    << " idSuffix:" << s_idSuffix
    << std::endl;
#endif

}

std::string Wtx::ClientFolder::folder( const std::string & base, const std::string & sub )
{
  auto s = sub;
  if( s != "" )
      s = "/" + s;

  return
    Wt::WString("{1}{2}")
    .arg( base )
    .arg( s )
    .toUTF8()
    ;
}

std::string & Wtx::ClientFolder::rootPath()
{
#ifdef DEBUG_TRACE
  std::cout << __FILE__ << ":" << __LINE__
    << " rootPath:" << s_rootPath
    << std::endl;
#endif

  return s_rootPath;
}

std::string & Wtx::ClientFolder::idPrefix()
{
#ifdef DEBUG_TRACE
  std::cout << __FILE__ << ":" << __LINE__
    << " idPrefix:" << s_idPrefix
    << std::endl;
#endif

  return s_idPrefix;
}

int Wtx::ClientFolder::idLength()
{
#ifdef DEBUG_TRACE
  std::cout << __FILE__ << ":" << __LINE__
    << " idLength:" << s_idLength
    << std::endl;
#endif

  return s_idLength;
}

char Wtx::ClientFolder::idPadding()
{
#ifdef DEBUG_TRACE
  std::cout << __FILE__ << ":" << __LINE__
    << " idPadding:" << s_idPadding
    << std::endl;
#endif

  return s_idPadding;
}

std::string & Wtx::ClientFolder::idSuffix()
{
#ifdef DEBUG_TRACE
  std::cout << __FILE__ << ":" << __LINE__
    << " idSuffix:" << s_idSuffix
    << std::endl;
#endif

  return s_idSuffix;
}


bool Wtx::ClientFolder::isValid() const
{
#ifdef DEBUG_TRACE
  std::cout << __FILE__ << ":" << __LINE__
    << " isValid:" << m_isValid
    << std::endl;
#endif

  return m_isValid;
}

const std::string & Wtx::ClientFolder::uid() const
{
#ifdef DEBUG_TRACE
  std::cout << __FILE__ << ":" << __LINE__
    << " uid:" << m_uid
    << std::endl;
#endif

  return m_uid;
}

const std::string & Wtx::ClientFolder::key() const
{
#ifdef DEBUG_TRACE
  std::cout << __FILE__ << ":" << __LINE__
    << " key:" << m_key
    << std::endl;
#endif

  return m_key;
}

const std::string & Wtx::ClientFolder::name() const
{
#ifdef DEBUG_TRACE
  std::cout << __FILE__ << ":" << __LINE__
    << " name:" << m_name
    << std::endl;
#endif

  return m_name;
}

std::string Wtx::ClientFolder::fileParent( const std::string & subFolder ) const
{
#ifdef DEBUG_TRACE
  std::cout << __FILE__ << ":" << __LINE__
    << " fileParent:" << Wt::WString("{1}/{2}")
    .arg( fileRoot() )
    .arg( fileChar() )
    .toUTF8()
    << std::endl;
#endif

  return
    folder
    (
      Wt::WString("{1}/{2}")
      .arg( fileRoot() )
      .arg( fileChar() )
      .toUTF8(),
      subFolder
    );

}

std::string Wtx::ClientFolder::filePath( const std::string & subFolder ) const
{
#ifdef DEBUG_TRACE
  std::cout << __FILE__ << ":" << __LINE__
    << " filePath:" << Wt::WString("{1}/{2}")
    .arg( fileChar    () )
    .arg( fileFolder     () )
    .toUTF8()
    << std::endl;
#endif

  return
    folder
    (
      Wt::WString("{1}/{2}")
      .arg( fileChar    () )
      .arg( fileFolder  () )
      .toUTF8(),
      subFolder
    );

}

std::string Wtx::ClientFolder::fileFolder( const std::string & subFolder ) const
{
#ifdef DEBUG_TRACE
  std::cout << __FILE__ << ":" << __LINE__
    << " fileFolder:" << Wt::WString("{1} ({2}){3}")
    .arg( fileKey  () )
    .arg( fileName () )
    .arg( fileCode ( subFolder ) )
    .toUTF8()
    << std::endl;
#endif

  return
    folder
    (
      Wt::WString("{1} ({2}){3}")
      .arg( fileKey  () )
      .arg( fileName () )
      .arg( fileCode () )
      .toUTF8(),
      subFolder
    );

}

std::string Wtx::ClientFolder::fileAbsolutePath( const std::string & subFolder ) const
{
#ifdef DEBUG_TRACE
  std::cout << __FILE__ << ":" << __LINE__
    << " fileAbsolutePath:" << Wt::WString("{1}/{2}")
    .arg( fileRoot() )
    .arg( filePath( subFolder ) )
    .toUTF8()
    << std::endl;
#endif

  return
    Wt::WString("{1}/{2}")
    .arg( fileRoot() )
    .arg( filePath( subFolder ) )
    .toUTF8()
    ;

}

std::string Wtx::ClientFolder::fileId() const
{
#ifdef DEBUG_TRACE
  std::cout << __FILE__ << ":" << __LINE__
    << " fileId:" << Wt::WString("{1}")
    .arg( Wtx::prepend( uid(), idLength(), idPadding() ) )
    .toUTF8()
    << std::endl;
#endif

  return
    Wt::WString("{1}")
    .arg( Wtx::prepend( uid(), idLength() ) )
    .toUTF8()
    ;

}

std::string Wtx::ClientFolder::fileCode() const
{
#ifdef DEBUG_TRACE
  std::cout << __FILE__ << ":" << __LINE__
    << " fileCode:" << Wt::WString("{1}{2}{3}")
    .arg( idPrefix() )
    .arg( fileId() )
    .arg( idSuffix() )
    .toUTF8()
    << std::endl;
#endif

  return
    Wt::WString("{1}{2}{3}")
    .arg( idPrefix() )
    .arg( fileId() )
    .arg( idSuffix() )
    .toUTF8()
    ;

}

std::string Wtx::ClientFolder::fileName() const
{
#ifdef DEBUG_TRACE
  std::cout << __FILE__ << ":" << __LINE__
    << " fileName:" << Wtx::makeFileName( Wtx::ucase( name() ) )
    << std::endl;
#endif

  return Wtx::makeFileName( Wtx::ucase( name() ) );
}

std::string Wtx::ClientFolder::fileKey() const
{
#ifdef DEBUG_TRACE
  std::cout << __FILE__ << ":" << __LINE__
    << " fileKey:" << Wtx::makeFileName( Wtx::ucase( key() ) )
    << std::endl;
#endif

  return Wtx::makeFileName( Wtx::ucase( key() ) );
}

std::string Wtx::ClientFolder::fileChar() const
{
#ifdef DEBUG_TRACE
  std::cout << __FILE__ << ":" << __LINE__
    << " fileChar:" << Wtx::makeFileName( Wtx::ucase( key() ) ).substr(0,1)
    << std::endl;
#endif

  return Wtx::makeFileName( Wtx::ucase( key() ) ).substr(0,1);
}

std::string Wtx::ClientFolder::fileRoot( const std::string & subFolder ) const
{
#ifdef DEBUG_TRACE
  std::cout << __FILE__ << ":" << __LINE__
    << " fileRoot:" << rootPath()
    << std::endl;
#endif

  return folder( rootPath(), subFolder );
}

