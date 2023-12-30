// Mock de Ticker.h
#ifndef TICKER_H
#define TICKER_H

class Ticker {
  public:
	void attach(float seconds, void (*callback)(void)) {}
	void detach() {}
	void start() {}
	void update() {}
};

#endif // TICKER_H
