#ifndef DISPLAY_H
#define DISPLAY_H

#include <Arduino.h>

#define NEX_TIMEOUT  90  // 90 seconds
#define NEX_BRIGHT   95  // 100% = full brightness
#define NEX_MEDIUM   25  // For the clock
#define NEX_DIM       3  // for the lines, 1 = very dim, 0 = off

struct Line{
  int16_t x1;
  int16_t y1;
  int16_t x2;
  int16_t y2;
};

union gflags
{
  struct
  {
    uint16_t fan:1;
    uint16_t state:3;
    int16_t  rh:11;
    uint16_t res:1;
  } b;
  uint16_t u;
};

struct gPoint{
  uint32_t time;
  int16_t temp;
  int16_t l;
  int16_t h;
  gflags bits;
};

class Display
{
public:
  Display()
  {
  }
  void init(void);
  void oneSec(void);
  bool screen(bool bOn);
  void reset(void);
  void checkNextion(void); // all the Nextion recieved commands
  void updateTemps(void);
  void drawForecast(bool bRef);
  void Note(char *cNote);
  bool getGrapthPoints(gPoint *pt, int n);
private:
  void refreshAll(void);
  void updateClock(void);
  void displayTime(void);
  void displayOutTemp(void);
  void updateModes(void); // update any displayed settings
  void updateAdjMode(bool bRef);  // current adjust of the 4 temp settings
  void updateRSSI(void);
  void updateNotification(bool bRef);
  void updateRunIndicator(bool bForce); // run and fan running
  void addGraphPoints(void);
  void fillGraph(void);
  void drawPoints(int w, uint16_t color);
  void drawPointsRh(uint16_t color);
  void drawPointsTemp(void);
  uint16_t stateColor(gflags v);
  void Lines(void);
  int tween(int8_t t1, int8_t t2, int m, int8_t h);

  uint16_t m_backlightTimer = NEX_TIMEOUT;
#define GPTS 300 // 320 px width - (10+10) padding
  gPoint m_points[GPTS];
public:
  uint16_t m_pointsIdx;
  int16_t m_updateFcst = 1;
  uint16_t m_temp_counter = 10*60;
  uint8_t m_adjustMode;
};

#endif // DISPLAY_H
