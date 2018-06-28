#include <fstream>
#include <iostream>
#include <curl/curl.h>
#include <sys/stat.h>

#define FILE_NAME         "counter"

using namespace std;

string host;

size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream);
size_t read_data(void *ptr, size_t size, size_t nmemb, FILE *stream);
void identifyHost();
void downlodFile();
void add();
void uploadFile();
string decoding();

int main()
{
	identifyHost();
	downlodFile();
	add();
	uploadFile();

}

size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream) 
{
    return fwrite(ptr, size, nmemb, stream);
}

size_t read_data(void *ptr, size_t size, size_t nmemb, FILE *stream)
{
	return fread(ptr ,size ,nmemb ,stream);
}

void identifyHost()
{
	ifstream infile("key" ,ios_base::in);
	if(!infile.is_open())                    //is open
	{
		cout<<"Error: can not find the key"<<endl;
		system("pause");
		exit(1);
	}
	infile>>host;infile>>host;
	infile.close();
}

void downlodFile()
{
	CURL *curl;
	CURLcode result;
	curl = curl_easy_init();
	FILE *file;
	if(curl)
	{
		file = fopen(FILE_NAME,"w");
		curl_easy_setopt(curl ,CURLOPT_URL ,("ftp://" + host + "/" FILE_NAME + ".txt").c_str());
		curl_easy_setopt(curl ,CURLOPT_USERPWD ,decoding().c_str());
		curl_easy_setopt(curl ,CURLOPT_WRITEFUNCTION,write_data);
		curl_easy_setopt(curl ,CURLOPT_WRITEDATA,file);
		result = curl_easy_perform(curl);
		
		if(result != CURLE_OK)
		{
			curl_easy_strerror(result);
			fwrite("0",1,1,file);
			cout<<"no"<<endl;
		}
		curl_easy_cleanup(curl);
	}
	fclose(file);
}

void add()
{
	char number[4];
	FILE *file;
	file = fopen(FILE_NAME,"r");
	fread(number,1,4,file);
	fclose(file);
	file = fopen(FILE_NAME,"w");
	itoa(atoi(number)+1,number,10);
	fwrite(number,1,strlen(number),file);
	fclose(file);
}

void uploadFile()
{
	CURL *curl;
	CURLcode result;
	struct curl_slist *headerlist=NULL;
	struct stat file_info;
	curl_off_t fsize;
	FILE *file;
	
	stat(FILE_NAME, &file_info);
	fsize = (curl_off_t)file_info.st_size;
	curl = curl_easy_init();
	if(curl)
	{
		file = fopen(FILE_NAME ,"r");
		curl_easy_setopt(curl ,CURLOPT_URL ,("ftp://" + host + "/" FILE_NAME + ".txt").c_str());
		curl_easy_setopt(curl ,CURLOPT_USERPWD ,decoding().c_str());
		curl_easy_setopt(curl ,CURLOPT_READFUNCTION,read_data);
		curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);
		curl_easy_setopt(curl, CURLOPT_POSTQUOTE, headerlist);
		curl_easy_setopt(curl, CURLOPT_INFILESIZE_LARGE,(curl_off_t)fsize);
		curl_easy_setopt(curl ,CURLOPT_READDATA ,file);
		result = curl_easy_perform(curl);
		if(result != CURLE_OK)
			curl_easy_strerror(result);
		curl_easy_cleanup(curl);
	}
	fclose(file);
}

string decoding()
{
	//variables
	int r;
	char temp[6];
	string userpass;
	string key;
	ifstream infile;
	
	//decoding
	infile.open("key" ,ios::binary);
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
	return userpass;
}
