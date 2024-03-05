#ifndef ORDERBOOK_H
#define ORDERBOOK_H

#include <string>
#include <vector>

struct Order
{
  std::string symbol;
  double price;
  int size;
  bool isBuyOrder; // True for buy orders, false for sell orders
};

class OrderBook
{
public:
  virtual ~OrderBook() {}

  virtual const std::string &getSymbol() const = 0;
  virtual void addOrder(const Order &order) = 0;
  virtual std::vector<Order> getBestBids(int depth) const = 0;
  virtual std::vector<Order> getBestAsks(int depth) const = 0;
  // ... (add other relevant OrderBook methods, e.g., clear, updateOrder, etc.)
  
  // **Added methods:**
  virtual int getOrderCount() const = 0; // Get the current number of orders in the book
  virtual int getMaxOrders() const = 0;  // Get the maximum allowed number of orders (optional) 
private:
  // Consider adding private member variables for storing bids, asks, and other state
  std::string symbol_;
  // ...
};

#endif // ORDERBOOK_H
