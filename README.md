# Divoom Pixoo-64 ESPHome Weather & Clock Dashboard

Custom ESPHome firmware and Home Assistant templates for the **Divoom Pixoo-64** (`64×64` RGB LED matrix), featuring pixel-accurate custom typography, weather icons, adaptive room-light dimming, and an animated Shiba Inu companion.

## Features

- **5-Row `64×64` Pixel-Locked Layout (`pixoo_bitmaps.h`):**
  - **Row 1:** Day of week & date (`5×7` bitmap font).
  - **Row 2:** Hero clock (`9×15` rounded sans digits, `HH   MM`).
  - **Row 3:** Outdoor temperature (`5×8` thermometer icon) & humidity (`5×7` droplet icon), centered in 50/50 columns.
  - **Row 4:** Day-over-day temperature trend (`%+d°` vs. yesterday's daytime peak) & today's min/max range (`4×6` micro font).
  - **Row 5:**
    - `1×14 px` smooth gradient vertical bars on the left (`X=0` Rain `mm`, `X=2` daytime UV index).
    - `14×14` primary weather icon (12 conditions: sun, crescent moon, partly cloudy day/night, cloudy, fog, rain, pouring, thunderstorm, 3-snowflake snow, hail, wind).
    - Secondary badges on the right (rain `mm`, strong wind, cedar pollen) or an **8-frame animated Shiba Inu** (walking back and forth during the day, curled up sleeping at night) whenever space permits.
- **2-Stage Adaptive Dimming:**
  - Combines hardware panel brightness (`light: platform: pixoo`, `1%–90%`) with software RGB scaling (`DimmingDisplay`) and warm night-tint below `15%` RGB so the display can go far dimmer than the stock `1%` hardware floor during late-night hours (`22:00–07:30`), while responding immediately when bedroom lighting turns on.

## Files

- `pixoo64.yaml` — ESPHome device configuration (`esp-idf`, `pixoo` display & light platform, Home Assistant API sensors).
- `pixoo_bitmaps.h` — C++ pixel-art renderer (`9×15` clock, `5×7` & `4×6` bitmap fonts, weather icons, gradient bars, Shiba Inu sprites, `DimmingDisplay`).
- `homeassistant_templates.yaml` — Home Assistant template sensors (`sensor.pixoo_forecast_engine`, `pixoo_temp_diff`, `pixoo_temp_min`, `pixoo_temp_max`, `pixoo_precip_max`, `pixoo_alert_pollen`).
- `secrets.yaml.example` — Template for ESPHome `secrets.yaml` (`wifi_ssid`, `wifi_password`, `ota_password`).

## Setup

1. Add the template sensors from `homeassistant_templates.yaml` to your Home Assistant `configuration.yaml` (and adjust entity IDs in `pixoo64.yaml` to match your weather/illuminance/light entities).
2. Copy `secrets.yaml.example` to `secrets.yaml` and fill in your Wi-Fi and OTA credentials.
3. Copy `pixoo64.yaml`, `pixoo_bitmaps.h`, and `secrets.yaml` into your ESPHome config directory and install wirelessly.
