#include"HttpConn.h"
#include "json/json.h"
#include <fstream>
#include <sstream>
#include <windows.h>
#include <wininet.h>
#pragma comment(lib, "Wininet.lib")
#include <tchar.h>
using namespace std;

HttpConn::HttpConn(std::string _url) {
	host = _url;
}

int HttpConn::ope(const std::string &path, const std::string &fileN,const std::string &oper, const std::string &headers, const std::string &_post) {
	/**
	 *   解析网址为主机、端口和目标页面
	 */
	char* pst = new char[_post.size() + 5];
	for (int i = 0; i < _post.size(); i++) pst[i] = _post[i];
	pst[_post.size()] = '\0';
	std::string url = host + path;
	TCHAR szHostName[128];
	TCHAR szUrlPath[256];
	URL_COMPONENTS crackedURL = { 0 };
	crackedURL.dwStructSize = sizeof(URL_COMPONENTS);
	crackedURL.lpszHostName = szHostName;
	crackedURL.dwHostNameLength = ARRAYSIZE(szHostName);
	crackedURL.lpszUrlPath = szUrlPath;
	crackedURL.dwUrlPathLength = ARRAYSIZE(szUrlPath);
	InternetCrackUrl(url.c_str(), (DWORD)_tcslen(url.c_str()), 0, &crackedURL);

	/**
	 *   http请求相关初始化工作
	 */
	HINTERNET hInternet = InternetOpen(_T("Microsoft InternetExplorer"), INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
	if (hInternet == NULL) {
		delete[]pst;
		return -1;
	}

	HINTERNET hHttpSession = InternetConnect(hInternet, crackedURL.lpszHostName, crackedURL.nPort, NULL, NULL, INTERNET_SERVICE_HTTP, 0, 0);
	if (hHttpSession == NULL)
	{
		InternetCloseHandle(hInternet);
		delete[]pst;
		return -2;
	}

	HINTERNET hHttpRequest = HttpOpenRequest(hHttpSession, _T(oper.c_str()), crackedURL.lpszUrlPath, NULL, _T(""), NULL, 0, 0);
	if (hHttpRequest == NULL)
	{
		InternetCloseHandle(hHttpSession);
		InternetCloseHandle(hInternet);
		delete[]pst;
		return -3;
	}
	stringstream ss;
	string tmp;
	ss << headers;
	while (getline(ss, tmp)) {
		if (!HttpAddRequestHeadersA(hHttpRequest, tmp.c_str(), tmp.length(), HTTP_ADDREQ_FLAG_ADD)) {
			InternetCloseHandle(hHttpRequest);
			InternetCloseHandle(hHttpSession);
			InternetCloseHandle(hInternet);
			delete[]pst;
			return -5;
		}
	}
	/**
	 * 查询http状态码（这一步不是必须的）,但是HttpSendRequest()必须要调用
	 */
	DWORD dwRetCode = 0;
	DWORD dwSizeOfRq = sizeof(DWORD);
	if (!HttpSendRequest(hHttpRequest, NULL, NULL, pst, _post.size()))
	{
		InternetCloseHandle(hHttpRequest);
		InternetCloseHandle(hHttpSession);
		InternetCloseHandle(hInternet);
		delete[]pst;
		return -4;
	}

	/**
	*  查询文件大小
	*/
	DWORD dwContentLen;
	//这个地方有错误，参见后面分析！ 
	if (!InternetQueryDataAvailable(hHttpRequest, &dwContentLen, 0, 0) || dwContentLen == 0)
	{
		InternetCloseHandle(hHttpRequest);
		InternetCloseHandle(hHttpSession);
		InternetCloseHandle(hInternet);
		delete[]pst;
		return -6;
	}

	FILE* file = fopen((fileN + ".json").c_str(), "wb+");
	if (file == NULL)
	{
		InternetCloseHandle(hHttpRequest);
		InternetCloseHandle(hHttpSession);
		InternetCloseHandle(hInternet);
		delete[]pst;
		return -7;
	}



	DWORD dwError;
	DWORD dwBytesRead;
	DWORD nCurrentBytes = 0;
	char szBuffer[1024] = { 0 };
	while (TRUE)
	{
		//开始读取文件
		if (InternetReadFile(hHttpRequest, szBuffer, sizeof(szBuffer), &dwBytesRead))
		{
			if (dwBytesRead == 0)
			{
				break;
			}

			nCurrentBytes += dwBytesRead;
			fwrite(szBuffer, 1, dwBytesRead, file);
		}
		else
		{
			dwError = GetLastError();
			break;
		}
	}



	fclose(file);
	InternetCloseHandle(hInternet);
	InternetCloseHandle(hHttpSession);
	InternetCloseHandle(hHttpRequest);

	delete[]pst;
	return 0;
}
