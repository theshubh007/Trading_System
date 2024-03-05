#include "ordermanagement.h"
#include <stdexcept> // For exceptions

const std::vector<std::string> supportedSymbols = {"AAPL", "GOOG", "MSFT", "AMZN", "TSLA"};

OrderManagement::OrderManagement(OrderBook *orderBook) : orderBook_(orderBook) {}

OrderManagement::~OrderManagement() {}

void OrderManagement::addOrder(const Order &order)
{
  // Validate order data
  if (!isValidOrder(order))
  {
    throw std::invalid_argument("Invalid order data");
  }

  // Check for order book capacity (optional)
  if (orderBook_->getOrderCount() >= orderBook_->getMaxOrders())
  {
    throw std::runtime_error("Order book reached maximum capacity");
  }

  // Add the order to the order book

  std::cout << "Order added to the order book.  named :" << order.symbol << std::endl;
  orderBook_->addOrder(order);
}

bool OrderManagement::isValidOrder(const Order &order)
{
  // Implement your specific validation logic here
  // Check for:
  // - Valid symbol (exists in market data or reference list)
  // - Positive price
  // - Positive size
  // - Valid order type (buy/sell)
  // ... (add other validation rules as needed)
  // Check if symbol is supported
  if (std::find(supportedSymbols.begin(), supportedSymbols.end(), order.symbol) == supportedSymbols.end())
  {
    return false;
  }

  return true; // Replace with actual validation logic
}
