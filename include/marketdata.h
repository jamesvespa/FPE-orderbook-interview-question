#pragma once


namespace ORDERBOOK
{
	struct Price
	{
		char	type;
		long	orderId;
		char	side;
		int		qty;
		long	price;
	};

	struct Level
	{
		explicit Level(const Price& msg)
		{
			orderId = msg.orderId;
			qty = msg.qty;
			price = msg.price;
		}

		long	orderId;
		int		qty;
		long	price;
	};

	static const Price gs_marketData[] =
	{
		{'A', 100000, 'S', 5, 110},
		{'A', 100001, 'B', 10, 90},
		{'A', 100002, 'S', 10, 110},
		{'A', 100003, 'S', 3, 105},
		{'A', 100004, 'S', 7, 105},
		{'A', 100005, 'B', 2, 90},
		{'A', 100006, 'B', 3, 90},
		{'A', 100007, 'B', 4, 100},
		{'A', 100008, 'B', 6, 100},
		{'A', 100009, 'B', 4, 105},
		{'A', 100010, 'S', 23, 80},
		{'A', 100011, 'B', 8, 107},
		{'A', 100012, 'S', 10, 90}
	};

	static const Price gs_marketData2[] =
	{
		{'A',100000,'S',1,1075},
		{'A',100001,'B',9,1000},
		{'A',100002,'B',30,975},
		{'A',100003,'S',10,1050},
		{'A',100004,'B',10,950},
		{'A',100005,'S',2,1025},
		{'A',100006,'B',1,1000},
		{'X',100004,'B',10,950},
		{'A',100007,'S',5,1025},
		{'A',100008,'B',3,1050},
		{'X',100008,'B',3,1050},
		{'X',100005,'S',2,1025}
	};
}