#include  <iostream>
#include  <string>
#include  <sstream>
#include  <curl/curl.h>

size_t  receive_data(void  *ptr,  size_t  size,  size_t  nmemb,  void  *stream){
    std::string data((const  char*) ptr,  (size_t) size * nmemb);
    *((std::stringstream*) stream)  << data;
    return size * nmemb;
}
void statistic_comma_nb(std::string str);
void  request()  {
    CURL *pCurl =  NULL;
    CURLcode res;
    curl_global_init(CURL_GLOBAL_ALL);
    pCurl =  curl_easy_init();
    if  (NULL  != pCurl)  {
        std::stringstream out;
        curl_easy_setopt(pCurl, CURLOPT_TIMEOUT,  3);
        curl_easy_setopt(pCurl, CURLOPT_URL,  "https://dataapi.joinquant.com/apis");
        curl_slist *plist =  curl_slist_append(NULL,  "Content-Type:application/json;charset=UTF-8");
        curl_easy_setopt(pCurl, CURLOPT_HTTPHEADER, plist);
        const  char* szJsonData =  "{\"method\": \"get_token\",\"mob\": \"13918934560\",\"pwd\": \"Panjiaqi7395\"}";
        curl_easy_setopt(pCurl, CURLOPT_POSTFIELDS, szJsonData);
        curl_easy_setopt(pCurl, CURLOPT_WRITEFUNCTION, receive_data);
        curl_easy_setopt(pCurl, CURLOPT_WRITEDATA,  &out);
        res =  curl_easy_perform(pCurl);
        std::string token =  out.str();
        std::cout << token << std::endl;
        std::stringstream data;
        std::string params =  "{\"method\": \"get_all_securities\",\"token\": \""+token+"\",\"code\": \"stock\"}";
        const  char* jsonData =  (char*)params.c_str();
        curl_easy_setopt(pCurl, CURLOPT_POSTFIELDS, jsonData);
        curl_easy_setopt(pCurl, CURLOPT_WRITEDATA,  &data);
        res =  curl_easy_perform(pCurl);
        std::cout <<  data.str()  << std::endl;
        statistic_comma_nb(data.str());
        curl_easy_cleanup(pCurl);
    }
    curl_global_cleanup();
}
void statistic_comma_nb(std::string str)
{
    std::cout<<"stocks' size is : "<<str.size()/5<<std::endl;
    std::cout<<"stocks' size is : "<<str.at(str.size()-6)<<std::endl;
}
int  main(void)  {
    request();
}