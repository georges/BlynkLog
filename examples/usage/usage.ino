// Example usage for BlynkLog library.

#include "BlynkLog.h"
#include <blynk.h>

// Initialize a Blynk terminal where the log will go
WidgetTerminal logs(V0);

// Type cast to a Stream class because blynk.h header can only be included once
// in the main file so WidgetTerminal class are not available in other classes
BlynkLog blynkLog((Stream*)&logs);

void setup() 
{
    // Format time stamp that's automatically added to the log
    Time.setFormat("%m/%d %H:%M");

    Blynk.begin("<YOUR-AUTH-KEY>");
    blynkLog.info("Starting up...");
}

void loop() 
{
    Blynk.run();
    logs.flush();
}
