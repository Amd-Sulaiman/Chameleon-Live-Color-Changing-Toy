# 🦎 Chameleon Color-Changing Toy

**ESP32-C6 Mini + TCS34725 + WS2812**

A compact interactive toy inspired by a chameleon that **detects the color of any surface and reproduces it in real time** using addressable RGB LEDs—housed inside a custom 3D-printed chameleon enclosure.

---

## ✨ Highlights

* 🎨 Real-time color sensing with TCS34725 Color Sensor
* 💡 Smooth color output via WS2812B LEDs (ring / matrix)
* 🧠 Smoothing (EMA) for stable visuals (no flicker)
* ⚙️ Auto white calibration (no button required)
* 🌈 Gamma correction for natural-looking colors
* 🔋 Battery-powered (LiPo + boost converter)
* 🧩 Fully integrated **custom 3D chameleon body + base platform**

---

## 🧱 Hardware

| Component                      | Notes                                 |
| ------------------------------ | ------------------------------------- |
| ESP32-C6 Mini                  | Main controller (Wi-Fi + BLE capable) |
| TCS34725 Color Sensor          | RGB + clear channel sensing           |
| WS2812B LEDs                   | Ring (16 LEDs) or matrix              |
| LiPo Battery (3.7V)            | Portable power                        |
| Boost Converter (e.g., MT3608) | Steps 3.7V → 5V for LEDs              |

> ℹ️ **Note:** This build runs without series resistor/capacitor on the LED line. For maximum stability (especially at higher brightness or longer wiring), adding a **~330Ω data resistor** and **~1000µF capacitor across 5V/GND** is recommended.

---

## 🧩 Mechanical Design

* Custom **3D chameleon model** with an internal cavity
* Dedicated **base platform** to mount:

  * ESP32-C6 Mini
  * Color sensor (positioned near surface contact)
  * LED ring/matrix (diffused through body where needed)
* Designed in CAD (e.g., Fusion 360) and printed (FDM/Resin)
* Enclosure helps:

  * Maintain fixed sensor distance
  * Reduce ambient light interference
  * Improve perceived color accuracy

---

## 🧩 3D Model Attribution

The chameleon body is based on a model from Printables (modified for this project).
The design was adapted by:

*Splitting the model into two parts
*Designing a custom internal base platform to house electronics
*Integrating sensor placement and LED alignment
*Optimizing for assembly and component fit

---

## ⚙️ Software

* Platform: Arduino IDE / PlatformIO
* Libraries:

  * Adafruit TCS34725
  * Adafruit NeoPixel

---

## 🧠 How It Works

1. The sensor reads **raw RGB + clear (C)** values from the surface
2. Values are **normalized** using auto white calibration
3. **Exponential smoothing (EMA)** reduces noise and flicker
4. **Brightness normalization** keeps white from overpowering colors
5. **Gamma correction** improves visual perception
6. Final RGB is pushed to the LED array in real time

---

## ▶️ Usage

1. Power ON
2. Place the chameleon close to a surface (~1–2 cm)
3. LEDs adapt to the detected color
4. Keep it on a **white surface briefly** to auto-calibrate

---

## 🎯 Design Notes

* Works best with:

  * Consistent distance to surface
  * Controlled lighting (or integrated white illumination)
* White can appear overly bright without normalization—handled in code
* Color fidelity is **visually convincing**, not spectrometer-grade

---

## 📦 Setup

```bash
git clone https://github.com/yourusername/chameleon-toy.git
```

1. Open in Arduino IDE / PlatformIO
2. Install required libraries
3. Select ESP32-C6 board
4. Upload

---

## 🔧 Known Limitations

* Ambient light can affect readings
* Glossy surfaces may skew color
* WS2812 color space ≠ real-world color perfectly

---

## 🚀 Future Improvements

* 📱 BLE app (color lock, brightness, modes)
* 🧠 HSV-based correction for better perceptual matching
* 💾 Persistent calibration (Preferences/EEPROM)
* 🎮 Gesture input (e.g., APDS9960)
* 🔆 Integrated controlled illumination around sensor
* 🧴 Diffuser optimization for more uniform LED output

---

## 📸 Demo



---

## 🧠 What This Demonstrates

* Embedded systems integration
* Real-time signal processing
* Sensor calibration & filtering
* Power design with LiPo + boost
* Mechanical + electronics co-design

---

## 📜 License

MIT

---

## 🙌 Acknowledgements
Adafruit libraries
Open-source hardware community

## ⭐ Support

If you found this useful, consider giving the repo a star ⭐
