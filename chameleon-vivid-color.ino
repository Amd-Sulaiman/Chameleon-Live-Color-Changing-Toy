#include <Wire.h>
#include <Adafruit_TCS34725.h>
#include <Adafruit_NeoPixel.h>

#define LED_PIN 5
#define NUM_LEDS 16

Adafruit_NeoPixel strip(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_614MS, TCS34725_GAIN_16X);

float smooth_r = 128, smooth_g = 128, smooth_b = 128;
float alpha = 0.2;

// Convert RGB → Hue (0–360)
float rgbToHue(float r, float g, float b) {
  r /= 255.0; g /= 255.0; b /= 255.0;
  float mx = max(r, max(g, b));
  float mn = min(r, min(g, b));
  float delta = mx - mn;
  if (delta < 0.001) return -1; // achromatic (grey/white/black)
  float h;
  if      (mx == r) h = fmod((g - b) / delta, 6.0);
  else if (mx == g) h = (b - r) / delta + 2.0;
  else              h = (r - g) / delta + 4.0;
  h *= 60.0;
  if (h < 0) h += 360.0;
  return h;
}

// Pick a vivid display color from hue
void hueToVividRGB(float hue, float saturation, uint8_t &r, uint8_t &g, uint8_t &b) {
  if (hue < 0 || saturation < 0.15) {
    // Achromatic — show white
    r = g = b = 255; return;
  }
  // HSV → RGB with S=1, V=1 (fully vivid)
  float h = hue / 60.0;
  int   i = (int)h;
  float f = h - i;
  float q = 1 - f, t = f;
  switch (i % 6) {
    case 0: r=255; g=t*255; b=0;     break;
    case 1: r=q*255; g=255; b=0;     break;
    case 2: r=0; g=255; b=t*255;     break;
    case 3: r=0; g=q*255; b=255;     break;
    case 4: r=t*255; g=0; b=255;     break;
    case 5: r=255; g=0; b=q*255;     break;
  }
}

void setup() {
  Serial.begin(115200);
  if (!tcs.begin()) { Serial.println("Sensor not found"); while (1); }
  strip.begin(); strip.show();
}

void loop() {
  uint16_t r, g, b, c;
  tcs.getRawData(&r, &g, &b, &c);
  if (c < 30) { delay(50); return; }

  // Normalize channels against total light (removes brightness dependency)
  float total = r + g + b;
  float rn = (r / total) * 255.0;
  float gn = (g / total) * 255.0;
  float bn = (b / total) * 255.0;

  // Smooth
  smooth_r += alpha * (rn - smooth_r);
  smooth_g += alpha * (gn - smooth_g);
  smooth_b += alpha * (bn - smooth_b);

  float hue = rgbToHue(smooth_r, smooth_g, smooth_b);

  // Saturation estimate (how colorful vs grey)
  float mx = max(smooth_r, max(smooth_g, smooth_b));
  float mn = min(smooth_r, min(smooth_g, smooth_b));
  float sat = (mx > 0) ? (mx - mn) / mx : 0;

  uint8_t dr, dg, db;
  hueToVividRGB(hue, sat, dr, dg, db);

  for (int i = 0; i < NUM_LEDS; i++)
    strip.setPixelColor(i, strip.Color(dr, dg, db));
  strip.show();

  Serial.printf("Hue:%.1f Sat:%.2f → R:%d G:%d B:%d\n", hue, sat, dr, dg, db);
  delay(50);
}