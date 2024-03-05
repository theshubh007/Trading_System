#ifndef MARKETDATAFEED_H
#define MARKETDATAFEED_H

#include <string>
#include <vector>

// Structure to represent market data (replace with your specific fields)
struct MarketData
{
  std::string symbol;
  double bidPrice;
  double askPrice;
  int bidSize;
  int askSize;
  // ... (add other relevant market data fields)
};

class MarketDataFeed
{
public:
  virtual ~MarketDataFeed() {} // Virtual destructor for proper resource cleanup

  virtual void start() = 0; // Start data feed (abstract)
  virtual void stop() = 0;  // Stop data feed (abstract)

  // Optional: Specific data receiving method (if not using a callback mechanism)
  virtual std::vector<MarketData> getMarketData() const = 0; // Get current market data (optional)

protected:
  // Pure virtual destructor enforces subclass implementation of start() and stop()
  virtual void onMarketDataReceived(const MarketData &) = 0; // Handle incoming market data (abstract)

private:
  // Consider adding private member variables for configuration or internal state (if needed)
};

#endif // MARKETDATAFEED_H
