#include <DHT.h>

#define DHTPIN A0
#define DHTTYPE DHT22
#define pinr 6
#define ping 3
#define pinb 9

DHT dht(A0, DHT22);

int r, g, b, x, y, z, a = 0, c, incr = 1, k=0;
long detprev, detikbaru;
long t;
float hum, temp;

void setup()
{
  pinMode(pinr, OUTPUT); 
  pinMode(ping, OUTPUT);
  pinMode(pinb, OUTPUT);
  Serial.begin(9600);
  dht.begin();
}

void loop()
{
  t = millis();
  long  det = t / 1000;
  if (det != detprev) {
  detikbaru = 1;
  }
  else {
  detikbaru = 0;
  }
  detprev = det;
  hum = dht.readHumidity();
  temp = dht.readTemperature();
  if (temp == 25 && hum == 65)
  {
  r = 255;
  g = 255;
  b = 255;
  }
  else if (temp > 25 && hum > 65)
  {
  if (detikbaru == 1)
  {
    if (incr == 1) {
      if (a == 200) {
        incr = -1;
      }
    }
    else if (incr == -1) {
      if (a == 0) {
        incr = 1;
      }
    }
    if (det % 2 == 1) {
      g = a;
      a = a + incr;
      r = 255;
      b = 0;
    }
    else {
      r = 0;
      g = 0;
      b = 0;
    }
  }
  }
  else if (temp < 25 && hum > 65)
  {
  g = 255;
  b = 0;
  x = abs (-((t / 10) % 510) + 255);
  r = x;
  }
  else if (temp < 25 && hum < 65)
  {
  r = 0;
  b = 255;
  c = 100 + (100 * sin (0.38 * t / 1000));
  g = c;
  }
  else if (temp > 25 && hum < 65)
  {
  r = 255;
  g = 0;
  y = (t / 150) % 60;
  z = -3 * y + 255;
  b = z;
  }
  analogWrite(pinr, r);
  analogWrite(ping, g);
  analogWrite(pinb, b);
  Serial.print("Time is: ");
  Serial.print (t);
  Serial.print(" ms, Humidity: ");
  Serial.print(hum);
  Serial.print(" %, Temp: ");
  Serial.print(temp);
  Serial.print(" Celsius, R: ");
  Serial.print(r);
  Serial.print(", G: ");
  Serial.print(g);
  Serial.print(", B: ");
  Serial.print(b);
  Serial.print(", det: ");
  Serial.println(det);
  }
}
