# BlynkLog

A Particle library for logging to [Blynk terminal wiget](http://docs.blynk.cc/#widgets-displays-terminal).

## Usage

Create a logger and pass it an instance of a terminal widget.

```
#include <blynk.h>
#include "BlynkLog.h"
WidgetTerminal terminal(V0);
BlynkLog blynkLog((Stream*)&terminal);

void loop() {
  blynkLog.info("Hello world");
}
```

See the [examples](examples) folder for more details.

## Logging format

The library automatically adds timestamp, log level and category. To configure the timestamp format, use 

```
Time.setFormat("%m/%d %H:%M");
```

For brievety, log level is abreviated to first letter. For example 

```
02/14 14:23 I: app This is an info level log line
```