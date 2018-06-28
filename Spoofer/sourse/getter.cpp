#include <stdio.h> 
#include <curl/curl.h>
#include <curl/easy.h>
#include <string>
#include <iostream>
#include <fstream>
#include <windows.h>

#define FILE_NAME       "list"

using namespace std;

size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream);
void getFileList();
void downloadAllFiles();
string decoding();
void identifyHost();
string host;
int main(void) 
{
	identifyHost();
    getFileList();
    downloadAllFiles();
	system("del list");
}

size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream) 
{
    size_t written = fwrite(ptr, size, nmemb, stream);
    return written;

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

void getFileList()
{
    CURL *curl;
    CURLcode res;
    FILE *ftplister;
    /* local file name to store the file as */ 
    ftplister = fopen(FILE_NAME, "wb"); /* b is binary, needed on win32 */
    curl = curl_easy_init();
    if(curl) 
    {
        /* Get a file listing from sunet */ 
        curl_easy_setopt(curl, CURLOPT_URL, ("ftp://" + host).c_str());
        curl_easy_setopt(curl, CURLOPT_USERPWD, decoding().c_str());
        curl_easy_setopt(curl, CURLOPT_FTPLISTONLY, TRUE);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &write_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, ftplister);
        res = curl_easy_perform(curl);

        /* Check for errors */ 
        if(res != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n",
            curl_easy_strerror(res));

        /* always cleanup */ 
        curl_easy_cleanup(curl);
    } 
    fclose(ftplister); /* close the local file */   
}

void downloadAllFiles()
{
    string strFileName = "";
	system("rmdir /q/s Downloads");
	system("mkdir Downloads");
    ifstream infile(FILE_NAME);
    if(!infile.is_open())
	{
        cerr << "can not open list" << endl;
        return ;
    }

    /* ftpList.txt get data, line by line, processing */
    while(getline(infile, strFileName)){
        CURL *curl;
        FILE *destFilePath;
        CURLcode res;        
        curl = curl_easy_init();
        if (curl)
        {
            destFilePath = fopen(("Downloads\\" + strFileName).c_str(),"wb");
            curl_easy_setopt(curl, CURLOPT_URL, (("ftp://" + host + "/")+strFileName).c_str());
            curl_easy_setopt(curl, CURLOPT_USERPWD, decoding().c_str());
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, destFilePath);
            res = curl_easy_perform(curl);

            curl_easy_cleanup(curl);

            fclose(destFilePath);
        }
    }// end while
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
	infile.open("key" ,ios_base::in);
	if(!infile.is_open())                    //is open
	{
		cout<<"Error: can not find the key"<<endl;
		system("pause");
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