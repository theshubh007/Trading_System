#ifndef ORDERMANAGEMENT_H
#define ORDERMANAGEMENT_H

#include "../OrderBook/Orderbook.h"

class Order; // Forward declaration

class OrderManagement
{
public:
  OrderManagement(OrderBook *orderBook);
  ~OrderManagement();

  void addOrder(const Order &order);

private:
  bool isValidOrder(const Order &order);

  OrderBook *orderBook_;
};

#endif
