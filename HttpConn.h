#pragma once
#include<string>
#include <iostream>

class HttpConn {
public:
	std::string host;
	HttpConn() {}
	HttpConn(std::string _url);
	int ope(const std::string& path, const std::string& fileN, const std::string& ope, const std::string& headers, const std::string& _post);
};