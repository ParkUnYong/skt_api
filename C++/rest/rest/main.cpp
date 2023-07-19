#include <iostream>
#include <cpprest/http_client.h>

using namespace web::http;
using namespace web::http::client;

pplx::task<void> HTTPRequestCustomHeadersAsync()
{
	http_client client(L"http://apis.skplanetx.com");

	// Manually build up an HTTP request with header and request URI.
	http_request my_req(methods::GET);
	uri_builder builder(U("/weather/severe/alert"));

	my_req.headers().add(L"appKey", L"572ce589-6bbe-3c60-a4d3-d8ed9a8272c1");

	builder.append_query(U("version"), U("1"));
	builder.append_query(U("city"), U("서울"));
	builder.append_query(U("county"), U("중랑구"));
	builder.append_query(U("village"), U("면목"));
	my_req.set_request_uri(builder.to_string());

	// Manually build up an HTTP request with header and request URI.
	return client.request(my_req).then([](http_response response)
	{
		std::wcout << L"Server returned returned status code " 
					<< response.status_code() << L"." << std::endl;;

		std::wcout << response.to_string() << std::endl;
	});
}

int main(void) {
	try
	{
		HTTPRequestCustomHeadersAsync().wait();
	}
	catch (const std::exception &e)
	{
		std::cout << "Error exception:%s\n" << e.what();
	}

	return 0;
}