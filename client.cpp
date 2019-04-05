#include "Calculator.h"
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TBufferTransports.h>
#include <thrift/transport/TTransportUtils.h>

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;

using namespace ::shared;
using namespace ::calc;

int main() {
	std::shared_ptr<TTransport> socket(new TSocket("localhost", 9090));
	std::shared_ptr<TTransport> transport(new TBufferedTransport(socket));
	std::shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));
	CalculatorClient client(protocol);

	try {
		transport->open();
		client.ping();
		printf("1 + 2 = %d\n", client.add(1, 2));
		Work work;
		work.op = Operation::DIV;
		work.r1 = 1;
		work.r2 = 0;
		try {
			client.calc(1, work);
			printf("DIV by zero\n");
		} catch (InvalidOperation& e) {
			printf("InvalidOperation: %s\n", e.repr.c_str());
		}
		work.op = Operation::SUB;
		printf("1 - 0 = %d\n", client.calc(1, work));
		SharedStruct ss;
		client.getStruct(ss, 1);
		printf("getStruct = %d\n", ss.key);
		std::string s = "hello", t;
		client.echo(t, s);
		printf("echo = %s\n", t.c_str());
		transport->close();
	} catch (TException& tx) {
		printf("Exception: %s\n", tx.what());
	}
	return 0;
}
