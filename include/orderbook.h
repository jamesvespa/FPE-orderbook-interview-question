#pragma once

#include <map>

#include "marketdata.h"

namespace ORDERBOOK
{
	typedef std::map<long, Level> ORDERS;

	typedef std::map<long, ORDERS, std::greater<> > BIDS;
	typedef std::map<long, ORDERS, std::greater<> > ASKS;

	class OrderBook
	{
	public:
		OrderBook() = default;
		virtual ~OrderBook() = default;

		void ProcessMsg(const Price& msg);
		void PrintBook() const;

	private:
		bool Aggressing(const Price& msg) const;
		void Update(const Price& msg);
		void Add(const Price& msg);
		void Delete(const Price& msg);

		BIDS m_bids;
		ASKS m_asks;
	};
};

