#include "BlynkLog.h"

BlynkLog::BlynkLog( Stream *pt,
                    LogLevel level,
                    const LogCategoryFilters &filters) : LogHandler(level, filters), m_pTerminal(pt), m_semaphor(0)
{    
    LogManager::instance()->addHandler(this);
}

void BlynkLog::log(const char *category, String message) 
{
    // Prevent recursion in case Blynk terminal widget is logging something too
    if (!m_semaphor)
    {
        m_semaphor++;
        m_pTerminal->println(message);
        m_semaphor--;
    }
}

BlynkLog::~BlynkLog() 
{
    LogManager::instance()->removeHandler(this);
}

// The floowing methods are taken from Particle FW, specifically spark::StreamLogHandler.
// See https://github.com/spark/firmware/blob/develop/wiring/src/spark_wiring_logging.cpp
const char* BlynkLog::extractFileName(const char *s) {
    const char *s1 = strrchr(s, '/');
    if (s1) {
        return s1 + 1;
    }
    return s;
}

const char* BlynkLog::extractFuncName(const char *s, size_t *size) {
    const char *s1 = s;
    for (; *s; ++s) {
        if (*s == ' ') {
            s1 = s + 1;                                                                                                                         // Skip return type
        } else if (*s == '(') {
            break;                                                                                                                         // Skip argument types
        }
    }
    *size = s - s1;
    return s1;
}

void BlynkLog::logMessage(const char *msg, LogLevel level, const char *category, const LogAttributes &attr) {
    // Use default time format
    String s = Time.format(Time.now());

    // Level
    s.concat(" ");
    s.concat(levelName(level)[0]);
    s.concat(": ");

    // Source file
    if (attr.has_file) {
        s = extractFileName(attr.file);                                                                                 // Strip directory path
        s.concat(s);                                                                                 // File name
        if (attr.has_line) {
            s.concat(":");
            s.concat(String(attr.line));                                                                                                                         // Line number
        }
        if (attr.has_function) {
            s.concat(", ");
        } else {
            s.concat(": ");
        }
    }

    // Function name
    if (attr.has_function) {
        size_t n = 0;
        s = extractFuncName(attr.function, &n);                                                                                 // Strip argument and return types
        s.concat(s);
        s.concat("(): ");
    }

    if (category) 
    {
        s.concat(category);
        s.concat(" ");
    }

    // Message
    if (msg) {
        s.concat(msg);
    }

    // Additional attributes
    if (attr.has_code || attr.has_details) {
        s.concat(" [");
        // Code
        if (attr.has_code) {
            s.concat(String::format("code = %p", (intptr_t)attr.code));
        }
        // Details
        if (attr.has_details) {
            if (attr.has_code) {
                s.concat(", ");
            }
            s.concat("details = ");
            s.concat(attr.details);
        }
        s.concat(']');
    }

    log(category, s);
}