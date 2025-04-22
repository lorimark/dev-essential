
#include <Wt/WStandardItemModel.h>

#include "ModelProvider.h"

Wtx::Web::Calendar::ModelProvider::ModelProvider
(
  const std::string & name,
  const std::string & dateStart,
  const std::string & dateEnd,
  const std::string & timeStart,
  const std::string & timeEnd,
  const std::string & subject,
  const std::string & body
)
: Wt::WObject(),
  m_name(name)
{
  setMapping
  (
   dateStart,
   dateEnd,
   timeStart,
   timeEnd,
   subject,
   body
  );
}

std::shared_ptr<Wt::WAbstractItemModel> Wtx::Web::Calendar::ModelProvider::getModel( const Wt::WDate & date, const std::vector<std::string> & fieldList )
{
  return std::make_shared<Wt::WStandardItemModel>();
}

const std::string & Wtx::Web::Calendar::ModelProvider::name() const
{
  return m_name;
}

const std::string & Wtx::Web::Calendar::ModelProvider::dateStart() const
{
  return m_dateStart;
}

const std::string & Wtx::Web::Calendar::ModelProvider::dateEnd() const
{
  return m_dateEnd;
}

const std::string & Wtx::Web::Calendar::ModelProvider::timeStart() const
{
  return m_timeStart;
}

const std::string & Wtx::Web::Calendar::ModelProvider::timeEnd() const
{
  return m_timeEnd;
}

const std::string & Wtx::Web::Calendar::ModelProvider::subject() const
{
  return m_subject;
}

const std::string & Wtx::Web::Calendar::ModelProvider::body() const
{
  return m_body;
}

void Wtx::Web::Calendar::ModelProvider::setMapping
(
  const std::string & dateStart,
  const std::string & dateEnd,
  const std::string & timeStart,
  const std::string & timeEnd,
  const std::string & subject,
  const std::string & body
)
{
  m_dateStart = dateStart;
  m_dateEnd   = dateEnd;
  m_timeStart = timeStart;
  m_timeEnd   = timeEnd;
  m_subject   = subject;
  m_body      = body;

}



