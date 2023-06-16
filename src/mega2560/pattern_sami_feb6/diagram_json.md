# MD-file for the diagram in WokWi.
```json
{
  "version": 1.01,
  "author": "Kvadraturen vgs",
  "editor": "wokwi",
  "parts": [
    { "type": "wokwi-arduino-mega", "id": "uno", "top": -1855.49, "left": 1418.45, "attrs": {} },
    {
      "type": "wokwi-neopixel-canvas",
      "id": "neopixels1",
      "top": 950.07,
      "left": 0,
      "rotate": 90,
      "attrs": { "rows": "1", "cols": "60", "matrixBrightness": "10", "pixelate": "circle" }
    },
    {
      "type": "wokwi-neopixel-canvas",
      "id": "neopixels2",
      "top": 191,
      "left": 759,
      "rotate": 1e-8,
      "attrs": { "rows": "1", "cols": "60", "matrixBrightness": "10", "pixelate": "circle" }
    },
    {
      "type": "wokwi-neopixel-canvas",
      "id": "neopixels3",
      "top": -346.1,
      "left": -537.5,
      "rotate": 225,
      "attrs": { "rows": "1", "cols": "60", "matrixBrightness": "10", "pixelate": "circle" }
    },
    {
      "type": "wokwi-neopixel-canvas",
      "id": "neopixels4",
      "top": 727.9,
      "left": 536.5,
      "rotate": 45,
      "attrs": { "rows": "1", "cols": "60", "matrixBrightness": "10", "pixelate": "circle" }
    },
    {
      "type": "wokwi-neopixel-canvas",
      "id": "neopixels5",
      "top": -346.31,
      "left": 537.66,
      "rotate": 315,
      "attrs": { "rows": "1", "cols": "60", "matrixBrightness": "10", "pixelate": "circle" }
    },
    {
      "type": "wokwi-neopixel-canvas",
      "id": "neopixels6",
      "top": -568.79,
      "left": -1.19,
      "rotate": 270,
      "attrs": { "rows": "1", "cols": "60", "matrixBrightness": "10", "pixelate": "circle" }
    },
    {
      "type": "wokwi-neopixel-canvas",
      "id": "neopixels7",
      "top": 728.46,
      "left": -537.62,
      "rotate": 135,
      "attrs": { "rows": "1", "cols": "60", "matrixBrightness": "10", "pixelate": "circle" }
    },
    {
      "type": "wokwi-neopixel-canvas",
      "id": "neopixels8",
      "top": 892.62,
      "left": 290.25,
      "rotate": 67.5,
      "attrs": { "rows": "1", "cols": "60", "matrixBrightness": "10", "pixelate": "circle" }
    },
    {
      "type": "wokwi-neopixel-canvas",
      "id": "neopixels9",
      "top": 481.42,
      "left": 701.9,
      "rotate": 22.5,
      "attrs": { "rows": "1", "cols": "60", "matrixBrightness": "10", "pixelate": "circle" }
    },
    {
      "type": "wokwi-neopixel-canvas",
      "id": "neopixels10",
      "top": -510.84,
      "left": -290.83,
      "rotate": 247.5,
      "attrs": { "rows": "1", "cols": "60", "matrixBrightness": "10", "pixelate": "circle" }
    },
    {
      "type": "wokwi-neopixel-canvas",
      "id": "neopixels11",
      "top": -99.64,
      "left": -702.05,
      "rotate": 202.5,
      "attrs": { "rows": "1", "cols": "60", "matrixBrightness": "10", "pixelate": "circle" }
    },
    {
      "type": "wokwi-neopixel-canvas",
      "id": "neopixels12",
      "top": -511.07,
      "left": 290.53,
      "rotate": 292.5,
      "attrs": { "rows": "1", "cols": "60", "matrixBrightness": "10", "pixelate": "circle" }
    },
    {
      "type": "wokwi-neopixel-canvas",
      "id": "neopixels13",
      "top": 482.18,
      "left": -702.04,
      "rotate": 157.5,
      "attrs": { "rows": "1", "cols": "60", "matrixBrightness": "10", "pixelate": "circle" }
    },
    {
      "type": "wokwi-neopixel-canvas",
      "id": "neopixels14",
      "top": -99.12,
      "left": 702.44,
      "rotate": 337.5,
      "attrs": { "rows": "1", "cols": "60", "matrixBrightness": "10", "pixelate": "circle" }
    },
    {
      "type": "wokwi-neopixel-canvas",
      "id": "neopixels15",
      "top": 893,
      "left": -291.5,
      "rotate": 112.5,
      "attrs": { "rows": "1", "cols": "60", "matrixBrightness": "10", "pixelate": "circle" }
    },
    {
      "type": "wokwi-neopixel-canvas",
      "id": "neopixels16",
      "top": 191.55,
      "left": -759.75,
      "rotate": 180,
      "attrs": { "rows": "1", "cols": "60", "matrixBrightness": "10", "pixelate": "circle" }
    },
    {
      "type": "wokwi-pushbutton",
      "id": "btn1",
      "top": -1830,
      "left": 360.93,
      "rotate": -90,
      "attrs": { "color": "red", "key": "t" }
    },
    {
      "type": "wokwi-led",
      "id": "led1",
      "top": -1752,
      "left": 669.5,
      "attrs": { "color": "cyan", "flip": "" }
    },
    {
      "type": "wokwi-resistor",
      "id": "r1",
      "top": -1745,
      "left": 372.5,
      "rotate": -90,
      "attrs": { "value": "220" }
    }
  ],
  "connections": [
    [ "btn1:2.l", "uno:3", "goldTransp", [ "h0" ] ],
    [ "btn1:1.r", "uno:GND.1", "blackTransp", [ "v0" ] ],
    [ "Sec1:1", "Sec1:2", "Section1Transp", [ "*" ] ],
    [ "uno:5", "neopixels16:DIN", "orangeTransp", [ "v-14", "*", "v-8" ] ],
    [ "uno:6", "neopixels11:DIN", "orangeTransp", [ "v-14", "*", "v-8" ] ],
    [ "uno:7", "neopixels3:DIN", "orangeTransp", [ "v-14", "*", "v-8" ] ],
    [ "uno:8", "neopixels10:DIN", "orangeTransp", [ "v-14", "*", "v-8" ] ],
    [ "uno:9", "neopixels6:DIN", "orangeTransp", [ "v-14", "*", "v-8" ] ],
    [ "uno:10", "neopixels12:DIN", "orangeTransp", [ "v-14", "*", "v-8" ] ],
    [ "uno:11", "neopixels5:DIN", "orangeTransp", [ "v-14", "*", "v-8" ] ],
    [ "uno:12", "neopixels14:DIN", "orangeTransp", [ "v-14", "*", "v-8" ] ],
    [ "uno:22", "neopixels2:DIN", "orangeTransp", [ "h-29", "*", "v-8" ] ],
    [ "uno:24", "neopixels9:DIN", "orangeTransp", [ "h-26", "*", "v-8" ] ],
    [ "uno:26", "neopixels4:DIN", "orangeTransp", [ "h-23", "*", "v-8" ] ],
    [ "uno:28", "neopixels8:DIN", "orangeTransp", [ "h-20", "*", "v-8" ] ],
    [ "uno:30", "neopixels1:DIN", "orangeTransp", [ "h-17", "*", "v-8" ] ],
    [ "uno:32", "neopixels15:DIN", "orangeTransp", [ "h-14", "*", "v-8" ] ],
    [ "uno:34", "neopixels7:DIN", "orangeTransp", [ "h-11", "*", "v-8" ] ],
    [ "uno:36", "neopixels13:DIN", "orangeTransp", [ "h-8", "*", "v-8" ] ],
    [ "Sec2:1", "Sec2:1", "Section2Transp", [ "*" ] ],
    [ "uno:5V", "neopixels1:VDD", "redTransp", [ "v10", "h-98", "*", "v-20" ] ],
    [ "uno:5V", "neopixels2:VDD", "redTransp", [ "v13", "h-98", "*", "v-20" ] ],
    [ "uno:5V", "neopixels3:VDD", "redTransp", [ "v16", "h-98", "*", "v-20" ] ],
    [ "uno:5V", "neopixels4:VDD", "redTransp", [ "v19", "h-98", "*", "v-20" ] ],
    [ "uno:5V", "neopixels5:VDD", "redTransp", [ "v22", "h-98", "*", "v-20" ] ],
    [ "uno:5V", "neopixels6:VDD", "redTransp", [ "v25", "h-98", "*", "v-20" ] ],
    [ "uno:5V", "neopixels7:VDD", "redTransp", [ "v28", "h-98", "*", "v-20" ] ],
    [ "uno:5V", "neopixels8:VDD", "redTransp", [ "v31", "h-98", "*", "v-20" ] ],
    [ "uno:5V", "neopixels9:VDD", "redTransp", [ "v34", "h-98", "*", "v-20" ] ],
    [ "uno:5V", "neopixels10:VDD", "redTransp", [ "v37", "h-98", "*", "v-20" ] ],
    [ "uno:5V", "neopixels11:VDD", "redTransp", [ "v40", "h-98", "*", "v-20" ] ],
    [ "uno:5V", "neopixels12:VDD", "redTransp", [ "v43", "h-98", "*", "v-20" ] ],
    [ "uno:5V", "neopixels13:VDD", "redTransp", [ "v46", "h-98", "*", "v-20" ] ],
    [ "uno:5V", "neopixels14:VDD", "redTransp", [ "v49", "h-98", "*", "v-20" ] ],
    [ "uno:5V", "neopixels15:VDD", "redTransp", [ "v52", "h-98", "*", "v-20" ] ],
    [ "uno:5V", "neopixels16:VDD", "redTransp", [ "v55", "h-98", "*", "v-20" ] ],
    [ "Sec3:1", "Sec3:2", "Section3Transp", [ "*" ] ],
    [ "uno:GND.2", "neopixels1:VSS", "blackTransp", [ "v58", "h-105", "*", "v-14" ] ],
    [ "uno:GND.2", "neopixels2:VSS", "blackTransp", [ "v61", "h-105", "*", "v-14" ] ],
    [ "uno:GND.2", "neopixels3:VSS", "blackTransp", [ "v64", "h-105", "*", "v-14" ] ],
    [ "uno:GND.2", "neopixels4:VSS", "blackTransp", [ "v67", "h-105", "*", "v-14" ] ],
    [ "uno:GND.2", "neopixels5:VSS", "blackTransp", [ "v70", "h-105", "*", "v-14" ] ],
    [ "uno:GND.2", "neopixels6:VSS", "blackTransp", [ "v73", "h-105", "*", "v-14" ] ],
    [ "uno:GND.2", "neopixels7:VSS", "blackTransp", [ "v76", "h-105", "*", "v-14" ] ],
    [ "uno:GND.2", "neopixels8:VSS", "blackTransp", [ "v79", "h-105", "*", "v-14" ] ],
    [ "uno:GND.2", "neopixels9:VSS", "blackTransp", [ "v82", "h-105", "*", "v-14" ] ],
    [ "uno:GND.2", "neopixels10:VSS", "blackTransp", [ "v85", "h-105", "*", "v-14" ] ],
    [ "uno:GND.2", "neopixels11:VSS", "blackTransp", [ "v88", "h-105", "*", "v-14" ] ],
    [ "uno:GND.2", "neopixels12:VSS", "blackTransp", [ "v91", "h-105", "*", "v-14" ] ],
    [ "uno:GND.2", "neopixels13:VSS", "blackTransp", [ "v94", "h-105", "*", "v-14" ] ],
    [ "uno:GND.2", "neopixels15:VSS", "blackTransp", [ "v97", "h-105", "*", "v-14" ] ],
    [ "uno:GND.2", "neopixels16:VSS", "blackTransp", [ "v100", "h-105", "*", "v-14" ] ],
    [ "uno:GND.2", "neopixels14:VSS", "blackTransp", [ "v103", "h-105", "*", "v-14" ] ],
    [ "Sec4:1", "Sec4:2", "Section4Transp", [ "*" ] ],
    [ "uno:5V", "led1:A", "redTranspLED", [ "v0" ] ],
    [ "r1:1", "led1:C", "goldTranspLED", [ "v0" ] ],
    [ "r1:2", "btn1:2.l", "blackTranspLED", [ "v0" ] ]
  ],
  "serialMonitor": { "display": "always" },
  "dependencies": {}
}
```
