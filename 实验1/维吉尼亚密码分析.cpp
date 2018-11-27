#include<iostream>
#include<string>
#include<string.h>
using namespace std;

int Keylenth(string c);
string Key(int klen, string c);
void decode(string key, string c, int len);

int main()
{
    string ciphertext;
    cin >> ciphertext;
    int klen = Keylenth(ciphertext);
    string key = Key(klen,ciphertext);
    decode(key,ciphertext,klen);
    return 0;
}

int Keylenth(string c) 
{
    int klen = 1;   //密钥长度
    int clen = strlen(c.c_str());   //密文的长度 		     	
    while(1)
    {
        float IC[klen]; //重合指数
	    float avgIC = 0;  //平均重合指数(若m>1,密文串会分成m组,每一组应该是一组移位密码)
	    for(int i = 0;i < klen;i++)    //统计分组字母个数 
    	{		
    	    int out[26]={ 0 };   //存储每个字母的频数
    		for(int j = 0;i + j * klen < clen;j++)
    		   out[(int)(c[i + j * klen] - 'A')]++;  
            float e = 0.000f;
            int L = 0;
            for(int k = 0;k < 26;k++)    //子串密文长度 
                L += out[k];
            L = L * (L - 1);
    	    for(int k = 0;k < 26;k++)        //分组计算重合指数IC 
    	       if(out[k] != 0)
    	           e += ((float)out[k] * (float)(out[k] - 1)) / float(L);
    		IC[i] = e;
        }

    	for(int i = 0;i < klen;i++)
    	   avgIC += IC[i];
    	avgIC /= klen;          //求IC的平均值  

        if (avgIC >= 0.06)
            break;    //如果重合指数的值大于0.06,那么基本可以确定m的值是正确的
        else  klen++;
    }
    cout<<"length of key:"<<klen<<endl; 
    return klen;
}

string Key(int klen, string c)
{
    int clen = strlen(c.c_str());
    float p[26] = {0.082, 0.015, 0.028, 0.043, 0.127, 0.022, 0.02, 0.061, 0.07, 0.002, 0.008, 0.04, 0.024, 0.067, 0.075, 0.019, 0.001, 0.06, 0.063, 0.091, 0.028, 0.01, 0.023, 0.001, 0.02, 0.001};  //自然语言中26个英文字母出现的概率
    int key[100] = {0};    //存放密钥 
    for(int i = 0;i < klen;i++)    //统计分组字母个数 
    { 
        int g = 0;   //每一组移位密码移位的位数
        for(int t = 0;t < 26;t++)
        {
            float x = 0.000f;    //拟重合指数  
            int out[26]={0};   //存储每个字母的频数
            for(int j = 0;i + j * klen < clen;j++)
                out[(int)(c[i + j * klen] - 'A')]++;  
            int L = 0;
            for(int k = 0;k < 26;k++)      //子串密文长度 
                L += out[k];
            for(int k = 0;k < 26;k++)
                x = x + p[k] * out[(k + g) % 26];
            if(x / L > 0.055)
            {
                key[i] = g;
                break;
            }
            else g++;
        }
    }
    cout<<"key:"; 
    string k;
    for(int i=0;i<klen;i++) //输出密钥字 
    {  
        cout<<char('a'+key[i]);
        k += char('a'+key[i]);
    }
    cout<<endl;
    return k;
}

void decode(string key, string c, int len)
{
    int k[len];   //密钥的数字表示
    int x[strlen(c.c_str())];   //明文的数字表示存储在里面
    
    for(int i = 0; i < len; i++)  //将密钥转换为数字表示
    {
        k[i] = key[i] - 'a';
    }
    int m = strlen(c.c_str()) / len;
    int n = strlen(c.c_str()) % len;
    
    for(int i = 0; i < m; ++i)   //恢复明文
    {
        for(int j = len * i; j < len * (i+1); ++j)
        {
        	if((int)c[j] - 'A' - k[j - len * i] < 0)
        		x[j] = (int)c[j] - 'A' - k[j - len * i] + 26;
        	else
            	x[j] = ( (int)c[j] - 'A' - k[j - len * i]) % 26;
//            cout << char(x[j] + 'a');
        }
//        cout << endl;
    }
    for(int i = 0; i < n; ++i)
    {
    	if((int)c[m * len + i] - 'A' - k[i] < 0)
    		x[m * len + i] = (int)c[m * len + i] - 'A' - k[i] + 26;
        else
        	x[m * len + i] = ( (int)c[m * len + i] - 'A' - k[i]) % 26;
    }

    cout << "message is:";
    for(unsigned int i = 0; i < strlen(c.c_str()); ++i)
    {
        cout << char(x[i] + 'a');
    }
    cout << endl;
}

// KCCPKBGUFDPHQTYAVINRRTMVGRKDNBVFDETDGILTXRGUDDKOTFMBPVGEGLTGCKQRACQCWDNAWCRXIZAKFTLEWRPTYCQKYVXCHKFTPONCQQRHJVAJUWETMCMSPKQDYHJVDAHCTRLSVSKCGCZQQDZXGSFRLSWCWSJTBHAFSIASPRJAHKJRJUMVGKMITZHFPDISPZLVLGWTFPLKKEBDPGCEBSHCTJRWXBAFSPEZQNRWXCVYCGAONWDDKACKAWBBIKFTIOVKCGGHJVLNHTFFSQESVYCLACNVRWBBIREPBBVFEXOSCDYGZWPFDTKFQIYCWHJVLNHIQIBTKHJVNPIST