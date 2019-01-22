#include <Adafruit_CircuitPlayground.h>

// threshold to detect a capacitive touch (0-999)
int CAP_THRESHOLD = 50;

// debounce timing (ms)
int const DEBOUNCE = 250;

// pin definitions
uint8_t const SCROLL_FWD_PIN = 0;
uint8_t const SCROLL_BWD_PIN = 6;
uint8_t const PULSE_MODE_PIN = 9;

uint8_t const pads[] = {0,6,9};
uint8_t const num_pads = sizeof(pads)/sizeof(uint8_t);

// colors
const uint32_t pixel_colors[] = {
  0x7F0000, // red
  0x6F3F00, // orange
  0x5F5F00, // yellow
  0x007F00, // green
  0x00007F, // blue
  0x3F006F, // indigo
  0x4F2F4F  // violet
};
uint8_t const num_colors = sizeof(pixel_colors)/sizeof(uint32_t);
int8_t current_color = 0;
                            
bool capacitive_button(uint8_t pad) {
  if (CircuitPlayground.readCap(pad) > CAP_THRESHOLD) {
    return true;
  } else {
    return false;
  }
}

void change_color(int8_t step) {
  current_color += step;
  if (current_color >= num_colors) {
    current_color = 0;
  } else if (current_color < 0) {
    current_color = num_colors - 1;
  }
  for (int p = 0; p < 10; ++p) {
    CircuitPlayground.setPixelColor(p,pixel_colors[current_color]);
  }
}

void togglePulseMode() {
  // nop
}

void setup() {
  CircuitPlayground.begin();
}

void loop() {
  for (int i = 0; i < num_pads; ++i) {
    if (capacitive_button(pads[i])) {
      switch(pads[i]) {
      case SCROLL_FWD_PIN:
        change_color(1);
        break;  
      case SCROLL_BWD_PIN:
        change_color(-1);
        break;  
      case PULSE_MODE_PIN:
        togglePulseMode();
        break;
      }
      delay(DEBOUNCE);
    }
  }

}
