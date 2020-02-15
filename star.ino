#include <Adafruit_NeoPixel.h>
#define PIN 12 // номер порта к которому подключен модуль
#define count_led 16 // количество светодиодов 

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(count_led, PIN, NEO_GRB + NEO_KHZ800); //first number change does distance between colors

long color = 0;
int delay_def = 100;

void setup() {
  pixels.begin();
  pixels.show(); // Устанавливаем все светодиоды в состояние "Выключено"
}

long rand_color() {
  int red_only = random(0, 2);
  int green_only = random(0, 2);
  int blue_only = random(0, 2);
  if (red_only && green_only || red_only && blue_only || green_only && blue_only) {
    red_only = 0;
    green_only = 0;
    blue_only = 0;
  }
  return pixels.Color(
    random(red_only * 255, 256) * (1 - green_only) * (1 - blue_only),
    random(green_only * 255, 256) * (1 - red_only) * (1 - blue_only), 
    random(blue_only * 255, 256) * (1 - red_only) * (1 - green_only));
}

void center2edge(long color, int delay_time, int delay_vert, bool rnd_color) {
  if (rnd_color) {
    color = rand_color();
  }
  pixels.setPixelColor(0, color);
  pixels.show();
  delay(delay_time);
  
  for(int i = 0; i < 3; i += 1) {
    if (rnd_color) {
      color = rand_color();
    }
    for (int k = 0; k < 5; k += 1) {
      pixels.setPixelColor(1 + k * 3 + 2 - i, color);
      if (delay_vert) {
        pixels.show();
        delay(delay_vert);
      }
    }
    if (!delay_vert) {
      pixels.show();
    }
    delay(delay_time);
  }
}

void edge2center(long color, int delay_time, int delay_vert, bool rnd_color) {
  for(int i = 0; i < 3; i += 1) {
    if (rnd_color) {
      color = rand_color();
    }
    for (int k = 0; k < 5; k += 1) {
      pixels.setPixelColor(1 + k * 3 + i, color);
      if (delay_vert) {
        pixels.show();
        delay(delay_vert);
      }
    }
    if (!delay_vert) {
      pixels.show();
    }
    delay(delay_time);
  }
  
  if (rnd_color) {
    color = rand_color();
  }
  pixels.setPixelColor(0, color);
  pixels.show();
  delay(delay_time);
}

void vertcenter2edge(long color, int delay_time, int delay_vert, bool rnd_color) {
  for (int k = 0; k < 5; k += 1) {
    if (rnd_color) {
      color = rand_color();
    }
    pixels.setPixelColor(0, color);
    if (delay_vert) {
      pixels.show();
      delay(delay_vert);
    }
    
    for(int i = 0; i < 3; i += 1) {
      pixels.setPixelColor(1 + k * 3 + 2 - i, color);
      if (delay_vert) {
        pixels.show();
        delay(delay_vert);
      }
    }
    if (!delay_vert) {
      pixels.show();
    }
    
    delay(delay_time);
  }
}

void vertedge2center(long color, int delay_time, int delay_vert, bool rnd_color) {
  for (int k = 0; k < 5; k += 1) {
    if (rnd_color) {
      color = rand_color();
    }
    for(int i = 0; i < 3; i += 1) {
      pixels.setPixelColor(1 + k * 3 + i, color);
      if (delay_vert) {
        pixels.show();
        delay(delay_vert);
      }
    }
    
    pixels.setPixelColor(0, color);
    if (delay_vert) {
      pixels.show();
      delay(delay_vert);
    }
    if (!delay_vert) {
      pixels.show();
    }
    
    delay(delay_time);
  }
}


void fill(long color) {
  for (int i = 0; i < count_led; i += 1) {
    pixels.setPixelColor(i, color);
  }
  pixels.show();
}

void loop() {
  long color1;
  long color2;
  bool use_vertex = random(0, 2);
  bool rnd_color = random(0, 3) == 0;
  bool type = random(0,3);
  int count = random(1, 10);

  for (int i = 0; i < count; i += 1) {
    int delay_vert = random(0, 3) != 0 ? random(5, 100) : 0;
    int delay_norm = random(0, 3) != 0 ? random(5, 150) : 0;
    
    if (!rnd_color) {
      color1 = rand_color();
      color2 = rand_color();
    }
    if (use_vertex) {
      if (type == 0 || type == 1) {
        vertcenter2edge(color1, delay_norm, delay_vert, rnd_color);
      }
      if (type == 0 || type == 2) {
        vertedge2center(color2, delay_norm, delay_vert, rnd_color);
      }
    } else {
      if (type == 0 || type == 1) {
        center2edge(color1, delay_norm, delay_vert, rnd_color);
      }
      if (type == 0 || type == 2) {
        edge2center(color2, delay_norm, delay_vert, rnd_color);
      }
    }
  }
}
