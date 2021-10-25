#include  <iostream>
#include  <string>
#include  <sstream>
#include  <curl/curl.h>
#include  <vector>
#include <controller.h>
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
std::vector<std::string> sub_string_array;

void statistic_comma_nb(std::string str)
{
    std::cout<<"stocks' size is : "<<str.size()/5<<std::endl;
    std::cout<<"stocks' size is : "<<str.at(str.size()-6)<<std::endl;
    static int line_nb=0;
    int comma_acumulator=0;
    char array_tmp[100];
    int array_tmp_count=0;
    for(auto i=str.begin();i<=str.end();i++)
    {
        array_tmp[array_tmp_count++]=*i;
        if((*i)=='\n')
        {
            
            array_tmp[array_tmp_count-1]='\0';
            // stock_name_array.copy(array_tmp,array_tmp_count,0);
            std::string stock_name_array=array_tmp;
            sub_string_array.push_back(stock_name_array);
            std::cout<<array_tmp<<std::endl;
            comma_acumulator++;
            line_nb++;
            array_tmp_count=0;
            // std::cout<<i[0]<<comma_nb<<std::endl;
            // if(comma_acumulator==)
        }
    }
    std::cout<<"line_nb is : "<<line_nb<<std::endl;
    std::cout<<"line_nb is : "<<sub_string_array.size()<<std::endl;
    //decode the first line
    auto first_line_string = sub_string_array.at(0);
    int id=0;
    std::vector<std::string> item_name;
    char array_t[100];
    int array_t_count=0;
    for(int i=0;i<first_line_string.size()+1;i++)
    {
        array_t[array_t_count++] = (first_line_string.c_str()[i]);
        if(first_line_string.c_str()[i]==',' || first_line_string.c_str()[i]=='\0')
        {
            array_t[array_t_count-1] = '\0';
            std::string item = array_t;
            item_name.push_back(item);
            array_t_count=0;
        }
    }
    std::cout<<"item nb is "<<item_name.size()<<std::endl;
    for(int i=0;i<item_name.size();i++)
    {
        std::cout<<"item["<<i<<"]: "<<item_name.at(i).c_str()<<std::endl;
    }
}
int  main(void)  {
    stock_sdk_space::stock_sdk stock_sdk_obj = stock_sdk_space::stock_sdk("13918934560","Panjiaqi7395");
    stock_sdk_obj.get_stock_data();
    stock_sdk_obj.get_price_data();
    // stock_sdk_obj.log_stock_info_by_codeNB(600104);
    stock_sdk_obj.find_strong10days_week3days(0.08,-0.02);
    // stock_sdk_obj.get_priceInfo_10Days(600104);
    // request()  ;
}