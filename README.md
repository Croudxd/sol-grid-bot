WebSockets:

advanced-trade-ws.coinbase.com — ticker + level2
advanced-trade-ws-user.coinbase.com — order fills/updates

REST:

POST /api/v3/brokerage/orders — create order
DELETE /api/v3/brokerage/orders/batch_cancel — cancel order
PUT /api/v3/brokerage/orders/edit — edit order
GET /api/v3/brokerage/accounts — get balance
