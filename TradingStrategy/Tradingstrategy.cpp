#include <vector> // for storing historical data

class TradingStrategy
{
public:
  TradingStrategy(int shortTermWindow, int longTermWindow) : shortTermWindow_(shortTermWindow), longTermWindow_(longTermWindow) {}

  void update(const MarketData &marketData)
  {
    std::cout << "Trading strategy updated with market data for symbol: " << marketData.symbol << std::endl;
    // Store historical closing prices
    closingPrices_.push_back(marketData.bidPrice); // Replace with actual closing price if available

    // Calculate SMAs only when enough data is available
    if (closingPrices_.size() < longTermWindow_)
    {
      return;
    }

    shortTermSMA_ = calculateSMA(closingPrices_, shortTermWindow_);
    longTermSMA_ = calculateSMA(closingPrices_, longTermWindow_);

    // Check for SMA crossover and generate signals (optional)
    if (shortTermSMA_ > longTermSMA_ && !isLong_)
    {
      // Generate buy signal
      isLong_ = true;
      std::cout << "Buy signal generated! (Short-term SMA crossed above long-term SMA)" << std::endl;
    }
    else if (shortTermSMA_ < longTermSMA_ && isLong_)
    {
      // Generate sell signal
      isLong_ = false;
      std::cout << "Sell signal generated! (Short-term SMA crossed below long-term SMA)" << std::endl;
    }
  }

private:
  double calculateSMA(const std::vector<double> &prices, int window) const
  {
    double sum = 0.0;
    for (int i = 0; i < window && i < prices.size(); ++i)
    {
      sum += prices[i];
    }
    return sum / window;
  }

  int shortTermWindow_;
  int longTermWindow_;
  std::vector<double> closingPrices_; // Store historical closing prices
  double shortTermSMA_;
  double longTermSMA_;
  bool isLong_ = false; // Flag to indicate current position (long or short)
};
