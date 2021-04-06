/*
   WebSocketClient.ino

    Created on: 24.05.2015

*/

#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

#include <WebSocketsClient.h>

#include <Hash.h>

ESP8266WiFiMulti WiFiMulti;
WebSocketsClient webSocket;

// assign pin num
int right_pin = D3;
int left_pin = D2;
int forward_pin = D0;
int reverse_pin = D1;

int speedPin = D6;
int dirPin1 = D7;
int dirPin2 = D8;

// duration for output
int time1 = 50;
// initial command
int command = 0;

int normalSpeed = 1000;
int slowSpeed = 550;

void right(int time)
{
  Serial.println("right");
  digitalWrite(right_pin, LOW);
  delay(time);
}

void left(int time)
{
  Serial.println("left");
  digitalWrite(left_pin, LOW);
  delay(time);
}

void forward(int time)
{
  Serial.println("forward");
  digitalWrite(forward_pin, LOW);
  delay(time);
}

void reverse(int time)
{
  Serial.println("back");
  digitalWrite(reverse_pin, LOW);
  delay(time);
}

void forward_right(int time)
{
  digitalWrite(forward_pin, LOW);
  digitalWrite(right_pin, LOW);
  delay(time);
}

void reverse_right(int time)
{
  digitalWrite(reverse_pin, LOW);
  digitalWrite(right_pin, LOW);
  delay(time);
}

void forward_left(int time)
{
  digitalWrite(forward_pin, LOW);
  digitalWrite(left_pin, LOW);
  delay(time);
}

void reverse_left(int time)
{
  digitalWrite(reverse_pin, LOW);
  digitalWrite(left_pin, LOW);
  delay(time);
}

void reset(int time)
{
  Serial.println("Resetting pins");
  digitalWrite(right_pin, HIGH);
  digitalWrite(left_pin, HIGH);
  digitalWrite(forward_pin, HIGH);
  digitalWrite(reverse_pin, HIGH);
  delay(time);
}

void stopCar(int time) {
  Serial.println("stoppppp");
  analogWrite(speedPin, 0);
  delay(time);
}

void forward_normal(int time) {
  Serial.println("goooooo");
  digitalWrite(dirPin1, HIGH);
  digitalWrite(dirPin2, LOW);
  analogWrite(speedPin, normalSpeed);
  delay(time);
}

void forward_slow(int time) {
  digitalWrite(dirPin1, HIGH);
  digitalWrite(dirPin2, LOW);
  analogWrite(speedPin, slowSpeed);
  delay(time);
}

void backward_normal(int time) {
  digitalWrite(dirPin1, LOW);
  digitalWrite(dirPin2, HIGH);
  analogWrite(speedPin, normalSpeed);
  delay(time);
}

void backward_slow(int time) {
  digitalWrite(dirPin1, LOW);
  digitalWrite(dirPin2, HIGH);
  analogWrite(speedPin, slowSpeed);
  delay(time);
}
void webSocketEvent(WStype_t type, uint8_t *payload, size_t length)
{

  switch (type)
  {
    case WStype_DISCONNECTED:
      Serial.printf("[WSc] Disconnected!\n");
      break;
    case WStype_CONNECTED:
      {
        Serial.printf("[WSc] Connected to url: %s\n", payload);

        // send message to server when Connected
        //        webSocket.sendTXT("Connected");
      }
      break;
    case WStype_TEXT:
      Serial.printf("[WSc] get text: %s\n", payload);
      for (size_t i = 0; i < length; i++)
      {
        command = payload[i];
      }
      switch (command)
      {
        //reset command
        case 48:
          //            reset(time1);
          stopCar(time1);
          break;
        // single command
        case 49:
          //            forward(time1);
          forward_normal(time1);
          break;
        case 50:
          //            reverse(time1);
          backward_normal(time1);
          break;
        case 51:
          //            right(time1);
          forward_slow(time1);
          break;
        case 52:
          //            left(time1);
          backward_slow(time1);
          break;
        //combination command
        case 53:
          forward_right(time1);
          break;
        case 54:
          forward_left(time1);
          break;
        case 55:
          reverse_right(time1);
          break;
        case 56:
          reverse_left(time1);
          break;

        default:
          Serial.print("Inalid Command\n");
          break;
      };

      // send message to server
      // webSocket.sendTXT("message here");
      break;
    case WStype_BIN:
      Serial.printf("[WSc] get binary length: %u\n", length);
      hexdump(payload, length);

      // send data to server
      // webSocket.sendBIN(payload, length);
      break;
    case WStype_PING:
      // pong will be send automatically
      Serial.printf("[WSc] get ping\n");
      break;
    case WStype_PONG:
      // answer to a ping we send
      Serial.printf("[WSc] get pong\n");
      break;
  }
}

void setup()
{
  // Serial.begin(921600);
  Serial.begin(115200);

  //Serial.setDebugOutput(true);
  Serial.setDebugOutput(true);

  Serial.println();
  Serial.println();
  Serial.println();

  pinMode(right_pin, OUTPUT);
  pinMode(left_pin, OUTPUT);
  pinMode(forward_pin, OUTPUT);
  pinMode(reverse_pin, OUTPUT);

  pinMode(dirPin1, OUTPUT);
  pinMode(dirPin2, OUTPUT);
  pinMode(speedPin, OUTPUT);

  digitalWrite(right_pin, HIGH);
  digitalWrite(left_pin, HIGH);
  digitalWrite(forward_pin, HIGH);
  digitalWrite(reverse_pin, HIGH);

  for (uint8_t t = 4; t > 0; t--)
  {
    Serial.printf("[SETUP] BOOT WAIT %d...\n", t);
    Serial.flush();
    delay(1000);
  }

  WiFiMulti.addAP("HHome", "12345678");

  //WiFi.disconnect();
  while (WiFiMulti.run() != WL_CONNECTED)
  {
    delay(100);
  }

  // server address, port and URL
  webSocket.begin("192.168.0.2", 82, "/car");

  // event handler
  webSocket.onEvent(webSocketEvent);

  // use HTTP Basic Authorization this is optional remove if not needed
  //	webSocket.setAuthorization("user", "Password");

  // try ever 5000 again if connection has failed
  webSocket.setReconnectInterval(5000);

  // start heartbeat (optional)
  // ping server every 15000 ms
  // expect pong from server within 3000 ms
  // consider connection disconnected if pong is not received 2 times
  //  webSocket.enableHeartbeat(15000, 3000, 2);
}

void loop()
{
  webSocket.loop();
}
