#pragma once

// This will load the definition for common Particle variable types
#include "Particle.h"

/*
  Log handler that write to Blynk Terminal
*/
class BlynkLog : public LogHandler
{
  Stream *m_pTerminal;
  int m_semaphor;

public:
  explicit BlynkLog(Stream *pt,
                          LogLevel level = LOG_LEVEL_INFO, 
                          const LogCategoryFilters &filters = {
  });
  virtual ~BlynkLog();

private:

  const char* extractFileName(const char *s);
  const char* extractFuncName(const char *s, size_t *size);
  void log(const char *category, String message);

protected:
    virtual void logMessage(const char *msg, LogLevel level, const char *category, const LogAttributes &attr) override;
};