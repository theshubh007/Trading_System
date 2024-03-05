#include "OrderBook.h"
#include <algorithm> // for std::sort

class OrderBookImpl : public OrderBook
{
public:
  OrderBookImpl(const std::string &symbol) : symbol_(symbol) {}

  const std::string &getSymbol() const override
  {
    return symbol_;
  }

  void addOrder(const Order &order) override
  {
    if (order.isBuyOrder)
    {
      bids_.push_back(order);
      std::sort(bids_.rbegin(), bids_.rend(), [](const Order &a, const Order &b)
                { return a.price > b.price; }); // Sort bids by price (descending)
    }
    else
    {
      asks_.push_back(order);
      std::sort(asks_.begin(), asks_.end(), [](const Order &a, const Order &b)
                { return a.price < b.price; }); // Sort asks by price (ascending)
    }
  }

  std::vector<Order> getBestBids(int depth) const override
  {
    std::vector<Order> bestBids(std::min(depth, static_cast<int>(bids_.size())));
    std::copy(bids_.begin(), bids_.begin() + bestBids.size(), bestBids.begin());
    return bestBids;
  }

  std::vector<Order> getBestAsks(int depth) const override
  {
    std::vector<Order> bestAsks(std::min(depth, static_cast<int>(asks_.size())));
    std::copy(asks_.end() - bestAsks.size(), asks_.end(), bestAsks.begin());
    return bestAsks;
  }

  int getOrderCount() const override
  {
    return bids_.size() + asks_.size();
  }

  int getMaxOrders() const override
  {
    return 100; // Example maximum order capacity
  }

private:
  std::string symbol_;
  std::vector<Order> bids_;
  std::vector<Order> asks_;
};
