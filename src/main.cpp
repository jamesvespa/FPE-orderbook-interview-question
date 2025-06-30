#include <iostream>

#include "orderbook.h"

using namespace ORDERBOOK;

int main()
{
	//Sample created from the question description
	 OrderBook orderBook;
	 orderBook.ProcessMsg(gs_marketData[0]); //ASK 110: 5
	 orderBook.ProcessMsg(gs_marketData[1]); //BID 90: 10
	 orderBook.ProcessMsg(gs_marketData[2]); //ASK 110: 10
	 orderBook.ProcessMsg(gs_marketData[3]); //ASK 105: 3
	 orderBook.ProcessMsg(gs_marketData[4]); //ASK 105: 7
	 orderBook.ProcessMsg(gs_marketData[5]); //BID 90 : 2
	 orderBook.ProcessMsg(gs_marketData[6]); //BID 90 : 3
	 orderBook.ProcessMsg(gs_marketData[7]); //BID 100 : 4
	 orderBook.ProcessMsg(gs_marketData[8]); //BID 100 : 6
	 orderBook.ProcessMsg(gs_marketData[9]); //BID 105 : 4 - CROSS THE SPREAD!!
	 orderBook.ProcessMsg(gs_marketData[10]); //ASK 80 : 23 - CROSS THE SPREAD!!
	 orderBook.ProcessMsg(gs_marketData[11]); //BID 107 : 8 - //Aggress order but we will add 2 new unfilled qty at 107
	 orderBook.PrintBook();

	//data file sample
	// OrderBook orderBook;
	// orderBook.ProcessMsg(gs_marketData2[0]); //ASK {A,100000, S, 1, 1075},
	// orderBook.ProcessMsg(gs_marketData2[1]); //BID {A,100001,B,9,1000 },
	// orderBook.ProcessMsg(gs_marketData2[2]); //{ A,100002,B,30,975 },
	// orderBook.ProcessMsg(gs_marketData2[3]); //{ A,100003,S,10,1050 },
	// orderBook.ProcessMsg(gs_marketData2[4]); //{ A,100004,B,10,950 },
	// orderBook.ProcessMsg(gs_marketData2[5]); //{ A,100005,S,2,1025 },
	// orderBook.ProcessMsg(gs_marketData2[6]); //{ A,100006,B,1,1000 } //AGGRESS
	// orderBook.ProcessMsg(gs_marketData2[7]); //{ X,100004,B,10,950 },
	// orderBook.ProcessMsg(gs_marketData2[8]); //{ A,100007,S,5,1025 }
	// orderBook.ProcessMsg(gs_marketData2[9]); //{ A,100008,B,3,1050 }, //AGGRESS
	// orderBook.ProcessMsg(gs_marketData2[10]); //{ X,100008,B,3,1050 }, //Expect to fail as 100008 already filled.
	// orderBook.ProcessMsg(gs_marketData2[11]); //{ X,100005,S,2,1025 }  //Expect to fail as 100005 already filled.
}