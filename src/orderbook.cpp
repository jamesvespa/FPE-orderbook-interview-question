#pragma once

#include <iostream>
#include <map>
#include <ostream>

#include "marketdata.h"
#include "orderbook.h"

#include <ranges>

namespace ORDERBOOK
{
	void OrderBook::PrintBook() const
	{
		std::cout << "=================" << std::endl;
		std::cout << "ASK" << std::endl;

		for (auto & iter : m_asks) {
			std::cout << iter.first << ":";

			for (auto & orders : iter.second) {
				std::cout <<  " " << orders.second.qty;
			}

			std::cout << std::endl;
		}

		std::cout << "------------" << std::endl;
		for (auto & iter : m_bids) {
			std::cout << iter.first << ":";

			for (auto & orders : iter.second) {
				std::cout <<  " " << orders.second.qty;
			}

			std::cout << std::endl;
		}

		std::cout << "BID" << std::endl;
		std::cout << "=================" << std::endl;
	}

	void OrderBook::ProcessMsg(const Price& msg)
	{
		switch (msg.type)
		{
		case 'A':
		{
			if (Aggressing(msg))
			{
				Update(msg);  //update the book if it crosses the spread
			}
			else
			{
				Add(msg); //Here we add new entries to one side of the book
			}
			break;
		}
		case 'X':
			Delete(msg);
			break;
		default:
			std::cout << "Unknown msg type " << msg.type << std::endl;
		}
	}

	bool OrderBook::Aggressing(const Price& msg) const
	{
		if (msg.side == 'B')
		{
			for (const auto &key: m_asks | std::views::keys)
			{
				if (msg.price >= key)
				{
					return true;
				}
			}
		}
		else if (msg.side == 'S')
		{
			for (const auto &key: m_bids | std::views::keys)
			{
				if (msg.price <= key)
				{
					return true;
				}
			}
		}

		return false;
	}

	void OrderBook::Update(const Price& msg)
	{
		auto& side = (msg.side == 'B') ? m_asks : m_bids;

		if ( msg.side == 'B')
		{
			int qty = msg.qty;
			for (auto iter=side.rbegin(); side.rend() != iter; ++iter)
			{
				auto& orders = iter->second;
				//now we cycle through orders reducing the qty
				for (auto itr=orders.begin(); itr!=orders.end(); )
				{
					auto& order = itr->second;
					if (order.qty > qty)
					{
						order.qty -= qty; //qty can be filled by this order
						return;
					}

					qty -= order.qty; //Order is fully filled by qty so remove from level
					itr=orders.erase(itr);

					if (orders.empty()) {
						side.erase(order.price); //no more orders so remove price level
					}
				}

				if (qty > 0 && msg.price < iter->first ) { //Unable to fill, so add new open order to book
					auto open_order {msg};
					open_order.qty = qty;
					open_order.side='A';
					Add(open_order);
				}
			}
		}
		if ( msg.side == 'S')
		{
			int qty = msg.qty;
			for (auto iter=side.begin(); side.end() != iter; )
			{
				auto& orders = iter->second;
				//now we cycle through orders reducing the qty
				for (auto itr=orders.begin(); itr!=orders.end();)
				{
					auto& order = itr->second;
					if (order.qty > qty) {
						order.qty -= qty; //qty can be filled by this order
						return;
					}

					qty -= order.qty; //Order is fully filled by qty so remove from level
					itr=orders.erase(itr);

					if (orders.empty()) {
						iter=side.erase(iter); //no more orders so remove price level
					}

					if (qty > 0 && msg.price > iter->first ) { //Unable to fill, so add new open order to book
						auto open_order {msg};
						open_order.qty = qty;
						open_order.side='B';
						Add(open_order);
					}
				}
			}
		}
	}

	void OrderBook::Add(const Price& msg)
	{
		auto& side = (msg.side == 'B' ? m_bids : m_asks);

		if (const auto level = side.find(msg.price); level != side.end())
		{
			auto& orders = level->second;
			orders.emplace(msg.orderId, Level(msg));
		}
		else
		{
			auto newLevel = side.emplace(msg.price, ORDERS());
			auto& orders = newLevel.first->second;
			orders.emplace(msg.orderId, Level(msg));
		}
	}

	void OrderBook::Delete(const Price& msg)
	{
		auto& side = (msg.side == 'B' ? m_bids : m_asks);
		auto level = side.find(msg.price);
		if (level != side.end())
		{
			auto& orders = level->second;
			if (const auto order = orders.find(msg.orderId); order != orders.end())
			{
				orders.erase(order);
				if (orders.empty())
				{
					side.erase(msg.price);
					std::cout << "Removed price level .. " << msg.orderId  << " " << msg.price << std::endl;
				}
			}
			else
			{
				std::cout << "Unknown order id .. " << msg.orderId << std::endl;
			}
		}
		else
		{
			std::cout << "Unknown price level .." << msg.price << std::endl;
		}
	}
};

