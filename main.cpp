#include "./MarketDataFeed/marketdatafeed.h"
#include "./MarketDataFeed/marketdatafeed.cpp"
#include "./OrderBook/Orderbook.h"
#include "./OrderBook/Orderbook.cpp"
#include "./OrderManagement/Ordermanagement.h"
#include "./OrderManagement/Ordermanagement.cpp"
#include "./TradingStrategy/TradingStrategy.cpp"
#include <iostream>
#include <thread>
#include <chrono>

int main()
{
  try
  {
    // MarketDataFeed *marketDataFeed = createMarketDataFeed("SIMULATED", ""); // Replace config if needed
    MarketDataFeed *marketDataFeed = new MarketDataFeedImpl();
    marketDataFeed->start();
    std::vector<MarketData> marketData = marketDataFeed->getMarketData();

    std::cout << "\nReceived market data:" << std::endl;
    for (const MarketData &data : marketData)
    {
      std::cout << "Symbol: " << data.symbol << ", Bid Price: " << data.bidPrice << ", Ask Price: " << data.askPrice << ", Bid Size: " << data.bidSize << ", Ask Size: " << data.askSize << std::endl;
    }
    std::cout << std::endl;

    // OrderBook
    // separate order book for each symbol (e.g., "AAPL", "GOOG", etc.)
    std::string symbol = "AAPL";
    OrderBook *orderBook = new OrderBookImpl(symbol);

    // Order Management
    OrderManagement orderManagement(orderBook);
    // Create and add orders
    Order buyOrder;
    buyOrder.symbol = "AAPL";
    buyOrder.price = 151.00;
    buyOrder.size = 200;
    buyOrder.isBuyOrder = true;

    Order sellOrder;
    sellOrder.symbol = "AAPL";
    sellOrder.price = 152.50;
    sellOrder.size = 100;
    sellOrder.isBuyOrder = false;

    orderManagement.addOrder(buyOrder);
    orderManagement.addOrder(sellOrder);

    ///////////////////////
    ////////////////////
    // Trading strategy
    TradingStrategy strategy(3, 20); // Short-term: 5 days, Long-term: 20 days
                                     // Update strategy with each market data point
    for (const MarketData &data : marketData)
    {
      strategy.update(data);
      // ... (optionally use generated buy/sell signals for order management)
    }

    // Simulate some time passing (replace with actual usage in your application)
    // std::this_thread::sleep_for(std::chrono::seconds(2)); // Optional
    delete orderBook;
    marketDataFeed->stop();
    delete marketDataFeed;
  }
  catch (const std::exception &e)
  {
    std::cerr << "Error: " << e.what() << std::endl;
  }

  // Clean up resources

  return 0;
}
