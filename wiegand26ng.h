/************************************************
 This is a better Wiegand26 library

 Not only is it more maintainable, but it doesn't
 require copy and pasting the same functions
 to support multiple readers.

 *************************************************/

#ifndef	_WIEGAND26NG_H_ 
#define	_WIEGAND26NG_H_ 

#include <inttypes.h>

class Wiegand26ng {
public:

  Wiegand26ng(uint8_t p1, uint8_t p2);
  ~Wiegand26ng();

  void begin(uint8_t p1, uint8_t p2);
  void initReader(void);
  void readerOne(void);
  void readerZero(void);

  bool canReadTag(void);
  bool canReadTag(uint8_t);

  long read(void);

private:
  uint8_t readerPins[];
  long reader;
  int readerCount;

#ifdef MCU328
  PCATTACH pcattach;
#endif

  void end(void);
};

#endif
