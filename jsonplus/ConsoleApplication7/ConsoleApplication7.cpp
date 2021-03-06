// ConsoleApplication7.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <stack>

#include "jsvar.h"
#include "jsstring.h"
#include "jsarray.h" 
#include "jsobject.h"
#include "jsnull.h"
#include "jsboolean.h"
#include "jsnumber.h"

using std::stack;
stack <char> tokens;
stack <JSVar*> vars;

int readNum(const string &jsonStr, int pos);
int readStr(const string &jsonStr, int pos);
void readArr();
void readObj();
void getToken(char s);
void parser(const string &jsonStr);

int main()
{
	tokens.push(0);
	/*
	string sample(R"++({"text":"MXCHIP won a prize",

         "id": 1234,

         "detail":{

                      "comp": "MXCHIP.Inc",

                      "from":"ShangHai",

                      "focus":"Internet of Things",

                      "module":[{"k":"EMW3165"},{"k":"EMW3166"},{"k":"EMW3031"},{"k":"EMW3239"}]

                         }} )++");
	*/
	/*
	string sample
	(R"++(
{

　　　　　　"name":"王尼玛",

　　　　　　"fans":[{

　　　　　　　　　　　　"name":"小王",

　　　　　　　　　　　　"age":"7"

　　　　　　　　　　　},{

　　　　　　　　　　　　"name":"小尼玛",

　　　　　　　　　　　　"age":"10"

　　　　　　　　　　　}]

　　　　　　}
		 )++");
	*/

	string sample(R"++(
{  
    "data": {  
        "feedbacks": {  },  
        "liketeamlist": [  
            {  
                "limage": "http://baidu.com.465.jpg",  
                "lmarketprice": 199,  
                "lteamId": 386,  
                "lteamprice": 38,  
                "ltitle": "我才是测试文本哦,用于测试此次验证。"  
            },  
            {  
                "limage": "http://baidu.com/37.jpg",  
                "lmarketprice": 3380,  
                "lteamId": 57133,  
                "lteamprice": 580,  
                "ltitle": "测试文本,15级软件开发！"  
            }  
        ],  
        "partnerteamlist": [  
            {  
                "pteamId": 35,  
                "pteamprice": 228,  
                "ptitle": "计算机应用专业。"  
            },  
            {  
                "pteamId": 72598,  
                "pteamprice": 2888,  
                "ptitle": "潍坊职业学院。"  
            },  
            {  
                "pteamId": 3613,  
                "pteamprice": 499,  
                "ptitle": "2015级！"  
            },  
            {  
                "pteamId": 72638,  
                "pteamprice": 4299,  
                "ptitle": "本次测试于16年9月7日。"  
            },  
            {  
                "pteamId": 716,  
                "pteamprice": 38,  
                "ptitle": "后期持续更新！"  
            }  
        ]  
    }
} 



)++");

	parser(sample);
	vars.top()->display();
	auto a = vars.top();
	auto b = dynamic_cast<JSObject*>(a);
	(*b)["data"]->display();
	vars.pop();
	getchar();
    return 0;
}

int readNum(const string &jsonStr, int pos)
{
	string t;
	while (jsonStr[pos] != ',' && jsonStr[pos] != ' ')
	{
		t.push_back(jsonStr[pos]);
		++pos;
	}
	vars.push(new JSNumber(t));
	return pos;
}

int readStr(const string &jsonStr, int pos)
{
	string t;
	bool inStr = true;
	bool escape = false;
	++pos;
	while (true)
	{
		if (escape)
		{
			escape = false;
			t.push_back(jsonStr[pos]);
			++pos;
		}
		else
		{
			escape = (jsonStr[pos] == '\\');
			inStr = jsonStr[pos] != tokens.top();
			if (inStr)
			{
				t.push_back(jsonStr[pos]);
				++pos;
			}
			else
				break;
		}
	}
	vars.push(new JSString(t));
	return pos;
};

void getToken(char s)
{
	if (s >= '0' && s <= '9' || s == '-')
	{
		tokens.push('d');
	}
	switch (s)
	{
	case '\"': // q
	case '\'': // q
	case 't':
	case 'f':
	case 'n':
	case '{':
	case '[':
	case '}':
	case ']':
		tokens.push(s);
		return;
	}
}

void readArr()
{
	JSArray * tmpArr = new JSArray;
	tokens.pop();
	while (tokens.top() != '[')
	{
		tmpArr->push_front(vars.top());
		vars.pop();
		tokens.pop();
	}
	vars.push(tmpArr);
}

void readObj()
{
	JSObject* tmpObj = new JSObject;
	tokens.pop();
	while (tokens.top() != '{')
	{
		JSVar* t = vars.top();
		vars.pop();
		tokens.pop();
		string s = vars.top()->toString();
		vars.pop();
		tokens.pop();
		tmpObj->push(make_pair(s, t));
	}
	vars.push(tmpObj);
}

void parser(const string &jsonStr)
{
	for (int i = 0; i < jsonStr.length(); ++i)
	{
		getToken(jsonStr[i]);
		switch (tokens.top())
			{
			case 'n':
				vars.push(new JSNull);
				tokens.pop();
				tokens.push('e');
				i += 3;
				break;
			case 'f':
				vars.push(new JSBoolean(false));
				tokens.pop();
				tokens.push('e');
				i += 4;
				break;
			case 't':
				vars.push(new JSBoolean(true));
				tokens.pop();
				tokens.push('e');
				i += 3;
				break;
			case 'd':
				i = readNum(jsonStr, i);
				tokens.pop();
				tokens.push('e');
				break;
			case '\"':
			case '\'':
				i = readStr(jsonStr, i);
				tokens.pop();
				tokens.push('e');
				break;
			case ']':
				readArr();
				tokens.pop();
				tokens.push('e');
				break;
			case '}':
				readObj();
				tokens.pop();
				tokens.push('e');
				break;
		}
	}
}
