

#pragma once

#include "translib/tcpSession.h"

namespace translib
{
class TcpSessionFactory
{
public:
	TcpSessionFactory() {};
	virtual ~TcpSessionFactory() {};

	virtual TcpSessionPtr create()
	{
		return TcpSessionPtr(new TcpSession());
	}
};

} /* namespace translib */


