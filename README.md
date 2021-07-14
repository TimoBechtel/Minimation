# Minimation

## Table of Contents

- [About](#about)
- [Getting Started](#getting_started)
- [Usage](#usage)
- [Contributing](../CONTRIBUTING.md)

## About

I needed a simple way to run multiple actions "at the same time" in specific intervals for an ESP32.

Enter: Minimation. It is a mini animation framework for microcontrollers.
Think a bit like `setInterval` / `setTimeout` in javascript.

## Usage

### Include header file

```c++
#include "Animation.h"
```

### Create a new Animation

```c++
unsigned int duration = 5000; // in milliseconds
Animation *blink = new Animation(duration);
```

On Arduino, you would create this in a setup function.

### Call the loop function to advance the animation

For Arduino you can run this in the loop function, e.g.:

```c++
void loop() {
  blink->loop();
}
```

Now you can define functions that should run on certain events:

(You can do this wherever in the code, but I recommend not to add callbacks in a loop.)

### Run a function on start

```c++
blink->onStart([]() {
  cout << "Started" << endl;
});
```

### Run a function on an interval

```c++
unsigned int interval = 500; // interval in milliseconds
blink->onInterval(interval, []() {
  cout << "Hello World" << endl;
});
```

Sometimes a callback may be skipped because a loop takes longer than the given interval. If this is not what you want, you can set the `lazy` flag to `false`. Then callbacks are stacked and run in a batch on the next loop.

```c++
blink->onInterval(10, []() {
  cout << "Hello World" << endl;
}, false);
```

### Run a function on every loop

```c++
blink->onLoop([](float progress) {
  cout << progress << endl;
});
```

### Run a function when the animation has finished

```c++
blink->onDone([]() {
  cout << "Stopped" << endl;
});
```

### Make sure to start the animation

You can also use this function to reset the animation.

```c++
blink->start();
```

## Full example

Example with the arduino framework

```c++
#include <Arduino.h>
#include "Animation.h"

Animation *animation;

void setup()
{
  Serial.begin(9600);
  animation = new Animation(5000);
  animation->onStart([]() {
    Serial.println("Started animation");
  });
  animation->onInterval(1000, []() {
    Serial.println("1 second elapsed");
  });
  animation->onDone([]() {
    Serial.println("Animation finished");
    animation->start(); // restart animation
  });
  animation->start();
}

void loop()
{
  animation->loop();
}
```
